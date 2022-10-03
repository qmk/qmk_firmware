#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14
// ROWS: Top to bottom, COLS: Left to right
#define MATRIX_ROW_PINS {C2,D0,B0,C7,C5}
#define MATRIX_COL_PINS {C4,C6,B7,B6,B5,B4,B3,B2,B1,D6,D5,D4,D2,D1}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define QMK_ESC_OUTPUT  C4 // usually COL
#define QMK_ESC_INPUT   C2 // usually ROW

#define RGB_DI_PIN D3
#define RGBLED_NUM 12
#define BACKLIGHT_LEVELS 5

#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_ANIMATIONS
