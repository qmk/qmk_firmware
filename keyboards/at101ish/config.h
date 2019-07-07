#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0666
#define DEVICE_VER      0xA101
#define MANUFACTURER    Henrik O. Sørensen
#define PRODUCT         AT101(-ish) Keyboard
#define DESCRIPTION     Replacement PCB for AT101/2 keyboards

/* key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 10

/* key matrix pins */
#define MATRIX_ROW_PINS { B1, B0, B2, D5, B3, C7, B7, C6, D0, D3, D1, D2 }
#define MATRIX_COL_PINS { D7, B4, B5, B6, F7, F6, F5, F4, F1, F0 }

#define NUMLOCKLEDPIN D4
#define CAPSLOCKLEDPIN D6
#define SCROLLLOCKLEDPIN E6

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

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