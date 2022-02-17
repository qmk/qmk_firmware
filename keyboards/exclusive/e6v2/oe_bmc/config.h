/*
Copyright 2019 MechMerlin

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4558
#define PRODUCT_ID      0xE62B
#define DEVICE_VER      0x0001
#define MANUFACTURER    Exclusive / E-Team
#define PRODUCT         E6-V2 OE BMC

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 11

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

//                        0   1   2   3   4   5   6   7   8   9   A
#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5, B6, B7 }
#define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, C2, C3, C4, C5, D7 }
#define DIODE_DIRECTION COL2ROW

#define LED_CAPS_LOCK_PIN D1

#define BACKLIGHT_PIN D4
#define BACKLIGHT_LEVELS 3

#define RGBLED_NUM 6
#define RGBLIGHT_ANIMATIONS
