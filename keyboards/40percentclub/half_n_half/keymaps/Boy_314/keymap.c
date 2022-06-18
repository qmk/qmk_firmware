/* Copyright 2019 Boy_314
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

// Tap Dance Declarations
enum {
	TD_SWAP_LAYERS = 0
};

enum layers {
	_DVORAK,
	_QWERTY,
	_LOWER,
	_RAISE,
};

enum halfnhalf_keycodes {
	NEWTAB = SAFE_RANGE,
	ALTF4,
	CLSTAB,
	PRVWIN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* DVORAK
	 * ,-------------------------------------------------------------------------------------------------.
	 * |Tab   |'     |,     |.     |P     |Y     |Brght+|=     |F     |G     |C     |R     |L     |Bksp  |
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 * |CtlCps|A     |O     |E     |U     |I     |Brght-|Ctrl+F|D     |H     |T     |N     |S     |Enter |
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 * |LShift|;     |Q     |J     |K     |X     |LAlt  |-     |B     |M     |W     |V     |Z     |RShift|
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 *                             |TD Swap Layer|             |Space        |
	 *                             `-------------'			       `-------------'
	 */
	[_DVORAK] = LAYOUT(/* Base Dvorak */
	  KC_TAB,           KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_BRIU, KC_EQL,     KC_F, KC_G, KC_C,    KC_R,   KC_L,   KC_BSPC,
	  LCTL_T(KC_CAPS),  KC_A,    KC_O,    KC_E,   KC_U, KC_I, KC_BRID, LCTL(KC_F), KC_D, KC_H, KC_T,    KC_N,   KC_S,   KC_ENT,
	  KC_LSPO,          KC_SCLN, KC_Q,    KC_J,   KC_K, KC_X, KC_LALT, KC_MINS,    KC_B, KC_M, KC_W,    KC_V,   KC_Z,   KC_RSPC,
	                                              TD(TD_SWAP_LAYERS),                    KC_SPC
	),

	/* QWERTY
	 * ,-------------------------------------------------------------------------------------------------.
	 * |Tab   |Q     |W     |E     |R     |T     |Brght+|'     |Y     |U     |I     |O     |P     |Bksp  |
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 * |CtlCps|A     |S     |D     |F     |G     |Brght-|Ctrl+F|H     |J     |K     |L     |;     |Enter |
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 * |LShift|Z     |X     |C     |V     |B     |LAlt  |-     |N     |M     |,     |.     |/     |RShift|
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 *                             |TD Swap Layer|             |Space        |
	 *                             `-------------'			       `-------------'
	 */
	[_QWERTY] = LAYOUT(/* Base Qwerty */
	  KC_TAB,           KC_Q,    KC_W,    KC_E,   KC_R, KC_T, KC_BRIU, KC_QUOT,    KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_BSPC,
	  LCTL_T(KC_CAPS),  KC_A,    KC_S,    KC_D,   KC_F, KC_G, KC_BRID, LCTL(KC_F), KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_ENT,
	  KC_LSPO,          KC_Z,    KC_X,    KC_C,   KC_V, KC_B, KC_LALT, KC_MINS,    KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC,
	                                              TD(TD_SWAP_LAYERS),                    KC_SPC
	),

	/* LOWER
	 * ,-------------------------------------------------------------------------------------------------.
	 * |Esc   |1     |2     |3     |4     |5     |      |      |6     |7     |8     |9     |0     |/     |
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 * |Caps  |F1    |F2    |F3    |F4    |F5    |F6    |Vol Up|Play  |_     |+     |{     |}     ||     |
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 * |      |F7    |F8    |F9    |F10   |F11   |F12   |Vol Dn|Next  |Home  |PgDn  |PgUp  |End   |      |
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 *                             |             |             |             |
	 *                             `-------------'             `-------------'
	 */
	[_LOWER] = LAYOUT(/* Numbers, Function Row, Media Control, Shifted Symbols, Dvorak Slash Key */
	  KC_GESC, KC_1,  KC_2,  KC_3,  KC_4,   KC_5,   KC_TRNS, KC_TRNS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_SLSH,
	  KC_CAPS, KC_F1, KC_F2, KC_F3, KC_F4,  KC_F5,  KC_F6,   KC_VOLU, KC_MPLY, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
	  KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,  KC_VOLD, KC_MNXT, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS,
									                KC_TRNS,    					            KC_TRNS
	),

	/* RAISE
	 * ,-------------------------------------------------------------------------------------------------.
	 * |Reset |      |      |Up    |      |      |      |PRVWIN|CLSTAB|      |      |      |      |Del   |
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 * |`     |      |Left  |Down  |Right |      |      |NEWTAB|ALTF4 |-     |=     |[     |]     |\     |
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 * |      |!     |@     |#     |$     |%     |      |      |^     |&     |*     |(     |)     |      |
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 *                             |             |             |             |
	 *                             `-------------'             `-------------'
	 */
	[_RAISE] = LAYOUT(/* Arrows, Shifted Numbers, Symbols, Delete, Macros */
	  RESET,   KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, PRVWIN,  CLSTAB,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL,
	  KC_GRV,  KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, NEWTAB,  ALTF4,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
	  KC_TRNS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_TRNS, KC_TRNS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
										                    KC_TRNS,                            KC_TRNS
	)
};

void tap_dance_choose_layer (qk_tap_dance_state_t *state, void *user_data) {
	switch (state->count) {
		case 1:
			layer_on(_LOWER);
			break;
		case 2:
			layer_on(_RAISE);
			break;
	}
}

void tap_dance_choose_layer_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (state->count) {
		case 1:
			layer_off(_LOWER);
			break;
		case 2:
			layer_off(_RAISE);
			break;
		case 3:
			if (get_highest_layer(default_layer_state) == _DVORAK) {
				set_single_persistent_default_layer(_QWERTY);
			}
			else if (get_highest_layer(default_layer_state) == _QWERTY) {
				set_single_persistent_default_layer(_DVORAK);
			}
			break;
	}
}

qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_SWAP_LAYERS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_dance_choose_layer, tap_dance_choose_layer_reset)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		// Control + T
		case NEWTAB:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("t"));
			}
			break;
		// Alt + F4
		case ALTF4:
			if (record->event.pressed) {
				SEND_STRING(SS_DOWN(X_LALT)SS_TAP(X_F4)SS_UP(X_LALT));
			}
			break;
		// Control + W
		case CLSTAB:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("w"));
			}
			break;
		// Control + Shift + N
		case PRVWIN:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL(SS_LSFT("n")));
			}
			break;
	}
	return true;
}
