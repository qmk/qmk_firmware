/* Copyright 2022 Steven Karrmann
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

enum layer_names {
    _BASE,
    _SYMBOL,
    _FUNCTION
};

#define MO_SYMB MO(_SYMBOL)
#define MO_FUNC MO(_FUNCTION)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_CAPS, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSLS,
        KC_GRV , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_MINS,
        KC_EQL , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_LBRC, KC_RBRC, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_ESC , KC_ENT , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI, KC_APP , KC_DEL , KC_TAB , MO_SYMB, MO_FUNC, KC_SPC , KC_BSPC, KC_APP , KC_RGUI, KC_RALT, KC_RCTL
    ),
    [_SYMBOL] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        KC_TILD, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_UNDS,
        KC_PLUS, KC_EXLM, KC_LPRN, KC_RPRN, KC_DLR , KC_AMPR, _______, _______, KC_PIPE, KC_HASH, KC_LCBR, KC_RCBR, KC_COLN, KC_DQUO,
        _______, KC_AT  , KC_LBRC, KC_RBRC, KC_BSLS, KC_PERC, _______, _______, KC_CIRC, KC_ASTR, KC_LABK, KC_RABK, KC_QUES, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_FUNCTION] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_PSCR,                   KC_SCRL, KC_HOME, KC_PGDN, KC_PGUP, KC_END , _______,
        _______, KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_INS , _______, _______, KC_CAPS, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______,
        _______, KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_PAUS, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};