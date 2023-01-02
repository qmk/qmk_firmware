// Copyright 2022 Dane Skalski (@Daneski13)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "rev1.h"

typedef union {
    uint32_t raw;
    struct {
        bool junco_sync_enabled;
    };
} kb_config_t;
// Keyboard level data
extern kb_config_t kb_config;

#ifdef EE_HANDS
// Clear EEPROM but persist handedness
void eeconfig_init_persist_handedness(void);
#endif

#ifdef JUNCO_SYNC_ENABLE
#    include "junco_sync.h"

/* Whether to sync flags */
typedef struct {
    bool reset;
    bool eeprom;
    bool previous_failed;
} kb_needs_reset_t;
// Whether a reboot and/or eeprom clear needs to happen (applies to both sides)
extern kb_needs_reset_t kb_needs_reset;
// Whether the sides need to sync
extern bool kb_needs_sync;
// Whether the sides need to sync the RGB
extern bool kb_needs_rgb_sync;

/* Ability to disable/enable Junco Sync and get status*/

// Disables Junco Sync without the need for recompiling the firmware.
// Will sync across both halves.
void junco_sync_disable(void);

// Enables Junco Sync after it has been disabled by junco_sync_disable.
// Will sync across both halves.
void junco_sync_enable(void);

// Whether or not Junco Sync is currently enabled.
bool is_junco_sync_enabled(void);

#endif
