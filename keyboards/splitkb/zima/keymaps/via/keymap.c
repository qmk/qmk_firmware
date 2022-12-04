/* Copyright 2019 Thomas Baart
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
    // clang-format off
    [0] = LAYOUT_ortho_4x3(/* Base */
        KC_MUTE, TG(1),   TG(2),
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,
        KC_P1,   KC_P2,   KC_P3
    ),
    [1] = LAYOUT_ortho_4x3(/* Layer 1 */
        QK_BOOT,   _______, XXXXXXX,
        AU_ON,   AU_OFF,  XXXXXXX,
        CK_TOGG, XXXXXXX, CK_UP,
        CK_RST,  XXXXXXX, CK_DOWN
    ),
    [2] = LAYOUT_ortho_4x3(/* Layer 2*/
        RGB_TOG, RGB_MOD, _______,
        RGB_HUI, RGB_SAI, RGB_VAI,
        RGB_HUD, RGB_SAD, RGB_VAD,
        HPT_TOG, HPT_FBK, HPT_CONT
    ),
    [3] = LAYOUT_ortho_4x3(
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______
    ),
    [4] = LAYOUT_ortho_4x3(
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______
    ),
    [5] = LAYOUT_ortho_4x3(
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______
    ),
    [6] = LAYOUT_ortho_4x3(
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______
    ),
    [7] = LAYOUT_ortho_4x3(
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______
    ),
};
