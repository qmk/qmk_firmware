/* Copyright 2021 Jessica Sullivan and Don Kjer
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

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */

   {0, C_1,   B_1,   A_1},  // Esc
   {0, C_2,   B_2,   A_2},  // 1
   {0, C_3,   B_3,   A_3},  // 2
   {0, C_4,   B_4,   A_4},  // 3
   {0, C_5,   B_5,   A_5},  // 4
   {0, C_6,   B_6,   A_6},  // 5
   {0, C_7,   B_7,   A_7},  // 6
   {0, C_8,   B_8,   A_8},  // 7
   {0, C_9,   B_9,   A_9},  // 8
   {0, C_10,  B_10,  A_10}, // 9
   {0, C_11,  B_11,  A_11}, // 0
   {0, C_12,  B_12,  A_12}, // -
   {0, C_13,  B_13,  A_13}, // =
   {0, C_14,  B_14,  A_14}, // Bksp

   {0, F_1,   E_1,   D_1},  // Tab
   {0, F_2,   E_2,   D_2},  // Q
   {0, F_3,   E_3,   D_3},  // W
   {0, F_4,   E_4,   D_4},  // E
   {0, F_5,   E_5,   D_5},  // R
   {0, F_6,   E_6,   D_6},  // T
   {0, F_7,   E_7,   D_7},  // Y
   {0, F_8,   E_8,   D_8},  // U
   {0, F_9,   E_9,   D_9},  // I
   {0, F_10,  E_10,  D_10}, // O
   {0, F_11,  E_11,  D_11}, // P
   {0, F_12,  E_12,  D_12}, // [
   {0, F_13,  E_13,  D_13}, // ]
   {0, F_14,  E_14,  D_14}, // Pipe

   {0, I_1,   H_1,   G_1},  // Caps
   {0, I_2,   H_2,   G_2},  // A
   {0, I_3,   H_3,   G_3},  // S
   {0, I_4,   H_4,   G_4},  // D
   {0, I_5,   H_5,   G_5},  // F
   {0, I_6,   H_6,   G_6},  // G
   {0, I_7,   H_7,   G_7},  // H
   {0, I_8,   H_8,   G_8},  // J
   {0, I_9,   H_9,   G_9},  // K
   {0, I_10,  H_10,  G_10}, // L
   {0, I_11,  H_11,  G_11}, // :
   {0, I_12,  H_12,  G_12}, // '
   {0, I_14,  H_14,  G_14}, // Enter

   {0, L_1,   K_1,   J_1},  // LShift
   {0, L_2,   K_2,   J_2},  // Z
   {0, L_3,   K_3,   J_3},  // X
   {0, L_4,   K_4,   J_4},  // C
   {0, L_5,   K_5,   J_5},  // V
   {0, L_6,   K_6,   J_6},  // B
   {0, L_7,   K_7,   J_7},  // N
   {0, L_8,   K_8,   J_8},  // M
   {0, L_9,   K_9,   J_9},  // <
   {0, L_10,  K_10,  J_10}, // >
   {0, L_11,  K_11,  J_11}, // ?
   {0, L_12,  K_12,  J_12}, // RShift

   {1, C_1,   B_1,   A_1},  // LCtrl
   {1, C_2,   B_2,   A_2},  // LAlt
   {1, C_3,   B_3,   A_3},  // Windows
   {1, C_6,   B_6,   A_6},  // Space
   {1, C_10,  B_10,  A_10}, // Fn1/RAlt hades/venus
   {1, C_11,  B_11,  A_11}, // Fn2/Fn1
   {1, C_12,  B_12,  A_12}, // RCtrl/Fn2
   {1, C_13,  B_13,  A_13}, // LEFT/RCtrl
};

led_config_t g_led_config = { {
    {  0,   1,   2,   3,      4,      5,   6,      7,      8,      9,   10,  11,  12,     13     },
    {  14,  15,  16,  17,     18,     19,  20,     21,     22,     23,  24,  25,  26,     27     },
    {  28,  29,  30,  31,     32,     33,  34,     35,     36,     37,  38,  39,  NO_LED, 40     },
    {  41,  42,  43,  44,     45,     46,  47,     48,     49,     50,  51,  52,  NO_LED, NO_LED },
    {  53,  54,  55,  NO_LED, NO_LED, 56,  NO_LED, NO_LED, NO_LED, 57,  58,  59,  60,     NO_LED }
}, {
    {   0,   0 }, {  16,   0 }, {  32,   0 }, {  48,   0 }, {  64,   0 }, {  80,   0 }, {  96,   0 }, { 112,   0 }, { 128,   0 }, { 144,   0 }, { 160,   0 }, { 176,   0 }, { 192,   0 }, { 216,   0 },
    {   4,  16 }, {  24,  16 }, {  40,  16 }, {  56,  16 }, {  72,  16 }, {  88,  16 }, { 104,  16 }, { 120,  16 }, { 136,  16 }, { 152,  16 }, { 168,  16 }, { 184,  16 }, { 200,  16 }, { 220,  16 },
    {   6,  32 }, {  28,  32 }, {  44,  32 }, {  60,  32 }, {  76,  32 }, {  92,  32 }, { 108,  32 }, { 124,  32 }, { 140,  32 }, { 156,  32 }, { 172,  32 }, { 188,  32 },               { 214,  32 },
    {  10,  48 },               {  36,  48 }, {  52,  48 }, {  68,  48 }, {  84,  48 }, { 100,  48 }, { 116,  48 }, { 132,  48 }, { 148,  48 }, { 164,  48 }, { 180,  48 },               { 210,  48 },
    {   2,  64 }, {  22,  64 }, {  42,  64 },                                           { 102,  64 },                                           { 162,  64 }, { 182,  64 }, { 202,  64 }, { 222,  64 },
}, {
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,
    1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,
    1, 1, 1,          4,          1, 1, 1, 1
} };
#endif /* RGB_MATRIX_ENABLE */
