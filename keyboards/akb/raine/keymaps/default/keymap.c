/* Copyright 2019 Elliot Powell
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
  [0] = LAYOUT( /* Base */
  KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_BSPC, KC_PSLS, KC_PAST, KC_PPLS,
	KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS, KC_P7, KC_P8, KC_P9,
	CTL_T(KC_CAPS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_NUHS, KC_ENT, KC_P4, KC_P5, KC_P6,
	KC_LSFT, KC_NUBS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_SLSH, KC_RSFT, KC_UP, KC_P1, KC_P2, KC_P3,
	KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_SPC, KC_BSPC, KC_RALT, MO(1), KC_LEFT, KC_DOWN, KC_RGHT, KC_P0, KC_PDOT),
  [1] = LAYOUT( /* Second */
  KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_DEL, KC_NLCK, KC_PSCR, KC_INS,
	_______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______, KC_HOME, KC_UP, KC_PGUP,
	_______, _______, _______, _______, _______, _______, _______, _______, KC_SCLN, KC_QUOT, _______, _______, KC_LEFT, KC_SLCK, KC_RGHT,
	_______, _______, _______, _______, _______, _______, _______, KC_COMM, KC_DOT, _______, _______, _______, KC_END, KC_DOWN, KC_PGDN,
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET),
};

