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
    {0, A_2,    C_2,    B_2},
    {0, A_1,    C_1,    B_1},
    {0, A_4,    C_4,    B_4},
    {0, J_10,   L_10,   K_10},
    {0, J_11,   L_11,   K_11},
    {0, J_8,    L_8,    K_8},
    {0, J_2,    L_2,    K_2},
    {0, J_1,    L_1,    K_1},
    {0, D_1,    F_1,    E_1},
    {0, D_2,    F_2,    E_2},

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

    {0, A_16,   C_16,   B_16},
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
    {0, A_3,    C_3,    B_3},

    {0, G_16,   I_16,   H_16},
    {0, G_15,   I_15,   H_15},
    {0, G_14,   I_14,   H_14},
    {0, G_13,   I_13,   H_13},
    {0, G_12,   I_12,   H_12},
    {0, G_11,   I_11,   H_11},
    {0, G_10,   I_10,   H_10},
    {0, G_9,    I_9,    H_9},
    {0, G_8,    I_8,    H_8},
    {0, G_7,    I_7,    H_7},
    {0, G_6,    I_6,    H_6},
    {0, G_5,    I_5,    H_5},
    {0, G_4,    I_4,    H_4},
    {0, G_3,    I_3,    H_3},

    {0, J_16,   L_16,   K_16},
    {0, J_15,   L_15,   K_15},
    {0, J_14,   L_14,   K_14},
    {0, J_13,   L_13,   K_13},
    {0, J_12,   L_12,   K_12},
    {0, J_9,    L_9,    K_9},
    {0, J_7,    L_7,    K_7},
    {0, J_6,    L_6,    K_6},
    {0, J_5,    L_5,    K_5},
    {0, J_4,    L_4,    K_4},
    {0, J_3,    L_3,    K_3},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { __,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, __ },
        { 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 },
        { 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, __ },
        { 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52 },
        { 53, 54, 55, 56, 57, __, __, 58, __, 59, 60, 61, 62, 63 },
    },
    {
        //  LED Index to Physical Position
               {17,0}, {34,0}, {51,0}, {68,0}, {84,0}, {102,0}, {119,0}, {136,0}, {153,0}, {170,0}, {187,0}, {204,0}, 
        {0,16},{17,16},{34,16},{51,16},{68,16},{84,16},{102,16},{119,16},{136,16},{153,16},{170,16},{187,16},{204,16},{220,16},
        {0,32},{17,32},{34,32},{51,32},{68,32},{84,32},{102,32},{119,32},{136,32},{153,32},{170,32},{187,32},         {212,32},
        {0,48},{17,48},{34,48},{51,48},{68,48},{84,48},{102,48},{119,48},{136,48},{153,48},{170,48},{187,48},{204,48},{220,48},
        {0,64},{17,64},{34,64},{51,64},{76,64},                 {121,64},         {153,64},{170,64},{187,64},{204,64},{220,64},
    },
    {
        // RGB LED Index to Flag
           1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1,       1,    1, 1, 1, 1,
    }
};
#endif
