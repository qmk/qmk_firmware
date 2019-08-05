#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && !defined(DISABLE_RGB_MATRIX_TYPING_HEATMAP)
RGB_MATRIX_EFFECT(TYPING_HEATMAP)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// Array not large enough for PROGMEM to save firmware space on AVR
const uint8_t k_heatmap_vals[9] = {
    13, 16, 13,
    16, 32, 16,
    13, 16, 13
};

// TODO: Create a variable blackboard / scratchpad (memory page) that effects can use
static uint32_t heatmap_timer = 0;

static inline void heatmap_reset_timer(void) {
    uint8_t invert_spd = UINT8_MAX - rgb_matrix_config.speed;
    heatmap_timer = g_rgb_timer + 16 + invert_spd / 4;
}

void process_rgb_matrix_typing_heatmap(keyrecord_t *record) {
#ifndef DISABLE_RGB_MATRIX_TYPING_HEATMAP_KEY_SPREAD
    uint8_t rows[] = { record->event.key.row - 1, record->event.key.row, record->event.key.row + 1 };
    uint8_t cols[] = { record->event.key.col - 1, record->event.key.col, record->event.key.col + 1 };

    for (uint8_t i = 0; i < 9; i++) {
        uint8_t led[LED_HITS_TO_REMEMBER];
        uint8_t led_count = rgb_matrix_map_row_column_to_led(rows[i / 3], cols[i % 3], led);
        for (uint8_t j = 0; j < led_count; j++) {
            g_rgb_frame_buffer[led[j]] = qadd8(g_rgb_frame_buffer[led[j]], k_heatmap_vals[i]);
        }
    }
#else
    uint8_t led[LED_HITS_TO_REMEMBER];
    uint8_t led_count = rgb_matrix_map_row_column_to_led(record->event.key.row, record->event.key.col, led);
    for (uint8_t i = 0; i < led_count; i++) {
        g_rgb_frame_buffer[led[i]] = qadd8(g_rgb_frame_buffer[led[i]], k_heatmap_vals[4]);
    }
#endif
}

bool TYPING_HEATMAP(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (params->init) {
        rgb_matrix_set_color_all(0, 0, 0);
        memset(g_rgb_frame_buffer, 0, sizeof g_rgb_frame_buffer);
        heatmap_reset_timer();
    }

  // Render heatmap & decrease
    for (int i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();

        uint8_t val = g_rgb_frame_buffer[i];
        HSV hsv = { 170 - qsub8(val, 85), rgb_matrix_config.hsv.s, scale8((qadd8(170, val) - 170) * 3, rgb_matrix_config.hsv.v) };
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        if (timer_expired32(g_rgb_timer, heatmap_timer))
            g_rgb_frame_buffer[i] = qsub8(val, 1);
    }

    bool remaining = led_max < sizeof(g_rgb_frame_buffer);
    if (!remaining && timer_expired32(g_rgb_timer, heatmap_timer)) {
        heatmap_reset_timer();
    }
    return remaining;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && !defined(DISABLE_RGB_MATRIX_TYPING_HEATMAP)
