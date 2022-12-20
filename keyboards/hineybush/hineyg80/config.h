#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 9

/* key matrix pins */
#define MATRIX_ROW_PINS { B2, B3, D0, B1, D2, D1, D5, D3, D6, D4, B4, D7 }
#define MATRIX_COL_PINS { C7, F7, F6, F5, F4, F1, F0, B7, B0 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW


#define LED_NUM_LOCK_PIN C6
#define LED_CAPS_LOCK_PIN B6
#define LED_SCROLL_LOCK_PIN B5

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

#ifdef RGB_DI_PIN
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif
