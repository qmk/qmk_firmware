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
 * Modifications for QMK and STM32L432 by lalalademaxiya1 & lokher
 *
 * TODO: Add ECC correction interrupt handler.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "flash_stm32.h"
#include "eeprom_stm32_defs.h"
#include "eeprom_stm32_l4.h"
#include "print.h"
/*
 * We emulate eeprom by writing a snapshot compacted view of eeprom contents,
 * followed by a write log of any change since that snapshot:
 *
 * === SIMULATED EEPROM CONTENTS ===
 *
 * ┌─ Compacted─┬─ Write Log ──┐
 * │............│[DWord][DWord]│
 * │FFFF....FFFF│[DWord][DWord]│
 * │FFFFFFFFFFFF│[DWord][DWord]│
 * │....FFFFFFFF│[DWord][DWord]│
 * ├────────────┼──────────────┤
 * └──PAGE_BASE │              │
 *    PAGE_LAST─┴─WRITE_BASE   │
 *                WRITE_LAST ──┘
 *
 * Compacted contents are the 1's complement of the actual EEPROM contents.
 * e.g. An 'FFFF' represents a '0000' value.
 *
 * The size of the 'compacted' area is equal to the size of the 'emulated' eeprom.
 * The size of the compacted-area and write log are configurable, and the combined
 * size of Compacted + WriteLog is a multiple FEE_PAGE_SIZE, which is MCU dependent.
 * Simulated Eeprom contents are located at the end of available flash space.
 *
 * The following configuration defines can be set:
 *
 * FEE_PAGE_COUNT   # Total number of pages to use for eeprom simulation (Compact + Write log)
 * FEE_DENSITY_BYTES   # Size of simulated eeprom. (Defaults to one pages of FEE_PAGE_COUNT)
 * NOTE: The current implementation does not include page swapping,
 * and FEE_DENSITY_BYTES will consume that amount of RAM as a cached view of actual EEPROM contents.
 *
 * The maximum size of FEE_DENSITY_BYTES is currently 8192. The write log size equals
 * FEE_PAGE_COUNT * FEE_PAGE_SIZE - FEE_DENSITY_BYTES.
 * The larger the write log, the less frequently the compacted area needs to be rewritten.
 *
 *
 * *** General Algorithm ***
 *
 * During initialization:
 * The contents of the Compacted-flash area are loaded and the 1's complement value
 * is cached into memory (e.g. 0xFFFF in Flash represents 0x0000 in cache).
 * Write log entries are processed until a 0xFFFF is reached.
 * Each log entry updates 1/2/4 byte(s) in the cache.
 *
 * During reads:
 * EEPROM contents are given back directly from the cache in memory.
 *
 * During writes:
 * The contents of the cache is updated first.
 * If the Compacted-flash area corresponding to the write address is unprogrammed, the 1's complement of the value is written directly into Compacted-flash
 * Otherwise:
 * If the write log is full, erase both the Compacted-flash area and the Write log, then write cached contents to the Compacted-flash area.
 * Otherwise a Write log entry is constructed and appended to the next free position in the Write log.
 *
 *
 * *** Write Log Structure ***
 *
 * Each log entry compose of double word (2 x 32-bit) due to the minimum program size of STM32L432 flash.
 *
 * === WRITE LOG ENTRY FORMATS ===
 *
 * ╔══════════ Byte-Entry ═════════╗
 * ║ 00 01 XX XX   ║ FF FF FF YY   ║
 * ║ └─┬─┘ └─┬─┘   ║          └┘   ║
 * ║  Len  Address ║       ~Value  ║
 * ╚═══════════════╩═══════════════╝
 *
 * ╔══════════ Word-Entry ═════════╗
 * ║ 00 02 XX XX   ║ FF FF YY YY   ║
 * ║ └─┬─┘ └─┬─┘   ║       └─┬─┘   ║
 * ║  Len  Address ║      ~Value   ║
 * ╚═══════════════╩═══════════════╝
 *
 * ╔══════════ DWord-Entry  ═══════╗
 * ║ 00 04 XX XX   ║  FF FF FF FF  ║
 * ║ └─┬─┘ └─┬─┘   ║  └───┬────┘   ║
 * ║  Len  Address ║   ~Value      ║
 * ╚═══════════════╩═══════════════╝
 *
 */

#include "eeprom_stm32_defs.h"
#if !defined(FEE_PAGE_SIZE) || !defined(FEE_PAGE_COUNT) || !defined(FEE_MCU_FLASH_SIZE) || !defined(FEE_PAGE_BASE_ADDRESS)
#    error "not implemented."
#endif

/* These bits indicate that the length of data which was wrote to log space */
#define FEE_BYTE_FLAG 0x00010000
#define FEE_WORD_FLAG 0x00020000
#define FEE_DWORD_FLAG 0x00040000

/* Flash byte value after erase */
#define FEE_EMPTY_BYTE ((uint8_t)0xFF)
/* Flash double byte value after erase */
#define FEE_EMPTY_DBYTE ((uint16_t)0xFFFF)
/* Flash word value after erase */
#define FEE_EMPTY_WORD ((uint32_t)0xFFFFFFFF)
/* Flash double word value after erase */
#define FEE_EMPTY_DWORD ((uint64_t)0xFFFFFFFFFFFFFFFF)

/* Size of combined compacted eeprom and write log pages */
#define FEE_DENSITY_MAX_SIZE (FEE_PAGE_COUNT * FEE_PAGE_SIZE)

#ifndef FEE_MCU_FLASH_SIZE_IGNORE_CHECK /* *TODO: Get rid of this check */
#    if FEE_DENSITY_MAX_SIZE > (FEE_MCU_FLASH_SIZE * 1024)
#        pragma message STR(FEE_DENSITY_MAX_SIZE) " > " STR(FEE_MCU_FLASH_SIZE * 1024)
#        error emulated eeprom: FEE_DENSITY_MAX_SIZE is greater than available flash size
#    endif
#endif

/* Size of emulated eeprom */
#ifdef FEE_DENSITY_BYTES
#    if (FEE_DENSITY_BYTES > FEE_DENSITY_MAX_SIZE)
#        pragma message STR(FEE_DENSITY_BYTES) " > " STR(FEE_DENSITY_MAX_SIZE)
#        error emulated eeprom: FEE_DENSITY_BYTES exceeds FEE_DENSITY_MAX_SIZE
#    endif
#    if (FEE_DENSITY_BYTES == FEE_DENSITY_MAX_SIZE)
#        pragma message STR(FEE_DENSITY_BYTES) " == " STR(FEE_DENSITY_MAX_SIZE)
#        warning emulated eeprom: FEE_DENSITY_BYTES leaves no room for a write log.  This will greatly increase the flash wear rate!
#    endif
#    if FEE_DENSITY_BYTES > FEE_ADDRESS_MAX_SIZE
#        pragma message STR(FEE_DENSITY_BYTES) " > " STR(FEE_ADDRESS_MAX_SIZE)
#        error emulated eeprom: FEE_DENSITY_BYTES is greater than FEE_ADDRESS_MAX_SIZE allows
#    endif
#    if ((FEE_DENSITY_BYTES) % 8) != 0
#        error emulated eeprom: FEE_DENSITY_BYTES must be a multiple of 8
#    endif
#else
/* Default to one page of allocated space used for emulated eeprom, 3 pages for write log */
#    define FEE_DENSITY_BYTES FEE_PAGE_SIZE
#endif

/* Size of write log */
#ifdef FEE_WRITE_LOG_BYTES
#    if ((FEE_DENSITY_BYTES + FEE_WRITE_LOG_BYTES) > FEE_DENSITY_MAX_SIZE)
#        pragma message STR(FEE_DENSITY_BYTES) " + " STR(FEE_WRITE_LOG_BYTES) " > " STR(FEE_DENSITY_MAX_SIZE)
#        error emulated eeprom: FEE_WRITE_LOG_BYTES exceeds remaining FEE_DENSITY_MAX_SIZE
#    endif
#    if ((FEE_WRITE_LOG_BYTES) % 8) != 0
#        error emulated eeprom: FEE_WRITE_LOG_BYTES must be a multiple of 8
#    endif
#else
/* Default to use all remaining space */
#    define FEE_WRITE_LOG_BYTES (FEE_PAGE_COUNT * FEE_PAGE_SIZE - FEE_DENSITY_BYTES)
#endif

/* In-memory contents of emulated eeprom for faster access */
/* *TODO: Implement page swapping */
static uint64_t DWordBuf[FEE_DENSITY_BYTES / 8];
static uint8_t *DataBuf = (uint8_t *)DWordBuf;

/* Pointer to the first available slot within the write log */
static uint32_t *empty_slot;
/* ECC error flag, set in NMI when 2 bits ECC error is detected */
static bool eccd;

/* Start of the emulated eeprom compacted flash area */
#define FEE_COMPACTED_BASE_ADDRESS FEE_PAGE_BASE_ADDRESS
/* End of the emulated eeprom compacted flash area */
#define FEE_COMPACTED_LAST_ADDRESS (FEE_COMPACTED_BASE_ADDRESS + FEE_DENSITY_BYTES)
/* Start of the emulated eeprom write log */
#define FEE_WRITE_LOG_BASE_ADDRESS FEE_COMPACTED_LAST_ADDRESS
/* End of the emulated eeprom write log */
#define FEE_WRITE_LOG_LAST_ADDRESS (FEE_WRITE_LOG_BASE_ADDRESS + FEE_WRITE_LOG_BYTES)

uint16_t EEPROM_Init(void) {
    eccd = false;

    /* Load emulated eeprom contents from compacted flash into memory */
    uint32_t *src  = (uint32_t *)FEE_COMPACTED_BASE_ADDRESS;
    uint32_t *dest = (uint32_t *)DataBuf;
    for (; src < (uint32_t *)FEE_COMPACTED_LAST_ADDRESS; ++src, ++dest) {
        *dest = ~*src;
    }

    /* Replay write log */
    uint32_t *log_addr;
    for (log_addr = (uint32_t *)FEE_WRITE_LOG_BASE_ADDRESS; log_addr < (uint32_t *)FEE_WRITE_LOG_LAST_ADDRESS; log_addr += 2) {
        uint32_t address = *log_addr;

        uint32_t data = ~*(log_addr + 1);

        /* Break loop if ECC error is detected */
        if (eccd) break;

        if (address == FEE_EMPTY_WORD) {
            break;
        }
        /* Check if value is in bytes */
        else if ((address & FEE_BYTE_FLAG) == FEE_BYTE_FLAG) {
            uint8_t  value = (uint8_t)(data & 0xFF);
            uint16_t addr  = (uint16_t)address;
            DataBuf[addr]  = value;
        }
        /* Check if value is in words */
        else if ((address & FEE_WORD_FLAG) == FEE_WORD_FLAG) {
            uint16_t value                = (uint16_t)(data & 0xFFFF);
            uint16_t addr                 = (uint16_t)address;
            *(uint16_t *)(&DataBuf[addr]) = value;
        }
        /* Check if value is in double words */
        else if ((address & FEE_DWORD_FLAG) == FEE_DWORD_FLAG) {
            uint32_t value                = data;
            uint16_t addr                 = (uint16_t)address;
            *(uint32_t *)(&DataBuf[addr]) = value;
        }
    }

    empty_slot = log_addr;

    /* Give more chance for NMI interrupt */
    asm("nop");

    /* Reset eeprom data if ECC error is detected*/
    if (eccd) return 0;

    return FEE_DENSITY_BYTES;
}

/* Clear flash contents (doesn't touch in-memory DataBuf) */
static void eeprom_clear(void) {
    FLASH_Unlock();

    for (uint16_t page_num = 0; page_num < FEE_PAGE_COUNT; ++page_num) {
        FLASH_ErasePage(FEE_PAGE_BASE_ADDRESS + (page_num * FEE_PAGE_SIZE));
    }

    FLASH_Lock();

    empty_slot = (uint32_t *)FEE_WRITE_LOG_BASE_ADDRESS;
}

/* Erase emulated eeprom */
void EEPROM_Erase(void) {
    /* Erase compacted pages and write log */
    eeprom_clear();
    /* re-initialize to reset DataBuf */
    EEPROM_Init();
}

/* Compact write log */
static uint8_t eeprom_compact(void) {
    /* Erase compacted pages and write log */
    eeprom_clear();

    FLASH_Unlock();

    FLASH_Status final_status = FLASH_COMPLETE;

    /* Write emulated eeprom contents from memory to compacted flash */
    uint64_t *src  = (uint64_t *)DataBuf;
    uint32_t  dest = FEE_COMPACTED_BASE_ADDRESS;
    uint64_t  value;
    for (; dest < FEE_COMPACTED_LAST_ADDRESS; ++src, dest += 8) {
        value = *src;
        if (value) {
            FLASH_Status status = FLASH_ProgramDoubleWord(dest, ~value);
            if (status != FLASH_COMPLETE) final_status = status;
        }
    }

    FLASH_Lock();

    return final_status;
}

static uint8_t eeprom_write_direct_entry(uint16_t Address) {
    /* Check if we can just write this directly to the compacted flash area */
    uint32_t directAddress = FEE_COMPACTED_BASE_ADDRESS + (Address & 0xFFF8);

    /* Write the value directly to the compacted area without a log entry */
    if (*(uint64_t *)directAddress == FEE_EMPTY_DWORD) {
        /* Write the value directly to the compacted area without a log entry */
        uint64_t value = ~*(uint64_t *)(&DataBuf[Address & 0xFFF8]);

        /* Early exit if a write isn't needed */
        if (value == FEE_EMPTY_DWORD) return FLASH_COMPLETE;

        FLASH_Unlock();

        /* write to flash */
        FLASH_Status status = FLASH_ProgramDoubleWord(directAddress, value);

        FLASH_Lock();

        return status;
    }
    return 0;
}

static void blank_check(uint32_t Address) {
    /* Align address to 64 bit */
    Address &= (~0x07);

    /* Check if target address is blank */
    if (*(uint64_t *)(Address) != 0xFFFFFFFFFFFFFFFF) {
        if ((Address & (FEE_PAGE_SIZE - 1)) == 0) {
            /* Erase current page if first byte is not empty */
            FLASH_Unlock();
            FLASH_ErasePage(Address);
            FLASH_Lock();
        } else {
            /* Compact data if we encounter non empty target address after page head */
            eeprom_compact();
        }
    }
}

static uint8_t eeprom_write_log_byte_entry(uint16_t Address) {
    /* if we can't find an empty spot, we must compact emulated eeprom */
    if (empty_slot >= (uint32_t *)FEE_WRITE_LOG_LAST_ADDRESS) {
        /* compact the write log into the compacted flash area */
        return eeprom_compact();
    }

    blank_check((uint32_t)empty_slot);

    FLASH_Unlock();

    /* Pack address and value into the same word */
    uint64_t value = (((uint64_t)(~DataBuf[Address])) << 32) | (FEE_BYTE_FLAG) | Address;

    /* write to flash */
    FLASH_Status status = FLASH_ProgramDoubleWord((uint32_t)empty_slot, value);

    empty_slot += 2;

    FLASH_Lock();

    return status;
}

static uint8_t eeprom_write_log_word_entry(uint16_t Address) {
    /* if we can't find an empty spot, we must compact emulated eeprom */
    if (empty_slot >= (uint32_t *)FEE_WRITE_LOG_LAST_ADDRESS) {
        /* compact the write log into the compacted flash area */
        return eeprom_compact();
    }

    blank_check((uint32_t)empty_slot);

    FLASH_Unlock();

    /* Pack address and value into the same word */
    uint64_t value = (((uint64_t)(~(*(uint16_t *)&DataBuf[Address]))) << 32) | (FEE_WORD_FLAG) | Address;

    /* write to flash */
    FLASH_Status status = FLASH_ProgramDoubleWord((uint32_t)empty_slot, value);

    empty_slot += 2;

    FLASH_Lock();

    return status;
}

static uint8_t eeprom_write_log_dword_entry(uint16_t Address) {
    /* if we can't find an empty spot, we must compact emulated eeprom */
    if (empty_slot >= (uint32_t *)FEE_WRITE_LOG_LAST_ADDRESS) {
        /* compact the write log into the compacted flash area */
        return eeprom_compact();
    }

    blank_check((uint32_t)empty_slot);

    FLASH_Unlock();

    /* Pack address and value into the same word */
    uint64_t value = (((uint64_t)(~(*(uint32_t *)&DataBuf[Address]))) << 32) | (FEE_DWORD_FLAG) | Address;

    /* write to flash */
    FLASH_Status status = FLASH_ProgramDoubleWord((uint32_t)empty_slot, value);

    empty_slot += 2;

    FLASH_Lock();

    return status;
}

uint8_t EEPROM_WriteDataByte(uint16_t Address, uint8_t DataByte) {
    /* if the address is out-of-bounds, do nothing */
    if (Address >= (FEE_DENSITY_BYTES)) {
        return FLASH_BAD_ADDRESS;
    }

    /* if the value is the same, don't bother writing it */
    if (DataBuf[Address] == DataByte) {
        return 0;
    }

    /* keep DataBuf cache in sync */
    DataBuf[Address] = DataByte;

    /* perform the write into flash memory */
    /* First, attempt to write directly into the compacted flash area */
    FLASH_Status status = eeprom_write_direct_entry(Address);

    if (!status) {
        status = eeprom_write_log_byte_entry(Address);
    }

    return status;
}

uint8_t EEPROM_WriteDataWord(uint16_t Address, uint16_t DataWord) {
    /* if the address is out-of-bounds, do nothing */
    if (Address >= (FEE_DENSITY_BYTES - 1)) {
        return FLASH_BAD_ADDRESS;
    }

    /* if the value is the same, don't bother writing it */
    if (*(uint16_t *)&DataBuf[Address] == DataWord) {
        return 0;
    }

    /* keep DataBuf cache in sync */
    *(uint16_t *)(&DataBuf[Address]) = DataWord;

    /* perform the write into flash memory */
    /* First, attempt to write directly into the compacted flash area */
    FLASH_Status status = eeprom_write_direct_entry(Address);

    if (!status) {
        status = eeprom_write_log_word_entry(Address);
    }

    return status;
}

uint8_t EEPROM_WriteDataDWord(uint16_t Address, uint32_t DataDWord) {
    /* if the address is out-of-bounds, do nothing */
    if (Address >= (FEE_DENSITY_BYTES - 3)) {
        return FLASH_BAD_ADDRESS;
    }

    /* if the value is the same, don't bother writing it */
    if (*(uint32_t *)&DataBuf[Address] == DataDWord) {
        return 0;
    }

    /* keep DataBuf cache in sync */
    *(uint32_t *)&DataBuf[Address] = DataDWord;

    /* perform the write into flash memory */
    /* First, attempt to write directly into the compacted flash area */
    FLASH_Status status = eeprom_write_direct_entry(Address);

    if (!status) {
        status = eeprom_write_log_dword_entry(Address);
    }

    return status;
}

uint8_t EEPROM_ReadDataByte(uint16_t Address) {
    uint8_t DataByte = 0xFF;

    if (Address < FEE_DENSITY_BYTES) {
        DataByte = DataBuf[Address];
    }

    return DataByte;
}

uint16_t EEPROM_ReadDataWord(uint16_t Address) {
    uint16_t DataWord = 0xFFFF;

    if (Address < FEE_DENSITY_BYTES - 1) {
        /* Check word alignment */
        if (Address % 2) {
            DataWord = DataBuf[Address] | (DataBuf[Address + 1] << 8);
        } else {
            DataWord = *(uint16_t *)(&DataBuf[Address]);
        }
    }

    return DataWord;
}

/*****************************************************************************
 *  Bind to eeprom_driver.c
 *******************************************************************************/
uint16_t eeprom_driver_init(void) {
    return EEPROM_Init();
}

void eeprom_driver_erase(void) {
    EEPROM_Erase();
}

void eeprom_read_block(void *buf, const void *addr, size_t len) {
    const uint8_t *src  = (const uint8_t *)addr;
    uint8_t *      dest = (uint8_t *)buf;

    /* Check word alignment */
    if (len && (uint32_t)src % 2) {
        /* Read the unaligned first byte */
        *dest++ = EEPROM_ReadDataByte((const uintptr_t)((uint16_t *)src));
        --len;
    }

    uint16_t value;
    bool     aligned = ((uint32_t)dest % 2 == 0);
    while (len > 1) {
        value = EEPROM_ReadDataWord((const uintptr_t)((uint16_t *)src));
        if (aligned) {
            *(uint16_t *)dest = value;
            dest += 2;
        } else {
            *dest++ = value;
            *dest++ = value >> 8;
        }
        src += 2;
        len -= 2;
    }
    if (len) {
        *dest = EEPROM_ReadDataByte((const uintptr_t)src);
    }
}

void eeprom_write_block(const void *buf, void *addr, size_t len) {
    uint8_t *      dest = (uint8_t *)addr;
    const uint8_t *src  = (const uint8_t *)buf;
    uint8_t        write_len;

    while (len > 0) {
        /* Check and try to write double word fisrt */
        if ((uintptr_t)dest % 4 == 0 && len >= 4) {
            uint32_t dwvalue;
            bool     dwaligned = ((uint32_t)src % 4 == 0);

            if (dwaligned) {
                dwvalue = *(uint32_t *)src;
            } else {
                dwvalue = *(uint8_t *)src | (*(uint8_t *)(src + 1) << 8) | (*(uint8_t *)(src + 2) << 16) | (*(uint8_t *)(src + 3) << 24);
            }
            EEPROM_WriteDataDWord((uintptr_t)((uint16_t *)dest), dwvalue);
            write_len = 4;
        }
        /* Check and try to write word */
        else if ((uintptr_t)dest % 2 == 0 && len >= 2) {
            uint16_t wvalue;
            bool     waligned = ((uintptr_t)src % 2 == 0);

            if (waligned) {
                wvalue = *(uint16_t *)src;
            } else {
                wvalue = *(uint8_t *)src | (*(uint8_t *)(src + 1) << 8);
            }
            EEPROM_WriteDataWord((uintptr_t)((uint16_t *)dest), wvalue);
            write_len = 2;
        } else {
            /* Write the unaligned or single byte */
            EEPROM_WriteDataByte((uintptr_t)dest, *src);
            write_len = 1;
        }

        dest += write_len;
        src += write_len;
        len -= write_len;
    }
}

void NMI_Handler(void) {
    if (FLASH->ECCR & FLASH_ECCR_ECCD) {
        /* Clear ECCD error NMI */
        FLASH->ECCR = FLASH_ECCR_ECCD;
        eccd        = true;
    }
}
