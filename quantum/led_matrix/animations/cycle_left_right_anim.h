#ifdef ENABLE_LED_MATRIX_CYCLE_LEFT_RIGHT
LED_MATRIX_EFFECT(CYCLE_LEFT_RIGHT)
#    ifdef LED_MATRIX_CUSTOM_EFFECT_IMPLS

static uint8_t CYCLE_LEFT_RIGHT_math(uint8_t val, uint8_t i, uint8_t time) { return scale8(g_led_config.point[i].x - time, val); }

bool CYCLE_LEFT_RIGHT(effect_params_t* params) { return effect_runner_i(params, &CYCLE_LEFT_RIGHT_math); }

#    endif  // LED_MATRIX_CUSTOM_EFFECT_IMPLS
#endif      // ENABLE_LED_MATRIX_CYCLE_LEFT_RIGHT
