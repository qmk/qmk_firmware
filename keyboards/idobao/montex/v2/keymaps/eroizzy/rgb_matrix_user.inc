RGB_MATRIX_EFFECT(asuka)


// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// e.g: A simple effect, self-contained within a single method
static bool asuka(effect_params_t* params) {
    const int YELLOW_R = 255;
    const int YELLOW_G = 255;
    const int YELLOW_B = 0;

    const int RED_R = 255;
    const int RED_G = 0;
    const int RED_B = 0;

    const int WHITE_R = 255;
    const int WHITE_G = 255;
    const int WHITE_B = 255;
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_matrix_set_color(6, YELLOW_R, YELLOW_G, YELLOW_B);
    rgb_matrix_set_color(29, YELLOW_R, YELLOW_G, YELLOW_B);
    rgb_matrix_set_color(23, YELLOW_R, YELLOW_G, YELLOW_B);
    rgb_matrix_set_color(10, YELLOW_R, YELLOW_G, YELLOW_B);

    rgb_matrix_set_color(22, RED_R, RED_G, RED_B);
    rgb_matrix_set_color(21, RED_R, RED_G, RED_B);
    rgb_matrix_set_color(20, RED_R, RED_G, RED_B);
    rgb_matrix_set_color(16, RED_R, RED_G, RED_B);
    rgb_matrix_set_color(17, RED_R, RED_G, RED_B);
    rgb_matrix_set_color(18, RED_R, RED_G, RED_B);
    rgb_matrix_set_color(13, RED_R, RED_G, RED_B);
    rgb_matrix_set_color(12, RED_R, RED_G, RED_B);
    rgb_matrix_set_color(11, RED_R, RED_G, RED_B);
    rgb_matrix_set_color(8, RED_R, RED_G, RED_B);
    rgb_matrix_set_color(9, RED_R, RED_G, RED_B);

    rgb_matrix_set_color(5, WHITE_R, WHITE_G, WHITE_B);
    rgb_matrix_set_color(4, WHITE_R, WHITE_G, WHITE_B);
    rgb_matrix_set_color(30, WHITE_R, WHITE_G, WHITE_B);
    rgb_matrix_set_color(24, WHITE_R, WHITE_G, WHITE_B);
    rgb_matrix_set_color(25, WHITE_R, WHITE_G, WHITE_B);
    rgb_matrix_set_color(26, WHITE_R, WHITE_G, WHITE_B);
    rgb_matrix_set_color(27, WHITE_R, WHITE_G, WHITE_B);
    rgb_matrix_set_color(28, WHITE_R, WHITE_G, WHITE_B);
    rgb_matrix_set_color(19, WHITE_R, WHITE_G, WHITE_B);
    rgb_matrix_set_color(15, WHITE_R, WHITE_G, WHITE_B);
    rgb_matrix_set_color(14, WHITE_R, WHITE_G, WHITE_B);
    rgb_matrix_set_color(7, WHITE_R, WHITE_G, WHITE_B);
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS