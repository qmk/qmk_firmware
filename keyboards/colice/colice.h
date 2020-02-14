/* Copyright 2020 Takeshi Nishio
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

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */


#define LAYOUT( \
  L40,  L00, L01, L02, L03, L04, L05, L06,      L07, L08, L09,               R07, R06, R05, R04, R03, R02, R01, \
        L41, L10, L11, L12, L13, L14, L15,      L16, L17, L18, L19,          R17, R16, R15, R14, R13, R12, R11, R10, \
        L42, L20, L21, L22, L23, L24, L25,      L26, L27, L28, L29,          R27, R26, R25, R24, R23, R22, R21, \
        L43, L30, L31, L32, L33, L34, L35,      L36, L37, L38, L39,          R37, R36, R35, R34, R33, R32, R31, \
        L44,           L45, L46, L47,           L48,      L49,               R47, R46, R45, R44, R43, R42, R41 \
) \
{ \
  { L00,   L01, L02, L03, L04, L05, L06, L07, L08,   L09 }, \
  { L10,   L11, L12, L13, L14, L15, L16, L17, L18,   L19 }, \
  { L20,   L21, L22, L23, L24, L25, L26, L27, L28,   L29 }, \
  { L30,   L31, L32, L33, L34, L35, L36, L37, L38,   L39 }, \
  { L40,   L41, L42, L43, L44, L45, L46, L47, L48,   L49 }, \
  { KC_NO, R01, R02, R03, R04, R05, R06, R07, KC_NO, KC_NO }, \
  { R10,   R11, R12, R13, R14, R15, R16, R17, KC_NO, KC_NO }, \
  { KC_NO, R21, R22, R23, R24, R25, R26, R27, KC_NO, KC_NO }, \
  { KC_NO, R31, R32, R33, R34, R35, R36, R37, KC_NO, KC_NO }, \
  { KC_NO, R41, R42, R43, R44, R45, R46, R47, KC_NO, KC_NO } \
}


/* 動作確認済み
#define LAYOUT( \
  L00, L01, L02, L03, L04, L05, L06, L07, L08, L09, \
  L10, L11, L12, L13, L14, L15, L16, L17, L18, L19, \
  L20, L21, L22, L23, L24, L25, L26, L27, L28, L29, \
  L30, L31, L32, L33, L34, L35, L36, L37, L38, L39, \
  L40, L41, L42, L43, L44, L45, L46, L47, L48, L49 \
) \
{ \
  { L00, L01, L02, L03, L04, L05, L06, L07, L08, L09 }, \
  { L10, L11, L12, L13, L14, L15, L16, L17, L18, L19 }, \
  { L20, L21, L22, L23, L24, L25, L26, L27, L28, L29 }, \
  { L30, L31, L32, L33, L34, L35, L36, L37, L38, L39 }, \
  { L40, L41, L42, L43, L44, L45, L46, L47, L48, L49 } \
}
*/
