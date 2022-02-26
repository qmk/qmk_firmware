RGB_MATRIX_EFFECT(rgb_gradient_td)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
/* a rgb matrix effect similar to GRADIENT_UP_DOWN */
bool rgb_gradient_td(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    HSV     hsv   = rgb_matrix_config.hsv;
    uint8_t scale = scale8(64, rgb_matrix_config.speed);

    /* the y range will be 0..64, map this to 0..6 */
    const uint8_t g = 1 + (64 - 1) / 6;

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        /* relies on hue being 8-bit and wrapping */
        hsv.h = rgb_matrix_config.hsv.h /* original hue */
                + scale * (g_led_config.point[i].y / g);
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}
#endif
