#include "../../config.h"

/* pins for PCB v2 */
#undef MATRIX_ROW_PINS
#define MATRIX_ROW_PINS { C6, D7, E6, B4, B5 }

#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS { D1, D0, D4, B2 }

#undef ENCODERS_PAD_A
#define ENCODERS_PAD_A { F4, F7 }
#undef ENCODERS_PAD_B
#define ENCODERS_PAD_B { F5, B1 }
#define ENCODERS_PAD_C { F6, B3 }
