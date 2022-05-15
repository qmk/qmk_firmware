/* Copyright 2020 EMajesty
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_LGUI, KC_LALT, KC_SPC,  KC_DEL,  MO(1),        MO(2),   KC_ENT, KC_BSPC, KC_RALT, KC_RGUI),
    [1] = LAYOUT(
        KC_ESC,  _______, KC_UP,   _______, KC_HOME, KC_PGUP,                        _______, _______, _______, KC_LPRN, KC_RPRN, KC_GRV,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  KC_PGDN,                        _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______,
        _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,                        _______, _______, _______, KC_LCBR, KC_RCBR, _______,
                          _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______),
    [2] = LAYOUT(
        QK_BOOT,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                          KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
                          _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______)
};
