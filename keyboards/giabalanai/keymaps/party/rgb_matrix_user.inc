#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
RGB_MATRIX_EFFECT(my_solid_reactive_with_CnoteIndicator)
RGB_MATRIX_EFFECT(my_party_rocks)

#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool my_solid_reactive_with_CnoteIndicator(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint16_t max_tick = 65535 / rgb_matrix_config.speed;
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        HSV hsv = rgb_matrix_config.hsv;
        switch (i) {
            //  C note indicator
            case 15:
            case 19:
            case 23:
            case 52:
            case 56:
            case 60:
            case 80:  //  left hand side, bass C note when counter bass is chosen.
                // HSV_GOLDENROD
                hsv.h = 30;
                hsv.s = 218;
                hsv.v = 218;
                break;
        }
        uint16_t tick = max_tick;
        // Reverse search to find most recent key hit
        for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
            if (g_last_hit_tracker.x[j] == g_led_config.point[i].x && g_last_hit_tracker.y[j] == g_led_config.point[i].y && g_last_hit_tracker.tick[j] < tick) {
                tick = g_last_hit_tracker.tick[j];
                break;
            }
        }

        uint16_t offset = scale16by8(tick, rgb_matrix_config.speed);
        hsv.h += qsub8(130, offset);
        RGB      rgb    = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return led_max < RGB_MATRIX_LED_COUNT;
}

bool my_party_rocks(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    HSV hsv = {rand() & 0xFF, rand() & 0xFF, rgb_matrix_config.hsv.v};
    RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
    // rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
    return led_max < RGB_MATRIX_LED_COUNT;
}


#    endif      // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif          // RGB_MATRIX_KEYREACTIVE_ENABLED
