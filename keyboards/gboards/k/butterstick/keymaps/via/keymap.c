#include QMK_KEYBOARD_H
// You decided to use via
// have fun!

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_butter(
    KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
    KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_C
  ),
};
size_t keymapsCount  = sizeof(keymaps)/sizeof(keymaps[0]);
