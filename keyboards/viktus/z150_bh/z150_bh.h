#pragma once

#include "quantum.h"

#define LAYOUT( \
    K00, K01,     K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F,     K0G,   K0H, K0J,    \
    K10, K11,     K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F,     K1G, K1H, K1I, K1J, \
    K20, K21,     K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,               K2F, K2G, K2H, K2I, \
    K30, K31,     K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E,          K3F, K3G, K3H, K3I, \
    K40, K41,     K42, K43,                K47,                                 K4E,          K4F,      K4H     \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D,   K0E,   K0F,   K0G,   K0H,   KC_NO, K0J   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   K1D,   K1E,   K1F,   K1G,   K1H,   K1I,   K1J   }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   K2C,   K2D,   KC_NO, K2F,   K2G,   K2H,   K2I,   KC_NO }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   K3D,   K3E,   K3F,   K3G,   K3H,   K3I,   KC_NO }, \
    { K40,   K41,   K42,   K43,   KC_NO, KC_NO, KC_NO, K47,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K4E,   K4F,   KC_NO, K4H,   KC_NO, KC_NO }  \
}

#define LAYOUT_z150_tkl( \
    K00, K01,     K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F,     K0H, K0I, K0J, \
    K10, K11,     K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F,     K1H, K1I, K1J, \
    K20, K21,     K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E,          K2G, K2H, K2I, \
    K30, K31,     K32, K45, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E,     K3G, K3H, K3I, \
    K40, K41,     K42, K43, K44,                K47,                K4C, K4D, K4E, K4F,     K4G, K4H, K4I  \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D,   K0E,   K0F,   KC_NO, K0H,   K0I,   K0J   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   K1D,   K1E,   K1F,   KC_NO, K1H,   K1I,   K1J   }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   K2C,   K2D,   K2E,   KC_NO, K2G,   K2H,   K2I,   KC_NO }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   K3D,   K3E,   KC_NO, K3G,   K3H,   K3I,   KC_NO }, \
    { K40,   K41,   K42,   K43,   K44,   K45,   KC_NO, K47,   KC_NO, KC_NO, KC_NO, KC_NO, K4C,   K4D,   K4E,   K4F,   K4G,   K4H,   K4I,   KC_NO }  \
}
