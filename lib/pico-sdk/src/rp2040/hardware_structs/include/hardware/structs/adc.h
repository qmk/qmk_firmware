// THIS HEADER FILE IS AUTOMATICALLY GENERATED -- DO NOT EDIT

/*
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_ADC_H
#define _HARDWARE_STRUCTS_ADC_H

#include "hardware/address_mapped.h"
#include "hardware/regs/adc.h"

// Reference to datasheet: https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#tab-registerlist_adc
//
// The _REG_ macro is intended to help make the register navigable in your IDE (for example, using the "Go to Definition" feature)
// _REG_(x) will link to the corresponding register in hardware/regs/adc.h.
//
// Bit-field descriptions are of the form:
// BITMASK [BITRANGE]: FIELDNAME (RESETVALUE): DESCRIPTION

typedef struct {
    _REG_(ADC_CS_OFFSET) // ADC_CS
    // ADC Control and Status
    // 0x001f0000 [20:16] : RROBIN (0): Round-robin sampling
    // 0x00007000 [14:12] : AINSEL (0): Select analog mux input
    // 0x00000400 [10]    : ERR_STICKY (0): Some past ADC conversion encountered an error
    // 0x00000200 [9]     : ERR (0): The most recent ADC conversion encountered an error; result is undefined or noisy
    // 0x00000100 [8]     : READY (0): 1 if the ADC is ready to start a new conversion
    // 0x00000008 [3]     : START_MANY (0): Continuously perform conversions whilst this bit is 1
    // 0x00000004 [2]     : START_ONCE (0): Start a single conversion
    // 0x00000002 [1]     : TS_EN (0): Power on temperature sensor
    // 0x00000001 [0]     : EN (0): Power on ADC and enable its clock
    io_rw_32 cs;

    _REG_(ADC_RESULT_OFFSET) // ADC_RESULT
    // Result of most recent ADC conversion
    // 0x00000fff [11:0]  : RESULT (0)
    io_ro_32 result;

    _REG_(ADC_FCS_OFFSET) // ADC_FCS
    // FIFO control and status
    // 0x0f000000 [27:24] : THRESH (0): DREQ/IRQ asserted when level >= threshold
    // 0x000f0000 [19:16] : LEVEL (0): The number of conversion results currently waiting in the FIFO
    // 0x00000800 [11]    : OVER (0): 1 if the FIFO has been overflowed
    // 0x00000400 [10]    : UNDER (0): 1 if the FIFO has been underflowed
    // 0x00000200 [9]     : FULL (0)
    // 0x00000100 [8]     : EMPTY (0)
    // 0x00000008 [3]     : DREQ_EN (0): If 1: assert DMA requests when FIFO contains data
    // 0x00000004 [2]     : ERR (0): If 1: conversion error bit appears in the FIFO alongside the result
    // 0x00000002 [1]     : SHIFT (0): If 1: FIFO results are right-shifted to be one byte in size
    // 0x00000001 [0]     : EN (0): If 1: write result to the FIFO after each conversion
    io_rw_32 fcs;

    _REG_(ADC_FIFO_OFFSET) // ADC_FIFO
    // Conversion result FIFO
    // 0x00008000 [15]    : ERR (0): 1 if this particular sample experienced a conversion error
    // 0x00000fff [11:0]  : VAL (0)
    io_ro_32 fifo;

    _REG_(ADC_DIV_OFFSET) // ADC_DIV
    // Clock divider
    // 0x00ffff00 [23:8]  : INT (0): Integer part of clock divisor
    // 0x000000ff [7:0]   : FRAC (0): Fractional part of clock divisor
    io_rw_32 div;

    _REG_(ADC_INTR_OFFSET) // ADC_INTR
    // Raw Interrupts
    // 0x00000001 [0]     : FIFO (0): Triggered when the sample FIFO reaches a certain level
    io_ro_32 intr;

    _REG_(ADC_INTE_OFFSET) // ADC_INTE
    // Interrupt Enable
    // 0x00000001 [0]     : FIFO (0): Triggered when the sample FIFO reaches a certain level
    io_rw_32 inte;

    _REG_(ADC_INTF_OFFSET) // ADC_INTF
    // Interrupt Force
    // 0x00000001 [0]     : FIFO (0): Triggered when the sample FIFO reaches a certain level
    io_rw_32 intf;

    _REG_(ADC_INTS_OFFSET) // ADC_INTS
    // Interrupt status after masking & forcing
    // 0x00000001 [0]     : FIFO (0): Triggered when the sample FIFO reaches a certain level
    io_ro_32 ints;
} adc_hw_t;

#define adc_hw ((adc_hw_t *)ADC_BASE)

#endif
