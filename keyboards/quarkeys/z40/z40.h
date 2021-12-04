// Copyright 2021 Trent Hoh (@Trent Hoh)
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
#define LAYOUT_ortho_4x12_1x2uC( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B,   \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B,   \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,   \
    K30, K31, K32, K33, K34,    K35,   K37, K38, K39, K3A, K3B    \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B   }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B   }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   KC_NO, K37,   K38,   K39,   K3A,   K3B   }, \
}
