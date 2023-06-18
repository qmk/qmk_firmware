/* Copyright 2023 Cutie Club

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

#include "lib/pcal6416a/pcal6416a.h"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 5

/*
 * Keyboard Matrix Pin Assignments
 */
#define PCAL_ADDRESS (0b0100000 << 1)
#define PCAL_ROW_PINS \
    { PCAL_1_5, PCAL_1_0, PCAL_1_1, PCAL_1_2, PCAL_1_3 }
#define PCAL_COL_PINS \
    { PCAL_1_4, PCAL_0_5, PCAL_0_4, PCAL_0_3, PCAL_0_2 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define LED_PCAL_PINS \
    { PCAL_0_0, PCAL_0_1 }

#define WS2812_DI_PIN B2
#define RGBLED_NUM 1

#define DEFAULT_INDICATOR_LED NUM_LOCK
