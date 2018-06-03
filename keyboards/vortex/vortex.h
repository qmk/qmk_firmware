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

#ifndef VORTEX_H
#define VORTEX_H

#include "quantum.h"

#define OVERRIDE

#if defined(UPDATE_PROTO_POK3R)
    #define VERSION_ADDR    0x2800
    #define FIRMWARE_ADDR   0x2C00
#elif defined(UPDATE_PROTO_CYKB)
    #define VERSION_ADDR    0x3000
    #define FIRMWARE_ADDR   0x3400
#else
    #error "No update protocol"
#endif

#define EE_CONFIG_ADDR  0x0000
#define EE_KEYMAP_ADDR  0x1000

enum extra_keycodes {
    EX_ECHO = SAFE_RANGE,
    EX_DUMP,
    EX_RESET,
};

// util
uint16_t from_leu16(const uint8_t *bytes);
uint32_t from_leu32(const uint8_t *bytes);
void to_leu16(uint8_t *bytes, uint16_t num);
void to_leu32(uint8_t *bytes, uint32_t num);
uint16_t crc16(const uint8_t *ptr, uint32_t size, uint32_t crc);

// ht32
void firmware_reset(uint32_t key);
void flash_erase_page(uint32_t addr);
void flash_write_word(uint32_t addr, uint32_t word);

// eeprom
void spi_rdid(uint8_t *data);
void spi_read(uint32_t addr, uint16_t n, uint8_t *data);
void spi_write(uint32_t addr, uint16_t n, const uint8_t *data);
void spi_erase(uint32_t addr);
void spi_wait_wip(void);
uint16_t spi_crc(uint32_t addr, uint16_t len);

#endif // VORTEX_H
