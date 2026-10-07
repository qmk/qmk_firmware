// Copyright 2026 Andre Brait (@andrebrait)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdint.h>
#include <stddef.h> // offsetof

#include "nvm_os_detection.h"
#include "util.h"

// Size of the OS detection settings entry in eeprom_core_t, reserved whether or not OS detection is enabled.
#define EECONFIG_OS_DETECTION_SIZE 8

// Dummy struct only used to calculate offsets within the eeprom_core_t entry
typedef struct PACKED {
    uint16_t magic;
    uint8_t  disabled;
    uint8_t  boot_loop_count;
    uint32_t last_reboot_uptime;
} eeprom_os_detection_t;

#if defined(OS_DETECTION_ENABLE) && defined(OS_DETECTION_DEBUG_ENABLE)
// Dummy struct only used to calculate offsets within the debug datablock
typedef struct PACKED {
    uint16_t magic;
    uint8_t  setup_count;
    uint8_t  setup_reason;
    uint16_t setups[OS_DETECTION_STORED_SETUPS];
} eeprom_os_detection_debug_t;

#    define EECONFIG_OS_DETECTION_DEBUG_DATA_SIZE (sizeof(eeprom_os_detection_debug_t))
#else
#    define EECONFIG_OS_DETECTION_DEBUG_DATA_SIZE 0
#endif
