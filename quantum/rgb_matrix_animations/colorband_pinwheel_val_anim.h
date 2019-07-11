#ifndef DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
RGB_MATRIX_EFFECT(BAND_PINWHEEL_VAL)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static void BAND_PINWHEEL_VAL_math(HSV* hsv, int16_t dx, int16_t dy, uint8_t time) {
    hsv->v = scale8(rgb_matrix_config.val - time - atan2_8(dy, dx) * 3, rgb_matrix_config.val);
}

bool BAND_PINWHEEL_VAL(effect_params_t* params) {
    return effect_runner_dx_dy(params, &BAND_PINWHEEL_VAL_math);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
