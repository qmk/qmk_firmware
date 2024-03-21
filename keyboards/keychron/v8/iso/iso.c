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

// clang-format off

const snled27351_led_t PROGMEM g_snled27351_leds[SNLED27351_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, CB9_CA1,    CB7_CA1,    CB8_CA1},
    {0, CB9_CA2,    CB7_CA2,    CB8_CA2},
    {0, CB9_CA3,    CB7_CA3,    CB8_CA3},
    {0, CB9_CA4,    CB7_CA4,    CB8_CA4},
    {0, CB9_CA5,    CB7_CA5,    CB8_CA5},
    {0, CB9_CA6,    CB7_CA6,    CB8_CA6},
    {0, CB9_CA7,    CB7_CA7,    CB8_CA7},
    {0, CB9_CA8,    CB7_CA8,    CB8_CA8},
    {0, CB9_CA9,    CB7_CA9,    CB8_CA9},
    {0, CB9_CA10,   CB7_CA10,   CB8_CA10},
    {0, CB9_CA11,   CB7_CA11,   CB8_CA11},
    {0, CB9_CA12,   CB7_CA12,   CB8_CA12},
    {0, CB9_CA13,   CB7_CA13,   CB8_CA13},
    {0, CB9_CA14,   CB7_CA14,   CB8_CA14},
    {0, CB9_CA15,   CB7_CA15,   CB8_CA15},

    {0, CB6_CA1,    CB4_CA1,    CB5_CA1},
    {0, CB6_CA2,    CB4_CA2,    CB5_CA2},
    {0, CB6_CA3,    CB4_CA3,    CB5_CA3},
    {0, CB6_CA4,    CB4_CA4,    CB5_CA4},
    {0, CB6_CA5,    CB4_CA5,    CB5_CA5},
    {0, CB6_CA6,    CB4_CA6,    CB5_CA6},
    {0, CB6_CA7,    CB4_CA7,    CB5_CA7},
    {0, CB6_CA8,    CB4_CA8,    CB5_CA8},
    {0, CB6_CA9,    CB4_CA9,    CB5_CA9},
    {0, CB6_CA10,   CB4_CA10,   CB5_CA10},
    {0, CB6_CA11,   CB4_CA11,   CB5_CA11},
    {0, CB6_CA12,   CB4_CA12,   CB5_CA12},
    {0, CB6_CA13,   CB4_CA13,   CB5_CA13},
    {0, CB6_CA15,   CB4_CA15,   CB5_CA15},

    {0, CB3_CA1,    CB1_CA1,    CB2_CA1},
    {0, CB3_CA2,    CB1_CA2,    CB2_CA2},
    {0, CB3_CA3,    CB1_CA3,    CB2_CA3},
    {0, CB3_CA4,    CB1_CA4,    CB2_CA4},
    {0, CB3_CA5,    CB1_CA5,    CB2_CA5},
    {1, CB3_CA10,   CB1_CA10,   CB2_CA10},
    {1, CB3_CA8,    CB1_CA8,    CB2_CA8},
    {1, CB3_CA7,    CB1_CA7,    CB2_CA7},
    {1, CB3_CA6,    CB1_CA6,    CB2_CA6},
    {1, CB3_CA5,    CB1_CA5,    CB2_CA5},
    {1, CB3_CA4,    CB1_CA4,    CB2_CA4},
    {1, CB3_CA3,    CB1_CA3,    CB2_CA3},
    {1, CB3_CA2,    CB1_CA2,    CB2_CA2},
    {0, CB6_CA14,   CB4_CA14,   CB5_CA14},
    {1, CB3_CA1,    CB1_CA1,    CB2_CA1},

    {1, CB9_CA15,   CB7_CA15,   CB8_CA15},
    {1, CB9_CA14,   CB7_CA14,   CB8_CA14},
    {1, CB9_CA13,   CB7_CA13,   CB8_CA13},
    {1, CB9_CA12,   CB7_CA12,   CB8_CA12},
    {1, CB9_CA11,   CB7_CA11,   CB8_CA11},
    {1, CB9_CA10,   CB7_CA10,   CB8_CA10},
    {1, CB9_CA9,    CB7_CA9,    CB8_CA9},
    {1, CB9_CA8,    CB7_CA8,    CB8_CA8},
    {1, CB9_CA7,    CB7_CA7,    CB8_CA7},
    {1, CB9_CA6,    CB7_CA6,    CB8_CA6},
    {1, CB9_CA5,    CB7_CA5,    CB8_CA5},
    {1, CB9_CA4,    CB7_CA4,    CB8_CA4},
    {1, CB9_CA3,    CB7_CA3,    CB8_CA3},
    {1, CB9_CA2,    CB7_CA2,    CB8_CA2},
    {1, CB9_CA1,    CB7_CA1,    CB8_CA1},

    {1, CB6_CA15,   CB4_CA15,   CB5_CA15},
    {1, CB6_CA14,   CB4_CA14,   CB5_CA14},
    {1, CB6_CA13,   CB4_CA13,   CB5_CA13},
    {1, CB6_CA12,   CB4_CA12,   CB5_CA12},
    {1, CB6_CA9,    CB4_CA9,    CB5_CA9},
    {1, CB6_CA8,    CB4_CA8,    CB5_CA8},
    {1, CB6_CA7,    CB4_CA7,    CB5_CA7},
    {1, CB6_CA6,    CB4_CA6,    CB5_CA6},
    {1, CB6_CA3,    CB4_CA3,    CB5_CA3},
    {1, CB6_CA2,    CB4_CA2,    CB5_CA2},
    {1, CB6_CA1,    CB4_CA1,    CB5_CA1}
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
