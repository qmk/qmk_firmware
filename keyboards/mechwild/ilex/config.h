/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

/* USB Device descriptor parameter */#define VENDOR_ID       0x6D77 // mw = "MechWild"
#define PRODUCT_ID      0x1501
#define DEVICE_VER      0x0001
#define MANUFACTURER    MechWild
#define PRODUCT         Ilex

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

// wiring of each half
#define MATRIX_ROW_PINS { F6, F4, F5, F7 }
// wiring of each half
#define MATRIX_COL_PINS { D3, B1, B3, D7, E6, B2 }
// #define MATRIX_COL_PINS { B2, E6, D7, B3, B1, D3} 
#define UNUSED_PINS
//uncomment this line and comment line above if you need to reverse left-to-right key order
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D2

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#define RGB_DI_PIN B4
#define RGBLED_NUM 10
#define RGBLIGHT_ANIMATIONS
