// Copyright 2022 Marko Skakun <skakun.marko@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LAYOUT_3x5_5(\
    L10, L11, L12, L13, L14,                      R14, R13, R12, R11, R10, \
    L20, L21, L22, L23, L24,                      R24, R23, R22, R21, R20, \
    L30, L31, L32, L33, L34,                      R34, R33, R32, R31, R30, \
                        L00, L01,            R01, R00,                     \
                        L04, L03, L02,  R02, R03, R04                      \
    )\
    {\
        { L34, L33, L32, L31, L30 },     \
        { L24, L23, L22, L21, L20 },     \
        { L14, L13, L12, L11, L10 },     \
        { L04, L03, L02, L01, L00 },     \
\
        { R34, R33, R32, R31, R30 },    \
        { R24, R23, R22, R21, R20 },    \
        { R14, R13, R12, R11, R10 },    \
        { R04, R03, R02, R01, R00 },    \
}
