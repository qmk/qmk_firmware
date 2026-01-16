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

#ifdef LED_MATRIX_ENABLE

// clang-format off

const snled27351_led_t PROGMEM g_snled27351_leds[SNLED27351_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  LED address
 *   |  |   */
    {0, CB6_CA1},  // esc
    {0, CB6_CA2},  // f1
    {0, CB6_CA3},  // f2
    {0, CB6_CA4},  // f3
    {0, CB6_CA5},  // f4
    {0, CB6_CA6},  // f4
    {0, CB6_CA7},  // f6
    {0, CB6_CA8},  // f7
    {0, CB6_CA9},  // f8
    {0, CB6_CA10}, // f9
    {0, CB6_CA11}, // f10
    {0, CB6_CA12}, // f11
    {0, CB6_CA13}, // f12
    {0, CB6_CA14}, // print
    {0, CB6_CA15}, // del
    {0, CB6_CA16}, // light

    {0, CB5_CA1},  // ~
    {0, CB5_CA2},  // 1!
    {0, CB5_CA3},  // 2@
    {0, CB5_CA4},  // 3#
    {0, CB5_CA5},  // 4$
    {0, CB5_CA6},  // 5%
    {0, CB5_CA7},  // 6^
    {0, CB5_CA8},  // 7&
    {0, CB5_CA9},  // 8*
    {0, CB5_CA10}, // 9(
    {0, CB5_CA11}, // 0)
    {0, CB5_CA12}, // -_
    {0, CB5_CA13}, // =+
    {0, CB5_CA14}, // back space
    {0, CB5_CA16}, // page up

    {0, CB4_CA1},  // tab
    {0, CB4_CA2},  // q
    {0, CB4_CA3},  // w
    {0, CB4_CA4},  // e
    {0, CB4_CA5},  // r
    {0, CB4_CA6},  // t
    {0, CB4_CA7},  // y
    {0, CB4_CA8},  // u
    {0, CB4_CA9},  // i
    {0, CB4_CA10}, // o
    {0, CB4_CA11}, // p
    {0, CB4_CA12}, // [{
    {0, CB4_CA13}, // ]}
    {0, CB4_CA14}, // |
    {0, CB4_CA16}, // page down

    {0, CB3_CA1},  // caps lock
    {0, CB3_CA2},  // a
    {0, CB3_CA3},  // s
    {0, CB3_CA4},  // d
    {0, CB3_CA5},  // f
    {0, CB3_CA6},  // g
    {0, CB3_CA7},  // h
    {0, CB3_CA8},  // j
    {0, CB3_CA9},  // k
    {0, CB3_CA10}, // l
    {0, CB3_CA11}, // ;:
    {0, CB3_CA12}, // '"
    {0, CB3_CA14}, // enter
    {0, CB3_CA16}, // home

    {0, CB2_CA1},  // left shift
    {0, CB2_CA3},  // z
    {0, CB2_CA4},  // x
    {0, CB2_CA5},  // c
    {0, CB2_CA6},  // v
    {0, CB2_CA7},  // b
    {0, CB2_CA8},  // b
    {0, CB2_CA9},  // n
    {0, CB2_CA10}, // m
    {0, CB2_CA11}, // ,<
    {0, CB2_CA12}, // .>
    {0, CB2_CA13}, // right shift
    {0, CB2_CA14}, // up
    {0, CB2_CA16}, // end

    {0, CB1_CA1},  // left
    {0, CB1_CA2},  // left command
    {0, CB1_CA3},  // left optin
    {0, CB1_CA7},  // space
    {0, CB1_CA10}, // right command
    {0, CB1_CA11}, // fn
    {0, CB1_CA12}, // right ctrl
    {0, CB1_CA13}, // left
    {0, CB1_CA14}, // down
    {0, CB1_CA16}, // right
};
#endif
