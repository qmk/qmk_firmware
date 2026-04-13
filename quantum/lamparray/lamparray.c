// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include <string.h> // for memcpy
#include "lamparray.h"
#include "timer.h"
#include "lamparray_surface.h"
#include "keycodes.h"
#include "keymap_introspection.h"
#include "action_layer.h"

// Defaults are generated from info.json layout content
#ifndef LAMPARRAY_WIDTH
#    define LAMPARRAY_WIDTH ESTIMATED_KEYBOARD_WIDTH
#endif
#ifndef LAMPARRAY_HEIGHT
#    define LAMPARRAY_HEIGHT ESTIMATED_KEYBOARD_HEIGHT
#endif
#ifndef LAMPARRAY_DEPTH
#    define LAMPARRAY_DEPTH 30000
#endif
#ifndef LAMPARRAY_KIND
#    define LAMPARRAY_KIND LAMPARRAY_KIND_KEYBOARD
#endif

#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#    define LAMPARRAY_RED_LEVELS 255
#    define LAMPARRAY_GREEN_LEVELS 255
#    define LAMPARRAY_BLUE_LEVELS 255
#    define LAMPARRAY_INTENSITY_LEVELS 1
#    define LAMPARRAY_LAMP_COUNT RGB_MATRIX_LED_COUNT
#    define LAMPARRAY_UPDATE_INTERVAL (RGB_MATRIX_LED_FLUSH_LIMIT * 1000)
#endif

//****************************************************************************
// utils

/**
 * \brief Query a HID usage for a given location
 */
uint8_t lamparray_binding_at_keymap_location(uint8_t row, uint8_t col) {
    uint16_t keycode = keycode_at_keymap_location(get_highest_layer(default_layer_state), row, col);
    (void)keycode;
#if LAMPARRAY_KIND == LAMPARRAY_KIND_KEYBOARD
    // Basic QMK keycodes currently map directly to Keyboard UsagePage
    if (IS_BASIC_KEYCODE(keycode) || IS_MODIFIER_KEYCODE(keycode)) {
        return keycode;
    }
#elif LAMPARRAY_KIND == LAMPARRAY_KIND_MOUSE
    if ((keycode) >= KC_MS_BTN1 && (keycode) <= KC_MS_BTN5) {
        return keycode - KC_MS_BTN1 + 1;
    }
#endif
    return 0;
}

//****************************************************************************
// cache

static uint8_t input_binding_cache[LAMPARRAY_LAMP_COUNT];

void lamparray_update_cache(void) {
    for (uint8_t lamp_id = 0; lamp_id < LAMPARRAY_LAMP_COUNT; lamp_id++) {
        input_binding_cache[lamp_id] = lamparray_get_lamp_binding_impl(lamp_id);
    }
}

uint8_t lamparray_get_lamp_binding(uint16_t lamp_id) {
    return input_binding_cache[lamp_id];
}

//****************************************************************************
// queue

#ifndef LAMPARRAY_REQUEST_QUEUE_SIZE
#    define LAMPARRAY_REQUEST_QUEUE_SIZE 32
#endif

universal_lamparray_response_t request_queue[LAMPARRAY_REQUEST_QUEUE_SIZE] = {0};
uint8_t                        queue_size                                  = 0;

void lamparray_queue_request(universal_lamparray_response_t* report) {
    if (queue_size >= LAMPARRAY_REQUEST_QUEUE_SIZE) {
        return; // drop instead of overflowing
    }
    universal_lamparray_response_t* target = &request_queue[queue_size++];
    memcpy(target, report, sizeof(universal_lamparray_response_t));
}

void lamparray_handle_queue(void) {
    // Snapshot the queue size and reset atomically to avoid race with USB ISR
    uint8_t count = queue_size;
    queue_size    = 0;

    for (uint8_t id = 0; id < count; id++) {
        universal_lamparray_response_t* report = &request_queue[id];
        switch (report->report_id) {
            case LAMPARRAY_REPORT_ID_RANGE_UPDATE:
                lamparray_set_range(&report->range_update);
                break;
            case LAMPARRAY_REPORT_ID_MULTI_UPDATE:
                lamparray_set_items(&report->multi_update);
                break;
            case LAMPARRAY_REPORT_ID_CONTROL:
                lamparray_set_control_response(report->autonomous);
                break;
        }
    }
}

//****************************************************************************
// impl

static uint16_t cur_lamp_id       = 0;
static bool     is_autonomous     = true;
static uint32_t last_update_time  = 0;

// If no update from host in 5 seconds, revert to autonomous mode
#ifndef LAMPARRAY_HOST_TIMEOUT_MS
#    define LAMPARRAY_HOST_TIMEOUT_MS 5000
#endif

void lamparray_get_attributes(lamparray_attributes_t* data) {
    data->lamp_count      = LAMPARRAY_LAMP_COUNT;
    data->update_interval = LAMPARRAY_UPDATE_INTERVAL;
    data->kind            = LAMPARRAY_KIND;
    data->bounds.width    = LAMPARRAY_WIDTH;
    data->bounds.height   = LAMPARRAY_HEIGHT;
    data->bounds.depth    = LAMPARRAY_DEPTH;
}

void lamparray_get_attributes_response(lamparray_attributes_response_t* data) {
    data->lamp_id         = cur_lamp_id;
    data->update_latency  = 1000;
    data->is_programmable = 1;
    data->input_binding   = lamparray_get_lamp_binding(cur_lamp_id);

    data->levels.red       = LAMPARRAY_RED_LEVELS;
    data->levels.green     = LAMPARRAY_GREEN_LEVELS;
    data->levels.blue      = LAMPARRAY_BLUE_LEVELS;
    data->levels.intensity = LAMPARRAY_INTENSITY_LEVELS;

    lamparray_get_lamp_impl(cur_lamp_id, data);

    // Automatic address pointer incrementing - 26.8.1 LampAttributesRequestReport
    cur_lamp_id++;
    if (cur_lamp_id >= LAMPARRAY_LAMP_COUNT) cur_lamp_id = 0;
}

void lamparray_set_attributes_response(uint16_t lamp_id) {
    cur_lamp_id = lamp_id;
}

void lamparray_set_control_response(uint8_t autonomous) {
    is_autonomous = !!autonomous;
    last_update_time = timer_read32();

    lamparray_surface_enable(!autonomous);
}

void lamparray_set_range(lamparray_range_update_t* data) {
    if (is_autonomous) {
        return;
    }
    last_update_time = timer_read32();

    if ((data->start >= LAMPARRAY_LAMP_COUNT) || (data->end >= LAMPARRAY_LAMP_COUNT)) {
        return;
    }

    for (uint16_t index = data->start; index <= data->end; index++) {
        lamparray_surface_set_item(index, data->color);
    }

    if (data->flags & LAMP_UPDATE_FLAG_COMPLETE) {
        lamparray_surface_update_finished();
    }
}

void lamparray_set_items(lamparray_multi_update_t* data) {
    if (is_autonomous) {
        return;
    }
    last_update_time = timer_read32();

    if (data->count > LAMP_MULTI_UPDATE_LAMP_COUNT) {
        return;
    }

    for (uint8_t i = 0; i < data->count; i++) {
        if (data->ids[i] >= LAMPARRAY_LAMP_COUNT) {
            continue;
        }
        lamparray_surface_set_item(data->ids[i], data->colors[i]);
    }

    if (data->flags & LAMP_UPDATE_FLAG_COMPLETE) {
        lamparray_surface_update_finished();
    }
}

//****************************************************************************
// feature hooks

void lamparray_init(void) {
    lamparray_update_cache();
}

void lamparray_task(void) {
    lamparray_handle_queue();

    // Watchdog: if host stops sending updates, revert to autonomous mode
    // This prevents frozen LEDs when Windows disconnects without cleanup
    if (!is_autonomous && timer_elapsed32(last_update_time) > LAMPARRAY_HOST_TIMEOUT_MS) {
        lamparray_set_control_response(1); // force autonomous
    }
}

#ifdef RGB_MATRIX_ENABLE
#    include "lamparray_rgb_matrix.c"
#endif
