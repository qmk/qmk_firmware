#include QMK_KEYBOARD_H
#include "wanleg.h"

#define LAYOUT_miniaxe_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
     K01,	K02,	K03,	K04,	K05,	K06,	K07,	K08,	K09,	K0A, \
     K11,	K12,	K13,	K14,	K15,	K16,	K17,	K18,	K19,	K1A, \
     K21,	K22,	K23,	K24,	K25,	K26,	K27,	K28,	K29,	K2A, \
              _______, NUMBER, ETCETERA,	KC_SPC, DIRECTION, KC_RGUI            \
  )
#define LAYOUT_miniaxe_base_wrapper(...)       LAYOUT_miniaxe_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_GK] = LAYOUT_miniaxe_base_wrapper( 
  _______________Gherkin_Row_0_______________, 
  _______________Gherkin_Row_1_______________, 
  SFT_T(KC_Z), 	KC_X, 	KC_C, 	LT(NUM,KC_V),	LT(ETC,KC_B),  LT(_FN,KC_N), 	LT(DIR,KC_M), 	GUI_T(KC_COMM),	ALT_T(KC_DOT),	CTL_T(KC_BSPC)  
),

[NUM] = LAYOUT_wrapper(
  _______________Gherkin_NUM_0_______________,
  _______________Gherkin_NUM_1_______________,
  _______________Gherkin_NUM_2_______________,
  _______, _______, _______,	KC_ENT, KC_RSFT, _______
),

[DIR] = LAYOUT_miniaxe_base_wrapper(
  _______________Gherkin_DIR_0_______________,
  _______________Gherkin_DIR_1_______________,
  _______________Gherkin_DIR_2_______________
),

[ETC] = LAYOUT_wrapper(
  _______________Gherkin_ETC_0_______________,
  _______________Gherkin_ETC_1_______________,
  _______________Gherkin_ETC_2_______________,
  _______, NUMBER, ETCETERA,	LALT(LCTL(KC_DEL)), DIRECTION, KC_RGUI
),

[_FN] = LAYOUT_miniaxe_base_wrapper(
  _______________Gherkin_FN_0________________,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
};