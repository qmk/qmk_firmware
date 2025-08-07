/* Copyright 2020 Nick Brassel (tzarc)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <string.h>

#include <hal.h>
#include "eeprom_driver.h"
#include "eeprom_stm32_L0_L1.h"

#define EEPROM_BASE_ADDR 0x08080000
#define EEPROM_ADDR(offset) (EEPROM_BASE_ADDR + (offset))
#define EEPROM_PTR(offset) ((__IO uint8_t *)EEPROM_ADDR(offset))
#define EEPROM_BYTE(location, offset) (*(EEPROM_PTR(((uint32_t)location) + ((uint32_t)offset))))
#define EEPROM_WORD(location) (*(__IO uint32_t *)EEPROM_PTR(location))

#define BUFFER_BYTE(buffer, offset) (*(((uint8_t *)buffer) + offset))

#define FLASH_PEKEY1 0x89ABCDEF
#define FLASH_PEKEY2 0x02030405

static inline void STM32_L0_L1_EEPROM_WaitNotBusy(void) {
    while (FLASH->SR & FLASH_SR_BSY) {
        __WFI();
    }
}

static inline void STM32_L0_L1_EEPROM_Unlock(void) {
    STM32_L0_L1_EEPROM_WaitNotBusy();
    if (FLASH->PECR & FLASH_PECR_PELOCK) {
        FLASH->PEKEYR = FLASH_PEKEY1;
        FLASH->PEKEYR = FLASH_PEKEY2;
    }
}

static inline void STM32_L0_L1_EEPROM_Lock(void) {
    STM32_L0_L1_EEPROM_WaitNotBusy();
    FLASH->PECR |= FLASH_PECR_PELOCK;
}

void eeprom_driver_init(void) {}

void eeprom_driver_format(bool erase) {
    if (erase) {
        eeprom_driver_erase();
    }
}

void eeprom_driver_erase(void) {
    STM32_L0_L1_EEPROM_Unlock();

    for (size_t offset = 0; offset < STM32_ONBOARD_EEPROM_SIZE; offset += sizeof(uint32_t)) {
#ifdef QMK_MCU_SERIES_STM32L0XX
        FLASH->PECR |= FLASH_PECR_ERASE | FLASH_PECR_DATA;
#endif

        EEPROM_WORD(offset) = (uint32_t)0;

        STM32_L0_L1_EEPROM_WaitNotBusy();
#ifdef QMK_MCU_SERIES_STM32L0XX
        FLASH->PECR &= ~(FLASH_PECR_ERASE | FLASH_PECR_DATA);
#endif
    }

    STM32_L0_L1_EEPROM_Lock();
}

void eeprom_read_block(void *buf, const void *addr, size_t len) {
    for (size_t offset = 0; offset < len; ++offset) {
        // Drop out if we've hit the limit of the EEPROM
        if ((((uint32_t)addr) + offset) >= STM32_ONBOARD_EEPROM_SIZE) {
            break;
        }

        STM32_L0_L1_EEPROM_WaitNotBusy();
        BUFFER_BYTE(buf, offset) = EEPROM_BYTE(addr, offset);
    }
}

void eeprom_write_block(const void *buf, void *addr, size_t len) {
    // use word-aligned write to overcome issues with writing null bytes
    uint32_t start_addr = (uint32_t)addr;
    if (start_addr >= (STM32_ONBOARD_EEPROM_SIZE)) {
        return;
    }
    uint32_t max_len = (STM32_ONBOARD_EEPROM_SIZE)-start_addr;
    if (len > max_len) {
        len = max_len;
    }
    uint32_t end_addr = start_addr + len;

    uint32_t aligned_start = start_addr & ~0x3;
    uint32_t aligned_end   = (end_addr + 3) & ~0x3;

    STM32_L0_L1_EEPROM_Unlock();
    for (uint32_t word_addr = aligned_start; word_addr < aligned_end; word_addr += 4) {
        uint32_t existing_word = EEPROM_WORD(word_addr);
        uint32_t new_word      = existing_word;

        // Update the relevant bytes in the word
        for (int i = 0; i < 4; i++) {
            uint32_t byte_addr = word_addr + i;
            if (byte_addr >= start_addr && byte_addr < end_addr) {
                uint8_t new_byte = BUFFER_BYTE(buf, byte_addr - start_addr);
                new_word         = (new_word & ~(0xFFU << (i * 8))) | ((uint32_t)new_byte << (i * 8));
            }
        }

        // Only write if the word has changed
        if (new_word != existing_word) {
            STM32_L0_L1_EEPROM_WaitNotBusy();
            EEPROM_WORD(word_addr) = new_word;
        }
    }
    STM32_L0_L1_EEPROM_Lock();
}
