// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <stdbool.h>
#include <hal.h>
#include "timer.h"
#include "wear_leveling.h"
#include "wear_leveling_internal.h"

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
    bs_dprintf("Write ");
    uint32_t offset = (WEAR_LEVELING_EXTERNAL_FLASH_BLOCK_OFFSET) * (EXTERNAL_FLASH_BLOCK_SIZE) + address;
    wl_dump(offset, &value, sizeof(value));
    value = ~value;
    return flash_write_block(offset, &value, sizeof(value)) == FLASH_STATUS_SUCCESS;
}

bool backing_store_lock(void) {
    bs_dprintf("Lock  \n");
    // No-op -- handled by the flash driver as it is.
    return true;
}

bool backing_store_read(uint32_t address, backing_store_int_t *value) {
    bs_dprintf("Read  ");
    uint32_t       offset = (WEAR_LEVELING_EXTERNAL_FLASH_BLOCK_OFFSET) * (EXTERNAL_FLASH_BLOCK_SIZE) + address;
    flash_status_t status = flash_read_block(offset, value, sizeof(backing_store_int_t));
    *value                = ~(*value);
    wl_dump(offset, value, sizeof(backing_store_int_t));
    return status == FLASH_STATUS_SUCCESS;
}
