/*
Copyright 2016 Julien Pecqueur <julien@peclu.net>
Copyright 2016 Felix Uhl <ifreilicht@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "s60-x.h"

//make keymap a little easier to read
#define _______ KC_TRNS
#define XXXXXXX KC_NO

enum layer_names {
	DEFAULT,
	GAMING,
	FUNCTION
};

enum languages {
	GERMAN
};

#define LANGUAGE GERMAN

enum custom_keycodes {
	KC_C_AM = SAFE_RANGE,
	KC_C_EM,
	KC_C_IM,
	KC_C_OM,
	KC_C_UM,
	KC_C_SM,
	KC_C_YM,
	KC_C_WM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* Layout 0: Default Layer
	* ,-----------------------------------------------------------.
	* |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|Del|
	* |-----------------------------------------------------------|
	* |Tab  |  Q|  W|  E|  R|  T|  Z|  U|  I|  O|  P|  [|  ]|BckSp|
	* |-----------------------------------------------------------|
	* |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |
	* |-----------------------------------------------------------|
	* |Shift   |  Y|  X|  C|  V|  B|  N|  M|  ,|  .|  /| Up  |RSft|
	* |-----------------------------------------------------------|
	* |Fn2 |Gui |Alt |         SpaceFn       |Alt |Left|Down|Right|
	* `-----------------------------------------------------------'
	*/
	[DEFAULT] = KEYMAP(
		KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,  \
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Z,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,          \
		KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,           \
		KC_LSFT, KC_NUBS, KC_Y,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_NO,   KC_UP,   KC_RSFT, \
		KC_FN2,  KC_LGUI, KC_LALT,                            KC_FN0,                                      KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT),

	/* Layout 1: Gaming Layer, SpaceFn disabled
	* ,-----------------------------------------------------------.
	* |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
	* |-----------------------------------------------------------|
	* |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
	* |-----------------------------------------------------------|
	* |      |   |   |   |   |   |   |   |   |   |   |   |        |
	* |-----------------------------------------------------------|
	* |        |   |   |   |   |   |   |   |   |   |   |     |Fn1 |
	* |-----------------------------------------------------------|
	* |   | NOP|     |          Space         |    |    |    |    |
	* `-----------------------------------------------------------'
	*/
	[GAMING] = KEYMAP(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_FN1,  \
		_______, XXXXXXX,   _______,                            KC_SPC,                                    _______, _______, _______, _______),

	/* Layout 2: Function Layer
	* ,-----------------------------------------------------------.
	* |`  | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|RES|
	* |-----------------------------------------------------------|
	* |     |   |   |   |Prv|Ply|Nxt| Ü |   | Ö |   |Prt|Slk|Pau  |
	* |-----------------------------------------------------------|
	* |      | Ä | ß |   |Vl-|Mut|Vl+|   |   |   |   |   |PEnt    |
	* |-----------------------------------------------------------|
	* |        |   |   |   |   |Cal|   |   |   |   |Pau |PUp |Fn1 |
	* |-----------------------------------------------------------|
	* |    |    |    |                        |    |Home|PDn |End |
	* `-----------------------------------------------------------'
	*/
	[FUNCTION] = KEYMAP(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,   RESET,   \
		_______, _______, KC_C_WM, KC_C_EM, KC_MPRV, KC_MPLY, KC_MNXT, KC_C_UM, KC_C_IM, KC_C_OM, _______, KC_PSCR, KC_SLCK, KC_PAUS, \
		_______, KC_C_AM, KC_C_SM, _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______, _______, _______, _______, _______, KC_PENT,          \
		_______, KC_C_YM, _______, _______, _______, _______, KC_CALC, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_FN1, \
		_______, _______, _______,                            _______,                                     _______, KC_HOME, KC_PGDN, KC_END),
};

/*
* Fn action definition
*/
const uint16_t PROGMEM fn_actions[] = {
	[0] = ACTION_LAYER_TAP_KEY(2, KC_SPACE),    /* SpaceFn layout 1 */
	[1] = ACTION_LAYER_TOGGLE(1),                /* Disable SpaceFn  */
	[2] = ACTION_LAYER_MOMENTARY(2)             /* SpaceFn layout 1 */
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    return MACRO_NONE;
};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_german(uint16_t keycode, keyrecord_t *record) {
	uint16_t send_code = 0;
	switch (keycode) {
	case KC_C_AM:
		if (record->event.pressed) {
			send_code = KC_Q;
		}
		break;

	case KC_C_OM:
		if (record->event.pressed) {
			send_code = KC_P;
		}
		break;

	case KC_C_UM:
		if (record->event.pressed) {
			send_code = KC_Y;
		}
		break;

	case KC_C_SM:
		if (record->event.pressed) {
			send_code = KC_S;
		}
		break;
	}

	if (send_code == 0) {
		return true;
	}
	else {
		register_code(KC_RALT);
		register_code(send_code);
		unregister_code(send_code);
		unregister_code(KC_RALT);
		return false;
	}
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (keycode == KC_QUOT) {
		if (record->event.pressed) {
			register_code(KC_QUOT);
			unregister_code(KC_QUOT);
			register_code(KC_SPACE);
			unregister_code(KC_SPACE);
		}
		return false;
	}
#if LANGUAGE == GERMAN
	return process_german(keycode, record);
#else
	return true;
#endif
}

void led_set_user(uint8_t usb_led) {

}