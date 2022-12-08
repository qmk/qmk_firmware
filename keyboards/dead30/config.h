// Copyright 2022 Julien Marbach (@Julien Marbach)
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



/*
 * Rotary Encoder Support
 * Rot0 Jaune Orange -> 5 6 -> F7 F6
 * Rot1 Rouge Brun -> 7 8 -> F5 F4
 */
#define ENCODERS_PAD_A { F7, F5 }
#define ENCODERS_PAD_B { F6, F4 }
#define ENCODER_RESOLUTION 4
#define ENCODER_RESOLUTIONS { 4, 1 }
//#define TAP_CODE_DELAY 10
