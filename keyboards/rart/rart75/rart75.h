
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
#define LAYOUT_all( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08,      K0A, K0B, K0C, K0D, K0E, K0F, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,      K2F, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,           K3F, \
    K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B,           K4E, K4F, \
    K50, K51, K52, K53, K54,           K57, K58, K59, K5A, K5B,           K5E, K5F  \
) \
{ \
    { K00, K01, K02, K03, K04, K05,   K06,   K07, K08,   KC_NO, K0A, K0B, K0C,   K0D,   K0E,   K0F }, \
    { K10, K11, K12, K13, K14, K15,   K16,   K17, K18,   K19,   K1A, K1B, K1C,   K1D,   K1E,   K1F }, \
    { K20, K21, K22, K23, K24, K25,   K26,   K27, K28,   K29,   K2A, K2B, K2C,   K2D,   KC_NO, K2F }, \
    { K30, K31, K32, K33, K34, K35,   K36,   K37, K38,   K39,   K3A, K3B, K3C,   KC_NO, KC_NO, K3F }, \
    { K40, K41, K42, K43, K44, K45,   K46,   K47, K48,   K49,   K4A, K4B, KC_NO, KC_NO, K4E,   K4F }, \
    { K50, K51, K52, K53, K54, KC_NO, KC_NO, K57, K58,   K59,   K5A, K5B, KC_NO, KC_NO, K5E,   K5F }, \
}

#define LAYOUT_ansi( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08,      K0A, K0B, K0C, K0D, K0E, K0F, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,      K1F, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,      K2F, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,           K3F, \
    K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B,           K4E, K4F, \
    K50, K51, K52,      K54,                K58, K59, K5A, K5B,           K5E, K5F  \
) \
{ \
    { K00, K01, K02, K03,   K04, K05,   K06,   K07,   K08,   KC_NO, K0A, K0B, K0C,   K0D,   K0E,   K0F }, \
    { K10, K11, K12, K13,   K14, K15,   K16,   K17,   K18,   K19,   K1A, K1B, K1C,   K1D,   KC_NO, K1F }, \
    { K20, K21, K22, K23,   K24, K25,   K26,   K27,   K28,   K29,   K2A, K2B, K2C,   K2D,   KC_NO, K2F }, \
    { K30, K31, K32, K33,   K34, K35,   K36,   K37,   K38,   K39,   K3A, K3B, K3C,   KC_NO, KC_NO, K3F }, \
    { K40, K41, K42, K43,   K44, K45,   K46,   K47,   K48,   K49,   K4A, K4B, KC_NO, KC_NO, K4E,   K4F }, \
    { K50, K51, K52, KC_NO, K54, KC_NO, KC_NO, KC_NO, K58,   K59,   K5A, K5B, KC_NO, KC_NO, K5E,   K5F }, \
}
