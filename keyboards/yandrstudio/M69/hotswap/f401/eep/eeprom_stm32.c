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
 * update for STM32F4 support and the the flashing algorithm by yulei
 * Adjust the file structure to custom EEPROM_DRIVER by jiaxin96 for support stm32f401cc
 */

#include <stdio.h>
#include <string.h>
#include "eeprom_stm32_custom.h"
#include "eeprom_driver.h"
/*****************************************************************************
 * Allows to use the internal flash to store non volatile data. To initialize
 * the functionality use the EEPROM_Init() function. Be sure that by reprogramming
 * of the controller just affected pages will be deleted. In other case the non
 * volatile data will be lost.
 ******************************************************************************/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/

#define IS_VALID_ADDRESS(x) ((x) < FEE_MAX_BYTES)

uint8_t DataBuf[FEE_MAX_BYTES];
static void EEPROM_Backup(void);
static FLASH_Status EEPROM_Restore(void);
static uint32_t EEPROM_FindValidAddress(void);
static void EEPROM_Clear(void);

/*****************************************************************************
 *  Unlock the FLASH programming and initialized the DataBuf
 ******************************************************************************/
uint16_t EEPROM_Init(void) {
    // unlock flash
    FLASH_Unlock();

    // initialize DataBuf
    EEPROM_Backup();

    // Clear Flags
    // FLASH_ClearFlag(FLASH_SR_EOP|FLASH_SR_PGERR|FLASH_SR_WRPERR);

    return FEE_DENSITY_BYTES;
}
void eeprom_driver_init(void) {
    EEPROM_Init();
}

/*****************************************************************************
 *  Erase the whole reserved Flash Space used for user Data
 ******************************************************************************/
void EEPROM_Erase(void) {
    // erase all flash pages
    EEPROM_Clear();

    // reset the content of the buffer
    memset(&DataBuf[0], FEE_EMPTY_BYTE, sizeof(DataBuf));
}
void eeprom_driver_erase(void) {
    EEPROM_Erase();
}
/*****************************************************************************
 * Write data with its eeprom address to flash if there has empty words,
 * otherwise backup the current valid data, erase all flash pages,
 * and finally restore the valid data.
 *******************************************************************************/
uint16_t EEPROM_WriteDataByte(uint16_t Address, uint8_t DataByte) {
    FLASH_Status FlashStatus = FLASH_COMPLETE;

    uint32_t addr;
    // exit if not a valid address
    if (!IS_VALID_ADDRESS(Address)) {
        return 0;
    }

// we are sure the address will not be out of bound
#pragma GCC diagnostic ignored "-Warray-bounds"
    // same value, do not need program
    if (DataBuf[Address] == DataByte) {
        return FlashStatus;
    }

    // find the address can be written
    addr = EEPROM_FindValidAddress();
    DataBuf[Address] = DataByte;
#pragma GCC diagnostic pop
    if (addr == FEE_EMPTY_VALUE) {
        // EEPROM is full, need to erase and reprogramming
        EEPROM_Clear();
        EEPROM_Restore();
    } else {
        FLASH_ProgramHalfWord(FEE_ADDR_ADDRESS(addr), Address);
        FLASH_ProgramHalfWord(FEE_DATA_ADDRESS(addr), DataByte);
    }

    return FlashStatus;
}
/*****************************************************************************
 *  Read once data byte from a specified address.
 *******************************************************************************/
uint8_t EEPROM_ReadDataByte(uint16_t Address) {
    if (!IS_VALID_ADDRESS(Address)) {
        return FEE_EMPTY_BYTE;
    }

    // Get Byte from caches
    return DataBuf[Address];
}

/*****************************************************************************
 *  helper functions
 *******************************************************************************/
// backup the current data
void EEPROM_Backup(void)
{
    uint32_t begin = FEE_PAGE_BASE_ADDRESS;
    uint32_t end = FEE_PAGE_END_ADDRESS;
    memset(&DataBuf[0], FEE_EMPTY_BYTE, sizeof(DataBuf));
    while( begin < end) {
        uint16_t addr = *(__IO uint16_t*)(FEE_ADDR_ADDRESS(begin));
        if (IS_VALID_ADDRESS(addr)) {
            DataBuf[addr] = *(__IO uint16_t*)(FEE_DATA_ADDRESS(begin));
        } else if( addr == FEE_EMPTY_WORD) {
            uint16_t data = *(__IO uint16_t*)(FEE_DATA_ADDRESS(begin));
            if (data == FEE_EMPTY_WORD) {
                // we reached the end of valid data
                break;
            }
        }
        begin += 4;
    }
}
// restore data from DataBuf
FLASH_Status EEPROM_Restore(void) {
    uint32_t cur = FEE_PAGE_BASE_ADDRESS;
    for (uint8_t i = 0; i < FEE_MAX_BYTES; i++) {
        if (DataBuf[i] != FEE_EMPTY_BYTE) {
            FLASH_ProgramHalfWord(FEE_ADDR_ADDRESS(cur), i);
            FLASH_ProgramHalfWord(FEE_DATA_ADDRESS(cur), DataBuf[i]);
            cur += 4;
        }
    }
    return FLASH_COMPLETE;
}
// find an empty place for programming
uint32_t EEPROM_FindValidAddress(void) {
    uint32_t begin = FEE_PAGE_BASE_ADDRESS;
    uint32_t end = FEE_PAGE_END_ADDRESS;
    while( begin < end) {
        uint32_t data = *(__IO uint32_t*)(begin);
        if (data == FEE_EMPTY_VALUE) {
            return begin;
        }
        begin += 4;
    }
    return FEE_EMPTY_VALUE;
}

void EEPROM_Clear(void)
{
#if defined(EEPROM_EMU_STM32F401xC)
    FLASH_ErasePage(FEE_SECTOR_ID);
#else
    int page_num = 0;

    // delete all pages from specified start page to the last page
    do {
        FLASH_ErasePage(FEE_PAGE_BASE_ADDRESS + (page_num * FEE_PAGE_SIZE));
        page_num++;
    } while (page_num < FEE_DENSITY_PAGES);
#endif
}
/*****************************************************************************
 *  Wrap library in AVR style functions.
 *******************************************************************************/
uint8_t eeprom_read_byte_f4(const uint8_t *Address) {
    const uint16_t p = (const uint32_t)Address;
    return EEPROM_ReadDataByte(p);
}

void eeprom_write_byte_f4(uint8_t *Address, uint8_t Value) {
    uint16_t p = (uint32_t)Address;
    EEPROM_WriteDataByte(p, Value);
}


void eeprom_read_block(void *buf, const void *addr, size_t len) {
    const uint8_t *p    = (const uint8_t *)addr;
    uint8_t *      dest = (uint8_t *)buf;
    while (len--) {
        *dest++ = eeprom_read_byte_f4(p++);
    }
}

void eeprom_write_block(const void *buf, void *addr, size_t len) {
    uint8_t *      p   = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        eeprom_write_byte_f4(p++, *src++);
    }
}


