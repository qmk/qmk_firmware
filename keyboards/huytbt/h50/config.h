/*
Copyright 2022 huytbt <huytbt@gmail.com>
SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 14

/*
 * Keyboard Matrix Assignments
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 */
#define MATRIX_ROW_PINS { D1, D0, D4, C6 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2, B6, D7, E6, B4, B5, D2, D3 }

#define LED_CAPS_LOCK_PIN D5

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
// #define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5
