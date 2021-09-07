/* Copyright 2021 Cutie Club
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
#define LAYOUT_all( \
    k00_00, k00_01, k00_02, k00_03, k00_04, \
    k01_00, k01_01, k01_02, k01_03, k01_04, \
    k02_00, k02_01, k02_02, k02_03, k02_04, \
    k03_00, k03_01, k03_02, k03_03, k03_04, \
    k04_00, k04_01, k04_02, k04_03, k04_04  \
) \
{ \
    { k00_00, k00_01, k00_02, k00_03, k00_04 }, \
    { k01_00, k01_01, k01_02, k01_03, k01_04 }, \
    { k02_00, k02_01, k02_02, k02_03, k02_04 }, \
    { k03_00, k03_01, k03_02, k03_03, k03_04 }, \
    { k04_00, k04_01, k04_02, k04_03, k04_04 }  \
}
