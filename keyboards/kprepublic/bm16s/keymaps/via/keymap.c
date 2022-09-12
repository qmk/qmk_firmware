/* Copyright 2020 Relocks
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ortho_4x4(
		KC_KP_7, KC_KP_8, KC_KP_9, MO(1),
		KC_KP_4, KC_KP_5, KC_KP_6, KC_PMNS,
		KC_KP_1, KC_KP_2, KC_KP_3, KC_PPLS,
		KC_KP_0, KC_PDOT, KC_PCMM, KC_PENT
	),
	[1] = LAYOUT_ortho_4x4(
		QK_BOOT,   BL_STEP, KC_TRNS, KC_VOLU,
		BL_TOGG, BL_DEC,  BL_INC,  KC_VOLD,
		RGB_TOG, RGB_MOD, RGB_HUI, KC_MUTE,
		RGB_SAI, RGB_SAD, RGB_HUD, KC_TRNS
	),
	[2] = LAYOUT_ortho_4x4(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),
	[3] = LAYOUT_ortho_4x4(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),
};
