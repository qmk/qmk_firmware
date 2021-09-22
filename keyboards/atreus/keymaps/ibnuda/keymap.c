#include QMK_KEYBOARD_H

#include "ibnuda.h"

// clang-format off
#define LAYOUT_atreus_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, \
                   KTA, KTB, KTC, KTD                 \
  ) \
  LAYOUT_wrapper( \
    K01, K02, K03, K04, K05,           K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15,           K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25,           K26, K27, K28, K29, K2A, \
    ___, ___, ___, ___, KTA, KTB, KTC, KTD, ___, ___, ___, ___  \
  )
#define LAYOUT_atreus_base_wrapper(...)       LAYOUT_atreus_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_atreus_base_wrapper(
    ________________DVORAK_L1_______________,                   ________________DVORAK_R1_______________,
    ________________DVORAK_L2_______________,                   ________________DVORAK_R2_______________,
    ________________DVORAK_L3_______________,                   ________________DVORAK_R3_______________,
                                     LW_BSPC,SFT_ESC,   ALT_ENT,RS_SPC
),

[_RAISE] = LAYOUT_atreus_base_wrapper(
    ________________RAISE_L1________________,                   ________________RAISE_R1________________,
    ________________RAISE_L2________________,                   ________________RAISE_R2________________,
    ________________RAISE_L3________________,                   ________________RAISE_R3________________,
                                     ADDDD,  _______,   _______,_______
),
[_LOWER] = LAYOUT_atreus_base_wrapper(
    ________________LOWER_L1________________,                   ________________LOWER_R1________________,
    ________________LOWER_L2________________,                   ________________LOWER_R2________________,
    ________________LOWER_L3________________,                   ________________LOWER_R3________________,
                                     _______,_______,   _______,ADDDD
),
[_ADJUST] = LAYOUT_atreus_base_wrapper(
    ________________ADJUST_L1_______________,                   ________________ADJUST_R1_______________,
    ________________ADJUST_L2_______________,                   ________________ADJUST_R2_______________,
    ________________ADJUST_L3_______________,                   ________________ADJUST_R3_______________,
                                     _______,_______,   _______,_______
),
};
// clang-format on
