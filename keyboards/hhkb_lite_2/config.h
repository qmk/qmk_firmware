#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 14

/* key matrix pins */
#define MATRIX_ROW_PINS { F5, F4, F1, F0, B0, B1, B2, B3 }
#define MATRIX_COL_PINS { F6, F7, B6, B5, B4, D7, D6, D4, D5, C7, C6, D3, D2, D1}
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Bootmagic keys are non-standard because of matrix */
#define BOOTMAGIC_LITE_ROW 5
#define BOOTMAGIC_LITE_COLUMN 9
