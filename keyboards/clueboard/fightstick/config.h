#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define PRODUCT_ID      0x23B1
#define MANUFACTURER    Clueboard
#define PRODUCT         Fightstick
#define DESCRIPTION     A 4 direction 8 button joystick

/* key matrix pins */
#define MATRIX_ROWS 3
#define MATRIX_COLS 4
#define DIRECT_PINS { \
    { A5, B4, B6, A10 }, \
    { A6, A4, B5, A9 }, \
    { B0, B1, B2, B3 } \
}
#define UNUSED_PINS

#define JOYSTICK_BUTTON_COUNT 12
#define JOYSTICK_AXES_COUNT 0
