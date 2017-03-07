#include "../../config.h"

#undef MANUFACTURER
#undef PRODUCT
#undef DESCRIPTION
#undef MATRIX_ROWS
#undef MATRIX_COLS
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS

/* USB Device descriptor parameter */
#define MANUFACTURER    Mesh Industries
#define PRODUCT         Atreus52 Treeboard
#define DESCRIPTION     q.m.k. keyboard firmware for Atreus52

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 11

// wiring of each half
#define MATRIX_ROW_PINS { D2, D3, D1, D0, D4 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2, B6, B5, B4, E6 }

