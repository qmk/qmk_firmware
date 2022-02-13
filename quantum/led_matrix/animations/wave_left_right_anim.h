#ifdef ENABLE_LED_MATRIX_WAVE_LEFT_RIGHT
LED_MATRIX_EFFECT(WAVE_LEFT_RIGHT)
#    ifdef LED_MATRIX_CUSTOM_EFFECT_IMPLS

static uint8_t WAVE_LEFT_RIGHT_math(uint8_t val, uint8_t i, uint8_t time) { return scale8(sin8(g_led_config.point[i].x - time), val); }

bool WAVE_LEFT_RIGHT(effect_params_t* params) { return effect_runner_i(params, &WAVE_LEFT_RIGHT_math); }

#    endif  // LED_MATRIX_CUSTOM_EFFECT_IMPLS
#endif      // ENABLE_LED_MATRIX_WAVE_LEFT_RIGHT
