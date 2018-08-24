#include QMK_KEYBOARD_H
#include "wanleg.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[gGK] = LAYOUT_ortho_5x10_wrapper(
  _______________Gherkin_NUM_0_______________,
  _______________Gherkin_Row_0_______________,
  _______________Gherkin_Row_1_______________,
  _______________Gherkin_Row_2_______________,
  _______, _______, _______, gNUMBER, gETCETERA, KC_SPC,gDIRECTION, KC_RGUI, _______, _______
),


[gNUM] = LAYOUT_ortho_5x10_wrapper(
  _______________Gherkin_NUM_0_______________,
  _______________Gherkin_NUM_0_______________,
  _______________Gherkin_NUM_1_______________,
  _______________Gherkin_NUM_2_______________,
  _______, _______, _______, _______, _______, KC_ENT, KC_RSFT, KC_RGUI, _______, _______
),

[gDIR] = LAYOUT_ortho_5x10_wrapper(
  _______________Gherkin_NUM_0_______________,
  _______________Gherkin_DIR_0_______________,
  _______________Gherkin_DIR_1_______________,
  _______________Gherkin_DIR_2_______________,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[gETC] = LAYOUT_ortho_5x10_wrapper(
  _______________Gherkin_NUM_0_______________,
  _______________Gherkin_ETC_0_______________,
  _______________Gherkin_ETC_1_______________,
  _______________Gherkin_ETC_2_______________,
  _______, _______, _______, _______, _______, LALT(LCTL(KC_DEL)), _______, _______, _______, _______
),

};
