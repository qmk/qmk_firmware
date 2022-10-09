/*
Copyright 2019 Ethan Durrant (emdarcher)

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

enum layer_names {
  _BL,
  _FL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //Base Layer
    [_BL] = LAYOUT_all(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_GRV, KC_BSPC, 
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, 
		LT(_FL, KC_CAPS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_NO, MT(MOD_RCTL, KC_ENT), 
		KC_LSPO, KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, KC_UP, KC_DEL, 
		KC_LCTL, KC_LGUI, KC_LALT, MO(_FL), KC_SPC, MO(_FL), KC_RALT, KC_APP, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    //FN Layer
    [_FL] = LAYOUT_all(
		KC_TILD, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, QK_BOOT, 
		_______, _______, KC_HOME, KC_UP, KC_END, KC_PGUP, _______, NK_TOGG, KC_PSCR, KC_SLCK, KC_PAUS, _______, BL_STEP, BL_TOGG, 
		_______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, KC_INS, KC_HOME, KC_PGUP, KC_BSPC, _______, _______, _______, 
		_______, _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_VAD, RGB_VAI, _______, KC_DEL, KC_END, KC_PGDN, _______, _______, _______, _______, 
		_______, _______, _______, _______, KC_ENT, _______, _______, _______, _______, _______, _______
    ),
};
