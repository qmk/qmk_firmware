// THIS HEADER FILE IS AUTOMATICALLY GENERATED -- DO NOT EDIT

/*
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_SYSTICK_H
#define _HARDWARE_STRUCTS_SYSTICK_H

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
    _REG_(M0PLUS_SYST_CSR_OFFSET) // M0PLUS_SYST_CSR
    // Use the SysTick Control and Status Register to enable the SysTick features
    // 0x00010000 [16]    : COUNTFLAG (0): Returns 1 if timer counted to 0 since last time this was read
    // 0x00000004 [2]     : CLKSOURCE (0): SysTick clock source
    // 0x00000002 [1]     : TICKINT (0): Enables SysTick exception request:
    // 0x00000001 [0]     : ENABLE (0): Enable SysTick counter:
    io_rw_32 csr;

    _REG_(M0PLUS_SYST_RVR_OFFSET) // M0PLUS_SYST_RVR
    // Use the SysTick Reload Value Register to specify the start value to load into the current value register when the...
    // 0x00ffffff [23:0]  : RELOAD (0): Value to load into the SysTick Current Value Register when the counter reaches 0
    io_rw_32 rvr;

    _REG_(M0PLUS_SYST_CVR_OFFSET) // M0PLUS_SYST_CVR
    // Use the SysTick Current Value Register to find the current value in the register
    // 0x00ffffff [23:0]  : CURRENT (0): Reads return the current value of the SysTick counter
    io_rw_32 cvr;

    _REG_(M0PLUS_SYST_CALIB_OFFSET) // M0PLUS_SYST_CALIB
    // Use the SysTick Calibration Value Register to enable software to scale to any required speed using divide and multiply
    // 0x80000000 [31]    : NOREF (0): If reads as 1, the Reference clock is not provided - the CLKSOURCE bit of the...
    // 0x40000000 [30]    : SKEW (0): If reads as 1, the calibration value for 10ms is inexact (due to clock frequency)
    // 0x00ffffff [23:0]  : TENMS (0): An optional Reload value to be used for 10ms (100Hz) timing, subject to system clock...
    io_ro_32 calib;
} systick_hw_t;

#define systick_hw ((systick_hw_t *)(PPB_BASE + M0PLUS_SYST_CSR_OFFSET))

#endif
