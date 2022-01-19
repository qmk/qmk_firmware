/*
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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4342 // CB
#define PRODUCT_ID      0x1818
#define DEVICE_VER      0x0001
#define MANUFACTURER    CherryB.Studio
#define PRODUCT         CB1800

/* key matrix size */
#define MATRIX_ROWS 10
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
 *                        0   1   2   3   4   5   6   7   8   9
*/
#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5, B6, B7, C6, C7 }
#define MATRIX_COL_PINS { D0, D1, D2, D3, D4, D5, D6, D7, F0, F1, F4 }
//#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* LED Indicators */
#define LED_CAPS_LOCK_PIN F5
#define LED_NUM_LOCK_PIN F6
#define LED_SCROLL_LOCK_PIN F7
#define LED_PIN_ON_STATE 0

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define RGB_DI_PIN E6
#ifdef RGB_DI_PIN
#    define RGBLIGHT_ANIMATIONS
#    define RGBLED_NUM 20 
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#endif
