#ifdef ENABLE_LED_MATRIX_BAND_PINWHEEL
LED_MATRIX_EFFECT(BAND_PINWHEEL)
#    ifdef LED_MATRIX_CUSTOM_EFFECT_IMPLS

static uint8_t BAND_PINWHEEL_math(uint8_t val, int16_t dx, int16_t dy, uint8_t time) { return scale8(val - time - atan2_8(dy, dx) * 3, val); }

bool BAND_PINWHEEL(effect_params_t* params) { return effect_runner_dx_dy(params, &BAND_PINWHEEL_math); }

#    endif  // LED_MATRIX_CUSTOM_EFFECT_IMPLS
#endif      // ENABLE_LED_MATRIX_BAND_PINWHEEL
