// Copyright 2022 Lalit Mistry (@schwarzer-geiger)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#define LAYOUT_jakob33( \
    k16,      k26, \
    k00, k01, k02, k03, k04, k05, k06, \
    k10, k11, k12, k13, k14, k15, \
    k20, k21, k22, k23, k24, k25, \
    k30, k31, k32, k33, k34, k35, k36, \
    k40, k41, k42, k43, k44 \
) { \
    { k00, k01, k02, k03, k04, k05,   k06 }, \
    { k10, k11, k12, k13, k14, k15,   k16 }, \
    { k20, k21, k22, k23, k24, k25,   k26 }, \
    { k30, k31, k32, k33, k34, k35,   k36 }, \
    { k40, k41, k42, k43, k44, KC_NO, KC_NO } \
}
