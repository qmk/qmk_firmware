/* Copyright 2021 Work Louder
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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_MUTE, KC_MPLY, R_M_TOG, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,  MO(1)
    ),
    [1] = LAYOUT(
        QK_BOOT, _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD,  MO(2),  _______
    ),
    [2] = LAYOUT(
        QK_BOOT, _______, R_M_TOG, R_M_MOD, R_M_HUI, R_M_HUD, R_M_SAI, R_M_SAD, R_M_VAI, R_M_VAD, _______, _______
    )
};
// clang-format on

// bool encoder_update_user(uint8_t index, bool clockwise) {
//     if (index == 0) {
//         if (clockwise) {
//             tap_code(KC_VOLD);
//         } else {
//             tap_code(KC_VOLU);
//         }
//     } else if (index == 2) {
//         if (clockwise) {
//             tap_code(KC_MPRV);
//         } else {
//             tap_code(KC_MNXT);
//         }
//     } else {
//         if (clockwise) {
//             rgb_matrix_step_reverse();
//         } else {
//             rgb_matrix_step();
//         }
//     }
//     return false;
// }
