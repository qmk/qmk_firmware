#ifndef MF68_H
#define MF68_H

#include "quantum.h"

#define LAYOUT( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K10, K11, K12, K13, K14,     K15, K16, \
    K17, K18, K20, K21, K22, K23, K24, K25, K26, K27, K28, K30, K31, K32,     K33, K34, \
    K35,  K36, K37, K38, K40, K41, K42, K43, K44, K45, K46, K47,     K48, \
    K50,   K51, K52, K53, K54, K55, K56, K57, K58, K60, K61,    K62,          K63, \
    K64,  K65,  K66,                 K67,              K68,  K70,  K71,  K72, K73, K74 \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08 }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18 }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28 }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38 }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48 }, \
    { K50, K51, K52, K53, K54, K55, K56, K57, K58 }, \
    { K60, K61, K62, K63, K64, K65, K66, K67, K68 }, \
    { K70, K71, K72, K73, K74 } \
}

#define LAYOUT_kc( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K10, K11, K12, K13, K14,     K15, K16, \
    K17, K18, K20, K21, K22, K23, K24, K25, K26, K27, K28, K30, K31, K32,     K33, K34, \
    K35,  K36, K37, K38, K40, K41, K42, K43, K44, K45, K46, K47,     K48, \
    K50,   K51, K52, K53, K54, K55, K56, K57, K58, K60, K61,    K62,          K63, \
    K64,  K65,  K66,                 K67,              K68,  K70,  K71,  K72, K73, K74 \
) LAYOUT( \
    KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07, KC_##K08, \
    KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17, KC_##K18, \
    KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27, KC_##K28, \
    KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37, KC_##K38, \
    KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_##K47, KC_##K48, \
    KC_##K50, KC_##K51, KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57, KC_##K58, \
    KC_##K60, KC_##K61, KC_##K62, KC_##K63, KC_##K64, KC_##K65, KC_##K66, KC_##K67, KC_##K68, \
    KC_##K70, KC_##K71, KC_##K72, KC_##K73, KC_##K74 \
)

#endif
