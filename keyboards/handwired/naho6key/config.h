#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* Pinout */
#define PIN_ROW_LEFT D4   // Pro Micro: 4
#define PIN_ROW_RIGHT D0  // Pro Micro: 3
#define PIN_COL_1 F6      // Pro Micro: A1
#define PIN_COL_2 F5      // Pro Micro: A2
#define PIN_COL_3 F4      // Pro Micro: A3
#define PIN_LED_R E6      // Pro Micro: 7
#define PIN_LED_G B4      // Pro Micro: 8
#define PIN_LED_B B5      // Pro Micro: 9

// Unicode mode (UC_LNX, UC_WINC, or UC_MAC)
#define UNICODE_SELECTED_MODES UC_LNX

// Transform TT into LT/MO
#define TAPPING_TOGGLE 1

// USB Device descriptor parameter
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x6061
#define DEVICE_VER 0x0001
#define MANUFACTURER qmkbuilder
#define PRODUCT keyboard
#define DESCRIPTION Keyboard(macro 6 key by naholyr)

// key matrix size
#define MATRIX_ROWS 2
#define MATRIX_COLS 3

// key matrix pins
#define MATRIX_ROW_PINS \
    { PIN_ROW_LEFT, PIN_ROW_RIGHT }
#define MATRIX_COL_PINS \
    { PIN_COL_1, PIN_COL_2, PIN_COL_3 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
//#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() (keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)))

/* prevent stuck modifiers */
#define PREVENT_STUCK_MODIFIERS

#ifdef RGB_DI_PIN
#    define RGBLIGHT_ANIMATIONS
#    define RGBLED_NUM 0
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#endif

#endif
