/* Copyright 2020 Jason Williams (Wilba)
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
#define VENDOR_ID       0x6582 // wilba.tech
#define PRODUCT_ID      0x001F // PCB #31
#define DEVICE_VER      0x0001
#define MANUFACTURER    wilba.tech
#define PRODUCT         wilba.tech WT70-JB

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 17

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
#define MATRIX_ROW_PINS { E6, F0, F4, F6, F7 }
#define MATRIX_COL_PINS { F5, D5, D3, D2, D1, D0, B7, C7, C6, B6, B5, B4, D7, D6, D4, B0, B3 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

// RGBLIGHT configuation
#define RGB_DI_PIN B2
#ifdef RGB_DI_PIN
   #define RGBLED_NUM 2
   #define RGBLIGHT_HUE_STEP 8
   #define RGBLIGHT_SAT_STEP 8
   #define RGBLIGHT_VAL_STEP 8
   #define RGBLIGHT_ANIMATIONS
#endif
