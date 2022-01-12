#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x416B //Ak
#define PRODUCT_ID      0x0007
#define DEVICE_VER      0x0001
#define MANUFACTURER    Atlantis
#define PRODUCT         AK7
#define DESCRIPTION     Keyboard

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

/* key matrix pins */
#define MATRIX_ROW_PINS { F0, B4, B5 }
#define MATRIX_COL_PINS { F6, F7, D3 }
#define UNUSED_PINS

/* encoder pins */
#define ENCODERS_PAD_A { D2 }
#define ENCODERS_PAD_B { D1 }
#define ENCODER_RESOLUTION 4

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */

#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 3
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
#define FORCE_NKRO

#define RGB_DI_PIN B7
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYER_BLINK
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF //RGB LAYERS在RGB关闭的情况下仍然有效，实现全局分层指示灯。
#define RGBLED_NUM 30
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LIMIT_VAL 200
#endif

#endif