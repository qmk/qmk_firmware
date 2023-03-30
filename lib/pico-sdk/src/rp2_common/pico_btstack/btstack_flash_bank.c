/*
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/btstack_flash_bank.h"
#include "hardware/flash.h"
#include "hardware/sync.h"
#include <string.h>

// Check sizes
static_assert(PICO_FLASH_BANK_TOTAL_SIZE % (FLASH_SECTOR_SIZE * 2) == 0, "PICO_FLASH_BANK_TOTAL_SIZE invalid");
static_assert(PICO_FLASH_BANK_TOTAL_SIZE <= PICO_FLASH_SIZE_BYTES, "PICO_FLASH_BANK_TOTAL_SIZE too big");
static_assert(PICO_FLASH_BANK_STORAGE_OFFSET + PICO_FLASH_BANK_TOTAL_SIZE <= PICO_FLASH_SIZE_BYTES, "PICO_FLASH_BANK_TOTAL_SIZE too big");

// Size of one bank
#define PICO_FLASH_BANK_SIZE (PICO_FLASH_BANK_TOTAL_SIZE / 2)

#if 0
#define DEBUG_PRINT(format,args...) printf(format, ## args)
#else
#define DEBUG_PRINT(...)
#endif

static uint32_t pico_flash_bank_get_size(void * context) {
    (void)(context);
    return PICO_FLASH_BANK_SIZE;
}

static uint32_t pico_flash_bank_get_alignment(void * context) {
    (void)(context);
    return 1;
}

static void pico_flash_bank_erase(void * context, int bank) {
    (void)(context);
    DEBUG_PRINT("erase: bank %d\n", bank);
    uint32_t status = save_and_disable_interrupts();
    flash_range_erase(PICO_FLASH_BANK_STORAGE_OFFSET + (PICO_FLASH_BANK_SIZE * bank), PICO_FLASH_BANK_SIZE);
    restore_interrupts(status);
}

static void pico_flash_bank_read(void *context, int bank, uint32_t offset, uint8_t *buffer, uint32_t size) {
    (void)(context);
    DEBUG_PRINT("read: bank %d offset %u size %u\n", bank, offset, size);

    assert(bank <= 1);
    if (bank > 1) return;

    assert(offset < PICO_FLASH_BANK_SIZE);
    if (offset >= PICO_FLASH_BANK_SIZE) return;

    assert((offset + size) <= PICO_FLASH_BANK_SIZE);
    if ((offset + size) > PICO_FLASH_BANK_SIZE) return;

    // Flash is xip
    memcpy(buffer, (void *)(XIP_BASE + PICO_FLASH_BANK_STORAGE_OFFSET + (PICO_FLASH_BANK_SIZE * bank) + offset), size);
}

static void pico_flash_bank_write(void * context, int bank, uint32_t offset, const uint8_t *data, uint32_t size) {
    (void)(context);
    DEBUG_PRINT("write: bank %d offset %u size %u\n", bank, offset, size);

    assert(bank <= 1);
    if (bank > 1) return;

    assert(offset < PICO_FLASH_BANK_SIZE);
    if (offset >= PICO_FLASH_BANK_SIZE) return;

    assert((offset + size) <= PICO_FLASH_BANK_SIZE);
    if ((offset + size) > PICO_FLASH_BANK_SIZE) return;

    if (size == 0) return;

    // calc bank start position
    const uint32_t bank_start_pos = PICO_FLASH_BANK_STORAGE_OFFSET + (PICO_FLASH_BANK_SIZE * bank);

    // Calculate first and last page in the bank
    const uint32_t first_page = offset / FLASH_PAGE_SIZE;
    const uint32_t last_page = (offset + size + FLASH_PAGE_SIZE - 1) / FLASH_PAGE_SIZE;

    // Now we only care about the offset in the first page
    offset %= FLASH_PAGE_SIZE;

    // Amount of data we've copied
    uint32_t data_pos = 0;
    uint32_t size_left = size;

    // Write all the pages required
    for(uint32_t page = first_page; page < last_page; page++) {
        uint8_t page_data[FLASH_PAGE_SIZE];

        assert(data_pos < size && size_left <= size);

        // Copy data we're not going to overwrite in the first page
        if (page == first_page && offset > 0) {
            memcpy(page_data,
                (void *)(XIP_BASE + bank_start_pos + (page * FLASH_PAGE_SIZE)),
                offset);
        }

        // Copy the data we're not going to overwrite in the last page
        if (page == last_page - 1 && (offset + size_left) < FLASH_PAGE_SIZE) {
            memcpy(page_data + offset + size_left,
                (void *)(XIP_BASE + bank_start_pos + (page * FLASH_PAGE_SIZE) + offset + size_left),
                FLASH_PAGE_SIZE - offset - size_left);
        }

        // Now copy the new data into the page
        const uint32_t size_to_copy = MIN(size_left, FLASH_PAGE_SIZE - offset);
        memcpy(page_data + offset, data + data_pos, size_to_copy);

        data_pos += size_to_copy;
        size_left -= size_to_copy;

        // zero offset for the following pages
        offset = 0;

        // Now program the entire page
        uint32_t status = save_and_disable_interrupts();
        flash_range_program(bank_start_pos + (page * FLASH_PAGE_SIZE), page_data, FLASH_PAGE_SIZE);
        restore_interrupts(status);
    }
}

static const hal_flash_bank_t pico_flash_bank_instance_obj = {
    /* uint32_t (*get_size)(..) */ 		 &pico_flash_bank_get_size,
    /* uint32_t (*get_alignment)(..); */ &pico_flash_bank_get_alignment,
    /* void (*erase)(..);    */ 		 &pico_flash_bank_erase,
    /* void (*read)(..);      */ 		 &pico_flash_bank_read,
    /* void (*write)(..);     */ 		 &pico_flash_bank_write,
};

const hal_flash_bank_t *pico_flash_bank_instance(void) {

#ifndef NDEBUG
    // Check we're not overlapping the binary in flash
    extern char __flash_binary_end;
    assert((uintptr_t)&__flash_binary_end - XIP_BASE <= PICO_FLASH_BANK_STORAGE_OFFSET);
#endif

    return &pico_flash_bank_instance_obj;
}
