/* Copyright 2019 Kevin Lockwood
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
	[0] = LAYOUT_ortho_4x12(KC_TAB, KC_SCLN, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_DEL, KC_LCTL, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_ENT, KC_LSFT, KC_QUOT, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_RSFT, LT(2,KC_CAPS), MO(3), KC_LGUI, KC_LALT, KC_SPC, MO(1), MO(2), KC_BSPC, KC_RALT, KC_VOLD, KC_VOLU, LT(2,KC_MPLY)),
	[1] = LAYOUT_ortho_4x12(KC_PERC, KC_LBRC, KC_LCBR, KC_RCBR, KC_LPRN, KC_PEQL, KC_ASTR, KC_RPRN, KC_PLUS, KC_EXLM, KC_RBRC, KC_GRV, KC_LCTL, KC_7, KC_5, KC_3, KC_1, KC_9, KC_0, KC_2, KC_4, KC_6, KC_8, KC_MINS, KC_LSFT, KC_LBRC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_SLSH, KC_NO, KC_TRNS, KC_NO, KC_LGUI, KC_LALT, KC_SPC, KC_TRNS, KC_NO, KC_DEL, KC_RALT, KC_PSCR, KC_APP, KC_NO),
	[2] = LAYOUT_ortho_4x12(KC_WAKE, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_SLEP, KC_LCTL, KC_NO, KC_CUT, KC_COPY, KC_PSTE, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_ENT, KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_LGUI, KC_LALT, KC_BTN1, KC_BTN2, KC_TRNS, KC_NO, KC_RALT, KC_NO, KC_APP, KC_NO),
	[3] = LAYOUT_ortho_4x12(KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LCTL, KC_F7, KC_F5, KC_F3, KC_F1, KC_F9, KC_F10, KC_F2, KC_F4, KC_F6, KC_F8, KC_NO, KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_LGUI, KC_LALT, KC_SPC, KC_NO, KC_NO, KC_DEL, KC_RALT, KC_BRID, KC_BRIU, KC_NO)
};
