#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 10

/* key matrix pins */
#define MATRIX_ROW_PINS { F0, F1, F4, D4, F6, F5, F7, B6, B5, D5, C7, C6 }
#define MATRIX_COL_PINS { D1, D0, B7, B3, B2, B1, B0, E6, D2, D3 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* force n-key rollover*/
#define FORCE_NKRO
