#ifdef ENABLE_RGB_MATRIX_DUAL_BEACON
RGB_MATRIX_EFFECT(DUAL_BEACON)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV DUAL_BEACON_math(HSV hsv, int8_t sin, int8_t cos, uint8_t i, uint8_t time) {
    hsv.h += ((g_led_config.point[i].y - k_rgb_matrix_center.y) * cos + (g_led_config.point[i].x - k_rgb_matrix_center.x) * sin) / 128;
    return hsv;
}

bool DUAL_BEACON(effect_params_t* params) {
    return effect_runner_sin_cos_i(params, &DUAL_BEACON_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_DUAL_BEACON
