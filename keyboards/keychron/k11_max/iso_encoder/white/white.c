/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

// clang-format off
#ifdef LED_MATRIX_ENABLE
const snled27351_led_t g_snled27351_leds[LED_MATRIX_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  LED address
 *   |  | */
    {0, E_1},
    {0, E_2},
    {0, E_3},
    {0, E_4},
    {0, E_5},
    {0, E_6},
    {0, E_7},
    {0, E_8},
    {0, E_9},
    {0, E_10},
    {0, E_11},
    {0, E_12},
    {0, E_13},
    {0, E_14},

    {0, D_1},
    {0, D_2},
    {0, D_3},
    {0, D_4},
    {0, D_5},
    {0, D_6},
    {0, D_7},
    {0, D_8},
    {0, D_9},
    {0, D_10},
    {0, D_11},
    {0, D_12},
    {0, D_13},
    {0, D_14},
    {0, D_16},

    {0, C_1},
    {0, C_2},
    {0, C_3},
    {0, C_4},
    {0, C_5},
    {0, C_6},
    {0, C_7},
    {0, C_8},
    {0, C_9},
    {0, C_10},
    {0, C_11},
    {0, C_12},
    {0, C_14},
    {0, C_16},

    {0, B_1},
    {0, B_2},
    {0, B_3},
    {0, B_4},
    {0, B_5},
    {0, B_6},
    {0, B_7},
    {0, B_8},
    {0, B_9},
    {0, B_10},
    {0, B_11},
    {0, B_12},
    {0, B_14},
    {0, B_15},
    {0, B_16},

    {0, A_1},
    {0, A_2},
    {0, A_3},
    {0, A_6},
    {0, A_7},
    {0, A_8},
    {0, A_10},
    {0, A_13},
    {0, A_14},
    {0, A_15},
    {0, A_16},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, __, __ },
        { 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, __, 28 },
        { 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, __, 41, __, 42 },
        { 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, __, 55, 56, 57 },
        { 58, 59, 60, __, __, 61, 62, 63, __, 64, __, __, 65, 66, 67, 68 },
    },
    {
        // LED Index to Physical Position
        {8, 1}, {20, 1}, {33, 0}, {48, 3}, {61, 6}, {74, 8}, {87,11}, {106,11}, {119, 8}, {132, 6}, {145, 3}, {160, 0}, {173, 1}, {193, 1},
        {8,14}, {24,14}, {39,14}, {52,17}, {65,20}, {78,22}, {103,25},{116,22}, {129,20}, {142,17}, {155,14}, {170,14}, {183,14}, {200,20},           {222,14},
        {8,27}, {24,27}, {39,28}, {52,30}, {65,33}, {78,36}, {109,37},{122,34}, {135,32}, {148,29}, {162,27}, {176,27}, {190,27},                     {224,27},
        {8,40}, {13,40}, {28,40}, {43,42}, {56,44}, {69,47}, {82,50}, {102,52}, {115,49}, {128,46}, {141,44}, {154,44},           {169,40}, {189,40}, {209,43},
        {0,53}, {16,53}, {42,55},                   {65,60}, {86,64}, {107,64},           {131,59},                     {156,54}, {196,56}, {209,56}, {222,56},
    },
    {
        //LED Index to Flag
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,    1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1,
        1, 1, 1,       1, 1, 1,    1,       1, 1, 1, 1,
    }
};

#endif
