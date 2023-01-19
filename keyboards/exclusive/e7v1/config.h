#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

/* key matrix pins */
#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5 }
#define MATRIX_COL_PINS { B6, D0, D1, D2, D3, D4, D5, D6, D7, C6, C7, F4, F5, F6, F7, F1 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define LED_CAPS_LOCK_PIN F0

/* number of backlight levels */
#define BACKLIGHT_PIN B7
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 6
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN E6
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
#define RGBLED_NUM 20
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif
