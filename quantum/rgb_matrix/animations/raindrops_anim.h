#ifdef ENABLE_RGB_MATRIX_RAINDROPS
RGB_MATRIX_EFFECT(RAINDROPS)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static void raindrops_set_color(uint8_t i, effect_params_t* params) {
    if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) return;
    hsv_t hsv = rgb_matrix_config.hsv;

    // Take the shortest path between hues
    int16_t deltaH = ((hsv.h + 180) % 360 - hsv.h) / 4;
    if (deltaH > 127) {
        deltaH -= 256;
    } else if (deltaH < -127) {
        deltaH += 256;
    }

    hsv.h += (deltaH * random8_max(3));
    rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

bool RAINDROPS(effect_params_t* params) {
    static uint16_t index = RGB_MATRIX_LED_COUNT + 1;

    // Periodic trigger for LED change
    if ((params->iter == 0) && (scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 16)) % 10 == 0)) {
        index = random8_max(RGB_MATRIX_LED_COUNT);
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (params->init) {
        for (uint8_t i = led_min; i < led_max; i++) {
            raindrops_set_color(i, params);
        }
    }
    // Change LED once and set index out of range till next trigger
    else if (led_min <= index && index < led_max) {
        raindrops_set_color(index, params);
        index = RGB_MATRIX_LED_COUNT + 1;
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_RAINDROPS
