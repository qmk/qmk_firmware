#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 3

/* key matrix pins */
#define MATRIX_ROW_PINS { D4, C6, D7, E6 }
#define MATRIX_COL_PINS { F7, B1, B3 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
