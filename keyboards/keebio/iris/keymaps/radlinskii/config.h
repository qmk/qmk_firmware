// Copyright 2022 Ignacy Radliński (@radlinskii)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// #define USE_I2C
#define EE_HANDS

#define TAPPING_TOGGLE 1 // tap just once for TT() to toggle the layer
#define TAPPING_TERM 200
#define IGNORE_MOD_TAP_INTERRUPT

#define RGBLIGHT_LAYERS

#define RGBLIGHT_DEFAULT_HUE 85
#define RGBLIGHT_DEFAULT_SAT 255

#undef RGBLIGHT_DEFAULT_MODE
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_STATIC_LIGHT

#undef RGBLIGHT_EFFECT_BREATHING // fading in and out
#undef RGBLIGHT_EFFECT_RAINBOW_MOOD // rainbow all keys at the same time
#undef RGBLIGHT_EFFECT_RAINBOW_SWIRL // rainbow top bottom
#undef RGBLIGHT_EFFECT_SNAKE
#undef RGBLIGHT_EFFECT_KNIGHT
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#undef RGBLIGHT_EFFECT_RGB_TEST // red -> green -> blue
#undef RGBLIGHT_EFFECT_ALTERNATING // blinking
#undef RGBLIGHT_EFFECT_TWINKLE // randomly fading in and out single keys

#define MOUSEKEY_DELAY 20
#define MOUSEKEY_INTERVAL 20
#define MOUSEKEY_MAX_SPEED 5
#define MOUSEKEY_TIME_TO_MAX 40
#define MOUSEKEY_WHEEL_MAX_SPEED 10
