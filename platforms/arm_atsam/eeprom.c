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
#include "debug.h"
#include "samd51j18a.h"
#include "core_cm4.h"
#include "component/nvmctrl.h"

#ifndef EEPROM_SIZE
#    include "eeconfig.h"
#    define EEPROM_SIZE (((EECONFIG_SIZE + 3) / 4) * 4)  // based off eeconfig's current usage, aligned to 4-byte sizes, to deal with LTO
#endif

#ifndef MAX
#    define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#endif

#ifndef BUSY_RETRIES
#    define BUSY_RETRIES 10000
#endif

// #define DEBUG_EEPROM_OUTPUT

/*
 * Debug print utils
 */
#if defined(DEBUG_EEPROM_OUTPUT)
#    define eeprom_printf(fmt, ...) xprintf(fmt, ##__VA_ARGS__);
#else /* NO_DEBUG */
#    define eeprom_printf(fmt, ...)
#endif /* NO_DEBUG */

__attribute__((aligned(4))) static uint8_t buffer[EEPROM_SIZE] = {0};
volatile uint8_t *                         SmartEEPROM8        = (uint8_t *)SEEPROM_ADDR;

static inline bool eeprom_is_busy(void) {
    int timeout = BUSY_RETRIES;
    while (NVMCTRL->SEESTAT.bit.BUSY && timeout-- > 0)
        ;

    return NVMCTRL->SEESTAT.bit.BUSY;
}

static uint32_t get_virtual_eeprom_size(void) {
    // clang-format off
    static const uint32_t VIRTUAL_EEPROM_MAP[11][8] = {
    /*          4    8    16    32    64    128    256    512 */
    /* 0*/ {   0,    0,    0,    0,    0,     0,     0,     0 },
    /* 1*/ { 512, 1024, 2048, 4096, 4096,  4096,  4096,  4096 },
    /* 2*/ { 512, 1024, 2048, 4096, 8192,  8192,  8192,  8192 },
    /* 3*/ { 512, 1024, 2048, 4096, 8192, 16384, 16384, 16384 },
    /* 4*/ { 512, 1024, 2048, 4096, 8192, 16384, 16384, 16384 },
    /* 5*/ { 512, 1024, 2048, 4096, 8192, 16384, 32768, 32768 },
    /* 6*/ { 512, 1024, 2048, 4096, 8192, 16384, 32768, 32768 },
    /* 7*/ { 512, 1024, 2048, 4096, 8192, 16384, 32768, 32768 },
    /* 8*/ { 512, 1024, 2048, 4096, 8192, 16384, 32768, 32768 },
    /* 9*/ { 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536 },
    /*10*/ { 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536 },
    };
    // clang-format on

    static uint32_t virtual_eeprom_size = UINT32_MAX;
    if (virtual_eeprom_size == UINT32_MAX) {
        virtual_eeprom_size = VIRTUAL_EEPROM_MAP[NVMCTRL->SEESTAT.bit.PSZ][NVMCTRL->SEESTAT.bit.SBLK];
    }
    // eeprom_printf("get_virtual_eeprom_size:: %d:%d:%d\n", NVMCTRL->SEESTAT.bit.PSZ, NVMCTRL->SEESTAT.bit.SBLK, virtual_eeprom_size);
    return virtual_eeprom_size;
}

uint8_t eeprom_read_byte(const uint8_t *addr) {
    uintptr_t offset = (uintptr_t)addr;
    if (offset >= MAX(EEPROM_SIZE, get_virtual_eeprom_size())) {
        eeprom_printf("eeprom_read_byte:: out of bounds\n");
        return 0x0;
    }

    if (get_virtual_eeprom_size() == 0) {
        return buffer[offset];
    }

    if (eeprom_is_busy()) {
        eeprom_printf("eeprom_write_byte:: timeout\n");
        return 0x0;
    }

    return SmartEEPROM8[offset];
}

void eeprom_write_byte(uint8_t *addr, uint8_t value) {
    uintptr_t offset = (uintptr_t)addr;
    if (offset >= MAX(EEPROM_SIZE, get_virtual_eeprom_size())) {
        eeprom_printf("eeprom_write_byte:: out of bounds\n");
        return;
    }

    if (get_virtual_eeprom_size() == 0) {
        buffer[offset] = value;
        return;
    }

    if (eeprom_is_busy()) {
        eeprom_printf("eeprom_write_byte:: timeout\n");
        return;
    }

    SmartEEPROM8[offset] = value;
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
