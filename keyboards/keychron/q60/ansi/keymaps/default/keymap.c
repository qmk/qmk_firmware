/* Copyright 2022 @ Keychron (https://www.keychron.com)
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

// clang-format off

enum layers {
    MAC_BASE,
    WIN_BASE,
    FUNC,
    L3,
    L4,
    L5
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_60(
        KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,    KC_BSLS, KC_GRV,
        KC_TAB,  KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC,            KC_DEL,
        KC_LCTL, KC_A,     KC_S,     KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                      KC_ENT,
        KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,             KC_RSFT, MO(FUNC),
                           KC_LWIN,  KC_LALT,                            KC_SPC,                             KC_RALT,  KC_RWIN),

    [WIN_BASE] = LAYOUT_ansi_60(
        KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,    KC_BSLS, KC_GRV,
        KC_TAB,  KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC,            KC_DEL,
        KC_LCTL, KC_A,     KC_S,     KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                      KC_ENT,
        KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,             KC_RSFT, MO(FUNC),
                           KC_LALT,  KC_LWIN,                            KC_SPC,                             KC_RWIN,  KC_RALT),

    [FUNC] = LAYOUT_ansi_60(
        _______, KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,    _______, _______,
        RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______, _______,  _______,            _______,
        _______, RGB_RMOD, RGB_VAD,  RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, _______, _______, _______,                      _______,
        _______,           _______,  _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,             _______, _______,
                           _______,  _______,                            _______,                            _______,  _______),

    [L3] = LAYOUT_ansi_60(
        _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,   _______, _______,
        _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______,
        _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,                      _______,
        _______,           _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______, _______,
                           _______,  _______,                            _______,                            _______,  _______),

    [L4] = LAYOUT_ansi_60(
        _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,   _______, _______,
        _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______,
        _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,                      _______,
        _______,           _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______, _______,
                           _______,  _______,                            _______,                            _______,  _______),

    [L5] = LAYOUT_ansi_60(
        _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,   _______, _______,
        _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______,
        _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,                      _______,
        _______,           _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______, _______,
                           _______,  _______,                            _______,                            _______,  _______)
};
