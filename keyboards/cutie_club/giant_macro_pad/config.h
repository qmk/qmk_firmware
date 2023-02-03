/* Copyright 2021 Cutie Club
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
#define MATRIX_ROWS 20
#define MATRIX_COLS 20

/*
 * Keyboard Matrix Assignments
 */
#define MATRIX_ROW_PINS { C10, C11, C12, D2,  B3,  B4,  B5,  B6,  B7,  B8,  A3,  B2,  B1,  B0,  C5,  C4,  A7,  A6,  A5,  A4 }
#define MATRIX_COL_PINS { C9,  C8,  C7,  C6,  B15, B14, B13, B12, A8,  A15, B9,  A2,  A1,  A0,  C3,  C2,  C1,  C0,  F1,  F0 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
