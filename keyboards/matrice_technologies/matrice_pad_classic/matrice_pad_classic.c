/* Copyright 2025 Matrice Technologies
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
 
#include "quantum.h"
#include QMK_KEYBOARD_H
#include "print.h"

void keyboard_pre_init_kb(void) {
	gpio_set_pin_input_high(F6);
    keyboard_pre_init_user();
}

bool shutdown_kb(bool jump_to_bootloader) {
    if (!shutdown_user(jump_to_bootloader)) {
        return false;
    }
    return true;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    return layer_state_set_user(state);
}

void matrix_init_kb(void) {
    matrix_init_user();
}