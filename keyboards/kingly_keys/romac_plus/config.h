#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4B4B
#define PRODUCT_ID      0x0002
#define DEVICE_VER      0x0001
#define MANUFACTURER    TheRoyalSweatshirt
#define PRODUCT         RoMac+
#define DESCRIPTION     A *Plaid inspired twelve-key macropad with upgraded features
/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 3

/* key matrix pins */
#define MATRIX_ROW_PINS { C6, D4, D2, D3 }
#define MATRIX_COL_PINS { F6, F5, F4 }
#define UNUSED_PINS

#define ENCODERS_PAD_A { B3 }
#define ENCODERS_PAD_B { B2 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */
#define BACKLIGHT_LEVELS 0

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#define RGB_DI_PIN F7
#define RGBLED_NUM 4    // Number of LEDs

#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 6
#define RGBLIGHT_SAT_STEP 4
#define RGBLIGHT_VAL_STEP 8
