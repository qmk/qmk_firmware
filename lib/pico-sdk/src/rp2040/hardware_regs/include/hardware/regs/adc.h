/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : ADC
// Version        : 2
// Bus type       : apb
// Description    : Control and data interface to SAR ADC
// =============================================================================
#ifndef HARDWARE_REGS_ADC_DEFINED
#define HARDWARE_REGS_ADC_DEFINED
// =============================================================================
// Register    : ADC_CS
// Description : ADC Control and Status
#define ADC_CS_OFFSET _u(0x00000000)
#define ADC_CS_BITS   _u(0x001f770f)
#define ADC_CS_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : ADC_CS_RROBIN
// Description : Round-robin sampling. 1 bit per channel. Set all bits to 0 to
//               disable.
//               Otherwise, the ADC will cycle through each enabled channel in a
//               round-robin fashion.
//               The first channel to be sampled will be the one currently
//               indicated by AINSEL.
//               AINSEL will be updated after each conversion with the
//               newly-selected channel.
#define ADC_CS_RROBIN_RESET  _u(0x00)
#define ADC_CS_RROBIN_BITS   _u(0x001f0000)
#define ADC_CS_RROBIN_MSB    _u(20)
#define ADC_CS_RROBIN_LSB    _u(16)
#define ADC_CS_RROBIN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ADC_CS_AINSEL
// Description : Select analog mux input. Updated automatically in round-robin
//               mode.
#define ADC_CS_AINSEL_RESET  _u(0x0)
#define ADC_CS_AINSEL_BITS   _u(0x00007000)
#define ADC_CS_AINSEL_MSB    _u(14)
#define ADC_CS_AINSEL_LSB    _u(12)
#define ADC_CS_AINSEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ADC_CS_ERR_STICKY
// Description : Some past ADC conversion encountered an error. Write 1 to
//               clear.
#define ADC_CS_ERR_STICKY_RESET  _u(0x0)
#define ADC_CS_ERR_STICKY_BITS   _u(0x00000400)
#define ADC_CS_ERR_STICKY_MSB    _u(10)
#define ADC_CS_ERR_STICKY_LSB    _u(10)
#define ADC_CS_ERR_STICKY_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : ADC_CS_ERR
// Description : The most recent ADC conversion encountered an error; result is
//               undefined or noisy.
#define ADC_CS_ERR_RESET  _u(0x0)
#define ADC_CS_ERR_BITS   _u(0x00000200)
#define ADC_CS_ERR_MSB    _u(9)
#define ADC_CS_ERR_LSB    _u(9)
#define ADC_CS_ERR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : ADC_CS_READY
// Description : 1 if the ADC is ready to start a new conversion. Implies any
//               previous conversion has completed.
//               0 whilst conversion in progress.
#define ADC_CS_READY_RESET  _u(0x0)
#define ADC_CS_READY_BITS   _u(0x00000100)
#define ADC_CS_READY_MSB    _u(8)
#define ADC_CS_READY_LSB    _u(8)
#define ADC_CS_READY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : ADC_CS_START_MANY
// Description : Continuously perform conversions whilst this bit is 1. A new
//               conversion will start immediately after the previous finishes.
#define ADC_CS_START_MANY_RESET  _u(0x0)
#define ADC_CS_START_MANY_BITS   _u(0x00000008)
#define ADC_CS_START_MANY_MSB    _u(3)
#define ADC_CS_START_MANY_LSB    _u(3)
#define ADC_CS_START_MANY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ADC_CS_START_ONCE
// Description : Start a single conversion. Self-clearing. Ignored if start_many
//               is asserted.
#define ADC_CS_START_ONCE_RESET  _u(0x0)
#define ADC_CS_START_ONCE_BITS   _u(0x00000004)
#define ADC_CS_START_ONCE_MSB    _u(2)
#define ADC_CS_START_ONCE_LSB    _u(2)
#define ADC_CS_START_ONCE_ACCESS "SC"
// -----------------------------------------------------------------------------
// Field       : ADC_CS_TS_EN
// Description : Power on temperature sensor. 1 - enabled. 0 - disabled.
#define ADC_CS_TS_EN_RESET  _u(0x0)
#define ADC_CS_TS_EN_BITS   _u(0x00000002)
#define ADC_CS_TS_EN_MSB    _u(1)
#define ADC_CS_TS_EN_LSB    _u(1)
#define ADC_CS_TS_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ADC_CS_EN
// Description : Power on ADC and enable its clock.
//               1 - enabled. 0 - disabled.
#define ADC_CS_EN_RESET  _u(0x0)
#define ADC_CS_EN_BITS   _u(0x00000001)
#define ADC_CS_EN_MSB    _u(0)
#define ADC_CS_EN_LSB    _u(0)
#define ADC_CS_EN_ACCESS "RW"
// =============================================================================
// Register    : ADC_RESULT
// Description : Result of most recent ADC conversion
#define ADC_RESULT_OFFSET _u(0x00000004)
#define ADC_RESULT_BITS   _u(0x00000fff)
#define ADC_RESULT_RESET  _u(0x00000000)
#define ADC_RESULT_MSB    _u(11)
#define ADC_RESULT_LSB    _u(0)
#define ADC_RESULT_ACCESS "RO"
// =============================================================================
// Register    : ADC_FCS
// Description : FIFO control and status
#define ADC_FCS_OFFSET _u(0x00000008)
#define ADC_FCS_BITS   _u(0x0f0f0f0f)
#define ADC_FCS_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : ADC_FCS_THRESH
// Description : DREQ/IRQ asserted when level >= threshold
#define ADC_FCS_THRESH_RESET  _u(0x0)
#define ADC_FCS_THRESH_BITS   _u(0x0f000000)
#define ADC_FCS_THRESH_MSB    _u(27)
#define ADC_FCS_THRESH_LSB    _u(24)
#define ADC_FCS_THRESH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ADC_FCS_LEVEL
// Description : The number of conversion results currently waiting in the FIFO
#define ADC_FCS_LEVEL_RESET  _u(0x0)
#define ADC_FCS_LEVEL_BITS   _u(0x000f0000)
#define ADC_FCS_LEVEL_MSB    _u(19)
#define ADC_FCS_LEVEL_LSB    _u(16)
#define ADC_FCS_LEVEL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : ADC_FCS_OVER
// Description : 1 if the FIFO has been overflowed. Write 1 to clear.
#define ADC_FCS_OVER_RESET  _u(0x0)
#define ADC_FCS_OVER_BITS   _u(0x00000800)
#define ADC_FCS_OVER_MSB    _u(11)
#define ADC_FCS_OVER_LSB    _u(11)
#define ADC_FCS_OVER_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : ADC_FCS_UNDER
// Description : 1 if the FIFO has been underflowed. Write 1 to clear.
#define ADC_FCS_UNDER_RESET  _u(0x0)
#define ADC_FCS_UNDER_BITS   _u(0x00000400)
#define ADC_FCS_UNDER_MSB    _u(10)
#define ADC_FCS_UNDER_LSB    _u(10)
#define ADC_FCS_UNDER_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : ADC_FCS_FULL
// Description : None
#define ADC_FCS_FULL_RESET  _u(0x0)
#define ADC_FCS_FULL_BITS   _u(0x00000200)
#define ADC_FCS_FULL_MSB    _u(9)
#define ADC_FCS_FULL_LSB    _u(9)
#define ADC_FCS_FULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : ADC_FCS_EMPTY
// Description : None
#define ADC_FCS_EMPTY_RESET  _u(0x0)
#define ADC_FCS_EMPTY_BITS   _u(0x00000100)
#define ADC_FCS_EMPTY_MSB    _u(8)
#define ADC_FCS_EMPTY_LSB    _u(8)
#define ADC_FCS_EMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : ADC_FCS_DREQ_EN
// Description : If 1: assert DMA requests when FIFO contains data
#define ADC_FCS_DREQ_EN_RESET  _u(0x0)
#define ADC_FCS_DREQ_EN_BITS   _u(0x00000008)
#define ADC_FCS_DREQ_EN_MSB    _u(3)
#define ADC_FCS_DREQ_EN_LSB    _u(3)
#define ADC_FCS_DREQ_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ADC_FCS_ERR
// Description : If 1: conversion error bit appears in the FIFO alongside the
//               result
#define ADC_FCS_ERR_RESET  _u(0x0)
#define ADC_FCS_ERR_BITS   _u(0x00000004)
#define ADC_FCS_ERR_MSB    _u(2)
#define ADC_FCS_ERR_LSB    _u(2)
#define ADC_FCS_ERR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ADC_FCS_SHIFT
// Description : If 1: FIFO results are right-shifted to be one byte in size.
//               Enables DMA to byte buffers.
#define ADC_FCS_SHIFT_RESET  _u(0x0)
#define ADC_FCS_SHIFT_BITS   _u(0x00000002)
#define ADC_FCS_SHIFT_MSB    _u(1)
#define ADC_FCS_SHIFT_LSB    _u(1)
#define ADC_FCS_SHIFT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ADC_FCS_EN
// Description : If 1: write result to the FIFO after each conversion.
#define ADC_FCS_EN_RESET  _u(0x0)
#define ADC_FCS_EN_BITS   _u(0x00000001)
#define ADC_FCS_EN_MSB    _u(0)
#define ADC_FCS_EN_LSB    _u(0)
#define ADC_FCS_EN_ACCESS "RW"
// =============================================================================
// Register    : ADC_FIFO
// Description : Conversion result FIFO
#define ADC_FIFO_OFFSET _u(0x0000000c)
#define ADC_FIFO_BITS   _u(0x00008fff)
#define ADC_FIFO_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : ADC_FIFO_ERR
// Description : 1 if this particular sample experienced a conversion error.
//               Remains in the same location if the sample is shifted.
#define ADC_FIFO_ERR_RESET  "-"
#define ADC_FIFO_ERR_BITS   _u(0x00008000)
#define ADC_FIFO_ERR_MSB    _u(15)
#define ADC_FIFO_ERR_LSB    _u(15)
#define ADC_FIFO_ERR_ACCESS "RF"
// -----------------------------------------------------------------------------
// Field       : ADC_FIFO_VAL
// Description : None
#define ADC_FIFO_VAL_RESET  "-"
#define ADC_FIFO_VAL_BITS   _u(0x00000fff)
#define ADC_FIFO_VAL_MSB    _u(11)
#define ADC_FIFO_VAL_LSB    _u(0)
#define ADC_FIFO_VAL_ACCESS "RF"
// =============================================================================
// Register    : ADC_DIV
// Description : Clock divider. If non-zero, CS_START_MANY will start
//               conversions
//               at regular intervals rather than back-to-back.
//               The divider is reset when either of these fields are written.
//               Total period is 1 + INT + FRAC / 256
#define ADC_DIV_OFFSET _u(0x00000010)
#define ADC_DIV_BITS   _u(0x00ffffff)
#define ADC_DIV_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : ADC_DIV_INT
// Description : Integer part of clock divisor.
#define ADC_DIV_INT_RESET  _u(0x0000)
#define ADC_DIV_INT_BITS   _u(0x00ffff00)
#define ADC_DIV_INT_MSB    _u(23)
#define ADC_DIV_INT_LSB    _u(8)
#define ADC_DIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : ADC_DIV_FRAC
// Description : Fractional part of clock divisor. First-order delta-sigma.
#define ADC_DIV_FRAC_RESET  _u(0x00)
#define ADC_DIV_FRAC_BITS   _u(0x000000ff)
#define ADC_DIV_FRAC_MSB    _u(7)
#define ADC_DIV_FRAC_LSB    _u(0)
#define ADC_DIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : ADC_INTR
// Description : Raw Interrupts
#define ADC_INTR_OFFSET _u(0x00000014)
#define ADC_INTR_BITS   _u(0x00000001)
#define ADC_INTR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : ADC_INTR_FIFO
// Description : Triggered when the sample FIFO reaches a certain level.
//               This level can be programmed via the FCS_THRESH field.
#define ADC_INTR_FIFO_RESET  _u(0x0)
#define ADC_INTR_FIFO_BITS   _u(0x00000001)
#define ADC_INTR_FIFO_MSB    _u(0)
#define ADC_INTR_FIFO_LSB    _u(0)
#define ADC_INTR_FIFO_ACCESS "RO"
// =============================================================================
// Register    : ADC_INTE
// Description : Interrupt Enable
#define ADC_INTE_OFFSET _u(0x00000018)
#define ADC_INTE_BITS   _u(0x00000001)
#define ADC_INTE_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : ADC_INTE_FIFO
// Description : Triggered when the sample FIFO reaches a certain level.
//               This level can be programmed via the FCS_THRESH field.
#define ADC_INTE_FIFO_RESET  _u(0x0)
#define ADC_INTE_FIFO_BITS   _u(0x00000001)
#define ADC_INTE_FIFO_MSB    _u(0)
#define ADC_INTE_FIFO_LSB    _u(0)
#define ADC_INTE_FIFO_ACCESS "RW"
// =============================================================================
// Register    : ADC_INTF
// Description : Interrupt Force
#define ADC_INTF_OFFSET _u(0x0000001c)
#define ADC_INTF_BITS   _u(0x00000001)
#define ADC_INTF_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : ADC_INTF_FIFO
// Description : Triggered when the sample FIFO reaches a certain level.
//               This level can be programmed via the FCS_THRESH field.
#define ADC_INTF_FIFO_RESET  _u(0x0)
#define ADC_INTF_FIFO_BITS   _u(0x00000001)
#define ADC_INTF_FIFO_MSB    _u(0)
#define ADC_INTF_FIFO_LSB    _u(0)
#define ADC_INTF_FIFO_ACCESS "RW"
// =============================================================================
// Register    : ADC_INTS
// Description : Interrupt status after masking & forcing
#define ADC_INTS_OFFSET _u(0x00000020)
#define ADC_INTS_BITS   _u(0x00000001)
#define ADC_INTS_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : ADC_INTS_FIFO
// Description : Triggered when the sample FIFO reaches a certain level.
//               This level can be programmed via the FCS_THRESH field.
#define ADC_INTS_FIFO_RESET  _u(0x0)
#define ADC_INTS_FIFO_BITS   _u(0x00000001)
#define ADC_INTS_FIFO_MSB    _u(0)
#define ADC_INTS_FIFO_LSB    _u(0)
#define ADC_INTS_FIFO_ACCESS "RO"
// =============================================================================
#endif // HARDWARE_REGS_ADC_DEFINED
