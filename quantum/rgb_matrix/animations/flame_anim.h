#ifdef ENABLE_RGB_MATRIX_FLAME
RGB_MATRIX_EFFECT(FLAME)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#if 0
static HSV CYCLE_ALL_math(HSV hsv, uint8_t i, uint8_t time) {
    hsv.h = time;
    return hsv;
}

bool CYCLE_ALL(effect_params_t* params) { return effect_runner_i(params, &CYCLE_ALL_math); }
#endif

bool FLAME(effect_params_t* params) { return effect_runner_i(params, &CYCLE_ALL_math); }


#    endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif      // ENABLE_RGB_MATRIX_FLAME
