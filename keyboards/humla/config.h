#pragma once
#include "config_common.h"

// USB device descriptor parameter
#define MANUFACTURER    jmnw
#define PRODUCT         humla
#define DESCRIPTION     A 36 key column-staggered split keyboard.

// key matrix size
#define MATRIX_ROWS 4
#define MATRIX_COLS 10

// wiring
#define MATRIX_ROW_PINS { B1, B3, B2, B6 }
#define MATRIX_COL_PINS { D4, F4, F5, F6, F7, C6, D7, E6, B4, B5 }
#define DIODE_DIRECTION COL2ROW
