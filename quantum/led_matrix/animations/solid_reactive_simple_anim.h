#ifdef LED_MATRIX_KEYREACTIVE_ENABLED
#    ifdef ENABLE_LED_MATRIX_SOLID_REACTIVE_SIMPLE
LED_MATRIX_EFFECT(SOLID_REACTIVE_SIMPLE)
#        ifdef LED_MATRIX_CUSTOM_EFFECT_IMPLS

static uint8_t SOLID_REACTIVE_SIMPLE_math(uint8_t val, uint16_t offset) {
    return scale8(255 - offset, val);
}

bool SOLID_REACTIVE_SIMPLE(effect_params_t* params) {
    return effect_runner_reactive(params, &SOLID_REACTIVE_SIMPLE_math);
}

#        endif // LED_MATRIX_CUSTOM_EFFECT_IMPLS
#    endif     // ENABLE_LED_MATRIX_SOLID_REACTIVE_SIMPLE
#endif         // LED_MATRIX_KEYREACTIVE_ENABLED
