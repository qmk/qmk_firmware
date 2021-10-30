#include "config_common.h"


#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    lpad
#define PRODUCT         v1
#define DESCRIPTION     Keyboard

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

/* key matrix pins */
#define MATRIX_ROW_PINS { D2, D3, D4, D5, D6 }
#define MATRIX_COL_PINS { B4, B5, B6, B7 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW


/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE


#define RGB_DI_PIN B0
#define RGBLIGHT_ANIMATIONS

#define RGBLED_NUM 22        //13+9
#define RGBLIGHT_HUE_STEP 4
#define RGBLIGHT_SAT_STEP 4
#define RGBLIGHT_VAL_STEP 4
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LIMIT_VAL 255


//encoder
#define ENCODERS_PAD_B { F0, F4 }
#define ENCODERS_PAD_A { F1, F5 }

#define ENCODER_RESOLUTION 4


#ifdef OLED_DRIVER_ENABLE
  #define OLED_TIMEOUT 400000
#endif

//oled
#if !defined(OLED_FONT_WIDTH)
#    define OLED_FONT_WIDTH 6
#endif

#if !defined(OLED_FONT_HEIGHT)
#    define OLED_FONT_HEIGHT 8
#endif

/* EEPROM for via */
#define DYNAMIC_KEYMAP_LAYER_COUNT 5
