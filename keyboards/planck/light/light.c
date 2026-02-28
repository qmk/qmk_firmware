/* Copyright 2017 Jack Humbert
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

#include "quantum.h"

const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C1_3,  C2_3,  C3_3},
    {0, C1_4,  C2_4,  C3_4},
    {0, C1_5,  C2_5,  C3_5},
    {0, C1_11, C2_11, C3_11},
    {0, C1_12, C2_12, C3_12},
    {0, C1_13, C2_13, C3_13},
    {1, C1_3,  C2_3,  C3_3},
    {1, C1_4,  C2_4,  C3_4},
    {1, C1_5,  C2_5,  C3_5},
    {1, C1_11, C2_11, C3_11},
    {1, C1_12, C2_12, C3_12},
    {1, C1_13, C2_13, C3_13},

    {0, C1_6,  C2_6,  C3_6},
    {0, C1_7,  C2_7,  C3_7},
    {0, C1_8,  C2_8,  C3_8},
    {0, C1_14, C2_14, C3_14},
    {0, C1_15, C2_15, C3_15},
    {0, C1_16, C2_16, C3_16},
    {1, C1_6,  C2_6,  C3_6},
    {1, C1_7,  C2_7,  C3_7},
    {1, C1_8,  C2_8,  C3_8},
    {1, C1_14, C2_14, C3_14},
    {1, C1_15, C2_15, C3_15},
    {1, C1_16, C2_16, C3_16},

    {0, C9_1,  C8_1,  C7_1},
    {0, C9_2,  C8_2,  C7_2},
    {0, C9_3,  C8_3,  C7_3},
    {0, C9_9,  C8_9,  C7_9},
    {0, C9_10, C8_10, C7_10},
    {0, C9_11, C8_11, C7_11},
    {1, C9_1,  C8_1,  C7_1},
    {1, C9_2,  C8_2,  C7_2},
    {1, C9_3,  C8_3,  C7_3},
    {1, C9_9,  C8_9,  C7_9},
    {1, C9_10, C8_10, C7_10},
    {1, C9_11, C8_11, C7_11},

    {0, C9_4,  C8_4,  C7_4},
    {0, C9_5,  C8_5,  C7_5},
    {0, C9_6,  C8_6,  C7_6},
    {0, C9_12, C8_12, C7_12},
    {0, C9_13, C8_13, C7_13},
    {0, C9_14, C8_14, C7_14},
    {0, C9_15, C8_15, C6_14}, // middle 2u switch
    {1, C9_4,  C8_4,  C7_4},
    {1, C9_5,  C8_5,  C7_5},
    {1, C9_6,  C8_6,  C7_6},
    {1, C9_12, C8_12, C7_12},
    {1, C9_13, C8_13, C7_13},
    {1, C9_14, C8_14, C7_14}
};

void matrix_init_kb(void) {

    // Turn status LED on
    gpio_set_pin_output(D6);
    gpio_write_pin_high(D6);

    matrix_init_user();
}

uint8_t rgb_matrix_map_row_column_to_led_kb(uint8_t row, uint8_t column, uint8_t *led_i) {
    // Spacebar has 2 leds 41 & 42, so add 42 to the array here, and 41 will be added
    // by the default lookup code that runs after this
    if (row == 3 && column == 5) {
        led_i[0] = 42;
        return 1;
    }
    return 0;
}

#ifdef SWAP_HANDS_ENABLE
__attribute__ ((weak))
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    {{11, 0}, {10, 0}, {9, 0}, {8, 0}, {7, 0}, {6, 0}, {5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}},
    {{11, 1}, {10, 1}, {9, 1}, {8, 1}, {7, 1}, {6, 1}, {5, 1}, {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1}},
    {{11, 2}, {10, 2}, {9, 2}, {8, 2}, {7, 2}, {6, 2}, {5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 2}},
    {{11, 3}, {10, 3}, {9, 3}, {8, 3}, {7, 3}, {6, 3}, {5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3}},
};

#    ifdef ENCODER_MAP_ENABLE
const uint8_t PROGMEM encoder_hand_swap_config[NUM_ENCODERS] = {0};
#    endif
#endif

const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = {
    {36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47},
    {24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35},
    {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23},
    { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11}
};
