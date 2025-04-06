#ifdef ENABLE_LED_MATRIX_BREATHING
LED_MATRIX_EFFECT(BREATHING)
#    ifdef LED_MATRIX_CUSTOM_EFFECT_IMPLS

static uint8_t BREATHING_math(uint8_t val, uint8_t i, uint8_t time) {
    return scale8(abs8(sin8(time / 2) - 128) * 2, val);
}

bool BREATHING(effect_params_t* params) {
    return effect_runner_i(params, &BREATHING_math);
}

#    endif // LED_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_LED_MATRIX_BREATHING
