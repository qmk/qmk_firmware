// Copyright 2026 Hiiwwy
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#define XL_87_RGB_SCROLL_LOCK_LED 14
#define XL_87_RGB_CAPS_LOCK_LED   62

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    led_t led_state = host_keyboard_led_state();

    if (led_state.caps_lock) {
        rgb_matrix_set_color(XL_87_RGB_CAPS_LOCK_LED, RGB_WHITE);
    }

    if (led_state.scroll_lock) {
        rgb_matrix_set_color(XL_87_RGB_SCROLL_LOCK_LED, RGB_WHITE);
    }

    return true;
}
