/* Copyright 2020 Nick Brassel (tzarc)
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

#include <stdint.h>
#include <string.h>

/*
    Note that the implementations of eeprom_XXXX_YYYY on AVR are normally
    provided by avr-libc. The same functions are reimplemented below and are
    rerouted to the external SPI equivalent.

    Seemingly, as this is compiled from within QMK, the object file generated
    during the build overrides the avr-libc implementation during the linking
    stage.

    On other platforms such as ARM, there are no provided implementations, so
    there is nothing to override during linkage.
*/

#include "wait.h"
#include "spi_master.h"
#include "eeprom.h"
#include "eeprom_spi.h"

#define CMD_WREN 6
#define CMD_WRDI 4
#define CMD_RDSR 5
#define CMD_WRSR 1
#define CMD_READ 3
#define CMD_WRITE 2

#define SR_WIP 0x01

// #define DEBUG_EEPROM_OUTPUT

#ifndef EXTERNAL_EEPROM_SPI_TIMEOUT
#    define EXTERNAL_EEPROM_SPI_TIMEOUT 100
#endif

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif  // CONSOLE_ENABLE

static void init_spi_if_required(void) {
    static int done = 0;
    if (!done) {
        spi_init();
        done = 1;
    }
}

static bool spi_eeprom_start(void) { return spi_start(EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN, EXTERNAL_EEPROM_SPI_LSBFIRST, EXTERNAL_EEPROM_SPI_MODE, EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR); }

static spi_status_t spi_eeprom_wait_while_busy(int timeout) {
    uint32_t     deadline = timer_read32() + timeout;
    spi_status_t response;
    do {
        spi_write(CMD_RDSR);
        response = spi_read();
        if (timer_read32() >= deadline) {
            return SPI_STATUS_TIMEOUT;
        }
    } while (response & SR_WIP);
    return SPI_STATUS_SUCCESS;
}

static void spi_eeprom_transmit_address(uintptr_t addr) {
    uint8_t buffer[EXTERNAL_EEPROM_ADDRESS_SIZE];

    for (int i = 0; i < EXTERNAL_EEPROM_ADDRESS_SIZE; ++i) {
        buffer[EXTERNAL_EEPROM_ADDRESS_SIZE - 1 - i] = addr & 0xFF;
        addr >>= 8;
    }

    spi_transmit(buffer, EXTERNAL_EEPROM_ADDRESS_SIZE);
}

//----------------------------------------------------------------------------------------------------------------------

void eeprom_driver_init(void) {}

void eeprom_driver_erase(void) {
#ifdef CONSOLE_ENABLE
    uint32_t start = timer_read32();
#endif

    uint8_t buf[EXTERNAL_EEPROM_PAGE_SIZE];
    memset(buf, 0x00, EXTERNAL_EEPROM_PAGE_SIZE);
    for (uint32_t addr = 0; addr < EXTERNAL_EEPROM_BYTE_COUNT; addr += EXTERNAL_EEPROM_PAGE_SIZE) {
        eeprom_write_block(buf, (void *)(uintptr_t)addr, EXTERNAL_EEPROM_PAGE_SIZE);
    }

#ifdef CONSOLE_ENABLE
    dprintf("EEPROM erase took %ldms to complete\n", ((long)(timer_read32() - start)));
#endif
}

void eeprom_read_block(void *buf, const void *addr, size_t len) {
    init_spi_if_required();

    //-------------------------------------------------
    // Wait for the write-in-progress bit to be cleared
    bool res = spi_eeprom_start();
    if (!res) {
        dprint("failed to start SPI for WIP check\n");
        memset(buf, 0, len);
        return;
    }

    spi_status_t response = spi_eeprom_wait_while_busy(EXTERNAL_EEPROM_SPI_TIMEOUT);
    spi_stop();
    if (response == SPI_STATUS_TIMEOUT) {
        dprint("SPI timeout for WIP check\n");
        memset(buf, 0, len);
        return;
    }

    //-------------------------------------------------
    // Perform read
    res = spi_eeprom_start();
    if (!res) {
        dprint("failed to start SPI for read\n");
        memset(buf, 0, len);
        return;
    }

    spi_write(CMD_READ);
    spi_eeprom_transmit_address((uintptr_t)addr);
    spi_receive(buf, len);

#ifdef DEBUG_EEPROM_OUTPUT
    dprintf("[EEPROM R] 0x%08lX: ", ((uint32_t)(uintptr_t)addr));
    for (size_t i = 0; i < len; ++i) {
        dprintf(" %02X", (int)(((uint8_t *)buf)[i]));
    }
    dprintf("\n");
#endif  // DEBUG_EEPROM_OUTPUT

    spi_stop();
}

void eeprom_write_block(const void *buf, void *addr, size_t len) {
    init_spi_if_required();

    bool      res;
    uint8_t * read_buf    = (uint8_t *)buf;
    uintptr_t target_addr = (uintptr_t)addr;

    while (len > 0) {
        uintptr_t page_offset  = target_addr % EXTERNAL_EEPROM_PAGE_SIZE;
        int       write_length = EXTERNAL_EEPROM_PAGE_SIZE - page_offset;
        if (write_length > len) {
            write_length = len;
        }

        //-------------------------------------------------
        // Wait for the write-in-progress bit to be cleared
        res = spi_eeprom_start();
        if (!res) {
            dprint("failed to start SPI for WIP check\n");
            return;
        }

        spi_status_t response = spi_eeprom_wait_while_busy(EXTERNAL_EEPROM_SPI_TIMEOUT);
        spi_stop();
        if (response == SPI_STATUS_TIMEOUT) {
            dprint("SPI timeout for WIP check\n");
            return;
        }

        //-------------------------------------------------
        // Enable writes
        res = spi_eeprom_start();
        if (!res) {
            dprint("failed to start SPI for write-enable\n");
            return;
        }

        spi_write(CMD_WREN);
        spi_stop();

        //-------------------------------------------------
        // Perform the write
        res = spi_eeprom_start();
        if (!res) {
            dprint("failed to start SPI for write\n");
            return;
        }

#ifdef DEBUG_EEPROM_OUTPUT
        dprintf("[EEPROM W] 0x%08lX: ", ((uint32_t)(uintptr_t)target_addr));
        for (size_t i = 0; i < write_length; i++) {
            dprintf(" %02X", (int)(uint8_t)(read_buf[i]));
        }
        dprintf("\n");
#endif  // DEBUG_EEPROM_OUTPUT

        spi_write(CMD_WRITE);
        spi_eeprom_transmit_address(target_addr);
        spi_transmit(read_buf, write_length);
        spi_stop();

        read_buf += write_length;
        target_addr += write_length;
        len -= write_length;
    }

    //-------------------------------------------------
    // Disable writes
    res = spi_eeprom_start();
    if (!res) {
        dprint("failed to start SPI for write-disable\n");
        return;
    }

    spi_write(CMD_WRDI);
    spi_stop();
}
