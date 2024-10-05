#ifdef ENABLE_RGB_MATRIX_STARLIGHT_DUAL_HUE
RGB_MATRIX_EFFECT(STARLIGHT_DUAL_HUE)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

void set_starlight_dual_hue_color(uint8_t i, effect_params_t* params) {
    uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
    HSV      hsv  = rgb_matrix_config.hsv;
    hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
    hsv.h         = hsv.h + random8_max((30 + 1 - -30) + -30);
    RGB rgb       = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

bool STARLIGHT_DUAL_HUE(effect_params_t* params) {
    if (!params->init) {
        if (scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 5)) % 5 == 0) {
            uint8_t rand_led = random8_max(RGB_MATRIX_LED_COUNT);
            set_starlight_dual_hue_color(rand_led, params);
        }
        return false;
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        set_starlight_dual_hue_color(i, params);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_STARLIGHT_DUAL_HUE