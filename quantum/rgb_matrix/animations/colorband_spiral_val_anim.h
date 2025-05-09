#ifdef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
RGB_MATRIX_EFFECT(BAND_SPIRAL_VAL)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static hsv_t BAND_SPIRAL_VAL_math(hsv_t hsv, int16_t dx, int16_t dy, uint8_t dist, uint8_t time) {
    hsv.v = scale8(hsv.v + dist - time - atan2_8(dy, dx), hsv.v);
    return hsv;
}

bool BAND_SPIRAL_VAL(effect_params_t* params) {
    return effect_runner_dx_dy_dist(params, &BAND_SPIRAL_VAL_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
