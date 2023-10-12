#ifdef ENABLE_LED_MATRIX_DUAL_BEACON
LED_MATRIX_EFFECT(DUAL_BEACON)
#    ifdef LED_MATRIX_CUSTOM_EFFECT_IMPLS

static uint8_t DUAL_BEACON_math(uint8_t val, int8_t sin, int8_t cos, uint8_t i, uint8_t time) {
    return scale8(((g_led_config.point[i].y - k_led_matrix_center.y) * cos + (g_led_config.point[i].x - k_led_matrix_center.x) * sin) / 128, val);
}

bool DUAL_BEACON(effect_params_t* params) {
    return effect_runner_sin_cos_i(params, &DUAL_BEACON_math);
}

#    endif // LED_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_LED_MATRIX_DUAL_BEACON
