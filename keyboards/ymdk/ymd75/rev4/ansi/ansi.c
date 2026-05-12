// Copyright 2021 Mike Tsao
// Copyright 2026 Steffen Olszewski (@sodevel)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(46, 200, 0, 0);
    }

    if (keymap_config.nkro && get_highest_layer(layer_state) == 1) {
        rgb_matrix_set_color(66, 200, 0, 0);
    }

    if (keymap_config.no_gui && get_highest_layer(layer_state) == 1) {
        rgb_matrix_set_color(75, 200, 0, 0);
    }

    return true;
}

#endif // #ifdef RGB_MATRIX_ENABLE
