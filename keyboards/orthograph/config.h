/*
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
#define VENDOR_ID       0x564B
#define PRODUCT_ID      0x0602
#define DEVICE_VER      0x0001
#define MANUFACTURER    vladkvit
#define PRODUCT         Orthograph
#define DESCRIPTION     An ortho split keyboard with 6 rows

/* key matrix size */
/* rows are doubled-up */
#define MATRIX_ROWS 12
#define MATRIX_COLS 8

/* wiring of each half */
#define MATRIX_ROW_PINS { F5, F6, F7, B1, B3, B2 }
#define MATRIX_COL_PINS { B5, B4, D7, C6, D4, D2, D3, F4 }
#define EE_HANDS // need to flash eeprom with eeprom-lefthand.eep for left, etc
#define SPLIT_USB_DETECT

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 3

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN E6
// #define USE_I2C

// disable backlight after timeout in minutes, 0 = no timeout
// #define RGB_BACKLIGHT_DISABLE_AFTER_TIMEOUT 0
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_ALL

#define DRIVER_ADDR_1 0b1010000
#define DRIVER_ADDR_2 0b1010000  // this is here for compliancy reasons.
#define DRIVER_COUNT 2

// 7 + 8 + 8 + 7 + 8 + 8 = 46
// 36 + 46 = 82

#define DRIVER_1_LED_TOTAL 82
// #define DRIVER_2_LED_TOTAL 48
// 36, 46


// #define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL
#define RGB_MATRIX_KEYPRESSES

#define RGB_MATRIX_SPLIT { 36,  46 }

#define DISABLE_RGB_MATRIX_BAND_SAT
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define DISABLE_RGB_MATRIX_DUAL_BEACON
#define DISABLE_RGB_MATRIX_RAINBOW_BEACON
#define DISABLE_RGB_MATRIX_RAINDROPS
#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define DISABLE_RGB_MATRIX_HUE_BREATHING
#define DISABLE_RGB_MATRIX_HUE_PENDULUM
#define DISABLE_RGB_MATRIX_HUE_WAVE

#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define DISABLE_RGB_MATRIX_SPLASHRGB_MATRIX_SOLID_SPLASH
#define DISABLE_RGB_MATRIX_SOLID_SPLASH
#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH


#define SPLIT_TRANSPORT_MIRROR