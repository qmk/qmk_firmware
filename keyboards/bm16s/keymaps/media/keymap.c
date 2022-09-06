#include QMK_KEYBOARD_H

#define RGB_BRU RGB_VAI
#define RGB_BRD RGB_VAD

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT_ortho_4x4(
		KC_BRIU, _______, _______, KC_VOLU, \
		KC_BRID, _______, _______, KC_VOLD, \
		_______, _______, _______, KC_MUTE, \
		KC_MPRV, KC_MPLY, KC_MNXT, MO(1)    \
	),
	[1] = LAYOUT_ortho_4x4(
		RESET,    _______, _______, _______, \
		RGB_SPD,  RGB_BRU, RGB_SPI, _______, \
		RGB_RMOD, RGB_BRD, RGB_MOD, _______, \
		RGB_TOG,  _______, _______, _______  \
	),
};