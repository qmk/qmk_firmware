/* Copyright 2019 Erovia
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "erovia.h"

// Left space on tap, LOWER on hold
#define SPC_LOW LT(_LOWER, KC_TAB)
// Left space on tap, UPPER on hold
#define SPC_UPR LT(_RAISE, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * ,---------------------------------------------------------------.
 * | `  | Q  | W  | E  | R  | T  | Y  | U  | I  | O  | P  |  Bspc  |
 * |---------------------------------------------------------------|
 * | Esc  | A  | S  | D  | F  | G  | H  | J  | K  | L  | '  |  .   |
 * |---------------------------------------------------------------|
 * | Shift  | Z  | X  | C  | V  | B  | N  | M  | ,  | .  |  Enter  |
 * |---------------------------------------------------------------|
 *      |Ctrl|Gui |Alt | Spc/Lwr |   Spc/Rse   |    |    |    |
 *      `-----------------------------------------------------'
 */

	[_QWERTY] = LAYOUT(
		KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
		VIM_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_DOT,
		TD_SHFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   TD_ENTR,
		KC_LCTL, KC_LGUI, KC_LALT, SPC_LOW,  SPC_UPR,  KC_NO, KC_NO, KC_NO
	),

/*
 * ,---------------------------------------------------------------.
 * | `  | Q  | W  | E  | R  | T  | Y  | U  | I  | O  | P  |  Bspc  |
 * |---------------------------------------------------------------|
 * | Esc  | A  | S  | D  | F  | G  | H  | J  | K  | L  | '  |  '   |
 * |---------------------------------------------------------------|
 * | Shift  | Z  | X  | C  | V  | B  | N  | M  | ,  | .  |  Enter  |
 * |---------------------------------------------------------------|
 *      |Ctrl|Gui |Alt | Spc/Lwr |   Spc/Rse   |    |    |    |
 *      `-----------------------------------------------------'
 */

	[_COLEMAK] = LAYOUT(
		KC_GRV,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,    KC_BSPC,
		VIM_ESC, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,       KC_QUOT,
		TD_SHFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  TD_ENTR,
		KC_LCTL, KC_LGUI, KC_LALT, SPC_LOW,  SPC_UPR,  KC_NO, KC_NO, KC_NO
	),

/*
 * ,---------------------------------------------------------------.
 * | ~  | !  | @  | #  | $  | %  | ^  | &  | *  | (  | )  |        |
 * |---------------------------------------------------------------|
 * | Del  | F1 | F2 | F3 | F4 | F5 | F6 | _  | +  | {  | }  |  |   |
 * |---------------------------------------------------------------|
 * |        | F7 | F8 | F9 |F10 |F11 |F12 |    | ;  |PgUp|   /     |
 * |---------------------------------------------------------------|
 *      |    |    |    |         |             |Home|PgDn|End |
 *      `-----------------------------------------------------'
 */

	[_LOWER] = LAYOUT(
		KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
		KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
		KC_NO,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,   KC_SCLN, KC_PGUP, KC_SLSH,
		KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END
	),

/*
 * ,---------------------------------------------------------------.
 * | `  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 0  |        |
 * |---------------------------------------------------------------|
 * | Ins  | F1 | F2 | F3 | F4 | F5 | F6 | -  | =  | [  | ]  |  \   |
 * |---------------------------------------------------------------|
 * |        | F7 | F8 | F9 |F10 |F11 |F12  |    |    |   |         |
 * |---------------------------------------------------------------|
 *      |VolD|Mute|VolU|         |             |    |    |    |
 *      `-----------------------------------------------------'
 */

	[_RAISE] = LAYOUT(
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
		KC_INS,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
		KC_NO,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_VOLD, KC_MUTE, KC_VOLU, KC_TRNS, KC_TRNS, KC_NO,   KC_NO,   KC_NO
	),

/*
 * ,---------------------------------------------------------------.
 * |EEPR|RST |    |    |    |    |    |    |    |    |    |        |
 * |---------------------------------------------------------------|
 * |Leader|    |    |    |    |    |    |    |    |    |    |      |
 * |---------------------------------------------------------------|
 * |        |    |    |    |    |    |     |    |    |   |         |
 * |---------------------------------------------------------------|
 *      |RGB-|RGB |RGB+|         |             |    |    |    |
 *      `-----------------------------------------------------'
 */

	[_ADJUST] = LAYOUT(
		EEP_RST, RESET,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_LEAD, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   QWERTY,  COLEMAK, KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
		RGB_VAD, RGB_TOG, RGB_VAI, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
	),

/*
 * ,---------------------------------------------------------------.
 * |    |    |    |    |    |    |    |    |    |    |    |        |
 * |---------------------------------------------------------------|
 * |      |    |    |    |    |    | H  | J  | K  | L  |    |      |
 * |---------------------------------------------------------------|
 * |        |    |    |    |    |    |     |    |    |Up |         |
 * |---------------------------------------------------------------|
 *      |    |    |    |         |             |Left|Down|Rght|
 *      `-----------------------------------------------------'
 */

	[_VIM] = LAYOUT(
		EEP_RST, RESET,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_H,    KC_J,    KC_K,    KC_L,    KC_NO,   KC_NO,
		KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_UP,   KC_NO,
		RGB_VAD, RGB_TOG, RGB_VAI, KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT
	),
};

layer_state_t layer_state_set_keymap(layer_state_t state) {
	state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
	switch (biton32(state)) {
		case _LOWER:
			rgblight_sethsv_noeeprom(HSV_GREEN);
			break;
		case _RAISE:
			rgblight_sethsv_noeeprom(HSV_GOLD);
			break;
		case _ADJUST:
			rgblight_sethsv_noeeprom(HSV_RED);
			break;
		default:
			rgblight_sethsv_noeeprom(HSV_WHITE);
			break;
	}
	return state;
}

void keyboard_post_init_user(void) {
	dimple_led_off();
}
