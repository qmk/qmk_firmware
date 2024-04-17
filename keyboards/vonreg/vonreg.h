// Copyright 2022 Tompi
// SPDX-License-Identifier: MIT

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

// readability
#define ___ KC_NO

#define LAYOUT_split_3x5_3( \
        L01, L02, L03, L04, L05, R05, R04, R03, R02, R01, \
        L06, L07, L08, L09, L10, R10, R09, R08, R07, R06, \
        L11, L12, L13, L14, L15, R15, R14, R13, R12, R11, \
                  L16, L17, L18, R18, R17, R16                 \
    ) \
    { \
        { L01, L02, L03, L04, L05 }, \
        { L06, L07, L08, L09, L10 }, \
        { L11, L12, L13, L14, L15 }, \
        { L16, L17, L18, ___, ___ }, \
        { R01, R02, R03, R04, R05 }, \
        { R06, R07, R08, R09, R10 }, \
        { R11, R12, R13, R14, R15 }, \
        { R16, R17, R18, ___, ___ }  \
    }
