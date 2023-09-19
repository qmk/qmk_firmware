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
    _SYM,
    _NAV,
    _FUN,
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_Q,   KC_W,   KC_E,   KC_R,       KC_T,               KC_P,   KC_Y,   KC_U,   KC_I,   xxxxxxx,
        KC_A,   KC_S,   KC_D,   KC_F,       KC_G,               KC_O,   KC_H,   KC_J,   KC_K,   KC_L,
        KC_Z,   KC_X,   KC_C,   KC_V,       KC_TAB,             KC_ESC, KC_B,   KC_N,   KC_M,   KC_DEL,
                                KC_BSPC,    KC_SPC,             KC_ENT, XXXXXXX, // Replace NOOP with layer handling
    ),

    [_SYM] = LAYOUT(),

    [_NAV] = LAYOUT(
        KC_MS_BTN3,     KC_MS_BTN2,     KC_UP,      KC_MS_BTN1, XXXXXXX,            XXXXXXX,    KC_MS_BTN1, KC_MS_U,    KC_MS_BTN2, KC_MS_BTN3,
        XXXXXXX,        KC_LEFT,        KC_DOWN,    KC_RIGHT,   XXXXXXX,            XXXXXXX,    KC_MS_L,    KC_MS_D,    KC_MS_R,    XXXXXXX,
        KC_END,         KC_HOME,        KC_PGDN,    KC_PGUP,    KC_WFWD,            KC_WBAK,    KC_WH_U,    KC_WH_D,    KC_WH_L,    KC_WH_R,
                                                    KC_BSPC,    KC_SPC,             KC_ENT,     XXXXXXX
    ),

    [_FUN] = LAYOUT(
        XXXXXXX,    KC_CUT, KC_COPY,    KC_PASTE,   XXXXXXX,                XXXXXXX,    ,   , XXXXXXX, XXXXXXX,
        XXXXXXX,    KC_F1,  KC_F2,      KC_F3,      XXXXXXX,                XXXXXXX,    KC_F7,  KC_F8,  KC_F9,  XXXXXXX,
        XXXXXXX,    KC_F4,  KC_F5,      KC_F6,      XXXXXXX,                XXXXXXX,    KC_F10, KC_F11, KC_F12, XXXXXXX,
                                        KC_BSPC,    KC_SPC,                 KC_ENT,     XXXXXXX,
    ),
}
