#include QMK_KEYBOARD_H
#include "wanleg.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
#if defined(KEYBOARD_lets_split_rev2)
[_GK] = LAYOUT_ortho_4x12_wrapper(
  _______________GherkinLike_0_______________,
  _______________GherkinLike_1_______________,
  _______________GherkinLike_2_______________,
  _______________GherkinLike_3_OneHand_______
),
[ONE] = LAYOUT_ortho_4x12_wrapper(
  _______________Qwerty_Row__0_______________,
  _______________Qwerty_Row__1_______________,
  _______________Qwerty_Row__2_______________,
  KC_LCTL, KC_LGUI, KC_LALT, GHERKIN, SUBTER, SH_T(KC_SPC), SH_T(KC_SPC), SUPRA, KC_RGUI, KC_RALT, GHERKIN, KC_RCTL
),
#else
[_GK] = LAYOUT_ortho_4x12_wrapper(
  _______________GherkinLike_0_______________,
  _______________GherkinLike_1_______________,
  _______________GherkinLike_2_______________,
  _______________GherkinLike_3_______________
),
#endif
[_QW] = LAYOUT_ortho_4x12_wrapper(
  _______________Qwerty_Row__0_______________,
  _______________Qwerty_Row__1_______________,
  _______________Qwerty_Row__2_______________,
  _______________Qwerty_Row__3_______________
),

[SUP] = LAYOUT_ortho_4x12_wrapper(
  ________________SUPRA_Row_0________________,
  ________________SUPRA_Row_1________________,
  ________________SUPRA_Row_2________________,
  ________________SUPRA_Row_3________________
),

[SUB] = LAYOUT_ortho_4x12_wrapper(
  _______________SUBTER_Row__0_______________,
  _______________SUBTER_Row__1_______________,
  _______________SUBTER_Row__2_______________,
  _______________SUBTER_Row__3_______________
),

[NUM] = LAYOUT_ortho_4x12_wrapper(
  _______________NUMBERS_Row_0_______________,
  _______________NUMBERS_Row_1_______________,
  _______________NUMBERS_Row_2_______________,
  _______________NUMBERS_Row_3_______________
),

[DIR] = LAYOUT_ortho_4x12_wrapper(
  _____________DIRECTIONS_Row__0_____________,
  _____________DIRECTIONS_Row__1_____________,
  _____________DIRECTIONS_Row__2_____________,
  _____________DIRECTIONS_Row__3_____________
),

[ETC] = LAYOUT_ortho_4x12_wrapper(
  ______________ETCETERA_Row__0______________,
  ______________ETCETERA_Row__1______________,
  ______________ETCETERA_Row__2______________,
  ______________ETCETERA_Row__3______________
),
};
