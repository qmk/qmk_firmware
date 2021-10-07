#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x7BA1
#define PRODUCT_ID      0x6502
#define DEVICE_VER      0x0001
#define MANUFACTURER    MWStudio
#define PRODUCT         MW65

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

/* key matrix pins */
#define MATRIX_ROW_PINS { D0, D1, D2, D3, B7, B0 }
#define MATRIX_COL_PINS { C6, B6, B5, B4, D7, D6, D4, C7, F7, F6, F5, F4, F1, F0, E6 }
#define UNUSED_PINS

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 1

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* prevent stuck modifiers */
#define PREVENT_STUCK_MODIFIERS

#define RGB_DI_PIN B3
#ifdef RGB_DI_PIN
    #define RGBLIGHT_SLEEP

    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
    #define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS

    #define DRIVER_LED_TOTAL 83

    #define RGBLED_NUM 83
    #define RGB_MATRIX_KEYPRESSES

    #define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    #define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
    #define DISABLE_RGB_MATRIX_TYPING_HEATMAP
    #define DISABLE_RGB_MATRIX_DIGITAL_RAIN
    #define DISABLE_RGB_MATRIX_BAND_SAT
    #define DISABLE_RGB_MATRIX_BAND_VAL
    #define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
    #define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
    #define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
    #define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL

    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
#endif

#define ENCODERS_PAD_A { B1 }
#define ENCODERS_PAD_B { B2 }
#endif
