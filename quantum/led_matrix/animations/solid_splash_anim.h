#ifdef LED_MATRIX_KEYREACTIVE_ENABLED
#    if !defined(DISABLE_LED_MATRIX_SOLID_SPLASH) || !defined(DISABLE_LED_MATRIX_SOLID_MULTISPLASH)

#        ifdef ENABLE_LED_MATRIX_SOLID_SPLASH
LED_MATRIX_EFFECT(SOLID_SPLASH)
#        endif

#        ifdef ENABLE_LED_MATRIX_SOLID_MULTISPLASH
LED_MATRIX_EFFECT(SOLID_MULTISPLASH)
#        endif

#        ifdef LED_MATRIX_CUSTOM_EFFECT_IMPLS

uint8_t SOLID_SPLASH_math(uint8_t val, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = tick - dist;
    if (effect > 255) effect = 255;
    return qadd8(val, 255 - effect);
}

#            ifdef ENABLE_LED_MATRIX_SOLID_SPLASH
bool SOLID_SPLASH(effect_params_t* params) { return effect_runner_reactive_splash(qsub8(g_last_hit_tracker.count, 1), params, &SOLID_SPLASH_math); }
#            endif

#            ifdef ENABLE_LED_MATRIX_SOLID_MULTISPLASH
bool SOLID_MULTISPLASH(effect_params_t* params) { return effect_runner_reactive_splash(0, params, &SOLID_SPLASH_math); }
#            endif

#        endif  // LED_MATRIX_CUSTOM_EFFECT_IMPLS
#    endif      // !defined(DISABLE_LED_MATRIX_SPLASH) && !defined(DISABLE_LED_MATRIX_MULTISPLASH)
#endif          // LED_MATRIX_KEYREACTIVE_ENABLED
