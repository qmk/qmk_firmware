// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Wear Leveling EEPROM Emulation
 */

// #define   4096                              // Number of bytes "exposed" to the rest of QMK and denotes the size of the usable EEPROM.
// #define WEAR_LEVELING_BACKING_SIZE (WEAR_LEVELING_LOGICAL_SIZE * 2)  // Number of bytes used by the wear-leveling algorithm for its underlying storage, and needs to be a multiple of the logical size.
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
// #define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2
#define USB_POLLING_INTERVAL_MS 3
#define NO_ACTION_ONESHOT
#define NO_MUSIC_MODE
// #define LAYER_STATE_3BIT
#define RGBLIGHT_LAYERS
// #define USB_MAX_POWER_CONSUMPTION 100
