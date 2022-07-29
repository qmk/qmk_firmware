#ifdef ENABLE_RGB_MATRIX_RAINDROPS
RGB_MATRIX_EFFECT(RAINDROPS)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static void raindrops_set_color(int i, effect_params_t* params) {
    if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) return;
    HSV hsv = {0, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v};

    // Take the shortest path between hues
    int16_t deltaH = ((rgb_matrix_config.hsv.h + 180) % 360 - rgb_matrix_config.hsv.h) / 4;
    if (deltaH > 127) {
        deltaH -= 256;
    } else if (deltaH < -127) {
        deltaH += 256;
    }

    hsv.h   = rgb_matrix_config.hsv.h + (deltaH * (random8() & 0x03));
    RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

bool RAINDROPS(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (!params->init) {
        // Change one LED every tick, make sure speed is not 0
        if (scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 16)) % 10 == 0) {
            raindrops_set_color(random8() % DRIVER_LED_TOTAL, params);
        }
    } else {
        for (int i = led_min; i < led_max; i++) {
            raindrops_set_color(i, params);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_RAINDROPS
