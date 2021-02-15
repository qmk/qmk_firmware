#pragma once

#include "config_common.h"

#define MATRIX_ROWS 8
#define MATRIX_COLS 8

#define MATRIX_ROW_PINS { D1, D0, D4, C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2, B6 }
#define UNUSED_PINS { D3, D2 }

/* LEDs are not used in the standard 64key configuration. */
#define RGB_DI_PIN D3
#define RGBLED_NUM 0

#define DIODE_DIRECTION COL2ROW

#define PERMISSIVE_HOLD
