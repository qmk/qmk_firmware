/*
Copyright 2020 dsanchezseco
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
  DVO, // dvorak
  QWE, // qwerty
  SYS, // system
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* dvorak */
    [DVO] = LAYOUT(
                                     KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______,  _______, KC_PSCR, KC_PAUS, MO(SYS),
                                     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,

    LCTL(KC_A), LCTL(KC_Z), KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, XXXXXXX, KC_BSPC,     KC_INS,  KC_HOME, KC_PGUP,     KC_BSPC, KC_PEQL, KC_PSLS, KC_PAST,
    LCTL(KC_B), LCTL(KC_X), KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,           XXXXXXX,     KC_DEL,  KC_END,  KC_PGDN,     KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
    LCTL(KC_D), LCTL(KC_C), KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,          KC_BSLS, KC_ENT,               KC_UP,                KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    LCTL(KC_F), LCTL(KC_V), KC_LSFT, KC_BSLS, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,             XXXXXXX, KC_RSFT,     KC_LEFT, KC_DOWN, KC_RGHT,     KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    LCTL(KC_G), LCTL(KC_W), KC_LCTL,          KC_LALT,                            KC_SPC,                                               KC_RALT,          KC_RCTL,              KC_LGUI,              XXXXXXX, KC_P0,   KC_PDOT, XXXXXXX
    ),
    /* qwerty */
    [QWE] = LAYOUT(
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

    _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,   XXXXXXX, _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,           XXXXXXX,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           _______, _______,              _______,              _______, _______, _______, _______,
    _______, _______,     _______, KC_GRV,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           XXXXXXX, _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______,          _______,                            _______,                                              _______,           _______,              _______,              XXXXXXX, _______, _______, XXXXXXX
    ),

    /* system */
    [SYS] = LAYOUT(
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,   _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

    _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, _______,     _______, _______, _______,     KC_NLCK, _______, _______, _______,
    _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          XXXXXXX,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______, _______, _______, _______, _______, _______, TO(DVO), _______, _______, _______, _______, _______,          _______, _______,              _______,              _______, _______, _______, _______,
    _______, _______,     _______, _______, _______, TO(QWE), _______, _______, _______, _______, _______, _______, _______, _______,          XXXXXXX, _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______,          _______,                            _______,                                              _______,          _______,              _______,              XXXXXXX, _______, _______, XXXXXXX
    ),
};
