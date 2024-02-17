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
    {0, F_1},  // esc
    {0, F_2},  // f1
    {0, F_3},  // f2
    {0, F_4},  // f3
    {0, F_5},  // f4
    {0, F_6},  // f4
    {0, F_7},  // f6
    {0, F_8},  // f7
    {0, F_9},  // f8
    {0, F_10}, // f9
    {0, F_11}, // f10
    {0, F_12}, // f11
    {0, F_13}, // f12
    {0, F_14}, // print
    {0, F_15}, // del
    {0, F_16}, // light

    {0, E_1},  // ~
    {0, E_2},  // 1!
    {0, E_3},  // 2@
    {0, E_4},  // 3#
    {0, E_5},  // 4$
    {0, E_6},  // 5%
    {0, E_7},  // 6^
    {0, E_8},  // 7&
    {0, E_9},  // 8*
    {0, E_10}, // 9(
    {0, E_11}, // 0)
    {0, E_12}, // -_
    {0, E_13}, // =+
    {0, E_14}, // back space
    {0, E_16}, // page up

    {0, D_1},  // tab
    {0, D_2},  // q
    {0, D_3},  // w
    {0, D_4},  // e
    {0, D_5},  // r
    {0, D_6},  // t
    {0, D_7},  // y
    {0, D_8},  // u
    {0, D_9},  // i
    {0, D_10}, // o
    {0, D_11}, // p
    {0, D_12}, // [{
    {0, D_13}, // ]}
    {0, D_14}, // |
    {0, D_16}, // page down

    {0, C_1},  // caps lock
    {0, C_2},  // a
    {0, C_3},  // s
    {0, C_4},  // d
    {0, C_5},  // f
    {0, C_6},  // g
    {0, C_7},  // h
    {0, C_8},  // j
    {0, C_9},  // k
    {0, C_10}, // l
    {0, C_11}, // ;:
    {0, C_12}, // '"
    {0, C_14}, // enter
    {0, C_16}, // home

    {0, B_1},  // left shift
    {0, B_3},  // z
    {0, B_4},  // x
    {0, B_5},  // c
    {0, B_6},  // v
    {0, B_7},  // b
    {0, B_8},  // b
    {0, B_9},  // n
    {0, B_10}, // m
    {0, B_11}, // ,<
    {0, B_12}, // .>
    {0, B_13}, // right shift
    {0, B_14}, // up
    {0, B_16}, // end

    {0, A_1},  // left
    {0, A_2},  // left command
    {0, A_3},  // left optin
    {0, A_7},  // space
    {0, A_10}, // right command
    {0, A_11}, // fn
    {0, A_12}, // right ctrl
    {0, A_13}, // left
    {0, A_14}, // down
    {0, A_16}, // right
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 15 },
        { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 },
        { 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45 },
        { 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 14, 58, 59 },
        { 60, __, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73 },
        { 74, 75, 76, __, __, __, 77, __, __, 78, 79, 80, 81, 82, 83 }
    },
    {
        // LED Index to Physical Position
        {0,0},  {15,0},  {30,0},  {45,0},  {60,0},  {75,0},  {90,0},   {105,0},  {119,0},  {134,0},  {149,0},  {164,0},  {179,0},  {194,0},  {209,0},  {224,0},
        {0,13}, {15,13}, {30,13}, {45,13}, {60,13}, {75,13}, {90,13},  {105,13}, {119,13}, {134,13}, {149,13}, {164,13}, {179,13}, {202,13},           {224,13},
        {4,26}, {22,26}, {37,26}, {52,26}, {67,26}, {82,26}, {97,26},  {112,26}, {127,26}, {142,26}, {157,26}, {172,26}, {187,26}, {205,26},           {224,26},
        {6,38}, {26,38}, {41,38}, {56,38}, {71,38}, {86,38}, {101,38}, {116,38}, {131,38}, {146,38}, {160,38}, {175,38},           {200,38},           {224,38},
        {9,51},          {34,51}, {48,51}, {63,51}, {78,51}, {93,51},  {108,51}, {123,51}, {138,51}, {153,51}, {168,51},           {189,51}, {209,51}, {224,51},
        {2,64}, {21,64}, {39,64},                            {95,64},                                {149,64}, {164,64}, {179,64}, {194,64}, {209,64}, {224,64}
    },
    {
        // RGB LED Index to Flag
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,    1,
        1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1, 1, 1,
        1, 1, 1,          4,          1, 1, 1, 1, 1, 1,
    }
};

#endif // RGB_MATRIX_ENABLE
