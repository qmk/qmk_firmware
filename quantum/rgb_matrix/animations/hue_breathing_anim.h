#ifdef ENABLE_RGB_MATRIX_HUE_BREATHING
RGB_MATRIX_EFFECT(HUE_BREATHING)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// Hue Breathing - All LED's light up
hsv_t HUE_BREATHING_math(hsv_t hsv, uint8_t i, uint8_t time) {
    // Adjust delta between 0-255 to change hue range
    uint8_t delta = 12;
    hsv.h         = hsv.h + scale8(abs8(sin8(time / 2) - 128) * 2, delta);
    return hsv;
}

bool HUE_BREATHING(effect_params_t* params) {
    return effect_runner_i(params, &HUE_BREATHING_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_HUE_BREATHING
