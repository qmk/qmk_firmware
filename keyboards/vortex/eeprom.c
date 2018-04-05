/*
 * Copyright (c) 2018 Charlie Waters
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

#include "ch.h"
#include "hal.h"
#include "print.h"

#include "eeconfig.h"
#include "vortex.h"
#include "gd25q_flash.h"

#define EEPROM_SIZE 524288 // 4Mbit = 512KiB

uint8_t tx_data[4];
uint8_t rx_data[4];

void spi_select(void) {
    palClearLine(LINE_SPICS);
}

void spi_deselect(void) {
    palSetLine(LINE_SPICS);
}

void spi_txrx(uint16_t n, const uint8_t *txbuf, uint8_t *rxbuf) {
    if (txbuf) {
        const uint8_t *txptr = txbuf;
        if (rxbuf) {
            uint8_t *rxptr = rxbuf;
            for (uint16_t i = 0; i < n; ++i) {
                *rxptr = spiPolledExchange(&SPID1, *txptr);
                ++txptr;
                ++rxptr;
            }
        } else {
            for (uint16_t i = 0; i < n; ++i) {
                spiPolledExchange(&SPID1, *txptr);
                ++txptr;
            }
        }
    } else {
        if (rxbuf) {
            uint8_t *rxptr = rxbuf;
            for (uint16_t i = 0; i < n; ++i) {
                *rxptr = spiPolledExchange(&SPID1, 0);
                ++rxptr;
            }
        } else {
            for (uint16_t i = 0; i < n; ++i) {
                spiPolledExchange(&SPID1, 0);
            }
        }
    }
}

void spi_rdid(void) {
    tx_data[0] = GD25Q_RDID;
    tx_data[1] = 0;
    tx_data[2] = 0;
    tx_data[3] = 0;

    spi_select();
    spi_txrx(4, tx_data, rx_data);
    spi_deselect();

    printf("%02x %02x %02x\n", rx_data[1], rx_data[2], rx_data[3]);
}

void spi_read(uint32_t addr, uint16_t n, uint8_t *data) {
    tx_data[0] = GD25Q_READ;
    tx_data[1] = (addr >> 16) & 0xFF;
    tx_data[2] = (addr >> 8) & 0xFF;
    tx_data[3] = addr & 0xFF;

    spi_select();
    spi_txrx(4, tx_data, NULL);
    spi_txrx(n, NULL, data);
    spi_deselect();
}


void spi_dump_page(uint32_t addr) {
    const uint16_t size = 64;
    uint8_t buffer[size];
    spi_read(addr, size, buffer);

    for (uint16_t i = 0; i < size;) {
        uint16_t line = i;
        printf("%06x ", addr + i);
        for (; i < line + 8; ++i) {
            printf(" %02x", buffer[i]);
        }
        printf("\n");
    }
}

void spi_dump(void) {
    for (uint32_t a = 0; a < GD24Q40_BYTES; a += 64) {
        spi_dump_page(a);
    }
}

uint8_t eeprom_read_byte(const uint8_t *addr) {

    return 0;
}

void eeprom_write_byte(uint8_t *addr, uint8_t value) {

}

uint16_t eeprom_read_word(const uint16_t *addr) {
    const uint8_t *p = (const uint8_t *)addr;
    return eeprom_read_byte(p) | (eeprom_read_byte(p+1) << 8);
}

uint32_t eeprom_read_dword(const uint32_t *addr) {
    const uint8_t *p = (const uint8_t *)addr;
    return eeprom_read_byte(p) | (eeprom_read_byte(p+1) << 8)
            | (eeprom_read_byte(p+2) << 16) | (eeprom_read_byte(p+3) << 24);
}

void eeprom_read_block(void *buf, const void *addr, uint32_t len) {
    const uint8_t *p = (const uint8_t *)addr;
    uint8_t *dest = (uint8_t *)buf;
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

void eeprom_write_block(const void *buf, void *addr, uint32_t len) {
    uint8_t *p = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        eeprom_write_byte(p++, *src++);
    }
}

void eeprom_update_byte(uint8_t *addr, uint8_t value) {
    eeprom_write_byte(addr, value);
}

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

void eeprom_update_block(const void *buf, void *addr, uint32_t len) {
    uint8_t *p = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        eeprom_write_byte(p++, *src++);
    }
}
