#ifdef ENABLE_RGB_MATRIX_STARLIGHT_SMOOTH
RGB_MATRIX_EFFECT(STARLIGHT_SMOOTH)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool STARLIGHT_SMOOTH(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    static uint16_t time_offsets[RGB_MATRIX_LED_COUNT] = {0};

    if (params->init) {
        for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
            time_offsets[i] = random16_max(65000);
        }
    }

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();

        uint16_t time = scale16by8((g_rgb_timer / 2) + time_offsets[i], rgb_matrix_config.speed / 16);
        HSV      hsv  = rgb_matrix_config.hsv;
        hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
        RGB rgb       = rgb_matrix_hsv_to_rgb(hsv);

        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_STARLIGHT_SMOOTH
