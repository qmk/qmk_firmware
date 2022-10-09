/* Copyright 2021 SamuraiKek
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

#define EE_HANDS

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

/* define pins */
#define MATRIX_ROW_PINS { F6, F5, F4, B6, D3 }
#define MATRIX_COL_PINS { B5, B4, D7, D6, F0, F1, C6 }
#define MATRIX_ROW_PINS_RIGHT { D6, D7, B4, F7, E6 }
#define MATRIX_COL_PINS_RIGHT { B1, B2, B3, F1, F4, F5, F6 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 2

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D0
