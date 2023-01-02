// Copyright 2022 Dane Skalski (@Daneski13)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef JUNCO_SYNC_ENABLE

// Must be called once before any other sync functions.
// Already always be called within Junco's keyboard_post_init_kb
void junco_sync_init(void);

// Pointer to the user's user_config.raw. If the user wants to sync their own user config,
// set this to the address of user_config.raw in the keyboard_post_init after reading the
// user_config from eeprom `user_config_raw_ptr = &user_config.raw`.
extern uint32_t* user_config_raw_ptr;

// Syncs common settings between the halves (default layer, Magic settings, user config),
// call only on master. True on success, false on failure. Allows syncing of a user's
// custom config (pass in the user_config.raw, pass 0 if not).
bool junco_sync(void);

// Reset/reboot both halves, optionally clearing EEPROM.
// Must be called from both halves (top housekeeping).
//
// needs_reset: is required, will set to false on success.
//
// clear_eeprom: is optional, will be set to false when cleared,
// if NULL or false won't clear EEPROM.
//
// failed: is optional, will be set to true if reseting both halves failed,
// just the master will be reset on the next call
void junco_sync_reset(bool* needs_reset, bool* clear_eeprom, bool* failed);

#    ifdef RGB_MATRIX_ENABLE
// Sync RGB matrix settings between the halves, call only on master.
// Also, ensure reaction on both keypress and key release events.
// Returns true on success, false on failure.
bool junco_sync_rgb(void);
#    endif

#endif
