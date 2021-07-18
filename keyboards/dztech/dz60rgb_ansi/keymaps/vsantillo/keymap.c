/* Copyright 2021 Vincent Santillo (vincentsantillo@gmail.com)
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

#include "vs_dz60rgb_ansi.h"

// Set up keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Base Alphanumeric layer for MacOS
    [BASE] = LAYOUT_60_ansi(
        KC_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSPC, // 14
         KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,     KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC, KC_BSLS, // 14
        TD_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,     KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,           KC_ENT, // 13
          TD_LS,             KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,            TD_RS, // 12
        KC_LCTL, KC_LALT, KC_LCMD,                              L_SFN,                             KC_RCMD, KC_RALT,  L_FN1, KC_RCTL  // 8
    ),
    // Windows Layer - Toggle
    [WINDOWS] = LAYOUT_60_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, // 14
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, // 14
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, // 13
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, // 12
        _______, KC_LWIN, KC_LALT,                            _______,                            KC_RALT, KC_RWIN, _______, _______  // 8
    ),
    // SpaceFN Layer - Momentary
    [SPACEFN] = LAYOUT_60_ansi(
         KC_GRV, KC_MPRV, KC_MNXT, KC_MPLY, XXXXXXX,    KC_7,    KC_8,    KC_9, XXXXXXX, XXXXXXX, XXXXXXX,   TD_QM, KC_VOLU,  KC_DEL, // 14
        XXXXXXX, XXXXXXX,   KC_UP, XXXXXXX, KC_PGUP,    KC_4,    KC_5,    KC_6, XXXXXXX, KC_MS_U, XXXXXXX, KC_BRMD, KC_BRMU, RGB_TOG, // 14
        KC_ASTG, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,    KC_1,    KC_2,    KC_3, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX,          XXXXXXX, // 13
          TD_LS,          XXXXXXX, XXXXXXX, XXXXXXX,    KC_0,  KC_SPC,  KC_DOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            TD_RS, // 12
        _______, _______, _______,                            _______,                            _______, _______, _______, _______  // 8

    ),
    // FN1 Layer - Momentary
    [FN1] = LAYOUT_60_ansi(
        XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,   KC_F12,  KC_DEL, // 14
         L_WIND, XXXXXXX,   KC_UP, XXXXXXX, KC_PGUP, KC_BTN1, KC_MS_U, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_RMOD, RGB_TOG, // 14
         L_GAME, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX, RGB_SPI, RGB_SPD,           XXXXXXX, // 13
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, // 12
          RESET, _______, _______,                             KC_SPC,                            _______, _______,  _______, _______  // 8
    ),
    // Gaming Layer - Toggle
    [GAME] = LAYOUT_60_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, // 14
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, // 14
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, // 13
        KC_LSFT,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_RSFT, // 12
        _______, XXXXXXX, _______,                             KC_SPC,                            _______, XXXXXXX, _______, _______  // 8
    ),
    // Blank Layer - Unused
    [BLANK] = LAYOUT_60_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, // 14
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, // 14
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, // 13
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, // 12
        _______, _______, _______,                            _______,                            _______, _______, _______, _______  // 8
    ),
    // No-op Layer - Unused
    [NOOP] = LAYOUT_60_ansi(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, // 14
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, // 14
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, // 13
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, // 12
        XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  // 8
    )
};
