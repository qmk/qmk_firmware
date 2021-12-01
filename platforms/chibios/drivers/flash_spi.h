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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//-------------------------------------SPI configuration-------------------------------------/

/*
    The slave select pin of the FLASH.
    This needs to be a normal GPIO pin_t value, such as B14.
*/
#ifndef SPI_FLASH_SLAVE_SELECT_PIN
#    define SPI_FLASH_SLAVE_SELECT_PIN B14
#endif

/*
    Whether or not the SPI communication between the MCU and FLASH should be
    LSB-first.
*/
#ifndef SPI_FLASH_LSBFIRST
#    define SPI_FLASH_LSBFIRST false
#endif

/*
    The SPI mode to communicate with the FLASH.
*/
#ifndef SPI_FLASH_MODE
#    define SPI_FLASH_MODE 0
#endif

/*
    The clock divisor for SPI to ensure that the MCU is within the
    specifications of the FLASH chip. Generally this will be PCLK divided by
    the intended divisor -- check your clock settings and the datasheet of
    your FLASH.
    SPI speed = WB32_MAINCLK / (SPI_FLASH_CLOCK_DIVISOR << 2)
    The default value for WB32_MAINCLK is 72MHz.
*/
#ifndef SPI_FLASH_CLOCK_DIVISOR
#    define SPI_FLASH_CLOCK_DIVISOR 18
#endif

/*
    The time-out time of flash transmission.
*/
#ifndef SPI_FLASH_TIMEOUT
#    define SPI_FLASH_TIMEOUT 1000
#endif

//-----------------------------------SPI flash configuration-----------------------------------/

/*
    Flash address size, as specified in datasheet, in bytes.
*/
#ifndef SPI_FLASH_ADDRESS_SIZE
#    define SPI_FLASH_ADDRESS_SIZE 3
#endif

/*
    The page size in bytes of the FLASH, as specified in the datasheet.
*/
#ifndef SPI_FLASH_PAGE_SIZE
#    define SPI_FLASH_PAGE_SIZE 256
#endif

/*
    The Page count is used to indicate how many pages are used in FLASH.
*/
#ifndef SPI_FLASH_PAGE_COUNT
#    define SPI_FLASH_PAGE_COUNT 8
#endif

/*
    The sector size in bytes of the FLASH, as specified in the datasheet.
*/
#ifndef SPI_FLASH_SECTOR_SIZE
#    define SPI_FLASH_SECTOR_SIZE 4096UL
#endif

/*
    The sector count of the FLASH, the number of Address of the starting sector.
*/
#ifndef SPI_FLASH_SECTOR_START_COUNT
#    define SPI_FLASH_SECTOR_START_COUNT 0
#endif

/*
    The sector count of the FLASH, the number of sectors that need to be used.
*/
#ifndef SPI_FLASH_SECTOR_COUNT
#    define SPI_FLASH_SECTOR_COUNT 1
#endif

/*
    The FLASH size is used to indicate the size of this flash in KB.
*/
#ifndef SPI_FLASH_SIZE
#    define SPI_FLASH_SIZE 8 // KB
#endif

/*
    The total size of the FLASH, in bytes. The FLASH datasheet will usually
    specify this value in kbits, and will require conversion to bytes.
*/
#ifndef SPI_FLASH_BYTE_COUNT
#    define SPI_FLASH_BYTE_COUNT (SPI_FLASH_SECTOR_COUNT * SPI_FLASH_SECTOR_SIZE)
#endif

/*
    The FLASH page base address is used to indicate the start address of using this flash.
*/
#ifndef SPI_FLASH_PAGE_BASE_ADDRESS
#    define SPI_FLASH_PAGE_BASE_ADDRESS (SPI_FLASH_SECTOR_SIZE * SPI_FLASH_SECTOR_START_COUNT)
#endif

typedef enum { FLASH_BUSY = 1, FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_ERROR_OPT, FLASH_COMPLETE, FLASH_TIMEOUT, FLASH_BAD_ADDRESS } FLASH_Status;

FLASH_Status SPI_FLASH_Erase(void);
FLASH_Status SPI_FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);
int16_t SPI_FLASH_ReadBlock(uint8_t *Buffer, const uint8_t *Address, size_t Length);

#ifdef __cplusplus
}
#endif
