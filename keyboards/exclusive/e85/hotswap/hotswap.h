/* Copyright 2020 MechMerlin
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

#define ___ KC_NO

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k68, k67, k65, k64, k63, k66, k62, k61,  \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k78, k70, k77, k75, k73, k76, k72, k71,  \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k88, k87, k85, k84, k83, k86, k82, k81,  \
    k30, k31, k32, k33, k34, k35, k36, k37, k94, k98, k97, k95, k93,  \
    k40, k42, k43, k44, k45, k46, k47, k48, ka8, ka7, ka5, ka4, ka2,  \
    k50, k51, k52, k56, k58, k57, k54, k53, ka6, ka3, ka1 \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08 },  \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18 },  \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28 },  \
    { k30, k31, k32, k33, k34, k35, k36, k37, ___ },  \
    { k40, ___, k42, k43, k44, k45, k46, k47, k48 },  \
    { k50, k51, k52, k53, k54, ___, k56, k57, k58 },  \
    { ___, k61, k62, k63, k64, k65, k66, k67, k68 },  \
    { k70, k71, k72, k73, ___, k75, k76, k77, k78 },  \
    { ___, k81, k82, k83, k84, k85, k86, k87, k88 },  \
    { ___, ___, ___, k93, k94, k95, ___, k97, k98 },  \
    { ___, ka1, ka2, ka3, ka4, ka5, ka6, ka7, ka8 } \
}
