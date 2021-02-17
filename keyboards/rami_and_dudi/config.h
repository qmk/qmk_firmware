#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x2004
#define DEVICE_VER      0x0001
#define MANUFACTURER    1up Keyboards
#define PRODUCT         Four Banger
#define DESCRIPTION     2x2 grid

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 3

/* key matrix pins */
#define MATRIX_ROW_PINS { E6, B4, B5, B1 }
#define MATRIX_COL_PINS { B3, B2, B6 }
#define UNUSED_PINS


/* key matrix Encoders */

#define ENCODERS_PAD_A { D4, D7 }
#define ENCODERS_PAD_B { D0, C6 }
#define ENCODER_RESOLUTION 4

/* key matrix Encoder switch */
#define DIP_SWITCH_PINS { F4 }





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

#define RGB_DI_PIN F4
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 1
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

#endif
