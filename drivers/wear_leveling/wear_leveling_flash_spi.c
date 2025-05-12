// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <stdbool.h>
#include <hal.h>
#include "util.h"
#include "timer.h"
#include "wear_leveling.h"
#include "wear_leveling_flash_spi_config.h"
#include "wear_leveling_internal.h"

#ifndef WEAR_LEVELING_EXTERNAL_FLASH_BULK_COUNT
#    define WEAR_LEVELING_EXTERNAL_FLASH_BULK_COUNT 32
#endif // WEAR_LEVELING_EXTERNAL_FLASH_BULK_COUNT

bool backing_store_init(void) {
    bs_dprintf("Init\n");
    flash_init();
    return true;
}

bool backing_store_unlock(void) {
    bs_dprintf("Unlock\n");
    // No-op -- handled by the flash driver as it is.
    return true;
}

bool backing_store_erase(void) {
#ifdef WEAR_LEVELING_DEBUG_OUTPUT
    uint32_t start = timer_read32();
#endif

    bool ret = true;
    for (int i = 0; i < (WEAR_LEVELING_EXTERNAL_FLASH_BLOCK_COUNT); ++i) {
        flash_status_t status = flash_erase_block(((WEAR_LEVELING_EXTERNAL_FLASH_BLOCK_OFFSET) + i) * (EXTERNAL_FLASH_BLOCK_SIZE));
        if (status != FLASH_STATUS_SUCCESS) {
            ret = false;
            break;
        }
    }

    bs_dprintf("Backing store erase took %ldms to complete\n", ((long)(timer_read32() - start)));
    return ret;
}

bool backing_store_write(uint32_t address, backing_store_int_t value) {
    return backing_store_write_bulk(address, &value, 1);
}

bool backing_store_lock(void) {
    bs_dprintf("Lock  \n");
    // No-op -- handled by the flash driver as it is.
    return true;
}

bool backing_store_read(uint32_t address, backing_store_int_t *value) {
    return backing_store_read_bulk(address, value, 1);
}

bool backing_store_read_bulk(uint32_t address, backing_store_int_t *values, size_t item_count) {
    bs_dprintf("Read  ");
    uint32_t       offset = (WEAR_LEVELING_EXTERNAL_FLASH_BLOCK_OFFSET) * (EXTERNAL_FLASH_BLOCK_SIZE) + address;
    flash_status_t status = flash_read_range(offset, values, sizeof(backing_store_int_t) * item_count);
    if (status == FLASH_STATUS_SUCCESS) {
        for (size_t i = 0; i < item_count; ++i) {
            values[i] = ~values[i];
        }
        wl_dump(offset, values, sizeof(backing_store_int_t) * item_count);
    }
    return status == FLASH_STATUS_SUCCESS;
}

bool backing_store_write_bulk(uint32_t address, backing_store_int_t *values, size_t item_count) {
    uint32_t            offset = (WEAR_LEVELING_EXTERNAL_FLASH_BLOCK_OFFSET) * (EXTERNAL_FLASH_BLOCK_SIZE) + address;
    size_t              index  = 0;
    backing_store_int_t temp[WEAR_LEVELING_EXTERNAL_FLASH_BULK_COUNT];
    do {
        // Copy out the block of data we want to transmit first
        size_t this_loop = MIN(item_count, WEAR_LEVELING_EXTERNAL_FLASH_BULK_COUNT);
        for (size_t i = 0; i < this_loop; ++i) {
            temp[i] = values[index + i];
        }

        bs_dprintf("Write ");
        wl_dump(offset, temp, sizeof(backing_store_int_t) * this_loop);

        // Take the complement instead
        for (size_t i = 0; i < this_loop; ++i) {
            temp[i] = ~temp[i];
        }

        // Write out the block
        if (flash_write_range(offset, temp, sizeof(backing_store_int_t) * this_loop) != FLASH_STATUS_SUCCESS) {
            return false;
        }

        offset += this_loop * sizeof(backing_store_int_t);
        index += this_loop;
        item_count -= this_loop;
    } while (item_count > 0);

    return true;
}
