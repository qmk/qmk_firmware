/*
Copyright 2022 huytbt <huytbt@gmail.com>
SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 13

/* Planck PCB default pin-out */
#define MATRIX_ROW_PINS { C6, D4, D0, D1 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2, B6, D7, E6, B4, B5, D3 }
#define UNUSED_PINS

#define LED_CAPS_LOCK_PIN D2

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
