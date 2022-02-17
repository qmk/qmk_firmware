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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xCEEB
#define PRODUCT_ID      0x0007
#define DEVICE_VER      0x0001
#define MANUFACTURER    leafcutterlabs
#define PRODUCT         bigKNOB

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 5

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *                  NO_DIODE = switches are directly connected to AVR pins
 *
*/

// Srating with closest to USB port 
#define DIRECT_PINS {   \
    { B7, D4, D6, F6, F7} \
}
#define UNUSED_PINS

/* rotary encoder 1,2,3 closest to usb port is 0*/
#define ENCODERS_PAD_A { D0}
#define ENCODERS_PAD_B { D2}
#define ENCODER_RESOLUTION 4 //default/suggested

/* ws2812 RGB LED */
#define RGB_DI_PIN C7 //D3 - underglow C7 - backlight
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 5    // Number of LEDs