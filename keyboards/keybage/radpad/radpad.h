/* Copyright 2020 Brandon Schlack
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

#define XXX KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT_4x4_encoders( \
    k00,           k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, k23, \
    k30, k31, k32, k33, \
    k40, k41, k42, k43  \
) \
{ \
    { k00, XXX, XXX, k03 }, \
    { k10, k11, k12, k13 }, \
    { k20, k21, k22, k23 }, \
    { k30, k31, k32, k33 }, \
    { k40, k41, k42, k43 }  \
}

#define LAYOUT_4x3_encoders( \
    k00,           k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, k23, \
    k30, k31, k32, k33 \
) \
{ \
    { k00, XXX, XXX, k03 }, \
    { k10, k11, k12, k13 }, \
    { k20, k21, k22, k23 }, \
    { k30, k31, k32, k33 }, \
    { XXX, XXX, XXX, XXX }  \
}

#define LAYOUT_3x4_encoders( \
    k01,      k03, \
    k11, k12, k13, \
    k21, k22, k23, \
    k31, k32, k33, \
    k41, k42, k43  \
) \
{ \
    { XXX, k01, XXX, k03 }, \
    { XXX, k11, k12, k13 }, \
    { XXX, k21, k22, k23 }, \
    { XXX, k31, k32, k33 }, \
    { XXX, k41, k42, k43 }  \
}

#define LAYOUT_3x3_encoders( \
    k01,      k03, \
    k11, k12, k13, \
    k21, k22, k23, \
    k31, k32, k33  \
) \
{ \
    { XXX, k01, XXX, k03 }, \
    { XXX, k11, k12, k13 }, \
    { XXX, k21, k22, k23 }, \
    { XXX, k31, k32, k33 }, \
    { XXX, XXX, XXX, XXX }  \
}
