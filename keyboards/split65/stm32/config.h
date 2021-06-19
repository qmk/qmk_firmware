#pragma once

#include "config_common.h"

// USB Device descriptor parameter
#define VENDOR_ID     0x1209
#define PRODUCT_ID    0x0001
#define DEVICE_VER    0x0001
#define MANUFACTURER  percyjw
#define PRODUCT       split65

// Audio
#define AUDIO_PIN A5
#define AUDIO_PIN_ALT A4
#define AUDIO_PIN_ALT_AS_NEGATIVE

// Matrix Assignments
#define MATRIX_ROWS 10 //Rows are doubled-up
#define MATRIX_COLS 8

#define MATRIX_COL_PINS {A2, A1, A0, B8, B13, B14, B15, B9}
#define MATRIX_ROW_PINS {B5, B4, B3, B2, B1}

// COL2ROW, ROW2COL
#define DIODE_DIRECTION COL2ROW

#define MATRIX_IO_DELAY 5

// Split Keyboard specifics
#define MASTER_LEFT
#define SOFT_SERIAL_PIN A9
#define USART_REMAP
#define SELECT_SOFT_SERIAL_SPEED 1
#define SERIAL_USART_DRIVER SD1
#define SERIAL_USART_TX_PAL_MODE 7
#define SERIAL_USART_TIMEOUT 100

// Debounce to reduce unintended double-presses use 0 if not needed
#define DEBOUNCE 5

// Feature diable options
//#define NO_DEBUG
//#define NO_PRINT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
