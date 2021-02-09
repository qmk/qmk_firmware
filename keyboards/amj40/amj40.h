/* Copyright 2017 Fabian Topfstedt
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

// readability  
#define XXX KC_NO

/* AMJ40 ver2.0 layout1 配列一
 * ,-----------------------------------------------------------.
 * | 00 | 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09 | 0A | 0B |
 * |-----------------------------------------------------------|
 * | 10   | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 1B    |
 * |-----------------------------------------------------------|
 * | 20     | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 |  2A | 2B |
 * |-----------------------------------------------------------|
 * | 30  | 31 | 32  |   34      |  35         | 39  | 3A | 3B  |
 * `-----------------------------------------------------------'
 */
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19,      k1b,  \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,  \
    k30, k31, k32,      k34, k35,                k39, k3a, k3b  \
) { \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b}, \
    {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, XXX, k1b}, \
    {k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b}, \
    {k30, k31, k32, XXX, k34, k35, XXX, XXX, XXX, k39, k3a, k3b} \
}
