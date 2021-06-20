#ifndef DISABLE_LED_MATRIX_BAND_SPIRAL
LED_MATRIX_EFFECT(BAND_SPIRAL)
#    ifdef LED_MATRIX_CUSTOM_EFFECT_IMPLS

static uint8_t BAND_SPIRAL_math(uint8_t val, int16_t dx, int16_t dy, uint8_t dist, uint8_t time) { return scale8(val + dist - time - atan2_8(dy, dx), val); }

bool BAND_SPIRAL(effect_params_t* params) { return effect_runner_dx_dy_dist(params, &BAND_SPIRAL_math); }

#    endif  // LED_MATRIX_CUSTOM_EFFECT_IMPLS
#endif  // DISABLE_LED_MATRIX_BAND_SPIRAL
