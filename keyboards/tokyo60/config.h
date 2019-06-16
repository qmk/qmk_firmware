#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Tokyo Keyboard
#define PRODUCT         tokyo60
#define DESCRIPTION     q.m.k. keyboard firmware for tokyo60

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

/* number of backlight levels */
#define BACKLIGHT_PIN B7
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 6
//#define BACKLIGHT_ON_STATE 1
#endif

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Set power consumption to work with mobile devices */
#define USB_MAX_POWER_CONSUMPTION 100

/* key matrix pins */
#define MATRIX_ROW_PINS { D0, D1, D2, D3, D5 }
#define MATRIX_COL_PINS { F0, F1, E6, C7, C6, B6, D4, B1, B2, B5, B4, D7, D6, B3 }
#define UNUSED_PINS

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN F7
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 10
#define RGBLIGHT_HUE_STEP 12
#define RGBLIGHT_SAT_STEP 12
#define RGBLIGHT_VAL_STEP 12
#endif

/* For Production */
#define QMK_ESC_OUTPUT F0 // usually COL
#define QMK_ESC_INPUT D0 // usually ROW

#endif
