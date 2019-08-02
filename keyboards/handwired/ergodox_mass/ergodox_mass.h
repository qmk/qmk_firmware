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
    L00,L01,L02,L03,L04,L05,L06,     \
    L10,L11,L12,L13,L14,L15,L16,     \
    L20,L21,L22,L23,L24,L25,         \
    L30,L31,L32,L33,L34,L35,L36,     \
    L40,L41,L42,L43,L44,             \
                          LT01,LT02, \
                               LT12, \
                     LT20,LT21,LT22, \
                     LT30,     LT32, \
                                     \
        R06,R05,R04,R03,R02,R01,R00, \
        R16,R15,R14,R13,R12,R11,R10, \
        R25,R24,R23,R22,R21,R20,     \
        R36,R35,R34,R33,R32,R31,R30, \
        R44,R43,R42,R41,R40,         \
    RT02,RT01,                       \
    RT12,                            \
    RT22,RT21,RT20,                  \
    RT32,     RT30 )                 \
\
{\
  { R13,   R03,   R14,   R04,   R15,   R05,   R06,   R16   }, \
  { R02,   R12,   R01,   R11,   R00,   R10,   R20,   R21   }, \
  { R22,   R33,   R23,   R34,   R24,   R25,   R36,   R35   }, \
  { R32,   R31,   R30,   R40,   R41,   R42,   R43,   R44   }, \
  { RT01,  RT02,  RT12,  RT22,  RT32,  RT21,  RT30,  RT20  }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
\
  { L21,   L20,   L10,   L00,   L11,   L01,   L12,   L02   }, \
  { L16,   L06,   L05,   L15,   L04,   L14,   L03,   L13   }, \
  { L44,   L43,   L42,   L41,   L40,   L30,   L31,   L32   }, \
  { L35,   L36,   L25,   L24,   L34,   L23,   L33,   L22   }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { LT20,  LT30,  LT21,  LT32,  LT22,  LT12,  LT02,  LT01  }, \
}
