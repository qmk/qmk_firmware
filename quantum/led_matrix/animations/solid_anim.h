LED_MATRIX_EFFECT(SOLID)
#ifdef LED_MATRIX_CUSTOM_EFFECT_IMPLS

bool SOLID(effect_params_t* params) {
    LED_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t val = led_matrix_eeconfig.val;
    for (uint8_t i = led_min; i < led_max; i++) {
        LED_MATRIX_TEST_LED_FLAGS();
        led_matrix_set_value(i, val);
    }
    return led_matrix_check_finished_leds(led_max);
}

#endif  // LED_MATRIX_CUSTOM_EFFECT_IMPLS
