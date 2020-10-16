 /* 
 Copyright 2020 Alec Penland
 Copyright 2020 Garret Gartner
  
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
#define VENDOR_ID       0xAB13
#define PRODUCT_ID      0x4511
#define DEVICE_VER      0x0001
#define MANUFACTURER    Abec13
#define PRODUCT         45ATS

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 14

#define ENCODERS_PAD_A { B4 }
#define ENCODERS_PAD_B { B5 }

/* key matrix pins */
#define MATRIX_ROW_PINS { D3, D5, D7, D6 }
#define MATRIX_COL_PINS { E6, B0, B1, B2, B3, B7, F6, F5, F4, C7, F7, C6, B6, D4 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
