// Copyright 2023 Hyojin Bak (@eerraa)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
         return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(96, 0, 128, 128);
        rgb_matrix_set_color(97, 0, 128, 128);
        rgb_matrix_set_color(98, 0, 128, 128);
    }
    return true;
}