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

#define PRODUCT Tractyl Manuform(6x7) Elite C

// wiring of each half
#define MATRIX_COL_PINS \
    { D4, C6, D7, E6, B4, B5, B7 }
#define MATRIX_ROW_PINS \
    { F5, F6, F7, F0, F1, C7, D5 }

#define DIODE_DIRECTION COL2ROW

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D0 // default
#define EE_HANDS

/* PMW3360 Settings */
#define PMW3360_CS_PIN B6
