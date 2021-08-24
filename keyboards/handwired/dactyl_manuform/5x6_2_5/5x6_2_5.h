/* Copyright 2021 Jan Christoph Ebersbach
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

#include "dactyl_manuform.h"

#define LAYOUT_5x6_2_5(\
  L00, L01, L02, L03, L04, L05,                          R00, R01, R02, R03, R04, R05, \
  L10, L11, L12, L13, L14, L15,                          R10, R11, R12, R13, R14, R15, \
  L20, L21, L22, L23, L24, L25,                          R20, R21, R22, R23, R24, R25, \
  L30, L31, L32, L33, L34, L35,                          R30, R31, R32, R33, R34, R35, \
  L40, L41, L42, L43,      L44, L55, L53,      R52, R50, R41,      R42, R43, R44, R45, \
                                L54, L52,      R53, R51                                \
  ) \
  { \
    { L00,   L01,   L02, L03, L04, L05   }, \
    { L10,   L11,   L12, L13, L14, L15   }, \
    { L20,   L21,   L22, L23, L24, L25   }, \
    { L30,   L31,   L32, L33, L34, L35   }, \
    { L40,   L41,   L42, L43, L44, KC_NO }, \
    { KC_NO, KC_NO, L52, L53, L54, L55   }, \
                                          \
    { R00,   R01, R02, R03, R04,   R05   }, \
    { R10,   R11, R12, R13, R14,   R15   }, \
    { R20,   R21, R22, R23, R24,   R25   }, \
    { R30,   R31, R32, R33, R34,   R35   }, \
    { KC_NO, R41, R42, R43, R44,   R45   }, \
    { R50,   R51, R52, R53, KC_NO, KC_NO }  \
}
