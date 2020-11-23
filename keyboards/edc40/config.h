#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0x5454 // TT
#define PRODUCT_ID 0x0002
#define DEVICE_VER 0x0001
#define MANUFACTURER OJ
#define PRODUCT edc40

#define MATRIX_ROWS 4
#define MATRIX_COLS 12

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
 #define MATRIX_ROW_PINS { D4, D6, D7, F7 }
 #define MATRIX_COL_PINS { B0, B1, B2, B3, D0, D1, D2, D3, D5, B4, B5 }
 #define UNUSED_PINS

 #define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
#define RGB_DI_PIN { C6 }
