/* Copyright (C) 2023 jonylee@hfd
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
// clang-format off
enum __layers {
    _Base,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_Base] = LAYOUT( /* Base */
		KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
		KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_RSFT,
		KC_LCTL, KC_LGUI, KC_LALT,     KC_SPC,               KC_SPC,          MO(_FN),KC_LEFT, KC_DOWN, KC_RGHT),

    [_FN] = LAYOUT( /* Fn */
		_______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
		_______, _______, _______, _______, _______, _______, KC_PGUP, KC_PGDN, KC_HOME, KC_END,  RM_TOGG, RM_NEXT,
		_______, _______, _______, KC_CALC, _______, AG_TOGG, _______, KC_MUTE, KC_VOLD, KC_VOLU, RM_VALU, _______,
		_______, GU_TOGG, _______,          _______,          _______,          _______, RM_SPDU, RM_VALD, RM_SATU)
};
