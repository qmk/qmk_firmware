/* Copyright 2019
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
#define MATRIX_ROW_PINS { F4, B2, B4, B5 }
#if defined(PCBDOWN)
  #define MATRIX_COL_PINS { D0, D4, C6, D7, E6, B6, B3, B1, F7, F6, F5 }
#else
  #define MATRIX_COL_PINS { F5, F6, F7, B1, B3, B6, E6, D7, C6, D4, D0 }
#endif

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW
