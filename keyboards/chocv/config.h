/* Copyright 2021 BrickBots Labs
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
 #define VENDOR_ID 0xBBB0
 #define PRODUCT_ID 0x0002
 #define DEVICE_VER 0x0001
 #define MANUFACTURER BrickBots Labs
 #define PRODUCT chocV

 /* key matrix size */
 #define MATRIX_ROWS 4
 #define MATRIX_COLS 10


 #define MATRIX_ROW_PINS { F4, F5, D1, D0 }
 #define MATRIX_COL_PINS { B6, B2, B3, B1, F7, C6, D7, E6, B4, B5}
 #define UNUSED_PINS

 /* COL2ROW, ROW2COL*/
 #define DIODE_DIRECTION COL2ROW


 /* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
 #define DEBOUNCE 5

