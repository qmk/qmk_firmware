#ifdef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
RGB_MATRIX_EFFECT(BAND_PINWHEEL_VAL)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV BAND_PINWHEEL_VAL_math(HSV hsv, int16_t dx, int16_t dy, uint8_t time) {
    hsv.v = scale8(hsv.v - time - atan2_8(dy, dx) * 3, hsv.v);
    return hsv;
}

bool BAND_PINWHEEL_VAL(effect_params_t* params) {
    return effect_runner_dx_dy(params, &BAND_PINWHEEL_VAL_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
