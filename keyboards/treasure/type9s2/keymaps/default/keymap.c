/* Copyright 2021 Treasure
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
    [0] = LAYOUT_ortho_3x3(
        MO(1),   KC_MPLY, BL_STEP,
        KC_VOLD, KC_MUTE, KC_VOLU,
        KC_KP_1, KC_KP_2, KC_KP_3
    ),

    [1] = LAYOUT_ortho_3x3(
        _______, _______, MO(2),
        _______, _______, _______,
        _______, _______, _______
    ),

    [2] = LAYOUT_ortho_3x3(
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, MO(3)
    ),

    [3] = LAYOUT_ortho_3x3(
        _______, _______, _______,
        _______, _______, _______,
        QK_BOOT, _______, _______
    )
};
