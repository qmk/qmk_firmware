/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

// wiring of each half
// left
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }
#define MATRIX_ROW_PINS { F6, F7, B1, B3, B2, B6 }
// right
#define MATRIX_COL_PINS_RIGHT { D6, D7, B4, D3, C6, C7 }
#define MATRIX_ROW_PINS_RIGHT { D4, B7, F7, B6, B5, F6 }

#define DIODE_DIRECTION COL2ROW

/* serial.c configuration for split keyboard */
//#undef USE_I2C
#define SOFT_SERIAL_PIN D0
#define MASTER_RIGHT

/* PMW3360 Settings */
#define POINTING_DEVICE_CS_PIN B0
