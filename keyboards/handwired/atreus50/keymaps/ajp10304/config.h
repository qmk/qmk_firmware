#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS

#define MATRIX_ROW_PINS { D4, D5, C7, C6 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, D7, D1, B7, D0, B3, B2, B1, B0 }

#endif
