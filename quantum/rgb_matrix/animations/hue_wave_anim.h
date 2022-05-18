#ifdef ENABLE_RGB_MATRIX_HUE_WAVE
RGB_MATRIX_EFFECT(HUE_WAVE)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// Change huedelta to adjust range of hue change. 0-255.
// Looks better with a low value and slow speed for subtle change.
// Hue Wave - color changes in a wave to the right
static HSV HUE_WAVE_math(HSV hsv, uint8_t i, uint8_t time) {
    uint8_t huedelta = 24;
    hsv.h            = hsv.h + scale8(abs8(g_led_config.point[i].x - time), huedelta);
    return hsv;
}

bool HUE_WAVE(effect_params_t* params) {
    return effect_runner_i(params, &HUE_WAVE_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // DISABLE_RGB_HUE_WAVE
