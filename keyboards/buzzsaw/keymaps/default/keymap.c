/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 *
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * There's also a template for adding new layers at the bottom of this file!
 */

#include QMK_KEYBOARD_H

#define BASE 0 // default layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------.         ,-------------------------------.  .---.
 * |   ESC  | 1 | 2 | 3 | 4 | 5 | 6 |         | 7 | 8 | 9 | 0 | - | = | + |BSP|  |ESC|
 * |--------------------------------'         |-------------------------------|  |---|
 * |   TAB	| Q | W | E | R | T |             | Y | U | I | O | P | [ | ] | | |  |INS|
 * |----------------------------|             |-------------------------------|  |---|
 * | CAPS   | A | S | D | F | G |             | H | J | K | L | ; | " | RET   |  |DEL|
 * |----------------------------|             |-------------------------------|  '---'
 * | Shift  | Z | X | C | V | B |		          | B | N | M | < | > | ? |	    		  .---.
 * |----------------------------'             '-----------------------'--.   			|UP |
 * | CNTL   |ALT| 0 |COD|         											|SPC| ALT | CTL  |    .---|---|---|
 * '--------------------'						          					'----------------'    |LFT|DWN|RGT|
 *                                                                            '-----------'
 */
[BASE] = LAYOUT_buzzsaw(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,     KC_7, KC_8, KC_9, KC_0, 	 KC_MINS, KC_PPLS, KC_PMNS, KC_BSPC, KC_ESC,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, 					KC_Y, KC_U, KC_I, KC_O, 	 KC_P, 	 	KC_LBRC, KC_RBRC, KC_NUBS, KC_INS,
		KC_CAPS,KC_A, KC_S, KC_D, KC_F, KC_G, 					KC_H, KC_J, KC_K, KC_L, 	 KC_SCLN, KC_QUOT, KC_ENT,				   KC_DEL,
		KC_LSFT,KC_Z, KC_X, KC_C, KC_V, KC_B,						KC_B, KC_N, KC_M, KC_COMM, KC_DOT, 	KC_SLSH, 								   KC_UP,
		KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,																                 KC_SPC, KC_RALT,    KC_LEFT,KC_DOWN, KC_RIGHT)
};
