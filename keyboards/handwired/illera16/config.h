// Copyright 2023 y (@villeramassana)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//Vial 


#define WS2812_DI_PIN D0
#define RGBLED_NUM 6
#define RGBLIGHT_LAYERS

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define ENCODERS_PAD_A { B5, B4}
#define ENCODERS_PAD_B { B6, B2}
#define ENCODER_RESOLUTION 2

#define MIDI_BASIC

