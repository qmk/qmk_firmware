#pragma once

#ifndef PROMICRO_CONFIG_H
#define PROMICRO_CONFIG_H

#include "config_common.h"

// USB Device descriptor parameter
#define VENDOR_ID     0x1209
#define PRODUCT_ID    0x0001
#define DEVICE_VER    0x0001
#define MANUFACTURER  percyjw
#define PRODUCT       split65

// Matrix Assignments
#define MATRIX_ROWS 10 //Rows are doubled-up
#define MATRIX_COLS 8

#define MATRIX_COL_PINS {F4, F5, F6, F7, B1, B3, B2, B6}
#define MATRIX_ROW_PINS {D4, C6, D7, E6, B4}

// COL2ROW, ROW2COL
#define DIODE_DIRECTION COL2ROW

#define MATRIX_IO_DELAY 5

// Split Keyboard specifics
#define MASTER_LEFT
#define SOFT_SERIAL_PIN D3
#define SELECT_SOFT_SERIAL_SPEED 1

// Debounce to reduce unintended double-presses use 0 if not needed
#define DEBOUNCE 5

// Feature diable options
//#define NO_DEBUG
//#define NO_PRINT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#endif
