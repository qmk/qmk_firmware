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

#ifdef RGB_MATRIX_ENABLE
const snled27351_led_t PROGMEM g_snled27351_leds[SNLED27351_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    // {0, CB9_CA1,    CB7_CA1,    CB8_CA1}
    {0, CB9_CA2,    CB7_CA2,    CB8_CA2},  // F13
    {0, CB9_CA3,    CB7_CA3,    CB8_CA3},  // F14
    {0, CB9_CA4,    CB7_CA4,    CB8_CA4},  // F15
    {0, CB9_CA5,    CB7_CA5,    CB8_CA5},  // Esc
    {0, CB9_CA6,    CB7_CA6,    CB8_CA6},  // F1
    {0, CB9_CA7,    CB7_CA7,    CB8_CA7},  // F2
    {0, CB9_CA8,    CB7_CA8,    CB8_CA8},  // F3
    {0, CB9_CA9,    CB7_CA9,    CB8_CA9},  // F4
    {0, CB9_CA10,   CB7_CA10,   CB8_CA10}, // F5
    {0, CB9_CA11,   CB7_CA11,   CB8_CA11}, // F6
    {0, CB9_CA12,   CB7_CA12,   CB8_CA12}, // F7
    {0, CB9_CA13,   CB7_CA13,   CB8_CA13}, // F8
    {0, CB9_CA14,   CB7_CA14,   CB8_CA14}, // F9
    {0, CB9_CA15,   CB7_CA15,   CB8_CA15}, // F10
    {0, CB9_CA16,   CB7_CA16,   CB8_CA16}, // F11
    {0, CB12_CA16,   CB10_CA16,   CB11_CA16}, // F12
    {0, CB12_CA15,   CB10_CA15,   CB11_CA15}, // DEL
    {0, CB12_CA14,   CB10_CA14,   CB11_CA14}, // Light


    {0, CB3_CA1,    CB1_CA1,    CB2_CA1},  // num_lock
    {0, CB3_CA2,    CB1_CA2,    CB2_CA2},  // /
    {0, CB3_CA3,    CB1_CA3,    CB2_CA3},  // *
    {0, CB3_CA4,    CB1_CA4,    CB2_CA4},  // -
    {0, CB3_CA5,    CB1_CA5,    CB2_CA5},  // ~`
    {0, CB3_CA6,    CB1_CA6,    CB2_CA6},  // 1!
    {0, CB3_CA7,    CB1_CA7,    CB2_CA7},  // 2@
    {0, CB3_CA8,    CB1_CA8,    CB2_CA8},  // 3#
    {0, CB3_CA9,    CB1_CA9,    CB2_CA9},  // 4$
    {0, CB3_CA10,   CB1_CA10,   CB2_CA10}, // 5%
    {0, CB3_CA11,   CB1_CA11,   CB2_CA11}, // 6^
    {0, CB3_CA12,   CB1_CA12,   CB2_CA12}, // 7&
    {0, CB3_CA13,   CB1_CA13,   CB2_CA13}, // 8*
    {0, CB3_CA14,   CB1_CA14,   CB2_CA14}, // 9(
    {0, CB3_CA15,   CB1_CA15,   CB2_CA15}, // 0)
    {0, CB3_CA16,   CB1_CA16,   CB2_CA16}, // -_
    {0, CB12_CA13,   CB10_CA13,   CB11_CA13}, // =+
    {0, CB12_CA12,   CB10_CA12,   CB11_CA12}, // BackSpace
    {0, CB12_CA11,   CB10_CA11,   CB11_CA11}, // PgUp

    {0, CB6_CA1,    CB4_CA1,    CB5_CA1},  // 7
    {0, CB6_CA2,    CB4_CA2,    CB5_CA2},  // 8
    {0, CB6_CA3,    CB4_CA3,    CB5_CA3},  // 9
    {0, CB6_CA4,    CB4_CA4,    CB5_CA4},  // +
    {0, CB6_CA5,    CB4_CA5,    CB5_CA5},  // TAB
    {0, CB6_CA6,    CB4_CA6,    CB5_CA6},  // Q
    {0, CB6_CA7,    CB4_CA7,    CB5_CA7},  // W
    {0, CB6_CA8,    CB4_CA8,    CB5_CA8},  // E
    {0, CB6_CA9,    CB4_CA9,    CB5_CA9},  // R
    {0, CB6_CA10,   CB4_CA10,   CB5_CA10}, // T
    {0, CB6_CA11,   CB4_CA11,   CB5_CA11}, // Y
    {0, CB6_CA12,   CB4_CA12,   CB5_CA12}, // U
    {0, CB6_CA13,   CB4_CA13,   CB5_CA13}, // I
    {0, CB6_CA14,   CB4_CA14,   CB5_CA14}, // O
    {0, CB6_CA15,   CB4_CA15,   CB5_CA15}, // P
    {0, CB6_CA16,   CB4_CA16,   CB5_CA16}, // [
    {0, CB12_CA10,   CB10_CA10,   CB11_CA10}, // ]
    {0, CB12_CA9,    CB10_CA9,    CB11_CA9},  // \|
    {0, CB12_CA8,    CB10_CA8,    CB11_CA8},  // PgDn

    {1, CB3_CA16,   CB1_CA16,   CB2_CA16}, // 4
    {1, CB3_CA15,   CB1_CA15,   CB2_CA15}, // 5
    {1, CB3_CA14,   CB1_CA14,   CB2_CA14}, // 6
    // {0, CB6_CA4,    CB4_CA4,    CB5_CA4},  // +
    {1, CB3_CA12,   CB1_CA12,   CB2_CA12}, // CapsLock
    {1, CB3_CA11,   CB1_CA11,   CB2_CA11}, // A
    {1, CB3_CA10,   CB1_CA10,   CB2_CA10}, // S
    {1, CB3_CA9,    CB1_CA9,    CB2_CA9},  // D
    {1, CB3_CA8,    CB1_CA8,    CB2_CA8},  // F
    {1, CB3_CA7,    CB1_CA7,    CB2_CA7},  // G
    {1, CB3_CA6,    CB1_CA6,    CB2_CA6},  // H
    {1, CB3_CA5,    CB1_CA5,    CB2_CA5},  // J
    {1, CB3_CA4,    CB1_CA4,    CB2_CA4},  // k
    {1, CB3_CA3,    CB1_CA3,    CB2_CA3},  // l
    {1, CB3_CA2,    CB1_CA2,    CB2_CA2},  // ；
    {1, CB3_CA1,    CB1_CA1,    CB2_CA1},  // '
    {1, CB12_CA1,    CB10_CA1,    CB11_CA1},  // Enter
    {1, CB12_CA2,    CB10_CA2,    CB11_CA2},  // Home

    {1, CB9_CA16,   CB7_CA16,   CB8_CA16}, // 1
    {1, CB9_CA15,   CB7_CA15,   CB8_CA15}, // 2
    {1, CB9_CA14,   CB7_CA14,   CB8_CA14}, // 3
    {1, CB9_CA13,   CB7_CA13,   CB8_CA13}, // Enter
    {1, CB9_CA12,   CB7_CA12,   CB8_CA12}, //Shift_L
    {1, CB9_CA10,   CB7_CA10,   CB8_CA10}, // Z
    {1, CB9_CA9,    CB7_CA9,    CB8_CA9},  // X
    {1, CB9_CA8,    CB7_CA8,    CB8_CA8},  // C
    {1, CB9_CA7,    CB7_CA7,    CB8_CA7},  // V
    {1, CB9_CA6,    CB7_CA6,    CB8_CA6},  // B
    {1, CB9_CA5,    CB7_CA5,    CB8_CA5},  // N
    {1, CB9_CA4,    CB7_CA4,    CB8_CA4},  // M
    {1, CB9_CA3,    CB7_CA3,    CB8_CA3},  // ,
    {1, CB9_CA2,    CB7_CA2,    CB8_CA2},  // .
    {1, CB9_CA1,    CB7_CA1,    CB8_CA1},  // ?
    {1, CB12_CA3,    CB10_CA3,    CB11_CA3},  // Shift_R
    {1, CB12_CA4,    CB10_CA4,    CB11_CA4},  // Up

    {1, CB6_CA16,   CB4_CA16,   CB5_CA16}, // 0
    {1, CB6_CA14,   CB4_CA14,   CB5_CA14}, // .
    {1, CB6_CA12,   CB4_CA12,   CB5_CA12}, // Ctrl_L
    {1, CB6_CA11,   CB4_CA11,   CB5_CA11}, // Win_L
    {1, CB6_CA10,   CB4_CA10,   CB5_CA10}, // Alt_L
    {1, CB6_CA6,    CB4_CA6,    CB5_CA6},  // Space
    {1, CB6_CA3,    CB4_CA3,    CB5_CA3},  // Alt_R
    {1, CB6_CA2,    CB4_CA2,    CB5_CA2},  // Fn
    {1, CB6_CA1,    CB4_CA1,    CB5_CA1},  // Ctrl_R
    {1, CB12_CA5,    CB10_CA5,    CB11_CA5},  // Left
    {1, CB12_CA6,    CB10_CA6,    CB11_CA6},  // Down
    {1, CB12_CA7,    CB10_CA7,    CB11_CA7},  // Right
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,  16,  17, __,  0,  1 },
        { 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,  35,  36, 18, 19, 20 },
        { 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53,  54,  55, 37, 38, 39 },
        { 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 76,  71,  72, 56, 57, 58 },
        { 77, __, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, __,  88,  89, 73, 74, 75 },
        { 92, 93, 94, __, __, 21, 95, 40, __, 96, 97, 98, 99, 100, 101, 90,  2, 91 },
    },
    {
        // LED Index to Physical Position
                {11,0},  {23,0},  {34,0},  {49,0},  {63,0},  {75,0},  {86,0},  {98,0},   {112,0},  {123,0},  {135,0},  {146,0},  {161,0},  {172,0},  {184,0},  {195,0},  {209,0},            {224,0},
        {0,15}, {11,15}, {23,15}, {34,15}, {49,15}, {60,15}, {72,15}, {83,15}, {95,15},  {106,15}, {118,15}, {129,15}, {141,15}, {152,15}, {164,15}, {175,15}, {186,15}, {204,15},           {224,15},
        {0,26}, {11,26}, {23,26}, {34,32}, {52,26}, {66,26}, {78,26}, {89,26}, {101,26}, {112,26}, {123,26}, {135,26}, {146,26}, {158,26}, {169,26}, {181,26}, {192,26}, {207,26},           {224,26},
        {0,38}, {11,38}, {23,38},          {53,38}, {69,38}, {81,38}, {92,38}, {103,38}, {115,38}, {126,38}, {138,38}, {149,38}, {161,38}, {172,38}, {184,38},           {202,38},           {224,38},
        {0,49}, {11,49}, {23,49}, {34,55}, {56,49},          {75,49}, {86,49}, {98,49},  {109,49}, {121,49}, {132,49}, {144,49}, {155,49}, {166,49}, {178,49},           {194,49}, {213,52},
        {6,61},          {23,61},          {50,61}, {65,61}, {79,61},                              {122,61},                               {163,61}, {175,61}, {186,61}, {201,64}, {213,64}, {224,64},
    },
    {
        // RGB LED Index to Flag
           1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,
        8, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    1,
        4, 4, 4, 4,  1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,
        4, 4, 4,     8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,    1,
        4, 4, 4, 4,  1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1, 1,
        4,    4,     1, 1, 1,          4,          1, 4, 1, 1, 1, 1,
    }
};
#endif
