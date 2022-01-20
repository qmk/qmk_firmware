/* Copyright 2019 Brandon Schlack
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
    NUMPAD = 0,
    FN,
    NUMLOCK,
    KARABINER
};

#define DF_NMPD   DF(NUMPAD)
#define DF_NMLK   DF(NUMLOCK)
#undef  DF_KBNR
#define DF_KBNR   DF(KARABINER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[NUMPAD] = LAYOUT(
		KC_P7, KC_P8, KC_P9, \
		KC_P4, KC_P5, KC_P6, \
		KC_P1, KC_P2, KC_P3, \
		OSL(FN), KC_P0, KC_PDOT \
	),

	[FN] = LAYOUT(
		KC_PSLS, KC_PAST, KC_BSPC, \
		KC_TRNS, KC_TRNS, KC_PMNS, \
		DF_NMLK, DF_KBNR, KC_PPLS, \
		KC_TRNS, TG_ADJT, KC_PENT \
	),

    [NUMLOCK] = LAYOUT(
		KC_HOME, KC_UP, KC_PGUP, \
		KC_LEFT, CMD_TAB, KC_RGHT, \
		KC_END, KC_DOWN, KC_PGDN, \
		DF_NMPD, KC_INS, KC_DEL  \
	),

    [KARABINER] = LAYOUT(
		KC_F13, KC_F14, KC_F15, \
		KC_F16, KC_F17, KC_F18, \
		KC_F19, KC_F20, KC_F21, \
		LT(_ADJUST,KC_F22), KC_F23, KC_F24  \
	),

    [_ADJUST] = LAYOUT(
		QM_MAKE, EEP_RST, XXXXXXX, \
		XXXXXXX, XXXXXXX, XXXXXXX, \
		DF_NMPD, DF_NMLK, DF_KBNR, \
		KC_TRNS, XXXXXXX, XXXXXXX  \
	)
};
