// Copyright 2026 Andre Brait (@andrebrait)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdbool.h>
#include "eeprom.h"
#include "nvm_os_detection.h"
#include "nvm_eeprom_eeconfig_internal.h"

// Change whenever eeprom_os_detection_t changes, so stale data is discarded.
#define EECONFIG_OS_DETECTION_MAGIC_NUMBER 0x4F53
#define EECONFIG_OS_DETECTION_MAGIC (uint16_t *)(EECONFIG_OS_DETECTION + offsetof(eeprom_os_detection_t, magic))

#ifdef OS_DETECTION_DEBUG_ENABLE
// Change whenever eeprom_os_detection_debug_t changes, so stale data is discarded.
#    define EECONFIG_OS_DETECTION_DEBUG_MAGIC_NUMBER 0x4F44
#    define EECONFIG_OS_DETECTION_DEBUG_MAGIC (uint16_t *)(EECONFIG_OS_DETECTION_DEBUG_DATABLOCK + offsetof(eeprom_os_detection_debug_t, magic))
#    define EECONFIG_OS_DETECTION_SETUP_COUNT (uint8_t *)(EECONFIG_OS_DETECTION_DEBUG_DATABLOCK + offsetof(eeprom_os_detection_debug_t, setup_count))
#    define EECONFIG_OS_DETECTION_SETUPS (uint16_t *)(EECONFIG_OS_DETECTION_DEBUG_DATABLOCK + offsetof(eeprom_os_detection_debug_t, setups))

// The datablock may hold data from other features after a firmware update, so check its magic before trusting it.
static bool nvm_os_detection_debug_is_valid(void) {
    return eeprom_read_word(EECONFIG_OS_DETECTION_DEBUG_MAGIC) == EECONFIG_OS_DETECTION_DEBUG_MAGIC_NUMBER;
}

static void nvm_os_detection_debug_erase(void) {
    // Write the magic last, so an interrupted erase leaves the datablock invalid.
    eeprom_update_word(EECONFIG_OS_DETECTION_DEBUG_MAGIC, 0);
    eeprom_update_byte(EECONFIG_OS_DETECTION_SETUP_COUNT, 0);
    eeprom_update_word(EECONFIG_OS_DETECTION_DEBUG_MAGIC, EECONFIG_OS_DETECTION_DEBUG_MAGIC_NUMBER);
}
#endif // OS_DETECTION_DEBUG_ENABLE

void nvm_os_detection_erase(void) {
    eeprom_update_word(EECONFIG_OS_DETECTION_MAGIC, EECONFIG_OS_DETECTION_MAGIC_NUMBER);
#ifdef OS_DETECTION_DEBUG_ENABLE
    nvm_os_detection_debug_erase();
#endif // OS_DETECTION_DEBUG_ENABLE
}

#ifdef OS_DETECTION_DEBUG_ENABLE
uint8_t nvm_os_detection_read_setup_count(void) {
    if (!nvm_os_detection_debug_is_valid()) {
        return 0;
    }
    uint8_t count = eeprom_read_byte(EECONFIG_OS_DETECTION_SETUP_COUNT);
    return count > OS_DETECTION_STORED_SETUPS ? 0 : count;
}

uint16_t nvm_os_detection_read_setup(uint8_t index) {
    return index < OS_DETECTION_STORED_SETUPS ? eeprom_read_word(EECONFIG_OS_DETECTION_SETUPS + index) : 0;
}

void nvm_os_detection_update_setups(const uint16_t *setups, uint8_t count) {
    if (!nvm_os_detection_debug_is_valid()) {
        nvm_os_detection_debug_erase();
    }
    if (count > OS_DETECTION_STORED_SETUPS) {
        count = OS_DETECTION_STORED_SETUPS;
    }
    // Write the count last, so an interrupted update reads as an empty capture.
    eeprom_update_byte(EECONFIG_OS_DETECTION_SETUP_COUNT, 0);
    for (uint8_t i = 0; i < count; ++i) {
        eeprom_update_word(EECONFIG_OS_DETECTION_SETUPS + i, setups[i]);
    }
    eeprom_update_byte(EECONFIG_OS_DETECTION_SETUP_COUNT, count);
}
#endif // OS_DETECTION_DEBUG_ENABLE
