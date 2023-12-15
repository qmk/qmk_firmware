/* Copyright 2021 ai03
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
#include "keymap_japanese.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT( /* Base */
        KC_ESC,  JP_1,    JP_2,    JP_3,    JP_4,    JP_5,    JP_6,    JP_7,    JP_8,    JP_9,    JP_0,    JP_MINS, JP_CIRC, JP_YEN,  KC_DEL,
        KC_TAB,  JP_Q,    JP_W,    JP_E,    JP_R,    JP_T,    JP_Y,    JP_U,    JP_I,    JP_O,    JP_P,    JP_AT,   JP_LBRC,                  
        MO(1),   JP_A,    JP_S,    JP_D,    JP_F,    JP_G,    JP_H,    JP_J,    JP_K,    JP_L,    JP_SCLN, JP_COLN, JP_RBRC,          KC_ENT,
        KC_LSFT,          JP_Z,    JP_X,    JP_C,    JP_V,    JP_B,    JP_N,    JP_M,    JP_COMM, JP_DOT,  JP_SLSH, JP_BSLS,          KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, JP_MHEN,                            KC_SPC,                             JP_HENK, JP_KANA, JP_ZKHK, JP_EISU
    ),
    [_FN] = LAYOUT( /* FN */
        QK_BOOT,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
        _______, _______, KC_PGUP, _______, _______, _______, _______, _______, KC_UP,   _______, _______, _______, _______,          
        _______, KC_HOME, KC_PGDN, KC_END,  _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______,                            _______,                            _______, _______, _______, _______
    )
};
