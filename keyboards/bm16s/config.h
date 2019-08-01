#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    KPrepublic
#define PRODUCT         bm16s
#define DESCRIPTION     KPrepublic bm16s

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 4

/* key matrix pins */
#define MATRIX_ROW_PINS { D1, D0, D3, D2 }
#define MATRIX_COL_PINS { F7, F6, D4, D6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */

#ifdef BACKLIGHT_PIN
    #define BACKLIGHT_LEVELS 3
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN E2
#ifdef RGB_DI_PIN
    #define RGBLIGHT_ANIMATIONS
    #define RGBLED_NUM 16
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
#endif
