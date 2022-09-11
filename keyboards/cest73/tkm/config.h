 /* Copyright 2021 cest73 
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
#define MATRIX_ROWS 11
#define MATRIX_COLS 10

/* matrix sz handy ruler:  1   2   3   4   5   6   7   8   9  10  11  12 */
/* key matrix pins */
/*    row    handy ruler: r0  r1  r2  r3  r4  r5  r6  r7  r8  r9  r10 */
#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5, B6, B7, C6, C7, D0 }
/*    column handy ruler: c0  c1  c2  c3  c4  c5  c6  c7  c8  c9 */
#define MATRIX_COL_PINS { D1, D2, D3, D4, D5, D6, D7, F0, F1, F4 }

//NOTE: if D6 pin shows any issues in exploatation the LED on the Teensy is to be removed

#define LED_NUM_LOCK_PIN F6
#define LED_CAPS_LOCK_PIN F5
#define LED_SCROLL_LOCK_PIN F7
#define LED_PIN_ON_STATE 0
//TODO change the E6 pin to either B5, B6, B7 or C6 to utilize hardware PWM on a future PCB revision
#define BACKLIGHT_PIN E6

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* force n-key rollover*/
#define FORCE_NKRO
