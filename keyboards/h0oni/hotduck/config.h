/* Copyright 2021 Md Mashur Shalehin, aka h0oni <mashursakib1920@gmail.com>
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
#define VENDOR_ID       0x4D53 
#define PRODUCT_ID      0x6844 //hD
#define DEVICE_VER      0x0001
#define MANUFACTURER    h0oni
#define PRODUCT         hotDuck

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 10

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
#define MATRIX_ROW_PINS { B6, B2, B3, B1, F7, F6, F5 }
#define MATRIX_COL_PINS { B5, B4, E6, D7, C6, D4, D0, D1, D2, D3}
#define UNUSED_PINS

// #define LED_CAPS_LOCK_PIN B2
// #define LED_PIN_ON_STATE 0

// /* Backlight Setup */
// #define BACKLIGHT_PIN B5
// #define BACKLIGHT_LEVELS 6
// //#define BACKLIGHT_BREATHING

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* RGB Underglow
 * F4 PIN for pre-soldered WS2812 LEDs
 */
#define RGB_DI_PIN F4
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 20
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 15
#define RGBLIGHT_VAL_STEP 15

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

