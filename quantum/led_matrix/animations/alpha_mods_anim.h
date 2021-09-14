#ifdef ENABLE_LED_MATRIX_ALPHAS_MODS
LED_MATRIX_EFFECT(ALPHAS_MODS)
#    ifdef LED_MATRIX_CUSTOM_EFFECT_IMPLS

// alphas = val1, mods = val2
bool ALPHAS_MODS(effect_params_t* params) {
    LED_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t val1 = led_matrix_eeconfig.val;
    uint8_t val2 = val1 + led_matrix_eeconfig.speed;

    for (uint8_t i = led_min; i < led_max; i++) {
        LED_MATRIX_TEST_LED_FLAGS();
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
            led_matrix_set_value(i, val2);
        } else {
            led_matrix_set_value(i, val1);
        }
    }
    return led_max < DRIVER_LED_TOTAL;
}

#    endif  // LED_MATRIX_CUSTOM_EFFECT_IMPLS
#endif      // DISABLE_LED_MATRIX_ALPHAS_MODS
