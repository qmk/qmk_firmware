#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,
    KC_TAB,  KC_Q,    KC_W,    KC_E,
    KC_LCTL, KC_A,    KC_S,    KC_D,
    KC_SPC,  KC_Z,    KC_X,    KC_C
  )
};
