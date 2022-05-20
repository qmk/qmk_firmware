/* Copyright (C) 2021 Westberry Technology (ChangZhou) Corp., Ltd
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

#include <stdio.h>
#include <stdbool.h>
#include "util.h"
#include "debug.h"
#include "wait.h"
#include "timer.h"
#include "eeprom.h"
#include "flash_spi.h"

/*
 * We emulate eeprom by writing a snapshot compacted view of eeprom contents,
 * followed by a write log of any change since that snapshot:
 *
 * === SIMULATED EEPROM CONTENTS ===
 *
 * ┌─ Compacted ┬ Write Log ─┐
 * │............│[BYTE][BYTE]│
 * │FFFF....FFFF│[WRD0][WRD1]│
 * │FFFFFFFFFFFF│[WORD][NEXT]│
 * │....FFFFFFFF│[BYTE][WRD0]│
 * ├────────────┼────────────┤
 * └──PAGE_BASE │            │
 *    PAGE_LAST─┴─WRITE_BASE │
 *                WRITE_LAST ┘
 *
 * Compacted contents are the 1's complement of the actual EEPROM contents.
 * e.g. An 'FFFF' represents a '0000' value.
 *
 * The size of the 'compacted' area is equal to the size of the 'emulated' eeprom.
 * The size of the compacted-area and write log are configurable, and the combined
 * size of Compacted + WriteLog is a multiple EXTERNAL_FLASH_PAGE_SIZE, which is MCU dependent.
 * Simulated Eeprom contents are located at the end of available flash space.
 *
 * The following configuration defines can be set:
 *
 * EXTERNAL_FLASH_PAGE_COUNT   # Total number of pages to use for eeprom simulation (Compact + Write log)
 * FEE_DENSITY_BYTES   # Size of simulated eeprom. (Defaults to half the space allocated by EXTERNAL_FLASH_PAGE_COUNT)
 * NOTE: The current implementation does not include page swapping,
 * and FEE_DENSITY_BYTES will consume that amount of RAM as a cached view of actual EEPROM contents.
 *
 * The maximum size of FEE_DENSITY_BYTES is currently 16384. The write log size equals
 * EXTERNAL_FLASH_PAGE_COUNT * EXTERNAL_FLASH_PAGE_SIZE - FEE_DENSITY_BYTES.
 * The larger the write log, the less frequently the compacted area needs to be rewritten.
 *
 *
 * *** General Algorithm ***
 *
 * During initialization:
 * The contents of the Compacted-flash area are loaded and the 1's complement value
 * is cached into memory (e.g. 0xFFFF in Flash represents 0x0000 in cache).
 * Write log entries are processed until a 0xFFFF is reached.
 * Each log entry updates a byte or word in the cache.
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
 * Write log entries allow for optimized byte writes to addresses below 128. Writing 0 or 1 words are also optimized when word-aligned.
 *
 * === WRITE LOG ENTRY FORMATS ===
 *
 * ╔═══ Byte-Entry ══╗
 * ║0XXXXXXX║YYYYYYYY║
 * ║ └──┬──┘║└──┬───┘║
 * ║ Address║ Value  ║
 * ╚════════╩════════╝
 * 0 <= Address < 0x80 (128)
 *
 * ╔ Word-Encoded 0 ╗
 * ║100XXXXXXXXXXXXX║
 * ║  │└─────┬─────┘║
 * ║  │Address >> 1 ║
 * ║  └── Value: 0  ║
 * ╚════════════════╝
 * 0 <= Address <= 0x3FFE (16382)
 *
 * ╔ Word-Encoded 1 ╗
 * ║101XXXXXXXXXXXXX║
 * ║  │└─────┬─────┘║
 * ║  │Address >> 1 ║
 * ║  └── Value: 1  ║
 * ╚════════════════╝
 * 0 <= Address <= 0x3FFE (16382)
 *
 * ╔═══ Reserved ═══╗
 * ║110XXXXXXXXXXXXX║
 * ╚════════════════╝
 *
 * ╔═══════════ Word-Next ═══════════╗
 * ║111XXXXXXXXXXXXX║YYYYYYYYYYYYYYYY║
 * ║   └─────┬─────┘║└───────┬──────┘║
 * ║(Address-128)>>1║     ~Value     ║
 * ╚════════════════╩════════════════╝
 * (  0 <= Address <  0x0080 (128): Reserved)
 * 0x80 <= Address <= 0x3FFE (16382)
 *
 * Write Log entry ranges:
 * 0x0000 ... 0x7FFF - Byte-Entry;     address is (Entry & 0x7F00) >> 4; value is (Entry & 0xFF)
 * 0x8000 ... 0x9FFF - Word-Encoded 0; address is (Entry & 0x1FFF) << 1; value is 0
 * 0xA000 ... 0xBFFF - Word-Encoded 1; address is (Entry & 0x1FFF) << 1; value is 1
 * 0xC000 ... 0xDFFF - Reserved
 * 0xE000 ... 0xFFBF - Word-Next;      address is (Entry & 0x1FFF) << 1 + 0x80; value is ~(Next_Entry)
 * 0xFFC0 ... 0xFFFE - Reserved
 * 0xFFFF            - Unprogrammed
 *
 */

/* These bits are used for optimizing encoding of bytes, 0 and 1 */
#define FEE_WORD_ENCODING 0x8000
#define FEE_VALUE_NEXT 0x6000
#define FEE_VALUE_RESERVED 0x4000
#define FEE_VALUE_ENCODED 0x2000
#define FEE_BYTE_RANGE 0x80

/* Addressable range 16KByte: 0 <-> (0x1FFF << 1) */
#define FEE_ADDRESS_MAX_SIZE 0x4000

/* Flash word value after erase */
#define FEE_EMPTY_WORD ((uint16_t)0xFFFF)

/* Size of combined compacted eeprom and write log pages */
#define FEE_DENSITY_MAX_SIZE (EXTERNAL_FLASH_PAGE_COUNT * EXTERNAL_FLASH_PAGE_SIZE)

#ifndef EXTERNAL_FLASH_SIZE_IGNORE_CHECK /* *TODO: Get rid of this check */
#    if FEE_DENSITY_MAX_SIZE > (EXTERNAL_FLASH_SIZE * 1024)
#        pragma message STR(FEE_DENSITY_MAX_SIZE) " > " STR(EXTERNAL_FLASH_SIZE * 1024)
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
#    if ((FEE_DENSITY_BYTES) % 2) == 1
#        error emulated eeprom: FEE_DENSITY_BYTES must be even
#    endif
#else
/* Default to half of allocated space used for emulated eeprom, half for write log */
#    define FEE_DENSITY_BYTES (EXTERNAL_FLASH_PAGE_COUNT * (EXTERNAL_FLASH_PAGE_SIZE >> 1))
#endif

/* Size of write log */
#ifdef FEE_WRITE_LOG_BYTES
#    if ((FEE_DENSITY_BYTES + FEE_WRITE_LOG_BYTES) > FEE_DENSITY_MAX_SIZE)
#        pragma message STR(FEE_DENSITY_BYTES) " + " STR(FEE_WRITE_LOG_BYTES) " > " STR(FEE_DENSITY_MAX_SIZE)
#        error emulated eeprom: FEE_WRITE_LOG_BYTES exceeds remaining FEE_DENSITY_MAX_SIZE
#    endif
#    if ((FEE_WRITE_LOG_BYTES) % 2) == 1
#        error emulated eeprom: FEE_WRITE_LOG_BYTES must be even
#    endif
#else
/* Default to use all remaining space */
#    define FEE_WRITE_LOG_BYTES (EXTERNAL_FLASH_PAGE_COUNT * EXTERNAL_FLASH_PAGE_SIZE - FEE_DENSITY_BYTES)
#endif

#define EXTERNAL_FLASH_PAGE_BASE_ADDRESS 0
/* Start of the emulated eeprom compacted flash area */
#define FEE_COMPACTED_BASE_ADDRESS EXTERNAL_FLASH_PAGE_BASE_ADDRESS
/* End of the emulated eeprom compacted flash area */
#define FEE_COMPACTED_LAST_ADDRESS (FEE_COMPACTED_BASE_ADDRESS + FEE_DENSITY_BYTES)
/* Start of the emulated eeprom write log */
#define FEE_WRITE_LOG_BASE_ADDRESS FEE_COMPACTED_LAST_ADDRESS
/* End of the emulated eeprom write log */
#define FEE_WRITE_LOG_LAST_ADDRESS (FEE_WRITE_LOG_BASE_ADDRESS + FEE_WRITE_LOG_BYTES)

#if defined(DYNAMIC_KEYMAP_EEPROM_MAX_ADDR) && (DYNAMIC_KEYMAP_EEPROM_MAX_ADDR >= FEE_DENSITY_BYTES)
#    error emulated eeprom: DYNAMIC_KEYMAP_EEPROM_MAX_ADDR is greater than the FEE_DENSITY_BYTES available
#endif

/* In-memory contents of emulated eeprom for faster access */
/* *TODO: Implement page swapping */
uint16_t WordBuf[FEE_DENSITY_BYTES / 2] = {0xFFFF};
static uint8_t *DataBuf = (uint8_t *)WordBuf;

/* Pointer to the first available slot within the write log */
static uint16_t *empty_slot;

#define DEBUG_EEPROM_OUTPUT

/*
 * Debug print utils
 */

#if defined(DEBUG_EEPROM_OUTPUT)

#    define debug_eeprom debug_enable
#    define eeprom_println(s) println(s)
#    define eeprom_printf(fmt, ...) dprintf(fmt, ##__VA_ARGS__)

#else /* NO_DEBUG */

#    define debug_eeprom false
#    define eeprom_println(s)
#    define eeprom_printf(fmt, ...)

#endif /* NO_DEBUG */

void print_eeprom(void) {
#ifndef NO_DEBUG
    int empty_rows = 0;
    for (uint16_t i = 0; i < FEE_DENSITY_BYTES; i++) {
        if (i % 16 == 0) {
            if (i >= FEE_DENSITY_BYTES - 16) {
                /* Make sure we display the last row */
                empty_rows = 0;
            }
            /* Check if this row is uninitialized */
            ++empty_rows;
            for (uint16_t j = 0; j < 16; j++) {
                if (DataBuf[i + j]) {
                    empty_rows = 0;
                    break;
                }
            }
            if (empty_rows > 1) {
                /* Repeat empty row */
                if (empty_rows == 2) {
                    /* Only display the first repeat empty row */
                    println("*");
                }
                i += 15;
                continue;
            }
            xprintf("%04x", i);
        }
        if (i % 8 == 0) print(" ");

        xprintf(" %02x", DataBuf[i]);
        if ((i + 1) % 16 == 0) {
            println("");
        }
    }
#endif
}

static flash_status_t external_flash_program_half_word(uint32_t addr, uint16_t value) {
    uint8_t *src  = (uint8_t *)&value;

    return flash_write_block(addr, src, 2);
}

static uint32_t EEPROM_Init(void) {
    /* Load emulated eeprom contents from compacted flash into memory */
    uint32_t src  = (uint32_t)FEE_COMPACTED_BASE_ADDRESS;
    uint16_t *dest = (uint16_t *)DataBuf;

    flash_read_block(src, (uint8_t *)dest, FEE_COMPACTED_LAST_ADDRESS - FEE_COMPACTED_BASE_ADDRESS);

    for (int i = 0; i < ((FEE_COMPACTED_LAST_ADDRESS - FEE_COMPACTED_BASE_ADDRESS) >> 1); i++, ++dest) {
        *dest = ~*dest;
    }

    if (debug_eeprom) {
        println("EEPROM_Init Compacted Pages:");
        print_eeprom();
        println("EEPROM_Init Write Log:");
    }

    /* Replay write log */
    uint16_t *log_addr;
    for (log_addr = (uint16_t *)FEE_WRITE_LOG_BASE_ADDRESS; log_addr < (uint16_t *)FEE_WRITE_LOG_LAST_ADDRESS; ++log_addr) {
        uint16_t address;

        flash_read_block((uint32_t)log_addr, (uint8_t *)&address, 0x02);
        if (address == FEE_EMPTY_WORD) {
            break;
        }
        /* Check for lowest 128-bytes optimization */
        if (!(address & FEE_WORD_ENCODING)) {
            uint8_t bvalue = (uint8_t)address;
            address >>= 8;
            DataBuf[address] = bvalue;
            eeprom_printf("DataBuf[0x%02x] = 0x%02x;\n", address, bvalue);
        } else {
            uint16_t wvalue;

            /* Check if value is in next word */
            if ((address & FEE_VALUE_NEXT) == FEE_VALUE_NEXT) {
                /* Read value from next word */
                if (++log_addr >= (uint16_t *)FEE_WRITE_LOG_LAST_ADDRESS) {
                    break;
                }
                flash_read_block((uint32_t)log_addr, (uint8_t *)&wvalue, 0x02);
                wvalue = ~wvalue;
                if (!wvalue) {
                    eeprom_printf("Incomplete write at log_addr: 0x%04x;\n", (uint32_t)log_addr);
                    /* Possibly incomplete write.  Ignore and continue */
                    continue;
                }
                address &= 0x1FFF;
                address <<= 1;
                /* Writes to addresses less than 128 are byte log entries */
                address += FEE_BYTE_RANGE;
            } else {
                /* Reserved for future use */
                if (address & FEE_VALUE_RESERVED) {
                    eeprom_printf("Reserved encoded value at log_addr: 0x%04x;\n", (uint32_t)log_addr);
                    continue;
                }

                /* Optimization for 0 or 1 values. */
                wvalue = (address & FEE_VALUE_ENCODED) >> 13;
                address &= 0x1FFF;
                address <<= 1;
            }
            if (address < FEE_DENSITY_BYTES) {
                eeprom_printf("DataBuf[0x%04x] = 0x%04x;\n", address, wvalue);
                *(uint16_t *)(&DataBuf[address]) = wvalue;
            } else {
                eeprom_printf("DataBuf[0x%04x] cannot be set to 0x%04x [BAD ADDRESS]\n", address, wvalue);
            }
        }
    }

    empty_slot = log_addr;

    if (debug_eeprom) {
        println("EEPROM_Init Final DataBuf:");
        print_eeprom();
    }

    return (uint32_t)FEE_DENSITY_BYTES;
}

/* Clear flash contents (doesn't touch in-memory DataBuf) */
static void eeprom_clear(void) {
    uint32_t erase_addr = EXTERNAL_FLASH_PAGE_BASE_ADDRESS;

    for ( ; erase_addr < (uint32_t)(EXTERNAL_FLASH_SIZE);) {

        if (erase_addr % ((uint32_t)(EXTERNAL_FLASH_SECTOR_SIZE)) != 0) {
            eeprom_printf("The external Flash address to be erased is incorrect: 0x%08x\n", (uint32_t)erase_addr);
            break;
        }
        flash_erase_sector(erase_addr);
        erase_addr += (uint32_t)(EXTERNAL_FLASH_SECTOR_SIZE);
    }

    empty_slot = (uint16_t *)FEE_WRITE_LOG_BASE_ADDRESS;
    eeprom_printf("eeprom_clear empty_slot: 0x%08x\n", (uint32_t)empty_slot);
}

/* Erase emulated eeprom */
void EEPROM_Erase(void) {
    eeprom_println("EEPROM_Erase");
    /* Erase compacted pages and write log */
    eeprom_clear();
    /* re-initialize to reset DataBuf */
    EEPROM_Init();
}

/* Compact write log */
static uint8_t eeprom_compact(void) {
    /* Erase compacted pages and write log */
    eeprom_clear();

    flash_status_t final_status = FLASH_STATUS_SUCCESS;

    /* Write emulated eeprom contents from memory to compacted flash */
    uint16_t *src  = (uint16_t *)DataBuf;
    uintptr_t dest = FEE_COMPACTED_BASE_ADDRESS;
    uint16_t  value;
    for (; dest < FEE_COMPACTED_LAST_ADDRESS; ++src, dest += 2) {
        value = *src;
        if (value) {
            eeprom_printf("external_flash_program_half_word(0x%04x, 0x%04x)\n", (uint32_t)dest, ~value);
            flash_status_t status = external_flash_program_half_word(dest, ~value);
            if (status != FLASH_STATUS_SUCCESS) final_status = status;
        }
    }

    if (debug_eeprom) {
        println("eeprom_compacted:");
        print_eeprom();
    }

    return final_status;
}

static uint8_t eeprom_write_direct_entry(uint16_t Address) {
    /* Check if we can just write this directly to the compacted flash area */
    uint32_t directAddress = FEE_COMPACTED_BASE_ADDRESS + (Address & 0xFFFE);
    uint16_t wvalue;

    flash_read_block(directAddress, (uint8_t *)&wvalue, 0x02);
    if (wvalue == FEE_EMPTY_WORD) {
        /* Write the value directly to the compacted area without a log entry */
        wvalue = ~*(uint16_t *)(&DataBuf[Address & 0xFFFE]);

        /* Early exit if a write isn't needed */
        if (wvalue == FEE_EMPTY_WORD) return FLASH_STATUS_SUCCESS;

        eeprom_printf("external_flash_program_half_word(0x%08x, 0x%04x) [DIRECT]\n", directAddress, wvalue);
        flash_status_t status = external_flash_program_half_word(directAddress, wvalue);

        return status;
    }
    return 0;
}

static uint8_t eeprom_write_log_word_entry(uint16_t Address) {
    flash_status_t final_status = FLASH_STATUS_SUCCESS;

    uint16_t value = *(uint16_t *)(&DataBuf[Address]);
    eeprom_printf("eeprom_write_log_word_entry(0x%04x): 0x%04x\n", Address, value);

    /* MSB signifies the lowest 128-byte optimization is not in effect */
    uint16_t encoding = FEE_WORD_ENCODING;
    uint8_t  entry_size;
    if (value <= 1) {
        encoding |= value << 13;
        entry_size = 2;
    } else {
        encoding |= FEE_VALUE_NEXT;
        entry_size = 4;
        /* Writes to addresses less than 128 are byte log entries */
        Address -= FEE_BYTE_RANGE;
    }

    /* if we can't find an empty spot, we must compact emulated eeprom */
    if (empty_slot > (uint16_t *)(FEE_WRITE_LOG_LAST_ADDRESS - entry_size)) {
        /* compact the write log into the compacted flash area */
        return eeprom_compact();
    }

    /* Word log writes should be word-aligned.  Take back a bit */
    Address >>= 1;
    Address |= encoding;

    /* ok we found a place let's write our data */

    /* address */
    eeprom_printf("external_flash_program_half_word(0x%08x, 0x%04x)\n", (uint32_t)empty_slot, Address);
    final_status = external_flash_program_half_word((uintptr_t)empty_slot++, Address);

    /* value */
    if (encoding == (FEE_WORD_ENCODING | FEE_VALUE_NEXT)) {
        eeprom_printf("external_flash_program_half_word(0x%08x, 0x%04x)\n", (uint32_t)empty_slot, ~value);
        flash_status_t status = external_flash_program_half_word((uintptr_t)empty_slot++, ~value);
        if (status != FLASH_STATUS_SUCCESS) final_status = status;
    }

    return final_status;
}

static uint8_t eeprom_write_log_byte_entry(uint16_t Address) {
    eeprom_printf("eeprom_write_log_byte_entry(0x%04x): 0x%02x\n", Address, DataBuf[Address]);

    /* if couldn't find an empty spot, we must compact emulated eeprom */
    if (empty_slot >= (uint16_t *)FEE_WRITE_LOG_LAST_ADDRESS) {
        /* compact the write log into the compacted flash area */
        return eeprom_compact();
    }

    /* ok we found a place let's write our data */

    /* Pack address and value into the same word */
    uint16_t value = (Address << 8) | DataBuf[Address];

    /* write to flash */
    eeprom_printf("external_flash_program_half_word(0x%08x, 0x%04x)\n", (uint32_t)empty_slot, value);
    flash_status_t status = external_flash_program_half_word((uintptr_t)empty_slot++, value);

    return status;
}

flash_status_t EEPROM_WriteDataByte(uint16_t Address, uint8_t DataByte) {
    /* if the address is out-of-bounds, do nothing */
    if (Address >= FEE_DENSITY_BYTES) {
        eeprom_printf("EEPROM_WriteDataByte(0x%04x, 0x%02x) [BAD ADDRESS]\n", Address, DataByte);
        return FLASH_STATUS_BAD_ADDRESS;
    }

    /* if the value is the same, don't bother writing it */
    if (DataBuf[Address] == DataByte) {
        eeprom_printf("EEPROM_WriteDataByte(0x%04x, 0x%02x) [SKIP SAME]\n", Address, DataByte);
        return FLASH_STATUS_SUCCESS;
    }

    /* keep DataBuf cache in sync */
    DataBuf[Address] = DataByte;
    eeprom_printf("EEPROM_WriteDataByte DataBuf[0x%04x] = 0x%02x\n", Address, DataBuf[Address]);

    /* perform the write into flash memory */
    /* First, attempt to write directly into the compacted flash area */
    flash_status_t status = eeprom_write_direct_entry(Address);
    if (!status) {
        /* Otherwise append to the write log */
        if (Address < FEE_BYTE_RANGE) {
            status = eeprom_write_log_byte_entry(Address);
        } else {
            status = eeprom_write_log_word_entry(Address & 0xFFFE);
        }
    }
    if (status != 0 && status != FLASH_STATUS_SUCCESS) {
        eeprom_printf("EEPROM_WriteDataByte [STATUS == %d]\n", status);
    }
    return status;
}

flash_status_t EEPROM_WriteDataWord(uint16_t Address, uint16_t DataWord) {
    /* if the address is out-of-bounds, do nothing */
    if (Address >= FEE_DENSITY_BYTES) {
        eeprom_printf("EEPROM_WriteDataWord(0x%04x, 0x%04x) [BAD ADDRESS]\n", Address, DataWord);
        return FLASH_STATUS_BAD_ADDRESS;
    }

    /* Check for word alignment */
    flash_status_t final_status = FLASH_STATUS_SUCCESS;
    if (Address % 2) {
        final_status        = EEPROM_WriteDataByte(Address, DataWord);
        flash_status_t status = EEPROM_WriteDataByte(Address + 1, DataWord >> 8);
        if (status != FLASH_STATUS_SUCCESS) final_status = status;
        if (final_status != 0 && final_status != FLASH_STATUS_SUCCESS) {
            eeprom_printf("EEPROM_WriteDataWord [STATUS == %d]\n", final_status);
        }
        return final_status;
    }

    /* if the value is the same, don't bother writing it */
    uint16_t oldValue = *(uint16_t *)(&DataBuf[Address]);
    if (oldValue == DataWord) {
        eeprom_printf("EEPROM_WriteDataWord(0x%04x, 0x%04x) [SKIP SAME]\n", Address, DataWord);
        return FLASH_STATUS_SUCCESS;
    }

    /* keep DataBuf cache in sync */
    *(uint16_t *)(&DataBuf[Address]) = DataWord;
    eeprom_printf("EEPROM_WriteDataWord DataBuf[0x%04x] = 0x%04x\n", Address, *(uint16_t *)(&DataBuf[Address]));

    /* perform the write into flash memory */
    /* First, attempt to write directly into the compacted flash area */
    final_status = eeprom_write_direct_entry(Address);
    if (!final_status) {
        /* Otherwise append to the write log */
        /* Check if we need to fall back to byte write */
        if (Address < FEE_BYTE_RANGE) {
            final_status = FLASH_STATUS_SUCCESS;
            /* Only write a byte if it has changed */
            if ((uint8_t)oldValue != (uint8_t)DataWord) {
                final_status = eeprom_write_log_byte_entry(Address);
            }
            flash_status_t status = FLASH_STATUS_SUCCESS;
            /* Only write a byte if it has changed */
            if ((oldValue >> 8) != (DataWord >> 8)) {
                status = eeprom_write_log_byte_entry(Address + 1);
            }
            if (status != FLASH_STATUS_SUCCESS) final_status = status;
        } else {
            final_status = eeprom_write_log_word_entry(Address);
        }
    }
    if (final_status != 0 && final_status != FLASH_STATUS_SUCCESS) {
        eeprom_printf("EEPROM_WriteDataWord [STATUS == %d]\n", final_status);
    }
    return final_status;
}

uint8_t EEPROM_ReadDataByte(uint16_t Address) {
    uint8_t DataByte = 0xFF;

    if (Address < FEE_DENSITY_BYTES) {
        DataByte = DataBuf[Address];
    }

    eeprom_printf("EEPROM_ReadDataByte(0x%04x): 0x%02x\n", Address, DataByte);

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

    eeprom_printf("EEPROM_ReadDataWord(0x%04x): 0x%04x\n", Address, DataWord);

    return DataWord;
}

/*****************************************************************************
 *  Bind to eeprom_driver.c
 *******************************************************************************/
void eeprom_driver_init(void) {
    flash_init();
    EEPROM_Init();
}

void eeprom_driver_erase(void) { EEPROM_Erase(); }

void eeprom_read_block(void *buf, const void *addr, size_t len) {
    const uint8_t *src  = (const uint8_t *)addr;
    uint8_t *      dest = (uint8_t *)buf;

    /* Check word alignment */
    if (len && (uintptr_t)src % 2) {
        /* Read the unaligned first byte */
        *dest++ = EEPROM_ReadDataByte((const uintptr_t)src++);
        --len;
    }

    uint16_t value;
    bool     aligned = ((uintptr_t)dest % 2 == 0);
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

    /* Check word alignment */
    if (len && (uintptr_t)dest % 2) {
        /* Write the unaligned first byte */
        EEPROM_WriteDataByte((uintptr_t)dest++, *src++);
        --len;
    }

    uint16_t value;
    bool     aligned = ((uintptr_t)src % 2 == 0);
    while (len > 1) {
        if (aligned) {
            value = *(uint16_t *)src;
        } else {
            value = *(uint8_t *)src | (*(uint8_t *)(src + 1) << 8);
        }
        EEPROM_WriteDataWord((uintptr_t)((uint16_t *)dest), value);
        dest += 2;
        src += 2;
        len -= 2;
    }

    if (len) {
        EEPROM_WriteDataByte((uintptr_t)dest, *src);
    }
}
