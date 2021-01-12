#include "../../config.h"

#undef MANUFACTURER
#undef PRODUCT
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#undef DIODE_DIRECTION

/* USB Device descriptor parameter */
#define MANUFACTURER    Mesh Industries
#define PRODUCT         Atreus52 Treeboard

#define MATRIX_ROW_PINS { C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { B2, B1, F7, F6, F5, F4, B6, D3, D2, D1, D0, D4, B3 }

#define DIODE_DIRECTION COL2ROW
