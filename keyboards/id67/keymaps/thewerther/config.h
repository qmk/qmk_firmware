/* Copyright 2021 thewerther
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
#define VENDOR_ID       0x6964 /* "id" */
#define PRODUCT_ID      0x0067
#define DEVICE_VER      0x0001
#define MANUFACTURER    IDOBAO
#define PRODUCT         ID67

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
#define MATRIX_ROW_PINS { B0, B1, B2, B3, F7 }
#define MATRIX_COL_PINS { C7, F6, F5, F4, F1, B7, D5, D1, D2, D3, D4, D0, D6, D7, B4 }

#define DIODE_DIRECTION COL2ROW
#define RGB_DI_PIN F0
#define DRIVER_LED_TOTAL 77
#define DRIVER_LED_UNDERGLOW 10

#if defined(RGB_DI_PIN)
    #define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255

    #define RGB_MATRIX_KEYPRESSES
    #define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
    #define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
    #define ENABLE_RGB_MATRIX_DUAL_BEACON
    #define ENABLE_RGB_MATRIX_RAINBOW_BEACON

#if defined(RGB_MATRIX_KEYPRESSES) || defined(RGB_MATRIX_KEYRELEASES)
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE// Pulses keys hit to hue & value then fades value out
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE       // Static single hue, pulses keys hit to shifted hue then fades to current hue
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE       // Hue & value pulse near a single key hit then fades value out
    #define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH    // Hue & value pulse away from multiple key hits then fades value out
#endif // #if defined(RGB_MATRIX_KEYPRESSES) || defined(RGB_MATRIX_KEYRELEASES)
#endif // #if defined(RGB_DI_PIN)
