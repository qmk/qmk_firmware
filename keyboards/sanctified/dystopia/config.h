/* Copyright 2021 Quentin Melis
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

#pragma once

#include "config_common.h"

/* Key Matrix Size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { B2, B3, E6, D5, D3 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, C7, C6, B6, B5, D4, D6, D7, B4 }

#define DIODE_DIRECTION COL2ROW

#define QMK_KEYS_PER_SCAN 12
