/* Copyright 2018 MechMerlin
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
#ifndef BUDGET96_H
#define BUDGET96_H

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
    k05, k25, k35, k45, k55, k06, kA6, kA7, k07, kB5, kC5, kD5, kE5, kD1, kE1, kD0, k67, k97, k87, \
    k04, k14, k24, k34, k44, k54, k16, kB6, kB7, k17, kA4, kB4, kC4, kD4, kE4, k64, k74, k84, k94, \
    k03, k13, k23, k33, k43, k53, k26, kC6, kC7, k27, kA3, kB3, kC3, kD3, k63, k73, k83, k93,      \
    k02, k12, k22, k32, k42, k52, k36, kD6, kD7, k37, kA2, kB2, kC2, k62, k72, k82, k92,           \
    k01, k30, k11, k21, k31, k41, k51, k46, kE6, k47, kA1, kB1, k86, k61, k71, k81, k91,           \
    k00, k10, k20, k56, k57, kA0, kB0, k66, k76, k96, k60, k80, k90
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67 }, \
    { k70, k71, k72, k73, k74, k75, k76, k77 }, \
    { k80, k81, k82, k83, k84, k85, k86, k87 }, \
    { k90, k91, k92, k93, k94, k95, k96, k97 }, \
    { kA0, kA1, kA2, kA3, kA4, kA5, kA6, kA7 }, \
    { kB0, kB1, kB2, kB3, kB4, kB5, kB6, kB7 }, \
    { kC0, kC1, kC2, kC3, kC4, kC5, kC6, kC7 }, \
    { kD0, kD1, kD2, kD3, kD4, kD5, kD6, kD7 }, \
    { kE0, kE1, kE2, kE3, kE4, kE5, kE6, kE7 }, \
}

#endif
