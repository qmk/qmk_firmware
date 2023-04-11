RGB_MATRIX_EFFECT(trans)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool trans(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (int i = 0; i < 8; i++) {
        rgb_matrix_set_color(i, 0x00, 0x00, 0xFF);
    }
    for (int i = 8; i < 15; i++) {
        rgb_matrix_set_color(i, 0xFF, 0x00, 0x92);
    }
    for (int i = 15; i < 28; i++) {
        rgb_matrix_set_color(i, 0xFF, 0xFF, 0xFF);
    }
    for (int i = 28; i < 33; i++) {
        rgb_matrix_set_color(i, 0xFF, 0x00, 0x92);
    }
    for (int i = 33; i < 38; i++) {
        rgb_matrix_set_color(i, 0x00, 0x00, 0xFF);
    }
    for (int i = 38; i < 44; i++) {
        rgb_matrix_set_color(i, 0x00, 0x00, 0xFF);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif 