#pragma once

/* matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3
#define MATRIX_ROW_PINS { F5, F4, F1 }
#define MATRIX_COL_PINS { D6, D2, D1 }
#define DIODE_DIRECTION ROW2COL
#define DEVICE_VER      0x0001

#define RGB_DI_PIN E2
#ifdef RGB_DI_PIN
 #define RGBLED_NUM 9
 #define RGBLIGHT_HUE_STEP 8
 #define RGBLIGHT_SAT_STEP 8
 #define RGBLIGHT_VAL_STEP 8
 #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
 #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
 /*== all animations enable ==*/
 #define RGBLIGHT_ANIMATIONS
#endif
