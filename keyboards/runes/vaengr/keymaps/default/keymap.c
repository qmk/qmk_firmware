/* Copyright 2021 Vicktor
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _DOUBLE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, 
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_DEL, 
		KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, 
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_UP, KC_ENT, 
		KC_LCTL, KC_LGUI, KC_GRV, KC_LALT, MO(1), KC_SPC, MO(2), KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT),

	[_LOWER] = LAYOUT(
		KC_F1, 	 KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, 
		KC_TRNS, KC_PGUP, KC_HOME, KC_DEL,  KC_BSPC, KC_TRNS, KC_TRNS, KC_MINS, KC_EQL,  KC_LCBR, KC_RCBR, KC_BSLS, 
		KC_TRNS, KC_PGDN, KC_END,  KC_ENT,  KC_TRNS, KC_TRNS, KC_TRNS, KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_PIPE, 
		KC_TRNS, KC_PSCR, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT, KC_SCRL, KC_PAUS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(3),   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	[_RAISE] = LAYOUT(
		KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NUM, KC_P7, KC_P8, KC_P9,KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_PMNS, KC_P4, KC_P5, KC_P6,KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_PAST, KC_P1, KC_P2, KC_P3,KC_TRNS, KC_PPLS, 
		KC_TRNS, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_PSLS, KC_P0, KC_PDOT, KC_PEQL,KC_TRNS, KC_PENT, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(3), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS),

	[_DOUBLE] = LAYOUT(
		KC_SLEP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};
