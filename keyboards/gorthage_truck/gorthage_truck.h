/* Copyright 2021 s8erdude
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT_3u( \
    k00, k01, k02, k03, k04, k05, k06, k07, k40, k41, k42, k43, k44, k45, k46, k47, k48, \
    k10, k11, k12, k13, k14, k15, k16, k17, k50, k51, k52, k53, k54,      k56, k57, k58, \
    k20, k21, k22, k23, k24, k25, k26, k27, k60, k61, k62, k63, k64, k65, k66, k67, k68, \
    k30, k31, k32,      k34,      k70,           k71, k73,      k74, k75, k76, k77, k78  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, XXX }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, XXX }, \
    { k30, k31, k32, XXX, k34, XXX, XXX, XXX, XXX }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48 }, \
    { k50, k51, k52, k53, k54, XXX, k56, k57, k58 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68 }, \
    { k70, k71, XXX, k73, k74, k75, k76, k77, k78 }  \
}

#define LAYOUT_7u( \
    k00, k01, k02, k03, k04, k05, k06, k07, k40, k41, k42, k43, k44, k45, k46, k47, k48, \
    k10, k11, k12, k13, k14, k15, k16, k17, k50, k51, k52, k53, k54,      k56, k57, k58, \
    k20, k21, k22, k23, k24, k25, k26, k27, k60, k61, k62, k63, k64, k65, k66, k67, k68, \
    k30, k31, k32,                k37,                     k73, k74, k75, k76, k77, k78  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, XXX }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, XXX }, \
    { k30, k31, k32, XXX, XXX, XXX, XXX, k37, XXX }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48 }, \
    { k50, k51, k52, k53, k54, XXX, k56, k57, k58 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68 }, \
    { XXX, XXX, XXX, k73, k74, k75, k76, k77, k78 }  \
}

#define LAYOUT_10u( \
    k00, k01, k02, k03, k04, k05, k06, k07, k40, k41, k42, k43, k44, k45, k46, k47, k48, \
    k10, k11, k12, k13, k14, k15, k16, k17, k50, k51, k52, k53, k54,      k56, k57, k58, \
    k20, k21, k22, k23, k24, k25, k26, k27, k60, k61, k62, k63, k64, k65, k66, k67, k68, \
    k30,                     k36,                     k73,      k74, k75, k76, k77, k78  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, XXX }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, XXX }, \
    { k30, XXX, XXX, XXX, XXX, XXX, k36, XXX, XXX }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48 }, \
    { k50, k51, k52, k53, k54, XXX, k56, k57, k58 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68 }, \
    { XXX, XXX, XXX, k73, k74, k75, k76, k77, k78 }  \
}
