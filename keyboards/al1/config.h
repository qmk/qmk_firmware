#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"


/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6050
#define DEVICE_VER      0x0104
#define MANUFACTURER    Alsoran
#define PRODUCT         AL1

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 20

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
 
#define BACKLIGHT_PIN B6
#define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 3


/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCING_DELAY 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE


/* key combination for magic key command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)


#endif
