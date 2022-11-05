 /* Copyright 2021 Domanic Calleja
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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4443  //DC
#define PRODUCT_ID      0x4C43  //LC
#define DEVICE_VER      0x3031  //01
#define MANUFACTURER    Dom
#define PRODUCT         Lyra

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

// wiring of each half
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
#define MATRIX_COL_PINS { B2, B3, B1, F7, F6, F5, F4 }

#define DIODE_DIRECTION COL2ROW

#define TAPPING_TERM 100

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* communication between sides */
#define USE_SERIAL
#define SOFT_SERIAL_PIN D2
