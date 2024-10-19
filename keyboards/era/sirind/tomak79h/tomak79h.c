// Copyright 2024 Hyojin Bak (@eerraa)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
         return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(87, 0, 128, 128);
        rgb_matrix_set_color(88, 0, 128, 128);
        rgb_matrix_set_color(89, 0, 128, 128);
        rgb_matrix_set_color(90, 0, 128, 128);
        rgb_matrix_set_color(91, 0, 128, 128);
        rgb_matrix_set_color(92, 0, 128, 128);
        rgb_matrix_set_color(93, 0, 128, 128);
        rgb_matrix_set_color(94, 0, 128, 128);
        rgb_matrix_set_color(95, 0, 128, 128);
    }
    return true;
}