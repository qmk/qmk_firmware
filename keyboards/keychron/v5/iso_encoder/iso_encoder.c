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

const snled27351_led_t PROGMEM g_snled27351_leds[SNLED27351_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, CB9_CA1,    CB7_CA1,    CB8_CA1},
    {0, CB9_CA3,    CB7_CA3,    CB8_CA3},
    {0, CB9_CA4,    CB7_CA4,    CB8_CA4},
    {0, CB9_CA5,    CB7_CA5,    CB8_CA5},
    {0, CB9_CA6,    CB7_CA6,    CB8_CA6},
    {0, CB9_CA8,    CB7_CA8,    CB8_CA8},
    {0, CB9_CA9,    CB7_CA9,    CB8_CA9},
    {0, CB9_CA10,   CB7_CA10,   CB8_CA10},
    {0, CB9_CA11,   CB7_CA11,   CB8_CA11},
    {0, CB9_CA12,   CB7_CA12,   CB8_CA12},
    {0, CB9_CA13,   CB7_CA13,   CB8_CA13},
    {0, CB9_CA14,   CB7_CA14,   CB8_CA14},
    {0, CB9_CA15,   CB7_CA15,   CB8_CA15},
    {0, CB9_CA16,   CB7_CA16,   CB8_CA16},
    {0, CB12_CA12,   CB10_CA12,   CB11_CA12},
    {0, CB12_CA13,   CB10_CA13,   CB11_CA13},
    {0, CB12_CA14,   CB10_CA14,   CB11_CA14},

    {0, CB3_CA1,    CB1_CA1,    CB2_CA1},  // `~
    {0, CB3_CA2,    CB1_CA2,    CB2_CA2},  // 1!
    {0, CB3_CA3,    CB1_CA3,    CB2_CA3},  // 2@
    {0, CB3_CA4,    CB1_CA4,    CB2_CA4},  // 3#
    {0, CB3_CA5,    CB1_CA5,    CB2_CA5},  // 4$
    {0, CB3_CA6,    CB1_CA6,    CB2_CA6},  // 5%
    {0, CB3_CA7,    CB1_CA7,    CB2_CA7},  // 6^
    {0, CB3_CA8,    CB1_CA8,    CB2_CA8},  // 7&
    {0, CB3_CA9,    CB1_CA9,    CB2_CA9},  // 8*
    {0, CB3_CA10,   CB1_CA10,   CB2_CA10}, // 9(
    {0, CB3_CA11,   CB1_CA11,   CB2_CA11}, // 0)
    {0, CB3_CA12,   CB1_CA12,   CB2_CA12}, // -_
    {0, CB3_CA13,   CB1_CA13,   CB2_CA13}, // =+
    {0, CB3_CA14,   CB1_CA14,   CB2_CA14}, // BackSpace
    {0, CB3_CA16,   CB1_CA16,   CB2_CA16}, // Numlock
    {0, CB12_CA9,    CB10_CA9,    CB11_CA9},  // /
    {0, CB12_CA10,   CB10_CA10,   CB11_CA10}, // *
    {0, CB12_CA11,   CB10_CA11,   CB11_CA11}, // -

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
    {0, CB6_CA16,   CB4_CA16,   CB5_CA16},
    {0, CB12_CA15,   CB10_CA15,   CB11_CA15},

    {1, CB3_CA16,   CB1_CA16,   CB2_CA16},
    {1, CB3_CA15,   CB1_CA15,   CB2_CA15},
    {1, CB3_CA14,   CB1_CA14,   CB2_CA14},
    {1, CB3_CA13,   CB1_CA13,   CB2_CA13},
    {1, CB3_CA12,   CB1_CA12,   CB2_CA12},
    {1, CB3_CA11,   CB1_CA11,   CB2_CA11},
    {1, CB3_CA10,   CB1_CA10,   CB2_CA10},
    {1, CB3_CA9,    CB1_CA9,    CB2_CA9},
    {1, CB3_CA8,    CB1_CA8,    CB2_CA8},
    {1, CB3_CA7,    CB1_CA7,    CB2_CA7},
    {1, CB3_CA6,    CB1_CA6,    CB2_CA6},
    {1, CB3_CA5,    CB1_CA5,    CB2_CA5},
    {1, CB3_CA3,    CB1_CA3,    CB2_CA3},
    {0, CB6_CA14,   CB4_CA14,   CB5_CA14},
    {1, CB3_CA1,    CB1_CA1,    CB2_CA1},
    {1, CB12_CA3,    CB10_CA3,    CB11_CA3},
    {1, CB12_CA4,    CB10_CA4,    CB11_CA4},
    {0, CB12_CA16,   CB10_CA16,   CB11_CA16},

    {1, CB9_CA16,   CB7_CA16,   CB8_CA16},
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
    {1, CB9_CA3,    CB7_CA3,    CB8_CA3},
    {1, CB9_CA2,    CB7_CA2,    CB8_CA2},
    {1, CB9_CA1,    CB7_CA1,    CB8_CA1},
    {1, CB12_CA5,    CB10_CA5,    CB11_CA5},
    {1, CB12_CA6,    CB10_CA6,    CB11_CA6},

    {1, CB6_CA16,   CB4_CA16,   CB5_CA16},
    {1, CB6_CA15,   CB4_CA15,   CB5_CA15},
    {1, CB6_CA14,   CB4_CA14,   CB5_CA14},
    {1, CB6_CA10,   CB4_CA10,   CB5_CA10},
    {1, CB6_CA6,    CB4_CA6,    CB5_CA6},
    {1, CB6_CA5,    CB4_CA5,    CB5_CA5},
    {1, CB6_CA4,    CB4_CA4,    CB5_CA4},
    {1, CB6_CA3,    CB4_CA3,    CB5_CA3},
    {1, CB6_CA2,    CB4_CA2,    CB5_CA2},
    {1, CB6_CA1,    CB4_CA1,    CB5_CA1},
    {1, CB12_CA1,    CB10_CA1,    CB11_CA1},
    {1, CB12_CA2,    CB10_CA2,    CB11_CA2},
    {1, CB12_CA7,    CB10_CA7,    CB11_CA7}
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {  0, __,  1,  2,  3,  4, __,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 },
        { 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, __, 31, 32, 33 },
        { 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 64, 68, 48, 49, 50 },
        { 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 16, 63, 34, 65, 66, 67 },
        { 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, __, 81, 82, 83, 84, 85 },
        { 86, 87, 88, __, __, 98, 89, __, __, __, 90, 91, 92, 93, 94, 95, 96, 97 },
    },
    {
        // LED Index to Physical Position
        {0,0},           {24,0},  {36,0},  {48,0},  {60,0},  {78,0},  {90,0},  {103,0},  {115,0},  {133,0},  {145,0},  {157,0},  {169,0},            {184,0},  {196,0},  {208,0},  {224,0},
        {0,15}, {12,15}, {24,15}, {36,15}, {48,15}, {60,15}, {72,15}, {85,15}, {97,15},  {109,15}, {121,15}, {133,15}, {145,15}, {163,15},           {188,15}, {200,15}, {212,15}, {224,15},
        {3,26}, {18,26}, {30,26}, {42,26}, {54,26}, {66,26}, {78,26}, {91,26}, {103,26}, {115,26}, {127,26}, {139,26}, {151,26},                     {188,26}, {200,26}, {212,26},
        {5,38}, {21,38}, {33,38}, {45,38}, {57,38}, {69,38}, {81,38}, {94,38}, {106,38}, {118,38}, {130,38}, {142,38}, {154,38}, {170,34},           {188,38}, {200,38}, {212,38}, {224,32},
        {3,49}, {15,49}, {27,49}, {39,49}, {51,49}, {63,49}, {75,49}, {88,49}, {100,49}, {112,49}, {124,49}, {136,49}, {152,49},           {172,52}, {188,49}, {200,49}, {212,49},
        {1,61}, {17,61}, {32,61},                            {77,61},                              {121,61}, {133,61}, {145,61}, {160,64}, {172,64}, {184,64}, {200,61}, {212,61}, {224,55},
    },
    {
        // RGB LED Index to Flag
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    8, 4, 4, 4,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,       4, 4, 4,
        8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    4, 4, 4, 4,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1, 1, 4, 4, 4,
        1, 1, 1,          4,          1, 1, 1, 1, 1, 1, 4, 4, 1,
    }
};

#endif // RGB_MATRIX_ENABLE
