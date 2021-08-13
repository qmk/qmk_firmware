/*
Copyright 2019-2021 Adrian L Lange <legal@p3lim.net>

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

#include QMK_KEYBOARD_H

#define LAYOUT_p3lim(\
  K04, K14, K24, K34, K44, K54, K16, KB6, KB7, K17, KA4, KB4, KC4, KE4, \
  K03, K13, K23, K33, K43, K53, K26, KC6, KC7, K27, KA3, KB3, KC3, \
  K02, K12, K22, K32, K42, K52, K36, KD6, KD7, K37, KA2, KB2, KC2, KD2, \
  K01, K11, K21, K31, K41, K51, K46, KE6, KE7, K47, KA1, KB1, KC1, \
  K00, K10, K20,           K56,                K57, KB0, KC0  \
){ \
  { K00,   K10,   K20,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KB0,   KC0,   KC_NO, KC_NO }, \
  { K01,   K11,   K21,   K31,   K41,   K51,   KC_NO, KC_NO, KC_NO, KC_NO, KA1,   KB1,   KC1,   KC_NO, KC_NO }, \
  { K02,   K12,   K22,   K32,   K42,   K52,   KC_NO, KC_NO, KC_NO, KC_NO, KA2,   KB2,   KC2,   KD2,   KC_NO }, \
  { K03,   K13,   K23,   K33,   K43,   K53,   KC_NO, KC_NO, KC_NO, KC_NO, KA3,   KB3,   KC3,   KC_NO, KC_NO }, \
  { K04,   K14,   K24,   K34,   K44,   K54,   KC_NO, KC_NO, KC_NO, KC_NO, KA4,   KB4,   KC4,   KC_NO, KE4   }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { KC_NO, K16,   K26,   K36,   K46,   K56,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KB6,   KC6,   KD6,   KE6   }, \
  { KC_NO, K17,   K27,   K37,   K47,   K57,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KB7,   KC7,   KD7,   KE7   } \
}

enum my_keycodes {
	C_ESC0 = SAFE_RANGE, // layer 0 esc
	C_ESC1,              // layer 1 esc
	C_NO1,               // æ, requires RCTL to be a compose key in software
	C_NO2,               // ø, requires RCTL to be a compose key in software
	C_NO3                // å, requires RCTL to be a compose key in software
};

// use compiler macros for simpler stuff
#define C_KVM1 LCA(KC_1)
#define C_KVM2 LCA(KC_2)
#define C_KVM3 LCA(KC_3)
#define C_KVM4 LCA(KC_4)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* QWERTY
	* ,-----------------------------------------------------------------------------------------.
	* | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |   Bkspc   |
	* |-----------------------------------------------------------------------------------------+
	* |   Tab  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |        |
	* |---------------------------------------------------------------------------------| Enter |
	* |   Ctrl  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |  \  |       |
	* |-----------------------------------------------------------------------------------------+
	* |   Shift   |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |   Shift   | Del |
	* |-----------------------------------------------------------------------------------------+
	* |  FN1  | Alt |  GUI   |              Space                      |  FN2   | Alt |  Ctrl   |
	* `-----------------------------------------------------------------------------------------'
	*/
	[0] = LAYOUT_p3lim(
		C_ESC0,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
		KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_DEL,
		MO(1),   KC_LALT, KC_LGUI,                   KC_SPC,                             MO(2),   KC_RGUI, KC_RCTL
	),

	/* FN1
	* ,-----------------------------------------------------------------------------------------.
	* |  `  | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |           |
	* |-----------------------------------------------------------------------------------------+
	* |  Caps  | Home| Up  | End | PgUp|     |     |     |     |     |     |     |     |        |
	* |---------------------------------------------------------------------------------|       |
	* |         | Left| Down|Right| PgDn|PrtSc|     |     |     |     |     |     |     |       |
	* |-----------------------------------------------------------------------------------------+
	* |           | KVM1| KVM2| KVM3| KVM4|     |     |     |     |     |     |           |     |
	* |-----------------------------------------------------------------------------------------+
	* |       |     |        |                                         |        |     |         |
	* `-----------------------------------------------------------------------------------------'
	*/
	[1] = LAYOUT_p3lim(
		C_ESC1,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
		KC_CAPS, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_PSCR, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, C_KVM1,  C_KVM2,  C_KVM3,  C_KVM4,  _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______,                   _______,                            KC_NO,   _______, _______
	),

	/* FN2
	* ,-----------------------------------------------------------------------------------------.
	* |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
	* |-----------------------------------------------------------------------------------------+
	* |        |     |     |     |     |     |     |     |     |     |     |  Å  |     |        |
	* |---------------------------------------------------------------------------------|       |
	* |         |     |     |     |     |     |     |     |     |     |  Ø  |  Æ  |     |       |
	* |-----------------------------------------------------------------------------------------+
	* |           |     |     |     |     |     |     |     |     |     |     |           |     |
	* |-----------------------------------------------------------------------------------------+
	* |       |     |        |                                         |        |     |         |
	* `-----------------------------------------------------------------------------------------'
	*/
	[2] = LAYOUT_p3lim(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, C_NO3,   _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, C_NO2,   C_NO1,   _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		KC_NO,   _______, _______,                   _______,                            _______, _______, _______
	),
	/*
	[n] = LAYOUT_p3lim(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______,                   _______,                            _______, _______, _______
	),
	*/
};

static bool grave_esc_shifted = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record){
	const uint8_t mods = get_mods();
	uint8_t shifted = mods & MOD_MASK_SHIFT;

	switch(keycode){
		case C_ESC0: // layer 0
			if(record->event.pressed){
				grave_esc_shifted = shifted;
				register_code(shifted ? KC_GRAVE : KC_ESCAPE);
			} else
				unregister_code(grave_esc_shifted ? KC_GRAVE : KC_ESCAPE);
			return false;
		case C_ESC1: // layer 1
			if(record->event.pressed){
				grave_esc_shifted = shifted;
				register_code(shifted ? KC_ESCAPE : KC_GRAVE);
			} else
				unregister_code(grave_esc_shifted ? KC_ESCAPE : KC_GRAVE);
			return false;
		case C_NO1: // æ
			if(record->event.pressed){
				// we use shift for A and E to make it capitalized, no need to handle it here
				tap_code(KC_RCTL);
				tap_code(KC_A);
				tap_code(KC_E);
			}
			return false;
		case C_NO2: // ø
			// the "/" symbol can't be shifted, so we have to deal with that
			if(record->event.pressed){
				if(shifted){
					unregister_code(KC_LSFT); // reset the shift state, I always use LSFT personally
					tap_code(KC_RCTL);
					tap_code(KC_SLSH);
					tap_code16(S(KC_O));
					register_code(KC_LSFT); // enable the shift state again to keep state consistent
				} else {
					tap_code(KC_RCTL);
					tap_code(KC_SLSH);
					tap_code(KC_O);
				}
			}
			return false;
		case C_NO3: // å
			// the "o" symbol can't be shifted, so we have to deal with that
			if(record->event.pressed){
				if(shifted){
					unregister_code(KC_LSFT); // reset the shift state, I always use LSFT personally
					tap_code(KC_RCTL);
					tap_code(KC_O);
					tap_code16(S(KC_A));
					register_code(KC_LSFT); // enable the shift state again to keep state consistent
				} else {
					tap_code(KC_RCTL);
					tap_code(KC_O);
					tap_code(KC_A);
				}
			}
			return false;
	}
	return true;
}
