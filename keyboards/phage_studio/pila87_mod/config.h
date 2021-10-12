/*
Copyright 2021 Phage Studio

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
#define VENDOR_ID       0x5048 //Phage Studio
#define PRODUCT_ID      0x5887
#define DEVICE_VER      0x0001
#define MANUFACTURER    Phage Studio
#define PRODUCT         Pila87 / XM87 Pro

/* Key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

/* Key matrix pin          0   1,   2,  3,  4,  5,  6,  7,  8,  9,  10,  11,  12,  13,  14,  15, 16 */
#define MATRIX_ROW_PINS { A1, A2, A10, A9, A8, C9 }
#define MATRIX_COL_PINS { B5, B4,  B6, C0, C1, C2, C3, B7, B3, D2, C12, C11, C10, A15, C15, C13, A3 }

/* Direction of diode (COL2ROW or ROW2COL) */
#define DIODE_DIRECTION COL2ROW

/* Forcing to use NKRO instead 6KRO */
#define FORCE_NKRO

/* Change USB Polling Rate to 1000hz and a larger keys per scan for elite gaming */
#define USB_POLLING_INTERVAL_MS 1
#define QMK_KEYS_PER_SCAN 12

/* LED Indicator */
#define LED_CAPS_LOCK_PIN C14
#define LED_SCROLL_LOCK_PIN A0

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* The pin connected to the data pin of the LEDs */
#define RGB_DI_PIN A4

/* The number of LEDs connected */
#define DRIVER_LED_TOTAL 91

/* RGB Matrix config */
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define DISABLE_RGB_MATRIX_BAND_SAT
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define DISABLE_RGB_MATRIX_SPLASH
#define DISABLE_RGB_MATRIX_SOLID_SPLASH
