#pragma once

#include "config_common.h"

/* key matrix pins */
#define MATRIX_ROW_PINS { F4, F5, F6, F7 }
#define MATRIX_COL_PINS { D1, D0, D4, C6 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#ifndef CONVERT_TO_PROTON_C
#    define LED_NUM_LOCK_PIN B0 // RXLED
#    define LED_CAPS_LOCK_PIN D5 // TXLED
#    define LED_PIN_ON_STATE 0
#endif

/* Underglow options */
#define RGB_DI_PIN B1
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 1
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif
