#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    blindassassin111
#define PRODUCT         Omnikey Blackheart PCB

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 23

/* key matrix pins */
#define MATRIX_ROW_PINS { B7, D0, D1, D2, D3, D4 }
#define MATRIX_COL_PINS { C2, C3, C4, C7, C1, C0, E1, E0, D7, F7, F6, F5, F4, F3, F2, F1, F0, E6, E7, B0, B1, B2, B3 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 0
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* force n-key rollover*/
#define FORCE_NKRO

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

#endif
