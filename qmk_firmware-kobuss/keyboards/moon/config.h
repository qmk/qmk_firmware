/*
Copyright 2019 Mathias Andersson <wraul@dbox.se>

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
#define PRODUCT_ID      0xFCB8
#define DEVICE_VER      0x0001
#define MANUFACTURER    EVE
#define PRODUCT         Moon
#define DESCRIPTION     A tenkeyless keyboard with astonishing curves

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 11

#define LED_CAPS_LOCK_PIN B5
#define LED_SCROLL_LOCK_PIN B6

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Backlight */
#define BACKLIGHT_PIN C6
#define BACKLIGHT_LEVELS 3

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
