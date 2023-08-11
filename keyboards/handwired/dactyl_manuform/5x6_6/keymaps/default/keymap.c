/*
Copyright 2022 fgoodwin <fgoodwin@north-tech.net>

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_split_5x6_6(
        KC_ESC,    KC_1,      KC_2,      KC_3,     KC_4,       KC_5,         KC_6,      KC_7,    KC_8,     KC_9,     KC_0,    KC_BSLS,
        KC_GRV,    KC_Q,      KC_W,      KC_E,     KC_R,       KC_T,         KC_Y,      KC_U,    KC_I,     KC_O,     KC_P,    KC_EQL,
        KC_TAB,    KC_A,      KC_S,      KC_D,     KC_F,       KC_G,         KC_H,      KC_J,    KC_K,     KC_L,     KC_SCLN, KC_QUOT,
        KC_LSFT,     KC_Z,      KC_X,      KC_C,     KC_V,       KC_B,         KC_N,      KC_M,    KC_COMM,  KC_DOT,   KC_SLSH, KC_MINS,
                              KC_NO,     KC_LGUI,  KC_LCTL,    KC_SPC,       KC_RSFT,   KC_ENT,  KC_LBRC,     KC_RBRC,
                                                   MO(1),      LCTL(KC_C),   KC_BSPC,   MO(1),
                                                   KC_LALT,    LCTL(KC_V),   KC_DEL,    KC_RSFT
    ),
    [1] = LAYOUT_split_5x6_6(
        KC_TRNS,   KC_F1,     KC_F2,     KC_F3,    KC_F4,         KC_F5,     KC_F6,       KC_F7,      KC_F8,       KC_F9,       KC_F10,     KC_F11,
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,       KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_F12,
        KC_TRNS,   KC_TRNS,   KC_PSCR,   KC_DOWN,  KC_UP,         KC_HOME,   KC_END,      KC_LEFT,    KC_RIGHT,    KC_TRNS,     KC_TRNS,    KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,       KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_BSLS,    KC_TRNS,
                   QK_BOOT,     KC_TRNS,   KC_TRNS,  KC_TRNS,       KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS,
                                         MO(1),    LCTL(KC_C),    KC_TRNS,   MO(1),
                                         KC_TRNS,  LCTL(KC_V),    KC_TRNS,   KC_TRNS
    )
};
