/* Copyright 2021 Kyle McCreery 
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
#define MATRIX_ROWS 7
#define MATRIX_COLS 7

/* key matrix pins */
#define MATRIX_ROW_PINS { D0, D1, D4, C3, C0, C1, C2}
#define MATRIX_COL_PINS { B0, D7, D6, D5, B1, B2, B3}

/* encoder pins */
#define ENCODERS_PAD_A { B4 }
#define ENCODERS_PAD_B { B5 }

/* encoder resolution */
#define ENCODER_RESOLUTION 4
#define TAP_CODE_DELAY 10

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Define custom font */
#define OLED_FONT_H "lib/mercutiofont.c"

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
