/* Copyright 2021
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
#define MATRIX_ROWS 1
#define MATRIX_COLS 12

/* key matrix pins 
 * Direct pins is not used because there is not a shared ground position
 * between all compatible microcontrollers.
*/ 
#define MATRIX_ROW_PINS { D7 }
#define MATRIX_COL_PINS { D1, D0, D4, C6, E6, B4, F4, F5, F6, F7, B3, B2 }
#define UNUSED_PINS

/* doesn't really matter lol */
#define DIODE_DIRECTION COL2ROW
