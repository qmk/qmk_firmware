#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x5350
#define PRODUCT_ID      0x0727
#define DEVICE_VER      0x0001
#define MANUFACTURER    MaiTheSan
#define PRODUCT         Satxri6key

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 3

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { F7, F6 }
#define MATRIX_COL_PINS { F1, F4, F5 }

#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN F0