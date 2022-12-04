#pragma once


/* key matrix pins */
#define MATRIX_ROW_PINS { F7, B1, B3, B2, B6 }
#define MATRIX_COL_PINS { B4, E6, D7, C6, D4, D0 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* eliminate lag on space cadet mods */
#define PERMISSIVE_HOLD

/* setup lighting */
#define RGB_DI_PIN B5
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 30
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
