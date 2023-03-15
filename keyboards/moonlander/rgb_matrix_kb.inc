#ifdef RGB_MATRIX_ENABLE
RGB_MATRIX_EFFECT(oryx_webhid_effect)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static void oryx_webhid_effect_init(void) {
    // Paint it black
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; ++i) {
        webhid_leds[i] = (RGB){0, 0, 0};
    }
}

static bool oryx_webhid_effect_run(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; ++i) {
        rgb_matrix_set_color(i, webhid_leds[i].r, webhid_leds[i].g, webhid_leds[i].b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

static bool oryx_webhid_effect(effect_params_t* params) {
    if (params->init) oryx_webhid_effect_init();
    return oryx_webhid_effect_run(params);
}

#    endif
#endif
