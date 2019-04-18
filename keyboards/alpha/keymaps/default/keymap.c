#include QMK_KEYBOARD_H

#define HOME 0
#define MODS 1
#define MODS2 2
#define OTHER 3

enum custom_keycodes {
	MACRO1 = SAFE_RANGE
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (record->event.pressed) {
		switch (keycode) {
			case MACRO1:
				SEND_STRING("I'm so sorry... -PyroL");
				return false;
		}
	}
	return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[HOME] = LAYOUT(
		KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
		KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, TO(1),
		KC_Z, KC_X, KC_C, KC_V, MT(MOD_LSFT, KC_SPC), KC_B, KC_N, KC_M),

	[MODS] = LAYOUT(
		KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
		KC_BSPC, KC_ESC, KC_TAB, KC_SCLN, KC_QUOT, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, TO(2),
		KC_LCTL, KC_LGUI, KC_LALT, TO(0), MT(MOD_LSFT, KC_ENT), KC_COMM, KC_DOT, KC_SLSH),

	[MODS2] = LAYOUT(
		KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
		KC_LSFT, KC_F11, KC_F12, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV, TO(3),
		RGB_VAI, RGB_VAD, RGB_HUI, TO(0), RGB_MOD, KC_MPLY, KC_VOLD, KC_VOLU),

	[OTHER] = LAYOUT(
		RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, TO(0), MACRO1, KC_NO, KC_NO, KC_NO),
};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}
