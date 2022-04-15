#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x8490
#define PRODUCT_ID      0x0006
#define DEVICE_VER      0x0002
#define MANUFACTURER    QUARKeys
#define PRODUCT         Z60
#define DESCRIPTION     Keyboard

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* key matrix pins */
#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4 }
#define MATRIX_COL_PINS { E6, F0, F7, F1, F6, F5, F4, C7, B7, D5, C6, B6, B5, D7, D4 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */

//#define BACKLIGHT_PIN D1
//#ifdef BACKLIGHT_PIN
//#define BACKLIGHT_LEVELS 8
//#endif

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
#define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
#define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#define RGBLIGHT_LIMIT_VAL 130
#define RGB_DI_PIN D6
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define DISABLE_RGB_MATRIX_STATIC_LIGHT
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_TWINKLE_4
#define RGBLIGHT_LAYERS
#define RGBLIGHT_SLEEP
#endif

#define RGBLED_NUM 78
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8



#define RGBLIGHT_SLEEP

#define RGBLIGHT_LAYERS
#define RGBLIGHT_MAX_LAYERS 10

#endif