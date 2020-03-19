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
     l13, l23, r13, r23, \
     l31, l21, r31, r21, \
     l32, l12, r32, r12 \
 ) \
 { \
     { KC_NO, l21, l31 }, \
     { l12, KC_NO, l32 }, \
     { l13, l23, KC_NO }, \
     { KC_NO, r21, r31 }, \
     { r12, KC_NO, r32 }, \
     { r13, r23, KC_NO }, \
 }
