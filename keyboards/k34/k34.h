// Copyright 2021 jp_smasher (@jp_smasher)
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
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, \
                   k33, k34, k35, k36 \
) { \
    { k00,   k01,   k02,   k03,   k04,   k05,   k06,   k07,   k08,   k09   }, \
    { k10,   k11,   k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19   }, \
    { k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29   }, \
    { KC_NO, KC_NO, KC_NO, k33,   k34,   k35,   k36,   KC_NO, KC_NO, KC_NO }, \
}
