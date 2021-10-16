/* Copyright 2021 Matthias Liffers
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

enum layers { NORMAL_LAYER, SECOND_LAYER, THIRD_LAYER, FOURTH_LAYER };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[NORMAL_LAYER] = LAYOUT_ortho_2x4(KC_A, KC_A, KC_A, TO(3), KC_A, KC_A, KC_A, TO(1)), [SECOND_LAYER] = LAYOUT_ortho_2x4(KC_B, KC_B, KC_B, TO(0), KC_B, KC_B, KC_B, TO(2)), [THIRD_LAYER] = LAYOUT_ortho_2x4(KC_C, KC_C, KC_C, TO(1), KC_C, KC_C, KC_C, TO(3)), [FOURTH_LAYER] = LAYOUT_ortho_2x4(KC_D, KC_D, KC_D, TO(2), KC_D, KC_D, KC_D, TO(0))};
