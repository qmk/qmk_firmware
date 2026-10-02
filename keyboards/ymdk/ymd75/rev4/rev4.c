// Copyright 2026 zvecr<git@zvecr.com>
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

rgb_t rgb_matrix_hsv_to_rgb(hsv_t hsv);

static void rgb_matrix_set_color_hsv(int index, uint8_t hue, uint8_t sat, uint8_t val) {
    hsv_t hsv = {
        .h = hue,
        .s = sat,
        .v = (val > RGB_MATRIX_MAXIMUM_BRIGHTNESS) ? RGB_MATRIX_MAXIMUM_BRIGHTNESS : val,
    };

    rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
}

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color_hsv(46, HSV_WHITE);
    }
    return true;
}

#endif
