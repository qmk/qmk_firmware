// Copyright 2023 Massdrop, Inc.
// SPDX-License-Identifier: GPL-2.0-or-later
#ifdef RGB_MATRIX_ENABLE
#    include "host.h"
#    include "quantum.h"
#    include "rgb_matrix.h"

#    ifdef RGB_MATRIX_CAPS_LOCK_INDEX
bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    if (host_keyboard_led_state().caps_lock && (rgb_matrix_get_flags() != LED_FLAG_NONE)) {
        rgb_matrix_set_color(RGB_MATRIX_CAPS_LOCK_INDEX, RGB_WHITE);
    } else if (rgb_matrix_get_flags() == LED_FLAG_UNDERGLOW) {
        rgb_matrix_set_color(RGB_MATRIX_CAPS_LOCK_INDEX, RGB_OFF);
    }
    return true;
}
#    endif
#endif
