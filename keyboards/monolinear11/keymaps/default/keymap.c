/*
Copyright 2022 Jacob Terry

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
    [0] = LAYOUT(
        KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  TG(1),
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT, KC_UP,   KC_DEL,
        KC_LCTL, KC_LGUI, KC_LALT,                                 KC_SPC,                       KC_LALT, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT(
        _______, _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_TRANSPARENT,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, _______,
        DB_TOGG, _______, _______, _______, _______, RGB_VAD, RGB_RMOD, RGB_VAI
    )
};

led_config_t g_led_config  = {
    {
        // Key Matrix to LED Index
        { 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, },
        { 49, 48, NO_LED, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36,  },
        { 35, NO_LED, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24,  23, 22,  },
        { 21, 20, NO_LED, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8,  },
        { 7, NO_LED, 6, 5, NO_LED, NO_LED, NO_LED, 4, NO_LED, NO_LED, NO_LED, 3, 2, 1, 0,}
    }, {
        // LED Index to Physical Position
        { 224, 64 }, { 208, 64 }, { 192, 64 }, { 174, 64 }, { 107, 64 }, { 39, 64 }, {  23, 64 }, { 3, 64 },
        { 223, 47 }, { 208, 47 }, { 188, 47 }, { 167, 47 }, { 151, 47 }, { 135, 47 }, { 119, 47  }, {  103, 47 }, { 87, 47 }, { 71, 47 }, { 55, 47 }, { 39, 47 }, { 23, 47 }, { 3, 47 },
        { 223, 32 }, { 203, 32 }, { 183, 32 }, { 166, 32 }, { 151, 32 }, { 135, 32 }, { 119, 32 }, { 103, 32 }, { 87, 32 }, { 71, 32 }, { 55, 32 }, { 39, 32 }, { 23, 32 }, { 3, 32 }, 
        { 219, 15 }, { 199, 15 }, { 183, 15 }, { 167, 15 }, { 151, 15 }, { 135, 15 }, { 119, 15 }, { 103, 15 }, { 87, 15 }, { 71, 15}, { 55, 15 },{ 39, 15 }, { 23, 15 }, { 3, 15 },
        { 223, 0 }, { 207, 0 }, {  191, 0 }, { 175, 0 }, { 159, 0 }, { 143, 0 }, { 127, 0 }, { 111, 0 }, { 95, 0 }, { 79, 0 }, { 63, 0 }, {  47, 0 }, { 31, 0 }, { 15, 0 }, {  0, 0 }
    }, {
        // LED Index to Flag
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4
    }
};
