// Copyright 2022 Arturo Avila (@ADPenrose)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define TAP_CODE_DELAY 10

/* Audio functionality */
#define AUDIO_PIN C6
#define AUDIO_CLICKY
#define AUDIO_ENABLE_TONE_MULTIPLEXING
#define AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT 10

// The number of LEDs connected
#define RGB_MATRIX_LED_COUNT 27
#define RGB_MATRIX_CENTER { 60, 77 }
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 175
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#ifdef RGB_MATRIX_ENABLE
// RGB Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#endif
