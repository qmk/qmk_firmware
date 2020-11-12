/* Copyright 2020 Ungodly Design <hello@ungodly.design>
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
#define VENDOR_ID       0x5544 // "UD" = Ungodly Design
#define PRODUCT_ID      0x544E // "TN" = The Nines
#define DEVICE_VER      0x9999
#define MANUFACTURER    Ungodly Design
#define PRODUCT         The Nines

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

/* Keyboard Matrix Assignments */
#define DIRECT_PINS { \
    { F4, F5, F6 }, \
    { F7, B1, B3 }, \
    { B2, B6, B5 }  \
}
#define UNUSED_PINS

/* Rotary Encoder Assignments */
#define ENCODERS_PAD_A { C6, E6 }
#define ENCODERS_PAD_B { D7, B4 }

#define ENCODER_RESOLUTION 2

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
