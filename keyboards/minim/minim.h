#pragma once

#include "quantum.h"

#define LAYOUT( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, \
    K10, K11, K12, K13, K14, K15, K16,      K18, K19, K1A, K1B, K1C, K1D, \
    K20,      K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2D, \
         K31, K32,      K34,           K37,      K39,      K3B, K3C       \
) \
{ \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   KC_NO, K18,   K19,   K1A,   K1B,   K1C,   K1D   }, \
    { K20,   KC_NO, K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   KC_NO, K2D   }, \
    { KC_NO, K31,   K32,   KC_NO, K34,   KC_NO, KC_NO, K37,   KC_NO, K39,   KC_NO, K3B,   K3C,   KC_NO }  \
}
