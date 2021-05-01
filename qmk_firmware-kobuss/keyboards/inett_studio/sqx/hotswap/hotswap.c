/**
 * @file hotswap.c
 *
    Copyright 2020 astro <yuleiz@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "hotswap.h"

#ifdef RGB_MATRIX_ENABLE
const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
// left CA
    {0, C1_1,   C3_2,   C4_2},
    {0, C1_2,   C2_2,   C4_3},
    {0, C1_3,   C2_3,   C3_3},
    {0, C1_4,   C2_4,   C3_4},
    {0, C1_5,   C2_5,   C3_5},
    {0, C1_6,   C2_6,   C3_6},
    {0, C1_7,   C2_7,   C3_7},
    {0, C1_8,   C2_8,   C3_8},

    //{0, C5_1,   C4_1,   C6_1},
    //{0, C5_8,   C4_8,   C6_8},

    {0, C9_1,   C8_1,   C7_1},
    {0, C9_2,   C8_2,   C7_2},
    //{0, C9_3,   C8_3,   C7_3},
    {0, C9_4,   C8_4,   C7_4},
    {0, C9_5,   C8_5,   C7_5},
    {0, C9_6,   C8_6,   C7_6},
    {0, C9_7,   C8_7,   C6_6},
    {0, C9_8,   C7_7,   C6_7},
// left CB
    {0, C1_9,   C3_10,  C4_10},
    {0, C1_10,  C2_10,  C4_11},
    {0, C1_11,  C2_11,  C3_11},
    {0, C1_12,  C2_12,  C3_12},
    {0, C1_13,  C2_13,  C3_13},
    {0, C1_14,  C2_14,  C3_14},
    {0, C1_15,  C2_15,  C3_15},
    {0, C1_16,  C2_16,  C3_16},

    {0, C5_9,   C4_9,   C6_9},
    {0, C5_16,  C4_16,  C6_16},

    {0, C9_9,   C8_9,   C7_9},
    {0, C9_10,  C8_10,  C7_10},
    {0, C9_11,  C8_11,  C7_11},
    {0, C9_12,  C8_12,  C7_12},
    {0, C9_13,  C8_13,  C7_13},
    {0, C9_14,  C8_14,  C7_14},
    {0, C9_15,  C8_15,  C6_14},
    {0, C9_16,  C7_15,  C6_15},

// right CA
    {1, C1_1,   C3_2,   C4_2},
    {1, C1_2,   C2_2,   C4_3},
    {1, C1_3,   C2_3,   C3_3},
    {1, C1_4,   C2_4,   C3_4},
    {1, C1_5,   C2_5,   C3_5},
    {1, C1_6,   C2_6,   C3_6},
    {1, C1_7,   C2_7,   C3_7},
    {1, C1_8,   C2_8,   C3_8},

    //{1, C5_1,   C4_1,   C6_1},
    //{1, C5_8,   C4_8,   C6_8},

    {1, C9_1,   C8_1,   C7_1},
    {1, C9_2,   C8_2,   C7_2},
    {1, C9_3,   C8_3,   C7_3},
    {1, C9_4,   C8_4,   C7_4},
    {1, C9_5,   C8_5,   C7_5},
    {1, C9_6,   C8_6,   C7_6},
    {1, C9_7,   C8_7,   C6_6},
    {1, C9_8,   C7_7,   C6_7},
// right CB
    {1, C1_9,   C3_10,  C4_10},
    {1, C1_10,  C2_10,  C4_11},
    {1, C1_11,  C2_11,  C3_11},
    {1, C1_12,  C2_12,  C3_12},
    {1, C1_13,  C2_13,  C3_13},
    //{1, C1_14,  C2_14,  C3_14},
    {1, C1_15,  C2_15,  C3_15},
    {1, C1_16,  C2_16,  C3_16},

    //{1, C5_9,   C4_9,   C6_9},
    //{1, C5_16,  C4_16,  C6_16},

    {1, C9_9,   C8_9,   C7_9},
    {1, C9_10,  C8_10,  C7_10},
    {1, C9_11,  C8_11,  C7_11},
    {1, C9_12,  C8_12,  C7_12},
    {1, C9_13,  C8_13,  C7_13},
    {1, C9_14,  C8_14,  C7_14},
    {1, C9_15,  C8_15,  C6_14},
    {1, C9_16,  C7_15,  C6_15},
};

led_config_t g_led_config = {
    {
        { 18,      19,     20,     21,     22,     23,  24,     16,     17,     36, 37,   38,     39, 40},
        { 26,      27,     28,     29,     30,     31,  25,     48,     41,     42, 43,   44,     45, 46},
        {  8,       7,      0,     32,     33,     34,  35,     49,     50,     51, 52,   53, NO_LED, 47},
        {  9, NO_LED,     10,      1,      2,      3,    4,      5,     56,     55, 57,   58,     59, 54},
        {  14,     13,     12,     11, NO_LED, NO_LED,   6,     15, NO_LED, NO_LED, 60,   61,     62, 63},
    },
    {
        { 48, 32},{ 48, 48},{ 64, 48},{ 80, 48},{ 96, 48},{112, 48},{112, 64},{ 32, 32},
        { 16, 32},{ 16, 48},          { 32, 48},{ 64, 64},{ 40, 64},{ 20, 64},{  0, 64},

        {  0,  0},{ 16,  0},{ 32,  0},{ 48,  0},{ 64,  0},{ 80, 0},{ 96,  0},{ 96, 16},
        {  0, 16},{ 16, 16},
        { 32, 16},{ 48, 16},{ 64, 16},{ 80, 16},{ 64, 32},{ 80, 32},{ 96, 32},{112, 32},

        {112,  0},{128,  0},{144,  0},{160,  0},{176,  0},{192,  0},{208,  0},{224,  0},
        {128, 16},{144, 16},{160, 16},{176, 16},{192, 16},{216, 16},{216, 32},{112, 16},

        {128, 32},{144, 32},{160, 32},{176, 32},{192, 32},          {224, 48},{144, 48},
        {128, 48},{160, 48},{176, 48},{192, 48},{160, 64},{180, 64},{200, 64},{224, 64}
    },
    {
        4, 4, 4, 4, 4, 4, 4, 1,
        1, 1,    4, 1, 1, 1, 1,

        1, 4, 4, 4, 4, 4, 4, 4,
        1, 4,
        4, 4, 4, 4, 4, 4, 4, 4,

        4, 4, 4, 4, 4, 4, 1, 1,
        4, 4, 4, 4, 4, 1, 1, 4,

        4, 4, 4, 4, 4,    1, 4,
        4, 4, 4, 1, 1, 1, 1, 1,
    }
};

#endif  //RGB_MATRIX_ENABLE

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
#if defined(RGB_MATRIX_DISABLE_KEYCODES)
        case RGB_MATRIX_TOGGLE: // toggle rgb matrix
            rgb_matrix_toggle();
            return false;
        case RGB_MATRIX_STEP:
            rgb_matrix_step();
            return false;
        case RGB_MATRIX_INC_HUE:
            rgb_matrix_increase_hue();
            return false;
        case RGB_MATRIX_DEC_HUE:
            rgb_matrix_decrease_hue();
            return false;
        case RGB_MATRIX_INC_SAT:
            rgb_matrix_increase_sat();
            return false;
        case RGB_MATRIX_DEC_SAT:
            rgb_matrix_decrease_sat();
            return false;
        case RGB_MATRIX_INC_VAL:
            rgb_matrix_increase_val();
            return false;
        case RGB_MATRIX_DEC_VAL:
            rgb_matrix_decrease_val();
            return false;
#endif
            default:
            break;
        }
    }
    return true;
}
