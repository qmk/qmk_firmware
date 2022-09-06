/* Copyright 2020 tominabox1
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
#define VENDOR_ID       0x4B50 // "KP"
#define PRODUCT_ID      0x3430 // "40"
#define DEVICE_VER      0x0001
#define MANUFACTURER    KPRepublic
#define PRODUCT         BM40 Hotswap RGB

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

/* key matrix pins */
#define MATRIX_ROW_PINS { B3, B2, E6, B5 }
#define MATRIX_COL_PINS { B6, C6, B4, D7, D4, D6, C7, F6, F5, F4, F1, F0 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN E2
#define DRIVER_LED_TOTAL 53
#ifdef RGB_DI_PIN
    #define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#endif
#ifndef RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
#endif
