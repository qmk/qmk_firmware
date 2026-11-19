// Copyright 2026 Antonio SJ Musumeci (@trapexit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <stdbool.h>
#include "wear_leveling.h"
#include "wear_leveling_internal.h"
#include "flash_spi.h"

// Wear-leveling backing store on the U3 SPI NOR flash. The stock firmware keeps its
// profiles at 0x1000-0x3FFF and a FAT disk from 0x10000, so the store uses whole
// 4 KiB sectors in between. QMK's spi_flash backend erases 64 KiB blocks, which would
// destroy the stock data, hence this sector-erasing backend.
#define SHURA_WL_ADDRESS 0xE000U

_Static_assert((WEAR_LEVELING_BACKING_SIZE % EXTERNAL_FLASH_SECTOR_SIZE) == 0, "Backing store must be whole sectors");
_Static_assert((SHURA_WL_ADDRESS + WEAR_LEVELING_BACKING_SIZE) <= 0x10000U, "Backing store must end below the stock disk");

bool backing_store_init(void) {
    flash_init();
    return true;
}

bool backing_store_unlock(void) {
    return true;
}

bool backing_store_lock(void) {
    return true;
}

bool backing_store_erase(void) {
    for (uint32_t offset = 0; offset < WEAR_LEVELING_BACKING_SIZE; offset += EXTERNAL_FLASH_SECTOR_SIZE) {
        if (flash_erase_sector(SHURA_WL_ADDRESS + offset) != FLASH_STATUS_SUCCESS) {
            return false;
        }
    }
    return true;
}

// Erased NOR reads as ones; wear leveling expects zeros, so values are stored inverted.
bool backing_store_write(uint32_t address, backing_store_int_t value) {
    value = ~value;
    return flash_write_range(SHURA_WL_ADDRESS + address, &value, sizeof(value)) == FLASH_STATUS_SUCCESS;
}

bool backing_store_read(uint32_t address, backing_store_int_t *value) {
    if (flash_read_range(SHURA_WL_ADDRESS + address, value, sizeof(*value)) != FLASH_STATUS_SUCCESS) {
        return false;
    }
    *value = ~*value;
    return true;
}
