#ifndef HHKB_H
#define HHKB_H

#include "quantum.h"

#define LAYOUT(                                                                \
    K31, K30, K00, K10, K11, K20, K21, K40, K41, K60, K61, K70, K71, K50, K51, \
    K32, K01, K02, K13, K12, K23, K22, K42, K43, K62, K63, K73, K72, K52,      \
    K33, K04, K03, K14, K15, K24, K25, K45, K44, K65, K64, K74, K53,           \
    K34, K05, K06, K07, K16, K17, K26, K46, K66, K76, K75, K55, K54,           \
         K35, K36,           K37,                K57, K56)                     \
                                                                               \
{                                                                              \
    { K00, K01, K02, K03, K04, K05, K06, K07   },                              \
    { K10, K11, K12, K13, K14, K15, K16, K17   },                              \
    { K20, K21, K22, K23, K24, K25, K26, KC_NO },                              \
    { K30, K31, K32, K33, K34, K35, K36, K37   },                              \
    { K40, K41, K42, K43, K44, K45, K46, KC_NO },                              \
    { K50, K51, K52, K53, K54, K55, K56, K57   },                              \
    { K60, K61, K62, K63, K64, K65, K66, KC_NO },                              \
    { K70, K71, K72, K73, K74, K75, K76, KC_NO }                               \
}

#define LAYOUT_60_hhkb LAYOUT

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


#endif
