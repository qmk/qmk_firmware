// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "stront.h"
#include "display.h"

static bool display_enabled;

/* public function to be used in keymaps */
bool is_display_side(void) {
#ifdef STRONT_DISPLAY_RIGHT
    return !is_keyboard_left();
#endif
#ifdef STRONT_DISPLAY_LEFT
    return is_keyboard_left();
#endif
    return false;
}

/* public function to be used in keymaps */
bool is_display_enabled(void) {
    return display_enabled;
}

/* default encoder keys */
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    if (index == 0) {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code_delay(KC_RIGHT, 10);
        } else {
            tap_code_delay(KC_LEFT, 10);
        }
    }
    return true;
}

/* Caps Lock processing */
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res && display_enabled) {
        display_process_caps(led_state.caps_lock);
    }

    return res;
}

void housekeeping_task_kb(void) {
    if (display_enabled) {
        display_housekeeping_task();
    }

    housekeeping_task_user();
}

void keyboard_post_init_kb(void) {
    display_enabled = false;

    if (is_display_side()) {
        display_enabled = display_init_kb();
    }

    keyboard_post_init_user();
}
