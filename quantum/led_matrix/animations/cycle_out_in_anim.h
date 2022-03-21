#ifdef ENABLE_LED_MATRIX_CYCLE_OUT_IN
LED_MATRIX_EFFECT(CYCLE_OUT_IN)
#    ifdef LED_MATRIX_CUSTOM_EFFECT_IMPLS

static uint8_t CYCLE_OUT_IN_math(uint8_t val, int16_t dx, int16_t dy, uint8_t dist, uint8_t time) {
    return scale8(3 * dist / 2 + time, val);
}

bool CYCLE_OUT_IN(effect_params_t* params) {
    return effect_runner_dx_dy_dist(params, &CYCLE_OUT_IN_math);
}

#    endif // LED_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_LED_MATRIX_CYCLE_OUT_IN
