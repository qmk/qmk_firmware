#ifdef ENABLE_RGB_MATRIX_CYCLE_ALL
RGB_MATRIX_EFFECT(CYCLE_ALL)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static hsv_t CYCLE_ALL_math(hsv_t hsv, uint8_t i, uint8_t time) {
    hsv.h = time;
    return hsv;
}

bool CYCLE_ALL(effect_params_t* params) {
    return effect_runner_i(params, &CYCLE_ALL_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_CYCLE_ALL
