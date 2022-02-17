/* Copyright 2021 Ramon Imbao
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

void adjust_leds(void);

#define ___ KC_NO


// Regular numpad layout
// Full sized backspace
// Full left shift
// ANSI enter
// 1.25 | 1.25 | 1.25 | 6.25 | 1.25 | 1.25 bottom row
#define LAYOUT_ansi( \
    k00, k10, k01, k11,  k02,   k12, k03, k13, k04,   k05, k15, k06, k16,   k17, k08, k18, k09,    k19, \
    k20, k30, k21, k31,  k22, k32, k23, k33, k24, k34, k25, k35, k26, k36, k27, k37, k28,   k38,   k39, \
    k40, k50, k41, k51,   k42,  k52, k43, k53, k44, k54, k45, k55, k46, k56, k47, k57, k48,  k49,  k59, \
    k60, k70, k61,         k62,  k72, k63, k73, k64, k74, k65, k75, k66, k76, k67, k77,    k78,    k79, \
    k80, k90, k81, k91,  k82,      k83, k93, k84, k94, k85, k95, k86, k96, k87, k97,   k98,   k89, k99, \
       ka0,   ka1,       ka2,  kb2,  ka3,               ka5,              ka7,  kb7,     kb8, ka9, kb9  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, ___, k08, k09 }, \
    { k10, k11, k12, k13, ___, k15, k16, k17, k18, k19 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, ___ }, \
    { k30 ,k31, k32, k33, k34, k35, k36, k37, k38, k39 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, ___, k59 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, ___, ___ }, \
    { k70, ___, k72, k73, k74, k75, k76, k77, k78, k79 }, \
    { k80, k81, k82, k83, k84, k85, k86, k87, ___, k89 }, \
    { k90, k91, ___, k93, k94, k95, k96, k97, k98, k99 }, \
    { ka0, ___, ka2, ka3, ___, ka5, ___, ka7, ___, ka9 }, \
    { ___, ___, kb2, ___, ___, ___, ___, kb7, kb8, kb9 }, \
    { ___, ___, ___, ___, ___, ___, ___, ___, ___, ___ }, \
}

// Regular numpad layout
// Full sized backspace
// Split left shift
// ISO enter
// 1.25 | 1.25 | 1.25 | 6.25 | 1.25 | 1.25 bottom row
#define LAYOUT_iso( \
    k00, k10, k01, k11,  k02,   k12, k03, k13, k04,   k05, k15, k06, k16,   k17, k08, k18, k09,    k19, \
    k20, k30, k21, k31,  k22, k32, k23, k33, k24, k34, k25, k35, k26, k36, k27, k37, k28,   k38,   k39, \
    k40, k50, k41, k51,   k42,  k52, k43, k53, k44, k54, k45, k55, k46, k56, k47, k57, k48,        k59, \
    k60, k70, k61,         k62,  k72, k63, k73, k64, k74, k65, k75, k66, k76, k67, k77, k78, k49,  k79, \
    k80, k90, k81, k91,  k82, k92, k83, k93, k84, k94, k85, k95, k86, k96, k87, k97,   k98,   k89, k99, \
       ka0,   ka1,       ka2,  kb2,  ka3,               ka5,              ka7,  kb7,     kb8, ka9, kb9  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, ___, k08, k09 }, \
    { k10, k11, k12, k13, ___, k15, k16, k17, k18, k19 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, ___ }, \
    { k30 ,k31, k32, k33, k34, k35, k36, k37, k38, k39 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, ___, k59 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, ___, ___ }, \
    { k70, ___, k72, k73, k74, k75, k76, k77, k78, k79 }, \
    { k80, k81, k82, k83, k84, k85, k86, k87, ___, k89 }, \
    { k90, k91, k92, k93, k94, k95, k96, k97, k98, k99 }, \
    { ka0, ___, ka2, ka3, ___, ka5, ___, ka7, ___, ka9 }, \
    { ___, ___, kb2, ___, ___, ___, ___, kb7, kb8, kb9 }, \
    { ___, ___, ___, ___, ___, ___, ___, ___, ___, ___ }, \
}

// Macro numpad layout
// Split backspace
// Split left shift
// ANSI enter
// 1.25 | 1.25 | 1.25 | 6.25 | 1 | 1 | 1 bottom row
// Encoder keymap exposed for VIA
#define LAYOUT_all( \
    k00, k10, k01, k11,  k02,   k12, k03, k13, k04,   k05, k15, k06, k16,   k17, k08, k18, k09,    k19, \
    k20, k30, k21, k31,  k22, k32, k23, k33, k24, k34, k25, k35, k26, k36, k27, k37, k28, k38,k29, k39, \
    k40, k50, k41, k51,   k42,  k52, k43, k53, k44, k54, k45, k55, k46, k56, k47, k57, k48,  k49,  k59, \
    k60, k70, k61, k71,    k62,  k72, k63, k73, k64, k74, k65, k75, k66, k76, k67, k77,    k78,    k79, \
    k80, k90, k81, k91,  k82, k92, k83, k93, k84, k94, k85, k95, k86, k96, k87, k97,   k98,   k89, k99, \
    ka0, kb0, ka1, kb1,  ka2,  kb2,  ka3,               ka5,              ka7, kb7, ka8, kb8, ka9, kb9, \
    re0, re1 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, ___, k08, k09 }, \
    { k10, k11, k12, k13, ___, k15, k16, k17, k18, k19 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, ___ }, \
    { k30 ,k31, k32, k33, k34, k35, k36, k37, k38, k39 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, ___, k59 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, ___, ___ }, \
    { k70, k71, k72, k73, k74, k75, k76, k77, k78, k79 }, \
    { k80, k81, k82, k83, k84, k85, k86, k87, ___, k89 }, \
    { k90, k91, k92, k93, k94, k95, k96, k97, k98, k99 }, \
    { ka0, ka1, ka2, ka3, ___, ka5, ___, ka7, ka8, ka9 }, \
    { kb0, kb1, kb2, ___, ___, ___, ___, kb7, kb8, kb9 }, \
    { re0, re1, ___, ___, ___, ___, ___, ___, ___, ___ }, \
}
