// Copyright 2021 gtips (@gtips)
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
              K02, K03, K04, K05, K06, K07, K40, K41, K42, K43,  \
    K10, K11, K12, K13, K14, K15, K16, K17, K44, K45, K46, K47, \
    K20, K21, K22, K23, K24, K25, K26, K27, K50, K51, K52, K53, \
    K30, K31, K32, K33, K34, K35, K36, K37, K54, K55, K56,\
    K60, K61, K62, K63, K64, K65, K66, K67 \
) { \
    { KC_NO, KC_NO, K02,   K03,   K04,   K05,   K06,   K07 }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17 }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27 }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37 }, \
    { K40,   K41,   K42,   K43,   K44,   K45,   K46,   K47 }, \
    { K50,   K51,   K52,   K53,   K54,   K55,   K56,   KC_NO }, \
    { K60,   K61,   K62,   K63,   K64,   K65,   K66,   K67 } \
}
