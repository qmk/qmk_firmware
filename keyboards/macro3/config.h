/* Copyright 2020 David Philip Barr <@davidphilipbarr>
 * Copyright 2021 @filterpaper
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
#define VENDOR_ID       0xC88B
#define PRODUCT_ID      0x3388
#define DEVICE_VER      0x0003
#define MANUFACTURER    DPB
#define PRODUCT         Macro3

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 4

/* key matrix pins */
#define DIRECT_PINS { \
    { D7, C6, D4, D1 }, \
    { B1, B4, B5, B3 }  \
}

#define ENCODERS_PAD_A { D2, F7 }
#define ENCODERS_PAD_B { D3, F6 }

#define UNUSED_PINS

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Top right key */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 3

