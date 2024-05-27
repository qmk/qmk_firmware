// Copyright 2024 mukil (@bukil)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
// Vial support
#define VIAL_KEYBOARD_UID {0x0F, 0xB0, 0xD3, 0xDF, 0x7B, 0x86, 0xA6, 0x00}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 1 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }

/* Encoder Configuration*/
#define ENCODER_DEFAULT_POS 0x3
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
