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
 * Modifications to add flash wear leveling by Ilya Zhuravlev
 */

#include <stdio.h>
#include <string.h>
#include "eeprom_stm32.h"

/* In-memory contents of emulated eeprom for faster access */
static uint8_t DataBuf[FEE_DENSITY_BYTES];

/* Pointer to the first available slot within flash area */
static uint8_t *empty_slot;

void EEPROM_Init(void) {
    memset(DataBuf, 0, sizeof(DataBuf));

    /* Load emulated eeprom contents from flash into memory */
    uint8_t *addr;
    for (addr = (uint8_t*)FEE_PAGE_BASE_ADDRESS; addr < (uint8_t*)FEE_LAST_PAGE_ADDRESS; addr += 4) {
        uint16_t address;
        uint8_t value;
        memcpy(&address, addr, sizeof(address));
        memcpy(&value, addr+2, sizeof(value));
        if (address == FEE_EMPTY_WORD)
            break;
        if (address < FEE_DENSITY_BYTES)
            DataBuf[address] = value;
    }

    empty_slot = addr;
}

/* Clear flash contents (doesn't touch in-memory DataBuf) */
static void eeprom_clear(void) {
    FLASH_Unlock();

    for (uint32_t page_num = 0; page_num < FEE_DENSITY_PAGES; ++page_num)
        FLASH_ErasePage(FEE_PAGE_BASE_ADDRESS + (page_num * FEE_PAGE_SIZE));

    FLASH_Lock();

    empty_slot = (void*)FEE_PAGE_BASE_ADDRESS;
}

/* Erase emulated eeprom */
void EEPROM_Erase(void) {
    eeprom_clear();
    /* re-initialize to clear DataBuf */
    EEPROM_Init();
}

static void eeprom_writedatabyte(uint16_t Address, uint8_t DataByte);

/* Dump in-memory contents into flash */
static void eeprom_restore(void) {
    for (uint32_t i = 0; i < FEE_DENSITY_BYTES; ++i) {
        /* don't bother writing zeroes */
        if (DataBuf[i]) {
            eeprom_writedatabyte(i, DataBuf[i]);
        }
    }
}

static void eeprom_writedatabyte(uint16_t Address, uint8_t DataByte) {
    /* if couldn't find an empty spot, we must re-initialize emulated eeprom */
    if (empty_slot >= (uint8_t*)FEE_LAST_PAGE_ADDRESS) {
        /* ensure that the following call to eeprom_restore will write our desired byte value */
        DataBuf[Address] = DataByte;

        /* fully erase emulated eeprom */
        eeprom_clear();

        /* and then write DataBuf contents back into flash */
        eeprom_restore();

        /* don't need to do anything else as eeprom_restore already wrote our value */
        return;
    }

    /* ok we found a place let's write our data */
    FLASH_Unlock();

    /* address */
    FLASH_ProgramHalfWord((uint32_t)empty_slot, Address);
    /* value */
    FLASH_ProgramHalfWord((uint32_t)empty_slot + 2, DataByte | 0xFF00);

    FLASH_Lock();

    empty_slot += 4;
}

void EEPROM_WriteDataByte(uint16_t Address, uint8_t DataByte) {
    /* if the address is out-of-bounds, do nothing */
    if (Address >= FEE_DENSITY_BYTES)
        return;

    /* if the value is the same, don't bother writing it */
    if (DataBuf[Address] == DataByte)
        return;

    /* perform the write into flash memory */
    eeprom_writedatabyte(Address, DataByte);

    /* keep DataBuf cache in sync */
    DataBuf[Address] = DataByte;
}

uint8_t EEPROM_ReadDataByte(uint16_t Address) {
    uint8_t DataByte = 0x00;

    if (Address < FEE_DENSITY_BYTES)
        DataByte = DataBuf[Address];

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

void eeprom_read_block(void *buf, const void *addr, size_t len) {
    const uint8_t *p    = (const uint8_t *)addr;
    uint8_t *      dest = (uint8_t *)buf;
    while (len--) {
        *dest++ = eeprom_read_byte(p++);
    }
}

void eeprom_write_block(const void *buf, void *addr, size_t len) {
    uint8_t *      p   = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        eeprom_write_byte(p++, *src++);
    }
}

void eeprom_update_block(const void *buf, void *addr, size_t len) {
    uint8_t *      p   = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        eeprom_write_byte(p++, *src++);
    }
}
