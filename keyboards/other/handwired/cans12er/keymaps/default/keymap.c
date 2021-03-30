// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _KEYPAD 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_KEYPAD] = LAYOUT_ortho_3x4(
		KC_A, KC_B, KC_C, KC_D, 
		KC_E, KC_F, KC_G, KC_H, 
		KC_I, KC_J, KC_K, KC_L 
),
};
