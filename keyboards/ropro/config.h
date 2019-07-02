#pragma once 

/* Copyright 2019 Garret G. (TheRoyalSweatshirt)
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.#pragma once 
 */

#include "config_common.h" 

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0002
#define DEVICE_VER      0x0001
#define MANUFACTURER    Kingly-Keys
#define PRODUCT         The_RoPro
#define DESCRIPTION     A 75-key ortholinear keyboard with rotary encoder

 /* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 14

#define NUMBER_OF_ENCODERS 1
#define ENCODERS_PAD_A { B7 }
#define ENCODERS_PAD_B { D5 }

 /* key matrix pins */
#define MATRIX_ROW_PINS { F4, F5, F6, F7, B1, F1, NO_PIN }
#define MATRIX_COL_PINS { F0, D1, D0, D4, C6, D7, E6, B4, B5, B3, B2, B6, D2, C7 }
#define UNUSED_PINS

 /* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

 /* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

 /* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

 /* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED --- DIN Pin Routed to VIA on main PCB marked "RGB" */
#define RGB_DI_PIN D3

#define RGBLIGHT_ANIMATIONS

#define RGBLED_NUM 16
