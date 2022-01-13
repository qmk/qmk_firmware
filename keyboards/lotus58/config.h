/*
Copyright 2021 TweetyDaBird

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

// USB Device descriptor parameter
#define VENDOR_ID    0x0079
#define PRODUCT_ID   0x0058
#define DEVICE_VER   0x0001
#define MANUFACTURER TweetyDaBird
#define PRODUCT      Lotus58 Glow

// Keyboard Matrix (Rows are doubled)
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
#define MATRIX_COL_PINS { B1, B2, B3, B6, F7, F6 }
#define DIODE_DIRECTION COL2ROW

// Encoder support
#define ENCODERS_PAD_A { F5 }
#define ENCODERS_PAD_B { F4 }
#define ENCODERS_PAD_A_RIGHT { F4 }
#define ENCODERS_PAD_B_RIGHT { F5 }
#define ENCODER_RESOLUTION 1

// Define detection pin handedness
#define SPLIT_HAND_PIN B5

// Define Communication
#define USE_SERIAL
#define SOFT_SERIAL_PIN D2

// Define which side is the master (should be connected to USB)
//#define MASTER_RIGHT

// Allows dual displays to show modifiers etc
#define SERIAL_USE_MULTI_TRANSACTION
#define SPLIT_MODS_ENABLE
#define SPLIT_TRANSPORT_MIRROR

// Detects USB and assigns master (Not recommended on Elite C/Pro Micro mix)
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2000
#define SPLIT_USB_TIMEOUT_POLL 10

// Used for tapping in keymap
#define TAPPING_TERM 175
#define TAPPING_TOGGLE 2
#define TAP_CODE_DELAY 10

// Basic RGB configuration
#define RGB_DI_PIN D3
#define RGBLIGHT_SPLIT

// Underglow LEDs
#define RGBLED_SPLIT { 6, 6 }
#define RGBLED_NUM 12

// Full backlight + underglow
//#define RGBLED_SPLIT { 35, 35 }
//#define RGBLED_NUM 70

// Disable depreciated
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

//#define NO_AUTO_SHIFT_SPECIAL
//#define NO_AUTO_SHIFT_NUMERIC

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is useful for the Windows task manager shortcut (ctrl+shift+esc).
 */
//#define GRAVE_ESC_CTRL_OVERRIDE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
#define NO_DEBUG

/* disable print */
#define NO_PRINT

/* disable action features */
#define NO_ACTION_ONESHOT

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
