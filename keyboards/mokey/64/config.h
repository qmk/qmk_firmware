#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6653 //64
#define PRODUCT_ID      0x5339
#define DEVICE_VER      0x0001
#define MANUFACTURER    RH
#define PRODUCT         Mokey64

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15


#define MATRIX_ROW_PINS { E6, C7, F6, F5, B0 }
#define MATRIX_COL_PINS { B1, B2, B3, F4, F1, F7, D0, D1, D2, D3, D5, D4, D6, D7, B4 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN E2
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 16
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

#define DEBOUNCE 5

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
