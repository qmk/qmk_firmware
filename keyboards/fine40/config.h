#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xA059
#define PRODUCT_ID      0x4564
#define DEVICE_VER      0x0001
#define MANUFACTURER    Aidan
#define PRODUCT         fine!40
#define DESCRIPTION     A modular PCB with Wired and Bluetooth options

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

#define ENCODER_RESOLUTION 2
#define ENCODERS_PAD_A { D5 }
#define ENCODERS_PAD_B { B7 }

/* key matrix pins */
#define MATRIX_ROW_PINS { F5, F6, B2, B5, F4, D4, B4, B6 }
#define MATRIX_COL_PINS { B3, E6, B1, D7, F7, C6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define OLED_DISPLAY_128X64 //Comment this out to change the screen size

/* number of backlight levels */

#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 3
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

#define RGB_DI_PIN C7
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 8
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

#endif
