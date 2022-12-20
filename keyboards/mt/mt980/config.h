#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 9

/* key matrix pins */
#define MATRIX_ROW_PINS { B7, B3, B2, B1, B0, E6, F0, F1, F4, F5, F6, F7 }
#define MATRIX_COL_PINS { D0, D1, D2, D3, D5, D4, D6, D7, B4 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

#define LED_NUM_LOCK_PIN C6
#define LED_CAPS_LOCK_PIN C7
#define LED_SCROLL_LOCK_PIN B5
#define LED_PIN_ON_STATE 0

/* number of backlight levels */
#define BACKLIGHT_PIN B6
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 3
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN E2
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
#define RGBLED_NUM 24
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 185
#endif

/* Place bootmagic key on Esc */
#define BOOTMAGIC_LITE_ROW 5
#define BOOTMAGIC_LITE_COLUMN 0
