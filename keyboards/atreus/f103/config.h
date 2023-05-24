/* Copyright 2022 DmNosachev
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

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/

/* key matrix pins */
#define MATRIX_COL_PINS { B10, B1, B0, A7, A6, B5, B4, B3, A15, A10, A9 }
#define MATRIX_ROW_PINS { A5, A4, A3, A2 }
#define UNUSED_PINS {B12, B13, B14, B15, A8, B6, B7, B8, B9, A1, A0, C15, C14, C13}

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW
