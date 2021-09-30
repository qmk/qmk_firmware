/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0xEC, 0x4D, 0xF7, 0xEA, 0x89, 0xFD, 0x64, 0x3E}

#define VIAL_UNLOCK_COMBO_ROWS { 1, 3 }
#define VIAL_UNLOCK_COMBO_COLS { 6, 4 }

// features below are intended to reduce size of final firmware
#define DYNAMIC_KEYMAP_LAYER_COUNT 2
#define VIAL_COMBO_ENTRIES 4