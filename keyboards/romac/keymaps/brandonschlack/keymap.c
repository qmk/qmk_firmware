/* Copyright 2018 Jack Humbert
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
#include "brandonschlack.h"

enum romac_layers {
    __NUMPAD = 0,
    __FN,
    __NUMLOCK,
    __MACRO
};

enum romac_keycodes {
    DF_NMPD = KEYMAP_SAFE_RANGE,
    DF_NMLK,
    DF_MCRO,
    DF_MAGC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[__NUMPAD] = LAYOUT(
		KC_P7, KC_P8, KC_P9, \
		KC_P4, KC_P5, KC_P6, \
		KC_P1, KC_P2, KC_P3, \
		OSL(_FN), KC_P0, KC_PDOT \
	),

	[__FN] = LAYOUT(
		KC_PSLS, KC_PAST, KC_BSPC, \
		KC_TRNS, KC_TRNS, KC_PMNS, \
		DF_NMLK, DF_MCRO, KC_PPLS, \
		KC_TRNS, DF_MAGC, KC_PENT \
	),

    [__NUMLOCK] = LAYOUT(
		KC_HOME, KC_UP, KC_PGUP, \
		KC_LEFT, CMD_TAB, KC_RGHT, \
		KC_END, KC_DOWN, KC_PGDN, \
		DF_NMPD, KC_INS, KC_DEL  \
	),

    [__MACRO] = LAYOUT(
		KC_F13, KC_F14, KC_F15, \
		KC_F16, KC_F17, KC_F18, \
		KC_F19, KC_F20, KC_F21, \
		LT(_MAGIC,KC_F22), KC_F23, KC_F24  \
	),

    [_MAGIC] = LAYOUT(
		KC_MAKE, XXXXXXX, XXXXXXX, \
		XXXXXXX, XXXXXXX, XXXXXXX, \
		DF_NMPD, DF_NMLK, DF_MCRO, \
		KC_TRNS, XXXXXXX, XXXXXXX  \
	)
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DF_NMPD:
            if (!record->event.pressed) {
                default_layer_set(__NUMPAD);
                layer_move(default_layer_state);
            }
            break;
        case DF_NMLK:
            if (!record->event.pressed) {
                default_layer_set(__NUMLOCK);
                layer_move(default_layer_state);
            }
            break;
        case DF_MCRO:
            if (!record->event.pressed) {
                default_layer_set(__MACRO);
                layer_move(default_layer_state);
            }
            break;
        case DF_MAGC:
            if (!record->event.pressed) {
                default_layer_set(_MAGIC);
                layer_move(default_layer_state);
            }
            break;
    }
    return true;
}
