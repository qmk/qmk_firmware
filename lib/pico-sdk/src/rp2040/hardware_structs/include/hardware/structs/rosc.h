// THIS HEADER FILE IS AUTOMATICALLY GENERATED -- DO NOT EDIT

/*
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_ROSC_H
#define _HARDWARE_STRUCTS_ROSC_H

#include "hardware/address_mapped.h"
#include "hardware/regs/rosc.h"

// Reference to datasheet: https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#tab-registerlist_rosc
//
// The _REG_ macro is intended to help make the register navigable in your IDE (for example, using the "Go to Definition" feature)
// _REG_(x) will link to the corresponding register in hardware/regs/rosc.h.
//
// Bit-field descriptions are of the form:
// BITMASK [BITRANGE]: FIELDNAME (RESETVALUE): DESCRIPTION

typedef struct {
    _REG_(ROSC_CTRL_OFFSET) // ROSC_CTRL
    // Ring Oscillator control
    // 0x00fff000 [23:12] : ENABLE (0): On power-up this field is initialised to ENABLE
    // 0x00000fff [11:0]  : FREQ_RANGE (0xaa0): Controls the number of delay stages in the ROSC ring
    io_rw_32 ctrl;

    _REG_(ROSC_FREQA_OFFSET) // ROSC_FREQA
    // The FREQA & FREQB registers control the frequency by controlling the drive strength of each stage
    // 0xffff0000 [31:16] : PASSWD (0): Set to 0x9696 to apply the settings
    // 0x00007000 [14:12] : DS3 (0): Stage 3 drive strength
    // 0x00000700 [10:8]  : DS2 (0): Stage 2 drive strength
    // 0x00000070 [6:4]   : DS1 (0): Stage 1 drive strength
    // 0x00000007 [2:0]   : DS0 (0): Stage 0 drive strength
    io_rw_32 freqa;

    _REG_(ROSC_FREQB_OFFSET) // ROSC_FREQB
    // For a detailed description see freqa register
    // 0xffff0000 [31:16] : PASSWD (0): Set to 0x9696 to apply the settings
    // 0x00007000 [14:12] : DS7 (0): Stage 7 drive strength
    // 0x00000700 [10:8]  : DS6 (0): Stage 6 drive strength
    // 0x00000070 [6:4]   : DS5 (0): Stage 5 drive strength
    // 0x00000007 [2:0]   : DS4 (0): Stage 4 drive strength
    io_rw_32 freqb;

    _REG_(ROSC_DORMANT_OFFSET) // ROSC_DORMANT
    // Ring Oscillator pause control
    io_rw_32 dormant;

    _REG_(ROSC_DIV_OFFSET) // ROSC_DIV
    // Controls the output divider
    // 0x00000fff [11:0]  : DIV (0): set to 0xaa0 + div where
    io_rw_32 div;

    _REG_(ROSC_PHASE_OFFSET) // ROSC_PHASE
    // Controls the phase shifted output
    // 0x00000ff0 [11:4]  : PASSWD (0): set to 0xaa
    // 0x00000008 [3]     : ENABLE (1): enable the phase-shifted output
    // 0x00000004 [2]     : FLIP (0): invert the phase-shifted output
    // 0x00000003 [1:0]   : SHIFT (0): phase shift the phase-shifted output by SHIFT input clocks
    io_rw_32 phase;

    _REG_(ROSC_STATUS_OFFSET) // ROSC_STATUS
    // Ring Oscillator Status
    // 0x80000000 [31]    : STABLE (0): Oscillator is running and stable
    // 0x01000000 [24]    : BADWRITE (0): An invalid value has been written to CTRL_ENABLE or CTRL_FREQ_RANGE or FREQA or...
    // 0x00010000 [16]    : DIV_RUNNING (0): post-divider is running
    // 0x00001000 [12]    : ENABLED (0): Oscillator is enabled but not necessarily running and stable
    io_rw_32 status;

    _REG_(ROSC_RANDOMBIT_OFFSET) // ROSC_RANDOMBIT
    // This just reads the state of the oscillator output so randomness is compromised if the ring oscillator is stopped or...
    // 0x00000001 [0]     : RANDOMBIT (1)
    io_ro_32 randombit;

    _REG_(ROSC_COUNT_OFFSET) // ROSC_COUNT
    // A down counter running at the ROSC frequency which counts to zero and stops
    // 0x000000ff [7:0]   : COUNT (0)
    io_rw_32 count;
} rosc_hw_t;

#define rosc_hw ((rosc_hw_t *)ROSC_BASE)

#endif
