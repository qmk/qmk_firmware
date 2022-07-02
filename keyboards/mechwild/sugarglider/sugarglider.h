// Copyright 2022 Kyle McCreery
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define ___ KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
k00, k01, k02, k03, k04, k05,            sw1,  k06, k07, k08, k09, k0A, k0B, \
k10, k11, k12, k13, k14, k15,       sw5, sw2,  k16, k17, k18, k19, k1A, k1B, \
k20, k21, k22, k23, k24, k25,            sw3,  k26, k27, k28, k29, k2A, k2B, \
     sw4,      k30, k31, k32,  k33, k34, k35,  k36, k37, k38,      sw6       \
) { \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, k15 }, \
    { k20, k21, k22, k23, k24, k25 }, \
    { sw4, k30, k31, k32, k33, ___ }, \
    { k06, k07, k08, k09, k0A, k0B }, \
    { k16, k17, k18, k19, k1A, k1B }, \
    { k26, k27, k28, k29, k2A, k2B }, \
    { k34, k35, k36, k37, k38, sw6 }, \
    { sw1, sw2, sw3, ___, ___, sw5 }  \
}
