#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 18

/* key matrix pins */
#define MATRIX_ROW_PINS { C7, C6, B6, B5, B4 }
#define MATRIX_COL_PINS { F6, F5, F4, F1, F0, E6, B0, B1, D5, B2, B3, D0, D1, D2, D4, D6, D7, F7 }

#define LED_CAPS_LOCK_PIN B7
#define LED_PIN_ON_STATE 0

/* number of backlight levels */
#define BACKLIGHT_PIN B7
#define BACKLIGHT_LEVELS 3

#define RGB_DI_PIN D3
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 20
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_EFFECT_KNIGHT_OFFSET 20

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
