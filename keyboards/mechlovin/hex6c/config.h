/*
Copyright 2021 Mechlovin' Studio

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


/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { A10, B13, B12, B11, C14, C15 }
#define MATRIX_COL_PINS { A13, A14, A1, A0, C13, B9, B4, B7, B8, B5, B6, A9, A5, A6, A7, B1, B2, B10, B3, B14, B15 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PWM_DRIVER PWMD3
#define BACKLIGHT_PWM_CHANNEL 3

#define TAP_CODE_DELAY 10

#define WEAR_LEVELING_BACKING_SIZE 4096
#define WEAR_LEVELING_LOGICAL_SIZE 2048
