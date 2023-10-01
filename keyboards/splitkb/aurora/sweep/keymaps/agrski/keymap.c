/* Copyright 2023 Alex Rakowski (@agrski)
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

enum layer_names {
    _BASE,
    _NUM,
    _SYM,
    _NAV,
    _FUN,
    _KITTY,
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_Q,       KC_W,   KC_F,           KC_P,       KC_G,               KC_J,       KC_L,       KC_U,   KC_Y,           KC_Z,
        KC_A,       KC_R,   LT(_NUM, KC_S), KC_T,       KC_D,               KC_H,       KC_N,       KC_E,   KLT(_SYM, C_I), KC_O,
        TG(_NAV),   KC_X,   KC_C,           KC_V,       KC_TAB,             KC_DEL,     KC_M,       KC_K,   KC_B,           TG(_FUN),
                                            G(KC_BSPC), S(KC_SPC),          C(KC_ENT),  A(KC_ESC),
    ),

    [_SYM] = LAYOUT(),

    [_NAV] = LAYOUT(
        KC_MS_BTN3,     KC_MS_BTN2,     KC_UP,      KC_MS_BTN1, xxxxxxx,            xxxxxxx,    KC_MS_BTN1, KC_MS_U,    KC_MS_BTN2, KC_MS_BTN3,
        KC_ESC,         KC_LEFT,        KC_DOWN,    KC_RIGHT,   KC_WBAK,            KC_WFWD,    KC_MS_L,    KC_MS_D,    KC_MS_R,    KC_ESC,
        _______,        KC_END,         KC_PGDN,    KC_PGUP,    KC_HOME,            KC_WH_L,    KC_WH_U,    KC_WH_D,    KC_WH_R,    _______,
                                                    _______,    _______,            _______,    _______,
    ),

    [_FUN] = LAYOUT(
        xxxxxxx,    KC_CUT, KC_COPY,    KC_PASTE,   xxxxxxx,                xxxxxxx,    BL_UP,  BL_TOGG,    BL_DOWN,    xxxxxxx,
        xxxxxxx,    KC_F1,  KC_F2,      KC_F3,      xxxxxxx,                xxxxxxx,    KC_F7,  KC_F8,      KC_F9,      xxxxxxx,
        _______,    KC_F4,  KC_F5,      KC_F6,      xxxxxxx,                xxxxxxx,    KC_F10, KC_F11,     KC_F12,     _______,
                                        _______,    _______,                _______,    _______,
    ),
}
