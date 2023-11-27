#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_LEFT, KC_RGHT, KC_UP,   KC_DOWN,
    KC_P7,   KC_P8,   KC_P9,   KC_PLUS,
    KC_P4,   KC_P5,   KC_P6,   KC_MINS,
    KC_P1,   KC_P2,   KC_P3,   KC_ENT,
    KC_P0,   KC_DOT,  KC_RGHT, KC_TAB
  )
};
