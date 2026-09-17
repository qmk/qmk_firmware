// Copyright 2024 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "eeprom.h"
#include "util.h"
#include "via.h"
#include "nvm_via.h"
#include "nvm_eeprom_eeconfig_internal.h"
#include "nvm_eeprom_via_internal.h"

void nvm_via_erase(void) {
    // No-op, nvm_eeconfig_erase() will have already erased EEPROM if necessary.
}

void nvm_via_read_magic(uint8_t *magic0, uint8_t *magic1, uint8_t *magic2) {
    if (magic0) {
        *magic0 = eeprom_read_byte((void *)VIA_EEPROM_MAGIC_ADDR + 0);
    }

    if (magic1) {
        *magic1 = eeprom_read_byte((void *)VIA_EEPROM_MAGIC_ADDR + 1);
    }

    if (magic2) {
        *magic2 = eeprom_read_byte((void *)VIA_EEPROM_MAGIC_ADDR + 2);
    }
}

void nvm_via_update_magic(uint8_t magic0, uint8_t magic1, uint8_t magic2) {
    eeprom_update_byte((void *)VIA_EEPROM_MAGIC_ADDR + 0, magic0);
    eeprom_update_byte((void *)VIA_EEPROM_MAGIC_ADDR + 1, magic1);
    eeprom_update_byte((void *)VIA_EEPROM_MAGIC_ADDR + 2, magic2);
}

uint32_t nvm_via_read_layout_options(void) {
    uint32_t value = 0;
    // Start at the most significant byte
    void *source = (void *)(VIA_EEPROM_LAYOUT_OPTIONS_ADDR);
    for (uint8_t i = 0; i < VIA_EEPROM_LAYOUT_OPTIONS_SIZE; i++) {
        value = value << 8;
        value |= eeprom_read_byte(source);
        source++;
    }
    return value;
}

void nvm_via_update_layout_options(uint32_t val) {
    // Start at the least significant byte
    void *target = (void *)(VIA_EEPROM_LAYOUT_OPTIONS_ADDR + VIA_EEPROM_LAYOUT_OPTIONS_SIZE - 1);
    for (uint8_t i = 0; i < VIA_EEPROM_LAYOUT_OPTIONS_SIZE; i++) {
        eeprom_update_byte(target, val & 0xFF);
        val = val >> 8;
        target--;
    }
}

uint32_t nvm_via_read_custom_config(void *buf, uint32_t offset, uint32_t length) {
#if VIA_EEPROM_CUSTOM_CONFIG_SIZE > 0
    void *ee_start = (void *)(uintptr_t)(VIA_EEPROM_CUSTOM_CONFIG_ADDR + offset);
    void *ee_end   = (void *)(uintptr_t)(VIA_EEPROM_CUSTOM_CONFIG_ADDR + MIN(VIA_EEPROM_CUSTOM_CONFIG_SIZE, offset + length));
    eeprom_read_block(buf, ee_start, ee_end - ee_start);
    return ee_end - ee_start;
#else
    return 0;
#endif
}

uint32_t nvm_via_update_custom_config(const void *buf, uint32_t offset, uint32_t length) {
#if VIA_EEPROM_CUSTOM_CONFIG_SIZE > 0
    void *ee_start = (void *)(uintptr_t)(VIA_EEPROM_CUSTOM_CONFIG_ADDR + offset);
    void *ee_end   = (void *)(uintptr_t)(VIA_EEPROM_CUSTOM_CONFIG_ADDR + MIN(VIA_EEPROM_CUSTOM_CONFIG_SIZE, offset + length));
    eeprom_update_block(buf, ee_start, ee_end - ee_start);
    return ee_end - ee_start;
#else
    return 0;
#endif
}
