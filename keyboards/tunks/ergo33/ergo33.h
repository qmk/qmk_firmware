/* Copyright 2020 Mika Kuitunen 
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

/* The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

/* Matrix layout
 * ,---------.
 * | 00 | 01 |------------------------.
 * |----|----| 02 | 03 | 04 | 05 | 06 |
 * | 10 | 11 |----|----|----|----|----|
 * |----|----| 12 | 13 | 14 | 14 | 16 |
 * | 20 | 21 |----|----|----|----|----|
 * |----|----| 22 | 23 | 24 | 25 | 26 |
 * | 30 | 31 |----|----|----|----|----|  ,----.
 * |----|----| 32 | 33 | 34 | 35 | 36 |  | 46 |
 * | 40 | 41 |---------------------------|----'
 * `---------'            | 43 | 44 | 45 |
 *                        `--------------'
 */

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, \
    k10, k11, k12, k13, k14, k15, k16, \
    k20, k21, k22, k23, k24, k25, k26, \
    k30, k31, k32, k33, k34, k35, k36, \
    k40, k41,                          k46, \
                        k43, k44, k45 \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06 }, \
    { k10, k11, k12, k13, k14, k15, k16 }, \
    { k20, k21, k22, k23, k24, k25, k26 }, \
    { k30, k31, k32, k33, k34, k35, k36 }, \
    { k40, k41, KC_NO, k43, k44, k45, k46 } \
}
