// ----------------------------------------------------------------------------
// Copyright (c) 2019-2021 Raspberry Pi (Trading) Ltd.
// SPDX-License-Identifier: BSD-3-Clause
//
// Device:      ISSI IS25LP080D
//              Based on W25Q080 code: main difference is the QE bit being in
//              SR1 instead of SR2.
//
// Description: Configures IS25LP080D to run in Quad I/O continuous read XIP mode
//
// Details:     * Check status register to determine if QSPI mode is enabled,
//                and perform an SR programming cycle if necessary.
//              * Use SSI to perform a dummy 0xEB read command, with the mode
//                continuation bits set, so that the flash will not require
//                0xEB instruction prefix on subsequent reads.
//              * Configure SSI to write address, mode bits, but no instruction.
//                SSI + flash are now jointly in a state where continuous reads
//                can take place.
//              * Set VTOR = 0x10000100 (user vector table immediately after
//                this boot2 image).
//              * Read stack pointer (MSP) and reset vector from the flash
//                vector table; set SP and jump, as though the processor had
//                booted directly from flash.
//
// Building:    * This code must be linked to run at 0x20027f00
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


// Define interface width: single/dual/quad IO
#define FRAME_FORMAT SSI_CTRLR0_SPI_FRF_VALUE_QUAD

// For W25Q080 this is the "Read data fast quad IO" instruction:
#define CMD_READ 0xeb

// "Mode bits" are 8 special bits sent immediately after
// the address bits in a "Read Data Fast Quad I/O" command sequence. 
// On W25Q080, the four LSBs are don't care, and if MSBs == 0xa, the
// next read does not require the 0xeb instruction prefix.
#define MODE_CONTINUOUS_READ 0xa0

// The number of address + mode bits, divided by 4 (always 4, not function of
// interface width).
#define ADDR_L 8

// How many clocks of Hi-Z following the mode bits. For W25Q080, 4 dummy cycles
// are required.
#define WAIT_CYCLES 4

// If defined, we will read status reg, compare to SREG_DATA, and overwrite
// with our value if the SR doesn't match.
// This isn't great because it will remove block protections.
// A better solution is to use a volatile SR write if your device supports it.
#define PROGRAM_STATUS_REG

#define CMD_WRITE_ENABLE 0x06
#define CMD_READ_STATUS 0x05
#define CMD_WRITE_STATUS 0x01
#define SREG_DATA 0x40  // Enable quad-SPI mode

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

// On QSPI parts we usually need a 01h SR-write command to enable QSPI mode
// (i.e. turn WPn and HOLDn into IO2/IO3)
#ifdef PROGRAM_STATUS_REG
program_sregs:
#define CTRL0_SPI_TXRX \
    (7 << SSI_CTRLR0_DFS_32_LSB) | /* 8 bits per data frame */ \
    (SSI_CTRLR0_TMOD_VALUE_TX_AND_RX << SSI_CTRLR0_TMOD_LSB)

    ldr r1, =(CTRL0_SPI_TXRX)
    str r1, [r3, #SSI_CTRLR0_OFFSET]

     // Enable SSI and select slave 0
    mov r1, #1
    str r1, [r3, #SSI_SSIENR_OFFSET]

    // Check whether SR needs updating
    ldr r0, =CMD_READ_STATUS
    bl read_flash_sreg
    ldr r2, =SREG_DATA
    cmp r0, r2
    beq skip_sreg_programming

    // Send write enable command
    mov r1, #CMD_WRITE_ENABLE
    str r1, [r3, #SSI_DR0_OFFSET]

    // Poll for completion and discard RX
    bl wait_ssi_ready
    ldr r1, [r3, #SSI_DR0_OFFSET]

    // Send status write command followed by data bytes
    mov r1, #CMD_WRITE_STATUS
    str r1, [r3, #SSI_DR0_OFFSET]
    mov r0, #0
    str r2, [r3, #SSI_DR0_OFFSET]

    bl wait_ssi_ready
    ldr r1, [r3, #SSI_DR0_OFFSET]
    ldr r1, [r3, #SSI_DR0_OFFSET]

    // Poll status register for write completion
1:
    ldr r0, =CMD_READ_STATUS
    bl read_flash_sreg
    mov r1, #1
    tst r0, r1
    bne 1b

skip_sreg_programming:

    // Send a 0xA3 high-performance-mode instruction
//    ldr r1, =0xa3
//    str r1, [r3, #SSI_DR0_OFFSET]
//    bl wait_ssi_ready

    // Disable SSI again so that it can be reconfigured
    mov r1, #0
    str r1, [r3, #SSI_SSIENR_OFFSET]
#endif


// First we need to send the initial command to get us in to Fast Read Quad I/O
// mode.  As this transaction requires a command, we can't send it in XIP mode.
// To enter Continuous Read mode as well we need to append 4'b0010 to the address
// bits and then add a further 4 don't care bits.  We will construct this by
// specifying a 28-bit address, with the least significant bits being 4'b0010.
// This is just a dummy transaction so we'll perform a read from address zero
// and then discard what comes back.  All we really care about is that at the
// end of the transaction, the flash device is in Continuous Read mode
// and from then on will only expect to receive addresses.
dummy_read:
#define CTRLR0_ENTER_XIP \
    (FRAME_FORMAT                          /* Quad I/O mode */                \
        << SSI_CTRLR0_SPI_FRF_LSB) |                                          \
    (31 << SSI_CTRLR0_DFS_32_LSB)  |       /* 32 data bits */                 \
    (SSI_CTRLR0_TMOD_VALUE_EEPROM_READ     /* Send INST/ADDR, Receive Data */ \
        << SSI_CTRLR0_TMOD_LSB)

    ldr r1, =(CTRLR0_ENTER_XIP)
    str r1, [r3, #SSI_CTRLR0_OFFSET]

    mov r1, #0x0                    // NDF=0 (single 32b read)
    str r1, [r3, #SSI_CTRLR1_OFFSET]

#define SPI_CTRLR0_ENTER_XIP \
    (ADDR_L << SSI_SPI_CTRLR0_ADDR_L_LSB) |     /* Address + mode bits */ \
    (WAIT_CYCLES << SSI_SPI_CTRLR0_WAIT_CYCLES_LSB) | /* Hi-Z dummy clocks following address + mode */ \
    (SSI_SPI_CTRLR0_INST_L_VALUE_8B \
        << SSI_SPI_CTRLR0_INST_L_LSB) |        /* 8-bit instruction */ \
    (SSI_SPI_CTRLR0_TRANS_TYPE_VALUE_1C2A      /* Send Command in serial mode then address in Quad I/O mode */ \
        << SSI_SPI_CTRLR0_TRANS_TYPE_LSB)

    ldr r1, =(SPI_CTRLR0_ENTER_XIP)
    ldr r0, =(XIP_SSI_BASE + SSI_SPI_CTRLR0_OFFSET)  // SPI_CTRL0 Register
    str r1, [r0]

    mov r1, #1                      // Re-enable SSI
    str r1, [r3, #SSI_SSIENR_OFFSET]

    mov r1, #CMD_READ 
    str r1, [r3, #SSI_DR0_OFFSET]   // Push SPI command into TX FIFO
    mov r1, #MODE_CONTINUOUS_READ   // 32-bit: 24 address bits (we don't care, so 0) and M[7:4]=1010
    str r1, [r3, #SSI_DR0_OFFSET]   // Push Address into TX FIFO - this will trigger the transaction

    // Poll for completion
    bl wait_ssi_ready

// At this point CN# will be deasserted and the SPI clock will not be running.
// The Winbond WX25X10CL device will be in continuous read, dual I/O mode and
// only expecting address bits after the next CN# assertion.  So long as we
// send 4'b0010 (and 4 more dummy HiZ bits) after every subsequent 24b address
// then the Winbond device will remain in continuous read mode.  This is the
// ideal mode for Execute-In-Place.
// (If we want to exit continuous read mode then we will need to switch back
// to APM mode and generate a 28-bit address phase with the extra nibble set
// to 4'b0000).

    mov r1, #0
    str r1, [r3, #SSI_SSIENR_OFFSET]   // Disable SSI (and clear FIFO) to allow further config

// Note that the INST_L field is used to select what XIP data gets pushed into
// the TX FIFO:
//      INST_L_0_BITS   {ADDR[23:0],XIP_CMD[7:0]}       Load "mode bits" into XIP_CMD
//      Anything else   {XIP_CMD[7:0],ADDR[23:0]}       Load SPI command into XIP_CMD
configure_ssi:
#define SPI_CTRLR0_XIP \
    (MODE_CONTINUOUS_READ                      /* Mode bits to keep flash in continuous read mode */ \
        << SSI_SPI_CTRLR0_XIP_CMD_LSB) | \
    (ADDR_L << SSI_SPI_CTRLR0_ADDR_L_LSB) |    /* Total number of address + mode bits */ \
    (WAIT_CYCLES << SSI_SPI_CTRLR0_WAIT_CYCLES_LSB) |    /* Hi-Z dummy clocks following address + mode */ \
    (SSI_SPI_CTRLR0_INST_L_VALUE_NONE          /* Do not send a command, instead send XIP_CMD as mode bits after address */ \
        << SSI_SPI_CTRLR0_INST_L_LSB) | \
    (SSI_SPI_CTRLR0_TRANS_TYPE_VALUE_2C2A      /* Send Address in Quad I/O mode (and Command but that is zero bits long) */ \
        << SSI_SPI_CTRLR0_TRANS_TYPE_LSB)

    ldr r1, =(SPI_CTRLR0_XIP)
    ldr r0, =(XIP_SSI_BASE + SSI_SPI_CTRLR0_OFFSET)
    str r1, [r0]

    mov r1, #1
    str r1, [r3, #SSI_SSIENR_OFFSET]   // Re-enable SSI

// We are now in XIP mode, with all transactions using Dual I/O and only
// needing to send 24-bit addresses (plus mode bits) for each read transaction.

// Pull in standard exit routine
#include "boot2_helpers/exit_from_boot2.S"

// Common functions
#include "boot2_helpers/wait_ssi_ready.S"
#ifdef PROGRAM_STATUS_REG
#include "boot2_helpers/read_flash_sreg.S"
#endif

.global literals
literals:
.ltorg

.end
