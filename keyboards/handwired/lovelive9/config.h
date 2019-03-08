

#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0007
#define DEVICE_VER         0x0001
#define MANUFACTURER    numazu Keyboards
#define PRODUCT         lovelive9
#define DESCRIPTION     lovelive sunshine Keyboards 9Key

/* key matrix size */
#define RGBLIGHT_ANIMATIONS
#define BACKLIGHT_LEVELS 5
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 4
#define BREATHING_PERIOD 2
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

#define MATRIX_ROWS 9
#define MATRIX_COLS 1

/* Planck PCB default pin-out */
#define MATRIX_ROW_PINS { B4, B6, B2, D7, B1, F7, F6, F5, F4 }
#define MATRIX_COL_PINS { NO_PIN }
#define UNUSED_PINS

/* ws2812 RGB LED */


#define USE_SERIAL
#define RGB_DI_PIN D3

#define RGBLED_NUM 9    // Number of LEDs

#if defined(RGBLIGHT_ENABLE) && !defined(IOS_DEVICE_ENABLE)
// USB_MAX_POWER_CONSUMPTION value
//  120  RGBoff
//  330  RGB 6
//  300  RGB 32
 #define USB_MAX_POWER_CONSUMPTION 400
#else
 // fix iPhone and iPad power adapter issue
 // iOS device need lessthan 100
 #define USB_MAX_POWER_CONSUMPTION 100
#endif



/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

#define TAPPING_TERM 200
