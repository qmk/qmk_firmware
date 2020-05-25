#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID     0xFEED
#define PRODUCT_ID    0x01ED
#define DEVICE_VER      0x0001

#define MANUFACTURER "QMK"
#define USBSTR_MANUFACTURER    'Q', '\x00', 'M', '\x00', 'K', '\x00', ' ', '\x00', '\xc6', '\x00'
#define PRODUCT "8x18"
#define USBSTR_PRODUCT         'C', '\x00', 'h', '\x00', 'i', '\x00', 'b', '\x00', 'i', '\x00', 'O', '\x00', 'S', '\x00', ' ', '\x00', 'Q', '\x00', 'M', '\x00', 'K', '\x00'
#define DESCRIPTION "QMK keyboard firmware with ChibiOS"

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 18
#define DIODE_DIRECTION ROW2COL
#define MATRIX_HAS_GHOST

// V0
//#define MATRIX_ROW_PINS { B15, A8, A9, A10, A4, B14, A15, B3 }
//#define MATRIX_COL_PINS { B4, B5, B6, B7, B8, B9, B13, B11, B10, B1, B0, A7, A6, A3, A2, A1, A0, C15 }

// V1
#define MATRIX_COL_PINS { A7, B10, B1, B0, A6, A5, A4, A3, A2, A1, A0, B11, B8, B7, B6, B5, B4, B3 }
//#define MATRIX_ROW_PINS { A15, A10, A9, A8, B15, B14, B13, B12 }
#define MATRIX_ROW_PINS { B12, B13, B14, B15, A8, A9, A10, A15 }

// bitbanged RGB
#define RGB_DI_PIN B9

// the on-board LED for the bluepill board. 
// usually C13
//#define STM32LED C13
