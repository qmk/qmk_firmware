// Copyright 2024 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

extern rgb_led_t rgb_matrix_ws2812_array[RGB_MATRIX_LED_COUNT];

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    /* Synchronize all led colors under the space key */
    for (uint8_t i = 83; i <= 87; i++) {
        rgb_matrix_ws2812_array[i].r = rgb_matrix_ws2812_array[85].r;
        rgb_matrix_ws2812_array[i].g = rgb_matrix_ws2812_array[85].g;
        rgb_matrix_ws2812_array[i].b = rgb_matrix_ws2812_array[85].b;
    }

    return true;
}

#endif