// Copyright 2021 Austin Wang (@Dafondo)
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
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k010, k011, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k110, k111, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k210, k211, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k310, k311, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k410, k411 \
) { \
    { k06  , k17  , k28  , k23  , k34  , k45 , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { k46  , k07  , k18  , k13  , k24  , k35 , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { k36  , k47  , k08  , k03  , k14  , k25 , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { k26  , k37  , k48  , k43  , k04  , k15 , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { k16  , k27  , k38  , k33  , k44  , k05 , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k40  , k30  , k20  , k10  , k00   }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k01  , k41  , k31  , k21  , k11   }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k12  , k02  , k42  , k32  , k22   }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k19  , k09  , k49  , k39  , k29   }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k210 , k110 , k010 , k410 , k310  }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k311 , k211 , k111 , k011 , k411  } \
}
