/* Copyright 2021 Swiftrax <swiftrax@gmail.com>
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

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

/* default pinout */
#define MATRIX_ROW_PINS { D5, D3, D2, D1, D0 }
#define MATRIX_COL_PINS { B4, B5, B6, C6, C7, F7, F6, F5, F4, F1, F0, E6, B0, B1, B2, B3 }

#define DIODE_DIRECTION COL2ROW
