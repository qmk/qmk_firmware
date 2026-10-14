// Copyright 2026 Michael Loukeris (@milouk)
// SPDX-License-Identifier: GPL-2.0-or-later

// On-chip EEPROM of the LPC11U2x/3x, through the ROM's IAP calls.
// Only the EEPROM commands are issued here, so this cannot alter flash.

#include <string.h>
#include "ch.h"
#include "hal.h"
#include "eeprom_driver.h"
#include "eeprom_lpc11uxx.h"

#define IAP_ENTRY 0x1FFF1FF1U
#define IAP_CMD_EEPROM_WRITE 61U
#define IAP_CMD_EEPROM_READ 62U
#define IAP_CMD_SUCCESS 0U

#define EEPROM_PAGE_SIZE 64U

// Interrupts are off for the whole of each IAP call (UM10462 20.8.7), about 3 ms for
// a write. QMK writes its defaults a byte at a time, and several hundred such calls in
// a row keep USB from enumerating. Sequential writes are therefore collected and sent
// a page at a time, at the latest FLUSH_DELAY after the last one. Reads see the
// collected bytes, so read-before-write updates do not force a write per byte.
// Call eeprom_lpc11uxx_flush() before a reset to write out anything still pending.
#define FLUSH_DELAY TIME_MS2I(10)

typedef void (*iap_entry_t)(uint32_t[], uint32_t[]);

static uint8_t         pending[EEPROM_PAGE_SIZE];
static uint32_t        pending_addr;
static uint8_t         pending_len;
static virtual_timer_t flush_timer;

// Call with the system locked.
static bool iap_eeprom(uint32_t command_code, uint32_t ee_addr, uint8_t *ram, uint32_t len) {
    uint32_t command[5] = {command_code, ee_addr, (uint32_t)ram, len, CPU_CLOCK / 1000U};
    uint32_t result[4]  = {~IAP_CMD_SUCCESS, 0, 0, 0};

    ((iap_entry_t)IAP_ENTRY)(command, result);

    return result[0] == IAP_CMD_SUCCESS;
}

// Call with the system locked.
static void flush_pending(void) {
    if (pending_len > 0) {
        iap_eeprom(IAP_CMD_EEPROM_WRITE, pending_addr, pending, pending_len);
        pending_len = 0;
    }
}

static void flush_timer_cb(virtual_timer_t *vtp, void *arg) {
    (void)vtp;
    (void)arg;

    chSysLockFromISR();
    flush_pending();
    chSysUnlockFromISR();
}

static size_t clamp_length(uintptr_t offset, size_t len) {
    if (offset >= LPC11UXX_EEPROM_SIZE) {
        return 0;
    }
    if (len > LPC11UXX_EEPROM_SIZE - offset) {
        len = LPC11UXX_EEPROM_SIZE - offset;
    }
    return len;
}

void eeprom_driver_init(void) {
    chVTObjectInit(&flush_timer);
}

void eeprom_driver_erase(void) {
    uint8_t blank[EEPROM_PAGE_SIZE];
    memset(blank, 0xFF, sizeof(blank));

    for (uint32_t addr = 0; addr < LPC11UXX_EEPROM_SIZE; addr += EEPROM_PAGE_SIZE) {
        uint32_t len = LPC11UXX_EEPROM_SIZE - addr < EEPROM_PAGE_SIZE ? LPC11UXX_EEPROM_SIZE - addr : EEPROM_PAGE_SIZE;

        syssts_t sts = chSysGetStatusAndLockX();
        if (addr == 0) {
            pending_len = 0;
        }
        iap_eeprom(IAP_CMD_EEPROM_WRITE, addr, blank, len);
        chSysRestoreStatusX(sts);
    }
}

void eeprom_read_block(void *buf, const void *addr, size_t len) {
    uintptr_t offset = (uintptr_t)addr;
    size_t    usable = clamp_length(offset, len);

    // Bytes outside the EEPROM, or a failed read, come back as erased.
    memset(buf, 0xFF, len);
    if (usable > 0) {
        syssts_t sts = chSysGetStatusAndLockX();
        bool     ok  = iap_eeprom(IAP_CMD_EEPROM_READ, offset, buf, usable);

        // Bytes still waiting to be written take precedence over what is stored.
        uint32_t start = offset > pending_addr ? offset : pending_addr;
        uint32_t end   = offset + usable < pending_addr + pending_len ? offset + usable : pending_addr + pending_len;
        if (ok && start < end) {
            memcpy((uint8_t *)buf + (start - offset), &pending[start - pending_addr], end - start);
        }
        chSysRestoreStatusX(sts);

        if (!ok) {
            memset(buf, 0xFF, len);
        }
    }
}

void eeprom_write_block(const void *buf, void *addr, size_t len) {
    uintptr_t      offset = (uintptr_t)addr;
    const uint8_t *src    = buf;

    len = clamp_length(offset, len);
    if (len == 0) {
        return;
    }

    while (len > 0) {
        syssts_t sts = chSysGetStatusAndLockX();

        // Start a new run when this byte does not follow the pending ones, or opens a new page.
        if (pending_len > 0 && (offset != pending_addr + pending_len || offset % EEPROM_PAGE_SIZE == 0)) {
            flush_pending();
        }
        if (pending_len == 0) {
            pending_addr = offset;
        }

        size_t chunk = EEPROM_PAGE_SIZE - (offset % EEPROM_PAGE_SIZE);
        if (chunk > len) {
            chunk = len;
        }
        memcpy(&pending[pending_len], src, chunk);
        pending_len += chunk;

        chSysRestoreStatusX(sts);

        offset += chunk;
        src += chunk;
        len -= chunk;
    }

    syssts_t sts = chSysGetStatusAndLockX();
    chVTSetI(&flush_timer, FLUSH_DELAY, flush_timer_cb, NULL);
    chSysRestoreStatusX(sts);
}

void eeprom_lpc11uxx_flush(void) {
    syssts_t sts = chSysGetStatusAndLockX();
    chVTResetI(&flush_timer);
    flush_pending();
    chSysRestoreStatusX(sts);
}
