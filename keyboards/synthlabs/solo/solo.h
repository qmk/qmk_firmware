// Copyright 2022 Aaron Hong (@hongaaronc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define XXX KC_NO

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT_all( \
                   k00, k01, k02, k03, k04, k05, k06, \
    k10, k11, k12, \
                   k20, k21, k22, k23, k24, k25, k26 \
) { \
    { k00, k01, k02, k03, k04, k05, k06 }, \
    { k10, k11, k12, XXX, XXX, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26 } \
}

#define LAYOUT_left( \
                     k01, k03, k05, \
    k10, k11, k12, \
                   k20, k22, k24, k26 \
) { \
    { XXX, k01, XXX, k03, XXX, k05, XXX }, \
    { k10, k11, k12, XXX, XXX, XXX, XXX }, \
    { k20, XXX, k22, XXX, k24, XXX, k26 } \
}

#define LAYOUT_right( \
      k25, k23, k21, \
                       k10, k11, k12, \
    k06, k04, k02, k00 \
) { \
    { k00, XXX, k02, XXX, k04, XXX, k06 }, \
    { k10, k11, k12, XXX, XXX, XXX, XXX }, \
    { XXX, k21, XXX, k23, XXX, k25, XXX } \
}
