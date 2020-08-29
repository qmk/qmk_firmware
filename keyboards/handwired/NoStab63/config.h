#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
<<<<<<< HEAD
#define VENDOR_ID       0x0000
=======
#define VENDOR_ID       0xFEED
>>>>>>> 4291fa68390067549e51bb52195ec9cabf6153cb
#define PRODUCT_ID      0x1707
#define DEVICE_VER      0x0001
#define MANUFACTURER    Santy
#define PRODUCT         NoStab63

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 18

#define MATRIX_ROW_PINS { B8, A0, A1, A2, B13 }
#define MATRIX_COL_PINS { A4, A5, A6, A7, B15, B14, B12, B11, B10, B9, B7, B6, B5, B4, B3, B2, B1, B0 }

#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* 1 Encoder */
#define ENCODERS_PAD_A { A8 }
#define ENCODERS_PAD_B { A15 }
#define TAP_CODE_DELAY 10
#define ENCODER_RESOLUTION 2

#define FORCE_NKRO
