#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* ============================= DEBUG LAYER ============================= */
  [0] = LAYOUT(
    KC_A, KC_1, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,
    KC_A, KC_2, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,
    KC_A, KC_3, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,
    KC_A, KC_4, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L
  )
};
