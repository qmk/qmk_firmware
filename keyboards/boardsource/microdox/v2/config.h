// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#define MATRIX_ROW_PINS \
    { F4, D2, C6, B1 }
#define MATRIX_COL_PINS \
    { D4, D7, B3, F7, F6 }
#define MATRIX_ROW_PINS_RIGHT \
    { F5, F7, F6, E6 }
#define MATRIX_COL_PINS_RIGHT \
    { F4, B1, D7, C6, B3 }
#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN D3
#undef RGB_DI_PIN
#define RGB_DI_PIN B5
#ifdef RGBLIGHT_ENABLE
#    undef RGBLED_NUM
#    undef RGBLED_SPLIT
#    define RGBLED_NUM 8
#    define RGBLED_SPLIT { 4, 4 } // underglow only
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#endif
#ifdef RGB_MATRIX_ENABLE
#    define DRIVER_LED_TOTAL 44
#    define RGB_MATRIX_SPLIT { 22, 22 }
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#    define ENABLE_RGB_MATRIX_ALPHAS_MODS
#    define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_BREATHING
#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#    define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#endif
#ifdef ENCODER_ENABLE
#    define ENCODERS_PAD_A { E6 }
#    define ENCODERS_PAD_B { B2 }
#    define ENCODERS_PAD_A_RIGHT { B6 }
#    define ENCODERS_PAD_B_RIGHT { B2 }
#endif
