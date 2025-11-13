/* Copyright 2018 Ryota Goto
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

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  MANUAL = SAFE_RANGE,
  DBLZERO
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT( /* Base */
		TO(1),   KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_BSPC,
		TO(1),   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_RBRC, KC_BSLS,
		KC_NO,   KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_NO,   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_PSCR, KC_DEL,
			     KC_LCTL, KC_LCTL, KC_LGUI, KC_LALT, MO(1),   KC_SPC,  KC_SPC,  MO(2),   KC_GRV,  KC_MENU, KC_MINS, KC_EQL 
	),
	[1] = LAYOUT( /* Fn, Arrowkeys, Media control, Backlight */
		TO(2),   _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_VOLU, _______,
		TO(2),   _______, _______, KC_PGUP, _______, _______, KC_F11,  KC_F12,  _______, KC_UP,   _______, _______, KC_VOLD, BL_STEP,
		TO(0),   _______, KC_HOME, KC_PGDN, KC_END,  _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_MPLY, _______,
		TO(0),   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,
			     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
	),
	[2] = LAYOUT( /* Mousekeys and Numpad */
		KC_NO,   _______, _______, _______, _______, _______, _______, KC_NUM,  KC_P7,   KC_P8,   KC_P9,   KC_PSLS, _______, _______,
		KC_NO,   _______, MS_BTN1, MS_UP,   MS_BTN2, MS_WHLU, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PAST, _______, _______,
		TO(1),   _______, MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLD, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PMNS, _______, _______,
		TO(1),   _______, MS_ACL0, MS_ACL1, MS_ACL2, MS_BTN3, _______, DBLZERO, KC_P0,   KC_PDOT, KC_PENT, KC_PPLS, _______, MANUAL,
			     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
	)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case MANUAL:
			if (record->event.pressed) {
				SEND_STRING("https://kb.ai03.me/redir/orbit");
			}
			break;
		case DBLZERO:
			if (record->event.pressed) {
				SEND_STRING("00");
			}
			break;
  }
  return true;
}
