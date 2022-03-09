/* Copyright 2018 Jumail Mundekkat
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

#define LAYOUT( \
    k40, k50, k41, k51, k42, k52, k43, k53, k44, k54, k45, k55, k46, k56, k47, k57, \
    k30, k60, k31, k61, k32, k62, k33, k63, k34, k64, k35, k65, k36, k66, k37, k67, \
    k20, k70, k21, k71, k22, k72, k23, k73, k24, k74, k25, k75, k26, k76, k27, k77, \
    k10, k80, k11, k81, k12, k82, k13, k83, k14, k84, k15, k85, k16, k86, k17, k87, \
    k00, k90, k01, k91, k02, k92, k03, k93, k04, k94, k05, k95, k06, k96, k07, k97 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67 }, \
    { k70, k71, k72, k73, k74, k75, k76, k77 }, \
    { k80, k81, k82, k83, k84, k85, k86, k87 }, \
    { k90, k91, k92, k93, k94, k95, k96, k97 } \
}
