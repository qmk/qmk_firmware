#pragma once

#include "quantum.h"

#define KNO KC_NO
#define LAYOUT_default LAYOUT_alice

#define LAYOUT_alice( \
  K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, \
  K10, K11, K12, K13, K14, K15, K16,      K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, \
  K20, K21, K22, K23, K24, K25, K26,      K28, K29, K2A, K2B, K2C, K2D,      K2F, \
       K31, K32, K33, K34, K35, K36,      K38, K39, K3A, K3B, K3C, K3D, K3E, K3F,         \
       K41,      K43, K44,      K46,           K49,      K4B,                K4F \
) { \
  {  K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F  }, \
  {  K10, K11, K12, K13, K14, K15, K16, KNO, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F  }, \
  {  K20, K21, K22, K23, K24, K25, K26, KNO, K28, K29, K2A, K2B, K2C, K2D, KNO, K2F  }, \
  {  KNO, K31, K32, K33, K34, K35, K36, KNO, K38, K39, K3A, K3B, K3C, K3D, K3E, K3F  }, \
  {  KNO, K41, KNO, K43, K44, KNO, K46, KNO, KNO, K49, KNO, K4B, KNO, KNO, KNO, K4F  }  \
}
