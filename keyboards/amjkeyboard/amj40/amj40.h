/* Copyright 2017 Fabian Topfstedt
 * Copyright 2021 James Young (@noroadsleft)
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

/* AMJ40 ver2.0 staggered layouts
 * ,-----------------------------------------------.
 * |00 |01 |02 |03 |04 |05 |06 |07 |08 |09 |0a |0b |
 * |-----------------------------------------------|
 * |10  |11 |12 |13 |14 |15 |16 |17 |18 |19 |1b    |
 * |-----------------------------------------------|
 * |20    |22 |23 |24 |25 |26 |27 |28 |29 |2a  |2b |
 * |-----------------------------------------------|
 * |30  |31 |32  |   34   |35        |39  |3a |3b  | Layout 1 Bottom Row
 * `-----------------------------------------------'
 * ,-----------------------------------------------.
 * |30  |31 |32 |           35           |3a  |3b  | Layout 2
 * `-----------------------------------------------'
 * ,-----------------------------------------------.
 * |30   |31 |32   |   34   |    35    |39 |3a |3b | Layout 3
 * `-----------------------------------------------'
 * ,-----------------------------------------------.
 * |30  |31 |32  |           35           |3a |3b  | Layout 4
 * `-----------------------------------------------'
 */

// a.k.a. Layout 1 or Layout 3 (matrix is the same for both)
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19,      k1b, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
    k30, k31, k32,      k34, k35,                k39, k3a, k3b  \
) { \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b}, \
    {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, XXX, k1b}, \
    {k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b}, \
    {k30, k31, k32, XXX, k34, k35, XXX, XXX, XXX, k39, k3a, k3b} \
}

// a.k.a. Layout 2 or Layout 4 (matrix is the same for both)
#define LAYOUT_625u_space( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19,      k1b, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
    k30, k31, k32,             k35,                   k3a, k3b  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, XXX, k1b }, \
    { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b }, \
    { k30, k31, k32, XXX, XXX, k35, XXX, XXX, XXX, XXX, k3a, k3b } \
}

/* AMJ40 ver2.0 ortholinear layouts
 * ,-----------------------------------------------.
 * |00 |01 |02 |03 |04 |05 |06 |07 |08 |09 |0a |0b |
 * |-----------------------------------------------|
 * |10 |11 |12 |13 |14 |15 |16 |17 |18 |19 |1a |1b |
 * |-----------------------------------------------|
 * |20 |21 |22 |23 |24 |25 |26 |27 |28 |29 |2a |2b |
 * |-----------------------------------------------|
 * |30 |31 |32 |33 |34 |    35    |38  |39 |3a |3b | 2.75u Spacebar
 * `-----------------------------------------------'
 * ,-----------------------------------------------.
 * |30 |31 |32 |          35           |39 |3a |3b | 6u Spacebar
 * `-----------------------------------------------'
 */

// equivalent to LAYOUT_all
#define LAYOUT_ortho_275u_space( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
    k30, k31, k32, k33, k34,     k35,      k38,  k39, k3a, k3b  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b }, \
    { k30, k31, k32, k33, k34, k35, XXX, XXX, k38, k39, k3a, k3b }  \
}

#define LAYOUT_ortho_600u_space( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
    k30, k31, k32,             k35,              k39, k3a, k3b  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b }, \
    { k30, k31, k32, XXX, XXX, k35, XXX, XXX, XXX, k39, k3a, k3b }  \
}
