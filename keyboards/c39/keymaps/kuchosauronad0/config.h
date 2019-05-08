#pragma once

/* ws2812 RGB LED 
#undef RGB_DI_PIN
#define RGB_DI_PIN D0
#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 4     // Number of LEDs
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

#undef RGBLED_NUM
#define RGBLED_NUM 10
*/

/* USB Device descriptor parameter */
//#define VENDOR_ID       0xCA17
//#define PRODUCT_ID      0xCA39
//#define DEVICE_VER      0x0001
//#define MANUFACTURER    Maple Computing
//#define PRODUCT         C39
//#define DESCRIPTION     A compact 39 key keyboard

/* key matrix size */
//#define MATRIX_ROWS 3
//#define MATRIX_COLS 13

//#define MATRIX_ROW_PINS { D1, B4, B5 }
//#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2, B6, D7, E6, C6, D2, D3 }

/* COL2ROW or ROW2COL */
//#define DIODE_DIRECTION COL2ROW


// firmware size optimization: https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/ and https://github.com/qmk/qmk_firmware/issues/3224
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
// more size optimization
#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT

// Leader Key timeout
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 250
