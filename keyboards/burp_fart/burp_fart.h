// Copyright 2022 Namit Nathwani (@namsnath)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

// readability
#define ___ KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT_split_3x5_3( \
    L20,    L21,    L22,    L23,    L24,                        R24,    R23,    R22,    R21,    R20,    \
    L10,    L11,    L12,    L13,    L14,                        R14,    R13,    R12,    R11,    R10,    \
    L00,    L01,    L02,    L03,    L04,                        R04,    R03,    R02,    R01,    R00,    \
                    LT3,    LT2,    LT1,                        RT1,    RT2,    RT3                     \
) { \
    { L20, L21, L22, L23, L24 }, \
    { L10, L11, L12, L13, L14 }, \
    { L00, L01, L02, L03, L04 }, \
    { LT3, LT2, LT1, ___, ___ }, \
    { R20, R21, R22, R23, R24 }, \
    { R10, R11, R12, R13, R14 }, \
    { R00, R01, R02, R03, R04 }, \
    { RT3, RT2, RT1, ___, ___ }  \
}

#define LAYOUT_split_3x5_3_encoder( \
    L20,    L21,    L22,    L23,    L24,                        R24,    R23,    R22,    R21,    R20,    \
    L10,    L11,    L12,    L13,    L14,                        R14,    R13,    R12,    R11,    R10,    \
    L00,    L01,    L02,    L03,    L04,    LE,        RE,      R04,    R03,    R02,    R01,    R00,    \
                    LT3,    LT2,    LT1,                        RT1,    RT2,    RT3                     \
) { \
    { L20, L21, L22, L23, L24 }, \
    { L10, L11, L12, L13, L14 }, \
    { L00, L01, L02, L03, L04 }, \
    { LT3, LT2, LT1, LE, ___  }, \
    { R20, R21, R22, R23, R24 }, \
    { R10, R11, R12, R13, R14 }, \
    { R00, R01, R02, R03, R04 }, \
    { RT3, RT2, RT1, RE, ___  }  \
}
