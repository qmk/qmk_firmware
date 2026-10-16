// Copyright 2026 Andre Brait (@andrebrait)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "eeprom.h"
#include "nvm_os_detection.h"
#include "nvm_eeprom_eeconfig_internal.h"

// Change whenever eeprom_os_detection_t changes, so stale data is discarded.
#define EECONFIG_OS_DETECTION_MAGIC_NUMBER 0x4F54
#define EECONFIG_OS_DETECTION_FIELD(type, field) (type *)(EECONFIG_OS_DETECTION + offsetof(eeprom_os_detection_t, field))
#define EECONFIG_OS_DETECTION_MAGIC EECONFIG_OS_DETECTION_FIELD(uint16_t, magic)
#define EECONFIG_OS_DETECTION_DISABLED EECONFIG_OS_DETECTION_FIELD(uint8_t, disabled)
#define EECONFIG_OS_DETECTION_BOOT_LOOP_COUNT EECONFIG_OS_DETECTION_FIELD(uint8_t, boot_loop_count)
#define EECONFIG_OS_DETECTION_LAST_REBOOT_UPTIME EECONFIG_OS_DETECTION_FIELD(uint32_t, last_reboot_uptime)

#ifdef OS_DETECTION_DEBUG_ENABLE
// Change whenever eeprom_os_detection_debug_t changes, so stale data is discarded.
#    define EECONFIG_OS_DETECTION_DEBUG_MAGIC_NUMBER 0x4F45
#    define EECONFIG_OS_DETECTION_DEBUG_FIELD(type, field) (type *)(EECONFIG_OS_DETECTION_DEBUG_DATABLOCK + offsetof(eeprom_os_detection_debug_t, field))
#    define EECONFIG_OS_DETECTION_DEBUG_MAGIC EECONFIG_OS_DETECTION_DEBUG_FIELD(uint16_t, magic)
#    define EECONFIG_OS_DETECTION_SETUP_COUNT EECONFIG_OS_DETECTION_DEBUG_FIELD(uint8_t, setup_count)
#    define EECONFIG_OS_DETECTION_SETUP_REASON EECONFIG_OS_DETECTION_DEBUG_FIELD(uint8_t, setup_reason)
#    define EECONFIG_OS_DETECTION_SETUPS EECONFIG_OS_DETECTION_DEBUG_FIELD(uint16_t, setups)

// The datablock may hold data from other features after a firmware update, so check its magic before trusting it.
static bool nvm_os_detection_debug_is_valid(void) {
    return eeprom_read_word(EECONFIG_OS_DETECTION_DEBUG_MAGIC) == EECONFIG_OS_DETECTION_DEBUG_MAGIC_NUMBER;
}

static void nvm_os_detection_debug_erase(void) {
    // Write the magic last, so an interrupted erase leaves the datablock invalid.
    eeprom_update_word(EECONFIG_OS_DETECTION_DEBUG_MAGIC, 0);
    eeprom_update_byte(EECONFIG_OS_DETECTION_SETUP_COUNT, 0);
    eeprom_update_byte(EECONFIG_OS_DETECTION_SETUP_REASON, 0);
    eeprom_update_word(EECONFIG_OS_DETECTION_DEBUG_MAGIC, EECONFIG_OS_DETECTION_DEBUG_MAGIC_NUMBER);
}
#endif // OS_DETECTION_DEBUG_ENABLE

// The entry may hold data from older firmware, whose eeconfig magic is unchanged, so check its own magic before trusting it.
static bool nvm_os_detection_is_valid(void) {
    return eeprom_read_word(EECONFIG_OS_DETECTION_MAGIC) == EECONFIG_OS_DETECTION_MAGIC_NUMBER;
}

static void nvm_os_detection_settings_erase(void) {
    // Write the magic last, so an interrupted erase leaves the entry invalid.
    eeprom_update_word(EECONFIG_OS_DETECTION_MAGIC, 0);
    eeprom_update_byte(EECONFIG_OS_DETECTION_DISABLED, 0);
    eeprom_update_byte(EECONFIG_OS_DETECTION_BOOT_LOOP_COUNT, 0);
    eeprom_update_dword(EECONFIG_OS_DETECTION_LAST_REBOOT_UPTIME, 0);
    eeprom_update_word(EECONFIG_OS_DETECTION_MAGIC, EECONFIG_OS_DETECTION_MAGIC_NUMBER);
}

static void nvm_os_detection_prepare(void) {
    if (!nvm_os_detection_is_valid()) {
        nvm_os_detection_settings_erase();
    }
}

void nvm_os_detection_erase(void) {
    nvm_os_detection_settings_erase();
#ifdef OS_DETECTION_DEBUG_ENABLE
    nvm_os_detection_debug_erase();
#endif // OS_DETECTION_DEBUG_ENABLE
}

bool nvm_os_detection_read_disabled(void) {
    return nvm_os_detection_is_valid() && eeprom_read_byte(EECONFIG_OS_DETECTION_DISABLED) != 0;
}

void nvm_os_detection_update_disabled(bool disabled) {
    nvm_os_detection_prepare();
    eeprom_update_byte(EECONFIG_OS_DETECTION_DISABLED, disabled);
}

#ifdef OS_DETECTION_BOOT_LOOP_GUARD
void nvm_os_detection_read_boot_loop_guard(uint8_t *count, uint32_t *last_reboot_uptime) {
    if (!nvm_os_detection_is_valid()) {
        *count              = 0;
        *last_reboot_uptime = 0;
        return;
    }
    *count              = eeprom_read_byte(EECONFIG_OS_DETECTION_BOOT_LOOP_COUNT);
    *last_reboot_uptime = eeprom_read_dword(EECONFIG_OS_DETECTION_LAST_REBOOT_UPTIME);
}

void nvm_os_detection_update_boot_loop_guard(uint8_t count, uint32_t last_reboot_uptime) {
    nvm_os_detection_prepare();
    eeprom_update_byte(EECONFIG_OS_DETECTION_BOOT_LOOP_COUNT, count);
    eeprom_update_dword(EECONFIG_OS_DETECTION_LAST_REBOOT_UPTIME, last_reboot_uptime);
}
#endif // OS_DETECTION_BOOT_LOOP_GUARD

#ifdef OS_DETECTION_DEBUG_ENABLE
uint8_t nvm_os_detection_read_setup_count(void) {
    if (!nvm_os_detection_debug_is_valid()) {
        return 0;
    }
    uint8_t count = eeprom_read_byte(EECONFIG_OS_DETECTION_SETUP_COUNT);
    return count > OS_DETECTION_STORED_SETUPS ? 0 : count;
}

uint8_t nvm_os_detection_read_setup_reason(void) {
    return eeprom_read_byte(EECONFIG_OS_DETECTION_SETUP_REASON);
}

uint16_t nvm_os_detection_read_setup(uint8_t index) {
    return index < OS_DETECTION_STORED_SETUPS ? eeprom_read_word(EECONFIG_OS_DETECTION_SETUPS + index) : 0;
}

void nvm_os_detection_update_setups(const uint16_t *setups, uint8_t count, uint8_t reason) {
    if (!nvm_os_detection_debug_is_valid()) {
        nvm_os_detection_debug_erase();
    }
    if (count > OS_DETECTION_STORED_SETUPS) {
        count = OS_DETECTION_STORED_SETUPS;
    }
    // Write the count last, so an interrupted update reads as an empty capture.
    eeprom_update_byte(EECONFIG_OS_DETECTION_SETUP_COUNT, 0);
    eeprom_update_byte(EECONFIG_OS_DETECTION_SETUP_REASON, reason);
    for (uint8_t i = 0; i < count; ++i) {
        eeprom_update_word(EECONFIG_OS_DETECTION_SETUPS + i, setups[i]);
    }
    eeprom_update_byte(EECONFIG_OS_DETECTION_SETUP_COUNT, count);
}
#endif // OS_DETECTION_DEBUG_ENABLE
