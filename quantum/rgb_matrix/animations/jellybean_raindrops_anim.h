#ifdef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
RGB_MATRIX_EFFECT(JELLYBEAN_RAINDROPS)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static void jellybean_raindrops_set_color(uint8_t i, effect_params_t* params) {
    if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) return;

    hsv_t hsv = {random8(), random8_min_max(127, 255), rgb_matrix_config.hsv.v};
    rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

bool JELLYBEAN_RAINDROPS(effect_params_t* params) {
    static uint16_t index = RGB_MATRIX_LED_COUNT + 1;

    // Periodic trigger for LED change
    if ((params->iter == 0) && (scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 16)) % 5 == 0)) {
        index = random8_max(RGB_MATRIX_LED_COUNT);
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (params->init) {
        for (uint8_t i = led_min; i < led_max; i++) {
            jellybean_raindrops_set_color(i, params);
        }
    }
    // Change LED once and set index out of range till next trigger
    else if (led_min <= index && index < led_max) {
        jellybean_raindrops_set_color(index, params);
        index = RGB_MATRIX_LED_COUNT + 1;
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
