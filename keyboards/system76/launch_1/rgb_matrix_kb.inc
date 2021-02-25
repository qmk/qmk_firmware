RGB_MATRIX_EFFECT(raw_rgb)

#if defined(RGB_MATRIX_CUSTOM_EFFECT_IMPLS)
RGB raw_rgb_data[DRIVER_LED_TOTAL] = { 0 };

static uint8_t normalize_component(uint8_t component) {
    uint16_t x = (uint16_t)component;
    x *= rgb_matrix_config.hsv.v; // Multiply by current brightness
    x /= 255; // Divide by maximum brightness
    return (uint8_t)x;
}

static RGB normalize_index(uint8_t i) {
    RGB raw = raw_rgb_data[i];
    RGB rgb = {
        .r = normalize_component(raw.r),
        .g = normalize_component(raw.g),
        .b = normalize_component(raw.b),
    };
    return rgb;
}

static bool raw_rgb(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        RGB rgb = normalize_index(i);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return led_max < DRIVER_LED_TOTAL;
}
#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
