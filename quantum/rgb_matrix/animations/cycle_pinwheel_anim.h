#ifdef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
RGB_MATRIX_EFFECT(CYCLE_PINWHEEL)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV CYCLE_PINWHEEL_math(HSV hsv, int16_t dx, int16_t dy, uint8_t time) {
    hsv.h = atan2_8(dy, dx) + time;
    return hsv;
}

bool CYCLE_PINWHEEL(effect_params_t* params) { return effect_runner_dx_dy(params, &CYCLE_PINWHEEL_math); }

#    endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif      // ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
