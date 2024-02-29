// Copyright 2022-2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <string.h>
#include "action.h"
#include "encoder.h"
#include "wait.h"

#ifndef ENCODER_MAP_KEY_DELAY
#    define ENCODER_MAP_KEY_DELAY TAP_CODE_DELAY
#endif

__attribute__((weak)) bool should_process_encoder(void) {
    return is_keyboard_master();
}

static encoder_events_t encoder_events;

void encoder_init(void) {
    memset(&encoder_events, 0, sizeof(encoder_events));
    encoder_driver_init();
}

static bool encoder_handle_queue(void) {
    bool changed = false;
    while (encoder_events.tail != encoder_events.head) {
        encoder_event_t event = encoder_events.queue[encoder_events.tail];
        encoder_events.tail   = (encoder_events.tail + 1) % MAX_QUEUED_ENCODER_EVENTS;

#ifdef ENCODER_MAP_ENABLE

        // The delays below cater for Windows and its wonderful requirements.
        action_exec(event.clockwise ? MAKE_ENCODER_CW_EVENT(event.index, true) : MAKE_ENCODER_CCW_EVENT(event.index, true));
#    if ENCODER_MAP_KEY_DELAY > 0
        wait_ms(ENCODER_MAP_KEY_DELAY);
#    endif // ENCODER_MAP_KEY_DELAY > 0

        action_exec(event.clockwise ? MAKE_ENCODER_CW_EVENT(event.index, false) : MAKE_ENCODER_CCW_EVENT(event.index, false));
#    if ENCODER_MAP_KEY_DELAY > 0
        wait_ms(ENCODER_MAP_KEY_DELAY);
#    endif // ENCODER_MAP_KEY_DELAY > 0

#else // ENCODER_MAP_ENABLE

        encoder_update_kb(event.index, event.clockwise ? true : false);

#endif // ENCODER_MAP_ENABLE

        changed = true;
    }
    return changed;
}

bool encoder_task(void) {
    bool changed = false;

#ifdef SPLIT_KEYBOARD
    // Attempt to process existing encoder events in case split handling has already enqueued events
    if (should_process_encoder()) {
        changed |= encoder_handle_queue();
    }
#endif // SPLIT_KEYBOARD

    // Let the encoder driver produce events
    encoder_driver_task();

    // Process any events that were enqueued
    if (should_process_encoder()) {
        changed |= encoder_handle_queue();
    }

    return changed;
}

bool encoder_queue_event(uint8_t index, bool clockwise) {
    // Drop out if we're full
    if ((encoder_events.head + 1) % MAX_QUEUED_ENCODER_EVENTS == encoder_events.tail) {
        return false;
    }

    // Append the event
    encoder_event_t new_event                 = {.index = index, .clockwise = clockwise ? 1 : 0};
    encoder_events.queue[encoder_events.head] = new_event;

    // Increment the head index
    encoder_events.head = (encoder_events.head + 1) % MAX_QUEUED_ENCODER_EVENTS;

    return true;
}

void encoder_retrieve_events(encoder_events_t *events) {
    memcpy(events, &encoder_events, sizeof(encoder_events));
}

#ifdef SPLIT_KEYBOARD
void encoder_set_tail_index(uint8_t tail_index) {
    encoder_events.tail = tail_index;
}

void encoder_handle_slave_events(encoder_events_t *events) {
    while (events->tail != events->head) {
        encoder_event_t event = events->queue[events->tail];
        events->tail          = (events->tail + 1) % MAX_QUEUED_ENCODER_EVENTS;
        encoder_queue_event(event.index, event.clockwise ? true : false);
    }
}
#endif // SPLIT_KEYBOARD

__attribute__((weak)) bool encoder_update_user(uint8_t index, bool clockwise) {
    return true;
}

__attribute__((weak)) bool encoder_update_kb(uint8_t index, bool clockwise) {
    bool res = encoder_update_user(index, clockwise);
#if !defined(ENCODER_TESTS)
    if (res) {
        if (clockwise) {
#    if defined(EXTRAKEY_ENABLE)
            tap_code_delay(KC_VOLU, 10);
#    elif defined(MOUSEKEY_ENABLE)
            tap_code_delay(KC_MS_WH_UP, 10);
#    else
            tap_code_delay(KC_PGDN, 10);
#    endif
        } else {
#    if defined(EXTRAKEY_ENABLE)
            tap_code_delay(KC_VOLD, 10);
#    elif defined(MOUSEKEY_ENABLE)
            tap_code_delay(KC_MS_WH_DOWN, 10);
#    else
            tap_code_delay(KC_PGUP, 10);
#    endif
        }
    }
#endif // ENCODER_TESTS
    return res;
}
