RGB_MATRIX_EFFECT(SOLID_UNDERGLOW)
RGB_MATRIX_EFFECT(HOLOGRAPHICS_UNDERGLOW)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool SOLID_UNDERGLOW(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    RGB rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);
    for (uint8_t i = led_min; i < led_max; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], 0x02)) { // 0x02 == LED_FLAG_UNDERGLOW
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        } else {
            rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

static bool HOLOGRAPHICS_UNDERGLOW(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], 0x02)) { // 0x02 == LED_FLAG_UNDERGLOW
            // RIGHT-HAND SIDE LEDS || LEFT-HAND SIDE LEDS
            if (i == 67) {
                rgb_matrix_set_color(i, 0xff, 0x00, 0xee);
            } else if (i == 68 || i == 77) {
                rgb_matrix_set_color(i, 0xcc, 0x00, 0xff);
            } else if (i == 69 || i == 78) {
                rgb_matrix_set_color(i, 0x9e, 0x00, 0xff);
            } else if (i == 70 || i == 79) {
                rgb_matrix_set_color(i, 0x70, 0x00, 0xff);
            } else if (i == 71 || i == 80) {
                rgb_matrix_set_color(i, 0x52, 0x00, 0xff);
            } else if (i == 72 || i == 81) {
                rgb_matrix_set_color(i, 0x33, 0x00, 0xff);
            } else if (i == 73 || i == 82) {
                rgb_matrix_set_color(i, 0x00, 0x38, 0xff);
            } else if (i == 74 || i == 83) {
                rgb_matrix_set_color(i, 0x00, 0x57, 0xff);
            } else if (i == 75 || i == 84) {
                rgb_matrix_set_color(i, 0x00, 0x85, 0xff);
            } else if (i == 76 || i == 85) {
                rgb_matrix_set_color(i, 0x00, 0xb2, 0xff);
            } else {
                rgb_matrix_set_color(i, 0x00, 0xb2, 0xff);
            }
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
