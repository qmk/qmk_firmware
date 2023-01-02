// Copyright 2022 Dane Skalski (@Daneski13)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "eeprom.h"

/* Manually Sync VIA Data */
// Size of keymaps in EEPROM
#define KEYMAPS_SIZE (DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2)
// Size of encoders in EEPROM
#define ENCODER_SIZE (DYNAMIC_KEYMAP_LAYER_COUNT * NUM_ENCODERS * 2 * 2)
// Starting address of VIA's non-core data
#define START_ADDR VIA_EEPROM_LAYOUT_OPTIONS_ADDR
// DYNAMIC_KEYMAP_EEPROM_MAX_ADDR is the maximum address that VIA will use for its data,
// including macros. This end address minus the start address + 1 is how large the VIA
// data block will be. I'm roughly copying how this address is calculated by default by
// taking the starting address, adding the custom config size, adding the keymaps size (including
// encoders), and the rest for macros. VIA says up to 1 Kilobyte is usable for macros (despite
// it delegating the entire rest of EEPROM to them). Personally I don't use them so I'm setting
// it to 1/3 of that Kilobyte just in case I choose to in the future. Lower numbers will
// speed up the syncing process. If you have no need for macros, you can set it to 0. Syncing VIA
// takes about 5 seconds at the default speed of 10 packets per second with my settings.
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR (START_ADDR + VIA_EEPROM_CUSTOM_CONFIG_SIZE + KEYMAPS_SIZE + ENCODER_SIZE + 333)
// Ending address of all VIA data (macros included)
#define END_ADDR DYNAMIC_KEYMAP_EEPROM_MAX_ADDR
// How big the VIA data block is
#define VIA_BLOCK_SIZE (END_ADDR - START_ADDR + 1)

// Call within keyboard_post_init_user to initialize the VIA sync RPC
void via_sync_init(void);

// Syncs VIA's data from the master to the slave.
// True when finished, false when still needs to
// send packets and/or retry.
// Call within housekeeping_task_user on the master
// only. VIA sync sends the data in packets of 20 bytes.
bool via_sync(void);
