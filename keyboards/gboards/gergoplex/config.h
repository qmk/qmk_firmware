/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Copy and worked on with love from the EZ team

#pragma once
#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_ROWS_PER_SIDE (MATRIX_ROWS / 2)
#define MATRIX_COLS 4

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 */
#define MATRIX_ROW_PINS { F6, F5, F4, F1 }
#define MATRIX_COL_PINS { B1, B2, B3, D2, D3 }
#define IGNORE_MOD_TAP_INTERRUPT

#define IS_COMMAND() (get_mods() == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))

#define DEBOUNCE 5
