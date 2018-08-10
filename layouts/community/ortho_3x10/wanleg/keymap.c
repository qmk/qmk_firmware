#include QMK_KEYBOARD_H
#include "wanleg.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_GK] = LAYOUT_ortho_3x10_wrapper(
  _______________Gherkin_Row_0_______________,
  _______________Gherkin_Row_1_______________,
  _______________Gherkin_Row_2_______________
),

[NUM] = LAYOUT_ortho_3x10_wrapper(
  _______________Gherkin_NUM_0_______________,
  _______________Gherkin_NUM_1_______________,
  _______________Gherkin_NUM_2_______________
),

[DIR] = LAYOUT_ortho_3x10_wrapper(
  _______________Gherkin_DIR_0_______________,
  _______________Gherkin_DIR_1_______________,
  _______________Gherkin_DIR_2_______________
),

[ETC] = LAYOUT_ortho_3x10_wrapper(
  _______________Gherkin_ETC_0_______________,
  _______________Gherkin_ETC_1_______________,
  _______________Gherkin_ETC_2_______________
),

};
