#include QMK_KEYBOARD_H

#define HOME 0
#define MEDIA 1
#define MACRO 2
#define SETTINGS 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[HOME] = LAYOUT(
					  KC_P0,
		KC_P7, KC_P8, KC_P9,
		KC_P4, KC_P5, KC_P6,
		LT(1, KC_P1), LT(2, KC_P2), LT(3, KC_P3)),

	[MEDIA] = LAYOUT(
						  KC_MUTE,
		KC_MPLY, KC_NO,   KC_VOLU,
		KC_MPRV, KC_MNXT, KC_VOLD,
		KC_TRNS, KC_NO,   KC_NO),

	[MACRO] = LAYOUT(
						KC_F13,
		KC_F14, KC_F15, KC_F16,
		KC_F19, KC_F18, KC_F17,
		KC_NO,  KC_TRNS, KC_NO),

	[SETTINGS] = LAYOUT(
						RESET,
		KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_TRNS),
};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}