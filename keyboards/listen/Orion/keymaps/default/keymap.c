/* Copyright 2025 listen
This is the c configuration file for the keymap

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
			KC_ENTER, KC_PSLS, KC_PAST, KC_PMNS,
			KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS,
		KC_NO, KC_KP_4, KC_KP_5, KC_KP_6, KC_SPC,
		KC_COPY, KC_P1, KC_P2, KC_P3, KC_PENT,
		KC_PSTE, KC_P0, KC_KP_9, KC_PDOT, KC_BSPC
    )
};
