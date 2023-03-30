// THIS HEADER FILE IS AUTOMATICALLY GENERATED -- DO NOT EDIT

/*
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_WATCHDOG_H
#define _HARDWARE_STRUCTS_WATCHDOG_H

#include "hardware/address_mapped.h"
#include "hardware/regs/watchdog.h"

// Reference to datasheet: https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#tab-registerlist_watchdog
//
// The _REG_ macro is intended to help make the register navigable in your IDE (for example, using the "Go to Definition" feature)
// _REG_(x) will link to the corresponding register in hardware/regs/watchdog.h.
//
// Bit-field descriptions are of the form:
// BITMASK [BITRANGE]: FIELDNAME (RESETVALUE): DESCRIPTION

typedef struct {
    _REG_(WATCHDOG_CTRL_OFFSET) // WATCHDOG_CTRL
    // Watchdog control
    // 0x80000000 [31]    : TRIGGER (0): Trigger a watchdog reset
    // 0x40000000 [30]    : ENABLE (0): When not enabled the watchdog timer is paused
    // 0x04000000 [26]    : PAUSE_DBG1 (1): Pause the watchdog timer when processor 1 is in debug mode
    // 0x02000000 [25]    : PAUSE_DBG0 (1): Pause the watchdog timer when processor 0 is in debug mode
    // 0x01000000 [24]    : PAUSE_JTAG (1): Pause the watchdog timer when JTAG is accessing the bus fabric
    // 0x00ffffff [23:0]  : TIME (0): Indicates the number of ticks / 2 (see errata RP2040-E1) before a watchdog reset will...
    io_rw_32 ctrl;

    _REG_(WATCHDOG_LOAD_OFFSET) // WATCHDOG_LOAD
    // Load the watchdog timer
    // 0x00ffffff [23:0]  : LOAD (0)
    io_wo_32 load;

    _REG_(WATCHDOG_REASON_OFFSET) // WATCHDOG_REASON
    // Logs the reason for the last reset
    // 0x00000002 [1]     : FORCE (0)
    // 0x00000001 [0]     : TIMER (0)
    io_ro_32 reason;

    _REG_(WATCHDOG_SCRATCH0_OFFSET) // WATCHDOG_SCRATCH0
    // (Description copied from array index 0 register WATCHDOG_SCRATCH0 applies similarly to other array indexes)
    //
    // Scratch register
    io_rw_32 scratch[8];

    _REG_(WATCHDOG_TICK_OFFSET) // WATCHDOG_TICK
    // Controls the tick generator
    // 0x000ff800 [19:11] : COUNT (0): Count down timer: the remaining number clk_tick cycles before the next tick is generated
    // 0x00000400 [10]    : RUNNING (0): Is the tick generator running?
    // 0x00000200 [9]     : ENABLE (1): start / stop tick generation
    // 0x000001ff [8:0]   : CYCLES (0): Total number of clk_tick cycles before the next tick
    io_rw_32 tick;
} watchdog_hw_t;

#define watchdog_hw ((watchdog_hw_t *)WATCHDOG_BASE)

#endif
