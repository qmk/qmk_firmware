/* Copyright 2020 Gondolindrim
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

#define RGBT RGB_MODE_RGBTEST

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT( /* Base */
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,            KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,    KC_P7,    KC_P8,   KC_P9, \
    KC_SLCK,  KC_A,    KC_S,    KC_D,    KC_F,            KC_G,    KC_H,    KC_J,    KC_K,    KC_L,             KC_ENTER,   KC_P4,    KC_P5,   KC_P6, \
    KC_LSHIFT,         KC_Z,    KC_X,    KC_C,            KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, MO(1)  , KC_UP,      KC_P1,    KC_P2,   KC_P3, \
    KC_LCTRL, KC_LWIN, KC_LALT,          LT(2, KC_SPACE),                   KC_SPC,           KC_RALT, KC_LEFT, KC_DOWN,    KC_RIGHT, KC_P0,   KC_DOT),
[1] = LAYOUT( /* Base */
    KC_F1,    KC_F2,   KC_F2,   KC_F4,   KC_F5,           KC_F6,   KC_F7,   KC_F8,   KC_LBRC, KC_RBRC, KC_MINS,  KC_EQL,    KC_NLCK, KC_SLCK, KC_CAPS, \
    KC_1,     KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,              KC_RSHIFT, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_SCLN, KC_QUOT, KC_SLSH, KC_TRNS,  KC_PGUP,   KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS,  KC_TRNS, KC_TRNS,          KC_TRNS,                           KC_SPC,           KC_TRNS, KC_HOME,  KC_PGDN,   KC_END , KC_TRNS, KC_TRNS),
[2] = LAYOUT( /* Base */                                    
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS ,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS ,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS,          RGB_TOG, RGB_MOD,  RGB_RMOD,        RGBT,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS ,                          KC_SPC,           KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS),
};
