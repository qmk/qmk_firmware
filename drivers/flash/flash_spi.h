/*
Copyright (C) 2021 Westberry Technology (ChangZhou) Corp., Ltd

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* All the following default configurations are based on MX25L4006E Nor FLASH. */

/*
    The slave select pin of the FLASH.
    This needs to be a normal GPIO pin_t value, such as B14.
*/
#ifndef EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN
#    error "No chip select pin defined -- missing EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN"
#endif

/*
    The clock divisor for SPI to ensure that the MCU is within the
    specifications of the FLASH chip. Generally this will be PCLK divided by
    the intended divisor -- check your clock settings and the datasheet of
    your FLASH.
*/
#ifndef EXTERNAL_FLASH_SPI_CLOCK_DIVISOR
#    ifdef __AVR__
#        define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR 4
#    else
#        define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR 8
#    endif
#endif

/*
    The SPI mode to communicate with the FLASH.
*/
#ifndef EXTERNAL_FLASH_SPI_MODE
#    define EXTERNAL_FLASH_SPI_MODE 0
#endif

/*
    Whether or not the SPI communication between the MCU and FLASH should be
    LSB-first.
*/
#ifndef EXTERNAL_FLASH_SPI_LSBFIRST
#    define EXTERNAL_FLASH_SPI_LSBFIRST false
#endif

/*
    The Flash address size in bytes, as specified in datasheet.
*/
#ifndef EXTERNAL_FLASH_ADDRESS_SIZE
#    define EXTERNAL_FLASH_ADDRESS_SIZE 3
#endif

/*
    The page size of the FLASH in bytes, as specified in the datasheet.
*/
#ifndef EXTERNAL_FLASH_PAGE_SIZE
#    define EXTERNAL_FLASH_PAGE_SIZE 256
#endif

/*
    The sector size of the FLASH in bytes, as specified in the datasheet.
*/
#ifndef EXTERNAL_FLASH_SECTOR_SIZE
#    define EXTERNAL_FLASH_SECTOR_SIZE (4 * 1024L)
#endif

/*
    The block size of the FLASH in bytes, as specified in the datasheet.
*/
#ifndef EXTERNAL_FLASH_BLOCK_SIZE
#    define EXTERNAL_FLASH_BLOCK_SIZE (64 * 1024L)
#endif

/*
    The total size of the FLASH in bytes, as specified in the datasheet.
*/
#ifndef EXTERNAL_FLASH_SIZE
#    define EXTERNAL_FLASH_SIZE (512 * 1024L)
#endif

/*
    The block count of the FLASH, calculated by total FLASH size and block size.
*/
#define EXTERNAL_FLASH_BLOCK_COUNT ((EXTERNAL_FLASH_SIZE) / (EXTERNAL_FLASH_BLOCK_SIZE))

/*
    The sector count of the FLASH, calculated by total FLASH size and sector size.
*/
#define EXTERNAL_FLASH_SECTOR_COUNT ((EXTERNAL_FLASH_SIZE) / (EXTERNAL_FLASH_SECTOR_SIZE))

/*
    The page count of the FLASH, calculated by total FLASH size and page size.
*/
#define EXTERNAL_FLASH_PAGE_COUNT ((EXTERNAL_FLASH_SIZE) / (EXTERNAL_FLASH_PAGE_SIZE))

typedef int16_t flash_status_t;

#define FLASH_STATUS_SUCCESS (0)
#define FLASH_STATUS_ERROR (-1)
#define FLASH_STATUS_TIMEOUT (-2)
#define FLASH_STATUS_BAD_ADDRESS (-3)

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void flash_init(void);

flash_status_t flash_erase_chip(void);

flash_status_t flash_erase_block(uint32_t addr);

flash_status_t flash_erase_sector(uint32_t addr);

flash_status_t flash_read_block(uint32_t addr, void *buf, size_t len);

flash_status_t flash_write_block(uint32_t addr, const void *buf, size_t len);

#ifdef __cplusplus
}
#endif
