// Copyright 2022 Thunderbird2086 (Thunderbird2086)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xF1F1
#define PRODUCT_ID      0x0315
#define DEVICE_VER      0x0001
#define MANUFACTURER    dztech
#define PRODUCT         YD3xn15mx

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 5

/* pin-out */
#define DIRECT_PINS { \
     { F4    , C7    , D4    , D5    , D1     }, \
     { F5    , C6    , D6    , D3    , D2     }, \
     { F6    , B6    , D7    , B4    , B5     }, \
     { NO_PIN, NO_PIN, B2    , NO_PIN, NO_PIN }, \
     { NO_PIN, B0    , NO_PIN, B1    , NO_PIN }, \
     { NO_PIN, E6    , NO_PIN, D0    , NO_PIN }, \
     { F1    , F0    , NO_PIN, B3    , B7     }, \
}

#define UNUSED_PINS E2

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#define RGB_DI_PIN F7

#ifdef RGBLIGHT_ENABLE
#   define RGBLED_NUM 27

#define LED_LAYOUT( \
        L05, L04, L03, L02, L01, L00, \
          L06, L15, L16, L17, L18, \
          L07, L14, L13, L12, L19, \
          L08, L09, L10, L11, L20, \
          \
          L22,                L21, \
          L23,                L26, \
          L24,                L25  \
          )\
    {\
        L00, L01, L02, L03, L04, \
        L05, L06, L07, L08, L09, \
        L10, L11, L12, L13, L14, \
        L15, L16, L17, L18, L19, \
        L20, L21, L22, L23, L24, \
        L25, L26  \
    }

#   define RGBLIGHT_LED_MAP LED_LAYOUT( \
        5,  4,  3,  2,  1,  0, \
          6, 11, 12, 17, 18, \
          7, 10, 13, 16, 19, \
          8,  9, 14, 15, 20, \
          \
          22,            21, \
          23,            26, \
          24,            25  \
          )
#endif

#ifdef RGB_MATRIX_ENABLE
#   define RGBLED_NUM 27
#   define DRIVER_LED_TOTAL RGBLED_NUM

#   define RGB_MATRIX_KEYPRESS
#   define RGB_MATRIX_RELEASES
#   define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#   define RGB_MATRIX_HUE_STEP 8
#   define RGB_MATRIX_SAT_STEP 8
#   define RGB_MATRIX_VAL_STEP 8
#   define RGB_MATRIX_SPD_STEP 10

#   define ENABLE_RGB_MATRIX_ALPHAS_MODS
#   define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#   define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#   define ENABLE_RGB_MATRIX_BREATHING
#   define ENABLE_RGB_MATRIX_BAND_SAT
#   define ENABLE_RGB_MATRIX_BAND_VAL
#   define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#   define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#   define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#   define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#   define ENABLE_RGB_MATRIX_CYCLE_ALL
#   define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#   define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#   define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#   define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#   define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#   define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#   define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#   define ENABLE_RGB_MATRIX_DUAL_BEACON
#   define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#   define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#   define ENABLE_RGB_MATRIX_RAINDROPS
#   define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#   define ENABLE_RGB_MATRIX_HUE_BREATHING
#   define ENABLE_RGB_MATRIX_HUE_PENDULUM
#   define ENABLE_RGB_MATRIX_HUE_WAVE
#   define ENABLE_RGB_MATRIX_PIXEL_RAIN
#   define ENABLE_RGB_MATRIX_PIXEL_FLOW
#   define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
//
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
#   define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#   define ENABLE_RGB_MATRIX_DIGITAL_RAIN
//
#   define RGB_MATRIX_KEYPRESSES
// enabled only of RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#   define ENABLE_RGB_MATRIX_SPLASH
#   define ENABLE_RGB_MATRIX_MULTISPLASH
#   define ENABLE_RGB_MATRIX_SOLID_SPLASH
#   define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif 
