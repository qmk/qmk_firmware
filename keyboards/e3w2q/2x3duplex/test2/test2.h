/* Copyright 2019 e3w2q
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
    l00, l01, l02, r00, r01, r02, \
    l10, l11, l12, r10, r11, r12, \
    l20, l21, l22, r20, r21, r22, \
    l30, l31, l32, r30, r31, r32  \
) \
{ \
    { l00, l01, l02 }, \
    { l10, l11, l12 }, \
    { l20, l21, l22 }, \
    { l30, l31, l32 }, \
    { r00, r01, r02 }, \
    { r10, r11, r12 }, \
    { r20, r21, r22 }, \
    { r30, r31, r32 }  \
}
