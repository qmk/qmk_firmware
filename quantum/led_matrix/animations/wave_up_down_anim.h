#ifdef ENABLE_LED_MATRIX_WAVE_UP_DOWN
LED_MATRIX_EFFECT(WAVE_UP_DOWN)
#    ifdef LED_MATRIX_CUSTOM_EFFECT_IMPLS

static uint8_t WAVE_UP_DOWN_math(uint8_t val, uint8_t i, uint8_t time) { return scale8(sin8(g_led_config.point[i].y - time), val); }

bool WAVE_UP_DOWN(effect_params_t* params) { return effect_runner_i(params, &WAVE_UP_DOWN_math); }

#    endif  // LED_MATRIX_CUSTOM_EFFECT_IMPLS
#endif      // ENABLE_LED_MATRIX_WAVE_UP_DOWN
