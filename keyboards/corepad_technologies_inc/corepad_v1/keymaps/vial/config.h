// Copyright 2026 CorePad Technologies Inc
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* VIAL_KEYBOARD_UID must be unique per keyboard design. This one was
 * randomly generated for "corepad" - keep it as-is, don't reuse across
 * unrelated keyboard projects.
 */
#define VIAL_KEYBOARD_UID {0xCA, 0x31, 0x3C, 0x73, 0x45, 0xA9, 0x82, 0x29}

/* Hold SW1 + SW3 together (matrix positions 0,0 and 0,2) to unlock Vial's
 * secure features from the Vial GUI.
 */
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 2 }

/* Number of layers available in Vial */
#define DYNAMIC_KEYMAP_LAYER_COUNT 8