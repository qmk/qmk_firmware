/* Copyright 2021 Ananya Kirti
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
#define MATRIX_ROWS 2
#define MATRIX_COLS 3

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { F7, B1 }
#define MATRIX_COL_PINS { F6, F5, F4 }

#define DIODE_DIRECTION COL2ROW





// D4 D0
// C6 E6 D7

#define LED_NUM_LOCK_PIN    D4
#define LED_CAPS_LOCK_PIN   D0
#define LED_SCROLL_LOCK_PIN C6
#define LED_COMPOSE_PIN     E6
#define LED_KANA_PIN        D7



#define ENCODERS_PAD_A { B3 }
#define ENCODERS_PAD_B { B2 }