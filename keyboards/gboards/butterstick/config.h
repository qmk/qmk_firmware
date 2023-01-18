#pragma once

#include "config_common.h"

#define VERSION 		"Paula Deen"

#define DEBOUNCE 5
#define FORCE_NKRO

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 10
#define MATRIX_ROW_PINS { F4, F5 }
#define MATRIX_COL_PINS { B0, B1, B2, B3, B4, B5, B6, B7, C6, C7}

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION ROW2COL
