/*
Copyright 2019 Basic I/O Instruments(Scott Wei) <scot.wei@gmail.com>

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

#define VENDOR_ID       0x8101  // 8101 = "BIOI"
#define PRODUCT_ID      0x6581
#define DEVICE_VER      0x0001
#define MANUFACTURER    Basic IO Instruments
#define PRODUCT         BIOI MORGAN65

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

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

#define MATRIX_ROW_PINS { E6, C6, F4, B2, D4 }
#define MATRIX_COL_PINS { F5, F6, F7, C7, B0, B7, B5, D5, B4, D7, D6, D1, D0, B3 }

//#define QMK_KEYS_PER_SCAN 4

/* Backlight Setup */
#define BACKLIGHT_PIN B6
#define BACKLIGHT_LEVELS 12

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* RGB Underglow */
#define RGB_DI_PIN B1
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 8  // Number of LEDs
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for magic key command */
#define KEYBOARD_LOCK_ENABLE
#define MAGIC_KEY_LOCK L

#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 1
