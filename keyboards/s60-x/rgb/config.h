#ifndef RBG_CONFIG_H
#define RBG_CONFIG_H

#include "../config.h"

#define PRODUCT         S60-X-RGB
#define DESCRIPTION     q.m.k. keyboard firmware for S60-X RGB

/* key matrix pins */
#define MATRIX_ROW_PINS { B5, B4, D7, D6, D4 }
#define MATRIX_COL_PINS { D0, D1, D2, D3, D5, B6, C6, C7, F1, F0, E6, B3, B2, B1, B0 }

/* number of backlight levels */
#define BACKLIGHT_PIN B7
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 3
#endif

/* prevent stuck modifiers */
#define PREVENT_STUCK_MODIFIERS

#define RGB_DI_PIN F6
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 10
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

#endif