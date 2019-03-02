#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_numpad_5x6(
		KC_F1,   KC_F2,    KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
		KC_F3,   KC_F4,    KC_P7,   KC_P8,   KC_P9,
		KC_F5,   KC_F6,    KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
		KC_F7,   KC_F8,    KC_P1,   KC_P2,   KC_P3,
		KC_F9,   KC_F10,        KC_P0,       KC_PDOT, KC_PENT
    ),
};
