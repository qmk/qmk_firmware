/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

enum custom_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

#define SEMICLN LT(LOWER, KC_SCLN)
#define F_KEY LT(RAISE, KC_F)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_6x7_right(
        KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,                      KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______,
        _______, KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                      KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_LBRC, KC_RBRC,
        _______, KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                      KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_QUOT, KC_BACKSLASH,
        _______, KC_LSFT, KC_A   , KC_S   , KC_D   , F_KEY  , KC_G   ,                      KC_H   , KC_J   , KC_K   , KC_L   , SEMICLN, KC_RSFT, _______,
        _______, KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                      KC_N   , KC_M   , KC_COMM, KC_DOT ,KC_SLSH , KC_RCTL, _______,
                                   KC_LALT, KC_LGUI,                                                          KC_EQL , KC_MINS,
                                                     KC_SPC , KC_BTN1,                               KC_BSPC,
                                                     KC_ENT , KC_BTN2,                               KC_DEL ,
                                                     _______, KC_BTN3,                      KC_ESC , KC_LALT
    ),

    [_LOWER] = LAYOUT_6x7_right(
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      KC_HOME, KC_PGUP, KC_PGDN, KC_END , _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______,                                                          _______, _______,
                                                     _______, _______,                               _______,
                                                     _______, _______,                               _______,
                                                     _______, _______,                      _______, _______
    ),

    [_RAISE] = LAYOUT_6x7_right(
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______ , _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______,
                                   _______, _______,                                                          _______, _______,
                                                     _______, _______,                               _______,
                                                     _______, _______,                               _______,
                                                     _______, _______,                      _______, _______
    )
};
