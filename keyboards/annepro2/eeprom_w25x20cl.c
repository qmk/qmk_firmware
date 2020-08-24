/* Copyright 2020 Nick Brassel (tzarc) and tech2077
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
#include "eeprom_w25x20cl.h"

#define CMD_WREN 0x06u
#define CMD_WRDI 0x04u
#define CMD_RDSR 0x05u
#define CMD_WRSR 0x01u
#define CMD_READ 0x03u
#define CMD_WRITE 0x02u
#define CMD_SECTOR_ERASE 0x20u

#define SR_WIP     0x01u

// #define DEBUG_EEPROM_OUTPUT

#ifndef EXTERNAL_EEPROM_SPI_TIMEOUT
#    define EXTERNAL_EEPROM_SPI_TIMEOUT 100
#endif

#if defined(CONSOLE_ENABLE) && defined(DEBUG_EEPROM_OUTPUT)
#    include "timer.h"
#    include "debug.h"
#endif  // CONSOLE_ENABLE

bool spi_eeprom_start(void) {
    return spi_start(EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN, EXTERNAL_EEPROM_SPI_LSBFIRST, EXTERNAL_EEPROM_SPI_MODE, EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR);
}

static spi_status_t spi_eeprom_wait_while_busy(int timeout) {
    uint32_t     deadline = timer_read32() + timeout;
    spi_status_t response;
    spi_write(CMD_RDSR);
    do {
        response = spi_read();
        if (timer_read32() >= deadline) {
            return SPI_STATUS_TIMEOUT;
        }
    } while ((uint16_t)response & SR_WIP);
    return SPI_STATUS_SUCCESS;
}
//----------------------------------------------------------------------------------------------------------------------

void eeprom_erase(uint32_t addr) {
#if defined(CONSOLE_ENABLE) && defined(DEBUG_EEPROM_OUTPUT)
    uint32_t start = timer_read32();
#endif

    spi_eeprom_start();
    spi_write(CMD_WREN);
    spi_stop();

    spi_eeprom_start();
    spi_write(CMD_SECTOR_ERASE);
    spi_write((uint8_t)((addr & 0xFF0000u) >> 16u));
    spi_write((uint8_t)((addr & 0x00FF00u) >> 8u));
    spi_write((uint8_t)((addr & 0x0000FFu)));
    spi_stop();

    spi_eeprom_start();
    spi_status_t response = spi_eeprom_wait_while_busy(10000);
    spi_stop();
    if (response == SPI_STATUS_TIMEOUT) {
        dprint("SPI timeout for WIP check\n");
        return;
    }

#if defined(CONSOLE_ENABLE) && defined(DEBUG_EEPROM_OUTPUT)
    dprintf("EEPROM erase took %ldms to complete\n", ((long)(timer_read32() - start)));
#endif
}

void eeprom_read(void *buf, uint32_t addr, size_t len) {
    //-------------------------------------------------
    // Wait for the write-in-progress bit to be cleared
    bool res = spi_eeprom_start();
    if (!res) {
        dprint("failed to start SPI for WIP check\n");
        spi_stop();
        return;
    }

    spi_status_t response = spi_eeprom_wait_while_busy(EXTERNAL_EEPROM_SPI_TIMEOUT);
    spi_stop();
    if (response == SPI_STATUS_TIMEOUT) {
        dprint("SPI timeout for WIP check\n");
        spi_stop();
        return;
    }

    //-------------------------------------------------
    // Perform read
    res = spi_eeprom_start();
    if (!res) {
        dprint("failed to start SPI for read\n");
        spi_stop();
        return;
    }

    spi_write(CMD_READ);
    spi_write((uint8_t)((addr & 0xFF0000u) >> 16u));
    spi_write((uint8_t)((addr & 0x00FF00u) >> 8u));
    spi_write((uint8_t)((addr & 0x0000FFu)));
    spi_receive(buf, len);
    spi_stop();

#if defined(CONSOLE_ENABLE) && defined(DEBUG_EEPROM_OUTPUT)
    dprintf("[EEPROM R] 0x%08lX: ", (addr));
    for (size_t i = 0; i < len; ++i) {
        dprintf(" %02X", (int)(((uint8_t *)buf)[i]));
    }
    dprintf("\n");
#endif  // DEBUG_EEPROM_OUTPUT

}

void eeprom_write(const void *buf, uint32_t addr, size_t len) {
    eeprom_erase(addr);

    //-------------------------------------------------
    // Enable writes
    bool res = spi_eeprom_start();
    if (!res) {
        dprint("failed to start SPI for write-enable\n");
        spi_stop();
        return;
    }

    spi_write(CMD_WREN);
    spi_stop();

    wait_us(1);

    //-------------------------------------------------
    // Perform the write
    res = spi_eeprom_start();
    if (!res) {
        dprint("failed to start SPI for write\n");
        spi_stop();
        return;
    }

#if defined(CONSOLE_ENABLE) && defined(DEBUG_EEPROM_OUTPUT)
    dprintf("[EEPROM W] 0x%08lX: ", ((uint32_t)(uintptr_t)addr));
    for (size_t i = 0; i < len; i++) {
        dprintf(" %02X", (int)(uint8_t)(buf[i]));
    }
    dprintf("\n");
#endif  // DEBUG_EEPROM_OUTPUT

    spi_write(CMD_WRITE);
    spi_write((uint8_t)((addr & 0xFF0000u) >> 16u));
    spi_write((uint8_t)((addr & 0x00FF00u) >> 8u));
    spi_write((uint8_t)((addr & 0x0000FFu)));
    spi_transmit(buf, len);
    spi_stop();

    res = spi_eeprom_start();
    if (!res) {
        dprint("failed to start SPI for status\n");
        spi_stop();
        return;
    }
    spi_status_t response = spi_eeprom_wait_while_busy(EXTERNAL_EEPROM_SPI_TIMEOUT);
    spi_stop();
    if (response == SPI_STATUS_TIMEOUT) {
        dprint("SPI timeout for WIP check\n");
        return;
    }
}
