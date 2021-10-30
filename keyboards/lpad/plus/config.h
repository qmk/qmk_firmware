#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    lpad
#define PRODUCT         plus
#define DESCRIPTION     Keyboard

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 6

/* key matrix pins */
#define MATRIX_ROW_PINS { D2, D3, D4, D5, D6 }
#define MATRIX_COL_PINS { B4, B5, B6, B7, D7, E6 }
#define UNUSED_PINS

/* via plus layer */
// #ifndef DYNAMIC_KEYMAP_LAYER_COUNT
// #define DYNAMIC_KEYMAP_LAYER_COUNT 5


#define ENCODERS_PAD_B { C6, F5, F0 }
#define ENCODERS_PAD_A { C7, F4, F1 }

#define ENCODER_RESOLUTION 4

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#ifdef OLED_DRIVER_ENABLE
  #define OLED_TIMEOUT 66666
#endif

#if !defined(OLED_FONT_WIDTH)
#    define OLED_FONT_WIDTH 6
#endif

// Font render height
#if !defined(OLED_FONT_HEIGHT)
#    define OLED_FONT_HEIGHT 8
#endif

#define OLED_FONT_H "./lib/glcdfont.c"

#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 3
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE


#define RGB_DI_PIN B0
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS

// #define RGB_DI_PIN B0
// #define DRIVER_LED_TOTAL 23 //一共有多少个灯，64+12个底灯﻿
// #define RGB_DISABLE_WHEN_USB_SUSPENDED true

#define RGBLED_NUM 30
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LIMIT_VAL 255
#endif

/* EEPROM for via */
#define DYNAMIC_KEYMAP_LAYER_COUNT 5
