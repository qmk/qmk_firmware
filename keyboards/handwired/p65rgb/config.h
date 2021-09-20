/*
Copyright 2019 marhalloweenvt

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
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x75B4
#define DEVICE_VER      0x0001
#define MANUFACTURER    marhalloweenvt
#define PRODUCT         p65rgb

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 17

/* key matrix pins */
#define MATRIX_ROW_PINS { C7, C6, B6, B5, D5 }
#define MATRIX_COL_PINS { E6, F0, F1, F4, F5, F6, F7, B0, B1, B2, B3, B7, D0, D1, D2, D3, D7 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN B4
#define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_LED_PROCESS_LIMIT 4
#define RGB_MATRIX_LED_FLUSH_LIMIT 26
#define DRIVER_LED_TOTAL 83
#define RGBLIGHT_LIMIT_VAL 180

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define QMK_ESC_OUTPUT E6 // usually COL
#define QMK_ESC_INPUT C7 // usually ROW
