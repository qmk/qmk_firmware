#pragma once

#include "config_common.h"

#undef MANUFACTURER
#define MANUFACTURER    Kingly-Keys
#undef PRODUCT
#define PRODUCT         The Little Foot
#undef DESCRIPTION
#define DESCRIPTION     A Mighty Small, 45-Percent, Ortholinear Keyboard.

/* key matrix size */
#undef MATRIX_ROWS
#define MATRIX_ROWS 5
#undef MATRIX_COLS
#define MATRIX_COLS 10

/* key matrix pins */
#undef MATRIX_ROW_PINS
#define MATRIX_ROW_PINS { D5, D7, B6, C7, D6 }
#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, B0, E6, B3, B7 }
#undef UNUSED_PINS
#define UNUSED_PINS

/* ws2812 RGB LED */
#define RGB_DI_PIN B1
#define RGBLED_NUM 5    // Number of LEDs
#define RGBLIGHT_HUE_STEP 6
#define RGBLIGHT_SAT_STEP 4
#define RGBLIGHT_VAL_STEP 8

#define RGBLIGHT_TIMER
