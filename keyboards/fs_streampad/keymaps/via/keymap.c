// Copyright 2023 Matthijs Muller
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
		KC_1, KC_2, KC_3,
		KC_4, KC_5, KC_6,
		KC_7, KC_8, MO(1)
	),

	[1] = LAYOUT(
		RGB_TOG, RGB_MOD, RGB_RMOD,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS
	)
};
