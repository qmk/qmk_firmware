/*
Copyright (c) 2022 David Kuehling <dvdkhlng TA posteo TOD de>
  
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
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x4451
#define DEVICE_VER 0x0001
#define PRODUCT    DQz11N1G Controller Replacement

/* Matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 19

/* Pin-out */
#define MATRIX_ROW_PINS { D1, D0, D4, C6, D7, E6, B4 }

/* The pin connecting to the SN74HC165 SH/~LD in */
#define ROW_SHIFT_PIN B6

/* Column read via SPI (shift register) */
/* #define MATRIX_COL_PINS { } */
#define UNUSED_PINS

#define LED_CAPS_LOCK_PIN F7 /* A0 */
#define LED_NUM_LOCK_PIN F5 /*A2 */
#define LED_SCROLL_LOCK_PIN F4 /*A3 */

#define LED_FUN_LOCK_PIN F6 /* A1 (handled in layer_state_set_user()) */

/* audio config */
#define AUDIO_PIN B5
#define AUDIO_CLICKY
#define AUDIO_INIT_DELAY
#define AUDIO_CLICKY_FREQ_RANDOMNESS 0.0f
#define NO_MUSIC_MODE

/* diodes go row->col, though this is hard-coded in matrix.c and we drive the
 * matrix differently: we have pull-down on the columns and drive the selected
 * row high */
/* #define DIODE_DIRECTION ROW2COL */
