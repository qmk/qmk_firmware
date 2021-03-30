
#pragma once

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT_tkl_ansi_wkl( \
     K00,      K01, KB1, K02, KB2, K03, KB3, K04, KB4, KB5, K06, KB6, K07,  KB7, K08, KB8, \
     K10, KA0, K11, KA1, K12, KA2, K13, KA3, K14, KA4, K15, KA5, K16, KA6,  KA7, K18, KA8, \
     K20, K90, K21, K91, K22, K92, K23, K93, K24, K94, K25, K95, K26, K96,  K97, K28, K98, \
     K30, K80, K31, K81, K32, K82, K33, K83, K34, K84, K35, K85,      K86, \
     K40, K70, K41, K71, K42, K72, K43, K73, K44, K74, K45,      K46,            K48, \
     K50,      K51,           K62,                          K55,      K56,  K67, K58, K68  \
) \
{ \
    { K00,   K01,   K02,   K03,   K04,   KC_NO, K06,   K07,   K08,   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   KC_NO, K18,   }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   KC_NO, K28,   }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   KC_NO, KC_NO, KC_NO, }, \
    { K40,   K41,   K42,   K43,   K44,   K45,   K46,   KC_NO, K48,   }, \
    { K50,   K51,   KC_NO, KC_NO, KC_NO, K55,   K56,   KC_NO, K58,   }, \
    { KC_NO, KC_NO, K62,   KC_NO, KC_NO, KC_NO, KC_NO, K67,   K68,   }, \
    { K70,   K71,   K72,   K73,   K74,   KC_NO, KC_NO, KC_NO, KC_NO, }, \
    { K80,   K81,   K82,   K83,   K84,   K85,   K86,   KC_NO, KC_NO, }, \
    { K90,   K91,   K92,   K93,   K94,   K95,   K96,   K97,   K98,   }, \
    { KA0,   KA1,   KA2,   KA3,   KA4,   KA5,   KA6,   KA7,   KA8,   }, \
    { KC_NO, KB1,   KB2,   KB3,   KB4,   KB5,   KB6,   KB7,   KB8,   }, \
}
