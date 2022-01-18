// Copyright 2022 s8erdude (@jpuerto96)
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
#define LAYOUT_2x3u( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k59, k58, k57, k56,   k55, k54,     k53, k52, k51, k50, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k69, k68, k67, k66,   k65, k64,     k63, k62, k61, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k79, k78, k77,                      k73, k72, k71, k70, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k89, k88,                k85,       k83, k82, k81, \
    k40, k41, k42, k43,           k46,           k49, k99, k98,           k96, k95, k94,       k92, k91, k90 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39 }, \
    { k40, k41, k42, k43, KC_NO, KC_NO, k46, KC_NO, KC_NO, k49 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58, k59 }, \
    { KC_NO, k61, k62, k63, k64, k65, k66, k67, k68, k69 }, \
    { k70, k71, k72, k73, KC_NO, KC_NO, KC_NO, k77, k78, k79 }, \
    { KC_NO, k81, k82, k83, KC_NO, k85, KC_NO, KC_NO, k88, k89 }, \
    { k90, k91, k92, KC_NO, k94, k95, k96, KC_NO, k98, k99 } \
}

#define LAYOUT_625u( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k59, k58, k57, k56,   k55, k54,     k53, k52, k51, k50, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k69, k68, k67, k66,   k65, k64,     k63, k62, k61, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k79, k78, k77,                      k73, k72, k71, k70, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k89, k88,                k85,       k83, k82, k81, \
    k40, k41, k42,           k45,                k49, k99, k98,           k96, k95, k94,       k92, k91, k90 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39 }, \
    { k40, k41, k42, KC_NO, KC_NO, k45, KC_NO, KC_NO, KC_NO, k49 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58, k59 }, \
    { KC_NO, k61, k62, k63, k64, k65, k66, k67, k68, k69 }, \
    { k70, k71, k72, k73, KC_NO, KC_NO, KC_NO, k77, k78, k79 }, \
    { KC_NO, k81, k82, k83, KC_NO, k85, KC_NO, KC_NO, k88, k89 }, \
    { k90, k91, k92, KC_NO, k94, k95, k96, KC_NO, k98, k99 } \
}
