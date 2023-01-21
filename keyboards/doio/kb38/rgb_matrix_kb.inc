RGB_MATRIX_EFFECT(trans)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool trans(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    int a;
    int b;
    int c;
    int d;
    int e;
    int bottom;
    for (a = 0; a < 8; a++) {
        rgb_matrix_set_color(a, 0x00, 0x00, 0xFF);
    }
    for (b = 8; b < 15; b++) {
        rgb_matrix_set_color(b, 0xFF, 0x00, 0x92);
    }
    for (c = 15; c < 28; c++) {
        rgb_matrix_set_color(c, 0xFF, 0xFF, 0xFF);
    }
    for (d = 28; d < 33; d++) {
        rgb_matrix_set_color(d, 0xFF, 0x00, 0x92);
    }
    for (e = 33; e < 38; e++) {
        rgb_matrix_set_color(e, 0x00, 0x00, 0xFF);
    }
    for (bottom = 38; bottom < 44; bottom++) {
        rgb_matrix_set_color(bottom, 0x00, 0x00, 0xFF);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif 