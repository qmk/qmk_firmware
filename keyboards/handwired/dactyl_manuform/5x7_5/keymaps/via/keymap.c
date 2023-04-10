/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

enum layers {
    _QWERTY,
    _FN,
    _NUMPAD,
    _BLANK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_5x7_5(
        KC_ESC,     KC_1,    KC_2    KC_3,   KC_4,    KC_5,    KC_6,                                KC_7,  KC_8,  KC_9,    KC_0, KC_MINS,  KC_EQL,  KC_GRV,
        KC_TAB,     KC_Q,    KC_W,   KC_E,   KC_R,    KC_T, KC_LBRC,                             KC_RBRC,  KC_Y,  KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
        KC_LCTL,    KC_A,    KC_S,   KC_D,   KC_F,    KC_G,   TG(3),                                TG(2), KC_H,  KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
        KC_LSFT,    KC_Z,    KC_X,   KC_C,   KC_V,    KC_B,                                                KC_N,  KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
        KC_CAPS, KC_LGUI,  KC_APP, KC_DEL,           TT(1),  KC_SPC,  KC_HOME,         KC_PGUP, KC_BSPC, KC_ENT,        KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT,
                                                            KC_LALT,   KC_END,         KC_PGDN, KC_RCTL
    ),
    [_FN] = LAYOUT_5x7_5(
        _______,   KC_F1,     KC_F2,      KC_F3,    KC_F4,     KC_F5,     KC_F6,                                  KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,
        _______,   _______,   _______,    KC_UP,    _______,   _______,   _______,                              _______, _______, _______, _______, _______, _______, _______,
        _______,   _______,   KC_LEFT,    KC_DOWN,  KC_RGHT,   _______,   QK_BOOT,                              _______, _______, _______, _______, _______, _______, _______,
        _______,   _______,   _______,   _______,   _______,   _______,                                                  _______, _______, _______, _______, _______, _______,
        KC_MSTP,   KC_MPLY,   KC_MPRV,   KC_MNXT,              _______,   _______,   _______,          _______, _______, _______,          _______, _______, _______, _______,
                                                                          _______,   _______,          _______, _______
    ),
    [_NUMPAD] = LAYOUT_5x7_5(
        _______,   _______,   _______,   _______,   _______,   _______,  _______,                               _______, _______,   KC_NUM,  _______,   KC_PMNS,   KC_PPLS,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,  _______,                               _______, _______,    KC_P7,    KC_P8,     KC_P9,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,  _______,                               _______, _______,    KC_P4,    KC_P5,     KC_P6,   KC_PAST,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,                                                  _______,    KC_P1,    KC_P2,     KC_P3,   KC_PSLS,   _______,
        _______,   _______,   _______,   _______,              _______, _______, _______,              _______, KC_PENT, _______,              KC_P0,   KC_PDOT,   _______,   _______,
                                                                        _______, _______,              _______, _______
    ),
    [_BLANK] = LAYOUT_5x7_5(
        _______,   _______,   _______,   _______,   _______,   _______,  _______,                           _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,  _______,                           _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,  _______,                           _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,                                                _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,              _______, _______, _______,          _______, _______,   _______,              _______,   _______,   _______,   _______,
                                                                        _______, _______,          _______, _______
    )
};
