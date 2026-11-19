// Copyright 2020 Yaotian Feng / Codetector
// Copyright 2026 Michael Loukeris (@milouk)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

enum snowfox_layers {
    SF_LAYER_WIN,
    SF_LAYER_MAC,
    SF_LAYER_PROFILE1, // profiles 1 to 4 are layers over the base layer
    SF_LAYER_PROFILE2,
    SF_LAYER_PROFILE3,
    SF_LAYER_PROFILE4,
    SF_LAYER_FN_LOCK,
    SF_LAYER_FN,
};

#define SF_PROFILE_COUNT 5 // profile 0 is the base layer alone

enum snowfox_keycodes {
    // Bluetooth host 1 to 3. Tap to connect, hold 3 seconds to pair.
    SF_BT1 = QK_KB_0,
    SF_BT2,
    SF_BT3,
    SF_BATT, // hold to show the battery level on the number row
    SF_FRST, // hold 3 seconds to reset all settings
    SF_PRF0, // profiles 0 to 4
    SF_PRF1,
    SF_PRF2,
    SF_PRF3,
    SF_PRF4,
    SF_FNLK, // lock the F keys on the number row
};

// Settings kept at the start of the keyboard's EEPROM data block,
// followed by the lighting of each profile.
typedef union {
    uint32_t raw;
    struct {
        uint8_t ble_slot : 2; // last Bluetooth host used plus one, 0 for none
        uint8_t sleep : 3;    // sleep on battery, see snowfox_power.c
        uint8_t profile : 3;
        uint8_t switch_mode : 2; // what the switch on the back does, see snowfox.c
        bool    host_is_mac : 1; // last operating system seen over USB
    };
} snowfox_config_t;

#define SF_SWITCH_MODES 3

#define SF_LIGHTING_OFFSET(profile) (sizeof(snowfox_config_t) + (profile) * sizeof(rgb_config_t))

snowfox_config_t snowfox_config_read(void);
void             snowfox_config_write(snowfox_config_t config);

void    snowfox_ble_select(uint8_t host, bool pair);
uint8_t snowfox_profile(void);
uint8_t snowfox_switch_mode(void);
void    snowfox_set_switch_mode(uint8_t mode);
void    snowfox_profile_select(uint8_t profile);
void    snowfox_profile_reset(void);
