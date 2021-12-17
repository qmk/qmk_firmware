// Copyright 2021 torbjorn rasmusson (@torbjorn rasmusson)
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

#define LAYOUT( \
      k00, k01, k02, k03, k04, k05, \
      k10, k11, k12, k13, k14, k15, \
      k20, k21, k22, k23, k24, k25, \
                     k33, k34, k35, \
\
      k0B, k0A, k09, k08, k07, k06, \
      k1B, k1A, k19, k18, k17, k16, \
      k2B, k2A, k29, k28, k27, k26, \
      k36, k37, k38 ) \
 { \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, k15 }, \
    { k20, k21, k22, k23, k24, k25 }, \
    { XXX, XXX, XXX, k33, k34, k35 }, \
    { k06, k07, k08, k09, k0A, k0B }, \
    { k16, k17, k18, k19, k1A, k1B }, \
    { k26, k27, k28, k29, k2A, k2B }, \
    { XXX, XXX, XXX, k38, k37, k36 }  \
}
