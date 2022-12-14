/* Copyright 2022 @ Keychron (https://www.keychron.com)
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
/* Refer to CKLED manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, C_15, A_15, B_15}, // Esc
    {0, C_14, A_14, B_14}, // 1!
    {0, C_13, A_13, B_13}, // 2@
    {0, C_12, A_12, B_12}, // 3#
    {0, C_11, A_11, B_11}, // 4$
    {0, C_10, A_10, B_10}, // 5%
    {0, C_9,  A_9,  B_9},  // 6^
    {0, C_8,  A_8,  B_8},  // 7&
    {0, C_7,  A_7,  B_7},  // 8*
    {0, C_6,  A_6,  B_6},  // 9(
    {0, C_5,  A_5,  B_5},  // 0)
    {0, C_4,  A_4,  B_4},  // -_
    {0, C_3,  A_3,  B_3},  // =+
    {0, C_2,  A_2,  B_2},  // BackSpace
    {0, C_1,  A_1,  B_1},  // Delete

    {0, F_16, D_16, E_16}, // Macro2
    {0, F_15, D_15, E_15}, // Tab
    {0, F_14, D_14, E_14}, // Q
    {0, F_13, D_13, E_13}, // W
    {0, F_12, D_12, E_12}, // E
    {0, F_11, D_11, E_11}, // R
    {0, F_10, D_10, E_10}, // T
    {0, F_9,  D_9,  E_9},  // Y
    {0, F_8,  D_8,  E_8},  // U
    {0, F_7,  D_7,  E_7},  // I
    {0, F_6,  D_6,  E_6},  // O
    {0, F_5,  D_5,  E_5},  // P
    {0, F_4,  D_4,  E_4},  // [{
    {0, F_3,  D_3,  E_3},  // ]}
    {0, F_2,  D_2,  E_2},  // |
    {0, F_1,  D_1,  E_1},  // PageUp

    {1, C_16, A_16, B_16}, // Macro3
    {1, C_15, A_15, B_15}, // CapsLock
    {1, C_14, A_14, B_14}, // A
    {1, C_13, A_13, B_13}, // S
    {1, C_12, A_12, B_12}, // D
    {1, C_11, A_11, B_11}, // F
    {1, C_10, A_10, B_10}, // G
    {1, C_9,  A_9,  B_9},  // H
    {1, C_8,  A_8,  B_8},  // J
    {1, C_7,  A_7,  B_7},  // K
    {1, C_6,  A_6,  B_6},  // L
    {1, C_5,  A_5,  B_5},  // ;:
    {1, C_4,  A_4,  B_4},  // '"
    {1, C_2,  A_2,  B_2},  // Enter
    {1, C_1,  A_1,  B_1},  // PageDown

    {1, I_16, G_16, H_16}, // Macro4
    {1, I_15, G_15, H_15}, // LeftShift
    {1, I_13, G_13, H_13}, // Z
    {1, I_12, G_12, H_12}, // X
    {1, I_11, G_11, H_11}, // C
    {1, I_10, G_10, H_10}, // V
    {1, I_9,  G_9,  H_9},  // B
    {1, I_8,  G_8,  H_8},  // N
    {1, I_7,  G_7,  H_7},  // M
    {1, I_6,  G_6,  H_6},  // ,<
    {1, I_5,  G_5,  H_5},  // .>
    {1, I_4,  G_4,  H_4},  // /?
    {1, I_3,  G_3,  H_3},  // RightShift
    {1, I_2,  G_2,  H_2},  // Up
    {1, I_1,  G_1,  H_1},  // Home

    {1, F_16, D_16, E_16}, // Macro5
    {1, F_15, D_15, E_15}, // LeftControl
    {1, F_14, D_14, E_14}, // LeftOption
    {1, F_13, D_13, E_13}, // LeftCommand
    {1, F_9,  D_9,  E_9},  // Space
    {1, F_6,  D_6,  E_6},  // RightCommand
    {1, F_5,  D_5,  E_5},  // Fn1
    {1, F_4,  D_4,  E_4},  // Fn2
    {1, F_3,  D_3,  E_3},  // Left
    {1, F_2,  D_2,  E_2},  // Down
    {1, F_1,  D_1,  E_1},  // Right
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { __,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14 },
        { 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 },
        { 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, __, 44, 45 },
        { 46, 47, __, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60 },
        { 61, 62, 63, 64, __, __, __, 65, __, __, 66, 67, 68, 69, 70, 71 },
    },
    {
        // LED Index to Physical Position
                {20,0},  {33,0},  {47,0},  {60,0},  {73,0},  {86,0},  {99,0},   {112,0},  {125,0},  {138,0},  {151,0},  {164,0},  {177,0},  {197,0},            {224,0},
        {0,15}, {24,15}, {40,15}, {53,15}, {66,15}, {79,15}, {92,15}, {105,15}, {119,15}, {132,15}, {145,15}, {158,15}, {171,15}, {184,15}, {200,15},           {224,15},
        {0,30}, {25,30}, {43,30}, {56,30}, {69,30}, {83,30}, {96,30}, {109,30}, {122,30}, {135,30}, {148,30}, {161,30}, {174,30},           {195,30},           {224,30},
        {0,45}, {29,45},          {50,45}, {63,45}, {76,45}, {89,45}, {102,45}, {115,45}, {128,45}, {141,45}, {155,45}, {168,45},           {186,45}, {207,49}, {224,45},
        {0,60}, {22,60}, {38,60}, {55,60},                            {104,60},                               {151,60}, {164,60}, {177,60}, {194,64}, {207,64}, {220,64},
    },
    {
        // RGB LED Index to Flag
           1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    1,
        1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,
        1, 9, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,    1,
        1, 1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1, 1, 1,
        1, 1, 1, 1,          4,          1, 1, 1, 1, 1, 1,
    }
};

#endif // RGB_MATRIX_ENABLE
