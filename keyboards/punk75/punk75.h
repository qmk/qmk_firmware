/* Copyright 2020 dsanchezseco
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
#define LAYOUT_ortho_5x15( \
    k01, k06, k11, k16, k21, k26, k31, k36, k41, k46, k51, k56, k61, k66, k71, \
    k02, k07, k12, k17, k22, k27, k32, k37, k42, k47, k52, k57, k62, k67, k72, \
    k03, k08, k13, k18, k23, k28, k33, k38, k43, k48, k53, k58, k63, k68, k73, \
    k04, k09, k14, k19, k24, k29, k34, k39, k44, k49, k54, k59, k64, k69, k74, \
    k05, k10, k15, k20, k25, k30, k35, k40, k45, k50, k55, k60, k65, k70, k75 \
) { \
    { k01, k06, k11, k16, k21, k26, k31, k36, k41, k46, k51, k56, k61, k66, k71 }, \
    { k02, k07, k12, k17, k22, k27, k32, k37, k42, k47, k52, k57, k62, k67, k72 }, \
    { k03, k08, k13, k18, k23, k28, k33, k38, k43, k48, k53, k58, k63, k68, k73 }, \
    { k04, k09, k14, k19, k24, k29, k34, k39, k44, k49, k54, k59, k64, k69, k74 }, \
    { k05, k10, k15, k20, k25, k30, k35, k40, k45, k50, k55, k60, k65, k70, k75 } \
}

//TODO: other layouts with the 2u keys
