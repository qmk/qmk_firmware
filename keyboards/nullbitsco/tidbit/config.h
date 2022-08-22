/* Copyright 2021 Jay Greco
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

/* Used to set slave for remote KB if VUSB detect doesn't work. */
// #define KEYBOARD_SLAVE

// Workaround for freezing after MacOS sleep
#define NO_USB_STARTUP_CHECK

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6E61
#define PRODUCT_ID      0x6061
#define DEVICE_VER      0x0001
#define MANUFACTURER    nullbits
#define PRODUCT         TIDBIT
#define DESCRIPTION     QMK keyboard firmware
/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

/* key matrix pins */
#define MATRIX_ROW_PINS { B1, E6, D7, C6, D4 }
#define MATRIX_COL_PINS { F4, F5, F6, F7 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Optional SMT LED pins */
#define RGB_DI_PIN B6
#define RGBLED_NUM 8
#define RGBLIGHT_ANIMATIONS

/* Additional optional encoder pins */

// You can mix/match pins within the ENCODERS_PAD_A and ENCODERS_PAD_B defines.

// Encoder 1 Pins:
 #define ENCODERS_PAD_A { B3 }
 #define ENCODERS_PAD_B { B2 }

// Encoder 2 Pins:
// #define ENCODERS_PAD_A { B4 }
// #define ENCODERS_PAD_B { B5 }

// Encoder 3 Pins: ⚠️ Compatibility note: encoder 3 shares the drive signals with the I2C bus. It can not be used at the same time as the OLED, alphanumeric display, or LED matrix options.
// #define ENCODERS_PAD_A { D0 }
// #define ENCODERS_PAD_B { D1 }

// Encoder 4 Pins: ⚠️ Compatibility note: encoder 4 shares the drive signals with the UART bus. It can not be used at the same time as the expansion port.
// #define ENCODERS_PAD_A { D2 }
// #define ENCODERS_PAD_B { D3 }
