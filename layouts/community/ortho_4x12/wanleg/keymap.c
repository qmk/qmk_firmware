#include QMK_KEYBOARD_H
#include "wanleg.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_GK] = LAYOUT_ortho_4x12_wrapper(
  _______________GherkinLike_0_______________,
  _______________GherkinLike_1_______________,
  _______________GherkinLike_2_______________
),

[_QW] = LAYOUT_ortho_4x12_wrapper(
  _______________Qwerty_Row__0_______________,
  _______________Qwerty_Row__1_______________,
  _______________Qwerty_Row__2_______________
),

[SUP] = LAYOUT_ortho_4x12_wrapper(
  ________________SUPRA_Row_0________________,
  ________________SUPRA_Row_1________________,
  ________________SUPRA_Row_2________________
),

[SUB] = LAYOUT_ortho_4x12_wrapper(
  _______________SUBTER_Row__0_______________,
  _______________SUBTER_Row__1_______________,
  _______________SUBTER_Row__2_______________
),

[NUM] = LAYOUT_ortho_4x12_wrapper(
  _______________NUMBERS_Row_0_______________,
  _______________NUMBERS_Row_1_______________,
  _______________NUMBERS_Row_2_______________
),

[DIR] = LAYOUT_ortho_4x12_wrapper(
  _____________DIRECTIONS_Row__0_____________,
  _____________DIRECTIONS_Row__1_____________,
  _____________DIRECTIONS_Row__2_____________
),

[ETC] = LAYOUT_ortho_4x12_wrapper(
  ______________ETCETERA_Row__0______________,
  ______________ETCETERA_Row__1______________,
  ______________ETCETERA_Row__2______________
),
};
