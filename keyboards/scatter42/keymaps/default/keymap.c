/* Copyright 2020 bbrfkr
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
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [0] = LAYOUT(KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_LCTL, KC_LSFT, KC_TAB, KC_LGUI, MO(1), KC_SPC, KC_ENT, MO(2), KC_RALT, KC_BSPC, KC_RSFT, KC_RCTL),
        [1] = LAYOUT(KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_F11, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_F12, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_LCTL, KC_LSFT, KC_ESC, KC_LGUI, KC_TRNS, KC_SPC, KC_ENT, MO(3), KC_RALT, KC_DEL, KC_RSFT, KC_PSCR),
        [2] = LAYOUT(KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_NO, KC_NO, KC_NO, KC_BSLS, KC_GRV, KC_MINS, KC_EQL, KC_QUOT, KC_LCBR, KC_RCBR, KC_NO, KC_NO, KC_NO, KC_PIPE, KC_TILD, KC_UNDS, KC_PLUS, KC_DQUO, KC_LBRC, KC_RBRC, KC_LCTL, KC_LSFT, KC_ESC, KC_LGUI, MO(3), KC_SPC, KC_ENT, KC_TRNS, KC_RALT, KC_DEL, KC_RSFT, KC_RCTL),
        [3] = LAYOUT(KC_VOLU, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BRIU, KC_VOLD, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO, KC_NO, KC_NO, KC_NO, KC_BRID, KC_MUTE, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO)
};
