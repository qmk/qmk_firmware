/*
Copyright 2019 Tom Short
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

enum layers{
    _QWERTY,
    _FN,
    _NUMPAD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_ESC,        KC_1,    KC_2,  KC_3,  KC_4,    KC_5, KC_6,         KC_7,        KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_GRV,
        KC_TAB,        KC_Q,    KC_W,  KC_E,  KC_R,    KC_T, KC_LBRC,      KC_RBRC,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_LCTL,       KC_A,    KC_S,  KC_D,  KC_F,    KC_G, A(KC_TAB),    TG(_NUMPAD), KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        OSM(MOD_LSFT), KC_Z,    KC_X,  KC_C,  KC_V,    KC_B,                            KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, OSM(MOD_RSFT),
                                KC_LEFT, KC_RGHT,                                                         KC_UP,   KC_DOWN, 
                                              TT(_FN), KC_SPC, KC_HOME,        KC_PGUP, KC_BSPC, KC_ENT,
                                              KC_LALT, KC_LGUI, KC_END,        KC_PGDN, KC_RCTL, KC_RALT
    ),

    [_FN] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        _______, _______, _______, KC_UP,   _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, QK_BOOT,      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
                          KC_MPRV, KC_MNXT,                                                            KC_MPLY, KC_MSTP,
                                            _______, _______, _______,      _______,  KC_DEL, _______,
                                            _______, _______, _______,      _______, KC_PSCR, KC_PAUS
    ),

    [_NUMPAD] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, KC_P7,   KC_P8,   KC_P9,   _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PAST, _______,
        _______, _______, _______, _______, _______, _______,                         _______, KC_P1,   KC_P2,   KC_P3,   KC_PSLS, _______,
                          _______, _______,                                                             KC_P0,   KC_PDOT,
                                            _______, _______, _______,       _______, _______, KC_PENT,
                                            _______, _______, _______,       _______, _______, _______
    )
};
