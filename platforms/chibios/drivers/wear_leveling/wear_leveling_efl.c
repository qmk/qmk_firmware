// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <stdbool.h>
#include <hal.h>
#include "timer.h"
#include "wear_leveling.h"
#include "wear_leveling_internal.h"

static flash_offset_t base_offset = UINT32_MAX;

#if defined(WEAR_LEVELING_EFL_FIRST_SECTOR)
static flash_sector_t first_sector = WEAR_LEVELING_EFL_FIRST_SECTOR;
#else  // defined(WEAR_LEVELING_EFL_FIRST_SECTOR)
static flash_sector_t first_sector = UINT16_MAX;
#endif // defined(WEAR_LEVELING_EFL_FIRST_SECTOR)

static flash_sector_t sector_count = UINT16_MAX;
static BaseFlash *    flash;

static volatile bool is_issuing_read    = false;
static volatile bool ecc_error_occurred = false;

// "Automatic" detection of the flash size -- ideally ChibiOS would have this already, but alas, it doesn't.
static inline uint32_t detect_flash_size(void) {
#if defined(WEAR_LEVELING_EFL_FLASH_SIZE)
    return WEAR_LEVELING_EFL_FLASH_SIZE;
#elif defined(FLASH_BANK_SIZE)
    return FLASH_BANK_SIZE;
#elif defined(FLASH_SIZE)
    return FLASH_SIZE;
#elif defined(FLASHSIZE_BASE)
#    if defined(QMK_MCU_SERIES_STM32F0XX) || defined(QMK_MCU_SERIES_STM32F1XX) || defined(QMK_MCU_SERIES_STM32F3XX) || defined(QMK_MCU_SERIES_STM32F4XX) || defined(QMK_MCU_SERIES_STM32G4XX) || defined(QMK_MCU_SERIES_STM32L0XX) || defined(QMK_MCU_SERIES_STM32L4XX) || defined(QMK_MCU_SERIES_GD32VF103)
    return ((*(uint32_t *)FLASHSIZE_BASE) & 0xFFFFU) << 10U; // this register has the flash size in kB, so we convert it to bytes
#    elif defined(QMK_MCU_SERIES_STM32L1XX)
#        error This MCU family has an uncommon flash size register definition and has not been implemented. Perhaps try using the true EEPROM on the MCU instead?
#    endif
#else
#    error Unknown flash size definition.
    return 0;
#endif
}

bool backing_store_init(void) {
    bs_dprintf("Init\n");
    flash = (BaseFlash *)&EFLD1;

    // Need to re-lock the EFL, as if we've just had the bootloader executing it'll already be unlocked.
    backing_store_lock();

    const flash_descriptor_t *desc       = flashGetDescriptor(flash);
    uint32_t                  counter    = 0;
    uint32_t                  flash_size = detect_flash_size();

#if defined(WEAR_LEVELING_EFL_FIRST_SECTOR)

    // Work out how many sectors we want to use, working forwards from the first sector specified
    for (flash_sector_t i = 0; i < desc->sectors_count - first_sector; ++i) {
        counter += flashGetSectorSize(flash, first_sector + i);
        if (counter >= (WEAR_LEVELING_BACKING_SIZE)) {
            sector_count = i + 1;
            base_offset  = flashGetSectorOffset(flash, first_sector);
            break;
        }
    }
    if (sector_count == UINT16_MAX || base_offset >= flash_size) {
        // We didn't get the required number of sectors. Can't do anything here. Fault.
        chSysHalt("Invalid sector count intended to be used with wear_leveling");
    }

#else // defined(WEAR_LEVELING_EFL_FIRST_SECTOR)

    // Work out how many sectors we want to use, working backwards from the end of the flash
    flash_sector_t last_sector = desc->sectors_count;
    for (flash_sector_t i = 0; i < desc->sectors_count; ++i) {
        first_sector = desc->sectors_count - i - 1;
        if (flashGetSectorOffset(flash, first_sector) >= flash_size) {
            last_sector = first_sector;
            continue;
        }
        counter += flashGetSectorSize(flash, first_sector);
        if (counter >= (WEAR_LEVELING_BACKING_SIZE)) {
            sector_count = last_sector - first_sector;
            base_offset  = flashGetSectorOffset(flash, first_sector);
            break;
        }
    }

#endif // defined(WEAR_LEVELING_EFL_FIRST_SECTOR)

    return true;
}

bool backing_store_unlock(void) {
    bs_dprintf("Unlock\n");
    return eflStart(&EFLD1, NULL) == HAL_RET_SUCCESS;
}

bool backing_store_erase(void) {
#ifdef WEAR_LEVELING_DEBUG_OUTPUT
    uint32_t start = timer_read32();
#endif

    bool          ret = true;
    flash_error_t status;
    for (int i = 0; i < sector_count; ++i) {
        // Kick off the sector erase
        status = flashStartEraseSector(flash, first_sector + i);
        if (status != FLASH_NO_ERROR && status != FLASH_BUSY_ERASING) {
            ret = false;
        }

        // Wait for the erase to complete
        status = flashWaitErase(flash);
        if (status != FLASH_NO_ERROR && status != FLASH_BUSY_ERASING) {
            ret = false;
        }
    }

    bs_dprintf("Backing store erase took %ldms to complete\n", ((long)(timer_read32() - start)));
    return ret;
}

bool backing_store_write(uint32_t address, backing_store_int_t value) {
    uint32_t offset = (base_offset + address);
    bs_dprintf("Write ");
    wl_dump(offset, &value, sizeof(value));
    value = ~value;
    return flashProgram(flash, offset, sizeof(value), (const uint8_t *)&value) == FLASH_NO_ERROR;
}

bool backing_store_lock(void) {
    bs_dprintf("Lock  \n");
    eflStop(&EFLD1);
    return true;
}

static backing_store_int_t backing_store_safe_read_from_location(backing_store_int_t *loc) {
    backing_store_int_t value;
    is_issuing_read    = true;
    ecc_error_occurred = false;
    value              = ~(*loc);
    is_issuing_read    = false;
    return value;
}

bool backing_store_read(uint32_t address, backing_store_int_t *value) {
    uint32_t             offset = (base_offset + address);
    backing_store_int_t *loc    = (backing_store_int_t *)flashGetOffsetAddress(flash, offset);
    backing_store_int_t  tmp    = backing_store_safe_read_from_location(loc);

    if (ecc_error_occurred) {
        bs_dprintf("Failed to read from backing store, ECC error detected\n");
        ecc_error_occurred = false;
        *value             = 0;
        return false;
    }

    *value = tmp;

    bs_dprintf("Read  ");
    wl_dump(offset, value, sizeof(backing_store_int_t));
    return true;
}

bool backing_store_allow_ecc_errors(void) {
    return is_issuing_read;
}

void backing_store_signal_ecc_error(void) {
    ecc_error_occurred = true;
}
