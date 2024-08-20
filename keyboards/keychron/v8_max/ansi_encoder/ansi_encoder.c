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

#ifdef RGB_MATRIX_ENABLE
const snled27351_led_t g_snled27351_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
   {0, G_1,     I_1,    H_1},
   {0, G_2,     I_2,    H_2},
   {0, G_3,     I_3,    H_3},
   {0, G_4,     I_4,    H_4},
   {0, G_5,     I_5,    H_5},
   {0, G_6,     I_6,    H_6},
   {0, G_7,     I_7,    H_7},
   {0, G_8,     I_8,    H_8},
   {0, G_9,     I_9,    H_9},
   {0, G_10,    I_10,   H_10},
   {0, G_11,    I_11,   H_11},
   {0, G_12,    I_12,   H_12},
   {0, G_13,    I_13,   H_13},
   {0, G_15,    I_15,   H_15},
   {0, G_16,    I_16,   H_16},

   {0, D_1,     F_1,    E_1},
   {0, D_2,     F_2,    E_2},
   {0, D_3,     F_3,    E_3},
   {0, D_4,     F_4,    E_4},
   {0, D_5,     F_5,    E_5},
   {0, D_6,     F_6,    E_6},
   {0, D_8,     F_8,    E_8},
   {0, D_9,     F_9,    E_9},
   {0, D_10,    F_10,   E_10},
   {0, D_11,    F_11,   E_11},
   {0, D_12,    F_12,   E_12},
   {0, D_13,    F_13,   E_13},
   {0, D_14,    F_14,   E_14},
   {0, D_15,    F_15,   E_15},
   {0, D_16,    F_16,   E_16},

   {0, A_1,     C_1,    B_1},
   {0, A_2,     C_2,    B_2},
   {0, A_3,     C_3,    B_3},
   {0, A_4,     C_4,    B_4},
   {0, A_5,     C_5,    B_5},
   {0, A_6,     C_6,    B_6},
   {0, A_8,     C_8,    B_8},
   {0, A_9,     C_9,    B_9},
   {0, A_10,    C_10,   B_10},
   {0, A_11,    C_11,   B_11},
   {0, A_12,    C_12,   B_12},
   {0, A_13,    C_13,   B_13},
   {0, A_15,    C_15,   B_15},
   {0, A_16,    C_16,   B_16},

   {1, D_16,    F_16,   E_16},
   {1, D_14,    F_14,   E_14},
   {1, D_13,    F_13,   E_13},
   {1, D_12,    F_12,   E_12},
   {1, D_11,    F_11,   E_11},
   {1, D_10,    F_10,   E_10},
   {1, D_9,     F_9,    E_9},
   {1, D_8,     F_8,    E_8},
   {1, D_7,     F_7,    E_7},
   {1, D_6,     F_6,    E_6},
   {1, D_5,     F_5,    E_5},
   {1, D_4,     F_4,    E_4},
   {1, D_3,     F_3,    E_3},
   {1, D_2,     F_2,    E_2},

   {1, A_16,    C_16,   B_16},
   {1, A_15,    C_15,   B_15},
   {1, A_13,    C_13,   B_13},
   {1, A_11,    C_11,   B_11},
   {1, A_10,    C_10,   B_10},
   {1, A_9,     C_9,    B_9},
   {1, A_7,     C_7,    B_7},
   {1, A_5,     C_5,    B_5},
   {1, A_3,     C_3,    B_3},
   {1, A_2,     C_2,    B_2},
   {1, A_1,     C_1,    B_1},
};
#define __ NO_LED

led_config_t g_led_config = {
     {
        // Key Matrix to LED Index
        {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, __,  13, __, 14},
        { 15, 16, 17, 18, 19, 20, __, 21, 22, 23, 24, 25, 26, 27,  28, __, 29},
        { 30, 31, 32, 33, 34, 35, __, 36, 37, 38, 39, 40, 41, __,  42, __, 43},
        { 44, __, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56,  __, 57, __},
        { 58, 59, __, 60, __, 61, 62, 63, __, 64, __, 65, __, __,  66, 67, 68},
    },
    {
        // LED Index to Physical Position
        {7,1},  {20,1},  {33,0},  {48,3},  {61,6},  {74,8 }, {87,11},  {106,11}, {119,8},  {132,6},  {145,3},  {160,0},  {173,1},            {193,1},            {220,0},
        {7,14}, {24,14}, {39,14}, {52,17}, {65,20}, {78,22},           {103,25}, {116,22}, {129,20}, {142,17}, {155,14}, {170,14}, {183,14}, {200,14},           {222,16},
        {6,27}, {24,27}, {39,28}, {52,30}, {65,33}, {78,36},           {109,37}, {122,34}, {135,32}, {148,29}, {162,27}, {176,27},           {197,27},           {224,29},
        {7,40},          {28,40}, {43,42}, {56,44}, {69,47}, {82,50},  {102,52}, {115,49}, {128,46}, {141,44}, {154,41}, {169,40}, {187,40},           {209,43},
        {0,53}, {17,53},          {42,55},          {65,60}, {86,64},  {107,64},           {131,59},           {156,54},                     {196,56}, {209,56}, {222,56},
    },
    {
        // RGB LED Index to Flag
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,    1,
        1, 4, 4, 4, 4, 4, 4,    4, 4, 4, 4, 4, 4, 4,    1,
        8, 4, 4, 4, 4, 4,    4, 4, 4, 4, 4, 4,    1,    1,
        1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    1,
        1, 1,    1,    4,    1, 1, 4,    1,       1, 1, 1,
    }
};
#endif
