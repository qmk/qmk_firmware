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

const ckled2001_led PROGMEM g_ckled2001_leds[LED_MATRIX_LED_COUNT] = {
/* Refer to CKLED2001 manual for these locations
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

#endif // RGB_MATRIX_ENABLE
