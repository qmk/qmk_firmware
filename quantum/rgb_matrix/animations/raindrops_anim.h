#ifdef ENABLE_RGB_MATRIX_RAINDROPS
RGB_MATRIX_EFFECT(RAINDROPS)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static rgb_t raindrops_set_color(hsv_t hsv) {
    // Take the shortest path between hues
    int16_t deltaH = ((hsv.h + 180) % 360 - hsv.h) / 4;
    if (deltaH > 127) {
        deltaH -= 256;
    } else if (deltaH < -127) {
        deltaH += 256;
    }

    hsv.h += (deltaH * random8_max(3));
    return rgb_matrix_hsv_to_rgb(hsv);
}

bool RAINDROPS(effect_params_t* params) {
    static uint16_t idx = 0;
    static rgb_t    rgb = {0};

    if (scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 16)) % 10 == 0) {
        idx = random8_max(RGB_MATRIX_LED_COUNT);
        rgb = raindrops_set_color(rgb_matrix_config.hsv);
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (params->init) {
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_TEST_LED_FLAGS();
            rgb = raindrops_set_color(rgb_matrix_config.hsv);
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
#endif     // ENABLE_RGB_MATRIX_RAINDROPS
