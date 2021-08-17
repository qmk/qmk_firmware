/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0x06, 0x57, 0x10, 0x3B, 0x9B, 0x10, 0x11, 0x99}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 3 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 11 }

#ifdef TAP_DANCE_ENABLE
#define VIAL_TAP_DANCE_ENTRIES 2
#endif

#ifdef COMBO_ENABLE
#define VIAL_COMBO_ENTRIES 4
#endif
