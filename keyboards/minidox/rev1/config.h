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

#pragma once

#define DEVICE_VER      0x0001

// wiring of each half
#define MATRIX_ROW_PINS { B2, B6, B4, B5 }
#define MATRIX_COL_PINS { F4, D3, D2, D1, D4 }

#define SOFT_SERIAL_PIN D0

#define USE_SERIAL

//#define EE_HANDS
