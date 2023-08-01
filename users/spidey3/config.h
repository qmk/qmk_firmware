// Copyright 2022 Joshua Diamond josh@windowoffire.com (@spidey3)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define LED_DISABLE_WHEN_USB_SUSPENDED
#define RGB_DISABLE_WHEN_USB_SUSPENDED

#ifdef RGBLIGHT_ENABLE

#    define RGBLIGHT_LAYERS
#    define RGBLIGHT_MAX_LAYERS 18
#    define RGBLIGHT_LAYER_BLINK
#    define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#    define RGBLIGHT_STARTUP_ANIMATION

#    undef RGBLIGHT_EFFECT_CHRISTMAS
#    undef RGBLIGHT_EFFECT_ALTERNATING

#    define RGBLIGHT_DEFAULT_HUE 213
#    define RGBLIGHT_DEFAULT_SAT UINT8_MAX
#    define RGBLIGHT_DEFAULT_VAL RGBLIGHT_LIMIT_VAL / 2

#    if defined(RGBLIGHT_EFFECT_TWINKLE)
#        define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_TWINKLE
#    elif defined(RGBLIGHT_EFFECT_RAINBOW_MOOD)
#        define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_MOOD
#    else
#        define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_STATIC_LIGHT
#    endif

#endif

#define UNICODE_SELECTED_MODES UNICODE_MODE_MACOS, UNICODE_MODE_LINUX, UNICODE_MODE_WINCOMPOSE, UNICODE_MODE_EMACS

#define SPI_DEBUG_SCAN_RATE

#undef MANUFACTURER
#define MANUFACTURER "Window of Fire"

// Some keyboards enable BACKLIGHT_CAPS_LOCK without checking if backlight is enabled.
// Undef as appropriate to avoid compiler warnings in that case.
#ifndef BACKLIGHT_ENABLE
#undef BACKLIGHT_CAPS_LOCK
#endif
