#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define PRODUCT_ID      0x2011
#define DEVICE_VER      0x0001

/* key matrix pins */
#define MATRIX_ROW_PINS { B5, B7, B2, B0 }
#define MATRIX_COL_PINS { B8, A0, A10, A9 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Backlight configuration
 */
#define LED_MATRIX_ROWS 4
#define LED_MATRIX_ROW_PINS { B13, B14, B15, B1 }
#define LED_MATRIX_COLS 4
#define LED_MATRIX_COL_PINS { B9, B6, B4, B3 }
#define LED_DRIVER_LED_COUNT 16

/* Encoder pins */
#define ENCODERS_PAD_A { A2 }
#define ENCODERS_PAD_B { A1 }
#define ENCODER_RESOLUTION 4
