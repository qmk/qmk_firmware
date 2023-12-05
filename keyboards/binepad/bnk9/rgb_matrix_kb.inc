// Copyright 2023 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifdef VIA_ENABLE

// Declare custom effects using the RGB_MATRIX_EFFECT macro
RGB_MATRIX_EFFECT(bnk9_per_key_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "eeprom.h"
#include "eeconfig.h"
#include "via.h"
#include "bkn9.h"

// Per-key color effect

static bool bnk9_per_key_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    HSV hsv;
    RGB rgb;

    // Assuming `user_config` is set prior

    hsv.v = rgb_matrix_get_val();
    for (uint8_t i = led_min; i < led_max; i++) {
        if (i < 9) {
            hsv.h = user_config.color[i].h;
            hsv.s = user_config.color[i].s;
            rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif  // VIA_ENABLE
