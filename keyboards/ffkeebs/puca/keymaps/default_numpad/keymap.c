/* Copyright 2021 Sleepdealer, James Young for QMK (@noroadsleft)
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_numpad(
        KC_MUTE,          KC_PGUP, KC_PGDN,
        TG(1),   KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,
        KC_P0,            KC_PDOT, KC_ENTER
    ),

    [1] = LAYOUT_numpad(
        _______,          UG_HUEU, UG_VALU,
        TG(1),   UG_TOGG, UG_HUED, UG_VALD,
        KC_PGUP, KC_UP,   KC_PGDN,
        KC_LEFT, KC_DOWN, KC_RGHT, UG_NEXT,
        KC_INS,  KC_HOME, KC_END,
        KC_ESC,           KC_DEL,  UG_PREV
    ),

};
