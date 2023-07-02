/* Copyright 2020 Austin "TuckTuckFloof" Ashmore
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
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _FN1,
    _FN2
};

// I put these combos in because they're easy to impliment and it gives you an idea of what you need to do
// Go nuts, have fun! It's why I build the board :)
enum WOMBO_COMBOS {
    VOLUME_UP = 0,
    VOLUME_DOWN
};

const uint16_t PROGMEM VOLUME_UP_COMBO[] = { KC_F1, KC_F2, COMBO_END };
const uint16_t PROGMEM VOLUME_DN_COMBO[] = { KC_F3, KC_F4, COMBO_END };

combo_t key_combos[] = {
    [VOLUME_UP] = COMBO(VOLUME_UP_COMBO, KC_VOLU),
    [VOLUME_DOWN] = COMBO(VOLUME_DN_COMBO, KC_VOLD)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_euiso_bigspace(
                        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_F1,  KC_F2,  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_F3,  KC_F4,  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
                        KC_LGUI, KC_LALT,                          KC_SPC,                                 MO(_FN2), MO(_FN1)
    ),

    [_FN1] = LAYOUT_euiso_bigspace(
                          KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,   KC_DEL,
        _______, _______, KC_ESC , KC_PIPE, KC_DQUO, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______, _______, _______, _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU,  _______,
                          _______, _______,                         _______,                                        KC_VOLD,  KC_MNXT
    ),

    [_FN2] = LAYOUT_euiso_bigspace(
                          KC_GRV ,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_DEL,
        _______, _______, KC_ESC , KC_BSLS, KC_QUOT, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC,    KC_4,    KC_5,    KC_6, _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______,    KC_1,    KC_2,    KC_3, KC_VOLU,  _______,
                          _______, _______,                         _______,                                        KC_VOLD,  KC_MNXT
    )
};
