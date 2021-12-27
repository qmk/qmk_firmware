/* Copyright 2021 omkbd
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

enum layer_number {
    _QWERTY = 0,
    _NAV,
    _SYMBOL,
    _MEDIA
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_QWERTY] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,  KC_4,  KC_5,          KC_6,   KC_7,  KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,  KC_T,          KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_ESC,  KC_A,    KC_S,    KC_D,  KC_F,  KC_G,          KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,  KC_V,  KC_B,          KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_DEL,
    KC_LCTL, KC_LALT, KC_LGUI, MO(2), MO(1), KC_SPC,        KC_SPC, MO(1), MO(2),   KC_RGUI, KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
),

[_NAV] = LAYOUT(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
    KC_TRNS, KC_NO,   KC_UP,   KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_NO,   KC_UP,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,         KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,   KC_TRNS, KC_TRNS,
    KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_PGUP, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, MO(3),   KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, MO(3),   KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END
),

[_SYMBOL] = LAYOUT(
    KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS, KC_BSPC,
    KC_TRNS, KC_NO,   KC_P7, KC_P8,   KC_P9,  KC_NO,            KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS, KC_NO,   KC_LCBR, KC_RCBR, KC_PIPE,
    KC_ESC,  KC_NO,   KC_P4, KC_P5,   KC_P6,  KC_NO,            KC_LCBR, KC_RCBR, KC_MINS, KC_EQL,  KC_COLN, KC_DQUO, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_NO,   KC_P1, KC_P2,   KC_P3,  KC_NO,            KC_LBRC, KC_RBRC, KC_LT,   KC_GT,   KC_QUES, KC_TRNS, KC_UP,   KC_TRNS,
    KC_TRNS, KC_TRNS, KC_P0, KC_TRNS, MO(3),  KC_TRNS,          KC_TRNS, MO(3),   KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT
),

[_MEDIA] = LAYOUT(
    KC_NO,   KC_SLCK,  KC_PAUS, KC_NO,    KC_NO,   RGB_VAD,         RGB_VAI, KC_MRWD, KC_MPLY, KC_MFFD, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO,
    RGB_TOG, RGB_MOD,  RGB_HUI, RGB_SAI,  RGB_VAI, RGB_SPI,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_MPLY, KC_NO,   KC_NO,   KC_NO,
    KC_NO,   RGB_RMOD, RGB_HUD, RGB_SAD,  RGB_VAD, RGB_SPD,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   RGB_M_P,  RGB_M_B, RGB_M_SW, RGB_M_G, KC_NO,           KC_NO,   KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_VOLU, KC_NO,
    KC_NO,   KC_NO,    KC_NO,   KC_TRNS,  KC_TRNS, KC_NO,           KC_NO,   KC_TRNS, KC_TRNS, KC_NO,   KC_NO,   KC_MRWD, KC_VOLD, KC_MFFD
)

};
