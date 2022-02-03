/*
Copyright 2020 Team Mechlovin'

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

#define PRODUCT_ID    0x6509
#define DEVICE_VER    0x0002
#define PRODUCT       Mechlovin9 Rev2

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
#define MATRIX_ROW_PINS { A0, A1, A2, A3, A4 }
#define MATRIX_COL_PINS { B2, B1, B0, B3, B4, B5, D0, D1, D5, D6, D7, C0, C3, C2, C1 }

#define LED_CAPS_LOCK_PIN A7

#define BACKLIGHT_PIN D4
#define BACKLIGHT_BREATHING

/* Bootmagic Lite key configuration */
 #define BOOTMAGIC_LITE_ROW 0
 #define BOOTMAGIC_LITE_COLUMN 13
