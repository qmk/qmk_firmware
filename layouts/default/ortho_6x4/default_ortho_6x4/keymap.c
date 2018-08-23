#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ortho_6x4(
    KC_F1,  KC_F2,  KC_F3,  KC_F4,  \
    KC_F5,  KC_F6,  KC_F7,  KC_F8,  \
    KC_F9,  KC_F10, KC_F11, KC_F12, \
    KC_F13, KC_F14, KC_F15, KC_F16, \
    KC_F17, KC_F18, KC_F19, KC_F20, \
    KC_F21, KC_F22, KC_F23, KC_F24  \
  ),
};
