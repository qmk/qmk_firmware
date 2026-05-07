// Copyright 2022 @filterpaper
// SPDX-License-Identifier: GPL-2.0+

#ifdef ENABLE_RGB_MATRIX_PIXEL_RAIN
RGB_MATRIX_EFFECT(PIXEL_RAIN)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool PIXEL_RAIN(effect_params_t* params) {
    static uint8_t  index = 0;
    static uint32_t timer = 0;

    if (params->iter == 0 && params->init) {
        index = random8_max(RGB_MATRIX_LED_COUNT);
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (timer < g_rgb_timer) { // Execute when the delay period has elapsed
        if (led_min <= index && index < led_max && HAS_ANY_FLAGS(g_led_config.flags[index], params->flags)) {
            // Assign a random HSV color to hsv with 50% probability, otherwise assign zeroed hsv
            hsv_t hsv = (random8() & 2) ? (hsv_t){0, 0, 0} : (hsv_t){random8(), random8_min_max(127, 255), rgb_matrix_config.hsv.v};
            rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
            rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
        }
        if (!rgb_matrix_check_finished_leds(led_max)) {
            // In the final LED range, update the LED index and advance the timer for
            // the next cycle, scaling the delay between 256–2048 ms based on speed.
            index = random8_max(RGB_MATRIX_LED_COUNT);
            timer = g_rgb_timer + (2048 - scale16by8(1792, rgb_matrix_config.speed));
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_PIXEL_RAIN
