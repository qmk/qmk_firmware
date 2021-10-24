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

#define SNAPSHOT_START (FEE_BASE_ADDRESS)
#define SNAPSHOT_END (FEE_BASE_ADDRESS+FEE_SNAPSHOT_SIZE)
#define WRITELOG_START (SNAPSHOT_END)
#define WRITELOG_END (WRITELOG_START+FEE_WRITELOG_SIZE)

/* In-memory contents of emulated eeprom for direct faster access */
static uint8_t DataBuf[FEE_DENSITY_BYTES];

/* Pointer to the first available slot within the writelog */
static uint8_t *empty_slot;

void EEPROM_Init(void) {
    /* First, load the snapshot directly from flash */
    void *volatile tmp = (void*)FEE_BASE_ADDRESS;
    memcpy(DataBuf, (void*)tmp, FEE_SNAPSHOT_SIZE);

    /* Then, process writelog to update DataBuf entries */
    uint8_t *addr;
    for (addr = (uint8_t*)WRITELOG_START; addr < (uint8_t*)WRITELOG_END; addr += 4) {
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

/* Erase flash contents so we can put updated data in (doesn't touch in-memory DataBuf) */
static void eeprom_clear(void) {
    FLASH_Unlock();

#if defined(EEPROM_EMU_STM32F4)
    FLASH_ErasePage(FEE_SECTOR_ID);
#else
    for (uint32_t erase_address = SNAPSHOT_START; erase_address < WRITELOG_END; erase_address += FEE_PAGE_SIZE)
        FLASH_ErasePage(erase_address);
#endif

    FLASH_Lock();

    empty_slot = (void*)WRITELOG_START;
}

/* Erase emulated eeprom */
void EEPROM_Erase(void) {
    eeprom_clear();
    /* re-initialize to clear DataBuf */
    EEPROM_Init();
}

static void eeprom_writedatabyte(uint16_t Address, uint8_t DataByte);

/* Dump in-memory eeprom contents into the snapshot area */
static void eeprom_write_snapshot(void) {
    FLASH_Unlock();

    for (uint32_t i = 0; i < FEE_DENSITY_BYTES; i += 2) {
        uint16_t halfword;
        memcpy(&halfword, &DataBuf[i], sizeof(halfword));

        FLASH_ProgramHalfWord(SNAPSHOT_START + i, halfword);
    }

    FLASH_Lock();
}

static void eeprom_writedatabyte(uint16_t Address, uint8_t DataByte) {
    /* if couldn't find an empty spot, we must re-initialize emulated eeprom */
    if (empty_slot >= (uint8_t*)WRITELOG_END) {
        /* fully erase emulated eeprom */
        eeprom_clear();

        /* and then write DataBuf contents back into flash */
        eeprom_write_snapshot();
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

static void EEPROM_WriteDataByte(uint16_t Address, uint8_t DataByte) {
    /* if the address is out-of-bounds, do nothing */
    if (Address >= FEE_DENSITY_BYTES)
        return;

    /* if the value is the same, don't bother writing it */
    if (DataBuf[Address] == DataByte)
        return;

    /* keep DataBuf cache in sync */
    DataBuf[Address] = DataByte;

    /* perform the write into flash memory */
    eeprom_writedatabyte(Address, DataByte);
}

static uint8_t EEPROM_ReadDataByte(uint16_t Address) {
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
