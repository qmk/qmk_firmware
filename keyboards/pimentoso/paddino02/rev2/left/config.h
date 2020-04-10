#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xD00D
#define PRODUCT_ID      0x0021
#define DEVICE_VER      0x0002
#define MANUFACTURER    jlcpcb
#define PRODUCT         Paddino02 rev2
#define DESCRIPTION     10-key ergo macropad

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 4

/* key matrix pins */
#define MATRIX_ROW_PINS { D0, D4, D1 }
#define MATRIX_COL_PINS { D7, E6, B4, B5 }
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

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS

#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LIMIT_VAL undefined
#endif

#endif
