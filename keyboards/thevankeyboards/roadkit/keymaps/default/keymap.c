#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _NP 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NP] = LAYOUT_numpad_4x4( /* Numpad */
    KC_P7, KC_P8,   KC_P9,   KC_PPLS,
    KC_P4, KC_P5,   KC_P6,
    KC_P1, KC_P2,   KC_P3,   KC_PENT,
    KC_P0,          KC_PDOT
  ),
};
