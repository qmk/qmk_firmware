#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0C61
#define DEVICE_VER      0x00C6
#define MANUFACTURER    PhrygianDesign
#define PRODUCT         ph100 v1.0.0
#define DESCRIPTION     100 key keyboard

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 10

#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5, B6, B7, B8, B9 }
#define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7, A8, A9 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 10
