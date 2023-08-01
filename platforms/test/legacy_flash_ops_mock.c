/* Copyright 2021 by Don Kjer
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

#include <string.h>
#include <stdbool.h>
#include "legacy_flash_ops.h"

uint8_t FlashBuf[MOCK_FLASH_SIZE] = {0};

static bool flash_locked = true;

FLASH_Status FLASH_ErasePage(uint32_t Page_Address) {
    if (flash_locked) return FLASH_ERROR_WRP;
    Page_Address -= (uintptr_t)FlashBuf;
    Page_Address -= (Page_Address % FEE_PAGE_SIZE);
    if (Page_Address >= MOCK_FLASH_SIZE) return FLASH_BAD_ADDRESS;
    memset(&FlashBuf[Page_Address], '\xff', FEE_PAGE_SIZE);
    return FLASH_COMPLETE;
}

FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data) {
    if (flash_locked) return FLASH_ERROR_WRP;
    Address -= (uintptr_t)FlashBuf;
    if (Address >= MOCK_FLASH_SIZE) return FLASH_BAD_ADDRESS;
    uint16_t oldData = *(uint16_t*)&FlashBuf[Address];
    if (oldData == 0xFFFF || Data == 0) {
        *(uint16_t*)&FlashBuf[Address] = Data;
        return FLASH_COMPLETE;
    } else {
        return FLASH_ERROR_PG;
    }
}

FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout) {
    return FLASH_COMPLETE;
}
void FLASH_Unlock(void) {
    flash_locked = false;
}
void FLASH_Lock(void) {
    flash_locked = true;
}
