// see https://github.com/pepaslabs/hexon38

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    pepaslabs
#define PRODUCT         hexon38
#define DESCRIPTION     "https://github.com/pepaslabs/hexon38"

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

/* key matrix pins */
#define MATRIX_ROW_PINS { B0, F0, B2, F4 }
#define MATRIX_COL_PINS { C6, D3, D2, D1, D0, B7, F6, F7, B6, B5, B4, D7 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* number of backlight levels */

#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 0
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* prevent stuck modifiers */
//#define PREVENT_STUCK_MODIFIERS


#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

// /* https://docs.qmk.fm/#/feature_advanced_keycodes */
// #define PERMISSIVE_HOLD
// #define IGNORE_MOD_TAP_INTERRUPT
// #define TAPPING_FORCE_HOLD

// hrmm, when I return false from process_record_user(), QMK seems to wait for TAPPING_TERM before I see my debug messages printed.
//#define TAPPING_TERM 1000

// maybe if I explicitly disable these I can avoid that?
//#undef TAP_DANCE_ENABLE
//#undef KEY_LOCK_ENABLE
//#undef AUDIO_ENABLE
//#undef AUDIO_CLICKY
// nope :(

#endif

