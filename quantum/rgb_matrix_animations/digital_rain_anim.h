#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && !defined(DISABLE_RGB_MATRIX_DIGITAL_RAIN)
RGB_MATRIX_EFFECT(DIGITAL_RAIN)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// TODO: Create a variable blackboard / scratchpad (memory page) that effects can use
static uint32_t digital_rain_drop_timer = 0;
static uint32_t digital_rain_timer = 0;
static uint8_t previous_drop = UINT8_MAX;

static inline void digital_rain_reset_drop_timer(void) {
    uint8_t invert_spd = UINT8_MAX - rgb_matrix_config.speed;
    digital_rain_drop_timer = g_rgb_timer + 250 + ((uint32_t)invert_spd * 3) + rand() % ((uint32_t)invert_spd * 4 + 1);
}

static inline void digital_rain_reset_timer(void) {
    uint8_t invert_spd = UINT8_MAX - rgb_matrix_config.speed;
    digital_rain_timer = g_rgb_timer + 50 + invert_spd / 2;
}

bool DIGITAL_RAIN(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    // Init animation
    if (params->init && led_min == 0) {
        rgb_matrix_set_color_all(0, 0, 0);
        memset(g_rgb_frame_buffer, 0, sizeof(g_rgb_frame_buffer));
        digital_rain_reset_drop_timer();
        digital_rain_reset_timer();
        previous_drop = UINT8_MAX;
    }

    // New Drop
    if (led_min == 0 && timer_expired32(g_rgb_timer, digital_rain_drop_timer)) {
        uint8_t led[LED_HITS_TO_REMEMBER];
        uint8_t new_drop = rand() % MATRIX_COLS;
        if (new_drop != previous_drop && rgb_matrix_map_row_column_to_led(0, new_drop, led) > 0) {
            g_rgb_frame_buffer[led[0]] = UINT8_MAX;
            digital_rain_reset_drop_timer();
            previous_drop = new_drop;
        }
    }

    // Render & decrease
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            // set the pixel colour
            uint8_t led[LED_HITS_TO_REMEMBER];
            if (rgb_matrix_map_row_column_to_led(row, col, led) == 0)
                continue;

            uint8_t val = g_rgb_frame_buffer[led[0]];
            uint8_t sat = qsub8(rgb_matrix_config.hsv.s, qadd8(qsub8(val, 192) * 4, 64));
            val = val > 192 ? UINT8_MAX : ((uint16_t)val * (uint16_t)UINT8_MAX) / 192;

            HSV hsv = { rgb_matrix_config.hsv.h, sat, scale8(val, rgb_matrix_config.hsv.v) };
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(led[0], rgb.r, rgb.g, rgb.b);

            if (timer_expired32(g_rgb_timer, digital_rain_timer))
                g_rgb_frame_buffer[led[0]] = qsub8(g_rgb_frame_buffer[led[0]], 1);

            uint8_t led_prev[LED_HITS_TO_REMEMBER];
            if (row == 0 || rgb_matrix_map_row_column_to_led(row - 1, col, led_prev) == 0)
                continue;

            if (g_rgb_frame_buffer[led_prev[0]] == 227) {
                g_rgb_frame_buffer[led[0]] = UINT8_MAX;
            }
        }
    }

    bool remaining = led_max < sizeof(g_rgb_frame_buffer);
    if (!remaining && timer_expired32(g_rgb_timer, digital_rain_timer)) {
        digital_rain_reset_timer();
    }
    return remaining;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && !defined(DISABLE_RGB_MATRIX_DIGITAL_RAIN)
