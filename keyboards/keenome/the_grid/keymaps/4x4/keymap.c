#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_COLS][MATRIX_ROWS] = {
  [0] = LAYOUT_test(
      KC_M, KC_I, KC_E, KC_A,
      KC_N, KC_J, KC_F, KC_B,
      KC_O, KC_K, KC_G, KC_C,
      KC_P, KC_L, KC_H, KC_D
  ),
};
