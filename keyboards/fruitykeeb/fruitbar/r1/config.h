/* Copyright 2021 Brandon Lewis
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
#define VENDOR_ID       0x666B // fk
#define PRODUCT_ID      0x6662 // fb
#define DEVICE_VER      0x0001 // rev 1
#define MANUFACTURER    fruitykeeb
#define PRODUCT         Fruitbar

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 11

/* key matrix pins */
#define MATRIX_ROW_PINS { F4, F5, F6, F7, B1 }
#define MATRIX_COL_PINS { D3, D2, D4, C6, D7, E6, B4, B5, B6, B2, B3 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Encoder Definitions */
#define ENCODERS_PAD_A { F0 }
#define ENCODERS_PAD_B { F1 }
#define ENCODER_RESOLUTION 4

/* RGB Definitions */
#define RGB_DI_PIN C7
#define RGBLED_NUM 8
