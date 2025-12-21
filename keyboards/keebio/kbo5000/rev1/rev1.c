// Copyright 2025 Danny Nguyen (danny@keeb.io)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "split_util.h"

void matrix_init_kb(void) {
    gpio_set_pin_output(CAPS_LOCK_LED_PIN);
    matrix_init_user();
}

void led_update_ports(led_t led_state) {
    // Only update if left half
    if (is_keyboard_left()) {
        gpio_write_pin(CAPS_LOCK_LED_PIN, !led_state.caps_lock);
    }
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 2) {
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    return false;
}
