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

// clang-format off

#ifdef RGB_MATRIX_ENABLE

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
    {0, CB9_CA15,   CB7_CA15,   CB8_CA15},
    {0, CB9_CA16,   CB7_CA16,   CB8_CA16},
    {0, CB12_CA5,    CB10_CA5,    CB11_CA5},
    {0, CB12_CA6,    CB10_CA6,    CB11_CA6},
    {0, CB12_CA7,    CB10_CA7,    CB11_CA7},
    {0, CB12_CA8,    CB10_CA8,    CB11_CA8},
    {0, CB12_CA4,    CB10_CA4,    CB11_CA4},

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
    {0, CB12_CA9,    CB10_CA9,    CB11_CA9},
    {0, CB12_CA10,   CB10_CA10,   CB11_CA10},
    {0, CB12_CA11,   CB10_CA11,   CB11_CA11},
    {0, CB12_CA12,   CB10_CA12,   CB11_CA12},
    {0, CB12_CA13,   CB10_CA13,   CB11_CA13},

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
    {0, CB12_CA14,   CB10_CA14,   CB11_CA14},
    {0, CB12_CA15,   CB10_CA15,   CB11_CA15},
    {0, CB12_CA16,   CB10_CA16,   CB11_CA16},
    {1, CB12_CA1,    CB10_CA1,    CB11_CA1},

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
    {1, CB12_CA3,    CB10_CA3,    CB11_CA3},
    {1, CB12_CA4,    CB10_CA4,    CB11_CA4},
    {1, CB12_CA5,    CB10_CA5,    CB11_CA5},
    {1, CB12_CA2,    CB10_CA2,    CB11_CA2},

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
    {1, CB9_CA1,    CB7_CA1,    CB8_CA1},
    {1, CB12_CA6,    CB10_CA6,    CB11_CA6},
    {1, CB12_CA7,    CB10_CA7,    CB11_CA7},
    {1, CB12_CA8,    CB10_CA8,    CB11_CA8},

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
    {1, CB12_CA10,   CB10_CA10,   CB11_CA10},
    {1, CB12_CA11,   CB10_CA11,   CB11_CA11},
    {1, CB12_CA12,   CB10_CA12,   CB11_CA12},
    {1, CB12_CA9,    CB10_CA9,    CB11_CA9},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11,  12,  __,  13,  14,  15,  39,  40,  16 },
        { 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,  32,  33,  34,  35,  36,  37,  38,  17 },
        { 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,  53,  73,  54,  55,  56,  57,  58,  18 },
        { 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71,  __,  72,  59,  77,  76,  74,  75,  19 },
        { 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,  __,  90,  94,  91,  108, 92,  93,  __ },
        { 95, 96, 97, __, __, __, 98, __, __, __, 99, 100, 101, 102, 103, 104, 105, 106, 107, __ },
    },
    {
        // LED Index to Physical Position
        {0,0},  {13,0},  {24,0},  {34,0},  {45,0},  {57,0},  {68,0},  {78,0},  {89,0},  {102,0},  {112,0},  {123,0},  {133,0},            {159,0},  {169,0},  {180,0},  {193,0},  {203,0},  {214,0},  {224,0},
        {0,15}, {10,15}, {21,15}, {31,15}, {42,15}, {52,15}, {63,15}, {73,15}, {83,15}, {94,15},  {104,15}, {115,15}, {125,15}, {141,15}, {159,15}, {169,15}, {180,15}, {193,15}, {203,15}, {214,15}, {224,15},
        {3,27}, {16,27}, {26,27}, {36,27}, {47,27}, {57,27}, {68,27}, {78,27}, {89,27}, {99,27},  {109,27}, {120,27}, {130,27}, {159,27},           {169,27}, {180,27}, {193,27}, {203,27}, {214,27},
        {4,40}, {18,40}, {29,40}, {39,40}, {50,40}, {60,40}, {70,40}, {81,40}, {91,40}, {102,40}, {112,40}, {123,40}, {133,40}, {147,36},                               {193,40}, {203,40}, {214,40}, {224,34},
        {1,52}, {13,52}, {23,52}, {34,52}, {44,52}, {55,52}, {65,52}, {76,52}, {86,52}, {96,52},  {107,52}, {117,52},           {137,52},           {169,52},           {193,52}, {203,52}, {214,52},
        {1,64}, {14,64}, {27,64},                            {66,64},                             {105,64}, {118,64}, {131,64}, {145,64}, {159,64}, {169,64}, {180,64}, {198,64},           {214,64}, {224,58},
    },
    {
        // RGB LED Index to Flag
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1, 1, 1, 1, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 8, 4, 4, 4,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1, 1, 1, 4, 4, 4,
        8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,          4, 4, 4, 4,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,    1,    4, 4, 4,
        1, 1, 1,          4,          1, 1, 1, 1, 1, 1, 1, 1,    4, 1,
    }
};

#endif // RGB_MATRIX_ENABLE
