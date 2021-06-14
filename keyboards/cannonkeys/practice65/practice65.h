#pragma once

#include "quantum.h"

#define KNO KC_NO

#define LAYOUT_default( \
  K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, \
  K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,      K1F, \
  K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2D,      K2F, \
  K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D,      K3F, \
  K40, K41,  K42,               K46,           K49, K4A, K4B, K4C, K4D,      K4F \
) { \
  {  K00,  K01,  K02,  K03,  K04,    K05,    K06,    K07,    K08,    K09,  K0A,  K0B,  K0C,    K0D,   K0E,    K0F }, \
  {  K10,  K11,  K12,  K13,  K14,    K15,    K16,    K17,    K18,    K19,  K1A,  K1B,  K1C,    K1D,   KC_NO ,  K1F }, \
  {  K20,  K21,  K22,  K23,  K24,    K25,    K26,    K27,    K28,    K29,  K2A,  K2B,  KC_NO,  K2D,   KC_NO,  K2F  }, \
  {  K30,  KNO,  K32,  K33,  K34,    K35,    K36,    K37,    K38,    K39,  K3A,  K3B,  K3C,    K3D,   KC_NO,  K3F  }, \
  {  K40,  K41,  K42,  KNO,  KC_NO,  KC_NO,  K46,    KC_NO,  KC_NO,  K49,  K4A,  K4B,  K4C,    K4D,   KC_NO,  K4F  }  \
}
