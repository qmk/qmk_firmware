// Copyright 2022 Sergey Vlasov (@sigprof)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

// Key matrix size.
#define MATRIX_ROWS 1
#define MATRIX_COLS 24

// Key pins (including encoder press switches).
// The NO_PIN entries are reserved for encoder rotation mappings.
#define DIRECT_PINS                                                                                                                \
    {                                                                                                                              \
        { F4, C7, D4, D5, D1, F5, C6, D6, D3, D2, F6, B6, D7, B4, B5, B2, D0, E6, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN } \
    }

// clang-format off

// Encoder pins.
// Encoder numbering (assuming the default board orientation with encoders on
// the top side):
//   0 - left
//   1 - center (with a longer shaft and a larger knob)
//   2 - right
#define ENCODERS_PAD_A { F1, B0, B3 }
#define ENCODERS_PAD_B { F0, B1, B7 }
#define ENCODER_RESOLUTION 4

// Encoder mappings (used for VIA).
#define ENCODERS 3
#define ENCODERS_CW_KEY  { { 22, 0 }, { 18, 0 }, { 20, 0 } }
#define ENCODERS_CCW_KEY { { 23, 0 }, { 19, 0 }, { 21, 0 } }

// clang-format on

// RGB LED parameters.
// This PCB uses a single chain of WS2812-compatible addressable RGB LEDs for
// per-key backlight and underglow.
#define RGB_DI_PIN F7
#define RGBLED_NUM 27
#define RGBLIGHT_LIMIT_VAL 150

// RGB Lighting configuration.  This mode is used by the vendor firmware, and
// can be chosen if the full RGB Matrix support is not desired for some reason.
#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
#endif

// RGB Matrix configuration.
#ifdef RGB_MATRIX_ENABLE
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS RGBLIGHT_LIMIT_VAL

#    define RGB_MATRIX_CENTER \
        { 35, 35 }

#    define RGB_DISABLE_WHEN_USB_SUSPENDED

// This option is required for the TYPING_HEATMAP and DIGITAL_RAIN effects,
// both of which are disabled below, so the common support for those effects is
// disabled too.
#    undef RGB_MATRIX_FRAMEBUFFER_EFFECTS

// This option is required for reactive effects; disabling this option will
// implicitly disable all of them.
#    define RGB_MATRIX_KEYPRESSES

#    define ENABLE_RGB_MATRIX_ALPHAS_MODS
#    define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_BREATHING
#    define ENABLE_RGB_MATRIX_BAND_SAT
#    define ENABLE_RGB_MATRIX_BAND_VAL
#    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#    define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#    define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#    define ENABLE_RGB_MATRIX_CYCLE_ALL
#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#    define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#    define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#    define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#    define ENABLE_RGB_MATRIX_DUAL_BEACON
#    define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#    define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#    define ENABLE_RGB_MATRIX_RAINDROPS
#    define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#    define ENABLE_RGB_MATRIX_HUE_BREATHING
#    define ENABLE_RGB_MATRIX_HUE_PENDULUM
#    define ENABLE_RGB_MATRIX_HUE_WAVE
#    define ENABLE_RGB_MATRIX_PIXEL_RAIN
// The PIXEL_FRACTAL effect does not work properly when the matrix layout is
// different from the physical layout; it also has problems when underglow
// LEDs are present, or when multiple LEDs are associated with the same key.
#    undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL

// Framebuffer effects; can be enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS
// is defined.  Both of these effects currently don't work properly when the
// key matrix does not match the physical layout, so they are disabled.
#    undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
#    undef ENABLE_RGB_MATRIX_DIGITAL_RAIN

// Reactive effects; can be enabled only if at least one of
// RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined.
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#    define ENABLE_RGB_MATRIX_SPLASH
#    define ENABLE_RGB_MATRIX_MULTISPLASH
#    define ENABLE_RGB_MATRIX_SOLID_SPLASH
#    define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

#endif

// Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed.
#define DEBOUNCE 5
