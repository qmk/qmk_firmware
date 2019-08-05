#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && !defined(DISABLE_RGB_MATRIX_BUBBLING_RAIN)
RGB_MATRIX_EFFECT(BUBBLING_RAIN)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// TODO: Create a variable blackboard / scratchpad (memory page) that effects can use
static uint32_t rain_drop_timer = 0;
static uint32_t rain_timer = 0;

static inline void bubbling_rain_reset_drop_timer(void) {
    uint8_t invert_spd = UINT8_MAX - rgb_matrix_config.speed;
    rain_drop_timer = g_rgb_timer + 10 + rand() % (invert_spd / 4 + 1);
}

static inline void bubbling_rain_reset_timer(void) {
    rain_timer = g_rgb_timer + 10;
}

bool BUBBLING_RAIN(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    // Init animation
    if (params->init && led_min == 0) {
        rgb_matrix_set_color_all(0, 0, 0);
        memset(g_rgb_frame_buffer, 0, sizeof(g_rgb_frame_buffer));
        bubbling_rain_reset_drop_timer();
        bubbling_rain_reset_timer();
    }

    // New Drop
    if (led_min == 0 && timer_expired32(g_rgb_timer, rain_drop_timer)) {
        uint8_t i = rand() % DRIVER_LED_TOTAL;
        uint8_t val = g_rgb_frame_buffer[i];
        if (val == 0) {
            g_rgb_frame_buffer[i] = 1;
            bubbling_rain_reset_drop_timer();
        }
    }

    // Render & decrease
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();

        uint8_t val = g_rgb_frame_buffer[i];
        HSV hsv = { rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, scale8(cos8(val + 127), rgb_matrix_config.hsv.v) };
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        if (val > 0 && timer_expired32(g_rgb_timer, rain_timer))
            g_rgb_frame_buffer[i] = val + 1;
    }

    bool remaining = led_max < sizeof(g_rgb_frame_buffer);
    if (!remaining &&  timer_expired32(g_rgb_timer, rain_timer)) {
        bubbling_rain_reset_timer();
    }
    return remaining;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && !defined(DISABLE_RGB_MATRIX_BUBBLING_RAIN)
