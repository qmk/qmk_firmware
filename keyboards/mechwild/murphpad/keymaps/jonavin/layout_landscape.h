/* Copyright 2021 Jonavin Eng
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

/* First section contains the physical layout of the board and position of keys.
 *
 * Second is a two-dimensional array which represents the switch matrix.
 */

#define LAYOUT_landscape( \
    k50, k40, k30, \
    k51, k41, k31, k20, k10,    k00, \
    k52, k42, k32, k21, k11,    k01, \
    k53, k43, k33, k22, k12,    k02, \
    k54, k44, k34, k23, k13,    k03, \
	\
	     BACK00, BACK01, BACK02 \
\
) { \
    { BACK00, k00, k01, k02, k03 }, \
    { BACK01, k10, k11, k12, k13 },  \
    { BACK02, k20, k21, k22, k23 },  \
    { k30, k31, k32, k33, k34 },     \
    { k40, k41, k42, k43, k44 },     \
    { k50, k51, k52, k53, k54 }      \
}

