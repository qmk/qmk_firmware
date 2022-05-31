/* Copyright 2021 Nathan Spears
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

#define LAYOUT_2x2u( \
    k00, k01, k11, k12, k02, k03, k13, k14, k04, k05, k15, k16, k06, k07, k17, \
    k20, k21, k31, k32, k22, k23, k33, k34, k24, k25, k35, k36, k26, k27, k37, \
    k40, k41, k51, k52, k42, k43, k53, k54, k44, k45, k55, k56, k46, k47, k57, \
    k60, k61, k71, k72, k62, k63, k73, k74, k64, k65, k75, k76, k66, k67, k77, \
    k80, k81, k82, k92, k83, k84, k85, k95, k86, k87, k97 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07 }, \
    { XXX, k11, k12, k13, k14, k15, k16, k17 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27 }, \
    { XXX, k31, k32, k33, k34, k35, k36, k37 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47 }, \
    { XXX, k51, k52, k53, k54, k55, k56, k57 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67 }, \
    { XXX, k71, k72, k73, k74, k75, k76, k77 }, \
    { k80, k81, k82, k83, k84, k85, k86, k87 }, \
    { XXX, XXX, k92, XXX, XXX, k95, XXX, k97 }  \
}
#define LAYOUT_2x3u( \
    k00, k01, k11, k12, k02, k03, k13, k14, k04, k05, k15, k16, k06, k07, k17, \
    k20, k21, k31, k32, k22, k23, k33, k34, k24, k25, k35, k36, k26, k27, k37, \
    k40, k41, k51, k52, k42, k43, k53, k54, k44, k45, k55, k56, k46, k47, k57, \
    k60, k61, k71, k72, k62, k63, k73, k74, k64, k65, k75, k76, k66, k67, k77, \
    k80, k81, k82, k83, k84, k85, k86, k87, k97 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07 }, \
    { XXX, k11, k12, k13, k14, k15, k16, k17 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27 }, \
    { XXX, k31, k32, k33, k34, k35, k36, k37 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47 }, \
    { XXX, k51, k52, k53, k54, k55, k56, k57 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67 }, \
    { XXX, k71, k72, k73, k74, k75, k76, k77 }, \
    { k80, k81, k82, k83, k84, k85, k86, k87 }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, k97 }  \
}
#define LAYOUT_7u( \
    k00, k01, k11, k12, k02, k03, k13, k14, k04, k05, k15, k16, k06, k07, k17, \
    k20, k21, k31, k32, k22, k23, k33, k34, k24, k25, k35, k36, k26, k27, k37, \
    k40, k41, k51, k52, k42, k43, k53, k54, k44, k45, k55, k56, k46, k47, k57, \
    k60, k61, k71, k72, k62, k63, k73, k74, k64, k65, k75, k76, k66, k67, k77, \
    k80, k81, k82, k84, k86, k87, k97 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07 }, \
    { XXX, k11, k12, k13, k14, k15, k16, k17 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27 }, \
    { XXX, k31, k32, k33, k34, k35, k36, k37 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47 }, \
    { XXX, k51, k52, k53, k54, k55, k56, k57 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67 }, \
    { XXX, k71, k72, k73, k74, k75, k76, k77 }, \
    { k80, k81, k82, XXX, k84, XXX, k86, k87 }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, k97 }  \
}
