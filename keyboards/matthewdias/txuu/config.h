/*
Copyright 2021 Matthew Dias <matthewdias@me.com>

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


/* m3n3van PCB default pin-out */
#define MATRIX_ROW_PINS { B1, B0, F7, F4, F1 }
#define MATRIX_COL_PINS { F0, F5, F6, D0, D1, D2, D3, D5, D4, D6, D7, B4, B5, B6, C6, C7 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

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
