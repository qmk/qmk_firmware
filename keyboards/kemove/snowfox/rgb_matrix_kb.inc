// Copyright 2026 Michael Loukeris (@milouk)
// SPDX-License-Identifier: GPL-2.0-or-later

// Typing speed: the keyboard goes from dim blue at rest
// to bright red at 120 words per minute and up.
RGB_MATRIX_EFFECT(TYPING_SPEED)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#    include "wpm.h"

#    define TYPING_SPEED_MAX_WPM 120

static bool TYPING_SPEED(effect_params_t *params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t wpm = get_current_wpm();
    if (wpm > TYPING_SPEED_MAX_WPM) {
        wpm = TYPING_SPEED_MAX_WPM;
    }
    hsv_t hsv = rgb_matrix_config.hsv;
    hsv.h     = 170 - (uint16_t)wpm * 170 / TYPING_SPEED_MAX_WPM;
    hsv.v     = scale8(hsv.v, 85 + (uint16_t)wpm * 170 / TYPING_SPEED_MAX_WPM);
    rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
