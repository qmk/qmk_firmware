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
    {0, CB9_CA1,  CB7_CA1,  CB8_CA1},  // esc
    {0, CB9_CA2,  CB7_CA2,  CB8_CA2},  // f1
    {0, CB9_CA3,  CB7_CA3,  CB8_CA3},  // f2
    {0, CB9_CA4,  CB7_CA4,  CB8_CA4},  // f3
    {0, CB9_CA5,  CB7_CA5,  CB8_CA5},  // f4
    {0, CB9_CA6,  CB7_CA6,  CB8_CA6},  // f4
    {0, CB9_CA7,  CB7_CA7,  CB8_CA7},  // f6
    {0, CB9_CA8,  CB7_CA8,  CB8_CA8},  // f7
    {0, CB9_CA9,  CB7_CA9,  CB8_CA9},  // f8
    {0, CB9_CA10, CB7_CA10, CB8_CA10}, // f9
    {0, CB9_CA11, CB7_CA11, CB8_CA11}, // f10
    {0, CB9_CA12, CB7_CA12, CB8_CA12}, // f11
    {0, CB9_CA13, CB7_CA13, CB8_CA13}, // f12
    {0, CB9_CA14, CB7_CA14, CB8_CA14}, // print
    {0, CB9_CA15, CB7_CA15, CB8_CA15}, // del
    {0, CB9_CA16, CB7_CA16, CB8_CA16}, // light

    {0, CB6_CA1,  CB4_CA1,  CB5_CA1},  // ~
    {0, CB6_CA2,  CB4_CA2,  CB5_CA2},  // 1!
    {0, CB6_CA3,  CB4_CA3,  CB5_CA3},  // 2@
    {0, CB6_CA4,  CB4_CA4,  CB5_CA4},  // 3#
    {0, CB6_CA5,  CB4_CA5,  CB5_CA5},  // 4$
    {0, CB6_CA6,  CB4_CA6,  CB5_CA6},  // 5%
    {0, CB6_CA7,  CB4_CA7,  CB5_CA7},  // 6^
    {0, CB6_CA8,  CB4_CA8,  CB5_CA8},  // 7&
    {0, CB6_CA9,  CB4_CA9,  CB5_CA9},  // 8*
    {0, CB6_CA10, CB4_CA10, CB5_CA10}, // 9(
    {0, CB6_CA11, CB4_CA11, CB5_CA11}, // 0)
    {0, CB6_CA12, CB4_CA12, CB5_CA12}, // -_
    {0, CB6_CA13, CB4_CA13, CB5_CA13}, // =+
    {0, CB6_CA14, CB4_CA14, CB5_CA14}, // back space
    {0, CB6_CA16, CB4_CA16, CB5_CA16}, // page up

    {0, CB3_CA1,  CB1_CA1,  CB2_CA1},  // tab
    {0, CB3_CA2,  CB1_CA2,  CB2_CA2},  // q
    {0, CB3_CA3,  CB1_CA3,  CB2_CA3},  // w
    {0, CB3_CA4,  CB1_CA4,  CB2_CA4},  // e
    {0, CB3_CA5,  CB1_CA5,  CB2_CA5},  // r
    {0, CB3_CA6,  CB1_CA6,  CB2_CA6},  // t
    {0, CB3_CA7,  CB1_CA7,  CB2_CA7},  // y
    {0, CB3_CA8,  CB1_CA8,  CB2_CA8},  // u
    {0, CB3_CA9,  CB1_CA9,  CB2_CA9},  // i
    {0, CB3_CA10, CB1_CA10, CB2_CA10}, // o
    {0, CB3_CA11, CB1_CA11, CB2_CA11}, // p
    {0, CB3_CA12, CB1_CA12, CB2_CA12}, // [{
    {0, CB3_CA13, CB1_CA13, CB2_CA13}, // ]}
    {0, CB3_CA14, CB1_CA14, CB2_CA14}, // |
    {0, CB3_CA16, CB1_CA16, CB2_CA16}, // page down

    {1, CB9_CA1,  CB7_CA1,  CB8_CA1},  // caps lock
    {1, CB9_CA2,  CB7_CA2,  CB8_CA2},  // a
    {1, CB9_CA3,  CB7_CA3,  CB8_CA3},  // s
    {1, CB9_CA4,  CB7_CA4,  CB8_CA4},  // d
    {1, CB9_CA5,  CB7_CA5,  CB8_CA5},  // f
    {1, CB9_CA6,  CB7_CA6,  CB8_CA6},  // g
    {1, CB9_CA7,  CB7_CA7,  CB8_CA7},  // h
    {1, CB9_CA8,  CB7_CA8,  CB8_CA8},  // j
    {1, CB9_CA9,  CB7_CA9,  CB8_CA9},  // k
    {1, CB9_CA10, CB7_CA10, CB8_CA10}, // l
    {1, CB9_CA11, CB7_CA11, CB8_CA11}, // ;:
    {1, CB9_CA12, CB7_CA12, CB8_CA12}, // '"
    {1, CB9_CA14, CB7_CA14, CB8_CA14}, // enter
    {1, CB9_CA16, CB7_CA16, CB8_CA16}, // home

    {1, CB3_CA1,  CB1_CA1,  CB2_CA1},  // left shift
    {1, CB3_CA3,  CB1_CA3,  CB2_CA3},  // z
    {1, CB3_CA4,  CB1_CA4,  CB2_CA4},  // x
    {1, CB3_CA5,  CB1_CA5,  CB2_CA5},  // c
    {1, CB3_CA6,  CB1_CA6,  CB2_CA6},  // v
    {1, CB3_CA7,  CB1_CA7,  CB2_CA7},  // b
    {1, CB3_CA8,  CB1_CA8,  CB2_CA8},  // b
    {1, CB3_CA9,  CB1_CA9,  CB2_CA9},  // n
    {1, CB3_CA10, CB1_CA10, CB2_CA10}, // m
    {1, CB3_CA11, CB1_CA11, CB2_CA11}, // ,<
    {1, CB3_CA12, CB1_CA12, CB2_CA12}, // .>
    {1, CB3_CA13, CB1_CA13, CB2_CA13}, // right shift
    {1, CB3_CA14, CB1_CA14, CB2_CA14}, // up
    {1, CB3_CA16, CB1_CA16, CB2_CA16}, // end

    {1, CB6_CA1,  CB4_CA1,  CB5_CA1},  // left
    {1, CB6_CA2,  CB4_CA2,  CB5_CA2},  // left command
    {1, CB6_CA3,  CB4_CA3,  CB5_CA3},  // left optin
    {1, CB6_CA7,  CB4_CA7,  CB5_CA7},  // space
    {1, CB6_CA10, CB4_CA10, CB5_CA10}, // right command
    {1, CB6_CA11, CB4_CA11, CB5_CA11}, // fn
    {1, CB6_CA12, CB4_CA12, CB5_CA12}, // right ctrl
    {1, CB6_CA13, CB4_CA13, CB5_CA13}, // left
    {1, CB6_CA14, CB4_CA14, CB5_CA14}, // down
    {1, CB6_CA16, CB4_CA16, CB5_CA16}, // right
};
#endif // RGB_MATRIX_ENABLE
