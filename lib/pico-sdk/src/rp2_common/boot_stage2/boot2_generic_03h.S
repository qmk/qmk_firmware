// ----------------------------------------------------------------------------
// Second stage boot code
// Copyright (c) 2019-2021 Raspberry Pi (Trading) Ltd.
// SPDX-License-Identifier: BSD-3-Clause
//
// Device:      Anything which responds to 03h serial read command
//
// Details:     * Configure SSI to translate each APB read into a 03h command
//              * 8 command clocks, 24 address clocks and 32 data clocks
//              * This enables you to boot from almost anything: you can pretty
//                much solder a potato to your PCB, or a piece of cheese
//              * The tradeoff is performance around 3x worse than QSPI XIP
//
// Building:    * This code must be position-independent, and use stack only
//              * The code will be padded to a size of 256 bytes, including a
//                4-byte checksum. Therefore code size cannot exceed 252 bytes.
// ----------------------------------------------------------------------------

#include "pico/asm_helper.S"
#include "hardware/regs/addressmap.h"
#include "hardware/regs/ssi.h"

// ----------------------------------------------------------------------------
// Config section
// ----------------------------------------------------------------------------
// It should be possible to support most flash devices by modifying this section

// The serial flash interface will run at clk_sys/PICO_FLASH_SPI_CLKDIV.
// This must be a positive, even integer.
// The bootrom is very conservative with SPI frequency, but here we should be
// as aggressive as possible.
#ifndef PICO_FLASH_SPI_CLKDIV
#define PICO_FLASH_SPI_CLKDIV 4
#endif

#define CMD_READ 0x03

// Value is number of address bits divided by 4
#define ADDR_L 6

#define CTRLR0_XIP \
    (SSI_CTRLR0_SPI_FRF_VALUE_STD << SSI_CTRLR0_SPI_FRF_LSB) |  /* Standard 1-bit SPI serial frames */ \
    (31 << SSI_CTRLR0_DFS_32_LSB)  |                            /* 32 clocks per data frame */ \
    (SSI_CTRLR0_TMOD_VALUE_EEPROM_READ  << SSI_CTRLR0_TMOD_LSB) /* Send instr + addr, receive data */

#define SPI_CTRLR0_XIP \
    (CMD_READ << SSI_SPI_CTRLR0_XIP_CMD_LSB) |        /* Value of instruction prefix */ \
    (ADDR_L << SSI_SPI_CTRLR0_ADDR_L_LSB) |           /* Total number of address + mode bits */ \
    (2 << SSI_SPI_CTRLR0_INST_L_LSB) |                /* 8 bit command prefix (field value is bits divided by 4) */ \
    (SSI_SPI_CTRLR0_TRANS_TYPE_VALUE_1C1A << SSI_SPI_CTRLR0_TRANS_TYPE_LSB) /* command and address both in serial format */

// ----------------------------------------------------------------------------
// Start of 2nd Stage Boot Code
// ----------------------------------------------------------------------------

.cpu cortex-m0
.thumb

.section .text

.global _stage2_boot
.type _stage2_boot,%function
.thumb_func
_stage2_boot:
    push {lr}

    ldr r3, =XIP_SSI_BASE                // Use as base address where possible

    // Disable SSI to allow further config
    mov r1, #0
    str r1, [r3, #SSI_SSIENR_OFFSET]

    // Set baud rate
    mov r1, #PICO_FLASH_SPI_CLKDIV
    str r1, [r3, #SSI_BAUDR_OFFSET]

    ldr r1, =(CTRLR0_XIP)
    str r1, [r3, #SSI_CTRLR0_OFFSET]

    ldr r1, =(SPI_CTRLR0_XIP)
    ldr r0, =(XIP_SSI_BASE + SSI_SPI_CTRLR0_OFFSET)
    str r1, [r0]

    // NDF=0 (single 32b read)
    mov r1, #0x0
    str r1, [r3, #SSI_CTRLR1_OFFSET]

    // Re-enable SSI
    mov r1, #1
    str r1, [r3, #SSI_SSIENR_OFFSET]

// We are now in XIP mode. Any bus accesses to the XIP address window will be
// translated by the SSI into 03h read commands to the external flash (if cache is missed),
// and the data will be returned to the bus.

// Pull in standard exit routine
#include "boot2_helpers/exit_from_boot2.S"

.global literals
literals:
.ltorg

.end
