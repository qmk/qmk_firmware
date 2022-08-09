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

#define MATRIX_ROW_PINS { A9, A10, B10, B11, B15}
#define MATRIX_COL_PINS { A8, B14, B13, B12, B1, B0, A7 , A1 , A15, B3, B4, B5, B6, B7, B8}
#define DIODE_DIRECTION ROW2COL
#define DEBOUNCE 5



#define RGB_DI_PIN A6
#define RGBLED_NUM 1
//#define RGBLIGHT_DISABLE_KEYCODES




/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE



