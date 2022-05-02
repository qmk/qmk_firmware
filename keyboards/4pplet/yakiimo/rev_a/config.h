/*
Copyright 2022 Stefan Sundin "4pplet" <4pplet@protonmail.com>

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4444
#define PRODUCT_ID      0x000A
#define DEVICE_VER      0x0002
#define MANUFACTURER    4pplet
#define PRODUCT         Yakiimo Rev A

#define MATRIX_ROWS 12
#define MATRIX_COLS 9

#define MATRIX_COL_PINS { B0, A5, A4, A3, A2, A1, A0, C15, A8 }
#define MATRIX_ROW_PINS { B10, B1, C13, C14, B14, B12, B9, B8, B5, B4, A15, B3 }
#define DIODE_DIRECTION COL2ROW

#define LED_CAPS_LOCK_PIN A6
#define LED_SCROLL_LOCK_PIN A7

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

#define STM32_HSECLK 8000000
