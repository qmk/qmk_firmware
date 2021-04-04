/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6324
#define DEVICE_VER      0x0001
#define MANUFACTURER ZHUWENQ THE BEST
#define PRODUCT ANTON

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

#define MATRIX_COL_PINS { A6, B1, B9, B10, B11, B13, B14, B15, A8, A15, B3, B4, B5, B6, B7, B8 }
#define MATRIX_ROW_PINS { C13, C14, C15, A1, A4, A5 }
#define DIODE_DIRECTION ROW2COL

#define DISABLE_RGB_MATRIX_RAINBOW_BEACON
#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
//#defin// The pin connected to the data pin of the LEDs
#define RGB_DI_PIN B12
// The number of LEDs connected
#define DRIVER_LED_TOTAL 84

// limit the brightness of rgb
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 170
// ENCODERS_PAD_A { A12 }
//#define ENCODERS_PAD_B { A11 }


/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

//USART2
#define SERIAL_DRIVER   SD2
#define SD2_TX_PIN      A2
#define SD2_TX_PAL_MODE 7
#define SD2_RX_PIN      A3
#define SD2_RX_PAL_MODE 7
