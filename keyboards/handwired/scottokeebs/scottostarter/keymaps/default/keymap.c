/*
Copyright 2022 Joe Scotto

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_4x11_8( 
        KC_1,         KC_2,    KC_3,    KC_4,    KC_5,   KC_6,  KC_7,  KC_8,     KC_9,   KC_0,            KC_BSPC,
        KC_Q,         KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,  KC_U,  KC_I,     KC_O,   KC_P,            KC_TAB,
        KC_A,         KC_S,    KC_D,    KC_F,    KC_G,   KC_H,  KC_J,  KC_K,     KC_L,   KC_SCLN,         KC_QUOT,
        LSFT_T(KC_Z), KC_X,    KC_C,    KC_V,    KC_B,   KC_N,  KC_M,  KC_COMM, KC_DOT, RSFT_T(KC_SLSH), KC_ENT,
        KC_LCTL,      KC_LGUI, KC_LALT,          KC_SPC,               MO(1),    MO(2),  KC_ESC,         KC_CAPS
    ),
    [1] = LAYOUT_ortho_4x11_8(
        KC_NO,           KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,           KC_DEL,
        KC_UNDS,         KC_MINS, KC_PLUS, KC_EQL,  KC_COLN,  KC_GRV,   KC_MRWD, KC_MPLY, KC_MFFD, KC_NO,           KC_TAB,
        KC_LCBR,         KC_LPRN, KC_RPRN, KC_RCBR, KC_PIPE,  KC_ESC,   KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT,         KC_QUOT,
        LSFT_T(KC_LBRC), KC_QUOT, KC_DQUO, KC_RBRC, KC_SCLN,  KC_TILD, KC_VOLD, KC_MUTE, KC_VOLU, RSFT_T(KC_BSLS), KC_ENT,
        KC_LCTL,         KC_LGUI, KC_LALT,          KC_SPC,                      KC_TRNS, KC_TRNS, KC_ESC,          KC_CAPS
    ),
    [2] = LAYOUT_ortho_4x11_8(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,           KC_BSPC,
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_CAPS, KC_BSPC,         KC_TAB,
        KC_1,    KC_2,    KC_3,    KC_4,   KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,            KC_QUOT,
        KC_LSFT, KC_NO,   KC_NO,   KC_NO,  MO(3),   KC_NO,   KC_NO,   KC_COMM, KC_DOT,  RSFT_T(KC_SLSH), KC_ENT,
        KC_LCTL, KC_LGUI, KC_LALT,         KC_SPC,                    KC_TRNS, KC_TRNS, KC_ESC,          KC_CAPS
    ),
    [3] = LAYOUT_ortho_4x11_8(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,  KC_BSPC,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO,   KC_NO,   TO(4),  KC_TAB,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, KC_F7, KC_F8,   KC_F9,   KC_F10, KC_QUOT,
        KC_F11,  KC_NO,   KC_NO,   QK_BOOT, KC_TRNS, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_F12, KC_ENT,
        KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,                KC_TRNS, KC_TRNS, KC_ESC, KC_CAPS
    )
};



