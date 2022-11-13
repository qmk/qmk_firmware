// Copyright 2022 @filterpaper
// SPDX-License-Identifier: GPL-2.0+

#ifdef ENABLE_RGB_MATRIX_PIXEL_RAIN
RGB_MATRIX_EFFECT(PIXEL_RAIN)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool PIXEL_RAIN(effect_params_t* params) {
    static uint32_t wait_timer = 0;

    inline uint32_t interval(void) {
        return 500 / scale16by8(qadd8(rgb_matrix_config.speed, 16), 16);
    }

    inline void rain_pixel(uint8_t led_index) {
        if (!HAS_ANY_FLAGS(g_led_config.flags[led_index], params->flags)) {
            return;
        }
        if (random8() & 2) {
            rgb_matrix_set_color(led_index, 0, 0, 0);
        } else {
            HSV hsv = {random8(), random8_min_max(127, 255), rgb_matrix_config.hsv.v};
            RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
            rgb_matrix_set_color(led_index, rgb.r, rgb.g, rgb.b);
        }
        wait_timer = g_rgb_timer + interval();
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (g_rgb_timer > wait_timer) {
        rain_pixel(random8_max(RGB_MATRIX_LED_COUNT));
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_PIXEL_RAIN
