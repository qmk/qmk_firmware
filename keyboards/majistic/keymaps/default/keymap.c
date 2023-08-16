/* Copyright 2020 yossiyossy
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
    _LOWER,
};

enum custom_keycodes {
    L_SPC = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
                     JP_1,    JP_2,    JP_3,    JP_4,     JP_5,               JP_6,     JP_7,               JP_8,    JP_9,     JP_0,    JP_MINS, JP_CIRC, JP_YEN,  KC_BSPC,
                     KC_TAB,  KC_Q,    KC_W,    KC_E,     KC_R,               KC_T,     KC_Y,               KC_U,    KC_I,     KC_O,    KC_P,    JP_AT,   JP_LBRC,
                     KC_CAPS, KC_A,    KC_S,    KC_D,     KC_F,               KC_G,     KC_H,               KC_J,    KC_K,     KC_L,    JP_SCLN, JP_COLN, JP_RBRC, KC_ENT ,
                     KC_LSFT, KC_Z,    KC_X,    KC_C,     KC_V,               KC_B,     KC_N,               KC_M,    JP_COMM,  JP_DOT,  JP_SLSH, KC_UP,   KC_RSFT,
                     KC_LCTL, KC_LALT, KC_LGUI, KC_LNG2,  LT(_LOWER, KC_SPC),           LT(_LOWER, KC_SPC), KC_LNG1, KC_RGUI, KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    [_LOWER] = LAYOUT(
                     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
                     KC_ESC,  _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______, _______, _______,
                     _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______, JP_UNDS, _______, _______,
                     _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______, KC_BRMU, KC_VOLU, _______,
                     _______, _______, _______, _______, _______,                       _______,          _______, _______, KC_BRMD, KC_VOLD, _______
    ),
};
