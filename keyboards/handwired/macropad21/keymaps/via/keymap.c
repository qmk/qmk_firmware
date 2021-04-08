/*
Copyright 2021 Taktloss
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
#include <quantum/keymap_extras/keymap_german.h>

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * ,----------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |
 * |------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |
 * |------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |
 * |------+------+------+------+------|
 * | LAlt |   Y  |      |   C  |   V  |
 * |------+------'      |------+------|
 * |  MO  |             |   Space     |
 * `------'             --------------'
*/
	[_BASE] = LAYOUT(
		KC_ESC, KC_1, KC_2, KC_3, KC_4,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R,
		KC_LSFT, KC_A, KC_S, KC_D, KC_F,
		KC_LALT, DE_Y, KC_C, KC_V,
		MO(_FN), KC_SPACE),
	[_FN] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC,
		KC_TRNS, DE_ODIA, DE_ADIA, DE_UDIA, DE_SS,
		KC_TRNS, LGUI(KC_D), KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, RESET, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_BTN1)
};
