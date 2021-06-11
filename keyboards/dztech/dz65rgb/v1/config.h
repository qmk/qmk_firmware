#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0x445A
#define PRODUCT_ID      0x1420
#define DEVICE_VER      0x0001
#define MANUFACTURER    DZTECH
#define PRODUCT         DZ65RGB

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { B1, B10, B11, B14, B12 }
#define MATRIX_COL_PINS { A6, A7, B0, B13, B15, A8, A15, B3, B4, B5, B8, B9, C13, C14, C15 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5

#ifdef RGB_MATRIX_ENABLE
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#    define DRIVER_ADDR_1 0b1110100
#    define DRIVER_ADDR_2 0b1110111
#    define DRIVER_COUNT 2
#    define DRIVER_1_LED_TOTAL 35
#    define DRIVER_2_LED_TOTAL 33
#    define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
#endif
