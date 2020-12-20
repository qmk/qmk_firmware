#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x726B
#define PRODUCT_ID      0x616B
#define DEVICE_VER      0x0001
#define MANUFACTURER    rainkeebs
#define PRODUCT         akhimbo
#define DESCRIPTION     split traditional with a touch of weeb

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

/* key matrix pins */
#define MATRIX_ROW_PINS { F6, C6, D4, D0 }
#define MATRIX_COL_PINS { D1, B6, B2, B3, B1, F7 }
#define MATRIX_ROW_PINS_RIGHT { F4, F7, F6, B6 }
#define MATRIX_COL_PINS_RIGHT { D4, C6, D7, E6, B4, B5 }
#define UNUSED_PINS

#define ENCODERS_PAD_A { F4 }
#define ENCODERS_PAD_B { F5 }
#define ENCODERS_PAD_A_RIGHT { D1 }
#define ENCODERS_PAD_B_RIGHT { D0 }

/* usb handedness? */
#define SPLIT_USB_DETECT

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

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

/* define serial pin */
#define SOFT_SERIAL_PIN D3

#endif