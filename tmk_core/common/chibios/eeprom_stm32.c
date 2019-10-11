/*
 * This software is experimental and a work in progress.
 * Under no circumstances should these files be used in relation to any critical system(s).
 * Use of these files is at your own risk.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This files are free to use from http://engsta.com/stm32-flash-memory-eeprom-emulator/ by
 * Artur F.
 *
 * Modifications for QMK and STM32F303 by Yiancar
 */

#include <stdio.h>
#include <string.h>
#include "eeprom_stm32.h"
/*****************************************************************************
 * Allows to use the internal flash to store non volatile data. To initialize
 * the functionality use the EEPROM_Init() function. Be sure that by reprogramming
 * of the controller just affected pages will be deleted. In other case the non
 * volatile data will be lost.
 ******************************************************************************/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/

uint8_t DataBuf[FEE_PAGE_SIZE];
/*****************************************************************************
 *  Delete Flash Space used for user Data, deletes the whole space between
 *  RW_PAGE_BASE_ADDRESS and the last uC Flash Page
 ******************************************************************************/
uint16_t EEPROM_Init(void) {
    // unlock flash
    FLASH_Unlock();

    // Clear Flags
    // FLASH_ClearFlag(FLASH_SR_EOP|FLASH_SR_PGERR|FLASH_SR_WRPERR);

    return FEE_DENSITY_BYTES;
}
/*****************************************************************************
 *  Erase the whole reserved Flash Space used for user Data
 ******************************************************************************/
void EEPROM_Erase(void) {
    int page_num = 0;

    // delete all pages from specified start page to the last page
    do {
        FLASH_ErasePage(FEE_PAGE_BASE_ADDRESS + (page_num * FEE_PAGE_SIZE));
        page_num++;
    } while (page_num < FEE_DENSITY_PAGES);
}
/*****************************************************************************
 *  Writes once data byte to flash on specified address. If a byte is already
 *  written, the whole page must be copied to a buffer, the byte changed and
 *  the manipulated buffer written after PageErase.
 *******************************************************************************/
uint16_t EEPROM_WriteDataByte(uint16_t Address, uint8_t DataByte) {
    FLASH_Status FlashStatus = FLASH_COMPLETE;

    uint32_t page;
    int      i;

    // exit if desired address is above the limit (e.G. under 2048 Bytes for 4 pages)
    if (Address > FEE_DENSITY_BYTES) {
        return 0;
    }

    // calculate which page is affected (Pagenum1/Pagenum2...PagenumN)
    page = FEE_ADDR_OFFSET(Address) / FEE_PAGE_SIZE;

    // if current data is 0xFF, the byte is empty, just overwrite with the new one
    if ((*(__IO uint16_t *)(FEE_PAGE_BASE_ADDRESS + FEE_ADDR_OFFSET(Address))) == FEE_EMPTY_WORD) {
        FlashStatus = FLASH_ProgramHalfWord(FEE_PAGE_BASE_ADDRESS + FEE_ADDR_OFFSET(Address), (uint16_t)(0x00FF & DataByte));
    } else {
        // Copy Page to a buffer
        memcpy(DataBuf, (uint8_t *)FEE_PAGE_BASE_ADDRESS + (page * FEE_PAGE_SIZE), FEE_PAGE_SIZE);  // !!! Calculate base address for the desired page

        // check if new data is differ to current data, return if not, proceed if yes
        if (DataByte == *(__IO uint8_t *)(FEE_PAGE_BASE_ADDRESS + FEE_ADDR_OFFSET(Address))) {
            return 0;
        }

        // manipulate desired data byte in temp data array if new byte is differ to the current
        DataBuf[FEE_ADDR_OFFSET(Address) % FEE_PAGE_SIZE] = DataByte;

        // Erase Page
        FlashStatus = FLASH_ErasePage(FEE_PAGE_BASE_ADDRESS + (page * FEE_PAGE_SIZE));

        // Write new data (whole page) to flash if data has been changed
        for (i = 0; i < (FEE_PAGE_SIZE / 2); i++) {
            if ((__IO uint16_t)(0xFF00 | DataBuf[FEE_ADDR_OFFSET(i)]) != 0xFFFF) {
                FlashStatus = FLASH_ProgramHalfWord((FEE_PAGE_BASE_ADDRESS + (page * FEE_PAGE_SIZE)) + (i * 2), (uint16_t)(0xFF00 | DataBuf[FEE_ADDR_OFFSET(i)]));
            }
        }
    }
    return FlashStatus;
}
/*****************************************************************************
 *  Read once data byte from a specified address.
 *******************************************************************************/
uint8_t EEPROM_ReadDataByte(uint16_t Address) {
    uint8_t DataByte = 0xFF;

    // Get Byte from specified address
    DataByte = (*(__IO uint8_t *)(FEE_PAGE_BASE_ADDRESS + FEE_ADDR_OFFSET(Address)));

    return DataByte;
}

/*****************************************************************************
 *  Wrap library in AVR style functions.
 *******************************************************************************/
uint8_t eeprom_read_byte(const uint8_t *Address) {
    const uint16_t p = (const uint32_t)Address;
    return EEPROM_ReadDataByte(p);
}

void eeprom_write_byte(uint8_t *Address, uint8_t Value) {
    uint16_t p = (uint32_t)Address;
    EEPROM_WriteDataByte(p, Value);
}

void eeprom_update_byte(uint8_t *Address, uint8_t Value) {
    uint16_t p = (uint32_t)Address;
    EEPROM_WriteDataByte(p, Value);
}

uint16_t eeprom_read_word(const uint16_t *Address) {
    const uint16_t p = (const uint32_t)Address;
    return EEPROM_ReadDataByte(p) | (EEPROM_ReadDataByte(p + 1) << 8);
}

void eeprom_write_word(uint16_t *Address, uint16_t Value) {
    uint16_t p = (uint32_t)Address;
    EEPROM_WriteDataByte(p, (uint8_t)Value);
    EEPROM_WriteDataByte(p + 1, (uint8_t)(Value >> 8));
}

void eeprom_update_word(uint16_t *Address, uint16_t Value) {
    uint16_t p = (uint32_t)Address;
    EEPROM_WriteDataByte(p, (uint8_t)Value);
    EEPROM_WriteDataByte(p + 1, (uint8_t)(Value >> 8));
}

uint32_t eeprom_read_dword(const uint32_t *Address) {
    const uint16_t p = (const uint32_t)Address;
    return EEPROM_ReadDataByte(p) | (EEPROM_ReadDataByte(p + 1) << 8) | (EEPROM_ReadDataByte(p + 2) << 16) | (EEPROM_ReadDataByte(p + 3) << 24);
}

void eeprom_write_dword(uint32_t *Address, uint32_t Value) {
    uint16_t p = (const uint32_t)Address;
    EEPROM_WriteDataByte(p, (uint8_t)Value);
    EEPROM_WriteDataByte(p + 1, (uint8_t)(Value >> 8));
    EEPROM_WriteDataByte(p + 2, (uint8_t)(Value >> 16));
    EEPROM_WriteDataByte(p + 3, (uint8_t)(Value >> 24));
}

void eeprom_update_dword(uint32_t *Address, uint32_t Value) {
    uint16_t p             = (const uint32_t)Address;
    uint32_t existingValue = EEPROM_ReadDataByte(p) | (EEPROM_ReadDataByte(p + 1) << 8) | (EEPROM_ReadDataByte(p + 2) << 16) | (EEPROM_ReadDataByte(p + 3) << 24);
    if (Value != existingValue) {
        EEPROM_WriteDataByte(p, (uint8_t)Value);
        EEPROM_WriteDataByte(p + 1, (uint8_t)(Value >> 8));
        EEPROM_WriteDataByte(p + 2, (uint8_t)(Value >> 16));
        EEPROM_WriteDataByte(p + 3, (uint8_t)(Value >> 24));
    }
}

void eeprom_read_block(void *buf, const void *addr, uint32_t len) {
    const uint8_t *p    = (const uint8_t *)addr;
    uint8_t *      dest = (uint8_t *)buf;
    while (len--) {
        *dest++ = eeprom_read_byte(p++);
    }
}

void eeprom_write_block(const void *buf, void *addr, uint32_t len) {
    uint8_t *      p   = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        eeprom_write_byte(p++, *src++);
    }
}

void eeprom_update_block(const void *buf, void *addr, uint32_t len) {
    uint8_t *      p   = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        eeprom_write_byte(p++, *src++);
    }
}
