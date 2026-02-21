/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

enum layers {
    _BASE,
    _RAISE,
    _LOWER
};

#define SFT_ESC  SFT_T(KC_ESC)
#define CTL_BSPC CTL_T(KC_BSPC)
#define ALT_SPC  ALT_T(KC_SPC)
#define SFT_ENT  SFT_T(KC_ENT)

#define KC_ML KC_MS_LEFT
#define KC_MR KC_MS_RIGHT
#define KC_MU KC_MS_UP
#define KC_MD KC_MS_DOWN
#define KC_MB1 KC_MS_BTN1
#define KC_MB2 KC_MS_BTN2

#define APP_X A(KC_F4)
#define DKMGR G(KC_TAB)
#define APP_P LSA(KC_TAB)
#define APP_N A(KC_TAB)

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    APP_X,         DKMGR,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    APP_P,         APP_N,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                            KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_QUOT,
                 KC_LBRC, KC_RBRC,                                                             KC_MINS, KC_EQL,
                                   SFT_ESC, CTL_BSPC, KC_HOME,      KC_END, ALT_SPC, SFT_ENT,
                                   KC_GRV,  RAISE,    KC_TAB,       KC_DEL, LOWER,   KC_LGUI
    ),

    [_RAISE] = LAYOUT(
        _______, _______, KC_MU,   _______, _______, _______,        _______, KC_VOLU, _______, KC_UP,   _______, KC_PGUP,
        _______, KC_ML,   KC_MD,   KC_MR,   _______, _______,        _______, KC_MUTE, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
        _______, _______, _______, _______, _______,                          KC_VOLD, KC_SLSH, KC_BSLS, KC_QUES, KC_PIPE,
                 _______, _______,                                                              KC_MB1,  KC_MB2,
                                   _______, _______, _______,        _______, _______, _______,
                                   _______, _______, _______,        _______, _______, _______
    ),

    [_LOWER] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,        _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,        _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
                 KC_F11,  KC_F12,                                                               _______, _______,
                                   _______, _______, _______,        _______, _______, _______,
                                   _______, _______, _______,        _______, _______, _______
    )
};
