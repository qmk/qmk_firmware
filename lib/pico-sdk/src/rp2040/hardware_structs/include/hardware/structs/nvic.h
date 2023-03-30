// THIS HEADER FILE IS AUTOMATICALLY GENERATED -- DO NOT EDIT

/*
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_NVIC_H
#define _HARDWARE_STRUCTS_NVIC_H

#include "hardware/address_mapped.h"
#include "hardware/regs/m0plus.h"

// Reference to datasheet: https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#tab-registerlist_m0plus
//
// The _REG_ macro is intended to help make the register navigable in your IDE (for example, using the "Go to Definition" feature)
// _REG_(x) will link to the corresponding register in hardware/regs/m0plus.h.
//
// Bit-field descriptions are of the form:
// BITMASK [BITRANGE]: FIELDNAME (RESETVALUE): DESCRIPTION

typedef struct {
    _REG_(M0PLUS_NVIC_ISER_OFFSET) // M0PLUS_NVIC_ISER
    // Use the Interrupt Set-Enable Register to enable interrupts and determine which interrupts are currently enabled
    // 0xffffffff [31:0]  : SETENA (0): Interrupt set-enable bits
    io_rw_32 iser;

    uint32_t _pad0[31];

    _REG_(M0PLUS_NVIC_ICER_OFFSET) // M0PLUS_NVIC_ICER
    // Use the Interrupt Clear-Enable Registers to disable interrupts and determine which interrupts are currently enabled
    // 0xffffffff [31:0]  : CLRENA (0): Interrupt clear-enable bits
    io_rw_32 icer;

    uint32_t _pad1[31];

    _REG_(M0PLUS_NVIC_ISPR_OFFSET) // M0PLUS_NVIC_ISPR
    // The NVIC_ISPR forces interrupts into the pending state, and shows which interrupts are pending
    // 0xffffffff [31:0]  : SETPEND (0): Interrupt set-pending bits
    io_rw_32 ispr;

    uint32_t _pad2[31];

    _REG_(M0PLUS_NVIC_ICPR_OFFSET) // M0PLUS_NVIC_ICPR
    // Use the Interrupt Clear-Pending Register to clear pending interrupts and determine which interrupts are currently pending
    // 0xffffffff [31:0]  : CLRPEND (0): Interrupt clear-pending bits
    io_rw_32 icpr;

    uint32_t _pad3[95];

    _REG_(M0PLUS_NVIC_IPR0_OFFSET) // M0PLUS_NVIC_IPR0
    // (Description copied from array index 0 register M0PLUS_NVIC_IPR0 applies similarly to other array indexes)
    //
    // Use the Interrupt Priority Registers to assign a priority from 0 to 3 to each of the available interrupts
    // 0xc0000000 [31:30] : IP_3 (0): Priority of interrupt 3
    // 0x00c00000 [23:22] : IP_2 (0): Priority of interrupt 2
    // 0x0000c000 [15:14] : IP_1 (0): Priority of interrupt 1
    // 0x000000c0 [7:6]   : IP_0 (0): Priority of interrupt 0
    io_rw_32 ipr[8];
} nvic_hw_t;

#define nvic_hw ((nvic_hw_t *)(PPB_BASE + M0PLUS_NVIC_ISER_OFFSET))

#endif
