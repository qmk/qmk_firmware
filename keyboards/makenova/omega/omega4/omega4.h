// Copyright 2022 makenova (@makenova)
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
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, \
    K30, K31,                K35,           K38, K39 \
){ \
    { K00, K01, K02,   K03,   K04,   K05, K06,   K07,   K08, K09 }, \
    { K10, K11, K12,   K13,   K14,   K15, K16,   K17,   K18, K19 }, \
    { K20, K21, K22,   K23,   K24,   K25, K26,   K27,   K28, K29 }, \
    { K30, K31, KC_NO, KC_NO, KC_NO, K35, KC_NO, KC_NO, K38, K39 } \
}

#define LAYOUT_6u_bar( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, \
    K30,                     K35,                K39 \
){ \
    { K00,   K01,   K02,   K03,   K04,   K05, K06,   K07,   K08,   K09 }, \
    { K10,   K11,   K12,   K13,   K14,   K15, K16,   K17,   K18,   K19 }, \
    { K20,   K21,   K22,   K23,   K24,   K25, K26,   K27,   K28,   K29 }, \
    { K30,   KC_NO, KC_NO, KC_NO, KC_NO, K35, KC_NO, KC_NO, KC_NO, K39 } \
}

#define LAYOUT_10u_bar( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, \
                             K35                      \
){ \
    { K00,   K01,   K02,   K03,   K04,   K05, K06,   K07,   K08,   K09 }, \
    { K10,   K11,   K12,   K13,   K14,   K15, K16,   K17,   K18,   K19 }, \
    { K20,   K21,   K22,   K23,   K24,   K25, K26,   K27,   K28,   K29 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K35, KC_NO, KC_NO, KC_NO, KC_NO } \
}
