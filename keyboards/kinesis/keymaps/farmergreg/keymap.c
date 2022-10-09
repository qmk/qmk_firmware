/*
 * Copyright 2022 Gregory L. Dietsche <gregory.dietsche@cuw.edu>
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
 *
 * To build this layout run:
 * qmk compile -kb kinesis/kint41 -km farmergreg
 *
 * Layout Details:
 * PROGM + F9 to QK_BOOT and load new firmware.
 * Colemak (default / PROGM+C), Dvorak (PROGM + F4) and QWERTY (PROGM+F3) layouts are available for use
 * CAPS LOCK is ESC (for use in VIM). Double tap to activate CAPS Lock
 * UP and DOWN arrows are swapped to be more like VIM
 * [] and {} are swapped to make programming easier
 */

#include QMK_KEYBOARD_H


enum {
	_COLEMAK,
	_DVORAK,
	_QWERTY,
	_QWERTY_GAME,
	_KEYPAD,
	_PROGM,
	_LAYER_COUNT,
};

/*
 * Tap Dances
 */
enum tap_dances {
	TD_CAPS,	// ESC on tap, CAPS on double tap
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
};

/*
 * Key Overrides
 */
const key_override_t lcurlytobracket = ko_make_basic(MOD_MASK_SHIFT, KC_LEFT_BRACKET, KC_LEFT_BRACKET);
const key_override_t rcurlytobracket = ko_make_basic(MOD_MASK_SHIFT, KC_RIGHT_BRACKET, KC_RIGHT_BRACKET);
const key_override_t lbrackettocurly = ko_make_basic(0, KC_LEFT_BRACKET, KC_LEFT_CURLY_BRACE);
const key_override_t rbrackettocurly = ko_make_basic(0, KC_RIGHT_BRACKET, KC_RIGHT_CURLY_BRACE);

const key_override_t **key_overrides = (const key_override_t *[]){
	&lcurlytobracket,
	&rcurlytobracket,
	&lbrackettocurly,
	&rbrackettocurly,
	NULL
};

/*
 * Key Maps
 */
const uint16_t PROGMEM keymaps[_LAYER_COUNT][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK] = LAYOUT(
	KC_ESC     , KC_F1 ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8,
	KC_EQL     , KC_1  ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,
	KC_TAB     , KC_Q  ,KC_W   ,KC_F   ,KC_P   ,KC_G   ,
	TD(TD_CAPS), KC_A  ,KC_R   ,KC_S   ,KC_T   ,KC_D   ,
	KC_LSFT    ,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,
		    KC_GRV ,KC_BSLS,KC_LEFT,KC_RGHT,

			KC_LCTL,KC_LALT,
				KC_HOME,
			KC_BSPC,KC_DEL ,KC_END,

	KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_PSCR ,KC_SLCK  ,KC_PAUS, TG(_KEYPAD), MO(_PROGM),	// I would prefer OSL(_PROGM) but MO emulates what Kinesis does in their firmware.
	KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_MINS,
	KC_J   ,KC_L   ,KC_U   ,KC_Y   ,KC_SCLN,KC_BSLS,
	KC_H   ,KC_N   ,KC_E   ,KC_I   ,KC_O   ,KC_QUOT,
	KC_K   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,KC_RSFT,
		KC_DOWN,KC_UP  ,KC_LBRC,KC_RBRC,

			KC_RGUI,KC_RCTL,
				KC_PGUP,
			KC_PGDN,KC_ENT ,KC_SPC
	)
,[_DVORAK] = LAYOUT(
	_______,_______,_______,_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
	_______,KC_QUOT,KC_COMM,KC_DOT ,KC_P   ,KC_Y   ,
	_______,KC_A   ,KC_O   ,KC_E   ,KC_U   ,KC_I   ,
	_______,KC_SCLN,KC_Q   ,KC_J   ,KC_K   ,KC_X   ,
		_______,_______,_______,_______,

			_______,_______,
				_______,
			_______,_______,_______,

	_______,_______,_______,_______,_______,_______,_______,_______, _______,
	_______,_______,_______,_______,_______,_______,
	KC_F   ,KC_G   ,KC_C   ,KC_R   ,KC_L   ,KC_SLSH,
	KC_D   ,KC_H   ,KC_T   ,KC_N   ,KC_S   ,KC_QUOT,
	KC_B   ,KC_M   ,KC_W   ,KC_V   ,KC_Z   ,_______,
		_______,_______,_______,_______,

			_______,_______,
				_______,
			_______,_______,_______
	)
,[_QWERTY] = LAYOUT(
	_______,_______,_______,_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
	_______,KC_Q  ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,
	_______,KC_A  ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,
	_______,KC_Z  ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,
		    _______,_______,_______,_______,
			_______,_______,
				_______,
			_______,_______,_______,

	_______,_______,_______,_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
	KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,_______,
	KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,_______,
	KC_N   ,KC_M   ,_______,_______,_______,_______,
		_______,_______,_______,_______,
			_______,_______,
				_______,
			_______,_______,_______
	)
,[_QWERTY_GAME] = LAYOUT( // Shift WASD over to ESDF (QWERTY). Also move T and G
	_______,_______,_______,_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
	_______,KC_T   ,KC_Q   , KC_W  ,KC_E   ,KC_R   ,
	_______,KC_G   ,KC_A   , KC_S  ,KC_D   ,KC_F   ,
	_______,_______,_______,_______,_______,_______,
		_______,_______,_______,_______,

			_______,_______,
				_______,
			KC_SPC ,_______,_______, // BACKSPACE becomes SPACE

	_______,_______,_______,_______,_______,_______,_______, _______,_______,
	_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
		_______,_______,_______,_______,

			_______,_______,
				_______,
			_______,_______,KC_BSPC // SPACE becomes BACKSPACE
	)
,[_KEYPAD] = LAYOUT(
	_______,_______,_______,_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
		_______,KC_INS ,_______,_______,

			_______,_______,
				_______,
			_______,_______,_______,

	_______,_______,_______ ,_______,KC_MUTE,KC_VOLD,KC_VOLU,TG(_KEYPAD), _______,
	_______,KC_NUM  ,KC_PEQL,KC_PSLS,KC_PAST,_______,
	_______,KC_P7   ,KC_P8  ,KC_P9  ,KC_PMNS,_______,
	_______,KC_P4   ,KC_P5  ,KC_P6  ,KC_PPLS,_______,
	_______,KC_P1   ,KC_P2  ,KC_P3  ,KC_PENT,_______,
		_______,_______ ,KC_PDOT,KC_PENT,

			_______,_______,
				_______,
			_______,_______,KC_P0
	)
	,[_PROGM] = LAYOUT(
	_______,_______,_______,DF(_QWERTY),DF(_DVORAK),_______         ,_______,_______,_______,
	_______,_______,_______,_______     ,_______    ,_______         ,
	_______,_______,_______,_______     ,_______    ,DF(_QWERTY_GAME),	// The G in Colemak
	_______,_______,_______,_______     ,_______    ,DF(_QWERTY_GAME),	// The G in QWERTY
	_______,_______,_______,DF(_COLEMAK),_______    ,_______,
		_______,_______,_______     ,_______,

			_______,_______,
				_______,
			_______,_______,_______,

	QK_BOOT,_______,_______,_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
		_______,_______,_______,_______,

			_______,_______,
				_______,
			_______,_______,_______
	)
/*
	,[_TEMPLATE] = LAYOUT(
	_______,_______,_______,_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
		_______,_______,_______,_______,

			_______,_______,
				_______,
			_______,_______,_______,

	_______,_______,_______,_______,_______,_______,_______,_______, _______,
	_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,
		_______,_______,_______,_______,

			_______,_______,
				_______,
			_______,_______,_______
	)
*/
};
