#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ortho_4x4(
    KC_TAB,  KC_Q,    KC_W,    KC_E,
    KC_ESC,  KC_A,    KC_S,    KC_D,
    KC_LSFT, KC_Z,    KC_X,    KC_C,
    KC_F,    KC_LALT, KC_LCTL, KC_SPC
  ),
};
