// Copyright 2022 Charue Design
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LAYOUT_all( \
    k00, k01,   k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k1g, \
    k10, k11,    k12,   k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e,  k1f,  k2f, \
    k20, k21,     k22,   k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,    k2e,    k3f, \
    k30, k31,    k32,  k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,   k3e,  k3g, k4g, \
    k40, k41,    k42,   k43,   k44,   k45,   k47,      k4a,  k4c,                k4d, k4e, k4f  \
) { \
    { k00, k01, k02, k03, k04, k05, k06,   k07, k08,   k09,   k0a, k0b,   k0c, k0d, k0e, k0f, k0g   }, \
    { k10, k11, k12, k13, k14, k15, k16,   k17, k18,   k19,   k1a, k1b,   k1c, k1d, k1e, k1f, k1g   }, \
    { k20, k21, k22, k23, k24, k25, k26,   k27, k28,   k29,   k2a, k2b,   k2c, k2d, k2e, k2f, KC_NO }, \
    { k30, k31, k32, k33, k34, k35, k36,   k37, k38,   k39,   k3a, k3b,   k3c, k3d, k3e, k3f, k3g   }, \
    { k40, k41, k42, k43, k44, k45, KC_NO, k47, KC_NO, KC_NO, k4a, KC_NO, k4c, k4d, k4e, k4f, k4g   }  \
}
