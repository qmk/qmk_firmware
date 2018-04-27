#include "../../config.h"
#define PREVENT_STUCK_MODIFIERS

// for the broken board
#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS { F1, F0, B0, B2, F4, F5, F6, F7, D4, D6, B4, D7 }