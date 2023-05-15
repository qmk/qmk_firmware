/*
Copyright 2019-2020 DMQ Design

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


//Matrix is 3x5 instead of 3x4, as the 3 encoders are wired into the matrix

#define MATRIX_ROW_PINS { F0, F1, F4 }
#define MATRIX_COL_PINS { F5, F6, F7, C7, C6 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

//Data pin for the 3 RGB LEDs
#define RGB_DI_PIN D3
//Number of RGB LEDs
#define RGBLED_NUM 3

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
