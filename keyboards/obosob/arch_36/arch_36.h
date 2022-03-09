/* Copyright 2020 Obosob <obosob@riseup.net>
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
#define LAYOUT_split_3x5_3( \
    L00, L01, L02, L03, L04,    R05, R06, R07, R08, R09, \
    L10, L11, L12, L13, L14,    R15, R16, R17, R18, R19, \
    L20, L21, L22, L23, L24,    R25, R26, R27, R28, R29, \
              L32, L33, L34,    R35, R36, R37 \
) \
{ \
    { L00,   L01,   L02,   L03,   L04 }, \
    { L10,   L11,   L12,   L13,   L14 }, \
    { L20,   L21,   L22,   L23,   L24 }, \
    { KC_NO, KC_NO, L32,   L33,   L34 }, \
    { R09,   R08,   R07,   R06,   R05 }, \
    { R19,   R18,   R17,   R16,   R15 }, \
    { R29,   R28,   R27,   R26,   R25 }, \
    { KC_NO, KC_NO, R37,   R36,   R35 }, \
}
