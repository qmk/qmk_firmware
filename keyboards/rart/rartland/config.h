/*Copyright 2021 Alabahuy

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

#define VENDOR_ID       0x414C
#define PRODUCT_ID      0x6065
#define DEVICE_VER      0x0001
#define MANUFACTURER    Alabahuy
#define PRODUCT         RARTLAND

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
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
/*                        0    1    2    3    4    5    6    7    8    9   10  11  12  13  14*/
#define MATRIX_ROW_PINS { B4, A7, A5, A6, C3 }
#define MATRIX_COL_PINS { B0, A1, B1, A2, B2, A3, B3, A4, C7, C6, D0, C5, D1, C4 }
#define UNUSED_PINS

#define LED_CAPS_LOCK_PIN A0
#define LED_PIN_ON_STATE 0

#define ENCODERS_PAD_B { D5 }
#define ENCODERS_PAD_A { C2 }
#define ENCODER_RESOLUTION 2 //default/suggested

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define OLED_TIMEOUT 10000

/* #define RGB_DI_PIN D7 */
/* #ifdef RGB_DI_PIN */
/* #define RGBLIGHT_ANIMATIONS */
/* #define RGBLED_NUM 11 */
/* #define RGBLIGHT_HUE_STEP 8 */
/* #define RGBLIGHT_SAT_STEP 8 */
/* #define RGBLIGHT_VAL_STEP 8 */
/* #define RGBLIGHT_LIMIT_VAL 240 */
/* #define RGBLIGHT_SLEEP */
/* #endif */

