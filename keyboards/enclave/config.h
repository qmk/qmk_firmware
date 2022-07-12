#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0x1117
#define PRODUCT_ID      0x0E0E
#define DEVICE_VER      0x0001
#define PRODUCT         Enclave-1

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

/* Keyboard Matrix Assignments*/
#define MATRIX_ROW_PINS { D6, B6, F5 }
#define MATRIX_COL_PINS { B4, B7, C7 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* RGB light setup*/
#define RGB_DI_PIN B5
#define RGBLED_NUM 2
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_SLEEP

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST
