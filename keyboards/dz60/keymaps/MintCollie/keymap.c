#include QMK_KEYBOARD_H

// Make special keycodes more visible
#define ____ KC_TRNS
#define XXXX KC_NO

// Layer definition
#define L0 0
#define L1 1
//#define L2 2

enum custom_keycodes {
	QMKBEST = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case QMKBEST:
			if (record->event.pressed) {
				// when keycode QMKBEST is pressed
				SEND_STRING("QMK is the best thing ever!");
			} else {
				// when keycode QMKBEST is released
				register_code(KC_ENT);
				unregister_code(KC_ENT);
			}
			break;
	}
	return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Base layer - ANSI QWERTY
[L0] = LAYOUT_all(
	KC_ESCAPE, KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  XXXX,   KC_BSPC,
	KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
	KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
	KC_LSFT, XXXX,    KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,    KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,  KC_SLSH,
	KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_SPC, KC_SPC, KC_RALT, MO(L1), KC_LEFT, KC_DOWN, KC_RIGHT),

// Utility layer - RGB and multimedia control
[L1] = LAYOUT_all(
	KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, XXXX, KC_DEL,
	____, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, ____, ____, ____, ____, RESET,
	____, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,RGB_M_SN,RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, ____, ____, ____,
	____, XXXX, ____, ____, ____, BL_DEC, BL_TOGG, BL_INC, BL_STEP, ____, ____, ____, ____, ____, ____,
	____, ____, ____, ____, ____, ____, ____, ____, KC_HOME, QMKBEST, KC_END),
};

