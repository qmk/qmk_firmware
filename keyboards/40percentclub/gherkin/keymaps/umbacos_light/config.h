#pragma once

/* Make layout upside down = USB port on left side
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#define MATRIX_ROW_PINS { B6, B2, B3, B1, F7 }
#define MATRIX_COL_PINS { D0, D4, C6, D7, E6, B4 }
*/

#define IGNORE_MOD_TAP_INTERRUPT

#define RGB_DI_PIN F6
#define RGBLED_NUM 6
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

#ifdef BACKLIGHT_LEVELS
#undef BACKLIGHT_LEVELS
#endif
#define BACKLIGHT_LEVELS 3

#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 6
