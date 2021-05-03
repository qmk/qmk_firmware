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
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
#define MATRIX_COL_PINS { F4,F4,F5,F5, F6,F6,F7,F7,  B6,B6,B2,B2, B3,B3,B1,B1 }

#define MATRIX_MUL_SEL  {  0, 1, 0, 1,  0, 1, 0, 1,   1, 0, 1, 0,  1, 0, 1, 0 }
/* use 74HC157: quadruple 2-line to 1-line data selectors / multiplexers */
#define MATRIX_MUL_SELECT  B5 /* 74HC157 pin1:~A/B */

#ifdef MATRIX_IO_DELAY_ADAPTIVE_FAST
#    define MATRIX_IO_DELAY_PORTS  B0, B0, F0, F0
#    define MATRIX_IO_DELAY_MULSEL  0,  1,  0,  1
//                                  76543210    76543210    76543210    76543210
#    define MATRIX_IO_DELAY_MASKS 0b01001110, 0b01001110, 0b11110000, 0b11110000
#endif
