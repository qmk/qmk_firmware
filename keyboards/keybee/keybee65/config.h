/*
Copyright 2020 <contact@vwolf.be>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0x6265 // KeyBee
#define PRODUCT_ID   0x0001 // Keybee65
#define DEVICE_VER   0x0001 // Version 1
#define MANUFACTURER    KeyBee
#define PRODUCT         KeyBee65

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *         ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/

// Checked with Eagle Schematic
#define MATRIX_ROW_PINS { D3, D2, D0, B0, F0  }
#define MATRIX_COL_PINS { E6, D1, D5, F1, F4, F5, F6, F7, C7, C6, B6, B5, B4, D7, D6, D4 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

// The pin connected to the data pin of the LEDs
#define RGB_DI_PIN B0
// The number of LEDs connected
#define DRIVER_LED_TOTAL 80
// Limit the Brithness of the LEDs
#define RGBLIGHT_LIMIT_VAL 96
#define RGB_VAL_STEP 12

#define RGB_MATRIX_KEYPRESSES
#define RGB_DISABLE_WHEN_USB_SUSPENDED
