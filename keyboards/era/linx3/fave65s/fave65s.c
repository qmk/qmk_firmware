// Copyright 2024 Hyojin Bak (@eerraa)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
         return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(0, 0, 128, 128);
    } else {
        rgb_matrix_set_color(0, 0, 0, 0);
    }
    return true;
}
