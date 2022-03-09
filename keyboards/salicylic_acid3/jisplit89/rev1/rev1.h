/*
Copyright 2020 Salicylic_Acid

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "jisplit89.h"

#include "quantum.h"

/*
 * ,--------------------------------------   ----------------------------------------------------------.
 * | L00 |  L01 | L02 | L03 | L04 |  L05 |   | R00 | R01 | R02 |  R03  | R04 | R05 | R06 |  R07  | R60 |
 * |-------------------------------------- ------------------------------------------------------------+
 * | L10 | L11 | L12 | L13 | L14 | L15 |   | R10 | R11 | R12 | R13 | R14 | R15 | R16 | R17 | R61 | R62 |
 * |---------------------------------------------------------------------------------------------------+
 * |   L20  | L21 | L22 | L23 | L24 | L25 |   | R20 | R21 | R22 | R23 | R24 | R25 | R26 |   R27  | R63 |
 * |----------------------------------------  ---------------------------------------------------------+
 * |    L30   | L31 | L32 | L33 | L34 | L35 |   | R30 | R31 | R32 | R33 | R34 | R35 | R36 |      | R37 |
 * |---------------------------------------------------------------------------------------------------+
 * |    L40    | L41 | L42 | L43 | L44 | L45 |   | R40 | R41 | R42 | R43 | R44 | R45 | R46 | R47 | R57 |
 * |-------------------------------------------   -----------------------------------------------------+
 * |  L50  | L51 |  L52 | L53 |  L54  | L55 |   | R50 |  R51 |  R52 |  R53 | R54 |   | R55 | R56 | R64 |
 * |----------------------------------------     ------------------------------------------------------'
 */

#define LAYOUT( \
    L00, L01, L02, L03, L04, L05,      R00, R01, R02, R03, R04, R05, R06, R07, R60, \
    L10, L11, L12, L13, L14, L15,      R10, R11, R12, R13, R14, R15, R16, R17, R61, R62, \
    L20, L21, L22, L23, L24, L25,      R20, R21, R22, R23, R24, R25, R26, R27, R63, \
    L30, L31, L32, L33, L34, L35,      R30, R31, R32, R33, R34, R35, R36, R37, \
    L40, L41, L42, L43, L44, L45,      R40, R41, R42, R43, R44, R45, R46, R47, R57, \
    L50, L51, L52, L53, L54, L55,      R50, R51, R52, R53, R54, R55, R56, R64 \
  ) \
  { \
    { L00,   L01,   L02,   L03,   L04,   L05, KC_NO, KC_NO }, \
    { L10,   L11,   L12,   L13,   L14,   L15, KC_NO, KC_NO }, \
    { L20,   L21,   L22,   L23,   L24,   L25, KC_NO, KC_NO }, \
    { L30,   L31,   L32,   L33,   L34,   L35, KC_NO, KC_NO }, \
    { L40,   L41,   L42,   L43,   L44,   L45, KC_NO, KC_NO }, \
    { L50,   L51,   L52,   L53,   L54,   L55, KC_NO, KC_NO }, \
    {KC_NO,KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { R00,   R01,   R02,   R03,   R04,   R05,   R06,   R07 }, \
    { R10,   R11,   R12,   R13,   R14,   R15,   R16,   R17 }, \
    { R20,   R21,   R22,   R23,   R24,   R25,   R26,   R27 }, \
    { R30,   R31,   R32,   R33,   R34,   R35,   R36,   R37 }, \
    { R40,   R41,   R42,   R43,   R44,   R45,   R46,   R47 }, \
    { R50,   R51,   R52,   R53,   R54,   R55,   R56,   R57 }, \
    { R60,   R61,   R62,   R63,   R64, KC_NO, KC_NO, KC_NO }  \
  }
