// Copyright (C) 2025 DOIO
// Copyright (C) 2025 ClownFish (@clownfish-og)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    hsv_t hsv = {0, 255, 100};
    switch (get_highest_layer(layer_state)) {
        case 0:
            hsv = (hsv_t){HSV_RED};
            break;
        case 1:
            hsv = (hsv_t){HSV_GREEN};
            break;
        case 2:
            hsv = (hsv_t){HSV_BLUE};
            break;
        case 3:
            hsv = (hsv_t){HSV_WHITE};
            break;
        default:
            hsv = (hsv_t){HSV_YELLOW};
            break;
        }
    hsv.v     = (rgb_matrix_get_val() * 70 / 200) + 30; //set indicator brightness range 30-100, vary based on RGB Matrix brightness
    rgb_t rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(9, rgb.r, rgb.g, rgb.b);
    return false;
}

#endif
