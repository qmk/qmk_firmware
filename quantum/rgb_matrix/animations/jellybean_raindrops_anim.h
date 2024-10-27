#ifdef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
RGB_MATRIX_EFFECT(JELLYBEAN_RAINDROPS)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static rgb_t jellybean_raindrops_set_color(void) {
    hsv_t hsv = {random8(), random8_min_max(127, 255), rgb_matrix_config.hsv.v};
    return rgb_matrix_hsv_to_rgb(hsv);
}

bool JELLYBEAN_RAINDROPS(effect_params_t* params) {
    static uint16_t idx = 0;
    static rgb_t    rgb = {0};

    if (scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 16)) % 5 == 0) {
        idx = random8_max(RGB_MATRIX_LED_COUNT);
        rgb = jellybean_raindrops_set_color();
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (params->init) {
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_TEST_LED_FLAGS();
            rgb = jellybean_raindrops_set_color();
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
    // Change one LED every tick
    else if (led_min <= idx && idx < led_max && HAS_ANY_FLAGS(g_led_config.flags[idx], params->flags)) {
        rgb_matrix_set_color(idx, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
