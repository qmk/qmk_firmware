/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#ifndef SCULPTMOBILE_TEENSY2PP_H
#define SCULPTMOBILE_TEENSY2PP_H

#include "../config.h"


/* key matrix size */
#define MATRIX_ROWS 8 
#define MATRIX_COLS 18 

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
/* flipped layout. 
#define MATRIX_ROW_PINS { F7,F6,F5,F4,F3,F2,F1,F0}
#define MATRIX_ROW_PINS { F0,F1, F2, F3, F4, F5, F6, F7 }
			   0  1  2  3  4 5  6   7 */
#define MATRIX_ROW_PINS { F7,F6,F4,F5,F3,F2,F1,F0}

// Teensy++ layout. #define MATRIX_COL_PINS { B7, D0, D1, D2, D3, D4, D5, D6, D7, E0,E1,C1, C0, C3, C2, C5, C4,C6}

/*                        A   B   C   D   E   F   G   H   I   J  K  L   M   N   O   P   Q  R  */
#define MATRIX_COL_PINS { B7, D0, D1, D2, D3, D4, D5, D6, D7, E0,E1,C1, C0, C3, C2, C5, C4,C6}
#define UNUSED_PINS { B6,B5,B4,B3,B2,B1,B0 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL
 
#endif
