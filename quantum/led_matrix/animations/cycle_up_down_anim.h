#ifdef ENABLE_LED_MATRIX_CYCLE_UP_DOWN
LED_MATRIX_EFFECT(CYCLE_UP_DOWN)
#    ifdef LED_MATRIX_CUSTOM_EFFECT_IMPLS

static uint8_t CYCLE_UP_DOWN_math(uint8_t val, uint8_t i, uint8_t time) { return scale8(g_led_config.point[i].y - time, val); }

bool CYCLE_UP_DOWN(effect_params_t* params) { return effect_runner_i(params, &CYCLE_UP_DOWN_math); }

#    endif  // LED_MATRIX_CUSTOM_EFFECT_IMPLS
#endif      // DISABLE_LED_MATRIX_CYCLE_UP_DOWN
