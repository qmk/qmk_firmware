/* Copyright 2021 Chonkerkeys
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
#include "virtser.h"
#include "../protocol.c"
#include "config.c"

const uint8_t key_strand[MATRIX_ROWS][MATRIX_COLS] = {
    { 3,  2,  1,  0},
    { 7,  6,  5,  4},
    {11, 10,  9,  8}
};

#include "../core.c"
