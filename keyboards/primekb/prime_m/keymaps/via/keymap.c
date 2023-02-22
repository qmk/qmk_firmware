/* Copyright 2020 Holten Campbell
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
	[0] = LAYOUT_ortho_5x6(
		KC_ESC,  KC_LPRN, KC_RPRN, KC_PSLS, KC_PAST, LT(2, KC_BSPC),
		KC_F1,   KC_F2,   KC_P7,   KC_P8,   KC_P9,   KC_DEL,
		KC_F3,   KC_F4,   KC_P4,   KC_P5,   KC_P6,   KC_PMNS,
		KC_F5,   KC_F6,   KC_P1,   KC_P2,   KC_P3,   KC_PPLS,
		KC_LCTL, KC_LALT, TO(1),   KC_P0,   KC_PDOT, KC_PENT
    ),

	[1] = LAYOUT_ortho_5x6(
		KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    LT(2, KC_F9),
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
		KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
		KC_LCTL, KC_LALT, TO(0),   KC_P,    KC_H,    KC_SPC
    ),

    [2] = LAYOUT_ortho_5x6(
		BL_TOGG, BL_STEP, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, KC_VOLU,
		_______, _______, _______, _______, KC_MUTE, KC_VOLD
    ),

    [3] = LAYOUT_ortho_5x6(
		_______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______
    )

};
