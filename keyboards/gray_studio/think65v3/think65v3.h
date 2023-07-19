// Copyright 2023 Yizhen Liu (@edwardslau)
// SPDX-License-Identifier: GPL-2.0
#pragma once

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the Keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, \
    K10,      K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, \
    K20,      K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,           \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3D,      K3E,      \
    K40, K41, K42,                     K47,           K4A, K4B,      K4D, K4E, K4F  \
) \
{ \
    { K00, K01,   K02,   K03, K04,   K05, K06,   K07, K08, K09,   K0A, K0B, K0C,   K0D, K0E,   K0F }, \
    { K10, KC_NO, K12,   K13, K14,   K15, K16,   K17, K18, K19,   K1A, K1B, K1C,   K1D, K1E,   K1F }, \
    { K20, KC_NO, K22,   K23, K24,   K25, K26,   K27, K28, K29,   K2A, K2B, K2C,   K2D, KC_NO, KC_NO }, \
    { K30, K31,   K32,   K33, K34,   K35, K36,   K37, K38, K39,   K3A, K3B, KC_NO, K3D, K3E,   KC_NO }, \
    { K40, K41,   K42, KC_NO,   KC_NO,KC_NO,KC_NO, K47,KC_NO, KC_NO,K4A, K4B, KC_NO, K4D, K4E,   K4F }, \
}

#define LAYOUT_65_blocker( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D,      K0F, \
    K10,      K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, \
    K20,      K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,           \
    K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3D,      K3E,      \
    K40, K41, K42,                     K47,           K4A, K4B,      K4D, K4E, K4F  \
) \
{ \
    { K00, K01,   K02,   K03, K04,   K05,   K06,   K07, K08,   K09,   K0A, K0B, K0C,   K0D,   KC_NO, K0F }, \
    { K10, KC_NO, K12,   K13, K14,   K15,   K16,   K17, K18,   K19,   K1A, K1B, K1C,   K1D,   K1E,   K1F }, \
    { K20, KC_NO, K22,   K23, K24,   K25,   K26,   K27, K28,   K29,   K2A, K2B, K2C,   K2D,   KC_NO, KC_NO }, \
    { K30, KC_NO, K32,   K33, K34,   K35,   K36,   K37, K38,   K39,   K3A, K3B, KC_NO, K3D,   K3E,   KC_NO }, \
    { K40, K41,   K42, KC_NO, KC_NO, KC_NO, KC_NO, K47, KC_NO, KC_NO, K4A, K4B, KC_NO, K4D,   K4E,   K4F }, \
}

#define LAYOUT_65_iso_blocker( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,    K0D,   K0F,   \
    K10,   K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,         K1F,   \
    K20,    K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K1E, K2D,          \
    K30,  K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3D,     K3E,        \
    K40,  K41,  K42,                    K47,           K4A,  K4B,     K4D, K4E, K4F    \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D,   KC_NO, K0F   }, \
    { K10,   KC_NO, K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   K1D,   K1E,   K1F   }, \
    { K20,   KC_NO, K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   K2C,   K2D,   KC_NO, KC_NO }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   KC_NO, K3D,   K3E,   KC_NO }, \
    { K40,   K41,   K42, KC_NO,   KC_NO, KC_NO, KC_NO, K47,   KC_NO, KC_NO, K4A,   K4B,   KC_NO, K4D,   K4E,   K4F   }, \
}
