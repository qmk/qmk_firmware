/*
Copyright 2021 marby3

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
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x0000
#define DEVICE_VER   0x0001
#define MANUFACTURER marby3
#define PRODUCT      formy46

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

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
#define MATRIX_ROW_PINS { B1, B3, B2, B6 }
#define MATRIX_COL_PINS { B5, B4, E6, D7, C6, D4}
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
#define SOFT_SERIAL_PIN D2

/* Split hand configration */
#define SPLIT_HAND_MATRIX_GRID B1, D4
#define SPLIT_HAND_MATRIX_GRID_LOW_IS_LEFT

#ifdef RGB_MATRIX_ENABLE
#    define RGBLED_NUM 46  // Number of LEDs
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120 // Sane brightness values so the board has enough power to operate
#    define RGBLED_SPLIT { 23, 23 } // broken leds :(
#    define RGB_MATRIX_SPLIT RGBLED_SPLIT
#endif

#define JOYSTICK_BUTTON_COUNT 0
#define JOYSTICK_AXES_COUNT 2
/* Rotary encoder define*/
//#define NUMBER_OF_ENCODERS 2
#define ENCODERS_PAD_A { F6 }
#define ENCODERS_PAD_B { F7 }
#define ENCODER_RESOLUTION 4  //Default Setting

#define COMBO_COUNT 12

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* Bootmagic Lite key configuration */
//#define BOOTMAGIC_LITE_ROW 0
//#define BOOTMAGIC_LITE_COLUMN 0

