#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ortho_4x4(
		KC_KP_7, KC_KP_8, KC_KP_9, MO(1),
		KC_KP_4, KC_KP_5, KC_KP_6, KC_PMNS,
		KC_KP_1, KC_KP_2, KC_KP_3, KC_PPLS,
		KC_KP_0, KC_PDOT, KC_PCMM, KC_PENT
	),
	[1] = LAYOUT_ortho_4x4(
		QK_BOOT,   BL_STEP, _______, KC_VOLU,
		BL_TOGG, BL_DOWN, BL_UP,   KC_VOLD,
		RGB_TOG, RGB_MOD, RGB_HUI, KC_MUTE,
		RGB_SAI, RGB_SAD, RGB_HUD, _______
	),
};