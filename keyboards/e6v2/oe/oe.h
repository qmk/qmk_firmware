#ifndef OE_H
#define OE_H

#include "quantum.h"

#define LAYOUT( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, \
     K10,  K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,  K1D,   \
      K20,  K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,  K2C,  K2D, \
    K30,  K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,  K3C,    K3D, \
    K40,  K41,  K42,                K46,                K4A,  K4B,  K4C,  K4D \
)\
{\
  { K00, K01, K02, K03,   K04,   K05,   K06, K07,   K08,   K09,   K0A, K0B, K0C, K0D, K0E   }, \
  { K10, K11, K12, K13,   K14,   K15,   K16, K17,   K18,   K19,   K1A, K1B, K1C, K1D, KC_NO }, \
  { K20, K21, K22, K23,   K24,   K25,   K26, K27,   K28,   K29,   K2A, K2B, K2C, K2D, KC_NO }, \
  { K30, K31, K32, K33,   K34,   K35,   K36, K37,   K38,   K39,   K3A, K3B, K3C, K3D, KC_NO }, \
  { K40, K41, K42, KC_NO, KC_NO, KC_NO, K46, KC_NO, KC_NO, KC_NO, K4A, K4B, K4C, K4D, KC_NO }, \
}

#define LAYOUT_60_ansi( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,      K0D, \
     K10,  K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,  K1D,   \
      K20,  K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,        K2D, \
     K30,  K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3C,         \
    K40,  K41,  K42,                K46,                K4A,  K4B,  K4C,  K4D \
)\
{\
  { K00, K01,   K02, K03,   K04,   K05,   K06, K07,   K08,   K09,   K0A, K0B, K0C,   K0D,   KC_NO }, \
  { K10, K11,   K12, K13,   K14,   K15,   K16, K17,   K18,   K19,   K1A, K1B, K1C,   K1D,   KC_NO }, \
  { K20, K21,   K22, K23,   K24,   K25,   K26, K27,   K28,   K29,   K2A, K2B, KC_NO, K2D,   KC_NO }, \
  { K30, KC_NO, K32, K33,   K34,   K35,   K36, K37,   K38,   K39,   K3A, K3B, K3C,   KC_NO, KC_NO }, \
  { K40, K41,   K42, KC_NO, KC_NO, KC_NO, K46, KC_NO, KC_NO, KC_NO, K4A, K4B, K4C,   K4D,   KC_NO }, \
}

#define LAYOUT_hhkb( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,      K0D, \
     K10,  K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,  K1D,   \
      K20,  K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,       K2D,  \
        K30,   K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,   K3C,  K3D,  \
          K41,  K42,                 K46,                   K4B,  K4C         \
)\
{\
  { K00,   K01,   K02, K03,   K04,   K05,   K06, K07,   K08,   K09,   K0A,   K0B, K0C,   K0D,   KC_NO }, \
  { K10,   K11,   K12, K13,   K14,   K15,   K16, K17,   K18,   K19,   K1A,   K1B, K1C,   K1D,   KC_NO }, \
  { K20,   K21,   K22, K23,   K24,   K25,   K26, K27,   K28,   K29,   K2A,   K2B, KC_NO, K2D,   KC_NO }, \
  { K30,   KC_NO, K32, K33,   K34,   K35,   K36, K37,   K38,   K39,   K3A,   K3B, K3C,   K3D,   KC_NO }, \
  { KC_NO, K41,   K42, KC_NO, KC_NO, KC_NO, K46, KC_NO, KC_NO, KC_NO, KC_NO, K4B, K4C,   KC_NO, KC_NO }, \
}

#define LAYOUT_hhkb_splits( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,    K0D, K0E,\
     K10,  K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,  K1D,     \
      K20,  K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2D,     \
     K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,   K3C, K3D,     \
          K41,  K42,                 K46,                   K4B,  K4C           \
)\
{\
  { K00,   K01, K02, K03,   K04,   K05,   K06, K07,   K08,   K09,   K0A,   K0B, K0C,   K0D,   K0E   }, \
  { K10,   K11, K12, K13,   K14,   K15,   K16, K17,   K18,   K19,   K1A,   K1B, K1C,   K1D,   KC_NO }, \
  { K20,   K21, K22, K23,   K24,   K25,   K26, K27,   K28,   K29,   K2A,   K2B, KC_NO, K2D,   KC_NO }, \
  { K30,   K31, K32, K33,   K34,   K35,   K36, K37,   K38,   K39,   K3A,   K3B, K3C,   K3D,   KC_NO }, \
  { KC_NO, K41, K42, KC_NO, KC_NO, KC_NO, K46, KC_NO, KC_NO, KC_NO, KC_NO, K4B, K4C,   KC_NO, KC_NO }, \
}

#endif
