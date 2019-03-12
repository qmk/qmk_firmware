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
	DVORAK,
	QWERTY,
	LOWER,
	RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* DVORAK
	 * ,-------------------------------------------------------------------------------------------------.
	 * |Tab   |'     |,     |.     |P     |Y     |Brght+|=     |F     |G     |C     |R     |L     |Bksp  |
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 * |LCtrl |A     |O     |E     |U     |I     |Brght-|Ctrl+F|D     |H     |T     |N     |S     |Enter |
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 * |LShift|;     |Q     |J     |K     |X     |LAlt  |-     |B     |M     |W     |V     |Z     |RShift|
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 *                             |TD Swap Layer|             |Space        |      
	 *                             `-------------'             `-------------'
	 */
	[DVORAK] = LAYOUT(/* Base Dvorak */
	  KC_TAB,   KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_BRIU, KC_EQL,     KC_F, KC_G, KC_C,    KC_R,   KC_L,   KC_BSPC, 
	  KC_LCTL,  KC_A,    KC_O,    KC_E,   KC_U, KC_I, KC_BRID, LCTL(KC_F), KC_D, KC_H, KC_T,    KC_N,   KC_S,   KC_ENT, 
	  KC_LSPO,  KC_SCLN, KC_Q,    KC_J,   KC_K, KC_X, KC_LALT, KC_MINS,    KC_B, KC_M, KC_W,    KC_V,   KC_Z,   KC_RSPC, 
	                                      TD(TD_SWAP_LAYERS),                    KC_SPC
	),
	
	/* QWERTY
	 * ,-------------------------------------------------------------------------------------------------.
	 * |Tab   |Q     |W     |E     |R     |T     |Brght+|'     |Y     |U     |I     |O     |P     |Bksp  |
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 * |LCtrl |A     |S     |D     |F     |G     |Brght-|Ctrl+F|H     |J     |K     |L     |;     |Enter |
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 * |LShift|Z     |X     |C     |V     |B     |LAlt  |-     |N     |M     |,     |.     |/     |RShift|
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 *                             |TD Swap Layer|             |Space        |      
	 *                             `-------------'             `-------------'
	 */
	[QWERTY] = LAYOUT(/* Base Qwerty */
	  KC_TAB,   KC_Q,    KC_W,    KC_E,   KC_R, KC_T, KC_BRIU, KC_QUOT,    KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_BSPC, 
	  KC_LCTL,  KC_A,    KC_S,    KC_D,   KC_F, KC_G, KC_BRID, LCTL(KC_F), KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_ENT, 
	  KC_LSPO,  KC_Z,    KC_X,    KC_C,   KC_V, KC_B, KC_LALT, KC_MINS,    KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, 
	                                      TD(TD_SWAP_LAYERS),                    KC_SPC
	),
	
	/* LOWER
	 * ,-------------------------------------------------------------------------------------------------.
	 * |Esc   |1     |2     |3     |4     |5     |      |=     |6     |7     |8     |9     |0     |/     |
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 * |Caps  |F1    |F2    |F3    |F4    |F5    |F6    |Vol Up|Play  |_     |+     |{     |}     ||     |
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 * |      |F7    |F8    |F9    |F10   |F11   |F12   |Vol Dn|Next  |Home  |PgDn  |PgUp  |End   |      |
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 *                             |             |             |             |      
	 *                             `-------------'             `-------------'
	 */
	[LOWER] = LAYOUT(/* Numbers, Function Row, Media Control, Shifted Symbols, Dvorak Slash Key */
	  KC_GESC, KC_1,  KC_2,  KC_3,  KC_4,   KC_5,   KC_TRNS, KC_TRNS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_SLSH, 
	  KC_CAPS, KC_F1, KC_F2, KC_F3, KC_F4,  KC_F5,  KC_F6,   KC_VOLU, KC_MPLY, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, 
	  KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,  KC_VOLD, KC_MNXT, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS,
									KC_TRNS,    					           KC_TRNS
	),
	
	/* RAISE
	 * ,-------------------------------------------------------------------------------------------------.
	 * |Reset |      |      |Up    |      |      |      |      |      |      |      |      |      |Del   |
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 * |`     |      |Left  |Down  |Right |      |      |      |      |-     |=     |[     |]     |\     |
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 * |      |!     |@     |#     |$     |%     |      |      |^     |&     |*     |(     |)     |      |
	 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
	 *                             |             |             |             |      
	 *                             `-------------'             `-------------'
	 */
	[RAISE] = LAYOUT(/* Arrows, Shifted Numbers, Symbols, Delete, Reset Key */
	  RESET,   KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL,
	  KC_GRV,  KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, 
	  KC_TRNS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_TRNS, KC_TRNS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS, 
										  KC_TRNS, 									   KC_TRNS
	)
};

void tap_dance_choose_layer (qk_tap_dance_state_t *state, void *user_data) {
	switch (state->count) {
		case 1:
			layer_on(LOWER);
			break;
		case 2:
			layer_on(RAISE);
			break;
	}
}

void tap_dance_choose_layer_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (state->count) {
		case 1:
			layer_off(LOWER);
			break;
		case 2:
			layer_off(RAISE);
			break;
		case 3:
			if (default_layer_state == DVORAK) {
				default_layer_set(QWERTY);
				layer_on(QWERTY);
				layer_off(DVORAK);
			}
			else if (default_layer_state == QWERTY) {
				default_layer_set(DVORAK);
				layer_on(DVORAK);
				layer_off(QWERTY);
			}
			break;
	}
}

qk_tap_dance_action_t tap_dance_actions[] = {
	// ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, on_dance_finished_fn, on_dance_reset_fn)
	[TD_SWAP_LAYERS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_dance_choose_layer, tap_dance_choose_layer_reset)
};