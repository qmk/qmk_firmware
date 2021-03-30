/* Copyright 2018 westfoxtrot
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	/* Default layer
	* ,--------------------------------------------------------------------------------------------------------------------.  ,-------.
	* | GrvEsc |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |   +   |   ´   | Backspace |  | PgUp  |
	* |--------------------------------------------------------------------------------------------------------------------+  +-------+
	* | Tab      |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |   Å   |   ¨   |  Enter  |  | PgDn  |
	* |-----------------------------------------------------------------------------------------------------------,        |  `-------`
	* | Mod Layer |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   Ö   |   Ä   |   '   |        |
	* |-----------------------------------------------------------------------------------------------------------------------,
	* | Shift   |   <  |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   |   -   |    Shift     |  Up   |
	* |-----------------------------------------------------------------------------------------------------------------------+-------,
	* | Control | Option | Command |                        Space                         | Command | Option  | Left  | Down  | Right |
	* `-------------------------------------------------------------------------------------------------------------------------------'
	*/

	[0] = LAYOUT(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL, KC_BSPC, KC_PGUP,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,         KC_PGDN,
		MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
		KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_NO,   KC_UP,
		KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, KC_RALT,          KC_LEFT, KC_DOWN, KC_RGHT),


	/* Modifier layer
	* ,--------------------------------------------------------------------------------------------------------------------.  ,-------.
	* | Esc    |       |       |       |       |       |       |       |   [   |   ]   |       |       |       |   Delete  |  | VolUp |
	* |--------------------------------------------------------------------------------------------------------------------+  +-------+
	* |          |       |       |       |       |       |       | PgUp  |  Up   | PgDn  |       |       |       |         |  | VolDn |
	* |-----------------------------------------------------------------------------------------------------------,        |  `-------`
	* |           |       |Scrnsht|Desktop|       |       |       | Left  |  Down | Right |       |       | Reset |        |
	* |-----------------------------------------------------------------------------------------------------------------------,
	* | Shift   |      |       |       |       |       |       |       |       |       |       |       |    Shift     | Play  |
	* |-----------------------------------------------------------------------------------------------------------------------+-------,
	* |         |        |         |                                                      |         |         | Prev  | Mute  | Next  |
	* `-------------------------------------------------------------------------------------------------------------------------------'
	*/

	[1] = LAYOUT(
		KC_ESC,  _______, _______,    _______, _______, _______, _______, _______, RALT(KC_8),  RALT(KC_9), _______, _______, _______, KC_DEL,  KC__VOLUP,
		_______, _______, _______,    _______, _______, _______, _______, KC_PGUP, KC_UP,       KC_PGDN,    _______, _______, _______,          KC__VOLDOWN,
		_______, _______, SGUI(KC_5), KC_F11,  _______, _______, _______, KC_LEFT, KC_DOWN,     KC_RGHT,    _______, _______, RESET  , _______,
		KC_LSFT, _______, _______,    _______, _______, _______, _______, _______, _______,     _______,    _______, _______, KC_RSFT, _______, KC_MPLY,
		_______, _______, _______,                               _______,                                   _______, _______,          KC_MRWD, KC__MUTE, KC_MFFD),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
