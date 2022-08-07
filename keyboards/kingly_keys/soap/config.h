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

 /* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 4

#define ENCODERS_PAD_A { D6 }
#define ENCODERS_PAD_B { D7 }

 /* key matrix pins */
#define MATRIX_ROW_PINS { C7, C6 }
#define MATRIX_COL_PINS { F4, F1, F0, D5 }
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
#define RGB_DI_PIN B6
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 3
