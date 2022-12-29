// Copyright 2022 Giuseppe Iannello (@giannello)
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

#define GPIO_INPUT_PIN_DELAY (NUC123_HCLK / 6 / 1000000L)

#define DIP_SWITCH_PINS { D0, D1, A12, A13, A14 }
