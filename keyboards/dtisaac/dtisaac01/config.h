/*
Copyright 2021 DTIsaac

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
#define MATRIX_ROWS 12
#define MATRIX_COLS 9

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
#define MATRIX_ROW_PINS { F7, F6, F5, F4, F1, B4, D2, B2, B1, B3, D4, D6 }
#define MATRIX_COL_PINS { C7, C6, D0, B5, F0, D7, B0, B7, D1 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION ROW2COL

#define LED_CAPS_LOCK_PIN D3
#define LED_SCROLL_LOCK_PIN D5
#define LED_PIN_ON_STATE 0


#define BACKLIGHT_PIN B6
#define BACKLIGHT_LEVELS 3
#define BACKLIGHT_BREATHING
