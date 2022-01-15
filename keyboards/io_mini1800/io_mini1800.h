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
#define LAYOUT( 
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k59, k58, k57, k56, k55, k54, k53, k52, k51, k50, 
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k69, k68, k67, k66, k65, k64, k63, k62, k61, 
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k79, k78, k77, k73, k72, k71, k70, 
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k89, k88, k83, k82, k81, 
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k99, k98, k96, k95, k94, k53, k92, k91, k90
) { 
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09 }, 
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19 }, 
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29 }, 
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39 }, 
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49 }, 
    { k59, k58, k57, k56, k55, k54, k53, k52, k51, k50 }, 
    { k69, k68, k67, k66, k65, k64, k63, k62, k61, KC_NO }, 
    { k79, k78, k77, KC_NO, KC_NO, KC_NO, k73, k72, k71, k70 }, 
    { k89, k88, KC_NO, KC_NO, KC_NO, KC_NO, k83, k82, k81, KC_NO }, 
    { k99, k98, KC_NO, k96, k95, k94, k53, k92, k91, k90 }
}
