#ifndef GONNERD_H
#define GONNERD_H

#include "quantum.h"

#define KEYMAP_TKL( \
        K08,      K09, K18, K19, K28, K29, K38, K39, K48, K49, K58, K59, K68,    K69, K88, K89, \
        K00, K01, K10, K11, K20, K21, K30, K31, K40, K41, K50, K51, K60, K61,    K80, K81, K84, \
        K02, K03, K12, K13, K22, K23, K32, K33, K42, K43, K52, K53, K62, K63,    K82, K83, K85, \
        K04, K14, K15, K24, K25, K34, K35, K44, K45, K54, K55, K64, K71, K65,                   \
        K07, K79, K16, K17, K26, K27, K36, K37, K46, K47, K56, K57, K66, K67,         K86,      \
        K06, K05, K78,                K70,                K72, K73, K74, K75,    K76, K77, K87  \
) \
{ \
      {  K00, K10, K20, K30, K40, K50, K60, K70, K80 }, \
      {  K01, K11, K21, K31, K41, K51, K61, K71, K81 }, \
      {  K02, K12, K22, K32, K42, K52, K62, K72, K82 }, \
      {  K03, K13, K23, K33, K43, K53, K63, K73, K83 }, \
      {  K04, K14, K24, K34, K44, K54, K64, K74, K84 }, \
      {  K05, K15, K25, K35, K45, K55, K65, K75, K85 }, \
      {  K06, K16, K26, K36, K46, K56, K66, K76, K86 }, \
      {  K07, K17, K27, K37, K47, K57, K67, K77, K87 }, \
      {  K08, K18, K28, K38, K48, K58, K68, K78, K88 }, \
      {  K09, K19, K29, K39, K49, K59, K69, K79, K89 } \
}

#define KEYMAP_60( \
        K08, K01, K10, K11, K20, K21, K30, K31, K40, K41, K50, K51, K60, K61, \
        K02, K03, K12, K13, K22, K23, K32, K33, K42, K43, K52, K53, K62, K63, \
        K04, K14, K15, K24, K25, K34, K35, K44, K45, K54, K55, K64, K71, K65, \
        K07, K79, K16, K17, K26, K27, K36, K37, K46, K47, K56, K57, K66, K67, \
        K06, K05, K78,                K70,                K72, K73, K74, K75  \
) KEYMAP_TKL( \
        K08,          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,    KC_NO, KC_NO, KC_NO,  \
        KC_NO, K01,   K10,   K11,   K20,   K21,   K30,   K31,   K40,   K41,   K50,   K51,   K60,    K61,      KC_NO, KC_NO, KC_NO,  \
        K02,   K03,   K12,   K13,   K22,   K23,   K32,   K33,   K42,   K43,   K52,   K53,   K62,    K63,      KC_NO, KC_NO, KC_NO,  \
        K04,   K14,   K15,   K24,   K25,   K34,   K35,   K44,   K45,   K54,   K55,   K64,   K71,    K65,                            \
        K07,   K79,   K16,   K17,   K26,   K27,   K36,   K37,   K46,   K47,   K56,   K57,   K66,    K67,             KC_NO,         \
        K06,   K05,   K78,                        K70,                        K72,   K73,   K74,    K75,      KC_NO, KC_NO, KC_NO   \
)

#endif
