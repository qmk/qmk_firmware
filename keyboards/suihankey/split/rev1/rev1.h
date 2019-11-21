/* Copyright 2019 kakunpc
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
 * layout of the board and position of the Leys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    L00, L01, L02, L03, L04,            R04, R03, R02, R01, R00, \
    L10, L11, L12, L13, L14,            R14, R13, R12, R11, R10, \
    L20, L21, L22, L23, L24,            R24, R23, R22, R21, R20, \
              L30, L31, L32,            R32, R31, R30   \
) \
{ \
    { L00, L10, L20, L30 }, \
    { L01, L11, L21, L31 }, \
    { L02, L12, L22, L32 }, \
    { L03, L13, L23, KC_NO }, \
    { L04, L14, L24, KC_NO }, \
    { R00, R10, R20, R30 }, \
    { R01, R11, R21, R31 }, \
    { R02, R12, R22, R32 }, \
    { R03, R13, R23, KC_NO }, \
    { R04, R14, R24, KC_NO }, \
}
