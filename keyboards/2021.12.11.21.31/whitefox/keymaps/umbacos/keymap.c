/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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
#include "keymap_italian.h"

enum layers {
    _MAIN,
    _SHIFT,
    _ACCENT,
    _SERVICE
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     [_MAIN] = LAYOUT_truefox( \
         KC_ESC,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   IT_MINS,IT_EQL,    /* IT_LESS */ KC_BSPC ,KC_DEL, KC_HOME, \
         KC_TAB,    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   IT_LBRC,IT_RBRC,    IT_LESS,         KC_END, \
         KC_CAPS,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   IT_SCLN,IT_APOS,            KC_ENT,          KC_PGUP, \
         LT(_SHIFT, KC_DEL),KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   IT_COMM,IT_DOT, IT_SLSH,MO(_SHIFT),         KC_UP,           KC_PGDN, \
         KC_LCTL,   KC_LALT, KC_LGUI,         LT(_ACCENT, KC_SPC),   KC_RALT,MO(_SERVICE),                             KC_LEFT, KC_DOWN, KC_RGHT \
     ),
     [_SHIFT] = LAYOUT_truefox( \
         S(KC_ESC), IT_EXLM, IT_AT,   IT_SHRP, IT_DLR,  IT_PERC, IT_CRC,  IT_AMPR, IT_ASTR, IT_LPRN, IT_RPRN, IT_UNDS, IT_PLUS, IT_MORE,    IT_PIPE,   S(KC_HOME), \
         S(KC_TAB), S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T), S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), S(IT_LBRC), S(IT_RBRC),   S(IT_LESS),S(KC_END), \
         S(KC_CAPS),S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G), S(KC_H), S(KC_J), S(KC_K), S(KC_L), IT_COLN, IT_DQOT,   S(KC_ENT), S(KC_PGUP), \
         IT_EACC,  S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N), S(KC_M), IT_BKSL, IT_PIPE, IT_QST,  S(IT_EACC),S(KC_UP),  S(KC_PGDN), \
         S(KC_LCTL), S(KC_LALT), S(KC_LGUI),             S(KC_SPC),                          KC_RALT, MO(_SERVICE), S(KC_LEFT), S(KC_DOWN), S(KC_RGHT)  \
     ),
     [_ACCENT] = LAYOUT_truefox( \
         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, IT_LESS, _______, _______,   \
         _______, IT_EURO, _______, IT_EACC, _______, _______, _______, IT_UACC, IT_IACC, IT_OACC, _______, _______, _______, _______, _______,            \
         _______, IT_AACC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                     \
         KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RSFT, _______, _______,                     \
         _______, _______, _______, _______, _______, _______, _______, _______, _______  \
     ),
    [_SERVICE] = LAYOUT_truefox( \
        RESET,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_MUTE,\
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______, _______, _______, \
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_VOLU, \
        KC_LSFT, _______, _______, _______, _______, RESET,   _______, _______, _______, _______, KC_RSFT, KC_HOME,  _______,          KC_VOLD,\
        _______,_______,_______,               _______,          _______,_______,                  KC_HOME,KC_END,KC_END  \
    ),
};
