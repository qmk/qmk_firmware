#ifdef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
RGB_MATRIX_EFFECT(BAND_PINWHEEL_SAT)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static hsv_t BAND_PINWHEEL_SAT_math(hsv_t hsv, int16_t dx, int16_t dy, uint8_t time) {
    hsv.s = scale8(hsv.s - time - atan2_8(dy, dx) * 3, hsv.s);
    return hsv;
}

bool BAND_PINWHEEL_SAT(effect_params_t* params) {
    return effect_runner_dx_dy(params, &BAND_PINWHEEL_SAT_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
