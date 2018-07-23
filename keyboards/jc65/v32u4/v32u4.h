#ifndef V32U4_H
#define V32U4_H

#include "quantum.h"

#define KEYMAP( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, \
    K10, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, \
    K20, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2F, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3D, K3E, K3F, \
    K40,  K41,  K43,    K44,      K46,      K48,      K4A, K4B, K4C, K4D, K4E, K4F \
)\
{\
  {K00, K01,   K02,   K03, K04, K05,   K06, K07,   K08, K09,   K0A, K0B, K0C,   K0D, K0E,   K0F}, \
  {K10, KC_NO, K12,   K13, K14, K15,   K16, K17,   K18, K19,   K1A, K1B, K1C,   K1D, K1E,   K1F}, \
  {K20, KC_NO, K22,   K23, K24, K25,   K26, K27,   K28, K29,   K2A, K2B, K2C,   K2D, KC_NO, K2F}, \
  {K30, K31,   K32,   K33, K34, K35,   K36, K37,   K38, K39,   K3A, K3B, KC_NO, K3D, K3E,   K3F}, \
  {K40, K41,   KC_NO, K43, K44, KC_NO, K46, KC_NO, K48, KC_NO, K4A, K4B, K4C,   K4D, K4E,   K4F}, \
}

#endif
