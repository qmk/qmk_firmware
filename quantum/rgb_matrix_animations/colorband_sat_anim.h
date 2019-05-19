#ifndef DISABLE_RGB_MATRIX_BAND_SAT
RGB_MATRIX_EFFECT(BAND_SAT)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static void BAND_SAT_math(HSV* hsv, uint8_t i, uint8_t time) {
    int16_t s = rgb_matrix_config.sat - abs(scale8(g_led_config.point[i].x, 228) + 28 - time) * 8;
    hsv->s = s < 0 ? 0 : s;
}

bool BAND_SAT(effect_params_t* params) {
    return effect_runner_i(params, &BAND_SAT_math);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // DISABLE_RGB_MATRIX_BAND_SAT
