/* Copyright 2022 yushakobo
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

#define LAYOUT( \
    R08,   R01, L02, R02, R03,   L04, R04, L07, L17,   L27, L37, L47, R07, \
    L00, R00, L01, R11, L12, R12, L03, R13, L14, R14, L05, R05, L06,  R06, \
     L10, R10, L11, R21, L22, R22, L13, R23, L24, R24, L15, R15, L16, R16,   R17, R37, \
      L20,  R20, L21, R31, L32, R32, L23, R33, L34, R34, L25, R25,    L26,   R27, R47, \
        L30,  R30, L31, R41, L42, R42, L33, R43, L44, R44, L35,       L36,   R26, \
    L40,  R40,  L41,           L43,           L45,  R35,  R45,          L46, R36, R46  \
  ) \
  { \
    { L00,   L01,   L02,   L03,   L04,   L05,   L06,   L07, KC_NO }, \
    { L10,   L11,   L12,   L13,   L14,   L15,   L16,   L17, KC_NO }, \
    { L20,   L21,   L22,   L23,   L24,   L25,   L26,   L27, KC_NO }, \
    { L30,   L31,   L32,   L33,   L34,   L35,   L36,   L37, KC_NO }, \
    { L40,   L41,   L42,   L43,   L44,   L45,   L46,   L47, KC_NO }, \
    { R00,   R01,   R02,   R03,   R04,   R05,   R06,   R07,   R08 }, \
    { R10,   R11,   R12,   R13,   R14,   R15,   R16,   R17, KC_NO }, \
    { R20,   R21,   R22,   R23,   R24,   R25,   R26,   R27, KC_NO }, \
    { R30,   R31,   R32,   R33,   R34,   R35,   R36,   R37, KC_NO }, \
    { R40,   R41,   R42,   R43,   R44,   R45,   R46,   R47, KC_NO }  \
  }
