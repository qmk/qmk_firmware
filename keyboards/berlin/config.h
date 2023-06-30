// Copyright 2023 Paul Vierkorn (@9hax)
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

#define DIP_SWITCH_PINS { D9, E6 }

#define SLIDER_PIN_A A2
#define SLIDER_PIN_B A1
#define SLIDER_PIN_C A0
