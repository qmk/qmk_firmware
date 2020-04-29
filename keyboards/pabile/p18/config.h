#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6666
#define PRODUCT_ID      0x6668
#define DEVICE_VER      0x0001
#define MANUFACTURER    Pabile
#define PRODUCT         P18 Macro Pad
#define DESCRIPTION     An 18-key DIY macropad kit

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 5

/* pin-out for PROMICRO */
#define MATRIX_ROW_PINS { D1, D0, D4, C6 }
#define MATRIX_COL_PINS { D2, D7, E6, B4, B5 }
#define UNUSED_PINS
 
/* Encoder position for PROMICRO */
#define ENCODERS_PAD_A { B6, F6 }
#define ENCODERS_PAD_B { F4, F5 } 

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
