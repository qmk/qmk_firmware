/* Copyright 2019
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

#define DEVICE_VER      0x0001
#define PRODUCT_ID      0x67F3
#define PRODUCT         UtholJR


/* key matrix size */

#define MATRIX_COL_PINS { B0, B2, B10, B11, B12, B13, B14, A8, A9, A10, B1, B5 }
#define MATRIX_ROW_PINS { A7, B4, A0, A2}

#define UNUSED_PINS

//Encoder config
#define ENCODERS_PAD_A { B9 }
#define ENCODERS_PAD_B { B8 }
#define ENCODER_RESOLUTION 2

//OLED config
#define OLED_DISPLAY_128X64
/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define TAPPING_TERM 500

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION



