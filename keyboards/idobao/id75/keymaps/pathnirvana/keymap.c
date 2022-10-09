/* Copyright 2021 pathnirvana (pathnirvana@gmail.com)
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
	[0] = LAYOUT_ortho_5x15(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_GRV, KC_MINS, KC_EQL, KC_6, KC_7, KC_8, KC_9, KC_0, KC_F5, 
		KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_LBRC, KC_BSLS, KC_RBRC, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_QUOT, 
		KC_BSPC, KC_A, KC_R, KC_S, KC_T, KC_G, KC_PGUP, KC_DEL, KC_PGDN, KC_M, KC_N, KC_E, KC_I, KC_O, KC_ENT, 
		KC_LSFT, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_HOME, KC_UP, KC_END, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_NO, 
		KC_LCTL, KC_MS_BTN3, KC_LALT, LT(2,KC_F2), KC_SPC, LSFT_T(KC_SPC), KC_LEFT, KC_DOWN, KC_RGHT, LT(3,KC_DEL), RSFT_T(KC_BSPC), LALT(KC_LSFT), KC_NO, DF(1), KC_ENT),
	[1] = LAYOUT_ortho_5x15(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_GRV, KC_MINS, KC_EQL, KC_6, KC_7, KC_8, KC_9, KC_0, KC_F5, 
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_LBRC, KC_BSLS, KC_RBRC, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_QUOT, 
		KC_BSPC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_PGUP, KC_DEL, KC_PGDN, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT, 
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_HOME, KC_UP, KC_END, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_NO, 
		KC_LCTL, KC_LGUI, KC_LALT, LT(2,KC_F2), KC_SPC, LSFT_T(KC_SPC), KC_LEFT, KC_DOWN, KC_RGHT, LT(3,KC_DEL), RSFT_T(KC_BSPC), LALT(KC_LSFT), KC_NO, DF(0), KC_ENT),
	[2] = LAYOUT_ortho_5x15(
		KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_MUTE, KC_VOLD, KC_VOLU, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, 
		KC_MSEL, BL_BRTG, RGB_HUD, RGB_HUI, KC_NO, KC_NO, KC_PSCR, KC_SLCK, KC_PAUS, LSFT(KC_LEFT), LSFT(KC_DOWN), LSFT(KC_UP), LSFT(KC_RGHT), KC_NO, KC_NO, 
		KC_SLEP, BL_STEP, RGB_SAD, RGB_SAI, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, QK_BOOT, 
		KC_NO, BL_TOGG, RGB_VAD, RGB_VAI, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO, LCTL(KC_LEFT), LCTL(KC_DOWN), LCTL(KC_UP), LCTL(KC_RGHT), KC_NO, KC_NO, 
		KC_NO, RGB_TOG, RGB_RMOD, RGB_MOD, KC_NO, KC_NO, KC_WBAK, KC_NO, KC_WFWD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[3] = LAYOUT_ortho_5x15(
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
		KC_NO, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_TILD, KC_UNDS, KC_PLUS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_NO, 
		KC_NO, KC_QUOT, KC_BSLS, KC_LCBR, KC_LBRC, KC_LT, KC_NO, KC_NO, KC_NO, KC_GT, KC_RBRC, KC_RCBR, KC_PIPE, KC_DQUO, KC_NO, 
		KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5, KC_GRV, KC_MINS, KC_EQL, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO, 
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
};
