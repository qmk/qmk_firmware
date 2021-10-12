/* Copyright 2017 Fred Sundvik
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "eeprom.h"
#include "samd51j18a.h"

#ifndef EEPROM_SIZE
#    include "eeconfig.h"
#    define EEPROM_SIZE (((EECONFIG_SIZE + 3) / 4) * 4)  // based off eeconfig's current usage, aligned to 4-byte sizes, to deal with LTO
#endif

__attribute__((aligned(4))) static uint8_t buffer[EEPROM_SIZE];
volatile uint8_t *smart_eeprom = (uint8_t *) SEEPROM_ADDR;

bool smart_eeprom_enabled(void) {
    return NVMCTRL->SEESTAT.bit.PSZ > 0 && NVMCTRL->SEESTAT.bit.SBLK > 0;
}

bool wait_for_eeprom_ready(void) {
    int timeout = 10000;
    while (NVMCTRL->SEESTAT.bit.BUSY && timeout > 0) {
        timeout -= 1;
    };
    return !NVMCTRL->SEESTAT.bit.BUSY;
}

uint8_t eeprom_read_byte(const uint8_t *addr) {
    uintptr_t offset = (uintptr_t)addr;
    if (offset >= EEPROM_SIZE) {
        return 0;
    }

    if (!smart_eeprom_enabled()) {
        return buffer[offset];
    }

    wait_for_eeprom_ready();
    return smart_eeprom[offset];
}

void eeprom_write_byte(uint8_t *addr, uint8_t value) {
    uintptr_t offset = (uintptr_t)addr;
    if (offset >= EEPROM_SIZE) {
        return;
    }

    if (!smart_eeprom_enabled()) {
        buffer[offset] = value;
        return;
    }

    if (wait_for_eeprom_ready()) {
        smart_eeprom[offset] = value;
    }
}

uint16_t eeprom_read_word(const uint16_t *addr) {
    const uint8_t *p = (const uint8_t *)addr;
    return eeprom_read_byte(p) | (eeprom_read_byte(p + 1) << 8);
}

uint32_t eeprom_read_dword(const uint32_t *addr) {
    const uint8_t *p = (const uint8_t *)addr;
    return eeprom_read_byte(p) | (eeprom_read_byte(p + 1) << 8) | (eeprom_read_byte(p + 2) << 16) | (eeprom_read_byte(p + 3) << 24);
}

void eeprom_read_block(void *buf, const void *addr, size_t len) {
    const uint8_t *p    = (const uint8_t *)addr;
    uint8_t *      dest = (uint8_t *)buf;
    while (len--) {
        *dest++ = eeprom_read_byte(p++);
    }
}

void eeprom_write_word(uint16_t *addr, uint16_t value) {
    uint8_t *p = (uint8_t *)addr;
    eeprom_write_byte(p++, value);
    eeprom_write_byte(p, value >> 8);
}

void eeprom_write_dword(uint32_t *addr, uint32_t value) {
    uint8_t *p = (uint8_t *)addr;
    eeprom_write_byte(p++, value);
    eeprom_write_byte(p++, value >> 8);
    eeprom_write_byte(p++, value >> 16);
    eeprom_write_byte(p, value >> 24);
}

void eeprom_write_block(const void *buf, void *addr, size_t len) {
    uint8_t *      p   = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        eeprom_write_byte(p++, *src++);
    }
}

void eeprom_update_byte(uint8_t *addr, uint8_t value) { eeprom_write_byte(addr, value); }

void eeprom_update_word(uint16_t *addr, uint16_t value) {
    uint8_t *p = (uint8_t *)addr;
    eeprom_write_byte(p++, value);
    eeprom_write_byte(p, value >> 8);
}

void eeprom_update_dword(uint32_t *addr, uint32_t value) {
    uint8_t *p = (uint8_t *)addr;
    eeprom_write_byte(p++, value);
    eeprom_write_byte(p++, value >> 8);
    eeprom_write_byte(p++, value >> 16);
    eeprom_write_byte(p, value >> 24);
}

void eeprom_update_block(const void *buf, void *addr, size_t len) {
    uint8_t *      p   = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        eeprom_write_byte(p++, *src++);
    }
}
