#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAB69
#define PRODUCT_ID      0x8585
#define DEVICE_VER      0x0001
#define MANUFACTURER    Valdydesu_
#define PRODUCT         MakrOSU

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 6

/* key matrix pins */
#define MATRIX_ROW_PINS { B6 }
#define MATRIX_COL_PINS { B2, B3, B1, F7, F6, F5}
#define UNUSED_PINS

#define ENCODERS_PAD_A { D1 }
#define ENCODERS_PAD_B { E6 }
#define ENCODER_DIRECTION_FLIP
#define TAP_CODE_DELAY 10 
/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 5
/* number of backlight levels */

#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 0
#endif


/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE



#define DYNAMIC_KEYMAP_LAYER_COUNT 4

// EEPROM usage


#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif
