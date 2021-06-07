#pragma once

#include "quantum.h"

#define LAYOUT_default_split( \
    K00, K01, K02, K03,   K04,   K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, K0G, K0H, K0I,  \
    K10, K11, K12, K13,   K14,   K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H, K1I,  \
    K20, K21, K22, K23,   K24,   K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H,       \
    K30, K31, K32, K33,   K34,   K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E, K3F, K3G,      K3H,  \
         K41, K42,   K43, K44, K45,   K46, K47,                K4B,                     K4G, K4H, K4I   \
) { \
    {    K00, K01, K02, K03,   K04,   K05,   K06,  K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D,   K0E,   K0F,   K0G,   K0H,    K0I,  }, \
    {    K10, K11, K12, K13,   K14,   K15,   K16,  K17,   K18,   K19,   K1A,   K1B,   K1C,   K1D,   K1E,   K1F,   K1G,   K1H,    K1I,  }, \
    {    K20, K21, K22, K23,   K24,   K25,   K26,  K27,   K28,   K29,   K2A,   K2B,   K2C,   K2D,   K2E,   K2F,   K2G,   K2H,  KC_NO,  }, \
    {    K30, K31, K32, K33,   K34,   K35, KC_NO,  K37,   K38,   K39,   K3A,   K3B,   K3C,   K3D,   K3E,   K3F,   K3G, KC_NO,    K3H,  }, \
    {  KC_NO, K41, K42,   K43, K44, K45,     K46,  K47, KC_NO, KC_NO, KC_NO,   K4B, KC_NO, KC_NO, KC_NO, KC_NO,   K4G,   K4H,    K4I   }  \
}
