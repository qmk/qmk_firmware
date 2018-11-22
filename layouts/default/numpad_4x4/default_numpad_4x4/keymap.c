#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_numpad_4x4(
    KC_P7,   KC_P8,   KC_P9,   KC_PPLS, \
    KC_P4,   KC_P5,   KC_P6,            \
    KC_P1,   KC_P2,   KC_P3,   KC_PENT, \
        KC_P0,        KC_PDOT           \
  ),

};
