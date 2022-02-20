// Copyright 2022 Lalit Mistry (@schwarzer-geiger)
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
#define LAYOUT_edinburgh41( \
    K00, K01, K02, K03, K04, K05,      K30, K31, K32, K33, K34, K35, \
    K10, K11, K12, K13, K14, K15,      K40, K41, K42, K43, K44, K45, \
    K20, K21, K22, K23, K24, K25,      K50, K51, K52, K53, K54, K55, \
                        K60, K61, K62, K63, K64 \
) \
{ \
    { K00, K01, K02, K03, K04, K05 }, \
    { K10, K11, K12, K13, K14, K15 }, \
    { K20, K21, K22, K23, K24, K25 }, \
    { K30, K31, K32, K33, K34, K35 }, \
    { K40, K41, K42, K43, K44, K45 }, \
    { K50, K51, K52, K53, K54, K55 }, \
    { K60, K61, K62, K63, K64, KC_NO } \
}
