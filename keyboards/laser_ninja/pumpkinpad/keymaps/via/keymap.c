 /* Copyright 2022 Joah Nelson (Jels)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation,   either version 2 of the License, or
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

[0] = LAYOUT(
    KC_F1, KC_F2, KC_F3,
    KC_F4, KC_F5, KC_F6, KC_F7,
    KC_F8, MO(1), KC_F10
),
[1] = LAYOUT(
    RGB_TOG, RGB_MOD, RGB_RMOD,
    RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,
    RGB_VAI, RGB_VAD, _______
),
[2] = LAYOUT(
    _______, _______, _______,
    _______, _______, _______, _______,
    _______, _______, _______
),
[3] = LAYOUT(
    _______, _______, _______,
    _______, _______, _______, _______,
    _______, _______, _______
)
};
