/* Copyright 2021 Joshua Cheung and Nathan Nguyen

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

//Pins for boot magic lite
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 4
#define BOOTMAGIC_LITE_ROW_RIGHT 5
#define BOOTMAGIC_LITE_COLUMN_RIGHT 8

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 13


// Defines the diode direction, can be changed to ROW2COL if diodes are soldered backwards.
#define DIODE_DIRECTION COL2ROW

#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
// B7 and B5 are dummy pins to ensure both columns == 13
#define MATRIX_COL_PINS { D2, D3, B5, B6, F4, F5, F6, F7, B1, B3, B2, B7, D5 }
#define MATRIX_ROW_PINS_RIGHT { F0, F1, C7, D5, B7 }
#define MATRIX_COL_PINS_RIGHT { B6, B2, B3, B1, F7, F6, F5, F4, B0, B5, B4, E6, D7 }

// Set 0 if debouncing isn't needed
#define DEBOUNCE 5
#define USE_I2C

// sets the handness according to eeprom
#define EE_HANDS
