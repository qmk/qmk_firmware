/* Copyright 2021 bululau
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

#include "plus.h"
#include "oled.c"
#include "encoder.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
		TO(1), KC_MUTE, KC_SPACE,
		KC_KP_PLUS, KC_P7, KC_P8, KC_P9, KC_BSPC,
		KC_KP_MINUS, KC_P4, KC_P5, KC_P6, LT(1, KC_PENT),
		KC_KP_ASTERISK, KC_P1, KC_P2, KC_P3,
		KC_KP_SLASH, KC_P0, KC_KP_DOT),

	[1] = LAYOUT(
		TO(2), KC_MUTE, KC_SPACE,
		RESET, RGB_RMOD, RGB_MOD, KC_TRNS, RGB_TOG,
		KC_SYSTEM_WAKE, RGB_VAD, RGB_VAI, KC_TRNS, LT(1, KC_PENT),
		KC_SYSTEM_SLEEP, RGB_SAD, RGB_SAI, KC_TRNS,
		KC_SYSTEM_POWER, KC_PWR, RESET),

	[2] = LAYOUT(
		TO(3), KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS),

    [3] = LAYOUT(
		TO(4), KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS),

    [4] = LAYOUT(
		TO(5), KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS),

    [5] = LAYOUT(
		TO(6), KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS),

    [6] = LAYOUT(
		TO(7), KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS),

    [7] = LAYOUT(
		TO(0), KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS)

};




// LT(1, KC_KP_ENTER)
// LCTL(KC_C)
// LALT(KC_TAB)
// LWIN(KC_L)
// LGUI(kc)
// LSFT(kc)
// KC_MS_BTN1 鼠标单击
// LCTL(KC_LSHIFT)







