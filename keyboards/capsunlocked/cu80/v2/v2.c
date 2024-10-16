// Copyright 2021 CapsUnlocked
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

void matrix_init_kb(void) {
    gpio_set_pin_output(E6);
    matrix_init_user();
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(62, 255, 255, 255);
    }
    if (host_keyboard_led_state().scroll_lock) {
        rgb_matrix_set_color(14, 255, 255, 255);
    }
    return true;
}
#endif
