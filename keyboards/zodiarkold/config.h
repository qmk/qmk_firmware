#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xF901
#define PRODUCT_ID      0xF902
#define DEVICE_VER      0x0001
#define MANUFACTURER    Aleblazer
#define PRODUCT         Zodiark


#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
  #define OLED_TIMEOUT 300000
#endif

#define NO_ACTION_MACRO
#define NO_ACTION_ONESHOT
#define NO_ACTION_TAPPING

#define USE_SERIAL
#define SOFT_SERIAL_PIN D3
#define SERIAL_USE_MULTI_TRANSACTION
#define SELECT_SOFT_SERIAL_SPEED 1

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 7
#define DIODE_DIRECTION COL2ROW

#define ENCODERS_PAD_A { D2 }
#define ENCODERS_PAD_B { D4 }
#define ENCODERS_PAD_A_RIGHT { D4 }
#define ENCODERS_PAD_B_RIGHT { D2 }
#define ENCODER_RESOLUTION 3

/* key matrix pins */
#define MATRIX_ROW_PINS { C6, D7, E6, B4, F4 }
#define MATRIX_COL_PINS { F5, F6, F7, B1, B3, B2, B6 }

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define SPLIT_USB_DETECT

#define RGB_DI_PIN B5
#ifdef RGB_DI_PIN
#define RGBLED_NUM 68
#define RGBLIGHT_SPLIT
#define RGBLED_SPLIT { 34, 34 }
#define RGBLIGHT_LIMIT_VAL 170
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

#endif
