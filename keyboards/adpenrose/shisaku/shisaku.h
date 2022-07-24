// Copyright 2022 Arturo Avila (@ADPenrose)
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

#define LAYOUT_all( \
    	 k00, k01, k02, k03, k04, k05,	 k06, k10, k11, k12, k13, k14, \
    	 k15, k16, k20, k21, k22, k23,	 k24, k25, k26, k30, k33, k34, \
    k35, k40, k41, k42, k43, k44, k45,	 k50, k51, k52, k53, k54, k55, k60, \
    k61, 	        k62, k63, k64, 	 k65,                k70, k74, k75 \
) { \
    { k00, k01, k02, k03, k04, k05, k06 }, \
    { k10, k11, k12, k13, k14, k15, k16 }, \
    { k20, k21, k22, k23, k24, k25, k26 }, \
    { k30, XXX, XXX, k33, k34, k35, XXX }, \
    { k40, k41, k42, k43, k44, k45, XXX }, \
    { k50, k51, k52, k53, k54, k55, XXX }, \
    { k60, k61, k62, k63, k64, k65, XXX }, \
    { k70, XXX, XXX, XXX, k74, k75, XXX } \
}
