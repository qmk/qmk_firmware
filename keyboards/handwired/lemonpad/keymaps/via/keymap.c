/* Copyright 2022 dari-studios (@dari-studios)
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

/* Defines names for use in layer keycodes and the keymap */

enum layer_names {
        _BASE,
        _EMPTY1,
        _EMPTY2,
        _EMPTY3,
        _EMPTY4,
        _EMPTY5,
        _EMPTY6,
        _EMPTY7,
        _EMPTY8
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [_BASE] = LAYOUT(
                KC_A,    KC_B,    KC_C,
                KC_D,    KC_E,    KC_F 
        ),

        [_EMPTY1] = LAYOUT(
                KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS
        ),

        [_EMPTY2] = LAYOUT(
                KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS
        ),

        [_EMPTY3] = LAYOUT(
                KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS
        ),

        [_EMPTY4] = LAYOUT(
                KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS
        ),

        [_EMPTY5] = LAYOUT(
                KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS
        ),

        [_EMPTY6] = LAYOUT(
                KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS
        ),

        [_EMPTY7] = LAYOUT(
                KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS
        ),

        [_EMPTY8] = LAYOUT(
                KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS
        )
};
