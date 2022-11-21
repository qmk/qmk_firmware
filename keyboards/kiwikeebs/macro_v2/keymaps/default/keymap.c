/* Copyright 2020 KiwiKeebs
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
    _BASE,
    _FN1,
    _FN2,
    _FN3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_DEL,  KC_HOME, LT(_FN1,KC_END),
        KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE
    ),
    [_FN1] = LAYOUT(
        QK_BOOT,    KC_UP,   _______,
        KC_LEFT, KC_DOWN, KC_RGHT, MAGIC_TOGGLE_NKRO
    ),
    [_FN2] = LAYOUT(
        _______,    _______,   _______,
        _______, _______, _______, _______
    ),
    [_FN3] = LAYOUT(
        _______,    _______,   _______,
        _______, _______, _______, _______
    )
};