/* Copyright 2023 TW59420 <https://github.com/TW59420>
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

    [0] = LAYOUT(LT(3, KC_LCTL), LT(1, KC_C), LT(2, KC_V)),

    [1] = LAYOUT(RGB_VAD, KC_TRNS, RGB_VAI),

    [2] = LAYOUT(RGB_SAD, RGB_SAI, KC_TRNS),

    [3] = LAYOUT(KC_TRNS, RGB_HUD, RGB_HUI)};
