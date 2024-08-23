// Copyright 2024 Hyojin Bak (@eerraa)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
         return false;
    }
    
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(0, 200, 0, 0);
    } else {
        rgb_matrix_set_color(0, 0, 0, 0);
    }
    
    if (host_keyboard_led_state().scroll_lock) {
        rgb_matrix_set_color(1, 200, 0, 0);
    } else {
        rgb_matrix_set_color(1, 0, 0, 0);
    }
    
    return true;
}