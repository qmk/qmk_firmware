#include QMK_KEYBOARD_H


#define QWER 0
#define GAMING 1
#define HHKB 2
#define UTIL 3
#define LIGHTING 4
#define HPR_TAB ALL_T(KC_TAB) // Tap for Tab, hold for Hyper (Super+Ctrl+Shift+Alt)
#define TG_GAME TG(GAMING)

enum custom_keycodes {
    FN_HHKB = SAFE_RANGE,
    FN_UTIL
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
	switch(keycode) {
		case FN_HHKB:
			if (record->event.pressed) {
				layer_on(2);
				update_tri_layer(2, 3, 4);
			} else {
				layer_off(2);
				update_tri_layer(2, 3, 4);
			}
			return false;
			break;
		case FN_UTIL:
			if (record->event.pressed) {
				layer_on(3);
				update_tri_layer(2, 3, 4);
			} else {
				layer_off(3);
				update_tri_layer(2, 3, 4);
			}
			return false;
			break;
    default:
      return true;
	}
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[QWER] = LAYOUT_60_hhkb(
	KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
	HPR_TAB, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
	KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
	KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, FN_HHKB,
	         KC_LALT, KC_LGUI,                            LT(UTIL, KC_SPC),                   KC_RGUI, FN_UTIL),

[GAMING] = LAYOUT_60_hhkb(
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
	 KC_TAB, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
	         _______, _______,                             KC_SPC,                            _______, _______),

[HHKB] = LAYOUT_60_hhkb(
	KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
	KC_CAPS, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP,   _______, _______,
	_______, KC_VOLD, KC_VOLU, KC_MUTE, KC_EJCT, _______, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, _______,
	_______, _______, _______, _______, _______, _______, KC_PPLS, KC_PMNS, KC_END,  KC_PGDN, KC_DOWN, _______, _______,
	         _______, _______,                            _______,                            _______, _______),

[UTIL] = LAYOUT_60_hhkb(
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
	_______, KC_MPLY, KC_MPRV, KC_MNXT, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, _______, _______,
	_______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______,
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
	         _______, _______,                            _______,                            _______, _______),

[LIGHTING] = LAYOUT_60_hhkb(
	RESET,   EF_DEC,  EF_INC,  H1_DEC,  H1_INC,  H2_DEC,  H2_INC,  _______, _______, _______, _______, BR_DEC,  BR_INC,  _______, _______,
	TG_GAME, _______, _______, S1_DEC,  S1_INC,  S2_DEC,  S2_INC,  _______, _______, _______, _______, ES_DEC,  ES_INC,  _______,
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
	         _______, _______,                            _______,                            _______, _______),

};
