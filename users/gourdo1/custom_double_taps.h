// Copyright 2022 Google LLC
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "gourdo1.h"

static bool process_capsnum(uint16_t keycode, keyrecord_t * record) {
    static bool toggled = false;
    static bool tapped = false;
    static uint16_t tap_timer = 0;

    if (keycode == CAPSNUM) {
        if (user_config.double_tap_shift_for_capslock) {
            // Act as TT(_NUMPADMOUSE)
            if (record -> event.pressed) { // CAPSNUM key was pressed
                // Check whether the key was recently tapped
                if (tapped && !timer_expired(record -> event.time, tap_timer)) {
                    // This is a double tap (or possibly a triple tap or more)
                    // Toggle the layer on.
                    toggled = true;
                } else if (toggled) {
                    // Otherwise if currently toggled, turn it off
                    toggled = false;
                    tapped = false;
                    layer_off(_NUMPADMOUSE);
                }
                // Set that the first tap occurred in a potential double tap
                tapped = true;
                tap_timer = record -> event.time + TAPPING_TERM;
                layer_on(_NUMPADMOUSE);
            } else if (!toggled) {
                // If not currently toggled, turn off on key release
                layer_off(_NUMPADMOUSE);
                return false;
            }
        } else { // When double_tap_shift_for_capslock == false
            // Act as KC_CAPS
            if (record -> event.pressed) {
                register_code(KC_CAPS);
            } else {
                unregister_code(KC_CAPS);
            }
        }
        return false;
    } else {
        // On an event with any other key, reset the double tap state
        tapped = false;
    }
    return true;
}

static bool process_esc_to_base(uint16_t keycode, keyrecord_t * record) {
    static bool tapped = false;
    static uint16_t tap_timer = 0;

    if (keycode == KC_ESC) {
        if (user_config.esc_double_tap_to_baselyr) {
            if (record -> event.pressed) {
                if (tapped && !timer_expired(record -> event.time, tap_timer)) {
                    // The key was double tapped.
                    layer_clear();
                }
                tapped = true;
                tap_timer = record -> event.time + TAPPING_TERM;
            }
        }
    } else {
        // On an event with any other key, reset the double tap state.
        tapped = false;
    }
    return true;
}
