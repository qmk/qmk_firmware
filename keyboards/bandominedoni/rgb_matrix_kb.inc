#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
RGB_MATRIX_EFFECT(my_party_rocks)

#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool my_party_rocks(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    HSV hsv = {rand() & 0xFF, rand() & 0xFF, rgb_matrix_config.hsv.v};
    RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
    // rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
    return rgb_matrix_check_finished_leds(led_max);
}

#    endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif      // RGB_MATRIX_KEYREACTIVE_ENABLED
