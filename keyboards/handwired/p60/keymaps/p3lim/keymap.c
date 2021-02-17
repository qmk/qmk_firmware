#include QMK_KEYBOARD_H

enum my_keycodes {
	C_ESC0 = SAFE_RANGE, // layer 0 esc
	C_ESC1,              // layer 1 esc
	C_NO1,               // æ, requires RCTL to be a compose key in software
	C_NO2,               // ø, requires RCTL to be a compose key in software
	C_NO3                // å, requires RCTL to be a compose key in software
};

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
	[0] = LAYOUT(
		C_ESC0,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_ENT,
		KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_DEL,
		MO(1),   KC_LALT, KC_LGUI,                   KC_SPC,                             MO(2),   KC_RGUI, KC_RALT, KC_RCTL
	),

	/* FN1
	* ,-----------------------------------------------------------------------------------------.
	* |  `  | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |           |
	* |-----------------------------------------------------------------------------------------+
	* |  Caps  | Home| Up  | End | PgUp|     |     |     |     |     |     |     |     |        |
	* |---------------------------------------------------------------------------------|       |
	* |         | Left| Down|Right| PgDn|     |     |     |     |     |     |     |     |       |
	* |-----------------------------------------------------------------------------------------+
	* |           | KVM1| KVM2| KVM3| KVM4|     |     |     |     |     |     |           |     |
	* |-----------------------------------------------------------------------------------------+
	* |       |     |        |                                         |        |     |         |
	* `-----------------------------------------------------------------------------------------'
	*/
	[1] = LAYOUT(
		C_ESC1,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
		KC_CAPS, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_PSCR, _______, _______, _______, _______, _______, _______, _______,
		_______, KC_VOLD, KC_MUTE, KC_VOLU, KC_F17,  _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______,                   _______,                            KC_NO,   _______, _______, _______
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
	[2] = LAYOUT(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, C_NO3,   _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, C_NO2,   C_NO1,   _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		KC_NO,   _______, _______,                   _______,                            _______, _______, _______, _______
	),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record){
	switch(keycode){
		case C_ESC0: // layer 0
			if(record->event.pressed){
				if(get_mods() & MOD_MASK_SHIFT)
					register_code(KC_GRAVE);
				else
					register_code(KC_ESCAPE);
			} else {
				if(get_mods() & MOD_MASK_SHIFT)
					unregister_code(KC_GRAVE);
				else
					unregister_code(KC_ESCAPE);
			}
			return false;
		case C_ESC1: // layer 1
			if(record->event.pressed){
				if(get_mods() & MOD_MASK_SHIFT)
					register_code(KC_ESCAPE);
				else
					register_code(KC_GRAVE);
			} else {
				if(get_mods() & MOD_MASK_SHIFT)
					unregister_code(KC_ESCAPE);
				else
					unregister_code(KC_GRAVE);
			}
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
				if(get_mods() & MOD_MASK_SHIFT){
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
				if(get_mods() & MOD_MASK_SHIFT){
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
