// THIS HEADER FILE IS AUTOMATICALLY GENERATED -- DO NOT EDIT

/*
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_RTC_H
#define _HARDWARE_STRUCTS_RTC_H

#include "hardware/address_mapped.h"
#include "hardware/regs/rtc.h"

// Reference to datasheet: https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#tab-registerlist_rtc
//
// The _REG_ macro is intended to help make the register navigable in your IDE (for example, using the "Go to Definition" feature)
// _REG_(x) will link to the corresponding register in hardware/regs/rtc.h.
//
// Bit-field descriptions are of the form:
// BITMASK [BITRANGE]: FIELDNAME (RESETVALUE): DESCRIPTION

typedef struct {
    _REG_(RTC_CLKDIV_M1_OFFSET) // RTC_CLKDIV_M1
    // Divider minus 1 for the 1 second counter
    // 0x0000ffff [15:0]  : CLKDIV_M1 (0)
    io_rw_32 clkdiv_m1;

    _REG_(RTC_SETUP_0_OFFSET) // RTC_SETUP_0
    // RTC setup register 0
    // 0x00fff000 [23:12] : YEAR (0): Year
    // 0x00000f00 [11:8]  : MONTH (0): Month (1
    // 0x0000001f [4:0]   : DAY (0): Day of the month (1
    io_rw_32 setup_0;

    _REG_(RTC_SETUP_1_OFFSET) // RTC_SETUP_1
    // RTC setup register 1
    // 0x07000000 [26:24] : DOTW (0): Day of the week: 1-Monday
    // 0x001f0000 [20:16] : HOUR (0): Hours
    // 0x00003f00 [13:8]  : MIN (0): Minutes
    // 0x0000003f [5:0]   : SEC (0): Seconds
    io_rw_32 setup_1;

    _REG_(RTC_CTRL_OFFSET) // RTC_CTRL
    // RTC Control and status
    // 0x00000100 [8]     : FORCE_NOTLEAPYEAR (0): If set, leapyear is forced off
    // 0x00000010 [4]     : LOAD (0): Load RTC
    // 0x00000002 [1]     : RTC_ACTIVE (0): RTC enabled (running)
    // 0x00000001 [0]     : RTC_ENABLE (0): Enable RTC
    io_rw_32 ctrl;

    _REG_(RTC_IRQ_SETUP_0_OFFSET) // RTC_IRQ_SETUP_0
    // Interrupt setup register 0
    // 0x20000000 [29]    : MATCH_ACTIVE (0)
    // 0x10000000 [28]    : MATCH_ENA (0): Global match enable
    // 0x04000000 [26]    : YEAR_ENA (0): Enable year matching
    // 0x02000000 [25]    : MONTH_ENA (0): Enable month matching
    // 0x01000000 [24]    : DAY_ENA (0): Enable day matching
    // 0x00fff000 [23:12] : YEAR (0): Year
    // 0x00000f00 [11:8]  : MONTH (0): Month (1
    // 0x0000001f [4:0]   : DAY (0): Day of the month (1
    io_rw_32 irq_setup_0;

    _REG_(RTC_IRQ_SETUP_1_OFFSET) // RTC_IRQ_SETUP_1
    // Interrupt setup register 1
    // 0x80000000 [31]    : DOTW_ENA (0): Enable day of the week matching
    // 0x40000000 [30]    : HOUR_ENA (0): Enable hour matching
    // 0x20000000 [29]    : MIN_ENA (0): Enable minute matching
    // 0x10000000 [28]    : SEC_ENA (0): Enable second matching
    // 0x07000000 [26:24] : DOTW (0): Day of the week
    // 0x001f0000 [20:16] : HOUR (0): Hours
    // 0x00003f00 [13:8]  : MIN (0): Minutes
    // 0x0000003f [5:0]   : SEC (0): Seconds
    io_rw_32 irq_setup_1;

    _REG_(RTC_RTC_1_OFFSET) // RTC_RTC_1
    // RTC register 1
    // 0x00fff000 [23:12] : YEAR (0): Year
    // 0x00000f00 [11:8]  : MONTH (0): Month (1
    // 0x0000001f [4:0]   : DAY (0): Day of the month (1
    io_ro_32 rtc_1;

    _REG_(RTC_RTC_0_OFFSET) // RTC_RTC_0
    // RTC register 0
    // 0x07000000 [26:24] : DOTW (0): Day of the week
    // 0x001f0000 [20:16] : HOUR (0): Hours
    // 0x00003f00 [13:8]  : MIN (0): Minutes
    // 0x0000003f [5:0]   : SEC (0): Seconds
    io_ro_32 rtc_0;

    _REG_(RTC_INTR_OFFSET) // RTC_INTR
    // Raw Interrupts
    // 0x00000001 [0]     : RTC (0)
    io_ro_32 intr;

    _REG_(RTC_INTE_OFFSET) // RTC_INTE
    // Interrupt Enable
    // 0x00000001 [0]     : RTC (0)
    io_rw_32 inte;

    _REG_(RTC_INTF_OFFSET) // RTC_INTF
    // Interrupt Force
    // 0x00000001 [0]     : RTC (0)
    io_rw_32 intf;

    _REG_(RTC_INTS_OFFSET) // RTC_INTS
    // Interrupt status after masking & forcing
    // 0x00000001 [0]     : RTC (0)
    io_ro_32 ints;
} rtc_hw_t;

#define rtc_hw ((rtc_hw_t *)RTC_BASE)

#endif
