#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_RGB_MATRIX_TYPING_HEATMAP)
RGB_MATRIX_EFFECT(TYPING_HEATMAP)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#        ifndef RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS
#            define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 25
#        endif

#        ifndef RGB_MATRIX_TYPING_HEATMAP_SPREAD
#            define RGB_MATRIX_TYPING_HEATMAP_SPREAD 40
#        endif

#        ifndef RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT
#            define RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT 16
#        endif
void process_rgb_matrix_typing_heatmap(uint8_t row, uint8_t col) {
#        ifdef RGB_MATRIX_TYPING_HEATMAP_SLIM
    // Limit effect to pressed keys
    g_rgb_frame_buffer[row][col] = qadd8(g_rgb_frame_buffer[row][col], 32);
#        else
    if (g_led_config.matrix_co[row][col] == NO_LED) { // skip as pressed key doesn't have an led position
        return;
    }
    for (uint8_t i_row = 0; i_row < MATRIX_ROWS; i_row++) {
        for (uint8_t i_col = 0; i_col < MATRIX_COLS; i_col++) {
            if (g_led_config.matrix_co[i_row][i_col] == NO_LED) { // skip as target key doesn't have an led position
                continue;
            }
            if (i_row == row && i_col == col) {
                g_rgb_frame_buffer[row][col] = qadd8(g_rgb_frame_buffer[row][col], 32);
            } else {
#            define LED_DISTANCE(led_a, led_b) sqrt16(((int8_t)(led_a.x - led_b.x) * (int8_t)(led_a.x - led_b.x)) + ((int8_t)(led_a.y - led_b.y) * (int8_t)(led_a.y - led_b.y)))
                uint8_t distance = LED_DISTANCE(g_led_config.point[g_led_config.matrix_co[row][col]], g_led_config.point[g_led_config.matrix_co[i_row][i_col]]);
#            undef LED_DISTANCE
                if (distance <= RGB_MATRIX_TYPING_HEATMAP_SPREAD) {
                    uint8_t amount = qsub8(RGB_MATRIX_TYPING_HEATMAP_SPREAD, distance);
                    if (amount > RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT) {
                        amount = RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT;
                    }
                    g_rgb_frame_buffer[i_row][i_col] = qadd8(g_rgb_frame_buffer[i_row][i_col], amount);
                }
            }
        }
    }
#        endif
}

// A timer to track the last time we decremented all heatmap values.
static uint16_t heatmap_decrease_timer;
// Whether we should decrement the heatmap values during the next update.
static bool decrease_heatmap_values;

bool TYPING_HEATMAP(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (params->init) {
        rgb_matrix_set_color_all(0, 0, 0);
        memset(g_rgb_frame_buffer, 0, sizeof g_rgb_frame_buffer);
    }

    // The heatmap animation might run in several iterations depending on
    // `RGB_MATRIX_LED_PROCESS_LIMIT`, therefore we only want to update the
    // timer when the animation starts.
    if (params->iter == 0) {
        decrease_heatmap_values = timer_elapsed(heatmap_decrease_timer) >= RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS;

        // Restart the timer if we are going to decrease the heatmap this frame.
        if (decrease_heatmap_values) {
            heatmap_decrease_timer = timer_read();
        }
    }

    // Render heatmap & decrease
    uint8_t count = 0;
    for (uint8_t row = 0; row < MATRIX_ROWS && count < RGB_MATRIX_LED_PROCESS_LIMIT; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS && RGB_MATRIX_LED_PROCESS_LIMIT; col++) {
            if (g_led_config.matrix_co[row][col] >= led_min && g_led_config.matrix_co[row][col] < led_max) {
                count++;
                uint8_t val = g_rgb_frame_buffer[row][col];
                if (!HAS_ANY_FLAGS(g_led_config.flags[g_led_config.matrix_co[row][col]], params->flags)) continue;

                HSV hsv = {170 - qsub8(val, 85), rgb_matrix_config.hsv.s, scale8((qadd8(170, val) - 170) * 3, rgb_matrix_config.hsv.v)};
                RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
                rgb_matrix_set_color(g_led_config.matrix_co[row][col], rgb.r, rgb.g, rgb.b);

                if (decrease_heatmap_values) {
                    g_rgb_frame_buffer[row][col] = qsub8(val, 1);
                }
            }
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_RGB_MATRIX_TYPING_HEATMAP)
