#ifdef ENABLE_LED_MATRIX_BREATHING
LED_MATRIX_EFFECT(BREATHING)
#    ifdef LED_MATRIX_CUSTOM_EFFECT_IMPLS

bool BREATHING(effect_params_t* params) {
    LED_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t  val  = led_matrix_eeconfig.val;
    uint16_t time = scale16by8(g_led_timer, led_matrix_eeconfig.speed / 8);
    val           = scale8(abs8(sin8(time) - 128) * 2, val);
    for (uint8_t i = led_min; i < led_max; i++) {
        LED_MATRIX_TEST_LED_FLAGS();
        led_matrix_set_value(i, val);
    }
    return led_matrix_check_finished_leds(led_max);
}

#    endif // LED_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_LED_MATRIX_BREATHING
