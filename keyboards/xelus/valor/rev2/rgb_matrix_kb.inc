// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(test_mode)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// e.g: A simple effect, self-contained within a single method
static bool test_mode(effect_params_t* params) {
    uint8_t factor = 9;
    switch ((g_rgb_timer & (0b11 << factor)) >> factor) {
        case 0: {
            rgb_matrix_set_color_all(150, 0, 0);
            break;
        }
        case 1: {
            rgb_matrix_set_color_all(0, 150, 0);
            break;
        }
        case 2: {
            rgb_matrix_set_color_all(0, 0, 150);
            break;
        }
        case 3: {
            rgb_matrix_set_color_all(150, 150, 150);
            break;
        }
    }
    return false;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
