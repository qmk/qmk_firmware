#ifndef DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
RGB_MATRIX_EFFECT(BAND_SPIRAL_SAT)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV BAND_SPIRAL_SAT_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint8_t time) {
    hsv.s = scale8(hsv.s + dist - time - atan2_8(dy, dx), hsv.s);
    return hsv;
}

bool BAND_SPIRAL_SAT(effect_params_t* params) {
    return effect_runner_dx_dy_dist(params, &BAND_SPIRAL_SAT_math);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
