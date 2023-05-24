/* Copyright 2020 Oliver Granlund
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

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
	QWERTY = SAFE_RANGE,
	LOWER,
	RAISE,
	ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_QWERTY] = LAYOUT(
	//┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
	 	KC_ESC,  KC_1, 	  KC_2, 	 KC_3, 	 KC_4, 	  KC_5,                				  KC_6,    KC_7,    KC_8, 	 KC_9,     KC_0,  KC_MINS,
	//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
		KC_TAB,	 KC_Q,    KC_W, 	 KC_E, 	 KC_R, 	  KC_T,                				  KC_Y,    KC_U, 	KC_I, 	 KC_O, 	  KC_P,   KC_LBRC,
	//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	 MO(_LOWER),  KC_A,  	KC_S,   KC_D, 	 KC_F, 	  KC_G,         					  KC_H, 	KC_J, 	KC_K, 	  KC_L,  KC_SCLN, KC_QUOT,
	//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 	KC_LSFT,   KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,   KC_LALT,           KC_BSPC,  KC_N,    KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
	//└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
	                   				   KC_LGUI, KC_LCTL, KC_SPC,         			 KC_ENT,MO(_RAISE),KC_RALT
								  // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
	),

	[_LOWER] = LAYOUT(
	//┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
	 	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                			KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_EQL,
	//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	   KC_TRNS,  KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS,                     		KC_TRNS,  KC_PGUP, KC_UP, KC_PGDOWN, KC_TRNS, KC_RBRC,
	//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	   KC_TRNS, KC_VOLD, KC_MUTE, KC_VOLU, KC_TRNS, KC_TRNS,                     		KC_TRNS, KC_LEFT,  KC_DOWN, KC_RGHT, KC_TRNS, KC_BSLS,
	//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_DEL, KC_TRNS, KC_GRAVE, KC_CIRC, KC_QUOTE, KC_TRNS, KC_TRNS,
	//└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
	                               	   KC_TRNS, KC_TRNS, KC_TRNS,         		    KC_TRNS, KC_TRNS, KC_TRNS
								  // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
	),

	[_RAISE] = LAYOUT(
	//┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
	 	KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     		 KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
	//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	 	KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     		 KC_TRNS,  KC_7,    KC_8,    KC_9,  KC_TRNS, KC_TRNS,
	//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	 	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     		KC_TRNS,  KC_4,    KC_5,    KC_6,   KC_TRNS, KC_TRNS,
	//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 	KC_LSFT, KC_NUBS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,  KC_1,   KC_2,     KC_3,   KC_0,   KC_TRNS,
	//└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
	                               	   KC_TRNS, KC_TRNS, KC_TRNS,         			KC_TRNS, KC_TRNS, KC_TRNS
								  // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
	),

	[_ADJUST] = LAYOUT(
	//┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
	   BL_TOGG, BL_STEP, BL_BRTG, RGB_TOG, RGB_RMOD, RGB_MOD,                            _______, _______, _______, _______, _______, _______,
	//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	   BL_DEC, _______,   BL_INC, RGB_VAD, RGB_SAI, RGB_VAI,                            _______, _______, _______, _______, _______, _______,
	//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	   _______, _______, _______, RGB_HUD, RGB_SAD, RGB_HUI,                            _______, _______, _______, _______, _______, _______,
	//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	   _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
	//└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
									  _______, _______, _______,                   _______, _______, _______
								  // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
	)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case QWERTY:
			if (record->event.pressed) {
				set_single_persistent_default_layer(_QWERTY);
			}
			return false;
		case LOWER:
			if (record->event.pressed) {
				layer_on(_LOWER);
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
			} else {
				layer_off(_LOWER);
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
			}
			return false;
		case RAISE:
			if (record->event.pressed) {
				layer_on(_RAISE);
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
			} else {
				layer_off(_RAISE);
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
			}
			return false;

		case ADJUST:
		if (record->event.pressed) {
			layer_on(_ADJUST);
		} else {
			layer_off(_ADJUST);
		}
		return false;
	}
	return true;
}
