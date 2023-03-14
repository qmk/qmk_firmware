/*
 * Copyright 2023 Maximilian Güntner <code@mguentner.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_RGB_RANDOM_FILL)
RGB_MATRIX_EFFECT(RANDOM_FILL)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
static bool is_filling = true;

bool RANDOM_FILL(effect_params_t* params) {
    static uint32_t wait_timer = 0;

    inline uint32_t interval(void) {
        return 500 / scale16by8(qadd8(rgb_matrix_config.speed, 16), 16);
    }

    inline void random_fill(void) {
        bool only_ones  = true;
        bool only_zeros = true;
        for (uint8_t i_row = 0; i_row < MATRIX_ROWS; i_row++) {
            for (uint8_t i_col = 0; i_col < MATRIX_COLS; i_col++) {
                if (g_rgb_frame_buffer[i_row][i_col] != 0 && only_zeros) {
                    only_zeros = false;
                }
                if (g_rgb_frame_buffer[i_row][i_col] != 1 && only_ones) {
                    only_ones = false;
                }
            }
        }
        if (is_filling == true && only_ones) {
            is_filling = false;
        }
        if (is_filling == false && only_zeros) {
            is_filling = true;
        }

        uint8_t row = random8_max(MATRIX_ROWS);
        uint8_t col = random8_max(MATRIX_COLS);
        RGB     rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);
        if (is_filling == true) {
            g_rgb_frame_buffer[row][col] = 1;
        } else {
            g_rgb_frame_buffer[row][col] = 0;
        }

        for (uint8_t i_row = 0; i_row < MATRIX_ROWS; i_row++) {
            for (uint8_t i_col = 0; i_col < MATRIX_COLS; i_col++) {
                uint8_t led_index = g_led_config.matrix_co[i_row][i_col];
                if (g_rgb_frame_buffer[i_row][i_col]) {
                    rgb_matrix_set_color(led_index, rgb.r, rgb.g, rgb.b);
                } else {
                    rgb_matrix_set_color(led_index, 0, 0, 0);
                }
            }
        }
        wait_timer = g_rgb_timer + interval();
    }

    if (params->init) {
        rgb_matrix_set_color_all(0, 0, 0);
        memset(g_rgb_frame_buffer, 0, sizeof g_rgb_frame_buffer);
    }
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (g_rgb_timer > wait_timer) {
        random_fill();
    }

    return rgb_matrix_check_finished_leds(led_max);
}
#    endif
#endif // ENABLE_RGB_RANDOM_FILL
