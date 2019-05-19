#ifndef DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
RGB_MATRIX_EFFECT(BAND_PINWHEEL_SAT)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static void BAND_PINWHEEL_SAT_math(HSV* hsv, int16_t dx, int16_t dy, uint8_t time) {
    hsv->s = rgb_matrix_config.sat - time - atan2_8(dy, dx) * 3;
}

bool BAND_PINWHEEL_SAT(effect_params_t* params) {
    return effect_runner_dx_dy(params, &BAND_PINWHEEL_SAT_math);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
