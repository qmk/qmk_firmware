// Copyright 2025 Stefan Kerkmann (@karlk90)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <hal.h>

#define FLASH_KEY1 0x45670123U
#define FLASH_KEY2 0xCDEF89ABU
#define FLASH_OPTKEY1 0x08192A3BU
#define FLASH_OPTKEY2 0x4C5D6E7FU
#define FLASH_OPTR_CLR_MASK (FLASH_OPTR_nBOOT_SEL)
#define FLASH_OPTR_SET_MASK (FLASH_OPTR_NRST_MODE_Msk)

static void wait_for_flash(void) {
    while (READ_BIT(FLASH->SR, FLASH_SR_BSY1)) {
    }
}

void __attribute__((constructor)) enable_boot0_and_nrst_pin(void) {
    // Only apply on STM32G0x1 devices, see RM0444 Rev 6, Table 265: "DEV_ID
    // and REV_ID field values."
    switch (READ_BIT(DBG->IDCODE, DBG_IDCODE_DEV_ID)) {
        case 0x467: // STM32G0B1xx and STM32G0C1xx
        case 0x460: // STM32G071xx and STM32G081xx
        case 0x456: // STM32G051xx and STM32G061xx
        case 0x466: // STM32G041xx and STM32G031xx
            break;
        default:
            return;
    }

    uint32_t optr = FLASH->OPTR;

    // Make sure that:
    // 1. legacy boot0 pin handling is enabled.
    //   OPTR[24] = 0
    // 2. legacy nRST pin handling is enabled.
    //   OPTR[28:27] = 0b11
    // To match the default behavior found in older (F0/F1/F3/F4) STM32 devices.
    if (READ_BIT(optr, FLASH_OPTR_CLR_MASK) || (READ_BIT(optr, FLASH_OPTR_SET_MASK) != FLASH_OPTR_SET_MASK)) {
        if (READ_BIT(FLASH->CR, FLASH_CR_LOCK)) {
            WRITE_REG(FLASH->KEYR, FLASH_KEY1);
            WRITE_REG(FLASH->KEYR, FLASH_KEY2);
            while (READ_BIT(FLASH->CR, FLASH_CR_LOCK)) {
            }
            wait_for_flash();
        }
        if (READ_BIT(FLASH->CR, FLASH_CR_OPTLOCK)) {
            WRITE_REG(FLASH->OPTKEYR, FLASH_OPTKEY1);
            WRITE_REG(FLASH->OPTKEYR, FLASH_OPTKEY2);
            while (READ_BIT(FLASH->CR, FLASH_CR_OPTLOCK)) {
            }
            wait_for_flash();
        }

        MODIFY_REG(FLASH->OPTR, FLASH_OPTR_CLR_MASK, FLASH_OPTR_SET_MASK);
        wait_for_flash();

        SET_BIT(FLASH->CR, FLASH_CR_OPTSTRT);
        wait_for_flash();

        CLEAR_BIT(FLASH->CR, FLASH_CR_OPTSTRT);
        wait_for_flash();

        // Launch the option byte (re)loading, which resets the device. This
        // should not return.
        SET_BIT(FLASH->CR, FLASH_CR_OBL_LAUNCH);
    }
}
