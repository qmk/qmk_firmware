/* Copyright 2019 'Naoto Takai'
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

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

#define LAYOUT( \
    L00, L01, L02, L03, L04, L05, R00, R01, R02, R03, R04, R05, R06, R07, \
    L10, L11, L12, L13, L14, L15, R10, R11, R12, R13, R14, R15, R16, \
    L20, L21, L22, L23, L24, L25, R20, R21, R22, R23, R24, R25, R26, \
         L31, L32, L33,           R30,      R32, R33 \
) \
{ \
    { L00,   L01,   L02,   L03,   L04,   L05,   KC_NO, KC_NO }, \
    { L10,   L11,   L12,   L13,   L14,   L15,   KC_NO, KC_NO }, \
    { L20,   L21,   L22,   L23,   L24,   L25,   KC_NO, KC_NO }, \
    { KC_NO, L31,   L32,   L33,   KC_NO, KC_NO, KC_NO, KC_NO }, \
    { R00,   R01,   R02,   R03,   R04,   R05,   R06,   R07 }, \
    { R10,   R11,   R12,   R13,   R14,   R15,   R16,   KC_NO }, \
    { R20,   R21,   R22,   R23,   R24,   R25,   R26,   KC_NO }, \
    { R30,   KC_NO, R32,   R33,   KC_NO, KC_NO, KC_NO, KC_NO }  \
}
