#include QMK_KEYBOARD_H

enum layer_names {
    HOME,
    MODS,
    MODS2,
    OTHER,
};

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
		KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, MT(MOD_LCTL,KC_P),
		KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, MT(MOD_LSFT,KC_ENT),
		KC_Z, KC_X, KC_C, LT(MODS2,KC_V), LT(MODS, KC_SPC), LT(OTHER,KC_B), KC_N, KC_M),

	[MODS] = LAYOUT(
		KC_TAB, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_BSPC,
		KC_LSFT, KC_ESC, _______, KC_SCLN, KC_QUOT, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______,
		KC_LCTL, KC_LGUI, KC_LALT, _______, _______, KC_COMM, KC_DOT, KC_SLSH),

	[MODS2] = LAYOUT(
		KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
		KC_LSFT, KC_ESC, _______, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV, _______,
		RGB_VAI, RGB_VAD, RGB_HUI, _______, _______, KC_MPLY, KC_VOLD, KC_VOLU),

	[OTHER] = LAYOUT(
		KC_ESC, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_DEL,
		KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, _______,
		KC_F10, KC_F11, KC_F12, _______, _______, KC_NO, KC_NO, KC_NO),
};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}