#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x21FF
#define PRODUCT_ID      0xAA99
#define DEVICE_VER      0x0002
#define MANUFACTURER    cablecardesigns
#define PRODUCT         cypher
#define DESCRIPTION     QMK Firmware for rev6 Cypher PCB

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 10

#define MATRIX_ROW_PINS { B0, F1, F5, F6, F7, D1, F4, D4, C6, C7 }
#define MATRIX_COL_PINS { D6, D7, B4, B5, B6, B7, B3, B2, B1, F0 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL, or CUSTOM_MATRIX */
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 5

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is userful for the Windows task manager shortcut (ctrl+shift+esc).
 */
#define GRAVE_ESC_CTRL_OVERRIDE

#define BACKLIGHT_PIN D0

#define RGB_DI_PIN E6
#ifdef RGB_DI_PIN
   #define RGBLED_NUM 10
   #define RGBLIGHT_HUE_STEP 12
   #define RGBLIGHT_SAT_STEP 25
   #define RGBLIGHT_VAL_STEP 12
   #define RGBLIGHT_LIMIT_VAL 255
   #define RGBLIGHT_SLEEP
   #define RGBLIGHT_ANIMATIONS
#endif
