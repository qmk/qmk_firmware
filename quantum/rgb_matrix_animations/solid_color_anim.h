RGB_MATRIX_EFFECT(SOLID_COLOR)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool SOLID_COLOR(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    RGB rgb     = hsv_to_rgb(rgb_matrix_config.hsv);
    HSV alt_hsv = rgb_matrix_config.hsv;
    alt_hsv.h  += rgb_matrix_alt_config.hsv.h;
    alt_hsv.s  += rgb_matrix_alt_config.hsv.s;
    alt_hsv.v  += rgb_matrix_alt_config.hsv.v;
    RGB alt_rgb = hsv_to_rgb(alt_hsv);

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        if (RGB_MATRIX_IS_UNDERGLOW()) {
            rgb_matrix_set_color(i, alt_rgb.r, alt_rgb.g, alt_rgb.b);
        } else {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
