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

#define MATRIX_COL_PINS { A4, C15, C14, A5, A6,  A15, B1, B10, B12, B13, B14, B15,  B6, A8, B5}
#define MATRIX_ROW_PINS { B7, B8, B9, C13, B4}
#define DIODE_DIRECTION ROW2COL

#define RGB_DI_PIN A7
#define RGBLED_NUM 78
//#define RGBLIGHT_DISABLE_KEYCODES




/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE



