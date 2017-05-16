#ifndef GENOVATION_PLUM_92_TEENSY_LC_H
#define GENOVATION_PLUM_92_TEENSY_LC_H

#include "quantum.h"

#define KEYMAP( \
    K00, K01, K02, K13, K04, K05, K06, K16, K07, K08, K09, K1A, K0B, K0C, K1E, K7E, \
    K20, K11, K12, K23, K24, K15, K25, K26, K17, K18, K19, K2A, K1B, K1C, K2D, K3E, \
    K30, K21, K22, K33, K34, K35, K45, K36, K27, K28, K39, K3A, K3B, K3C, K3D, K4E, \
    K40, K41, K42, K43, K44, K54, K55, K46, K57, K48, K49, K4A, K5B, K4C, K4D, K5E, \
    K50, K61, K62, K53, K64, K74, K65, K56, K67, K58, K59, K5A, K6B, K5C, K5D, K6E, \
    K60, K71, K72,      K73,           K77,      K68, K79, K6A, K7B, K7C, K6D, K7D \
) /* scan layout*/ { \
    { KC_##K00, KC_##K01, KC_##K02, KC_NO,    KC_##K04, KC_##K05, KC_##K06, KC_##K07, KC_##K08, KC_##K09, KC_NO,    KC_##K0B, KC_##K0C, KC_NO,    KC_NO,    KC_NO,   }, \
    { KC_NO,    KC_##K11, KC_##K12, KC_##K13, KC_NO,    KC_##K15, KC_##K16, KC_##K17, KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_NO,    KC_##K1E, KC_NO,   }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27, KC_##K28, KC_NO,    KC_##K2A, KC_NO,    KC_NO,    KC_##K2D, KC_NO,    KC_NO,   }, \
    { KC_##K30, KC_NO,    KC_NO,    KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_NO,    KC_NO,    KC_##K39, KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_NO,   }, \
    { KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_NO,    KC_##K48, KC_##K49, KC_##K4A, KC_NO,    KC_##K4C, KC_##K4D, KC_##K4E, KC_NO,   }, \
    { KC_##K50, KC_NO,    KC_NO,    KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57, KC_##K58, KC_##K59, KC_##K5A, KC_##K5B, KC_##K5C, KC_##K5D, KC_##K5E, KC_NO,   }, \
    { KC_NO,    KC_##K61, KC_##K62, KC_NO,    KC_##K64, KC_##K65, KC_NO,    KC_##K67, KC_##K68, KC_NO,    KC_##K6A, KC_##K6B, KC_NO,    KC_##K6D, KC_##K6E, KC_##K60,}, \
    { KC_NO,    KC_##K71, KC_##K72, KC_##K73, KC_##K74, KC_NO,    KC_NO,    KC_##K77, KC_NO,    KC_##K79, KC_NO,    KC_##K7B, KC_##K7C, KC_##K7D, KC_##K7E, KC_NO    } \
}

#endif

/*
Original keymap

#define KEYMAP( \
    K00, K01, K02, K13, K04, K05, K06, K16, K07, K08, K09, K1A, K0B, K0C, K1E, K7E, \
    K20, K11, K12, K23, K24, K15, K25, K26, K17, K18, K19, K2A, K1B, K1C, K2D, K3E, \
    K30, K21, K22, K33, K34, K35, K45, K36, K27, K28, K39, K3A, K3B, K3C, K3D, K4E, \
    K40, K41, K42, K43, K44, K54, K55, K46, K57, K48, K49, K4A, K5B, K4C, K4D, K5E, \
    K50, K61, K62, K53, K64, K74, K65, K56, K67, K58, K59, K5A, K6B, K5C, K5D, K6E, \
    K60, K71, K72,      K73,           K77,      K68, K79, K6A, K7B, K7C, K6D, K7D \
) { \
    { KC_##K00, KC_##K01, KC_##K02, KC_NO,    KC_##K04, KC_##K05, KC_##K06, KC_##K07, KC_##K08, KC_##K09, KC_NO,    KC_##K0B, KC_##K0C, KC_NO,    KC_NO    }, \
    { KC_NO,    KC_##K11, KC_##K12, KC_##K13, KC_NO,    KC_##K15, KC_##K16, KC_##K17, KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_NO,    KC_##K1E }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27, KC_##K28, KC_NO,    KC_##K2A, KC_NO,    KC_NO,    KC_##K2D, KC_NO    }, \
    { KC_##K30, KC_NO,    KC_NO,    KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_NO,    KC_NO,    KC_##K39, KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E }, \
    { KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_NO,    KC_##K48, KC_##K49, KC_##K4A, KC_NO,    KC_##K4C, KC_##K4D, KC_##K4E }, \
    { KC_##K50, KC_NO,    KC_NO,    KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57, KC_##K58, KC_##K59, KC_##K5A, KC_##K5B, KC_##K5C, KC_##K5D, KC_##K5E }, \
    { KC_##K60, KC_##K61, KC_##K62, KC_NO,    KC_##K64, KC_##K65, KC_NO,    KC_##K67, KC_##K68, KC_NO,    KC_##K6A, KC_##K6B, KC_NO,    KC_##K6D, KC_##K6E }, \
    { KC_NO,    KC_##K71, KC_##K72, KC_##K73, KC_##K74, KC_NO,    KC_NO,    KC_##K77, KC_NO,    KC_##K79, KC_NO,    KC_##K7B, KC_##K7C, KC_##K7D, KC_##K7E } \
}
*/