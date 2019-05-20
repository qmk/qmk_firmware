#ifndef DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
RGB_MATRIX_EFFECT(BAND_SPIRAL_VAL)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static void BAND_SPIRAL_VAL_math(HSV* hsv, int16_t dx, int16_t dy, uint8_t dist, uint8_t time) {
    hsv->v = rgb_matrix_config.val + dist - time - atan2_8(dy, dx);
}

bool BAND_SPIRAL_VAL(effect_params_t* params) {
    return effect_runner_dx_dy_dist(params, &BAND_SPIRAL_VAL_math);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
