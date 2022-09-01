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
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x0058
#define DEVICE_VER   0x0001
#define MANUFACTURER TweetyDaBird
#define PRODUCT      Lotus 58 Glow

// Keyboard Matrix (Rows are doubled)
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
#define MATRIX_COL_PINS { B1, B2, B3, B6, F7, F6 }
#define DIODE_DIRECTION COL2ROW

#define SPLIT_HAND_PIN B5

// Encoder support
#define ENCODERS_PAD_A { F5 }
#define ENCODERS_PAD_B { F4 }
#define ENCODERS_PAD_A_RIGHT { F4 }
#define ENCODERS_PAD_B_RIGHT { F5 }
#define ENCODER_RESOLUTION 1

// Define Communication
#define SOFT_SERIAL_PIN D2
#define USE_SERIAL
#define SERIAL_USE_MULTI_TRANSACTION
//#define SPLIT_MODS_ENABLE
//#define SPLIT_TRANSPORT_MIRROR

// Basic RGB configuration
#define RGB_DI_PIN D3

// Underglow LEDs
//#define RGBLED_SPLIT { 6, 6 }
//#define RGBLED_NUM 12

// Full backlight
//#define RGBLED_SPLIT { 29, 29 }
//#define RGBLED_NUM 58

// Full backlight + underglow
#define RGBLED_SPLIT { 35, 35 }
#define RGBLED_NUM 70
#define RGBLIGHT_SPLIT

#define RGBLIGHT_EFFECT_BREATHING

#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_BREATHING
#define RGBLIGHT_LAYERS_RETAIN_VAL
#define RGBLIGHT_LIMIT_VAL 175
#define RGBLIGHT_DEFAULT_VAL ( RGBLIGHT_LIMIT_VAL / 2 )

#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2000
#define SPLIT_USB_TIMEOUT_POLL 10

#define TAPPING_TERM 175
#define TAPPING_TOGGLE 2
#define TAP_CODE_DELAY 10

//#define NO_AUTO_SHIFT_SPECIAL
//#define NO_AUTO_SHIFT_NUMERIC

// Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed
#define DEBOUNCE 5

/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is useful for the Windows task manager shortcut (ctrl+shift+esc).
 */
#define GRAVE_ESC_CTRL_OVERRIDE

// disable action features
#define NO_ACTION_ONESHOT

// Bootmagic Lite key configuration
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define LAYER_STATE_8BIT
