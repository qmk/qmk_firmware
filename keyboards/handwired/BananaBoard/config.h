#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Sepsis
#define PRODUCT         BananaBoard
#define DESCRIPTION     MuchBanana

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 8

/* key matrix pins */
#define MATRIX_ROW_PINS { B1 }
#define MATRIX_COL_PINS { C6, D4, D0, D1, F4, F5, F6, F7 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */



/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5



#endif