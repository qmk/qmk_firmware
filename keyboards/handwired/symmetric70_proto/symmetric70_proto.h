/* Copyright 2020 mtei
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
     L00, L01, L02, L03, L04, L05, L06,            R06, R05, R04, R03, R02, R01, R00, \
      L10, L11, L12, L13, L14, L15, L16,          R16, R15, R14, R13, R12, R11, R10, \
     L20, L21, L22, L23, L24, L25, L26,            R26, R25, R24, R23, R22, R21, R20, \
    L30, L31, L32, L33, L34, L35, L36, L37,    R37, R36, R35, R34, R33, R32, R31, R30, \
    L40,      L42, L43, L44, L45,      L47,    R47,      R45, R44, R43, R42,      R40  \
) { \
    { L00, L01,   L02, L03, L04, L05, L06,   KC_NO,   KC_NO, R06, R05, R04, R03, R02, R01,   R00 }, \
    { L10, L11,   L12, L13, L14, L15, L16,   KC_NO,   KC_NO, R16, R15, R14, R13, R12, R11,   R10 }, \
    { L20, L21,   L22, L23, L24, L25, L26,   KC_NO,   KC_NO, R26, R25, R24, R23, R22, R21,   R20 }, \
    { L30, L31,   L32, L33, L34, L35, L36,   L37,     R37,   R36, R35, R34, R33, R32, R31,   R30 }, \
    { L40, KC_NO, L42, L43, L44, L45, KC_NO, L47,     R47, KC_NO, R45, R44, R43, R42, KC_NO, R40 }  \
}
