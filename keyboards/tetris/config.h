#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Fengz
#define PRODUCT         Tetris
#define DESCRIPTION     Planck mit
#define QMK_ESC_OUTPUT B0
#define QMK_ESC_INPUT D7
#define QMK_LED B7
#define QMK_SPEAKER B5

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

/* key matrix pins */
#define MATRIX_ROW_PINS { B3, B2, B1, B0 }
#define MATRIX_COL_PINS { D7, B4, B6, C6, C7, F6, F7, D4, D2, D3, D5, D6 }
#define UNUSED_PINS

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

#define TAPPING_TERM 200
#define PERMISSIVE_HOLD

#ifdef AUDIO_ENABLE
  #define B5_AUDIO
  #define STARTUP_SONG SONG(ONE_UP_SOUND)
  #define NO_MUSIC_MODE
#endif

#define RGB_DI_PIN F5
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_SLEEP
#define RGBLED_NUM 47
#define RGBLIGHT_EFFECT_KNIGHT_LED_NUM 12
//#define RGBLIGHT_LIMIT_VAL 128
#endif

#endif
