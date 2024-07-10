RGB_MATRIX_EFFECT(game_mode)
RGB_MATRIX_EFFECT(position_mode)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

extern rgb_config_t rgb_matrix_config;

static bool game_mode(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        if(i<83)
        rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
    }

    RGB rgb = hsv_to_rgb(rgb_matrix_config.hsv);
    rgb_matrix_set_color(0, rgb.r, rgb.g, rgb.b);       // ESC

    rgb_matrix_set_color(33, rgb.r, rgb.g, rgb.b);      // W
    rgb_matrix_set_color(47, rgb.r, rgb.g, rgb.b);      // D
    rgb_matrix_set_color(48, rgb.r, rgb.g, rgb.b);      // S
    rgb_matrix_set_color(49, rgb.r, rgb.g, rgb.b);      // A

    rgb_matrix_set_color(72, rgb.r, rgb.g, rgb.b);      // up
    rgb_matrix_set_color(80, rgb.r, rgb.g, rgb.b);      // right
    rgb_matrix_set_color(81, rgb.r, rgb.g, rgb.b);      // down
    rgb_matrix_set_color(82, rgb.r, rgb.g, rgb.b);      // left

    return rgb_matrix_check_finished_leds(led_max);
}

static bool position_mode(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        if(i<83)
        rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
    }

    RGB rgb = hsv_to_rgb(rgb_matrix_config.hsv);

    rgb_matrix_set_color(50, rgb.r, rgb.g, rgb.b);      // F
    rgb_matrix_set_color(53, rgb.r, rgb.g, rgb.b);      // J
    rgb_matrix_set_color(72, rgb.r, rgb.g, rgb.b);      // up

    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS

