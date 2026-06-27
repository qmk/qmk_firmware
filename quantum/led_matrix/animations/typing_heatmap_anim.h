#if defined(LED_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_LED_MATRIX_TYPING_HEATMAP)
LED_MATRIX_EFFECT(TYPING_HEATMAP)
#    ifdef LED_MATRIX_CUSTOM_EFFECT_IMPLS
#        ifndef LED_MATRIX_TYPING_HEATMAP_INCREASE_STEP
#            define LED_MATRIX_TYPING_HEATMAP_INCREASE_STEP 32
#        endif

#        ifndef LED_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS
#            define LED_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 25
#        endif

#        ifndef LED_MATRIX_TYPING_HEATMAP_SPREAD
#            define LED_MATRIX_TYPING_HEATMAP_SPREAD 40
#        endif

#        ifndef LED_MATRIX_TYPING_HEATMAP_AREA_LIMIT
#            define LED_MATRIX_TYPING_HEATMAP_AREA_LIMIT 16
#        endif
void process_led_matrix_typing_heatmap(uint8_t row, uint8_t col) {
#        ifdef LED_MATRIX_TYPING_HEATMAP_SLIM
    // Limit effect to pressed keys
    g_led_frame_buffer[row][col] = qadd8(g_led_frame_buffer[row][col], LED_MATRIX_TYPING_HEATMAP_INCREASE_STEP);
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
                g_led_frame_buffer[row][col] = qadd8(g_led_frame_buffer[row][col], LED_MATRIX_TYPING_HEATMAP_INCREASE_STEP);
            } else {
#            define LED_DISTANCE(led_a, led_b) sqrt16(((int32_t)(led_a.x - led_b.x) * (int32_t)(led_a.x - led_b.x)) + ((int32_t)(led_a.y - led_b.y) * (int32_t)(led_a.y - led_b.y)))
                uint8_t distance = LED_DISTANCE(g_led_config.point[g_led_config.matrix_co[row][col]], g_led_config.point[g_led_config.matrix_co[i_row][i_col]]);
#            undef LED_DISTANCE
                if (distance <= LED_MATRIX_TYPING_HEATMAP_SPREAD) {
                    uint8_t amount = qsub8(LED_MATRIX_TYPING_HEATMAP_SPREAD, distance);
                    if (amount > LED_MATRIX_TYPING_HEATMAP_AREA_LIMIT) {
                        amount = LED_MATRIX_TYPING_HEATMAP_AREA_LIMIT;
                    }
                    g_led_frame_buffer[i_row][i_col] = qadd8(g_led_frame_buffer[i_row][i_col], amount);
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
    LED_MATRIX_USE_LIMITS(led_min, led_max);

    if (params->init) {
        led_matrix_set_value_all(0);
        memset(g_led_frame_buffer, 0, sizeof g_led_frame_buffer);
    }

    // The heatmap animation might run in several iterations depending on
    // `LED_MATRIX_LED_PROCESS_LIMIT`, therefore we only want to update the
    // timer when the animation starts.
    if (params->iter == 0) {
        decrease_heatmap_values = timer_elapsed(heatmap_decrease_timer) >= LED_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS;

        // Restart the timer if we are going to decrease the heatmap this frame.
        if (decrease_heatmap_values) {
            heatmap_decrease_timer = timer_read();
        }
    }

    // Render heatmap & decrease
    uint8_t count = 0;
    for (uint8_t row = 0; row < MATRIX_ROWS && count < LED_MATRIX_LED_PROCESS_LIMIT; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS && LED_MATRIX_LED_PROCESS_LIMIT; col++) {
            uint8_t val = g_led_frame_buffer[row][col];

            bool processed = false;

            uint8_t led[LED_HITS_TO_REMEMBER];
            uint8_t led_count = led_matrix_map_row_column_to_led(row, col, led);
            for (uint8_t index = 0; index < led_count; index++) {
                uint8_t led_index = led[index];

                if (led_index >= led_min && led_index < led_max) {
                    count++;

                    if (!HAS_ANY_FLAGS(g_led_config.flags[led_index], params->flags)) {
                        continue;
                    }

                    uint8_t value = scale8(led_matrix_eeconfig.val, val);
                    led_matrix_set_value(led_index, value);
                    processed = true;
                }
            }

            if (processed && decrease_heatmap_values) {
                g_led_frame_buffer[row][col] = qsub8(val, 1);
            }
        }
    }

    return led_matrix_check_finished_leds(led_max);
}

#    endif // LED_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // defined(LED_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_LED_MATRIX_TYPING_HEATMAP)
