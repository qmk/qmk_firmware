// Copyright 2023 Thomas Haukland (@tompi)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define WS2812_PIO_USE_PIO1 // Force the usage of PIO1 peripheral, by default the WS2812 implementation uses the PIO0 peripheral
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB


// Pick good defaults for enabling homerow modifiers
#define TAPPING_TERM 230

#define WS2812_DI_PIN GP16 // The pin connected to the data pin of the LEDs
#define RGBLIGHT_LED_COUNT 1                     // The number of LEDs connected

// Max number of threads
#define MAX_DEFERRED_EXECUTORS 32

// #define DEBUG_MATRIX_SCAN_RATE

// Avoid very bright default LED
#define RGBLIGHT_DEFAULT_HUE 128 // Sets the default hue value, if none has been set
#define RGBLIGHT_DEFAULT_SAT 128 // Sets the default saturation value, if none has been set
#define RGBLIGHT_DEFAULT_VAL 32 // Sets the default brightness value, if none has been set
                                
