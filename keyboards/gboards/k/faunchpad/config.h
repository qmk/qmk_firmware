#pragma once

//#include "config_common.h"

#define FORCE_NKRO

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 4
#define MATRIX_ROW_PINS { F4, F5 }
#define MATRIX_COL_PINS { B3, B2, B1, B0}

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION ROW2COL
