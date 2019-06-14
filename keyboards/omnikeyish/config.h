#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

#define DYNAMIC_MACRO_COUNT 12
#define DYNAMIC_MACRO_SIZE 48


/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0666
#define DEVICE_VER      0x1337
#define MANUFACTURER    Henrik O. Sørensen
#define PRODUCT         Omnikey(-ish) PCB
#define DESCRIPTION     Replacement PCB for Omnikey keyboards

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 23

/* key matrix pins */
#define MATRIX_ROW_PINS { D2, D3, D4, D5, D6, D7 }
//#define MATRIX_ROW_PINS { D6 }
#define MATRIX_COL_PINS { F0, F1, F2, F3, F4, F5, F6, F7, C7, C6, C5, C4, C3, C2, C1, C0, B0, B1, B2, B3, B4, B5, B6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* number of backlight levels */
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 0
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

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

#define NUMLOCKLEDPIN E0
#define CAPSLOCKLEDPIN E1
#define SCROLLLOCKLEDPIN B7

#define DYNAMIC_MACRO_RANGE SAFE_RANGE + 1


