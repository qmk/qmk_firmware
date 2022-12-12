/* Copyright 2022 Yiancar-Designs
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
[0] = LAYOUT( /* Base */
    KC_VOLU, KC_VOLD, KC_MPLY,
             MO(1)           ),

[1] = LAYOUT( /* FN */
    LCTL(KC_X), LCTL(KC_C), LCTL(KC_V),
                KC_TRNS               ),

[2] = LAYOUT( /* Empty for dynamic keymaps */
    KC_TRNS, KC_TRNS, KC_TRNS,
             KC_TRNS         ),

[3] = LAYOUT( /* Empty for dynamic keymaps */
    KC_TRNS, KC_TRNS, KC_TRNS,
             KC_TRNS         )
};
