// THIS HEADER FILE IS AUTOMATICALLY GENERATED -- DO NOT EDIT

/*
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_VREG_AND_CHIP_RESET_H
#define _HARDWARE_STRUCTS_VREG_AND_CHIP_RESET_H

#include "hardware/address_mapped.h"
#include "hardware/regs/vreg_and_chip_reset.h"

// Reference to datasheet: https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#tab-registerlist_vreg_and_chip_reset
//
// The _REG_ macro is intended to help make the register navigable in your IDE (for example, using the "Go to Definition" feature)
// _REG_(x) will link to the corresponding register in hardware/regs/vreg_and_chip_reset.h.
//
// Bit-field descriptions are of the form:
// BITMASK [BITRANGE]: FIELDNAME (RESETVALUE): DESCRIPTION

typedef struct {
    _REG_(VREG_AND_CHIP_RESET_VREG_OFFSET) // VREG_AND_CHIP_RESET_VREG
    // Voltage regulator control and status
    // 0x00001000 [12]    : ROK (0): regulation status
    // 0x000000f0 [7:4]   : VSEL (0xb): output voltage select
    // 0x00000002 [1]     : HIZ (0): high impedance mode select
    // 0x00000001 [0]     : EN (1): enable
    io_rw_32 vreg;

    _REG_(VREG_AND_CHIP_RESET_BOD_OFFSET) // VREG_AND_CHIP_RESET_BOD
    // brown-out detection control
    // 0x000000f0 [7:4]   : VSEL (0x9): threshold select
    // 0x00000001 [0]     : EN (1): enable
    io_rw_32 bod;

    _REG_(VREG_AND_CHIP_RESET_CHIP_RESET_OFFSET) // VREG_AND_CHIP_RESET_CHIP_RESET
    // Chip reset control and status
    // 0x01000000 [24]    : PSM_RESTART_FLAG (0): This is set by psm_restart from the debugger
    // 0x00100000 [20]    : HAD_PSM_RESTART (0): Last reset was from the debug port
    // 0x00010000 [16]    : HAD_RUN (0): Last reset was from the RUN pin
    // 0x00000100 [8]     : HAD_POR (0): Last reset was from the power-on reset or brown-out detection blocks
    io_rw_32 chip_reset;
} vreg_and_chip_reset_hw_t;

#define vreg_and_chip_reset_hw ((vreg_and_chip_reset_hw_t *)VREG_AND_CHIP_RESET_BASE)

#endif
