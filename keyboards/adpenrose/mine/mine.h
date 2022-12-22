// Copyright 2022 Arturo Avila (@Arturo Avila)
// SPDX-License-Identifier: GPL-2.0-or-later

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
#define XXX KC_NO

#define LAYOUT_1800_alice_ansi( \
                                                                                                       k09, \
    k00, k01, k11, k02, k12, k03, k13,     k93, kA3, k04, k05, k06, k16, kA6, k07,      k17, k08, kA8, k19, \
    k10, kA0, k21, kA1, k22, kA2, k23,     k83, k14, kA4, k15, kA5, k26, k96,           k27, k18, k98, k88, \
    k20, k90, k31, k91, k32, k92,          k73, k24, k94, k25, k95, k36, k86, k77,      k37, k28, k78,      \
    k30, k80, k41, k81, k42, k82,          k63, k34, k84, k35, k85, k46,      k76,      k47, k38, k68, k58, \
    k40,      k51, k71, k52, k72, k33,     k53, k44, k54, k74, k45, k75, k56,      k57,      kA7, k48,      \
    k50, k60,                k61, k62,     k43, k64,      k55, k65,           k67, k87, k97                 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, XXX }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, XXX }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58, XXX }, \
    { k60, k61, k62, k63, k64, k65, XXX, k67, k68, XXX }, \
    { XXX, k71, k72, k73, k74, k75, k76, k77, k78, XXX }, \
    { k80, k81, k82, k83, k84, k85, k86, k87, k88, XXX }, \
    { k90, k91, k92, k93, k94, k95, k96, k97, k98, XXX }, \
    { kA0, kA1, kA2, kA3, kA4, kA5, kA6, kA7, kA8, XXX } \
}

#define LAYOUT_1800_alice_iso( \
                                                                                                       k09, \
    k00, k01, k11, k02, k12, k03, k13,     k93, kA3, k04, k05, k06, k16, kA6, k07,      k17, k08, kA8, k19, \
    k10, kA0, k21, kA1, k22, kA2, k23,     k83, k14, kA4, k15, kA5, k26, k96,           k27, k18, k98, k88, \
    k20, k90, k31, k91, k32, k92,          k73, k24, k94, k25, k95, k36, k86,           k37, k28, k78,      \
    k30, k80, k41, k81, k42, k82,          k63, k34, k84, k35, k85, k46, k66, k76,      k47, k38, k68, k58, \
    k40, k70, k51, k71, k52, k72, k33,     k53, k44, k54, k74, k45, k75, k56,      k57,      kA7, k48,      \
    k50, k60,                k61, k62,     k43, k64,      k55, k65,           k67, k87, k97                 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, XXX }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, XXX }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58, XXX }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68, XXX }, \
    { k70, k71, k72, k73, k74, k75, k76, XXX, k78, XXX }, \
    { k80, k81, k82, k83, k84, k85, k86, k87, k88, XXX }, \
    { k90, k91, k92, k93, k94, k95, k96, k97, k98, XXX }, \
    { kA0, kA1, kA2, kA3, kA4, kA5, kA6, kA7, kA8, XXX } \
}

#define LAYOUT_all( \
                                                                                                       k09, \
    k00, k01, k11, k02, k12, k03, k13,     k93, kA3, k04, k05, k06, k16, kA6, k07,      k17, k08, kA8, k19, \
    k10, kA0, k21, kA1, k22, kA2, k23,     k83, k14, kA4, k15, kA5, k26, k96,           k27, k18, k98, k88, \
    k20, k90, k31, k91, k32, k92,          k73, k24, k94, k25, k95, k36, k86, k77,      k37, k28, k78,      \
    k30, k80, k41, k81, k42, k82,          k63, k34, k84, k35, k85, k46, k66, k76,      k47, k38, k68, k58, \
    k40, k70, k51, k71, k52, k72, k33,     k53, k44, k54, k74, k45, k75, k56,      k57,      kA7, k48,      \
    k50, k60,                k61, k62,     k43, k64,      k55, k65,           k67, k87, k97                 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, XXX }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, XXX }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58, XXX }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68, XXX }, \
    { k70, k71, k72, k73, k74, k75, k76, k77, k78, XXX }, \
    { k80, k81, k82, k83, k84, k85, k86, k87, k88, XXX }, \
    { k90, k91, k92, k93, k94, k95, k96, k97, k98, XXX }, \
    { kA0, kA1, kA2, kA3, kA4, kA5, kA6, kA7, kA8, XXX } \
}
