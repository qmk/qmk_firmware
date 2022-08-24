#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 12

/* key matrix pins */
#define MATRIX_ROW_PINS { D7, E6, B4, B5, B6 }
#define MATRIX_COL_PINS { F4, F6, F5, F7, B1, B3, C6, D4, D0, D1, D2, D3 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5  // 5 is default
