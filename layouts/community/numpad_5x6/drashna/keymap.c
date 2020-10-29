/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include "drashna.h"

#define F2_MCRO LT(_GAMEPAD, KC_F2)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_NUMLOCK] = LAYOUT_numpad_5x6(
		KC_F1,   F2_MCRO,  KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
		KC_F3,   KC_F4,    KC_P7,   KC_P8,   KC_P9,
		KC_F5,   KC_F6,    KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
		KC_F7,   KC_F8,    KC_P1,   KC_P2,   KC_P3,
		KC_F9,   KC_COLN,       KC_P0,       KC_PDOT, KC_PENT
  ),

  [_GAMEPAD] = LAYOUT_numpad_5x6(
		RGB_TOG, _______,  _______, EEP_RST, KC_MAKE, RESET,
		RGB_MOD, RGB_RMOD, _______, _______, _______,
		RGB_HUI, RGB_HUD,  _______, _______, _______, _______,
		RGB_SAI, RGB_SAD,  _______, _______, _______,
		RGB_VAI, RGB_VAD,       _______,     _______, _______
  ),
};
// clang-format on
