#include QMK_KEYBOARD_H

#define _BL 0
#define _FN1 1
#define _FN2 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BL] = LAYOUT_ortho(
		KC_GESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
		KC_CAPS, KC_LCTL, KC_LALT, KC_LGUI, MO(1), KC_SPC, KC_SPC, MO(2), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),

	[_FN1] = LAYOUT_ortho(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_MINS, KC_EQL, KC_BSLS, KC_DEL,
		KC_TRNS, KC_TRNS, KC_TRNS, M(1), M(1), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_END, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY),

	[_FN2] = LAYOUT_ortho(
		KC_PWR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS,
		KC_TRNS, BL_TOGG, BL_STEP, BL_INC, BL_DEC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL,
		KC_TRNS, RGB_TOG, RGB_MOD, RGB_VAI, RGB_VAD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, KC_HOME, KC_END, KC_TRNS,
		QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_PGDN, KC_PGUP, KC_MPLY),

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {


	switch (id) {
		case 1:
			if (record->event.pressed) {
				return MACRO( D(LCTL), T(C), U(LCTL), END );
			}
			break;
		case 2:
			if (record->event.pressed) {
				return MACRO( D(LCTL), T(V), U(LCTL), END );
			}
			break;
	}
	return MACRO_NONE;
}
