#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_numpad_5x4(
    TG(1),   KC_PSLS, KC_PAST, KC_PMNS, \
    KC_P7,   KC_P8,   KC_P9,   \
    KC_P4,   KC_P5,   KC_P6,   KC_PPLS, \
    KC_P1,   KC_P2,   KC_P3,   \
      KC_P0,          KC_PDOT, KC_PENT  \
  ),

  [1] = LAYOUT_numpad_5x4(
    _______, _______, _______, _______, \
    KC_HOME, KC_UP,   KC_PGUP, \
    KC_LEFT, XXXXXXX, KC_RGHT, _______, \
    KC_END,  KC_DOWN, KC_PGDN, \
      KC_INS,         KC_DEL,  _______  \
  ),
};
