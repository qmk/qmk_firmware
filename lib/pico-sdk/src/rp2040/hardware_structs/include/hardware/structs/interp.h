// THIS HEADER FILE IS AUTOMATICALLY GENERATED -- DO NOT EDIT

/*
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_INTERP_H
#define _HARDWARE_STRUCTS_INTERP_H

#include "hardware/address_mapped.h"
#include "hardware/regs/sio.h"

// Reference to datasheet: https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#tab-registerlist_sio
//
// The _REG_ macro is intended to help make the register navigable in your IDE (for example, using the "Go to Definition" feature)
// _REG_(x) will link to the corresponding register in hardware/regs/sio.h.
//
// Bit-field descriptions are of the form:
// BITMASK [BITRANGE]: FIELDNAME (RESETVALUE): DESCRIPTION

typedef struct {
    _REG_(SIO_INTERP0_ACCUM0_OFFSET) // SIO_INTERP0_ACCUM0
    // (Description copied from array index 0 register SIO_INTERP0_ACCUM0 applies similarly to other array indexes)
    //
    // Read/write access to accumulator 0
    io_rw_32 accum[2];

    _REG_(SIO_INTERP0_BASE0_OFFSET) // SIO_INTERP0_BASE0
    // (Description copied from array index 0 register SIO_INTERP0_BASE0 applies similarly to other array indexes)
    //
    // Read/write access to BASE0 register
    io_rw_32 base[3];

    _REG_(SIO_INTERP0_POP_LANE0_OFFSET) // SIO_INTERP0_POP_LANE0
    // (Description copied from array index 0 register SIO_INTERP0_POP_LANE0 applies similarly to other array indexes)
    //
    // Read LANE0 result, and simultaneously write lane results to both accumulators (POP)
    io_ro_32 pop[3];

    _REG_(SIO_INTERP0_PEEK_LANE0_OFFSET) // SIO_INTERP0_PEEK_LANE0
    // (Description copied from array index 0 register SIO_INTERP0_PEEK_LANE0 applies similarly to other array indexes)
    //
    // Read LANE0 result, without altering any internal state (PEEK)
    io_ro_32 peek[3];

    _REG_(SIO_INTERP0_CTRL_LANE0_OFFSET) // SIO_INTERP0_CTRL_LANE0
    // (Description copied from array index 0 register SIO_INTERP0_CTRL_LANE0 applies similarly to other array indexes)
    //
    // Control register for lane 0
    // 0x02000000 [25]    : OVERF (0): Set if either OVERF0 or OVERF1 is set
    // 0x01000000 [24]    : OVERF1 (0): Indicates if any masked-off MSBs in ACCUM1 are set
    // 0x00800000 [23]    : OVERF0 (0): Indicates if any masked-off MSBs in ACCUM0 are set
    // 0x00200000 [21]    : BLEND (0): Only present on INTERP0 on each core
    // 0x00180000 [20:19] : FORCE_MSB (0): ORed into bits 29:28 of the lane result presented to the processor on the bus
    // 0x00040000 [18]    : ADD_RAW (0): If 1, mask + shift is bypassed for LANE0 result
    // 0x00020000 [17]    : CROSS_RESULT (0): If 1, feed the opposite lane's result into this lane's accumulator on POP
    // 0x00010000 [16]    : CROSS_INPUT (0): If 1, feed the opposite lane's accumulator into this lane's shift + mask hardware
    // 0x00008000 [15]    : SIGNED (0): If SIGNED is set, the shifted and masked accumulator value is sign-extended to 32 bits
    // 0x00007c00 [14:10] : MASK_MSB (0): The most-significant bit allowed to pass by the mask (inclusive)
    // 0x000003e0 [9:5]   : MASK_LSB (0): The least-significant bit allowed to pass by the mask (inclusive)
    // 0x0000001f [4:0]   : SHIFT (0): Logical right-shift applied to accumulator before masking
    io_rw_32 ctrl[2];

    _REG_(SIO_INTERP0_ACCUM0_ADD_OFFSET) // SIO_INTERP0_ACCUM0_ADD
    // (Description copied from array index 0 register SIO_INTERP0_ACCUM0_ADD applies similarly to other array indexes)
    //
    // Values written here are atomically added to ACCUM0
    // 0x00ffffff [23:0]  : INTERP0_ACCUM0_ADD (0)
    io_rw_32 add_raw[2];

    _REG_(SIO_INTERP0_BASE_1AND0_OFFSET) // SIO_INTERP0_BASE_1AND0
    // On write, the lower 16 bits go to BASE0, upper bits to BASE1 simultaneously
    io_wo_32 base01;
} interp_hw_t;

#define interp_hw_array ((interp_hw_t *)(SIO_BASE + SIO_INTERP0_ACCUM0_OFFSET))
#define interp0_hw (&interp_hw_array[0])
#define interp1_hw (&interp_hw_array[1])

#endif
