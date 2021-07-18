/* Copyright 2020 Cameron Buss camrbuss@vt.edu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "grabert.h"

#ifdef OLED_DRIVER_ENABLE
static uint32_t oled_timer                       = 0;
static uint8_t  gol_state[GOL_WIDTH][GOL_HEIGHT] = {0};
static uint32_t gol_update_count                 = 0;

void keyboard_pre_init_user(void) { gol_initialize(); }

void suspend_power_down_user(void) { oled_off(); }

void suspend_wakeup_init_user(void) {
    oled_timer       = timer_read32();
    gol_update_count = 0;
    gol_initialize();
}

void oled_task_user(void) {
    if (timer_read32() < (oled_timer + LOGO_TIMEOUT_MS)) {
        /* Display a logo for a short period of time after  */
        /* turning the keyboard on */
        oled_write_raw(kobuss_logo, OLED_MATRIX_SIZE);
    } else if (gol_update_count < GOL_UPDATE_MAX_COUNT) {
        if (gol_update_count % GOL_EVOLVE_PERIOD_MOD == 0) {
            for (size_t i = 0; i < OLED_DISPLAY_WIDTH; i++) {
                for (size_t j = 0; j < OLED_DISPLAY_HEIGHT; j++) {
                    oled_write_pixel(i, j, gol_state[i / GOL_SQUARE_SIZE][j / GOL_SQUARE_SIZE]);
                }
            }

            gol_play_game();
        }
        gol_update_count++;

    } else if (gol_update_count == GOL_UPDATE_MAX_COUNT) {
        oled_write_raw(screen_outline, OLED_MATRIX_SIZE);
        gol_update_count++;
    } else {
/* Set WPM rate */
#    ifdef WPM_ENABLE
        uint8_t wpm = get_current_wpm();
#    else
        uint8_t wpm = 0;
#    endif

        uint8_t bars = 0;
        if (wpm > SPEED_MAX_BARS_WPM) {
            bars = SPEED_NUM_BARS;
        } else {
            bars = wpm / SPEED_WPM_TO_BARS;
        }

        for (size_t i = 0; i < SPEED_NUM_BARS; i++) {
            if (bars) {
                oled_write_raw_byte(0xFF, 264 + i);
                bars--;
            } else {
                oled_write_raw_byte(0x00, 264 + i);
            }
        }

        /* Set Caps Lock */
        led_t       leds = host_keyboard_led_state();
        const char* caps_glyph;
        if (leds.caps_lock) {
            caps_glyph = caps_lock_on;
        } else {
            caps_glyph = caps_lock_off;
        }

        for (size_t i = 0; i < CAPS_LOCK_ROWS_BYTES; i++) {
            for (size_t j = 0; j < CAPS_LOCK_COLS_BITS; j++) {
                oled_write_raw_byte(caps_glyph[i * CAPS_LOCK_COLS_BITS + j], (OLED_DISPLAY_WIDTH + 50) + OLED_DISPLAY_WIDTH * i + j);
            }
        }

        /* Set Layer (Currently only supports 0-3 layers) */
        const char* layer_glyph;
        /* Check the highest possible layer first */
        if (layer_state_is(0b0011)) {
            layer_glyph = layer_num_3;
        } else if (layer_state_is(0b0010)) {
            layer_glyph = layer_num_2;
        } else if (layer_state_is(0b0001)) {
            layer_glyph = layer_num_1;
        } else if (layer_state_is(0b0000)) {
            layer_glyph = layer_num_0;
        } else {
            layer_glyph = layer_nan;
        }

        for (size_t i = 0; i < LAYER_ROWS_BYTES; i++) {
            for (size_t j = 0; j < LAYER_COLS_BITS; j++) {
                oled_write_raw_byte(layer_glyph[i * LAYER_COLS_BITS + j], (OLED_DISPLAY_WIDTH + 98) + OLED_DISPLAY_WIDTH * i + j);
            }
        }
    }
}

/*
 * John Conway's Game of Life
 * https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 * C implementation inspired by:
 * https://rosettacode.org/wiki/Conway%27s_Game_of_Life#C
 */
void gol_play_game(void) {
    for (size_t i = 0; i < GOL_WIDTH; i++) {
        for (size_t j = 0; j < GOL_HEIGHT; j++) {
            size_t n = 0;

            /* Since the state is stored in a uint8_t, we use the first bit for the current state */
            /* and the second bit as the next state */
            for (size_t x1 = i - 1; x1 <= i + 1; x1++) {
                for (size_t y1 = j - 1; y1 <= j + 1; y1++) {
                    if (gol_state[(x1 + GOL_WIDTH) % GOL_WIDTH][(y1 + GOL_HEIGHT) % GOL_HEIGHT] & 0x01) {
                        n++;
                    }
                }
            }

            if (gol_state[i][j] & 0x01) {
                n--;
            }
            gol_state[i][j] |= (n == 3 || (n == 2 && (gol_state[i][j] & 0x01))) << 1;
        }
    }

    /* second bit is shifted into the 1st bit position and the second bit is cleared */
    for (size_t i = 0; i < GOL_WIDTH; i++) {
        for (size_t j = 0; j < GOL_HEIGHT; j++) {
            gol_state[i][j] = (gol_state[i][j] >> 1) & 0x01;
        }
    }
}

void gol_initialize(void) {
    for (size_t i = 0; i < GOL_WIDTH; i++) {
        for (size_t j = 0; j < GOL_HEIGHT; j++) {
            size_t large_matrix_row = j * GOL_SQUARE_SIZE / 8;
            size_t matrix_row = j * GOL_SQUARE_SIZE % 8;
            size_t matrix_col = i * GOL_SQUARE_SIZE;
            gol_state[i][j] = (kobuss_logo[large_matrix_row * OLED_DISPLAY_WIDTH + matrix_col] >> matrix_row) & 0x1;
        }
    }
}
#endif