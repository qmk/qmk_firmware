#ifdef LED_MATRIX_KEYREACTIVE_ENABLED
#    if defined(ENABLE_LED_MATRIX_SOLID_REACTIVE_WIDE) || defined(ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTIWIDE)

#        ifdef ENABLE_LED_MATRIX_SOLID_REACTIVE_WIDE
LED_MATRIX_EFFECT(SOLID_REACTIVE_WIDE)
#        endif

#        ifdef ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTIWIDE
LED_MATRIX_EFFECT(SOLID_REACTIVE_MULTIWIDE)
#        endif

#        ifdef LED_MATRIX_CUSTOM_EFFECT_IMPLS

static uint8_t SOLID_REACTIVE_WIDE_math(uint8_t val, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = tick + dist * 5;
    if (effect > 255) effect = 255;
    return qadd8(val, 255 - effect);
}

#            ifdef ENABLE_LED_MATRIX_SOLID_REACTIVE_WIDE
bool SOLID_REACTIVE_WIDE(effect_params_t* params) { return effect_runner_reactive_splash(qsub8(g_last_hit_tracker.count, 1), params, &SOLID_REACTIVE_WIDE_math); }
#            endif

#            ifdef ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTIWIDE
bool SOLID_REACTIVE_MULTIWIDE(effect_params_t* params) { return effect_runner_reactive_splash(0, params, &SOLID_REACTIVE_WIDE_math); }
#            endif

#        endif  // LED_MATRIX_CUSTOM_EFFECT_IMPLS
#    endif      // defined(ENABLE_LED_MATRIX_SOLID_REACTIVE_WIDE) || defined(ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTIWIDE)
#endif          // LED_MATRIX_KEYREACTIVE_ENABLED
