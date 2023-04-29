/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

const ckled2001_led PROGMEM g_ckled2001_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, C_1,    A_1,    B_1},
    {0, C_2,    A_2,    B_2},
    {0, C_3,    A_3,    B_3},
    {0, C_4,    A_4,    B_4},
    {0, C_5,    A_5,    B_5},
    {0, C_6,    A_6,    B_6},
    {0, C_7,    A_7,    B_7},
    {0, C_8,    A_8,    B_8},
    {0, C_9,    A_9,    B_9},
    {0, C_10,   A_10,   B_10},
    {0, C_11,   A_11,   B_11},
    {0, C_12,   A_12,   B_12},
    {0, C_13,   A_13,   B_13},
    {0, C_14,   A_14,   B_14},
    {0, C_15,   A_15,   B_15},
    {0, C_16,   A_16,   B_16},

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
    {0, F_16,   D_16,   E_16},

    {0, I_1,    G_1,    H_1},
    {0, I_2,    G_2,    H_2},
    {0, I_3,    G_3,    H_3},
    {0, I_4,    G_4,    H_4},
    {0, I_5,    G_5,    H_5},
    {1, I_6,    G_6,    H_6},
    {1, I_7,    G_7,    H_7},
    {1, I_8,    G_8,    H_8},
    {1, I_9,    G_9,    H_9},
    {1, I_10,   G_10,   H_10},
    {1, I_11,   G_11,   H_11},
    {1, I_12,   G_12,   H_12},
    {1, I_14,   G_14,   H_14},
    {0, F_14,   D_14,   E_14},
    {1, I_16,   G_16,   H_16},

    {1, C_1,    A_1,    B_1},
    {1, C_3,    A_3,    B_3},
    {1, C_4,    A_4,    B_4},
    {1, C_5,    A_5,    B_5},
    {1, C_6,    A_6,    B_6},
    {1, C_7,    A_7,    B_7},
    {1, C_8,    A_8,    B_8},
    {1, C_9,    A_9,    B_9},
    {1, C_10,   A_10,   B_10},
    {1, C_11,   A_11,   B_11},
    {1, C_12,   A_12,   B_12},
    {1, C_13,   A_13,   B_13},
    {1, C_14,   A_14,   B_14},
    {1, C_15,   A_15,   B_15},

    {1, F_1,    D_1,    E_1},
    {1, F_2,    D_2,    E_2},
    {1, F_3,    D_3,    E_3},
    {1, F_4,    D_4,    E_4},
    {1, F_7,    D_7,    E_7},
    {1, F_10,   D_10,   E_10},
    {1, F_11,   D_11,   E_11},
    {1, F_12,   D_12,   E_12},
    {1, F_13,   D_13,   E_13},
    {1, F_14,   D_14,   E_14},
    {1, F_15,   D_15,   E_15},
    {1, F_16,   D_16,   E_16}
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 15 },
        { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 43, 29 },
        { 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 69, 42, 44 },
        { 45, 14, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58 },
        { 59, 60, 61, 62, __, __, 63, __, __, 64, 65, 66, 67, 68, 70 }
    },
    {
        // LED Index to Physical Position
        {0,4},  {15,4},  {29,4},  {44,4},  {59,4},  {73,4},  {88,4},  {103,4},  {117,4},  {132,4},  {146,4},  {161,4},  {176,4},  {190,4},  {205,4},  {224,0},
        {4,19}, {22,19}, {37,19}, {51,19}, {66,19}, {81,19}, {95,19}, {110,19}, {125,19}, {139,19}, {154,19}, {168,19}, {183,19},                     {224,19},
        {6,34}, {26,34}, {40,34}, {55,34}, {70,34}, {84,34}, {99,34}, {114,34}, {128,34}, {143,34}, {158,34}, {172,34}, {187,34}, {207,29},           {224,34},
        {9,49},          {33,49}, {48,49}, {62,49}, {77,49}, {92,49}, {106,49}, {121,49}, {136,49}, {150,49}, {165,49}, {179,49}, {194,49}, {209,49},
        {2,64}, {18,64}, {35,64}, {51,64},                   {92,64},                     {134,64}, {150,64}, {165,64}, {179,64}, {194,64}, {209,64}, {223,64},
    },
    {
        // RGB LED Index to Flag
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,       1,
        8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    1,
        1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
        1, 1, 1, 1,       4,       1, 1, 1, 1, 1, 1, 1
    }
};

#endif // RGB_MATRIX_ENABLE
