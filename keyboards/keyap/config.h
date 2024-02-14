// Copyright 2024 y (@y)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#define ENCODER_MAP_KEY_DELAY 10
#define ENCODERS_PAD_A \
    { D1 }
#define ENCODERS_PAD_B \
    { D0 }
#define ENCODERS_PAD_C \
    { D4 }
#define ENCODER_RESOLUTION 4
/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
// #define NO_ACTION_ONESHOT
