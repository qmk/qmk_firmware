/* Good on you for modifying your layout! if you don't have 
 * time to read the QMK docs, a list of keycodes can be found at
 *
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * There's also a template for adding new layers at the bottom of this file!
 */

#include QMK_KEYBOARD_H

#define FIESTA   0 // default layer
#define TACOTIME 1 // symbols

// Blank template at the bottom
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap template 
 *
 * ,-------------------------------------------------.           ,--------------------------------------------.
 * |       |      |      |      |      |      |      |           |       |      |      |      |      |        |
 * `-------+------+------+------+------+-------------'           `-------+------+------+------+------+--------' */
[FIESTA] = LAYOUT(  
   KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y,        KC_A, KC_S, KC_D, KC_F, KC_G, KC_H
),
};

/* Keymap template 
 *
 * ,-------------------------------------------------.           ,--------------------------------------------.
 * |       |      |      |      |      |      |      |           |       |      |      |      |      |        |
 * `-------+------+------+------+------+-------------'           `-------+------+------+------+------+--------'
[FIESTA] = LAYOUT(  
   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),
 */
