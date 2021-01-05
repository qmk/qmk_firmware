RGB_MATRIX_EFFECT(raw_rgb)

#if defined(RGB_MATRIX_CUSTOM_EFFECT_IMPLS)
uint8_t raw_rgb_r = 0;
uint8_t raw_rgb_g = 0;
uint8_t raw_rgb_b = 0;

static bool raw_rgb(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, raw_rgb_r, raw_rgb_g, raw_rgb_b);
    }
    return led_max < DRIVER_LED_TOTAL;
}
#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
