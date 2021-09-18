#include QMK_KEYBOARD_H

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

	[0] = LAYOUT_macropad(
		KC_MUTE, KC_F1,  KC_F2, 
		KC_F3,   KC_F4,  KC_F5,  KC_F6, 
		KC_F7,   KC_F8,  KC_F9,  KC_F10,  
		KC_F11,  KC_F12, KC_F13, KC_F14, 
		KC_F15,  KC_F16, KC_F17, KC_F18,  
		KC_F19,  KC_F20, KC_F21, KC_F22),

	[1] = LAYOUT_macropad(
		KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	[2] = LAYOUT_macropad(
		KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS), };

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



