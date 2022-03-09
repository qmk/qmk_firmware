/*
Copyright 2021 mtei

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
#define MATRIX_ROW_PINS { A4, A5, A6, A7, A8 }
#define MATRIX_COL_PINS { A2, A1, A0, B8,  B13, B14, B15, B9,  B0, B1, B2, B3,  B4, B5, B6, B7 }

#ifdef MATRIX_IO_DELAY_ADAPTIVE_FAST
#    define MATRIX_IO_DELAY_PORTS A0, B0
//                                  fedcba9876543210    fedcba9876543210
#    define MATRIX_IO_DELAY_MASKS 0b0000000000000111, 0b1110001111111111
#endif
