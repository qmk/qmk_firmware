#pragma once

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Set power consumption to work with mobile devices */
#define USB_MAX_POWER_CONSUMPTION 100

/* key matrix pins */
#define MATRIX_ROW_PINS { D0, D1, D2, D3, D5 }
#define MATRIX_COL_PINS { F0, F1, E6, C7, C6, B6, D4, B1, B2, B5, B4, D7, D6, B3 }

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN F7
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 10
#define RGBLIGHT_HUE_STEP 12
#define RGBLIGHT_SAT_STEP 12
#define RGBLIGHT_VAL_STEP 12
#endif
