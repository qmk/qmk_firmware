/* Copyright 2020 cmdremily
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

#define _BL 0

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BL] = LAYOUT(
    KC_F13,       KC_F14,       KC_F15,       KC_F16,       KC_F17,       KC_F18,       KC_F19,       KC_F20,
    KC_F21,       KC_F22,       KC_F23,       KC_F24,       LSFT(KC_F13), LSFT(KC_F14), LSFT(KC_F15), LSFT(KC_F16),
    LSFT(KC_F17), LSFT(KC_F18), LSFT(KC_F19), LSFT(KC_F20), LSFT(KC_F21), LSFT(KC_F22), LSFT(KC_F23), LSFT(KC_F24),
    LCTL(KC_F13), LCTL(KC_F14), LCTL(KC_F15), LCTL(KC_F16), LCTL(KC_F17), LCTL(KC_F18), LCTL(KC_F19), LCTL(KC_F20)
    )
};
// clang-format on
