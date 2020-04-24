#include "ch.h"
#include "hal.h"

#include "eeconfig.h"

/*************************************/
/*          Hardware backend         */
/*                                   */
/*    Code from PJRC/Teensyduino     */
/*************************************/

/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2013 PJRC.COM, LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * 1. The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * 2. If the Software is incorporated into a build system that allows
 * selection among a list of target devices, then similar target
 * devices manufactured by PJRC.COM must be included in the list of
 * target devices and selectable in the same manner.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#if defined(K20x) /* chip selection */
/* Teensy 3.0, 3.1, 3.2; mchck; infinity keyboard */

// The EEPROM is really RAM with a hardware-based backup system to
// flash memory.  Selecting a smaller size EEPROM allows more wear
// leveling, for higher write endurance.  If you edit this file,
// set this to the smallest size your application can use.  Also,
// due to Freescale's implementation, writing 16 or 32 bit words
// (aligned to 2 or 4 byte boundaries) has twice the endurance
// compared to writing 8 bit bytes.
//
#    ifndef EEPROM_SIZE
#        define EEPROM_SIZE 32
#    endif

/*
    ^^^ Here be dragons:
        NXP AppNote AN4282 section 3.1 states that partitioning must only be done once.
        Once EEPROM partitioning is done, the size is locked to this initial configuration.
        Attempts to modify the EEPROM_SIZE setting may brick your board.
*/

// Writing unaligned 16 or 32 bit data is handled automatically when
// this is defined, but at a cost of extra code size.  Without this,
// any unaligned write will cause a hard fault exception!  If you're
// absolutely sure all 16 and 32 bit writes will be aligned, you can
// remove the extra unnecessary code.
//
#    define HANDLE_UNALIGNED_WRITES

// Minimum EEPROM Endurance
// ------------------------
#    if (EEPROM_SIZE == 2048)  // 35000 writes/byte or 70000 writes/word
#        define EEESIZE 0x33
#    elif (EEPROM_SIZE == 1024)  // 75000 writes/byte or 150000 writes/word
#        define EEESIZE 0x34
#    elif (EEPROM_SIZE == 512)  // 155000 writes/byte or 310000 writes/word
#        define EEESIZE 0x35
#    elif (EEPROM_SIZE == 256)  // 315000 writes/byte or 630000 writes/word
#        define EEESIZE 0x36
#    elif (EEPROM_SIZE == 128)  // 635000 writes/byte or 1270000 writes/word
#        define EEESIZE 0x37
#    elif (EEPROM_SIZE == 64)  // 1275000 writes/byte or 2550000 writes/word
#        define EEESIZE 0x38
#    elif (EEPROM_SIZE == 32)  // 2555000 writes/byte or 5110000 writes/word
#        define EEESIZE 0x39
#    endif

/** \brief eeprom initialization
 *
 * FIXME: needs doc
 */
void eeprom_initialize(void) {
    uint32_t count          = 0;
    uint16_t do_flash_cmd[] = {0xf06f, 0x037f, 0x7003, 0x7803, 0xf013, 0x0f80, 0xd0fb, 0x4770};
    uint8_t  status;

    if (FTFL->FCNFG & FTFL_FCNFG_RAMRDY) {
        // FlexRAM is configured as traditional RAM
        // We need to reconfigure for EEPROM usage
        FTFL->FCCOB0 = 0x80;     // PGMPART = Program Partition Command
        FTFL->FCCOB4 = EEESIZE;  // EEPROM Size
        FTFL->FCCOB5 = 0x03;     // 0K for Dataflash, 32K for EEPROM backup
        __disable_irq();
        // do_flash_cmd() must execute from RAM.  Luckily the C syntax is simple...
        (*((void (*)(volatile uint8_t *))((uint32_t)do_flash_cmd | 1)))(&(FTFL->FSTAT));
        __enable_irq();
        status = FTFL->FSTAT;
        if (status & (FTFL_FSTAT_RDCOLERR | FTFL_FSTAT_ACCERR | FTFL_FSTAT_FPVIOL)) {
            FTFL->FSTAT = (status & (FTFL_FSTAT_RDCOLERR | FTFL_FSTAT_ACCERR | FTFL_FSTAT_FPVIOL));
            return;  // error
        }
    }
    // wait for eeprom to become ready (is this really necessary?)
    while (!(FTFL->FCNFG & FTFL_FCNFG_EEERDY)) {
        if (++count > 20000) break;
    }
}

#    define FlexRAM ((uint8_t *)0x14000000)

/** \brief eeprom read byte
 *
 * FIXME: needs doc
 */
uint8_t eeprom_read_byte(const uint8_t *addr) {
    uint32_t offset = (uint32_t)addr;
    if (offset >= EEPROM_SIZE) return 0;
    if (!(FTFL->FCNFG & FTFL_FCNFG_EEERDY)) eeprom_initialize();
    return FlexRAM[offset];
}

/** \brief eeprom read word
 *
 * FIXME: needs doc
 */
uint16_t eeprom_read_word(const uint16_t *addr) {
    uint32_t offset = (uint32_t)addr;
    if (offset >= EEPROM_SIZE - 1) return 0;
    if (!(FTFL->FCNFG & FTFL_FCNFG_EEERDY)) eeprom_initialize();
    return *(uint16_t *)(&FlexRAM[offset]);
}

/** \brief eeprom read dword
 *
 * FIXME: needs doc
 */
uint32_t eeprom_read_dword(const uint32_t *addr) {
    uint32_t offset = (uint32_t)addr;
    if (offset >= EEPROM_SIZE - 3) return 0;
    if (!(FTFL->FCNFG & FTFL_FCNFG_EEERDY)) eeprom_initialize();
    return *(uint32_t *)(&FlexRAM[offset]);
}

/** \brief eeprom read block
 *
 * FIXME: needs doc
 */
void eeprom_read_block(void *buf, const void *addr, uint32_t len) {
    uint32_t offset = (uint32_t)addr;
    uint8_t *dest   = (uint8_t *)buf;
    uint32_t end    = offset + len;

    if (!(FTFL->FCNFG & FTFL_FCNFG_EEERDY)) eeprom_initialize();
    if (end > EEPROM_SIZE) end = EEPROM_SIZE;
    while (offset < end) {
        *dest++ = FlexRAM[offset++];
    }
}

/** \brief eeprom is ready
 *
 * FIXME: needs doc
 */
int eeprom_is_ready(void) { return (FTFL->FCNFG & FTFL_FCNFG_EEERDY) ? 1 : 0; }

/** \brief flexram wait
 *
 * FIXME: needs doc
 */
static void flexram_wait(void) {
    while (!(FTFL->FCNFG & FTFL_FCNFG_EEERDY)) {
        // TODO: timeout
    }
}

/** \brief eeprom_write_byte
 *
 * FIXME: needs doc
 */
void eeprom_write_byte(uint8_t *addr, uint8_t value) {
    uint32_t offset = (uint32_t)addr;

    if (offset >= EEPROM_SIZE) return;
    if (!(FTFL->FCNFG & FTFL_FCNFG_EEERDY)) eeprom_initialize();
    if (FlexRAM[offset] != value) {
        FlexRAM[offset] = value;
        flexram_wait();
    }
}

/** \brief eeprom write word
 *
 * FIXME: needs doc
 */
void eeprom_write_word(uint16_t *addr, uint16_t value) {
    uint32_t offset = (uint32_t)addr;

    if (offset >= EEPROM_SIZE - 1) return;
    if (!(FTFL->FCNFG & FTFL_FCNFG_EEERDY)) eeprom_initialize();
#    ifdef HANDLE_UNALIGNED_WRITES
    if ((offset & 1) == 0) {
#    endif
        if (*(uint16_t *)(&FlexRAM[offset]) != value) {
            *(uint16_t *)(&FlexRAM[offset]) = value;
            flexram_wait();
        }
#    ifdef HANDLE_UNALIGNED_WRITES
    } else {
        if (FlexRAM[offset] != value) {
            FlexRAM[offset] = value;
            flexram_wait();
        }
        if (FlexRAM[offset + 1] != (value >> 8)) {
            FlexRAM[offset + 1] = value >> 8;
            flexram_wait();
        }
    }
#    endif
}

/** \brief eeprom write dword
 *
 * FIXME: needs doc
 */
void eeprom_write_dword(uint32_t *addr, uint32_t value) {
    uint32_t offset = (uint32_t)addr;

    if (offset >= EEPROM_SIZE - 3) return;
    if (!(FTFL->FCNFG & FTFL_FCNFG_EEERDY)) eeprom_initialize();
#    ifdef HANDLE_UNALIGNED_WRITES
    switch (offset & 3) {
        case 0:
#    endif
            if (*(uint32_t *)(&FlexRAM[offset]) != value) {
                *(uint32_t *)(&FlexRAM[offset]) = value;
                flexram_wait();
            }
            return;
#    ifdef HANDLE_UNALIGNED_WRITES
        case 2:
            if (*(uint16_t *)(&FlexRAM[offset]) != value) {
                *(uint16_t *)(&FlexRAM[offset]) = value;
                flexram_wait();
            }
            if (*(uint16_t *)(&FlexRAM[offset + 2]) != (value >> 16)) {
                *(uint16_t *)(&FlexRAM[offset + 2]) = value >> 16;
                flexram_wait();
            }
            return;
        default:
            if (FlexRAM[offset] != value) {
                FlexRAM[offset] = value;
                flexram_wait();
            }
            if (*(uint16_t *)(&FlexRAM[offset + 1]) != (value >> 8)) {
                *(uint16_t *)(&FlexRAM[offset + 1]) = value >> 8;
                flexram_wait();
            }
            if (FlexRAM[offset + 3] != (value >> 24)) {
                FlexRAM[offset + 3] = value >> 24;
                flexram_wait();
            }
    }
#    endif
}

/** \brief eeprom write block
 *
 * FIXME: needs doc
 */
void eeprom_write_block(const void *buf, void *addr, uint32_t len) {
    uint32_t       offset = (uint32_t)addr;
    const uint8_t *src    = (const uint8_t *)buf;

    if (offset >= EEPROM_SIZE) return;
    if (!(FTFL->FCNFG & FTFL_FCNFG_EEERDY)) eeprom_initialize();
    if (len >= EEPROM_SIZE) len = EEPROM_SIZE;
    if (offset + len >= EEPROM_SIZE) len = EEPROM_SIZE - offset;
    while (len > 0) {
        uint32_t lsb = offset & 3;
        if (lsb == 0 && len >= 4) {
            // write aligned 32 bits
            uint32_t val32;
            val32 = *src++;
            val32 |= (*src++ << 8);
            val32 |= (*src++ << 16);
            val32 |= (*src++ << 24);
            if (*(uint32_t *)(&FlexRAM[offset]) != val32) {
                *(uint32_t *)(&FlexRAM[offset]) = val32;
                flexram_wait();
            }
            offset += 4;
            len -= 4;
        } else if ((lsb == 0 || lsb == 2) && len >= 2) {
            // write aligned 16 bits
            uint16_t val16;
            val16 = *src++;
            val16 |= (*src++ << 8);
            if (*(uint16_t *)(&FlexRAM[offset]) != val16) {
                *(uint16_t *)(&FlexRAM[offset]) = val16;
                flexram_wait();
            }
            offset += 2;
            len -= 2;
        } else {
            // write 8 bits
            uint8_t val8 = *src++;
            if (FlexRAM[offset] != val8) {
                FlexRAM[offset] = val8;
                flexram_wait();
            }
            offset++;
            len--;
        }
    }
}

/*
void do_flash_cmd(volatile uint8_t *fstat)
{
    *fstat = 0x80;
    while ((*fstat & 0x80) == 0) ; // wait
}
00000000 <do_flash_cmd>:
   0:	f06f 037f 	mvn.w	r3, #127	; 0x7f
   4:	7003      	strb	r3, [r0, #0]
   6:	7803      	ldrb	r3, [r0, #0]
   8:	f013 0f80 	tst.w	r3, #128	; 0x80
   c:	d0fb      	beq.n	6 <do_flash_cmd+0x6>
   e:	4770      	bx	lr
*/

#elif defined(KL2x) /* chip selection */
/* Teensy LC (emulated) */

#    define SYMVAL(sym) (uint32_t)(((uint8_t *)&(sym)) - ((uint8_t *)0))

extern uint32_t __eeprom_workarea_start__;
extern uint32_t __eeprom_workarea_end__;

#    define EEPROM_SIZE 128

static uint32_t flashend = 0;

void eeprom_initialize(void) {
    const uint16_t *p = (uint16_t *)SYMVAL(__eeprom_workarea_start__);

    do {
        if (*p++ == 0xFFFF) {
            flashend = (uint32_t)(p - 2);
            return;
        }
    } while (p < (uint16_t *)SYMVAL(__eeprom_workarea_end__));
    flashend = (uint32_t)((uint16_t *)SYMVAL(__eeprom_workarea_end__) - 1);
}

uint8_t eeprom_read_byte(const uint8_t *addr) {
    uint32_t        offset = (uint32_t)addr;
    const uint16_t *p      = (uint16_t *)SYMVAL(__eeprom_workarea_start__);
    const uint16_t *end    = (const uint16_t *)((uint32_t)flashend);
    uint16_t        val;
    uint8_t         data = 0xFF;

    if (!end) {
        eeprom_initialize();
        end = (const uint16_t *)((uint32_t)flashend);
    }
    if (offset < EEPROM_SIZE) {
        while (p <= end) {
            val = *p++;
            if ((val & 255) == offset) data = val >> 8;
        }
    }
    return data;
}

static void flash_write(const uint16_t *code, uint32_t addr, uint32_t data) {
    // with great power comes great responsibility....
    uint32_t stat;
    *(uint32_t *)&(FTFA->FCCOB3) = 0x06000000 | (addr & 0x00FFFFFC);
    *(uint32_t *)&(FTFA->FCCOB7) = data;
    __disable_irq();
    (*((void (*)(volatile uint8_t *))((uint32_t)code | 1)))(&(FTFA->FSTAT));
    __enable_irq();
    stat = FTFA->FSTAT & (FTFA_FSTAT_RDCOLERR | FTFA_FSTAT_ACCERR | FTFA_FSTAT_FPVIOL);
    if (stat) {
        FTFA->FSTAT = stat;
    }
    MCM->PLACR |= MCM_PLACR_CFCC;
}

void eeprom_write_byte(uint8_t *addr, uint8_t data) {
    uint32_t        offset = (uint32_t)addr;
    const uint16_t *p, *end = (const uint16_t *)((uint32_t)flashend);
    uint32_t        i, val, flashaddr;
    uint16_t        do_flash_cmd[] = {0x2380, 0x7003, 0x7803, 0xb25b, 0x2b00, 0xdafb, 0x4770};
    uint8_t         buf[EEPROM_SIZE];

    if (offset >= EEPROM_SIZE) return;
    if (!end) {
        eeprom_initialize();
        end = (const uint16_t *)((uint32_t)flashend);
    }
    if (++end < (uint16_t *)SYMVAL(__eeprom_workarea_end__)) {
        val       = (data << 8) | offset;
        flashaddr = (uint32_t)end;
        flashend  = flashaddr;
        if ((flashaddr & 2) == 0) {
            val |= 0xFFFF0000;
        } else {
            val <<= 16;
            val |= 0x0000FFFF;
        }
        flash_write(do_flash_cmd, flashaddr, val);
    } else {
        for (i = 0; i < EEPROM_SIZE; i++) {
            buf[i] = 0xFF;
        }
        val = 0;
        for (p = (uint16_t *)SYMVAL(__eeprom_workarea_start__); p < (uint16_t *)SYMVAL(__eeprom_workarea_end__); p++) {
            val = *p;
            if ((val & 255) < EEPROM_SIZE) {
                buf[val & 255] = val >> 8;
            }
        }
        buf[offset] = data;
        for (flashaddr = (uint32_t)(uint16_t *)SYMVAL(__eeprom_workarea_start__); flashaddr < (uint32_t)(uint16_t *)SYMVAL(__eeprom_workarea_end__); flashaddr += 1024) {
            *(uint32_t *)&(FTFA->FCCOB3) = 0x09000000 | flashaddr;
            __disable_irq();
            (*((void (*)(volatile uint8_t *))((uint32_t)do_flash_cmd | 1)))(&(FTFA->FSTAT));
            __enable_irq();
            val = FTFA->FSTAT & (FTFA_FSTAT_RDCOLERR | FTFA_FSTAT_ACCERR | FTFA_FSTAT_FPVIOL);
            ;
            if (val) FTFA->FSTAT = val;
            MCM->PLACR |= MCM_PLACR_CFCC;
        }
        flashaddr = (uint32_t)(uint16_t *)SYMVAL(__eeprom_workarea_start__);
        for (i = 0; i < EEPROM_SIZE; i++) {
            if (buf[i] == 0xFF) continue;
            if ((flashaddr & 2) == 0) {
                val = (buf[i] << 8) | i;
            } else {
                val = val | (buf[i] << 24) | (i << 16);
                flash_write(do_flash_cmd, flashaddr, val);
            }
            flashaddr += 2;
        }
        flashend = flashaddr;
        if ((flashaddr & 2)) {
            val |= 0xFFFF0000;
            flash_write(do_flash_cmd, flashaddr, val);
        }
    }
}

/*
void do_flash_cmd(volatile uint8_t *fstat)
{
        *fstat = 0x80;
        while ((*fstat & 0x80) == 0) ; // wait
}
00000000 <do_flash_cmd>:
   0:	2380      	movs	r3, #128	; 0x80
   2:	7003      	strb	r3, [r0, #0]
   4:	7803      	ldrb	r3, [r0, #0]
   6:	b25b      	sxtb	r3, r3
   8:	2b00      	cmp	r3, #0
   a:	dafb      	bge.n	4 <do_flash_cmd+0x4>
   c:	4770      	bx	lr
*/

uint16_t eeprom_read_word(const uint16_t *addr) {
    const uint8_t *p = (const uint8_t *)addr;
    return eeprom_read_byte(p) | (eeprom_read_byte(p + 1) << 8);
}

uint32_t eeprom_read_dword(const uint32_t *addr) {
    const uint8_t *p = (const uint8_t *)addr;
    return eeprom_read_byte(p) | (eeprom_read_byte(p + 1) << 8) | (eeprom_read_byte(p + 2) << 16) | (eeprom_read_byte(p + 3) << 24);
}

void eeprom_read_block(void *buf, const void *addr, uint32_t len) {
    const uint8_t *p    = (const uint8_t *)addr;
    uint8_t *      dest = (uint8_t *)buf;
    while (len--) {
        *dest++ = eeprom_read_byte(p++);
    }
}

int eeprom_is_ready(void) { return 1; }

void eeprom_write_word(uint16_t *addr, uint16_t value) {
    uint8_t *p = (uint8_t *)addr;
    eeprom_write_byte(p++, value);
    eeprom_write_byte(p, value >> 8);
}

void eeprom_write_dword(uint32_t *addr, uint32_t value) {
    uint8_t *p = (uint8_t *)addr;
    eeprom_write_byte(p++, value);
    eeprom_write_byte(p++, value >> 8);
    eeprom_write_byte(p++, value >> 16);
    eeprom_write_byte(p, value >> 24);
}

void eeprom_write_block(const void *buf, void *addr, uint32_t len) {
    uint8_t *      p   = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        eeprom_write_byte(p++, *src++);
    }
}

#else
// No EEPROM supported, so emulate it

#    ifndef EEPROM_SIZE
#        include "eeconfig.h"
#        define EEPROM_SIZE (((EECONFIG_SIZE + 3) / 4) * 4)  // based off eeconfig's current usage, aligned to 4-byte sizes, to deal with LTO
#    endif
__attribute__((aligned(4))) static uint8_t buffer[EEPROM_SIZE];

uint8_t eeprom_read_byte(const uint8_t *addr) {
    uint32_t offset = (uint32_t)addr;
    return buffer[offset];
}

void eeprom_write_byte(uint8_t *addr, uint8_t value) {
    uint32_t offset = (uint32_t)addr;
    buffer[offset]  = value;
}

uint16_t eeprom_read_word(const uint16_t *addr) {
    const uint8_t *p = (const uint8_t *)addr;
    return eeprom_read_byte(p) | (eeprom_read_byte(p + 1) << 8);
}

uint32_t eeprom_read_dword(const uint32_t *addr) {
    const uint8_t *p = (const uint8_t *)addr;
    return eeprom_read_byte(p) | (eeprom_read_byte(p + 1) << 8) | (eeprom_read_byte(p + 2) << 16) | (eeprom_read_byte(p + 3) << 24);
}

void eeprom_read_block(void *buf, const void *addr, size_t len) {
    const uint8_t *p    = (const uint8_t *)addr;
    uint8_t *      dest = (uint8_t *)buf;
    while (len--) {
        *dest++ = eeprom_read_byte(p++);
    }
}

void eeprom_write_word(uint16_t *addr, uint16_t value) {
    uint8_t *p = (uint8_t *)addr;
    eeprom_write_byte(p++, value);
    eeprom_write_byte(p, value >> 8);
}

void eeprom_write_dword(uint32_t *addr, uint32_t value) {
    uint8_t *p = (uint8_t *)addr;
    eeprom_write_byte(p++, value);
    eeprom_write_byte(p++, value >> 8);
    eeprom_write_byte(p++, value >> 16);
    eeprom_write_byte(p, value >> 24);
}

void eeprom_write_block(const void *buf, void *addr, size_t len) {
    uint8_t *      p   = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        eeprom_write_byte(p++, *src++);
    }
}

#endif /* chip selection */
// The update functions just calls write for now, but could probably be optimized

void eeprom_update_byte(uint8_t *addr, uint8_t value) { eeprom_write_byte(addr, value); }

void eeprom_update_word(uint16_t *addr, uint16_t value) {
    uint8_t *p = (uint8_t *)addr;
    eeprom_write_byte(p++, value);
    eeprom_write_byte(p, value >> 8);
}

void eeprom_update_dword(uint32_t *addr, uint32_t value) {
    uint8_t *p = (uint8_t *)addr;
    eeprom_write_byte(p++, value);
    eeprom_write_byte(p++, value >> 8);
    eeprom_write_byte(p++, value >> 16);
    eeprom_write_byte(p, value >> 24);
}

void eeprom_update_block(const void *buf, void *addr, size_t len) {
    uint8_t *      p   = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        eeprom_write_byte(p++, *src++);
    }
}
