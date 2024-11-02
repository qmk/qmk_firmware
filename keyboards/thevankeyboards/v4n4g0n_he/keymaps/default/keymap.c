/*
Copyright 2020 <terry@terrymathews.net>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum layers {
    _LAYER0,
    _LAYER1,
    _LAYER2,
    _LAYER3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_LAYER0] = LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        LT(_LAYER1, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, LT(_LAYER1, KC_QUOT),
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, LT(_LAYER2, KC_ENT),
        KC_LCTL, MO(2), KC_LGUI, KC_SPC, KC_RSFT, KC_LALT, TG(_LAYER3)
    ),
    [_LAYER1] = LAYOUT(
        _______, _______, _______, _______, _______, _______,
        KC_GRV, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        _______, KC_BSLS, KC_QUOT, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_DOWN, KC_UP, KC_LEFT, KC_RIGHT, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_MSTP, KC_MPLY, KC_MPRV, KC_MNXT, _______,
        _______, _______, _______, _______, _______, _______, _______
    ),
    [_LAYER2] = LAYOUT(
        _______, _______, _______, _______, _______, _______,
        KC_TILD, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, _______,
        _______, KC_PIPE, KC_DQT, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_4, KC_5, KC_6, KC_VOLU, _______,
        _______, _______, _______, _______, _______, _______, KC_0, KC_1, KC_2, KC_3, KC_VOLD, _______,
        _______, _______, _______, _______, _______, _______, _______
    ),
    [_LAYER3] = LAYOUT(
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_F1, KC_F2, KC_F3, KC_F4, _______,
        KC_ESC, _______, _______, _______, _______, _______, _______, KC_F5, KC_F6, KC_F7, KC_F8, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_F9, KC_F10, KC_F11, KC_F12, _______,
        _______, KC_LALT, _______, _______, _______, _______, _______
    )
};
