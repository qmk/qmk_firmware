/* Copyright 2023 @ Keychron (https://www.keychron.com)
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
    {0, A_15,   C_15,   B_15},
    {0, A_14,   C_14,   B_14},
    {0, A_13,   C_13,   B_13},
    {0, A_12,   C_12,   B_12},
    {0, A_11,   C_11,   B_11},
    {0, A_10,   C_10,   B_10},
    {0, A_9,    C_9,    B_9},
    {0, A_8,    C_8,    B_8},
    {0, A_7,    C_7,    B_7},
    {0, A_6,    C_6,    B_6},
    {0, A_5,    C_5,    B_5},
    {0, A_4,    C_4,    B_4},
    {0, A_3,    C_3,    B_3},
    {0, A_2,    C_2,    B_2},
    {0, A_1,    C_1,    B_1},
    {0, D_16,   F_16,   E_16},
    {0, D_15,   F_15,   E_15},
    {0, D_14,   F_14,   E_14},
    {0, D_13,   F_13,   E_13},
    {0, D_12,   F_12,   E_12},
    {0, D_11,   F_11,   E_11},
    {0, D_10,   F_10,   E_10},
    {0, D_9,    F_9,    E_9},
    {0, D_8,    F_8,    E_8},
    {0, D_7,    F_7,    E_7},
    {0, D_6,    F_6,    E_6},
    {0, D_5,    F_5,    E_5},
    {0, D_4,    F_4,    E_4},
    {0, D_3,    F_3,    E_3},
    {0, D_2,    F_2,    E_2},
    {0, D_1,    F_1,    E_1},
    {1, A_16,   C_16,   B_16},
    {1, A_15,   C_15,   B_15},
    {1, A_14,   C_14,   B_14},
    {1, A_13,   C_13,   B_13},
    {1, A_12,   C_12,   B_12},
    {1, A_11,   C_11,   B_11},
    {1, A_10,   C_10,   B_10},
    {1, A_9,    C_9,    B_9},
    {1, A_8,    C_8,    B_8},
    {1, A_7,    C_7,    B_7},
    {1, A_6,    C_6,    B_6},
    {1, A_5,    C_5,    B_5},
    {1, A_4,    C_4,    B_4},
    {1, A_3,    C_3,    B_3},
    {1, A_2,    C_2,    B_2},
    {1, G_16,   I_16,   H_16},
    {1, G_15,   I_15,   H_15},
    {1, G_13,   I_13,   H_13},
    {1, G_12,   I_12,   H_12},
    {1, G_11,   I_11,   H_11},
    {1, G_10,   I_10,   H_10},
    {1, G_9,    I_9,    H_9},
    {1, G_8,    I_8,    H_8},
    {1, G_7,    I_7,    H_7},
    {1, G_6,    I_6,    H_6},
    {1, G_5,    I_5,    H_5},
    {1, G_4,    I_4,    H_4},
    {1, G_3,    I_3,    H_3},
    {1, G_2,    I_2,    H_2},
    {1, G_1,    I_1,    H_1},
    {1, D_16,   F_16,   E_16},
    {1, D_15,   F_15,   E_15},
    {1, D_14,   F_14,   E_14},
    {1, D_13,   F_13,   E_13},
    {1, D_9,    F_9,    E_9},
    {1, D_6,    F_6,    E_6},
    {1, D_5,    F_5,    E_5},
    {1, D_4,    F_4,    E_4},
    {1, D_3,    F_3,    E_3},
    {1, D_2,    F_2,    E_2},
    {1, D_1,    F_1,    E_1},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { __,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14 },
        { 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 },
        { 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, __ },
        { 46, 47, __, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60 },
        { 61, 62, 63, 64, __, __, __, 65, __, __, 66, 67, 68, 69, 70, 71 },
    },
    {
        // LED Index to Physical Position
                {20, 0}, {33, 0}, {47, 0}, {60, 0}, {73, 0}, {86, 0}, { 99, 0}, {112, 0}, {125, 0}, {138, 0}, {151, 0}, {164, 0}, {177, 0}, {197, 0}, {224, 0},
        {0,15}, {24,15}, {40,15}, {53,15}, {66,15}, {79,15}, {92,15}, {105,15}, {119,15}, {132,15}, {145,15}, {158,15}, {171,15}, {184,15}, {200,15}, {224,15},
        {0,30}, {25,30}, {43,30}, {56,30}, {69,30}, {83,30}, {96,30}, {109,30}, {122,30}, {135,30}, {148,30}, {161,30}, {174,30}, {195,30}, {224,30},
        {0,45}, {29,45},          {50,45}, {63,45}, {76,45}, {89,45}, {102,45}, {115,45}, {128,45}, {141,45}, {155,45}, {168,45}, {186,45}, {207,49}, {224,45},
        {0,60}, {22,60}, {38,60}, {55,60},                            {104,60},                     {151,60}, {164,60}, {177,60}, {194,64}, {207,64}, {220,64}
    },
    {
        // RGB LED Index to Flag
           1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1,          1,       1, 1, 1, 1, 1, 1
    }
};
#endif
