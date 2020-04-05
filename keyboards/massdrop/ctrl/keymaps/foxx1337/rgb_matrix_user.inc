// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(hid_effect)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

RGB rgb_matrix_led_state[DRIVER_LED_TOTAL];

// e.g: A simple effect, self-contained within a single method
static bool hid_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i,
            rgb_matrix_led_state[i].r,
            rgb_matrix_led_state[i].g,
            rgb_matrix_led_state[i].b);
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
