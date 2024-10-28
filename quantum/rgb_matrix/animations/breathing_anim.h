#ifdef ENABLE_RGB_MATRIX_BREATHING
RGB_MATRIX_EFFECT(BREATHING)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

hsv_t BREATHING_math(hsv_t hsv, uint8_t i, uint8_t time) {
    hsv.v = scale8(abs8(sin8(time / 2) - 128) * 2, hsv.v);
    return hsv;
}

bool BREATHING(effect_params_t* params) {
    return effect_runner_i(params, &BREATHING_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_BREATHING
