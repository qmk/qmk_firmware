#include QMK_KEYBOARD_H

/* KEYMAP_numpad
 * ┌───┐   ┌───┬───┐ 
 * │K00│   │K02│K03│
 * └───┘   └───┴───┘ 
 * ┌───┬───┬───┬───┐
 * │K10│K11│K12│K13│
 * ├───┼───┼───┼───┤ 
 * │K20│K21│K22│K23│
 * ├───┼───┼───┤   │ 
 * │K30│K31│K32│   │
 * ├───┼───┼───┼───┤ 
 * │K40│K41│K42│K43│
 * ├───┴───┼───┤   │ 
 * │K50    │K52│   │
 * └───────┴───┴───┘
 */

 /* KEYMAP_southpaw
 * ┌───┐   ┌───┬───┐ 
 * │K00│   │K02│K03│
 * └───┘   └───┴───┘ 
 * ┌───┬───┬───┬───┐
 * │K10│K11│K12│K13│
 * ├───┼───┼───┼───┤ 
 * │K20│K21│K22│K23│
 * │   ├───┼───┼───┤ 
 * │   │K31│K32│K33│
 * ├───┼───┼───┼───┤ 
 * │K40│K41│K42│K43│
 * │   ├───┼───┴───┤ 
 * │   │K51│K52    │
 * └───┴───┴───────┘
 */

/* KEYMAP_macropad
 * ┌───┐   ┌───┬───┐ 
 * │K00│   │K01│K02│
 * └───┘   └───┴───┘ 
 * ┌───┬───┬───┬───┐
 * │K10│K11│K12│K13│
 * ├───┼───┼───┼───┤ 
 * │K20│K21│K22│K23│
 * ├───┼───┼───┼───┤ 
 * │K30│K31│K32│K33│
 * ├───┼───┼───┼───┤ 
 * │K40│K41│K42│K43│
 * ├───┼───┼───┼───┤ 
 * │K50│K51│K52│K53│
 * └───┴───┴───┴───┘
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT_numpad(
		KC_MUTE, KC_MPLY,     KC_BSPC, 
		KC_CALC, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS, 
		KC_KP_7, KC_KP_8,     KC_KP_9,        KC_KP_PLUS, 
		KC_KP_4, KC_KP_5,     KC_KP_6, 
		KC_KP_1, KC_KP_2,     KC_KP_3,        KC_KP_ENTER, 
		KC_KP_0, KC_KP_DOT),

	[1] = LAYOUT_numpad(
		KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	[2] = LAYOUT_numpad(
		KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	[3] = LAYOUT_numpad(
		KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS), };

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } 
     return false; 
}



