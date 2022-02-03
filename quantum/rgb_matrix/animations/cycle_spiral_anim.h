#ifdef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
RGB_MATRIX_EFFECT(CYCLE_SPIRAL)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV CYCLE_SPIRAL_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint8_t time) {
    hsv.h = dist - time - atan2_8(dy, dx);
    return hsv;
}

bool CYCLE_SPIRAL(effect_params_t* params) { return effect_runner_dx_dy_dist(params, &CYCLE_SPIRAL_math); }

#    endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif      // ENABLE_RGB_MATRIX_CYCLE_SPIRAL
