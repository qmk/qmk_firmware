// Copyright 2022 Will Winder (@winder)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VENDOR_ID       0xCEE2
#define PRODUCT_ID      0x0003
#define DEVICE_VER      0x0004
#define MANUFACTURER    vitvlkv
#define PRODUCT         Avalanche

#define MATRIX_ROWS 10
#define MATRIX_COLS 7

#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
#define MATRIX_COL_PINS { F5, F6, F7, B1, B3, B2, B6 }

#define DIODE_DIRECTION COL2ROW

#define SOFT_SERIAL_PIN D2


#define ENCODERS_PAD_A { B5 }
#define ENCODERS_PAD_B { F4 }
#define ENCODER_RESOLUTION 2

#ifdef RGBLIGHT_ENABLE
#    define RGB_DI_PIN D3
#    define RGBLED_NUM 64
#    define RGBLED_SPLIT { 32, 32 }
#    define RGBLIGHT_SPLIT
#    define RGBLIGHT_LIMIT_VAL 100 // LED Brightness, high power draw may exceed the USB limitations of 0.6A and cause a crash.    
#    define RGBLIGHT_HUE_STEP  10    
#    define RGBLIGHT_SAT_STEP  17    
#    define RGBLIGHT_VAL_STEP  17    

#    define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL+2

#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_CHRISTMAS


// RGB LED Conversion macro from physical array to electric array. This results in better looking animated effects.    
#    define LED_LAYOUT( \
      /* LED matrix */ \
      L01, L02, L03, L04, L05, L06,                        L011, L012, L013, L014, L015, L016, \
      L11, L12, L13, L14, L15, L16,                        L111, L112, L113, L114, L115, L116, \
 L20, L21, L22, L23, L24, L25, L26,                        L211, L212, L213, L214, L215, L216, L217, \
      L31, L32, L33, L34, L35, L36, L37, L38,   L39, L310, L311, L312, L313, L314, L315, L316, \
                     L44, L45, L46, L47, L48,   L49, L410, L411, L412, L413 )\
  { \
    /* left half - electrical wiring order */ \
    L47,L48,L38,L37,L36,L26,L16,L06,L05,L15,L25,L35,L46,L45,L34,L24,L14,L04,L03,L13,L23,L33,L44,L32,L22,L12,L02,L01,L11,L21,L31,L20, \
    /* right half - electrical wiring order */ \
    L410,L49,L39,L310,L311,L211,L111,L011,L012,L112,L212,L312,L411,L412,L313,L213,L113,L013,L014,L114,L214,L314,L413,L315,L215,L115,L015,L016,L116,L216,L316,L217 \
  }
#    define RGBLIGHT_LED_MAP LED_LAYOUT( \
    /* animation order. */ \
      4,  8, 12, 17, 22, 27,                   40, 45, 50, 54, 58, 62, \
      3,  7, 11, 16, 21, 26,                   39, 44, 49, 53, 57, 61, \
  0,  2,  6, 10, 15, 20, 25,                   38, 43, 48, 52, 56, 60, 63, \
      1,  5,  9, 14, 19, 24, 29, 31,   33, 35, 37, 42, 47, 51, 55, 59, \
                 13, 18, 23, 28, 30,   32, 34, 36, 41, 46 )
#endif

#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X64
#    define OLED_TIMEOUT 30000
#endif
