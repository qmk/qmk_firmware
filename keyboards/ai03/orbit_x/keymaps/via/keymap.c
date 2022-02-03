/* Copyright 2020 Ryota Goto
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _NUM,
    _NAV,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT, 
        MO(3),   KC_TAB,  KC_LGUI, KC_LALT, MO(2),   KC_SPC,  KC_SPC,  MO(1),   KC_TAB,  KC_DEL,  KC_PSCR, MO(3)
    ),
    [_NUM] = LAYOUT(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, 
        _______, KC_GRV,  KC_SLSH, KC_LBRC, KC_LPRN, KC_MINS, KC_EQL,  KC_RPRN, KC_RBRC, KC_BSLS, XXXXXXX, _______, 
        _______, KC_TILD, KC_QUES, KC_LCBR, XXXXXXX, KC_UNDS, KC_PLUS, XXXXXXX, KC_RCBR, KC_PIPE, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_NAV] = LAYOUT(
        _______, XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, _______,
        _______, XXXXXXX, KC_HOME, KC_PGDN, KC_END,  XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, _______,
        _______, XXXXXXX, C(G(KC_LEFT)), XXXXXXX, C(G(KC_RGHT)), XXXXXXX, XXXXXXX, C(S(KC_TAB)), XXXXXXX, C(KC_TAB), XXXXXXX, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_FN] = LAYOUT(
        RESET,   XXXXXXX, KC_F1,   KC_F2,   KC_F3,   XXXXXXX, XXXXXXX, KC_F7,   KC_F8,   KC_F9,   XXXXXXX, RESET,
        _______, XXXXXXX, KC_F4,   KC_F5,   KC_F6,   XXXXXXX, XXXXXXX, KC_F10,  KC_F11,  KC_F12,  XXXXXXX, _______,
        _______, XXXXXXX, KC_VOLD, XXXXXXX, KC_VOLU, XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};
