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
static bool             signal_queue_drain = false;

void encoder_init(void) {
    memset(&encoder_events, 0, sizeof(encoder_events));
    encoder_driver_init();
}

static void encoder_queue_drain(void) {
    encoder_events.tail     = encoder_events.head;
    encoder_events.dequeued = encoder_events.enqueued;
}

static bool encoder_handle_queue(void) {
    bool    changed = false;
    uint8_t index;
    bool    clockwise;
    while (encoder_dequeue_event(&index, &clockwise)) {
#ifdef ENCODER_MAP_ENABLE

        // The delays below cater for Windows and its wonderful requirements.
        action_exec(clockwise ? MAKE_ENCODER_CW_EVENT(index, true) : MAKE_ENCODER_CCW_EVENT(index, true));
#    if ENCODER_MAP_KEY_DELAY > 0
        wait_ms(ENCODER_MAP_KEY_DELAY);
#    endif // ENCODER_MAP_KEY_DELAY > 0

        action_exec(clockwise ? MAKE_ENCODER_CW_EVENT(index, false) : MAKE_ENCODER_CCW_EVENT(index, false));
#    if ENCODER_MAP_KEY_DELAY > 0
        wait_ms(ENCODER_MAP_KEY_DELAY);
#    endif // ENCODER_MAP_KEY_DELAY > 0

#else // ENCODER_MAP_ENABLE

        encoder_update_kb(index, clockwise);

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

    if (signal_queue_drain) {
        signal_queue_drain = false;
        encoder_queue_drain();
    }

    // Let the encoder driver produce events
    encoder_driver_task();

    // Process any events that were enqueued
    if (should_process_encoder()) {
        changed |= encoder_handle_queue();
    }

    return changed;
}

bool encoder_queue_full_advanced(encoder_events_t *events) {
    return events->tail == (events->head + 1) % MAX_QUEUED_ENCODER_EVENTS;
}

bool encoder_queue_full(void) {
    return encoder_queue_full_advanced(&encoder_events);
}

bool encoder_queue_empty_advanced(encoder_events_t *events) {
    return events->head == events->tail;
}

bool encoder_queue_empty(void) {
    return encoder_queue_empty_advanced(&encoder_events);
}

bool encoder_queue_event_advanced(encoder_events_t *events, uint8_t index, bool clockwise) {
    // Drop out if we're full
    if (encoder_queue_full_advanced(events)) {
        return false;
    }

    // Append the event
    encoder_event_t new_event   = {.index = index, .clockwise = clockwise ? 1 : 0};
    events->queue[events->head] = new_event;

    // Increment the head index
    events->head = (events->head + 1) % MAX_QUEUED_ENCODER_EVENTS;
    events->enqueued++;

    return true;
}

bool encoder_dequeue_event_advanced(encoder_events_t *events, uint8_t *index, bool *clockwise) {
    if (encoder_queue_empty_advanced(events)) {
        return false;
    }

    // Retrieve the event
    encoder_event_t event = events->queue[events->tail];
    *index                = event.index;
    *clockwise            = event.clockwise;

    // Increment the tail index
    events->tail = (events->tail + 1) % MAX_QUEUED_ENCODER_EVENTS;
    events->dequeued++;

    return true;
}

bool encoder_queue_event(uint8_t index, bool clockwise) {
    return encoder_queue_event_advanced(&encoder_events, index, clockwise);
}

bool encoder_dequeue_event(uint8_t *index, bool *clockwise) {
    return encoder_dequeue_event_advanced(&encoder_events, index, clockwise);
}

void encoder_retrieve_events(encoder_events_t *events) {
    memcpy(events, &encoder_events, sizeof(encoder_events));
}

void encoder_signal_queue_drain(void) {
    signal_queue_drain = true;
}

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
