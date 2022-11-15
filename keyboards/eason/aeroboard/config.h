// Copyright 2022 Eason
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

#define MATRIX_COL_PINS { B9, B8, B7, B6, B5, B4, B3, B11, A15, A10, A9, B14, B13, B12, A5, A4 }
#define MATRIX_ROW_PINS { B10, B1, B0, A7, A6 }
#define DIODE_DIRECTION COL2ROW

#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE
#define RGB_DI_PIN B15
#define RGBLED_NUM 20
#define WS2812_SPI SPID2
#define WS2812_SPI_MOSI_PAL_MODE 5



/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */
/*
 * Force NKRO
 *
 * Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
 * state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in the
 * makefile for this to work.)
 *
 * If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
 * until the next keyboard reset.
 *
 * NKRO may prevent your keystrokes from being detected in the BIOS, but it is
 * fully operational during normal computer usage.
 *
 * For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
 * or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
 * bootmagic, NKRO mode will always be enabled until it is toggled again during a
 * power-up.
 *
 */
#define FORCE_NKRO


/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
