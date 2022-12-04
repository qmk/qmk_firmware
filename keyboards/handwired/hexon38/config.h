// see https://github.com/pepaslabs/hexon38

#pragma once


/* key matrix pins */
#define MATRIX_ROW_PINS { B0, F0, B2, F4 }
#define MATRIX_COL_PINS { C6, D3, D2, D1, D0, B7, F6, F7, B6, B5, B4, D7 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif
