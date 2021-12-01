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

#include <stdint.h>
#include <string.h>
#include "util.h"
#include "wait.h"
#include "debug.h"
#include "timer.h"
#include "eeprom.h"
#include "flash_spi.h"
#include "spi_master.h"

//-----------------------------------------CHECK-----------------------------------------/
#define SPI_FLASH_TOTAL_SECTOR_COUNT ((SPI_FLASH_SIZE * 1024) / SPI_FLASH_SECTOR_SIZE)
#if (SPI_FLASH_SECTOR_START_COUNT + SPI_FLASH_SECTOR_COUNT) > SPI_FLASH_TOTAL_SECTOR_COUNT
#    pragma message STR(SPI_FLASH_SECTOR_START_COUNT + SPI_FLASH_SECTOR_COUNT) " > " STR(SPI_FLASH_TOTAL_SECTOR_COUNT)
#    error emulated eeprom: (SPI_FLASH_SECTOR_START_COUNT + SPI_FLASH_SECTOR_COUNT) exceeds SPI_FLASH_TOTAL_SECTOR_COUNT
#endif

//-------------------------------------FLASH COMMAND-------------------------------------/
//ID comands
#define     FLASH_CMD_RDID         0x9F    // RDID (Read Identification)
#define     FLASH_CMD_RES          0xAB    // RES (Read Electronic ID)
#define     FLASH_CMD_REMS         0x90    // REMS (Read Electronic & Device ID)

//register comands
#define     FLASH_CMD_WRSR         0x01    // WRSR (Write Status register)
#define     FLASH_CMD_RDSR         0x05    // RDSR (Read Status register)

//READ comands
#define     FLASH_CMD_READ         0x03    // READ (1 x I/O)
#define     FLASH_CMD_FASTREAD     0x0B    // FAST READ (Fast read data)
#define     FLASH_CMD_DREAD        0x3B    // DREAD (1In/2 Out fast read)

//Program comands
#define     FLASH_CMD_WREN         0x06    // WREN (Write Enable)
#define     FLASH_CMD_WRDI         0x04    // WRDI (Write Disable)
#define     FLASH_CMD_PP           0x02    // PP (page program)

//Erase comands
#define     FLASH_CMD_SE           0x20    // SE (Sector Erase)
#define     FLASH_CMD_BE           0xD8    // BE (Block Erase)
#define     FLASH_CMD_CE           0x60    // CE (Chip Erase) hex code: 60 or C7

//Mode setting comands
#define     FLASH_CMD_DP           0xB9    // DP (Deep Power Down)
#define     FLASH_CMD_RDP          0xAB    // RDP (Release form Deep Power Down)

//Status register
#define  STATUS_FLAG_WIP           0x01    // Write in progress bit
#define  STATUS_FLAG_WEL           0x02    // Write enable latch bit

//-------------------------------------PRIVATE MACRO-------------------------------------/
#define DEBUG_SPI_FLASH_OUTPUT

//-----------------------------------PRIVATE FUNCTIONS-----------------------------------/
static bool spi_eeprom_start(void) { return spi_start(SPI_FLASH_SLAVE_SELECT_PIN, SPI_FLASH_LSBFIRST, SPI_FLASH_MODE, SPI_FLASH_CLOCK_DIVISOR); }

static spi_status_t spi_flash_wait_while_busy(int timeout) {
    uint32_t     deadline = timer_read32() + timeout;
    spi_status_t response = SPI_STATUS_SUCCESS;
    uint8_t retval;

    do {
        bool res = spi_eeprom_start();
        if (!res) {
            dprint("failed to start SPI for write-enable\n");
            return SPI_STATUS_ERROR;
        }

        spi_write(FLASH_CMD_RDSR);
        retval = spi_read();
        spi_stop();
        if (timer_read32() >= deadline) {
            response = SPI_STATUS_TIMEOUT;
            break;
        }
    } while (retval & STATUS_FLAG_WIP);

    return response;
}

static spi_status_t spi_flash_write_enable(void) {

    bool res = spi_eeprom_start();
    if (!res) {
        dprint("failed to start SPI for write-enable\n");
        return SPI_STATUS_ERROR;
    }

    spi_write(FLASH_CMD_WREN);

    spi_stop();
    return SPI_STATUS_SUCCESS;
}

static spi_status_t spi_flash_write_disable(void) {

    bool res = spi_eeprom_start();
    if (!res) {
        dprint("failed to start SPI for write-enable\n");
        return SPI_STATUS_ERROR;
    }

    spi_write(FLASH_CMD_WRDI);

    spi_stop();
    return SPI_STATUS_SUCCESS;
}

// read & write data & erase
static spi_status_t spi_flash_transmit(uint8_t cmd, uintptr_t addr, uint8_t *data, uint32_t length) {
    uint8_t buffer[SPI_FLASH_ADDRESS_SIZE + 1];
    spi_status_t response = SPI_STATUS_SUCCESS;

    buffer[0] = cmd;
    for (int i = 0; i < SPI_FLASH_ADDRESS_SIZE; ++i) {
        buffer[SPI_FLASH_ADDRESS_SIZE - i] = addr & 0xFF;
        addr >>= 8;
    }

    bool res = spi_eeprom_start();
    if (!res) {
        dprint("failed to start SPI for write-enable\n");
        return SPI_STATUS_ERROR;
    }

    response = spi_transmit(buffer, sizeof(buffer));

    if ((response == SPI_STATUS_SUCCESS) && (data != NULL)) {
        switch (cmd) {
          case FLASH_CMD_READ:
              response = spi_receive(data, length);
              break;
          case FLASH_CMD_PP:
              response = spi_transmit(data, length);
              break;
          default:
              response = SPI_STATUS_ERROR;
              break;
        }

    }

    spi_stop();

    return response;
}

static spi_status_t spi_flash_erase_sector(uint32_t sector_number, int timeout) {
    spi_status_t response = SPI_STATUS_SUCCESS;

    if (sector_number >= SPI_FLASH_SECTOR_COUNT + SPI_FLASH_SECTOR_START_COUNT) {
        return -1;
    }

    //-------------------------------------------------
    // Wait for the write-in-progress bit to be cleared
    response= spi_flash_wait_while_busy(timeout);
    if (response != SPI_STATUS_SUCCESS) {
        dprint("failed to WIP check\n");
        return response;
    }

    //-------------------------------------------------
    // Enable writes
    response = spi_flash_write_enable();
    if (response != SPI_STATUS_SUCCESS) {
        dprint("failed to start SPI for write-enable\n");
        return response;
    }

    //-------------------------------------------------
    // Erase Sector
    response = spi_flash_transmit((uint8_t)FLASH_CMD_SE, (uintptr_t)(sector_number * SPI_FLASH_SECTOR_SIZE), NULL, 0);
    if (response != SPI_STATUS_SUCCESS) {
        dprint("failed to erase sector\n");
        return response;
    }

    //-------------------------------------------------
    // Wait for the write-in-progress bit to be cleared
    response= spi_flash_wait_while_busy(timeout);
    if (response != SPI_STATUS_SUCCESS) {
        dprint("failed to WIP check\n");
        return response;
    }

    return response;
}

int16_t spi_flash_write_block(const void *buf, void *addr, size_t len) {
    spi_status_t response = SPI_STATUS_SUCCESS;
    uint8_t * read_buf    = (uint8_t *)buf;
    uintptr_t target_addr = (uintptr_t)addr;

    while (len > 0) {
        uintptr_t page_offset  = target_addr % SPI_FLASH_PAGE_SIZE;
        int       write_length = SPI_FLASH_PAGE_SIZE - page_offset;
        if (write_length > len) {
            write_length = len;
        }

        //-------------------------------------------------
        // Wait for the write-in-progress bit to be cleared
        response= spi_flash_wait_while_busy(SPI_FLASH_TIMEOUT);
        if (response != SPI_STATUS_SUCCESS) {
            dprint("failed to WIP check\n");
            return response;
        }

        //-------------------------------------------------
        // Enable writes
        response = spi_flash_write_enable();
        if (response != SPI_STATUS_SUCCESS) {
            dprint("failed to start SPI for write-enable\n");
            return response;
        }

#if defined(CONSOLE_ENABLE) && defined(DEBUG_SPI_FLASH_OUTPUT)
        dprintf("[EEPROM W] 0x%08lX: ", ((uint32_t)(uintptr_t)target_addr));
        for (size_t i = 0; i < write_length; i++) {
            dprintf(" %02X", (int)(uint8_t)(read_buf[i]));
        }
        dprintf("\n");
#endif  // DEBUG_SPI_FLASH_OUTPUT

        //-------------------------------------------------
        // Perform the write
        response = spi_flash_transmit((uint8_t)FLASH_CMD_PP, target_addr, read_buf, write_length);
        if (response != SPI_STATUS_SUCCESS) {
            dprint("failed to erase sector\n");
            return response;
        }

        read_buf += write_length;
        target_addr += write_length;
        len -= write_length;
    }

    //-------------------------------------------------
    // Wait for the write-in-progress bit to be cleared
    response= spi_flash_wait_while_busy(SPI_FLASH_TIMEOUT);
    if (response != SPI_STATUS_SUCCESS) {
      dprint("failed to WIP check\n");
      return response;
    }

    //-------------------------------------------------
    // Disable writes
    response= spi_flash_write_disable();
    if (response != SPI_STATUS_SUCCESS) {
      dprint("failed to start SPI for write-disable\n");
      return response;
    }

    return response;
}

//-----------------------------------EXTERNAL FUNCTIONS-----------------------------------/
FLASH_Status SPI_FLASH_Erase(void) {
#if defined(CONSOLE_ENABLE) && defined(DEBUG_SPI_FLASH_OUTPUT)
    uint32_t start = timer_read32();
#endif

    for (uint8_t idex = 0; idex < SPI_FLASH_SECTOR_COUNT; idex ++) {
        spi_status_t response = SPI_STATUS_SUCCESS;

        response = spi_flash_erase_sector(SPI_FLASH_SECTOR_START_COUNT + idex, SPI_FLASH_TIMEOUT);
        if (response != SPI_STATUS_SUCCESS) {
            dprintf("Erase sector failed! sector addr:[0x%x]\n", idex * SPI_FLASH_SECTOR_SIZE);
            return FLASH_TIMEOUT;
        }
    }

#if defined(CONSOLE_ENABLE) && defined(DEBUG_SPI_FLASH_OUTPUT)
    dprintf("EEPROM erase took %ldms to complete\n", ((long)(timer_read32() - start)));
#endif
    return FLASH_COMPLETE;
}

int16_t SPI_FLASH_ReadBlock(uint8_t *Buffer, const uint8_t *Address, size_t Length) {
    spi_status_t response = SPI_STATUS_SUCCESS;

    //-------------------------------------------------
    // Wait for the write-in-progress bit to be cleared
    response= spi_flash_wait_while_busy(SPI_FLASH_TIMEOUT);
    if (response != SPI_STATUS_SUCCESS) {
        dprint("failed to WIP check\n");
        memset(Buffer, 0, Length);
        return response;
    }

    //-------------------------------------------------
    // Perform read
    response = spi_flash_transmit((uint8_t)FLASH_CMD_READ, (uintptr_t)Address, Buffer, Length);
    if (response != SPI_STATUS_SUCCESS) {
        dprint("failed to erase sector\n");
        memset(Buffer, 0, Length);
        return response;
    }

#if defined(CONSOLE_ENABLE) && defined(DEBUG_SPI_FLASH_OUTPUT)
    dprintf("[EEPROM R] 0x%08lX: ", ((uint32_t)(uintptr_t)Address));
    for (size_t i = 0; i < Length; ++i) {
        dprintf(" %02X", (int)(((uint8_t *)Buffer)[i]));
    }
    dprintf("\n");
#endif  // DEBUG_SPI_FLASH_OUTPUT

    return response;
}

FLASH_Status SPI_FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data) {

    spi_flash_write_block((uint8_t *)&Data, (uint8_t *)Address, 0x02);

    return FLASH_COMPLETE;
}
