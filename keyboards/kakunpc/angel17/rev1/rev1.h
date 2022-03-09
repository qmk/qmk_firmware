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
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT_numpad_5x4( \
    k00, k01, k02, k03, \
    k10, k11, k12, \
    k20, k21, k22, k13, \
    k30, k31, k32, \
    k40, k41, k33 \
) \
{ \
    { k00, k10, k20, k31, k41 }, \
    { k02, k12, k22, k33, KC_NO }, \
    { k01, k11, k21, k32, KC_NO }, \
    { k03, k13, k30, k40, KC_NO }, \
}
