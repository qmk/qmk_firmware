/* Copyright 2020 Yoichiro Tanaka
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _NUMBERS,
    _CURSOR,
    _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_NUMBERS] = LAYOUT(
        KC_1,         KC_2,       KC_3,        KC_4,
        KC_5,         KC_6,       KC_7,        KC_8,
        KC_9,         KC_0,       DF(_CURSOR)
    ),
    [_CURSOR] = LAYOUT(
        KC_PGUP,      KC_HOME,    KC_UP,       KC_END,
        KC_PGDN,      KC_LEFT,    KC_DOWN,     KC_RGHT,
        KC_ENT,       KC_BSPC,    DF(_ADJUST)
    ),
    [_ADJUST] = LAYOUT(
        KC_NO,        KC_NO,      KC_NO,       KC_NO,
        KC_NO,        KC_NO,      KC_NO,       KC_NO,
        QK_BOOT,      KC_NO,      DF(_NUMBERS)
    )
};
