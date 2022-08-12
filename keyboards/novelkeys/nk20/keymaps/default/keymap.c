/* Copyright 2022 Yiancar
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
[0] = LAYOUT_all( /* Base */
    KC_VOLD, KC_VOLU, KC_MUTE,
    MO(1),   KC_PSLS, KC_PAST, KC_PMNS,
    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    KC_P4,   KC_P5,   KC_P6,
    KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    KC_P0,            KC_PDOT),

[1] = LAYOUT_all( /* FN */
    KC_NLCK, KC_TRNS, KC_TRNS,
    KC_TRNS, RGB_SPD, RGB_SPI, KC_TRNS,
    RGB_TOG, RGB_MOD, RGB_HUD, KC_TRNS,
    RGB_SAD, RGB_SAI, RGB_HUI,
    RGB_VAD, RGB_VAI, KC_TRNS, KC_TRNS,
    KC_TRNS,          KC_TRNS)
};
