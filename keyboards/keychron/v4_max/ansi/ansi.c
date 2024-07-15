/* Copyright 2024 @ Keychron (https://www.keychron.com)
 *
 * This program is free software : you can redistribute it and /or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.If not, see < http://www.gnu.org/licenses/>.
 */

#include "quantum.h"

// clang-format off

#ifdef RGB_MATRIX_ENABLE
const snled27351_led_t g_snled27351_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, G_1,    I_1,    H_1},
    {0, G_2,    I_2,    H_2},
    {0, G_3,    I_3,    H_3},
    {0, G_4,    I_4,    H_4},
    {0, G_5,    I_5,    H_5},
    {0, G_6,    I_6,    H_6},
    {0, G_7,    I_7,    H_7},
    {0, G_8,    I_8,    H_8},
    {0, G_9,    I_9,    H_9},
    {0, G_10,   I_10,   H_10},
    {0, G_11,   I_11,   H_11},
    {0, G_12,   I_12,   H_12},
    {0, G_13,   I_13,   H_13},
    {0, G_14,   I_14,   H_14},

    {0, D_1,    F_1,    E_1},
    {0, D_2,    F_2,    E_2},
    {0, D_3,    F_3,    E_3},
    {0, D_4,    F_4,    E_4},
    {0, D_5,    F_5,    E_5},
    {0, D_6,    F_6,    E_6},
    {0, D_7,    F_7,    E_7},
    {0, D_8,    F_8,    E_8},
    {0, D_9,    F_9,    E_9},
    {0, D_10,   F_10,   E_10},
    {0, D_11,   F_11,   E_11},
    {0, D_12,   F_12,   E_12},
    {0, D_13,   F_13,   E_13},
    {0, D_14,   F_14,   E_14},

    {0, A_1,    C_1,    B_1},
    {0, A_2,    C_2,    B_2},
    {0, A_3,    C_3,    B_3},
    {0, A_4,    C_4,    B_4},
    {0, A_5,    C_5,    B_5},
    {0, A_6,    C_6,    B_6},
    {0, A_7,    C_7,    B_7},
    {0, A_8,    C_8,    B_8},
    {0, A_9,    C_9,    B_9},
    {0, A_10,   C_10,   B_10},
    {0, A_11,   C_11,   B_11},
    {0, A_12,   C_12,   B_12},
    {0, A_14,   C_14,   B_14},

    {1, D_14,   F_14,   E_14},
    {1, D_12,   F_12,   E_12},
    {1, D_11,   F_11,   E_11},
    {1, D_10,   F_10,   E_10},
    {1, D_9,    F_9,    E_9 },
    {1, D_8,    F_8,    E_8 },
    {1, D_7,    F_7,    E_7 },
    {1, D_6,    F_6,    E_6 },
    {1, D_5,    F_5,    E_5 },
    {1, D_4,    F_4,    E_4 },
    {1, D_3,    F_3,    E_3},
    {1, D_1,    F_1,    E_1},

    {1, A_14,   C_14,   B_14},
    {1, A_13,   C_13,   B_13},
    {1, A_12,   C_12,   B_12},
    {1, A_8,    C_8,    B_8},
    {1, A_4,    C_4,    B_4},
    {1, A_3,    C_3,    B_3},
    {1, A_2,    C_2,    B_2},
    {1, A_1,    C_1,    B_1}
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13 },
        { 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27 },
        { 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, __, 40 },
        { 41, __, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, __, 52 },
        { 53, 54, 55, __, __, __, 56, __, __, __, 57, 58, 59, 60 }
    },
    {
        // LED Index to Physical Position
        {0, 0}, {13, 0}, {26, 0}, {35, 0}, {46, 0}, {57, 0}, {68, 0},  {79, 0}, {90, 0}, {101, 0}, {112, 0}, {123, 0}, {134, 0}, {145, 0},
        {7,16}, {20,16}, {30,16}, {41,16}, {52,16}, {63,16}, {74,16},  {85,16}, {96,16}, {107,16}, {118,16}, {129,16}, {140,16}, {149,16},
        {7,32}, {21,32}, {32,32}, {43,32}, {54,32}, {65,32}, {76,32},  {87,32}, {98,32}, {109,32}, {120,32}, {132,32},           {142,32},
        {8,48},          {28,48}, {37,48}, {48,48}, {59,48}, {70,48},  {81,48}, {92,48}, {103,48}, {114,48}, {125,48},           {142,48},
        {2,64}, {15,64}, {28,64},                            {72,64},                              {114,64}, {125,64}, {135,64}, {143,64}
    },
    {
        // RGB LED Index to Flag
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,
        1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,
        1, 1, 1,          4,          1, 1, 1, 1
    }
};
#endif
