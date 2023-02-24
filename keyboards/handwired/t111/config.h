/*
Copyright 2020 DmNosachev

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


#define MATRIX_ROW_PINS { A15, B6, B5, B4, B3, B9, B8, B7 }
/*                         0    1   2   3   4   5   6   7*/
#define MATRIX_COL_PINS { B15, B11, B10, B1, B0, A10, A9, A7, A6, A5, A4, A8, B13, B14 }
/*                         0    1    2    3   4   5    6   7   8   9   A   B   C    D*/


/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION ROW2COL

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
