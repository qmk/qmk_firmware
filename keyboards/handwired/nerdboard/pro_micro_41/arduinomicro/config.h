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

#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }
#define MATRIX_ROW_PINS { F4, F5, F6, F7 }

#define DIODE_DIRECTION COL2ROW
#define SOFT_SERIAL_PIN D3

#undef USE_I2C

#define MASTER_RIGHT
#define PMW3360_LIFTOFF_DISTANCE 0x40

/* PMW3360 Settings */
#define POINTING_DEVICE_CS_PIN B6

