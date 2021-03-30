#pragma once

#include "quantum.h"

#define LAYOUT_JP(                                                             \
    K02, K32, K62, K22, K12, K52, K72, KA2, K92, K82, KB2, KE2, KF2, KD2, KC2, \
    K03, K63, K23, K13, K53, K73, KA3, K93, K83, KB3, KE3, KF3, KD3,           \
    K06, K66, K26, K16, K56, K76, KA6, K96, K86, KB6, KE6, KF6, KD6, KC6,      \
    K05, K65, K25, K15, K55, K75, KA5, K95, K85, KB5, KE5, KF5, KD5, KC5,      \
    K04, K34, K64, K24, K14,      K74,      K94, K84, KB4, KE4, KF4, KD4, KC4) \
{                                                                              \
    { KC_NO, KC_NO, K02,   K03,   K04,   K05,   K06,   KC_NO },                \
    { KC_NO, KC_NO, K12,   K13,   K14,   K15,   K16,   KC_NO },                \
    { KC_NO, KC_NO, K22,   K23,   K24,   K25,   K26,   KC_NO },                \
    { KC_NO, KC_NO, K32,   KC_NO, K34,   KC_NO, KC_NO, KC_NO },                \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },                \
    { KC_NO, KC_NO, K52,   K53,   KC_NO, K55,   K56,   KC_NO },                \
    { KC_NO, KC_NO, K62,   K63,   K64,   K65,   K66,   KC_NO },                \
    { KC_NO, KC_NO, K72,   K73,   K74,   K75,   K76,   KC_NO },                \
    { KC_NO, KC_NO, K82,   K83,   K84,   K85,   K86,   KC_NO },                \
    { KC_NO, KC_NO, K92,   K93,   K94,   K95,   K96,   KC_NO },                \
    { KC_NO, KC_NO, KA2,   KA3,   KC_NO, KA5,   KA6,   KC_NO },                \
    { KC_NO, KC_NO, KB2,   KB3,   KB4,   KB5,   KB6,   KC_NO },                \
    { KC_NO, KC_NO, KC2,   KC_NO, KC4,   KC5,   KC6,   KC_NO },                \
    { KC_NO, KC_NO, KD2,   KD3,   KD4,   KD5,   KD6,   KC_NO },                \
    { KC_NO, KC_NO, KE2,   KE3,   KE4,   KE5,   KE6,   KC_NO },                \
    { KC_NO, KC_NO, KF2,   KF3,   KF4,   KF5,   KF6,   KC_NO }                 \
}
