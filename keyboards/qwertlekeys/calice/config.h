 /* Copyright 2021 Joah Nelson (Jels)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation,   either version 2 of the License, or
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

/* Define Matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 8

#define BOOTMAGIC_LITE_COLUMN 0
#define BOOTMAGIC_LITE_ROW 1

/*Define Matrix Pins */
#define MATRIX_ROW_PINS {F0, F1, F5, F4, C6, C7, B5, B6, D4, D2, D5, D3}
#define MATRIX_COL_PINS {D7, B4, F7, F6, D1, B7, B3, B2} 

#define LED_CAPS_LOCK_PIN D6

/* Envoder */
#define ENCODERS_PAD_A {B0}
#define ENCODERS_PAD_B {B1}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
