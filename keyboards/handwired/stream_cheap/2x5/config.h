#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 5

/* define direct pins used */
#define DIRECT_PINS { { D1,C6,B4,B5,B2}, { D0,D4,D7,E6,B6} }

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
