/*
Copyright 2020 Matthew Tso (zoo)

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
#define VENDOR_ID    0x0200
#define PRODUCT_ID   0xE600
#define DEVICE_VER   0x0001
#define MANUFACTURER zoo.haus
#define PRODUCT      Wampus

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
#define MATRIX_ROW_PINS { C13, C14, A5, A4, A3 }
#define MATRIX_COL_PINS { A10, A9, A8, B12, A15, A13, A7, A2, A1, A0, F1, F0, B3, B4, B5 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define LED_NUM_LOCK_PIN B0
#define LED_CAPS_LOCK_PIN B8
#define LED_SCROLL_LOCK_PIN B9

// In-switch LED defines
#define BACKLIGHT_PIN           A6
#define BACKLIGHT_LEVELS 3
#define BACKLIGHT_BREATHING

#define BACKLIGHT_PWM_DRIVER    PWMD3
#define BACKLIGHT_PWM_CHANNEL 1
#define BACKLIGHT_PAL_MODE      1

// RGB Underglow WS2812 Matrix defines
#define RGBLIGHT_ANIMATIONS
#define RGB_DI_PIN B15
#define RGBLED_NUM 20
// SPI RGB Driver
#define WS2812_SPI SPID2
#define WS2812_SPI_MOSI_PAL_MODE 0

// OLED defines
#define OLED_TIMEOUT 60000
/* Both pins are in bank B */
#define I2C1_SCL 6 // B6
#define I2C1_SDA 7 // B7
#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PAL_MODE 1
/* This configures the I2C clock to 400khz assuming a 48Mhz clock */
#define I2C1_TIMINGR_PRESC 	0U
#define I2C1_TIMINGR_SCLDEL 3U
#define I2C1_TIMINGR_SDADEL 1U
#define I2C1_TIMINGR_SCLH 	3U
#define I2C1_TIMINGR_SCLL   9U

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
