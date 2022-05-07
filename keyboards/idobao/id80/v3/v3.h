// Copyright 2022 peepeetee (@peepeetee)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LAYOUT( \
    K50,  K51, K52, K53, K54,  K55, K56, K57, K58,  KA7, KA5, KA4, KA3,   KA6,  KA2,  \
    K40, K41, K42, K43, K44, K45, K46, K47, K48, K98, K97, K95, K94, K96,       K92,  \
    K30,   K31, K32, K33, K34, K35, K36, K37, K38, K88, K87, K85, K84, K83,     K82,  \
    K20,    K21, K22, K23, K24, K25, K26, K27, K28, K78, K77, K75, K74,               \
    K10,       K12, K13, K14, K15, K16, K17, K18, K68, K67, K65, K64,      K63,       \
    K00,  K01,  K02,              K06,                K08,   K07,     K05, K04, K03   \
) { \
    { K00,   K10,   K20,   K30,   K40,   K50,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { K01,   KC_NO, K21,   K31,   K41,   K51,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { K02,   K12,   K22,   K32,   K42,   K52,   KC_NO, KC_NO, K82,   K92,   KA2   }, \
    { K03,   K13,   K23,   K33,   K43,   K53,   K63,   KC_NO, K83,   KC_NO, KA3   }, \
    { K04,   K14,   K24,   K34,   K44,   K54,   K64,   K74,   K84,   K94,   KA4   }, \
    { K05,   K15,   K25,   K35,   K45,   K55,   K65,   K75,   K85,   K95,   KA5   }, \
    { K06,   K16,   K26,   K36,   K46,   K56,   KC_NO, KC_NO, KC_NO, K96,   KA6   }, \
    { K07,   K17,   K27,   K37,   K47,   K57,   K67,   K77,   K87,   K97,   KA7   }, \
    { K08,   K18,   K28,   K38,   K48,   K58,   K68,   K78,   K88,   K98,   KC_NO }, \
}
