/* Copyright 2018 Andrew Mass
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

#define LAYOUT(                      \
    L03,L05,L07,L16,L14,L12,L11,     \
    L02,L04,L06,L17,L15,L13,L10,     \
    L01,L00,L37,L35,L33,L32,         \
    L25,L26,L27,L36,L34,L30,L31,     \
    L24,L23,L22,L21,L20,             \
                            L57,L56, \
                                L55, \
                        L50,L52,L54, \
                        L51,    L53, \
                                     \
        R06,R05,R03,R01,R10,R12,R14, \
        R07,R04,R02,R00,R11,R13,R15, \
        R25,R24,R22,R20,R17,R16,     \
        R26,R27,R23,R21,R30,R31,R32, \
        R37,R36,R35,R34,R33,         \
    R41,R40,                         \
    R42,                             \
    R43,R45,R47,                     \
    R44,    R46                     )\
\
{\
  { R00,   R01,   R02,   R03,   R04,   R05,   R06,   R07   }, \
  { R10,   R11,   R12,   R13,   R14,   R15,   R16,   R17   }, \
  { R20,   R21,   R22,   R23,   R24,   R25,   R26,   R27   }, \
  { R30,   R31,   R32,   R33,   R34,   R35,   R36,   R37   }, \
  { R40,   R41,   R42,   R43,   R44,   R45,   R46,   R47   }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
\
  { L00,   L01,   L02,   L03,   L04,   L05,   L06,   L07   }, \
  { L10,   L11,   L12,   L13,   L14,   L15,   L16,   L17   }, \
  { L20,   L21,   L22,   L23,   L24,   L25,   L26,   L27   }, \
  { L30,   L31,   L32,   L33,   L34,   L35,   L36,   L37   }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { L50,   L51,   L52,   L53,   L54,   L55,   L56,   L57   }, \
}
