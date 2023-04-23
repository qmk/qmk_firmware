/* Copyright 2022 Ramon Imbao
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
#define ___ KC_NO

#define LAYOUT_all( \
    k00, k10, k01, k11, k02, k12, k03, k13, k04, k14, k05, k15, k06, k16, k07, k17, \
    k20, k30, k21, k31, k22, k32, k23,      k24, k34, k25, k35, k26, k36, k27, k37, \
    k40, k50, k41, k51, k42, k52, k43,      k44, k54, k45, k55, k46, k56,      k57, \
         k70, k61, k71, k62, k72, k63,      k64, k74, k65, k75, k66, k76, k67, k77, \
         k80,      k81, k82,      k83,           k84,      k85,                k87  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27 }, \
    { k30, k31, k32, ___, k34, k35, k36, k37 }, \
    { k40, k41, k42, k43, k44, k45, k46, ___ }, \
    { k50, k51, k52, ___, k54, k55, k56, k57 }, \
    { ___, k61, k62, k63, k64, k65, k66, k67 }, \
    { k70, k71, k72, ___, k74, k75, k75, k77 }, \
    { k80, k81, k82, k83, k84, k85, ___, k87 }, \
}
