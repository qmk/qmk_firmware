 /* Copyright 2021 Weirdo
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

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_COL_PINS { A3, A4, A5, A7, B0, B1, B10, B15, A8, A9, A10, B7, B6, B5, B4}
#define MATRIX_ROW_PINS { B12, B13, B14, C11, A1}
#define DIODE_DIRECTION ROW2COL
#define DEBOUNCE 5



#define RGB_DI_PIN A6
#define RGBLED_NUM 64
//#define RGBLIGHT_DISABLE_KEYCODES




/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE



