// Copyright 2022 Arturo Avila (@ADPenrose)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* Key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 5

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { D4, D7, E6, B6, B4, B5 }
#define MATRIX_COL_PINS { D3, D2, F5, F6, B2 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/*Rotary encoder - set the resolution fitting your encoder.
Most will need a value of 4. If 1 encoder click results in 2 keycodes sent
increase the value. If you need 2 clicks for 1 keycode, decrease*/
#define ENCODER_RESOLUTION 4
#define ENCODERS_PAD_A { B1 }
#define ENCODERS_PAD_B { B3 }
#define TAP_CODE_DELAY 10

/* Audio functionality */
#define AUDIO_PIN C6
#define AUDIO_CLICKY
#define AUDIO_ENABLE_TONE_MULTIPLEXING
#define AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT 10

// The pin connected to the data pin of the LEDs
#define RGB_DI_PIN F4
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

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
