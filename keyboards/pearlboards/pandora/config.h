/*
Copyright 2021 Koobaczech

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
#define VENDOR_ID 0x6963
#define PRODUCT_ID 0x6963
#define DEVICE_VER 0x0002
#define MANUFACTURER Koobaczech
#define PRODUCT Pandora

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

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
#define MATRIX_ROW_PINS { B4, D7, D6, B3, B0 }
#define MATRIX_COL_PINS { D2, D1, D0, D3, D5, B5, B6, B7, D4, C6, C7, F0, F1, F4, F7 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Encoder Function */
#define ENCODERS_PAD_A { F6 }
#define ENCODERS_PAD_B { F5 }
//#define ENCODER_DIRECTION_FLIP
#define ENCODER_RESOLUTION 1
#define DIP_SWITCH_PINS { B2, B5 }

/*== all animations enabled ==*/
/* If RGBLIGHT_SLEEP defined, the RGB lighting will be switched off when the host goes to sleep */
#define RGB_DI_PIN B1
#ifdef RGB_DI_PIN
#    define RGBLIGHT_ANIMATIONS
#    define RGBLED_NUM 12
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_SLEEP
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Indicator Led's*/
#define LED_CAPS_LOCK_PIN E6
#define LED_PIN_ON_STATE 0
/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
