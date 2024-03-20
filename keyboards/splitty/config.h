/*
Copyright 2018 Nicolas Schodet

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


/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS \
    { F0, F1, D4, D5, D6 }
#define MATRIX_COL_PINS \
    { B0, B1, B2, B3, B4, B5, B6 }
#define DIODE_DIRECTION COL2ROW

/* Split Keyboard specific options. */
#define USE_I2C
#define EE_HANDS
#define SPLIT_USB_DETECT

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
