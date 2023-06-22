// Copyright 2022 Nick Lopez <github@glowingmonkey.org>
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

#define BLUEFRUIT_LE_RST_PIN D4
#define BLUEFRUIT_LE_CS_PIN B4
#define BLUEFRUIT_LE_IRQ_PIN E6
