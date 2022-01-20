/*
Copyright 2020 Hung DO <hungdohuy@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"
#define _x_ KC_NO

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 * MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5 }
 * MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7, C7, C6, C5, C4, C3, C2 }
 *
 */

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,   k0d, \
    k10 , k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,  k1d, \
    k20  , k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,   k2c, \
    k30   , k31, k32, k33, k34, k35, k36, k37, k38, k39,    k3a, k3b,  k3c, \
    k40 , k41 , k42 ,          k43              , k44, k45, k46, k47 , k48 \
) { \
    { k00, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_ }, \
    { _x_, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k46 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3c, k3a, k47, _x_ }, \
    { k40, k41, k42, k43, k45, _x_, _x_, k44, _x_, _x_, _x_, k3b, _x_, k48 }  \
}

