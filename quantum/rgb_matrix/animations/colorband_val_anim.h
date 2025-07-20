#ifdef ENABLE_RGB_MATRIX_BAND_VAL
RGB_MATRIX_EFFECT(BAND_VAL)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static hsv_t BAND_VAL_math(hsv_t hsv, uint8_t i, uint8_t time) {
    int16_t v = hsv.v - abs(scale8(g_led_config.point[i].x, 228) + 28 - time) * 8;
    hsv.v     = scale8(v < 0 ? 0 : v, hsv.v);
    return hsv;
}

bool BAND_VAL(effect_params_t* params) {
    return effect_runner_i(params, &BAND_VAL_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_BAND_VAL
