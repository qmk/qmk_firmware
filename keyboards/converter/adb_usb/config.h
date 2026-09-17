/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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

Ported to QMK by Peter Roe <pete@13bit.me>
*/

#pragma once

/* matrix size */
#define MATRIX_ROWS 16  // keycode bit: 3-0
#define MATRIX_COLS 8   // keycode bit: 6-4

/* ADB port setting */
#define ADB_PORT        PORTD
#define ADB_PIN         PIND
#define ADB_DDR         DDRD
#define ADB_DATA_BIT    0
//#define ADB_PSW_BIT     1       // optional
