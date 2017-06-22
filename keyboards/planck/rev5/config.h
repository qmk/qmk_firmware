#ifndef REV5_CONFIG_H
#define REV5_CONFIG_H

#include "../config.h"

#define DEVICE_VER 0x0005

#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS

#define MATRIX_ROW_PINS { B0, E7, A3, F1 }
#define MATRIX_COL_PINS { E6, E3, E4, D3, D4, D5, C0, A7, A6, E1, E0, D7 }

#undef BACKLIGHT_PIN

#define BACKLIGHT_PIN A5

#endif