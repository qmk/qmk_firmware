/* Copyright 2017 @TurboMech /u/TurboMech <discord> @A9entOran9e#6134
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0xCA75
#define DEVICE_VER      0x0001
#define MANUFACTURER    MECHKEYS
#define PRODUCT         ALU84

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

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
#define MATRIX_ROW_PINS { D0, D1, D2, D3, D5, B7 }
#define MATRIX_COL_PINS { F0, F1, E6, C7, C6, F5, D4, B1, B0, B5, B4, D7, D6, B3, F4, F6 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN B6
#define BACKLIGHT_LEVELS 3
#define BACKLIGHT_BREATHING

#define RGB_DI_PIN E2
#if defined(RGBLIGHT_ENABLE)
#    define RGBLED_NUM 16
#    define RGBLIGHT_HUE_STEP 10
#    define RGBLIGHT_SAT_STEP 10
#    define RGBLIGHT_VAL_STEP 10
#    define RGBLIGHT_ANIMATIONS
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
