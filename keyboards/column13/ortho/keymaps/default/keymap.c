/* Copyright 2021 ABplus Inc. kazhida
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
    _LOWER,
    _RAISE,
    _FUNCS
};

#define KL_EISU LT(_LOWER, KC_LANG2)
#define KS_KANA LSFT_T(KC_LANG1)
#define KL_TAB  LT(_FUNCS, KC_TAB)
#define KL_SPC  LT(_RAISE, KC_SPC)
#define KA_SPC  LALT_T(KC_SPC)
#define cmd(KC) LGUI(KC)
#define sft(KC) RSFT(KC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, KC_BSPC,
        KL_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,    KC_J,    KC_K,    KC_L,    KC_LBRC, KC_RBRC, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_RSFT,
        KC_LCTL, KC_LGUI, KC_DEL,  KA_SPC,  KL_EISU, KC_SPC, KS_KANA, KL_SPC,  KC_BSLS, KC_LEFT, KC_DOWN, KC_RGHT,
        KC_LALT, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,  KC_F12,
        KC_LSFT, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0
),
[_LOWER] = LAYOUT(
        KC_GRV,  cmd(KC_Q), cmd(KC_W), cmd(KC_E), cmd(KC_R), cmd(KC_T), cmd(KC_Y), cmd(KC_U), cmd(KC_I), cmd(KC_O), cmd(KC_P),  KC_EQL, _______,
        _______, cmd(KC_A), cmd(KC_S), cmd(KC_D), cmd(KC_F), cmd(KC_G), cmd(KC_H), cmd(KC_J), cmd(KC_K), cmd(KC_L), KC_SCLN,    KC_COLN,_______,
        _______, cmd(KC_Z), cmd(KC_X), cmd(KC_C), cmd(KC_V), cmd(KC_B), cmd(KC_N), cmd(KC_M), _______,   _______,   KC_BSLS,    KC_PGUP,_______,
        _______, _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_HOME,    KC_PGDN,KC_END,

        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
),
[_RAISE] = LAYOUT(
        _______,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_EQL, _______,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_SCLN,KC_COLN,_______,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_BSLS,KC_PGUP,_______,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,KC_HOME,KC_PGDN,KC_END,

        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
),
[_FUNCS] =  LAYOUT(
        _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,
        _______,RESET,  _______,_______,_______,_______,_______,_______,_______,_______,_______,RGB_MOD,RGB_TOG,
        _______,_______,_______,_______,_______,_______,_______,_______,RGB_VAI,RGB_VAD,_______,RGB_SAI,_______,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,RGB_HUI,RGB_SAD,RGB_HUD,

        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
)
};

