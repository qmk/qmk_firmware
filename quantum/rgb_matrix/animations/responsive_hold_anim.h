// Copyright @filterpaper
// SPDX-License-Identifier: GPL-2.0+

#ifdef ENABLE_RGB_MATRIX_RESPONSIVE_HOLD
RGB_MATRIX_EFFECT(RESPONSIVE_HOLD)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#        include "matrix.h"

bool RESPONSIVE_HOLD(effect_params_t* params) {
    // Store current brightness per LED
    static uint8_t  led_brightness[RGB_MATRIX_LED_COUNT] = {0};
    static uint8_t  decay;
    static uint32_t timer;

    if (params->iter == 0) {
        // On the first iteration, calculate brightness decay based on time scale since last update
        uint16_t ticks = MIN(g_rgb_timer - timer, 0xFFFF);
        uint8_t  phase = MIN(scale16by8(ticks, qadd8(rgb_matrix_config.speed, 1)), 0xFF);
        decay          = MAX(1, scale8(phase, rgb_matrix_config.hsv.v));
        timer          = g_rgb_timer;

        // Scan the key matrix and set maximum LED brightness for currently pressed keys
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            matrix_row_t row_state = matrix_get_row(row);
            if (!row_state) continue;
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                if (!((row_state >> col) & 1)) continue;
                uint8_t led = g_led_config.matrix_co[row][col];
                if (led < RGB_MATRIX_LED_COUNT) led_brightness[led] = rgb_matrix_config.hsv.v;
            }
        }
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; ++i) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_t rgb = {0, 0, 0};
        if (led_brightness[i] > 0) {
            // Apply a triangle wave hue shift to LEDs with brightness value
            uint8_t time = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed / 16, 1));
            uint8_t wave = triwave8(time) / 4;
            hsv_t   hsv  = rgb_matrix_config.hsv;
            hsv.h        = hsv.h - wave;
            hsv.v        = led_brightness[i];
            rgb          = rgb_matrix_hsv_to_rgb(hsv);
            // Fade brightness based on time since last update
            led_brightness[i] = qsub8(led_brightness[i], decay);
        }
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_RESPONSIVE_HOLD
