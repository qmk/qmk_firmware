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

const snled27351_led_t PROGMEM g_snled27351_leds[SNLED27351_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, CB3_CA1,    CB1_CA1,    CB2_CA1},
    {0, CB3_CA2,    CB1_CA2,    CB2_CA2},
    {0, CB3_CA3,    CB1_CA3,    CB2_CA3},
    {0, CB3_CA4,    CB1_CA4,    CB2_CA4},
    {0, CB3_CA5,    CB1_CA5,    CB2_CA5},
    {0, CB3_CA6,    CB1_CA6,    CB2_CA6},
    {0, CB3_CA7,    CB1_CA7,    CB2_CA7},
    {0, CB3_CA8,    CB1_CA8,    CB2_CA8},
    {0, CB3_CA9,    CB1_CA9,    CB2_CA9},
    {0, CB3_CA10,   CB1_CA10,   CB2_CA10},
    {0, CB3_CA11,   CB1_CA11,   CB2_CA11},
    {0, CB3_CA12,   CB1_CA12,   CB2_CA12},
    {0, CB3_CA13,   CB1_CA13,   CB2_CA13},
    {0, CB3_CA14,   CB1_CA14,   CB2_CA14},
    {0, CB3_CA15,   CB1_CA15,   CB2_CA15},
    {0, CB3_CA16,   CB1_CA16,   CB2_CA16},

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
    {0, CB6_CA16,   CB4_CA16,   CB5_CA16},

    {0, CB9_CA1,    CB7_CA1,    CB8_CA1},
    {0, CB9_CA2,    CB7_CA2,    CB8_CA2},
    {0, CB9_CA3,    CB7_CA3,    CB8_CA3},
    {0, CB9_CA4,    CB7_CA4,    CB8_CA4},
    {1, CB9_CA5,    CB7_CA5,    CB8_CA5},
    {1, CB9_CA6,    CB7_CA6,    CB8_CA6},
    {1, CB9_CA7,    CB7_CA7,    CB8_CA7},
    {1, CB9_CA8,    CB7_CA8,    CB8_CA8},
    {1, CB9_CA9,    CB7_CA9,    CB8_CA9},
    {1, CB9_CA10,   CB7_CA10,   CB8_CA10},
    {1, CB9_CA11,   CB7_CA11,   CB8_CA11},
    {1, CB9_CA12,   CB7_CA12,   CB8_CA12},
    {1, CB9_CA14,   CB7_CA14,   CB8_CA14},
    {0, CB6_CA14,   CB4_CA14,   CB5_CA14},
    {1, CB9_CA16,   CB7_CA16,   CB8_CA16},

    {1, CB3_CA1,    CB1_CA1,    CB2_CA1},
    {1, CB3_CA3,    CB1_CA3,    CB2_CA3},
    {1, CB3_CA4,    CB1_CA4,    CB2_CA4},
    {1, CB3_CA5,    CB1_CA5,    CB2_CA5},
    {1, CB3_CA6,    CB1_CA6,    CB2_CA6},
    {1, CB3_CA7,    CB1_CA7,    CB2_CA7},
    {1, CB3_CA8,    CB1_CA8,    CB2_CA8},
    {1, CB3_CA9,    CB1_CA9,    CB2_CA9},
    {1, CB3_CA10,   CB1_CA10,   CB2_CA10},
    {1, CB3_CA11,   CB1_CA11,   CB2_CA11},
    {1, CB3_CA12,   CB1_CA12,   CB2_CA12},
    {1, CB3_CA13,   CB1_CA13,   CB2_CA13},
    {1, CB3_CA14,   CB1_CA14,   CB2_CA14},
    {1, CB3_CA15,   CB1_CA15,   CB2_CA15},

    {1, CB6_CA1,    CB4_CA1,    CB5_CA1},
    {1, CB6_CA2,    CB4_CA2,    CB5_CA2},
    {1, CB6_CA3,    CB4_CA3,    CB5_CA3},
    {1, CB6_CA4,    CB4_CA4,    CB5_CA4},
    {1, CB6_CA7,    CB4_CA7,    CB5_CA7},
    {1, CB6_CA10,   CB4_CA10,   CB5_CA10},
    {1, CB6_CA11,   CB4_CA11,   CB5_CA11},
    {1, CB6_CA12,   CB4_CA12,   CB5_CA12},
    {1, CB6_CA13,   CB4_CA13,   CB5_CA13},
    {1, CB6_CA14,   CB4_CA14,   CB5_CA14},
    {1, CB6_CA15,   CB4_CA15,   CB5_CA15},
    {1, CB6_CA16,   CB4_CA16,   CB5_CA16}
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
