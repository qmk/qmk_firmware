#pragma once

/* Make layout upside down = USB port on left side
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#define MATRIX_ROW_PINS { B6, B2, B3, B1, F7 }
#define MATRIX_COL_PINS { D0, D4, C6, D7, E6, B4 }
*/

#define IGNORE_MOD_TAP_INTERRUPT

#define MUSIC_MAP

#define RGB_DI_PIN D3
#define RGBLED_NUM 20
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

//#define BACKLIGHT_BREATHING
//#define BREATHING_PERIOD 6
//#define BACKLIGHT_LEVELS 6
