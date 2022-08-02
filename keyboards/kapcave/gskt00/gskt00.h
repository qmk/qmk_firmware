/*
Copyright 2021 KapCave

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

#define XXX KC_NO

#define LAYOUT_all( \
    k36, k37, k46, k47, k56, k57, k66, k67, k76, k77, k06, k07, k17, k26, k27, \
    k34, k35, k44, k45, k54, k55, k64, k65, k75, k05, k15, k16, k25, k24, \
    k32, k33, k43, k52, k53, k63, k73, k74, k03, k04, k13, k14, k23, \
    k31, k41, k42, k51, k61, k62, k71, k72, k01, k02, k11, k12, k21, k22, \
    k30, k40, k50,           k60,                          k00, k10, k20 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67 }, \
    { XXX, k71, k72, k73, k74, k75, k76, k77 } \
}

#define LAYOUT_60_iso_tsangan( \
    k36, k37, k46, k47, k56, k57, k66, k67, k76, k77, k06, k07, k17,      k27, \
    k34, k35, k44, k45, k54, k55, k64, k65, k75, k05, k15, k16, k25, \
    k32, k33, k43, k52, k53, k63, k73, k74, k03, k04, k13, k14, k24, k23, \
    k31, k41, k42, k51, k61, k62, k71, k72, k01, k02, k11, k12, k21, \
    k30, k40, k50,           k60,                     k00, k10,      k20 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07 }, \
    { XXX, k11, k12, k13, k14, k15, k16, k17 }, \
    { k20, k21, XXX, k23, k24, k25, XXX, k27 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67 }, \
    { XXX, k71, k72, k73, k74, k75, k76, k77 } \
}

#define LAYOUT_60_ansi_tsangan( \
    k36, k37, k46, k47, k56, k57, k66, k67, k76, k77, k06, k07, k17,      k27, \
    k34, k35, k44, k45, k54, k55, k64, k65, k75, k05, k15, k16, k25, k24, \
    k32, k33, k43, k52, k53, k63, k73, k74, k03, k04, k13, k14, k23, \
    k31,      k42, k51, k61, k62, k71, k72, k01, k02, k11, k12, k21,  \
    k30, k40, k50,           k60,                          k00, k10, k20  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17 }, \
    { k20, k21, XXX, k23, k24, k25, XXX, k27 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37 }, \
    { k40, XXX, k42, k43, k44, k45, k46, k47 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67 }, \
    { XXX, k71, k72, k73, k74, k75, k76, k77 } \
}
