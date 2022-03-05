#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6869 // nabos
#define PRODUCT_ID      0x0001 // 10k
#define DEVICE_VER      0x0001
#define MANUFACTURER    nabos
#define PRODUCT         10k (1x5)
#define DESCRIPTION     A simple chord keyboard

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 2
#define MATRIX_COLS 5

// wiring of each half
#define MATRIX_COL_PINS { C6, D7, E6, B4, B5 }
#define MATRIX_ROW_PINS { B6 }

#define DIODE_DIRECTION COL2ROW


/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Enables This makes it easier for fast typists to use dual-function keys */
#define PERMISSIVE_HOLD

//#define COMBO_ALLOW_ACTION_KEYS
//#define COMBO_VARIABLE_LEN

#define USE_I2C
#define MASTER_RIGHT
//#define MASTER_LEFT
//#define EE_HAND
