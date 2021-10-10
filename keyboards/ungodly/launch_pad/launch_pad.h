/* Copyright 2020 Ungodly Design <hello@ungodly.design>
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

/* 4x5 numpad matrix layout
   * ,-------------------.
   * | 00 | 01 | 02 | 03 |
   * |----|----|----|----|
   * | 10 | 11 | 12 | 13 |
   * |----|----|----|----|
   * | 20 | 21 | 22 | 23 |
   * |----|----|----|----|
   * | 30 | 31 | 32 | 33 |
   * |----|----|----|----|
   * | 40 | 41 | 42 | 43 |
   * `-------------------'
 */

 /* Numpad matrix layout
    * ,-------------------.
    * | 00 | 01 | 02 | 03 |
    * |----|----|----|----|
    * | 10 | 11 | 12 | 13 |
    * |----|----|----|----|
    * | 20 | 21 | 22 | 23 |
    * |----|----|----|----|
    * | 30 | 31 | 32 |    |
    * |----|----|----| 33 |
    * |   41    | 42 |    |
    * `-------------------'
  */

#define LAYOUT_ortho_5x4( \
	k00, k01, k02, k03,  \
	k10, k11, k12, k13,  \
	k20, k21, k22, k23,  \
	k30, k31, k32, k33,  \
	k40, k41, k42, k43   \
) \
{ \
	{k00, k01, k02, k03}, \
	{k10, k11, k12, k13}, \
	{k20, k21, k22, k23}, \
	{k30, k31, k32, k33}, \
	{k40, k41, k42, k43}  \
}
