#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x11FD
#define PRODUCT_ID      0x4D41
#define DEVICE_VER      0xF021
#define MANUFACTURER    qmkEason
#define PRODUCT         Angle
#define DESCRIPTION     Angle

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

/* key matrix pins */
#define MATRIX_ROW_PINS { D2, D3, D4, D5, D6, D7 }
#define MATRIX_COL_PINS { F7, F6, F5, F4, F1, F0, E6, C7, C6, B0, B1, B2, B3, B4, B5, B6, B7 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */

#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 5
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* prevent stuck modifiers */
#define PREVENT_STUCK_MODIFIERS


#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

#endif
