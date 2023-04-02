/* Copyright 2021 Christian Sandven
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

__attribute__ ((weak))
const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_ortho_2x2u(
    0,
    0, 0, 0, 0, 0, 0, 0,  0, 0,  0,  0,  0,  0,  0,
    0, 1, 3, 0, 6, 8, 10, 0, 13, 15, 0,  18, 20, 0,
    0, 0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19, 0,
       0, 0, 0, 0,    0,     0,  0,  0,  0,  0
);
