/* Copyright 2020 Worldspawn <mcmancuso@gmail.com>
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

enum alpha9_layers {
    _HOME,
    _FN,
    _FNCHAR,
    _FKEYS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_HOME] = LAYOUT(
        KC_P7,   KC_P8,   KC_P9,   KC_Q,         KC_W,         KC_E,          KC_R,    KC_T,     KC_Y, KC_U,     KC_I,         KC_O,         KC_P,
        KC_P4,   KC_P5,   KC_P6,   KC_A,         KC_S,         KC_D,          KC_F,    KC_G,     KC_H, KC_J,     KC_K,         KC_L,         KC_ENT,
        KC_P1,   KC_P2,   KC_P3,   LCTL_T(KC_Z), LALT_T(KC_X), LT(_FN, KC_C), LT(_FNCHAR, KC_V), LSFT_T(KC_SPC), RGUI_T(KC_B), RALT_T(KC_N), RCTL_T(KC_M)
    ),

    [_FN] = LAYOUT(
        KC_INS,  KC_HOME, KC_PGUP, KC_ESC,  KC_MUTE, KC_VOLD, KC_VOLU,    KC_MPLY,        KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_NO,
        KC_DEL,  KC_UP,   KC_PGDN, KC_TAB,  KC_NO,   KC_NO,   KC_NO,      KC_NO,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_BSPC,
        KC_LEFT, KC_DOWN, KC_RGHT, KC_LCTL, KC_LALT, KC_TRNS, MO(_FKEYS), LSFT_T(KC_SPC),          KC_RGUI,          KC_RALT, KC_RCTL
    ),

    [_FNCHAR] = LAYOUT(
        KC_NLCK, KC_NO,   KC_NO,   KC_1,    KC_2,    KC_3,       KC_4,   KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_NO,   KC_NO,   KC_NO,   KC_GRV,  KC_NO,   KC_MINS,    KC_EQL, KC_BSLS, KC_LBRC, KC_RBRC, KC_SCLN, KC_QUOT, KC_BSPC,
        KC_NO,   KC_NO,   KC_NO,   KC_LCTL, KC_LALT, MO(_FKEYS), KC_TRNS,         LSFT_T(KC_SPC),   KC_COMM, KC_DOT,  KC_SLSH
    ),

    [_FKEYS] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,    KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_NO,   KC_NO,   KC_NO,    KC_F11,   KC_F12,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_DEL,
        KC_NO,   KC_NO,   KC_NO,    KC_LCTL,  KC_LALT, KC_TRNS, KC_TRNS,          LSFT_T(KC_SPC),   KC_RGUI, KC_RALT, KC_RCTL
    ),
};
