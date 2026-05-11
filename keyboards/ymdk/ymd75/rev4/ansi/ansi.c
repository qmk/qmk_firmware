// Copyright 2021 Mike Tsao
// Copyright 2026 sodevel<steffen.o.dev@gmail.com>
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

    return true;
}

#endif // #ifdef RGB_MATRIX_ENABLE
