#ifdef RGB_MATRIX_ENABLE
RGB_MATRIX_EFFECT(oryx_webhid_effect)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

extern RGB webhid_leds[RGB_MATRIX_LED_COUNT];

static bool oryx_webhid_effect_run(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
    for (uint8_t i = led_min; i < led_max; ++i) {
        rgb_matrix_set_color(i, webhid_leds[i].r * f, webhid_leds[i].g * f, webhid_leds[i].b * f);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

static bool oryx_webhid_effect(effect_params_t* params) {
    return oryx_webhid_effect_run(params);
}

#    endif
#endif
