#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
#    if !defined(DISABLE_RGB_MATRIX_SPLASH) || !defined(DISABLE_RGB_MATRIX_MULTISPLASH)

#        ifndef DISABLE_RGB_MATRIX_SPLASH
RGB_MATRIX_EFFECT(SPLASH)
#        endif

#        ifndef DISABLE_RGB_MATRIX_MULTISPLASH
RGB_MATRIX_EFFECT(MULTISPLASH)
#        endif

#        ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

HSV SPLASH_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = tick - dist;
    if (effect > 255) effect = 255;
    hsv.h += effect;
    hsv.v = qadd8(hsv.v, 255 - effect);
    return hsv;
}

#            ifndef DISABLE_RGB_MATRIX_SPLASH
bool SPLASH(effect_params_t* params) { return effect_runner_reactive_splash(qsub8(g_last_hit_tracker.count, 1), params, &SPLASH_math); }
#            endif

#            ifndef DISABLE_RGB_MATRIX_MULTISPLASH
bool MULTISPLASH(effect_params_t* params) { return effect_runner_reactive_splash(0, params, &SPLASH_math); }
#            endif

#        endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#    endif      // !defined(DISABLE_RGB_MATRIX_SPLASH) || !defined(DISABLE_RGB_MATRIX_MULTISPLASH)
#endif          // RGB_MATRIX_KEYREACTIVE_ENABLED
