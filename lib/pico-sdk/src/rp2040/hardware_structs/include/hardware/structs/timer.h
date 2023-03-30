// THIS HEADER FILE IS AUTOMATICALLY GENERATED -- DO NOT EDIT

/*
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_TIMER_H
#define _HARDWARE_STRUCTS_TIMER_H

#include "hardware/address_mapped.h"
#include "hardware/regs/timer.h"

// Reference to datasheet: https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#tab-registerlist_timer
//
// The _REG_ macro is intended to help make the register navigable in your IDE (for example, using the "Go to Definition" feature)
// _REG_(x) will link to the corresponding register in hardware/regs/timer.h.
//
// Bit-field descriptions are of the form:
// BITMASK [BITRANGE]: FIELDNAME (RESETVALUE): DESCRIPTION

typedef struct {
    _REG_(TIMER_TIMEHW_OFFSET) // TIMER_TIMEHW
    // Write to bits 63:32 of time
    io_wo_32 timehw;

    _REG_(TIMER_TIMELW_OFFSET) // TIMER_TIMELW
    // Write to bits 31:0 of time
    io_wo_32 timelw;

    _REG_(TIMER_TIMEHR_OFFSET) // TIMER_TIMEHR
    // Read from bits 63:32 of time
    io_ro_32 timehr;

    _REG_(TIMER_TIMELR_OFFSET) // TIMER_TIMELR
    // Read from bits 31:0 of time
    io_ro_32 timelr;

    _REG_(TIMER_ALARM0_OFFSET) // TIMER_ALARM0
    // (Description copied from array index 0 register TIMER_ALARM0 applies similarly to other array indexes)
    //
    // Arm alarm 0, and configure the time it will fire
    io_rw_32 alarm[NUM_TIMERS]; // 4

    _REG_(TIMER_ARMED_OFFSET) // TIMER_ARMED
    // Indicates the armed/disarmed status of each alarm
    // 0x0000000f [3:0]   : ARMED (0)
    io_rw_32 armed;

    _REG_(TIMER_TIMERAWH_OFFSET) // TIMER_TIMERAWH
    // Raw read from bits 63:32 of time (no side effects)
    io_ro_32 timerawh;

    _REG_(TIMER_TIMERAWL_OFFSET) // TIMER_TIMERAWL
    // Raw read from bits 31:0 of time (no side effects)
    io_ro_32 timerawl;

    _REG_(TIMER_DBGPAUSE_OFFSET) // TIMER_DBGPAUSE
    // Set bits high to enable pause when the corresponding debug ports are active
    // 0x00000004 [2]     : DBG1 (1): Pause when processor 1 is in debug mode
    // 0x00000002 [1]     : DBG0 (1): Pause when processor 0 is in debug mode
    io_rw_32 dbgpause;

    _REG_(TIMER_PAUSE_OFFSET) // TIMER_PAUSE
    // Set high to pause the timer
    // 0x00000001 [0]     : PAUSE (0)
    io_rw_32 pause;

    _REG_(TIMER_INTR_OFFSET) // TIMER_INTR
    // Raw Interrupts
    // 0x00000008 [3]     : ALARM_3 (0)
    // 0x00000004 [2]     : ALARM_2 (0)
    // 0x00000002 [1]     : ALARM_1 (0)
    // 0x00000001 [0]     : ALARM_0 (0)
    io_rw_32 intr;

    _REG_(TIMER_INTE_OFFSET) // TIMER_INTE
    // Interrupt Enable
    // 0x00000008 [3]     : ALARM_3 (0)
    // 0x00000004 [2]     : ALARM_2 (0)
    // 0x00000002 [1]     : ALARM_1 (0)
    // 0x00000001 [0]     : ALARM_0 (0)
    io_rw_32 inte;

    _REG_(TIMER_INTF_OFFSET) // TIMER_INTF
    // Interrupt Force
    // 0x00000008 [3]     : ALARM_3 (0)
    // 0x00000004 [2]     : ALARM_2 (0)
    // 0x00000002 [1]     : ALARM_1 (0)
    // 0x00000001 [0]     : ALARM_0 (0)
    io_rw_32 intf;

    _REG_(TIMER_INTS_OFFSET) // TIMER_INTS
    // Interrupt status after masking & forcing
    // 0x00000008 [3]     : ALARM_3 (0)
    // 0x00000004 [2]     : ALARM_2 (0)
    // 0x00000002 [1]     : ALARM_1 (0)
    // 0x00000001 [0]     : ALARM_0 (0)
    io_ro_32 ints;
} timer_hw_t;

#define timer_hw ((timer_hw_t *)TIMER_BASE)

static_assert( NUM_TIMERS == 4, "");

#endif
