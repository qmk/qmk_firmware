// Copyright 2021 Westberry Technology (ChangZhou) Corp., Ltd
// Copyright 2024 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <string.h>

#include "flash.h"
#include "util.h"
#include "wait.h"
#include "debug.h"
#include "timer.h"
#include "flash_spi.h"
#include "spi_master.h"

/*
    The time-out time of spi flash transmission.
*/
#ifndef EXTERNAL_FLASH_SPI_TIMEOUT
#    define EXTERNAL_FLASH_SPI_TIMEOUT 1000
#endif

/* ID comands */
#define FLASH_CMD_RDID 0x9F /* RDID (Read Identification) */
#define FLASH_CMD_RES 0xAB  /* RES (Read Electronic ID) */
#define FLASH_CMD_REMS 0x90 /* REMS (Read Electronic & Device ID) */

/* register comands */
#define FLASH_CMD_WRSR 0x01 /* WRSR (Write Status register) */
#define FLASH_CMD_RDSR 0x05 /* RDSR (Read Status register) */

/* READ comands */
#define FLASH_CMD_READ 0x03     /* READ (1 x I/O) */
#define FLASH_CMD_FASTREAD 0x0B /* FAST READ (Fast read data) */
#define FLASH_CMD_DREAD 0x3B    /* DREAD (1In/2 Out fast read) */

/* Program comands */
#define FLASH_CMD_WREN 0x06 /* WREN (Write Enable) */
#define FLASH_CMD_WRDI 0x04 /* WRDI (Write Disable) */
#define FLASH_CMD_PP 0x02   /* PP (page program) */

/* Erase comands */
#define FLASH_CMD_SE 0x20 /* SE (Sector Erase) */
#define FLASH_CMD_BE 0xD8 /* BE (Block Erase) */
#define FLASH_CMD_CE 0x60 /* CE (Chip Erase) hex code: 60 or C7 */

/* Mode setting comands */
#define FLASH_CMD_DP 0xB9  /* DP (Deep Power Down) */
#define FLASH_CMD_RDP 0xAB /* RDP (Release from Deep Power Down) */

/* Status register */
#define FLASH_FLAG_WIP 0x01 /* Write in progress bit */
#define FLASH_FLAG_WEL 0x02 /* Write enable latch bit */

// #define DEBUG_FLASH_SPI_OUTPUT

static bool spi_flash_start(void) {
    return spi_start(EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN, EXTERNAL_FLASH_SPI_LSBFIRST, EXTERNAL_FLASH_SPI_MODE, EXTERNAL_FLASH_SPI_CLOCK_DIVISOR);
}

static flash_status_t spi_flash_wait_while_busy_multiplier(int multiplier) {
    flash_status_t response = FLASH_STATUS_SUCCESS;
    uint32_t       deadline = timer_read32() + ((EXTERNAL_FLASH_SPI_TIMEOUT)*multiplier);
    do {
        if (timer_read32() >= deadline) {
            response = FLASH_STATUS_TIMEOUT;
            break;
        }

        response = flash_is_busy();
    } while (response == FLASH_STATUS_BUSY);
    return response;
}

static flash_status_t spi_flash_wait_while_busy(void) {
    return spi_flash_wait_while_busy_multiplier(1);
}

flash_status_t flash_is_busy(void) {
    bool res = spi_flash_start();
    if (!res) {
        dprint("Failed to start SPI! [spi flash wait while busy]\n");
        return FLASH_STATUS_ERROR;
    }

    spi_write(FLASH_CMD_RDSR);
    spi_status_t status = spi_read();
    spi_stop();

    if (status < 0) {
        return status;
    }

    uint8_t sr = (uint8_t)status;
    return (sr & FLASH_FLAG_WIP) ? FLASH_STATUS_BUSY : FLASH_STATUS_SUCCESS;
}

static flash_status_t spi_flash_write_enable(void) {
    bool res = spi_flash_start();
    if (!res) {
        dprint("Failed to start SPI! [spi flash write enable]\n");
        return FLASH_STATUS_ERROR;
    }

    spi_write(FLASH_CMD_WREN);
    spi_stop();

    return FLASH_STATUS_SUCCESS;
}

static flash_status_t spi_flash_write_disable(void) {
    bool res = spi_flash_start();
    if (!res) {
        dprint("Failed to start SPI! [spi flash write disable]\n");
        return FLASH_STATUS_ERROR;
    }

    spi_write(FLASH_CMD_WRDI);
    spi_stop();

    return FLASH_STATUS_SUCCESS;
}

/* This function is used for read transfer, write transfer and erase transfer. */
static flash_status_t spi_flash_transaction(uint8_t cmd, uint32_t addr, uint8_t *data, size_t len) {
    flash_status_t response = FLASH_STATUS_SUCCESS;
    uint8_t        buffer[EXTERNAL_FLASH_ADDRESS_SIZE + 1];

    buffer[0] = cmd;
    for (int i = 0; i < EXTERNAL_FLASH_ADDRESS_SIZE; ++i) {
        buffer[EXTERNAL_FLASH_ADDRESS_SIZE - i] = addr & 0xFF;
        addr >>= 8;
    }

    bool res = spi_flash_start();
    if (!res) {
        dprint("Failed to start SPI! [spi flash transmit]\n");
        return FLASH_STATUS_ERROR;
    }

    response = spi_transmit(buffer, sizeof(buffer));

    if ((!response) && (data != NULL)) {
        switch (cmd) {
            case FLASH_CMD_READ:
                response = spi_receive(data, len);
                break;
            case FLASH_CMD_PP:
                response = spi_transmit(data, len);
                break;
            default:
                response = FLASH_STATUS_ERROR;
                break;
        }
    }

    spi_stop();

    return response;
}

void flash_init(void) {
    spi_init();
}

flash_status_t flash_begin_erase_chip(void) {
    flash_status_t response = FLASH_STATUS_SUCCESS;

    /* Wait for the write-in-progress bit to be cleared. */
    response = spi_flash_wait_while_busy();
    if (response != FLASH_STATUS_SUCCESS) {
        dprint("Failed to check WIP flag! [spi flash erase chip]\n");
        return response;
    }

    /* Enable writes. */
    response = spi_flash_write_enable();
    if (response != FLASH_STATUS_SUCCESS) {
        dprint("Failed to write-enable! [spi flash erase chip]\n");
        return response;
    }

    /* Erase Chip. */
    bool res = spi_flash_start();
    if (!res) {
        dprint("Failed to start SPI! [spi flash erase chip]\n");
        return FLASH_STATUS_ERROR;
    }
    spi_write(FLASH_CMD_CE);
    spi_stop();
    return FLASH_STATUS_SUCCESS;
}

flash_status_t flash_wait_erase_chip(void) {
    flash_status_t response = spi_flash_wait_while_busy_multiplier(250); // Chip erase can take a long time, wait 250x the usual timeout
    if (response != FLASH_STATUS_SUCCESS) {
        dprint("Failed to check WIP flag! [spi flash erase chip]\n");
        return response;
    }
    return response;
}

flash_status_t flash_erase_chip(void) {
    flash_status_t response = flash_begin_erase_chip();
    if (response != FLASH_STATUS_SUCCESS) {
        dprint("Failed to begin erase chip! [spi flash erase chip]\n");
        return response;
    }

    return flash_wait_erase_chip();
}

flash_status_t flash_erase_sector(uint32_t addr) {
    flash_status_t response = FLASH_STATUS_SUCCESS;

    /* Check that the address exceeds the limit. */
    if ((addr + (EXTERNAL_FLASH_SECTOR_SIZE)) >= (EXTERNAL_FLASH_SIZE) || ((addr % (EXTERNAL_FLASH_SECTOR_SIZE)) != 0)) {
        dprintf("Flash erase sector address over limit! [addr:0x%lx]\n", (uint32_t)addr);
        return FLASH_STATUS_ERROR;
    }

    /* Wait for the write-in-progress bit to be cleared. */
    response = spi_flash_wait_while_busy();
    if (response != FLASH_STATUS_SUCCESS) {
        dprint("Failed to check WIP flag! [spi flash erase sector]\n");
        return response;
    }

    /* Enable writes. */
    response = spi_flash_write_enable();
    if (response != FLASH_STATUS_SUCCESS) {
        dprint("Failed to write-enable! [spi flash erase sector]\n");
        return response;
    }

    /* Erase Sector. */
    response = spi_flash_transaction(FLASH_CMD_SE, addr, NULL, 0);
    if (response != FLASH_STATUS_SUCCESS) {
        dprint("Failed to erase sector! [spi flash erase sector]\n");
        return response;
    }

    /* Wait for the write-in-progress bit to be cleared.*/
    response = spi_flash_wait_while_busy();
    if (response != FLASH_STATUS_SUCCESS) {
        dprint("Failed to check WIP flag! [spi flash erase sector]\n");
        return response;
    }

    return response;
}

flash_status_t flash_erase_block(uint32_t addr) {
    flash_status_t response = FLASH_STATUS_SUCCESS;

    /* Check that the address exceeds the limit. */
    if ((addr + (EXTERNAL_FLASH_BLOCK_SIZE)) >= (EXTERNAL_FLASH_SIZE) || ((addr % (EXTERNAL_FLASH_BLOCK_SIZE)) != 0)) {
        dprintf("Flash erase block address over limit! [addr:0x%lx]\n", (uint32_t)addr);
        return FLASH_STATUS_ERROR;
    }

    /* Wait for the write-in-progress bit to be cleared. */
    response = spi_flash_wait_while_busy();
    if (response != FLASH_STATUS_SUCCESS) {
        dprint("Failed to check WIP flag! [spi flash erase block]\n");
        return response;
    }

    /* Enable writes. */
    response = spi_flash_write_enable();
    if (response != FLASH_STATUS_SUCCESS) {
        dprint("Failed to write-enable! [spi flash erase block]\n");
        return response;
    }

    /* Erase Block. */
    response = spi_flash_transaction(FLASH_CMD_BE, addr, NULL, 0);
    if (response != FLASH_STATUS_SUCCESS) {
        dprint("Failed to erase block! [spi flash erase block]\n");
        return response;
    }

    /* Wait for the write-in-progress bit to be cleared.*/
    response = spi_flash_wait_while_busy();
    if (response != FLASH_STATUS_SUCCESS) {
        dprint("Failed to check WIP flag! [spi flash erase block]\n");
        return response;
    }

    return response;
}

flash_status_t flash_read_range(uint32_t addr, void *buf, size_t len) {
    flash_status_t response = FLASH_STATUS_SUCCESS;
    uint8_t       *read_buf = (uint8_t *)buf;

    /* Wait for the write-in-progress bit to be cleared. */
    response = spi_flash_wait_while_busy();
    if (response != FLASH_STATUS_SUCCESS) {
        dprint("Failed to check WIP flag! [spi flash read block]\n");
        memset(read_buf, 0, len);
        return response;
    }

    /* Perform read. */
    response = spi_flash_transaction(FLASH_CMD_READ, addr, read_buf, len);
    if (response != FLASH_STATUS_SUCCESS) {
        dprint("Failed to read block! [spi flash read block]\n");
        memset(read_buf, 0, len);
        return response;
    }

#if defined(CONSOLE_ENABLE) && defined(DEBUG_FLASH_SPI_OUTPUT)
    dprintf("[SPI FLASH R] 0x%08lx: ", addr);
    for (size_t i = 0; i < len; ++i) {
        dprintf(" %02X", (int)(((uint8_t *)read_buf)[i]));
    }
    dprintf("\n");
#endif // DEBUG_FLASH_SPI_OUTPUT

    return response;
}

flash_status_t flash_write_range(uint32_t addr, const void *buf, size_t len) {
    flash_status_t response  = FLASH_STATUS_SUCCESS;
    uint8_t       *write_buf = (uint8_t *)buf;

    while (len > 0) {
        uint32_t page_offset  = addr % EXTERNAL_FLASH_PAGE_SIZE;
        size_t   write_length = EXTERNAL_FLASH_PAGE_SIZE - page_offset;
        if (write_length > len) {
            write_length = len;
        }

        /* Wait for the write-in-progress bit to be cleared. */
        response = spi_flash_wait_while_busy();
        if (response != FLASH_STATUS_SUCCESS) {
            dprint("Failed to check WIP flag! [spi flash write block]\n");
            return response;
        }

        /* Enable writes. */
        response = spi_flash_write_enable();
        if (response != FLASH_STATUS_SUCCESS) {
            dprint("Failed to write-enable! [spi flash write block]\n");
            return response;
        }

#if defined(CONSOLE_ENABLE) && defined(DEBUG_FLASH_SPI_OUTPUT)
        dprintf("[SPI FLASH W] 0x%08lx: ", addr);
        for (size_t i = 0; i < write_length; i++) {
            dprintf(" %02X", (int)(uint8_t)(write_buf[i]));
        }
        dprintf("\n");
#endif // DEBUG_FLASH_SPI_OUTPUT

        /* Perform the write. */
        response = spi_flash_transaction(FLASH_CMD_PP, addr, write_buf, write_length);
        if (response != FLASH_STATUS_SUCCESS) {
            dprint("Failed to write block! [spi flash write block]\n");
            return response;
        }

        write_buf += write_length;
        addr += write_length;
        len -= write_length;
    }

    /* Wait for the write-in-progress bit to be cleared. */
    response = spi_flash_wait_while_busy();
    if (response != FLASH_STATUS_SUCCESS) {
        dprint("Failed to check WIP flag! [spi flash write block]\n");
        return response;
    }

    /* Disable writes. */
    response = spi_flash_write_disable();
    if (response != FLASH_STATUS_SUCCESS) {
        dprint("Failed to write-disable! [spi flash write block]\n");
        return response;
    }

    return response;
}
