#pragma once

#include "config_common.h"

// wiring of each half
#define MATRIX_ROW_PINS { F4, F5, C6, D7, E6 }
#define MATRIX_COL_PINS { F7, F6, B1, B3, B2, B6, B5, B4 }
#define DIODE_DIRECTION ROW2COL

/* ws2812 RGB LED */
#define RGB_DI_PIN D3
#define RGBLED_NUM 1    // Number of LEDs
