/* Copyright 2021 bitstarr
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

#define WORD_BACK C(KC_LEFT)
#define WORD_FORWARD C(KC_RIGHT)

enum layers {
	_BASE,
    _EXT,
	_ADV,
	_FN,
	_UNI,
	_UNI2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, LT(_EXT,KC_SPC), MO(_UNI), MO(_ADV), MO(_FN), KC_RCTL
    ),
    [_EXT] = LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS,
        KC_TRNS, KC_F11, KC_F12, KC_NO, KC_NO, KC_GRV, KC_SCLN, KC_QUOT, KC_LBRC, KC_RBRC, KC_BSLS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS
    ),
    [_ADV] = LAYOUT(
        KC_GRV, WORD_BACK, KC_UP, WORD_FORWARD, KC_NO, KC_NO, KC_NO, KC_NO, KC_PGUP, KC_NO, KC_PSCR, KC_DEL,
        KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, KC_NO, KC_HOME, KC_PGDN, KC_END, KC_NO,
        KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_MUTE, KC_VOLU, KC_NO, KC_NO, KC_NO, KC_INS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS
    ),
    [_FN] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    [_UNI] = LAYOUT(
        KC_NO, KC_NO, KC_NO, UC(L'€'), UC(L'§'), UC(L'°'), KC_NO, UC(L'ü'), KC_NO, UC(L'ö'), UC(L'–'), KC_NO,
        KC_NO, UC(L'ä'), UC(L'ß'), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        MO(_UNI2), UC(L'„'), UC(L'“'), UC(L'”'), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, UC(L'…'), KC_NO,
        KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, UC_MOD
    ),
    [_UNI2] = LAYOUT(
        KC_NO, KC_NO, KC_NO, UC(L'é'), KC_NO, KC_NO, KC_NO, UC(L'Ü'), KC_NO, UC(L'Ö'), UC(L'—'), KC_NO,
        KC_NO, UC(L'Ä'), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO
    ),
};

