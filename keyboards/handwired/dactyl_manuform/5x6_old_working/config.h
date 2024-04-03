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

// #define USE_SERIAL
#define USE_I2C

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

// Gray Keyboard
// wiring of left half
#define MATRIX_ROW_PINS \
    { D4, C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS \
    { B6, B2, B3, B1, F7, F6 }

// ms allowed for a tap-dance command

#ifdef JOYSTICK_ENABLE
  #define JOYSTICK_BUTTON_COUNT 0
  #define JOYSTICK_AXES_COUNT 2
  #define JOYSTICK_AXES_RESOLUTION 10
#endif
