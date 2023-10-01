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

#define VIAL_KEYBOARD_UID {0xFD, 0XC4, 0xE0, 0x12, 0x93, 0x1C, 0x2B, 0x9A}
#define VIAL_UNLOCK_COMBO_ROWS { 0,0 }
#define VIAL_UNLOCK_COMBO_COLS { 0,1 }


#define RGB_DI_PIN D0
#define RGBLED_NUM 6
#define RGBLIGHT_LAYERS

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define ENCODERS_PAD_A { B5, B4}
#define ENCODERS_PAD_B { B6, B2}
#define ENCODER_RESOLUTION 2

#define MIDI_BASIC

