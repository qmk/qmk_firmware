RGB_MATRIX_EFFECT(DIRECT)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
extern uint8_t color_buffer[RGB_MATRIX_LED_COUNT * 2];
extern uint8_t brightness_buffer[RGB_MATRIX_LED_COUNT];

static bool DIRECT(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB rgb = hsv_to_rgb((HSV){color_buffer[i * 2], color_buffer[i * 2 + 1], scale8(rgb_matrix_config.hsv.v, brightness_buffer[i])});
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return led_max < RGB_MATRIX_LED_COUNT;
}
#endif
