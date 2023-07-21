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
 * Adapted for SONIX chips by dexter93 and gloryhzw
 */

#include <stdio.h>
#include <string.h>
#include "debug.h"
#include "Flash.h"
#include "eeprom_sn32.h"

/*****************************************************************************
 * Allows to use the internal flash to store non volatile data. To initialize
 * the functionality use the EEPROM_Init() function. Be sure that by reprogramming
 * of the controller just affected pages will be deleted. In other case the non
 * volatile data will be lost.
 ******************************************************************************/
#include "eeprom_sn32_defs.h"
#if !defined(FEE_PAGE_SIZE) || !defined(FEE_TOTAL_PAGES) || !defined(FEE_DENSITY_PAGES) || !defined(FEE_MCU_FLASH_SIZE) || !defined(FEE_PAGE_BASE_ADDRESS)
#    error "not implemented."
#endif

#define FEE_DENSITY_BYTES (FEE_PAGE_SIZE * FEE_DENSITY_PAGES - 1)
#define FEE_LAST_PAGE_ADDRESS (FEE_PAGE_BASE_ADDRESS + (FEE_PAGE_SIZE * FEE_DENSITY_PAGES))
#define FEE_ADDR_OFFSET(Address) (Address)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/
/*
 * Debug print utils
 */

// #define DEBUG_EEPROM_OUTPUT

#if defined(DEBUG_EEPROM_OUTPUT)

#    define debug_eeprom debug_enable
#    define eeprom_println(s) println(s)
#    define eeprom_printf(fmt, ...) xprintf(fmt, ##__VA_ARGS__);

#else /* NO_DEBUG */

#    define debug_eeprom false
#    define eeprom_println(s)
#    define eeprom_printf(fmt, ...)

#endif /* NO_DEBUG */

/*****************************************************************************
 *  Delete Flash Space used for user Data, deletes the whole space between
 *  RW_PAGE_BASE_ADDRESS and the last uC Flash Page
 ******************************************************************************/
uint16_t EEPROM_Init(void) {
    // Clear Flags
    // SN_FLASH->STATUS &= ~FLASH_PGERR
    if (debug_eeprom) {
        println("EEPROM_Init");
    }

    return FEE_DENSITY_BYTES;
}

/*****************************************************************************
 *  Erase the whole reserved Flash Space used for user Data
 ******************************************************************************/
void EEPROM_Erase(void) {
    int page_num = 0;

    // delete all pages from specified start page to the last page
    do {
        eeprom_println("EEPROM_Erase");
        FLASH_EraseSector(FEE_PAGE_BASE_ADDRESS + (page_num * FEE_PAGE_SIZE));
        page_num++;
    } while (page_num < FEE_DENSITY_PAGES);
}

/*****************************************************************************
 *  Writes data to flash on specified address.
 *******************************************************************************/
uint8_t EEPROM_WriteDataByte(uint16_t Address, uint8_t DataByte) {
    FLASH_Status FlashStatus = FLASH_OKAY;

    /* if the address is out-of-bounds, do nothing */
    if (Address > FEE_DENSITY_BYTES) {
        eeprom_printf("EEPROM_WriteDataByte(0x%04x, 0x%02x) [BAD ADDRESS]\n", Address, DataByte);
        return FLASH_FAIL;
    }
    uint32_t addr = FEE_PAGE_BASE_ADDRESS + FEE_ADDR_OFFSET(Address);

    /* if the value is the same, don't bother writing it */
    if (DataByte == *(__IO uint8_t *)addr) {
        eeprom_printf("EEPROM_WriteDataByte(0x%04x, 0x%02x) [SKIP SAME]\n", Address, DataByte);
        return FLASH_OKAY;
    }

    // update the data byte aligned in a 32-bit dword
    uint32_t value = *((uint32_t *)(addr & 0xFFFFFFFC));
    uint8_t *v8    = (uint8_t *)&value;
    v8[addr & 3]   = DataByte;

    // program the 32-bit dword
    eeprom_printf("FLASH_ProgramDWord(0x%08x, 0x%04x) [DIRECT]\n", Address, value);
    FlashStatus = FLASH_ProgramDWord(addr & 0xFFFFFFFC, value);

    return FlashStatus;
}

/*****************************************************************************
 *  Read data from a specified address.
 *******************************************************************************/
uint8_t EEPROM_ReadDataByte(uint16_t Address) {
    uint8_t DataByte = 0xFF;

    if (Address <= FEE_DENSITY_BYTES) {
        // Get Byte from specified address
        DataByte = (*(__IO uint8_t *)(FEE_PAGE_BASE_ADDRESS + FEE_ADDR_OFFSET(Address)));
    }

    eeprom_printf("EEPROM_ReadDataByte(0x%04x): 0x%02x\n", Address, DataByte);

    return DataByte;
}

/*****************************************************************************
 *  Bind to eeprom_driver.c
 *******************************************************************************/
void eeprom_driver_init(void) {
    EEPROM_Init();
}

void eeprom_driver_erase(void) {
    EEPROM_Erase();
}

void eeprom_read_block(void *buf, const void *addr, size_t len) {
    const uint8_t *p    = (const uint8_t *)addr;
    uint8_t *      dest = (uint8_t *)buf;
    while (len--) {
        *dest++ = EEPROM_ReadDataByte((uint16_t)(uint32_t)(p++));
    }
}

void eeprom_write_block(const void *buf, void *addr, size_t len) {
    uint8_t *      p   = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        EEPROM_WriteDataByte((uint16_t)(uint32_t)p++, *src++);
    }
}
