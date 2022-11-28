/* Copyright 2021 @ Keychron (https://www.keychron.com)
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

#ifdef RGB_MATRIX_ENABLE

// clang-format off

const ckled2001_led PROGMEM g_ckled2001_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to CKLED manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, I_1,    G_1,    H_1},
    {0, I_2,    G_2,    H_2},
    {0, I_3,    G_3,    H_3},
    {0, I_4,    G_4,    H_4},
    {0, I_5,    G_5,    H_5},
    {0, I_6,    G_6,    H_6},
    {0, I_7,    G_7,    H_7},
    {0, I_8,    G_8,    H_8},
    {0, I_9,    G_9,    H_9},
    {0, I_10,   G_10,   H_10},
    {0, I_11,   G_11,   H_11},
    {0, I_12,   G_12,   H_12},
    {0, I_13,   G_13,   H_13},
    {0, I_14,   G_14,   H_14},
    {0, I_15,   G_15,   H_15},

    {0, F_1,    D_1,    E_1},
    {0, F_2,    D_2,    E_2},
    {0, F_3,    D_3,    E_3},
    {0, F_4,    D_4,    E_4},
    {0, F_5,    D_5,    E_5},
    {0, F_6,    D_6,    E_6},
    {0, F_7,    D_7,    E_7},
    {0, F_8,    D_8,    E_8},
    {0, F_9,    D_9,    E_9},
    {0, F_10,   D_10,   E_10},
    {0, F_11,   D_11,   E_11},
    {0, F_12,   D_12,   E_12},
    {0, F_13,   D_13,   E_13},
    {0, F_15,   D_15,   E_15},

    {0, C_1,    A_1,    B_1},
    {0, C_2,    A_2,    B_2},
    {0, C_3,    A_3,    B_3},
    {0, C_4,    A_4,    B_4},
    {0, C_5,    A_5,    B_5},
    {1, C_10,   A_10,   B_10},
    {1, C_8,    A_8,    B_8},
    {1, C_7,    A_7,    B_7},
    {1, C_6,    A_6,    B_6},
    {1, C_5,    A_5,    B_5},
    {1, C_4,    A_4,    B_4},
    {1, C_3,    A_3,    B_3},
    {1, C_2,    A_2,    B_2},
    {0, F_14,   D_14,   E_14},
    {1, C_1,    A_1,    B_1},

    {1, I_15,   G_15,   H_15},
    {1, I_14,   G_14,   H_14},
    {1, I_13,   G_13,   H_13},
    {1, I_12,   G_12,   H_12},
    {1, I_11,   G_11,   H_11},
    {1, I_10,   G_10,   H_10},
    {1, I_9,    G_9,    H_9},
    {1, I_8,    G_8,    H_8},
    {1, I_7,    G_7,    H_7},
    {1, I_6,    G_6,    H_6},
    {1, I_5,    G_5,    H_5},
    {1, I_4,    G_4,    H_4},
    {1, I_3,    G_3,    H_3},
    {1, I_2,    G_2,    H_2},
    {1, I_1,    G_1,    H_1},

    {1, F_15,   D_15,   E_15},
    {1, F_14,   D_14,   E_14},
    {1, F_13,   D_13,   E_13},
    {1, F_12,   D_12,   E_12},
    {1, F_9,    D_9,    E_9},
    {1, F_8,    D_8,    E_8},
    {1, F_7,    D_7,    E_7},
    {1, F_6,    D_6,    E_6},
    {1, F_3,    D_3,    E_3},
    {1, F_2,    D_2,    E_2},
    {1, F_1,    D_1,    E_1}
};

#define __ NO_LED

led_config_t g_led_config = {
     {
        // Key Matrix to LED Index
        {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14 },
        { 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 42, 28 },
        { 29, 30, 31, 32, 33, 34, __, 35, 36, 37, 38, 39, 40, 41, 43 },
        { 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58 },
        { 59, 60, 61, 62, __, __, 63, 64, 65, 66, __, __, 67, 68, 69 },
    },
    {
        // LED Index to Physical Position
        {7,1},  {20,1},  {33,0},  {48,3},  {61,6},  {74,8},  {87,11},  {106,11}, {119,8},  {132,6},  {145,3},  {160,0},  {173,1},  {193,1},            {220,0},
        {7,14}, {24,14}, {39,14}, {52,17}, {65,19}, {78,22}, {103,25}, {116,22}, {129,20}, {142,17}, {155,14}, {172,14}, {186,14},                     {222,16},
        {6,27}, {24,27}, {39,27}, {52,30}, {65,33}, {78,35}, {109,37}, {122,34}, {135,31}, {148,29}, {162,27}, {176,27}, {189,27}, {207,22},           {224,29},
        {0,40}, {15,40}, {28,40}, {43,41}, {56,44}, {69,47}, {82,49},  {102,51}, {115,49}, {128,46}, {141,43}, {154,41}, {169,40}, {187,40}, {209,43},
        {0,52}, {17,52}, {42,54},          {65,59},          {86,63},  {104,64},           {129,59},           {153,54},           {196,56}, {209,56}, {222,59},
    },
    {
        // RGB LED Index to Flag
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,       1,
        8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
        1, 1, 1,    1,    1,    1, 1,    1,    1, 1, 1,
    }
};

#endif // RGB_MATRIX_ENABLE
