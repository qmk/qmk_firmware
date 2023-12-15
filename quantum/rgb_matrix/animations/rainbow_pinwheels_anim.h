#ifdef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
RGB_MATRIX_EFFECT(RAINBOW_PINWHEELS)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV RAINBOW_PINWHEELS_math(HSV hsv, int8_t sin, int8_t cos, uint8_t i, uint8_t time) {
    hsv.h += ((g_led_config.point[i].y - k_rgb_matrix_center.y) * 3 * cos + (56 - abs8(g_led_config.point[i].x - k_rgb_matrix_center.x)) * 3 * sin) / 128;
    return hsv;
}

bool RAINBOW_PINWHEELS(effect_params_t* params) {
    return effect_runner_sin_cos_i(params, &RAINBOW_PINWHEELS_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
