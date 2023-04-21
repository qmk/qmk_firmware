// Copyright 2023 Synth-and-Keys (@Synth-and-Keys)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define NUMBER_OF_ENCODERS 3
#define ENCODERS_PAD_A { B2, A13, A15}
#define ENCODERS_PAD_B { B1, A14, B3}

#define BOOTMAGIC_LITE_ROW 2
#define BOOTMAGIC_LITE_COLUMN 0

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
