/* Copyright 2020 Purdea Andrei
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
    _BASE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_all(
                                        S(KC_F1), S(KC_F2), S(KC_F3), S(KC_F4), S(KC_F5), S(KC_F6), S(KC_F7), S(KC_F8), S(KC_F9), S(KC_F10), S(KC_F11), S(KC_F12),
                                        KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12,
        KC_ESC,     KC_SCRL,    KC_GRV, KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,  KC_0,  KC_MINS, KC_EQL,        KC_BSPC,  S(KC_TAB),   KC_INS,  KC_PGUP,  KC_END,  KC_NUM,  KC_PSLS, KC_PAST,
        KC_PSCR,    KC_PAUS,    KC_TAB,    KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,  KC_LBRC, KC_RBRC,    KC_BSLS,  S(KC_RCTL),  KC_DEL,  KC_PGDN,  KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
        C(KC_PAUS), A(KC_F1),   KC_CAPS,      KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,  KC_SCLN, KC_QUOT,KC_NUHS, KC_ENT,               KC_UP,             KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        S(C(KC_4)), S(C(KC_3)), KC_LSFT,KC_NUBS, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT, KC_SLSH,           KC_RSFT,  KC_LEFT,     KC_HOME, KC_RGHT,  KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_LGUI,    KC_APP,     KC_LCTL,           KC_LALT,                         KC_SPC,                        KC_RALT,          KC_RCTL,               KC_DOWN,           KC_P0,            KC_PDOT
    )
};
