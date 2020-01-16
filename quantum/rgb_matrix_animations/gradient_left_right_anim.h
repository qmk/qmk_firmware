#ifndef DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
RGB_MATRIX_EFFECT(GRADIENT_LEFT_RIGHT)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool GRADIENT_LEFT_RIGHT(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    HSV led_hsv;
    HSV hsv       = rgb_matrix_config.hsv;
    HSV alt_hsv   = rgb_matrix_config.hsv;
    alt_hsv.h    += rgb_matrix_alt_config.hsv.h;
    alt_hsv.s    += rgb_matrix_alt_config.hsv.s;
    alt_hsv.v    += rgb_matrix_alt_config.hsv.v;

    uint8_t led_scale;
    uint8_t scale     = scale8(64, rgb_matrix_config.speed);
    uint8_t alt_scale = scale8(64, rgb_matrix_config.speed + rgb_matrix_alt_config.speed);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        // The x range will be 0..224, map this to 0..7
        // Relies on hue being 8-bit and wrapping
        if (RGB_MATRIX_IS_UNDERGLOW()) {
            led_hsv = alt_hsv;
            led_scale = alt_scale;
        } else {
            led_hsv = hsv;
            led_scale = scale;
        }
        led_hsv.h   = led_hsv.h + (led_scale * g_led_config.point[i].x >> 5);
        RGB rgb = hsv_to_rgb(led_hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return led_max < DRIVER_LED_TOTAL;
}

#    endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif      // DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
