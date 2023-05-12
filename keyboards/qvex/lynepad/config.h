// Copyright 2023 seflm (@seflm)
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


//Digital joystick (4-way switch + encoder)
#define PIN_JU D4
#define PIN_JD B6
#define PIN_JL D7
#define PIN_JR B4
#define PIN_JC C6

//Thumbwheel
#define PIN_TC D2

//Thumbwheel and joystick encoders
#define ENCODERS_PAD_A { D6, D1 }
#define ENCODERS_PAD_B { B5, D0 }

