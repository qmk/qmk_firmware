#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x594d // "YM"
#define PRODUCT_ID      0x4D96 // "M" + 96
#define DEVICE_VER      0x0001
#define MANUFACTURER    YMDK
#define PRODUCT         Melody96
#define DESCRIPTION     Melody96

/* key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 9

/* key matrix pins */
#define MATRIX_ROW_PINS { B7, B3, B2, B1, B0, E6, F0, F1, F4, F5, F6, F7 }
#define MATRIX_COL_PINS { D0, D1, D2, D3, D5, D4, D6, D7, B4 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* number of backlight levels */
#define BACKLIGHT_PIN B6
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 5
#endif

/* Set location for BootMagic key*/
#define BOOTMAGIC_LITE_ROW 5
#define BOOTMAGIC_LITE_COLUMN 0

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN E2
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 18
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif
