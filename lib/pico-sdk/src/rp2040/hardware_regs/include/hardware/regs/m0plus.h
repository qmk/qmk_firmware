/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : M0PLUS
// Version        : 1
// Bus type       : ahbl
// Description    : None
// =============================================================================
#ifndef HARDWARE_REGS_M0PLUS_DEFINED
#define HARDWARE_REGS_M0PLUS_DEFINED
// =============================================================================
// Register    : M0PLUS_SYST_CSR
// Description : Use the SysTick Control and Status Register to enable the
//               SysTick features.
#define M0PLUS_SYST_CSR_OFFSET _u(0x0000e010)
#define M0PLUS_SYST_CSR_BITS   _u(0x00010007)
#define M0PLUS_SYST_CSR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_SYST_CSR_COUNTFLAG
// Description : Returns 1 if timer counted to 0 since last time this was read.
//               Clears on read by application or debugger.
#define M0PLUS_SYST_CSR_COUNTFLAG_RESET  _u(0x0)
#define M0PLUS_SYST_CSR_COUNTFLAG_BITS   _u(0x00010000)
#define M0PLUS_SYST_CSR_COUNTFLAG_MSB    _u(16)
#define M0PLUS_SYST_CSR_COUNTFLAG_LSB    _u(16)
#define M0PLUS_SYST_CSR_COUNTFLAG_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_SYST_CSR_CLKSOURCE
// Description : SysTick clock source. Always reads as one if SYST_CALIB reports
//               NOREF.
//               Selects the SysTick timer clock source:
//               0 = External reference clock.
//               1 = Processor clock.
#define M0PLUS_SYST_CSR_CLKSOURCE_RESET  _u(0x0)
#define M0PLUS_SYST_CSR_CLKSOURCE_BITS   _u(0x00000004)
#define M0PLUS_SYST_CSR_CLKSOURCE_MSB    _u(2)
#define M0PLUS_SYST_CSR_CLKSOURCE_LSB    _u(2)
#define M0PLUS_SYST_CSR_CLKSOURCE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_SYST_CSR_TICKINT
// Description : Enables SysTick exception request:
//               0 = Counting down to zero does not assert the SysTick exception
//               request.
//               1 = Counting down to zero to asserts the SysTick exception
//               request.
#define M0PLUS_SYST_CSR_TICKINT_RESET  _u(0x0)
#define M0PLUS_SYST_CSR_TICKINT_BITS   _u(0x00000002)
#define M0PLUS_SYST_CSR_TICKINT_MSB    _u(1)
#define M0PLUS_SYST_CSR_TICKINT_LSB    _u(1)
#define M0PLUS_SYST_CSR_TICKINT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_SYST_CSR_ENABLE
// Description : Enable SysTick counter:
//               0 = Counter disabled.
//               1 = Counter enabled.
#define M0PLUS_SYST_CSR_ENABLE_RESET  _u(0x0)
#define M0PLUS_SYST_CSR_ENABLE_BITS   _u(0x00000001)
#define M0PLUS_SYST_CSR_ENABLE_MSB    _u(0)
#define M0PLUS_SYST_CSR_ENABLE_LSB    _u(0)
#define M0PLUS_SYST_CSR_ENABLE_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_SYST_RVR
// Description : Use the SysTick Reload Value Register to specify the start
//               value to load into the current value register when the counter
//               reaches 0. It can be any value between 0 and 0x00FFFFFF. A
//               start value of 0 is possible, but has no effect because the
//               SysTick interrupt and COUNTFLAG are activated when counting
//               from 1 to 0. The reset value of this register is UNKNOWN.
//               To generate a multi-shot timer with a period of N processor
//               clock cycles, use a RELOAD value of N-1. For example, if the
//               SysTick interrupt is required every 100 clock pulses, set
//               RELOAD to 99.
#define M0PLUS_SYST_RVR_OFFSET _u(0x0000e014)
#define M0PLUS_SYST_RVR_BITS   _u(0x00ffffff)
#define M0PLUS_SYST_RVR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_SYST_RVR_RELOAD
// Description : Value to load into the SysTick Current Value Register when the
//               counter reaches 0.
#define M0PLUS_SYST_RVR_RELOAD_RESET  _u(0x000000)
#define M0PLUS_SYST_RVR_RELOAD_BITS   _u(0x00ffffff)
#define M0PLUS_SYST_RVR_RELOAD_MSB    _u(23)
#define M0PLUS_SYST_RVR_RELOAD_LSB    _u(0)
#define M0PLUS_SYST_RVR_RELOAD_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_SYST_CVR
// Description : Use the SysTick Current Value Register to find the current
//               value in the register. The reset value of this register is
//               UNKNOWN.
#define M0PLUS_SYST_CVR_OFFSET _u(0x0000e018)
#define M0PLUS_SYST_CVR_BITS   _u(0x00ffffff)
#define M0PLUS_SYST_CVR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_SYST_CVR_CURRENT
// Description : Reads return the current value of the SysTick counter. This
//               register is write-clear. Writing to it with any value clears
//               the register to 0. Clearing this register also clears the
//               COUNTFLAG bit of the SysTick Control and Status Register.
#define M0PLUS_SYST_CVR_CURRENT_RESET  _u(0x000000)
#define M0PLUS_SYST_CVR_CURRENT_BITS   _u(0x00ffffff)
#define M0PLUS_SYST_CVR_CURRENT_MSB    _u(23)
#define M0PLUS_SYST_CVR_CURRENT_LSB    _u(0)
#define M0PLUS_SYST_CVR_CURRENT_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_SYST_CALIB
// Description : Use the SysTick Calibration Value Register to enable software
//               to scale to any required speed using divide and multiply.
#define M0PLUS_SYST_CALIB_OFFSET _u(0x0000e01c)
#define M0PLUS_SYST_CALIB_BITS   _u(0xc0ffffff)
#define M0PLUS_SYST_CALIB_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_SYST_CALIB_NOREF
// Description : If reads as 1, the Reference clock is not provided - the
//               CLKSOURCE bit of the SysTick Control and Status register will
//               be forced to 1 and cannot be cleared to 0.
#define M0PLUS_SYST_CALIB_NOREF_RESET  _u(0x0)
#define M0PLUS_SYST_CALIB_NOREF_BITS   _u(0x80000000)
#define M0PLUS_SYST_CALIB_NOREF_MSB    _u(31)
#define M0PLUS_SYST_CALIB_NOREF_LSB    _u(31)
#define M0PLUS_SYST_CALIB_NOREF_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_SYST_CALIB_SKEW
// Description : If reads as 1, the calibration value for 10ms is inexact (due
//               to clock frequency).
#define M0PLUS_SYST_CALIB_SKEW_RESET  _u(0x0)
#define M0PLUS_SYST_CALIB_SKEW_BITS   _u(0x40000000)
#define M0PLUS_SYST_CALIB_SKEW_MSB    _u(30)
#define M0PLUS_SYST_CALIB_SKEW_LSB    _u(30)
#define M0PLUS_SYST_CALIB_SKEW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_SYST_CALIB_TENMS
// Description : An optional Reload value to be used for 10ms (100Hz) timing,
//               subject to system clock skew errors. If the value reads as 0,
//               the calibration value is not known.
#define M0PLUS_SYST_CALIB_TENMS_RESET  _u(0x000000)
#define M0PLUS_SYST_CALIB_TENMS_BITS   _u(0x00ffffff)
#define M0PLUS_SYST_CALIB_TENMS_MSB    _u(23)
#define M0PLUS_SYST_CALIB_TENMS_LSB    _u(0)
#define M0PLUS_SYST_CALIB_TENMS_ACCESS "RO"
// =============================================================================
// Register    : M0PLUS_NVIC_ISER
// Description : Use the Interrupt Set-Enable Register to enable interrupts and
//               determine which interrupts are currently enabled.
//               If a pending interrupt is enabled, the NVIC activates the
//               interrupt based on its priority. If an interrupt is not
//               enabled, asserting its interrupt signal changes the interrupt
//               state to pending, but the NVIC never activates the interrupt,
//               regardless of its priority.
#define M0PLUS_NVIC_ISER_OFFSET _u(0x0000e100)
#define M0PLUS_NVIC_ISER_BITS   _u(0xffffffff)
#define M0PLUS_NVIC_ISER_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_ISER_SETENA
// Description : Interrupt set-enable bits.
//               Write:
//               0 = No effect.
//               1 = Enable interrupt.
//               Read:
//               0 = Interrupt disabled.
//               1 = Interrupt enabled.
#define M0PLUS_NVIC_ISER_SETENA_RESET  _u(0x00000000)
#define M0PLUS_NVIC_ISER_SETENA_BITS   _u(0xffffffff)
#define M0PLUS_NVIC_ISER_SETENA_MSB    _u(31)
#define M0PLUS_NVIC_ISER_SETENA_LSB    _u(0)
#define M0PLUS_NVIC_ISER_SETENA_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_NVIC_ICER
// Description : Use the Interrupt Clear-Enable Registers to disable interrupts
//               and determine which interrupts are currently enabled.
#define M0PLUS_NVIC_ICER_OFFSET _u(0x0000e180)
#define M0PLUS_NVIC_ICER_BITS   _u(0xffffffff)
#define M0PLUS_NVIC_ICER_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_ICER_CLRENA
// Description : Interrupt clear-enable bits.
//               Write:
//               0 = No effect.
//               1 = Disable interrupt.
//               Read:
//               0 = Interrupt disabled.
//               1 = Interrupt enabled.
#define M0PLUS_NVIC_ICER_CLRENA_RESET  _u(0x00000000)
#define M0PLUS_NVIC_ICER_CLRENA_BITS   _u(0xffffffff)
#define M0PLUS_NVIC_ICER_CLRENA_MSB    _u(31)
#define M0PLUS_NVIC_ICER_CLRENA_LSB    _u(0)
#define M0PLUS_NVIC_ICER_CLRENA_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_NVIC_ISPR
// Description : The NVIC_ISPR forces interrupts into the pending state, and
//               shows which interrupts are pending.
#define M0PLUS_NVIC_ISPR_OFFSET _u(0x0000e200)
#define M0PLUS_NVIC_ISPR_BITS   _u(0xffffffff)
#define M0PLUS_NVIC_ISPR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_ISPR_SETPEND
// Description : Interrupt set-pending bits.
//               Write:
//               0 = No effect.
//               1 = Changes interrupt state to pending.
//               Read:
//               0 = Interrupt is not pending.
//               1 = Interrupt is pending.
//               Note: Writing 1 to the NVIC_ISPR bit corresponding to:
//               An interrupt that is pending has no effect.
//               A disabled interrupt sets the state of that interrupt to
//               pending.
#define M0PLUS_NVIC_ISPR_SETPEND_RESET  _u(0x00000000)
#define M0PLUS_NVIC_ISPR_SETPEND_BITS   _u(0xffffffff)
#define M0PLUS_NVIC_ISPR_SETPEND_MSB    _u(31)
#define M0PLUS_NVIC_ISPR_SETPEND_LSB    _u(0)
#define M0PLUS_NVIC_ISPR_SETPEND_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_NVIC_ICPR
// Description : Use the Interrupt Clear-Pending Register to clear pending
//               interrupts and determine which interrupts are currently
//               pending.
#define M0PLUS_NVIC_ICPR_OFFSET _u(0x0000e280)
#define M0PLUS_NVIC_ICPR_BITS   _u(0xffffffff)
#define M0PLUS_NVIC_ICPR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_ICPR_CLRPEND
// Description : Interrupt clear-pending bits.
//               Write:
//               0 = No effect.
//               1 = Removes pending state and interrupt.
//               Read:
//               0 = Interrupt is not pending.
//               1 = Interrupt is pending.
#define M0PLUS_NVIC_ICPR_CLRPEND_RESET  _u(0x00000000)
#define M0PLUS_NVIC_ICPR_CLRPEND_BITS   _u(0xffffffff)
#define M0PLUS_NVIC_ICPR_CLRPEND_MSB    _u(31)
#define M0PLUS_NVIC_ICPR_CLRPEND_LSB    _u(0)
#define M0PLUS_NVIC_ICPR_CLRPEND_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_NVIC_IPR0
// Description : Use the Interrupt Priority Registers to assign a priority from
//               0 to 3 to each of the available interrupts. 0 is the highest
//               priority, and 3 is the lowest.
//               Note: Writing 1 to an NVIC_ICPR bit does not affect the active
//               state of the corresponding interrupt.
//               These registers are only word-accessible
#define M0PLUS_NVIC_IPR0_OFFSET _u(0x0000e400)
#define M0PLUS_NVIC_IPR0_BITS   _u(0xc0c0c0c0)
#define M0PLUS_NVIC_IPR0_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR0_IP_3
// Description : Priority of interrupt 3
#define M0PLUS_NVIC_IPR0_IP_3_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR0_IP_3_BITS   _u(0xc0000000)
#define M0PLUS_NVIC_IPR0_IP_3_MSB    _u(31)
#define M0PLUS_NVIC_IPR0_IP_3_LSB    _u(30)
#define M0PLUS_NVIC_IPR0_IP_3_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR0_IP_2
// Description : Priority of interrupt 2
#define M0PLUS_NVIC_IPR0_IP_2_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR0_IP_2_BITS   _u(0x00c00000)
#define M0PLUS_NVIC_IPR0_IP_2_MSB    _u(23)
#define M0PLUS_NVIC_IPR0_IP_2_LSB    _u(22)
#define M0PLUS_NVIC_IPR0_IP_2_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR0_IP_1
// Description : Priority of interrupt 1
#define M0PLUS_NVIC_IPR0_IP_1_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR0_IP_1_BITS   _u(0x0000c000)
#define M0PLUS_NVIC_IPR0_IP_1_MSB    _u(15)
#define M0PLUS_NVIC_IPR0_IP_1_LSB    _u(14)
#define M0PLUS_NVIC_IPR0_IP_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR0_IP_0
// Description : Priority of interrupt 0
#define M0PLUS_NVIC_IPR0_IP_0_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR0_IP_0_BITS   _u(0x000000c0)
#define M0PLUS_NVIC_IPR0_IP_0_MSB    _u(7)
#define M0PLUS_NVIC_IPR0_IP_0_LSB    _u(6)
#define M0PLUS_NVIC_IPR0_IP_0_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_NVIC_IPR1
// Description : Use the Interrupt Priority Registers to assign a priority from
//               0 to 3 to each of the available interrupts. 0 is the highest
//               priority, and 3 is the lowest.
#define M0PLUS_NVIC_IPR1_OFFSET _u(0x0000e404)
#define M0PLUS_NVIC_IPR1_BITS   _u(0xc0c0c0c0)
#define M0PLUS_NVIC_IPR1_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR1_IP_7
// Description : Priority of interrupt 7
#define M0PLUS_NVIC_IPR1_IP_7_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR1_IP_7_BITS   _u(0xc0000000)
#define M0PLUS_NVIC_IPR1_IP_7_MSB    _u(31)
#define M0PLUS_NVIC_IPR1_IP_7_LSB    _u(30)
#define M0PLUS_NVIC_IPR1_IP_7_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR1_IP_6
// Description : Priority of interrupt 6
#define M0PLUS_NVIC_IPR1_IP_6_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR1_IP_6_BITS   _u(0x00c00000)
#define M0PLUS_NVIC_IPR1_IP_6_MSB    _u(23)
#define M0PLUS_NVIC_IPR1_IP_6_LSB    _u(22)
#define M0PLUS_NVIC_IPR1_IP_6_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR1_IP_5
// Description : Priority of interrupt 5
#define M0PLUS_NVIC_IPR1_IP_5_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR1_IP_5_BITS   _u(0x0000c000)
#define M0PLUS_NVIC_IPR1_IP_5_MSB    _u(15)
#define M0PLUS_NVIC_IPR1_IP_5_LSB    _u(14)
#define M0PLUS_NVIC_IPR1_IP_5_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR1_IP_4
// Description : Priority of interrupt 4
#define M0PLUS_NVIC_IPR1_IP_4_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR1_IP_4_BITS   _u(0x000000c0)
#define M0PLUS_NVIC_IPR1_IP_4_MSB    _u(7)
#define M0PLUS_NVIC_IPR1_IP_4_LSB    _u(6)
#define M0PLUS_NVIC_IPR1_IP_4_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_NVIC_IPR2
// Description : Use the Interrupt Priority Registers to assign a priority from
//               0 to 3 to each of the available interrupts. 0 is the highest
//               priority, and 3 is the lowest.
#define M0PLUS_NVIC_IPR2_OFFSET _u(0x0000e408)
#define M0PLUS_NVIC_IPR2_BITS   _u(0xc0c0c0c0)
#define M0PLUS_NVIC_IPR2_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR2_IP_11
// Description : Priority of interrupt 11
#define M0PLUS_NVIC_IPR2_IP_11_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR2_IP_11_BITS   _u(0xc0000000)
#define M0PLUS_NVIC_IPR2_IP_11_MSB    _u(31)
#define M0PLUS_NVIC_IPR2_IP_11_LSB    _u(30)
#define M0PLUS_NVIC_IPR2_IP_11_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR2_IP_10
// Description : Priority of interrupt 10
#define M0PLUS_NVIC_IPR2_IP_10_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR2_IP_10_BITS   _u(0x00c00000)
#define M0PLUS_NVIC_IPR2_IP_10_MSB    _u(23)
#define M0PLUS_NVIC_IPR2_IP_10_LSB    _u(22)
#define M0PLUS_NVIC_IPR2_IP_10_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR2_IP_9
// Description : Priority of interrupt 9
#define M0PLUS_NVIC_IPR2_IP_9_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR2_IP_9_BITS   _u(0x0000c000)
#define M0PLUS_NVIC_IPR2_IP_9_MSB    _u(15)
#define M0PLUS_NVIC_IPR2_IP_9_LSB    _u(14)
#define M0PLUS_NVIC_IPR2_IP_9_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR2_IP_8
// Description : Priority of interrupt 8
#define M0PLUS_NVIC_IPR2_IP_8_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR2_IP_8_BITS   _u(0x000000c0)
#define M0PLUS_NVIC_IPR2_IP_8_MSB    _u(7)
#define M0PLUS_NVIC_IPR2_IP_8_LSB    _u(6)
#define M0PLUS_NVIC_IPR2_IP_8_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_NVIC_IPR3
// Description : Use the Interrupt Priority Registers to assign a priority from
//               0 to 3 to each of the available interrupts. 0 is the highest
//               priority, and 3 is the lowest.
#define M0PLUS_NVIC_IPR3_OFFSET _u(0x0000e40c)
#define M0PLUS_NVIC_IPR3_BITS   _u(0xc0c0c0c0)
#define M0PLUS_NVIC_IPR3_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR3_IP_15
// Description : Priority of interrupt 15
#define M0PLUS_NVIC_IPR3_IP_15_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR3_IP_15_BITS   _u(0xc0000000)
#define M0PLUS_NVIC_IPR3_IP_15_MSB    _u(31)
#define M0PLUS_NVIC_IPR3_IP_15_LSB    _u(30)
#define M0PLUS_NVIC_IPR3_IP_15_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR3_IP_14
// Description : Priority of interrupt 14
#define M0PLUS_NVIC_IPR3_IP_14_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR3_IP_14_BITS   _u(0x00c00000)
#define M0PLUS_NVIC_IPR3_IP_14_MSB    _u(23)
#define M0PLUS_NVIC_IPR3_IP_14_LSB    _u(22)
#define M0PLUS_NVIC_IPR3_IP_14_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR3_IP_13
// Description : Priority of interrupt 13
#define M0PLUS_NVIC_IPR3_IP_13_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR3_IP_13_BITS   _u(0x0000c000)
#define M0PLUS_NVIC_IPR3_IP_13_MSB    _u(15)
#define M0PLUS_NVIC_IPR3_IP_13_LSB    _u(14)
#define M0PLUS_NVIC_IPR3_IP_13_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR3_IP_12
// Description : Priority of interrupt 12
#define M0PLUS_NVIC_IPR3_IP_12_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR3_IP_12_BITS   _u(0x000000c0)
#define M0PLUS_NVIC_IPR3_IP_12_MSB    _u(7)
#define M0PLUS_NVIC_IPR3_IP_12_LSB    _u(6)
#define M0PLUS_NVIC_IPR3_IP_12_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_NVIC_IPR4
// Description : Use the Interrupt Priority Registers to assign a priority from
//               0 to 3 to each of the available interrupts. 0 is the highest
//               priority, and 3 is the lowest.
#define M0PLUS_NVIC_IPR4_OFFSET _u(0x0000e410)
#define M0PLUS_NVIC_IPR4_BITS   _u(0xc0c0c0c0)
#define M0PLUS_NVIC_IPR4_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR4_IP_19
// Description : Priority of interrupt 19
#define M0PLUS_NVIC_IPR4_IP_19_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR4_IP_19_BITS   _u(0xc0000000)
#define M0PLUS_NVIC_IPR4_IP_19_MSB    _u(31)
#define M0PLUS_NVIC_IPR4_IP_19_LSB    _u(30)
#define M0PLUS_NVIC_IPR4_IP_19_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR4_IP_18
// Description : Priority of interrupt 18
#define M0PLUS_NVIC_IPR4_IP_18_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR4_IP_18_BITS   _u(0x00c00000)
#define M0PLUS_NVIC_IPR4_IP_18_MSB    _u(23)
#define M0PLUS_NVIC_IPR4_IP_18_LSB    _u(22)
#define M0PLUS_NVIC_IPR4_IP_18_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR4_IP_17
// Description : Priority of interrupt 17
#define M0PLUS_NVIC_IPR4_IP_17_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR4_IP_17_BITS   _u(0x0000c000)
#define M0PLUS_NVIC_IPR4_IP_17_MSB    _u(15)
#define M0PLUS_NVIC_IPR4_IP_17_LSB    _u(14)
#define M0PLUS_NVIC_IPR4_IP_17_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR4_IP_16
// Description : Priority of interrupt 16
#define M0PLUS_NVIC_IPR4_IP_16_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR4_IP_16_BITS   _u(0x000000c0)
#define M0PLUS_NVIC_IPR4_IP_16_MSB    _u(7)
#define M0PLUS_NVIC_IPR4_IP_16_LSB    _u(6)
#define M0PLUS_NVIC_IPR4_IP_16_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_NVIC_IPR5
// Description : Use the Interrupt Priority Registers to assign a priority from
//               0 to 3 to each of the available interrupts. 0 is the highest
//               priority, and 3 is the lowest.
#define M0PLUS_NVIC_IPR5_OFFSET _u(0x0000e414)
#define M0PLUS_NVIC_IPR5_BITS   _u(0xc0c0c0c0)
#define M0PLUS_NVIC_IPR5_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR5_IP_23
// Description : Priority of interrupt 23
#define M0PLUS_NVIC_IPR5_IP_23_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR5_IP_23_BITS   _u(0xc0000000)
#define M0PLUS_NVIC_IPR5_IP_23_MSB    _u(31)
#define M0PLUS_NVIC_IPR5_IP_23_LSB    _u(30)
#define M0PLUS_NVIC_IPR5_IP_23_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR5_IP_22
// Description : Priority of interrupt 22
#define M0PLUS_NVIC_IPR5_IP_22_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR5_IP_22_BITS   _u(0x00c00000)
#define M0PLUS_NVIC_IPR5_IP_22_MSB    _u(23)
#define M0PLUS_NVIC_IPR5_IP_22_LSB    _u(22)
#define M0PLUS_NVIC_IPR5_IP_22_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR5_IP_21
// Description : Priority of interrupt 21
#define M0PLUS_NVIC_IPR5_IP_21_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR5_IP_21_BITS   _u(0x0000c000)
#define M0PLUS_NVIC_IPR5_IP_21_MSB    _u(15)
#define M0PLUS_NVIC_IPR5_IP_21_LSB    _u(14)
#define M0PLUS_NVIC_IPR5_IP_21_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR5_IP_20
// Description : Priority of interrupt 20
#define M0PLUS_NVIC_IPR5_IP_20_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR5_IP_20_BITS   _u(0x000000c0)
#define M0PLUS_NVIC_IPR5_IP_20_MSB    _u(7)
#define M0PLUS_NVIC_IPR5_IP_20_LSB    _u(6)
#define M0PLUS_NVIC_IPR5_IP_20_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_NVIC_IPR6
// Description : Use the Interrupt Priority Registers to assign a priority from
//               0 to 3 to each of the available interrupts. 0 is the highest
//               priority, and 3 is the lowest.
#define M0PLUS_NVIC_IPR6_OFFSET _u(0x0000e418)
#define M0PLUS_NVIC_IPR6_BITS   _u(0xc0c0c0c0)
#define M0PLUS_NVIC_IPR6_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR6_IP_27
// Description : Priority of interrupt 27
#define M0PLUS_NVIC_IPR6_IP_27_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR6_IP_27_BITS   _u(0xc0000000)
#define M0PLUS_NVIC_IPR6_IP_27_MSB    _u(31)
#define M0PLUS_NVIC_IPR6_IP_27_LSB    _u(30)
#define M0PLUS_NVIC_IPR6_IP_27_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR6_IP_26
// Description : Priority of interrupt 26
#define M0PLUS_NVIC_IPR6_IP_26_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR6_IP_26_BITS   _u(0x00c00000)
#define M0PLUS_NVIC_IPR6_IP_26_MSB    _u(23)
#define M0PLUS_NVIC_IPR6_IP_26_LSB    _u(22)
#define M0PLUS_NVIC_IPR6_IP_26_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR6_IP_25
// Description : Priority of interrupt 25
#define M0PLUS_NVIC_IPR6_IP_25_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR6_IP_25_BITS   _u(0x0000c000)
#define M0PLUS_NVIC_IPR6_IP_25_MSB    _u(15)
#define M0PLUS_NVIC_IPR6_IP_25_LSB    _u(14)
#define M0PLUS_NVIC_IPR6_IP_25_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR6_IP_24
// Description : Priority of interrupt 24
#define M0PLUS_NVIC_IPR6_IP_24_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR6_IP_24_BITS   _u(0x000000c0)
#define M0PLUS_NVIC_IPR6_IP_24_MSB    _u(7)
#define M0PLUS_NVIC_IPR6_IP_24_LSB    _u(6)
#define M0PLUS_NVIC_IPR6_IP_24_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_NVIC_IPR7
// Description : Use the Interrupt Priority Registers to assign a priority from
//               0 to 3 to each of the available interrupts. 0 is the highest
//               priority, and 3 is the lowest.
#define M0PLUS_NVIC_IPR7_OFFSET _u(0x0000e41c)
#define M0PLUS_NVIC_IPR7_BITS   _u(0xc0c0c0c0)
#define M0PLUS_NVIC_IPR7_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR7_IP_31
// Description : Priority of interrupt 31
#define M0PLUS_NVIC_IPR7_IP_31_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR7_IP_31_BITS   _u(0xc0000000)
#define M0PLUS_NVIC_IPR7_IP_31_MSB    _u(31)
#define M0PLUS_NVIC_IPR7_IP_31_LSB    _u(30)
#define M0PLUS_NVIC_IPR7_IP_31_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR7_IP_30
// Description : Priority of interrupt 30
#define M0PLUS_NVIC_IPR7_IP_30_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR7_IP_30_BITS   _u(0x00c00000)
#define M0PLUS_NVIC_IPR7_IP_30_MSB    _u(23)
#define M0PLUS_NVIC_IPR7_IP_30_LSB    _u(22)
#define M0PLUS_NVIC_IPR7_IP_30_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR7_IP_29
// Description : Priority of interrupt 29
#define M0PLUS_NVIC_IPR7_IP_29_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR7_IP_29_BITS   _u(0x0000c000)
#define M0PLUS_NVIC_IPR7_IP_29_MSB    _u(15)
#define M0PLUS_NVIC_IPR7_IP_29_LSB    _u(14)
#define M0PLUS_NVIC_IPR7_IP_29_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_NVIC_IPR7_IP_28
// Description : Priority of interrupt 28
#define M0PLUS_NVIC_IPR7_IP_28_RESET  _u(0x0)
#define M0PLUS_NVIC_IPR7_IP_28_BITS   _u(0x000000c0)
#define M0PLUS_NVIC_IPR7_IP_28_MSB    _u(7)
#define M0PLUS_NVIC_IPR7_IP_28_LSB    _u(6)
#define M0PLUS_NVIC_IPR7_IP_28_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_CPUID
// Description : Read the CPU ID Base Register to determine: the ID number of
//               the processor core, the version number of the processor core,
//               the implementation details of the processor core.
#define M0PLUS_CPUID_OFFSET _u(0x0000ed00)
#define M0PLUS_CPUID_BITS   _u(0xffffffff)
#define M0PLUS_CPUID_RESET  _u(0x410cc601)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_CPUID_IMPLEMENTER
// Description : Implementor code: 0x41 = ARM
#define M0PLUS_CPUID_IMPLEMENTER_RESET  _u(0x41)
#define M0PLUS_CPUID_IMPLEMENTER_BITS   _u(0xff000000)
#define M0PLUS_CPUID_IMPLEMENTER_MSB    _u(31)
#define M0PLUS_CPUID_IMPLEMENTER_LSB    _u(24)
#define M0PLUS_CPUID_IMPLEMENTER_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_CPUID_VARIANT
// Description : Major revision number n in the rnpm revision status:
//               0x0 = Revision 0.
#define M0PLUS_CPUID_VARIANT_RESET  _u(0x0)
#define M0PLUS_CPUID_VARIANT_BITS   _u(0x00f00000)
#define M0PLUS_CPUID_VARIANT_MSB    _u(23)
#define M0PLUS_CPUID_VARIANT_LSB    _u(20)
#define M0PLUS_CPUID_VARIANT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_CPUID_ARCHITECTURE
// Description : Constant that defines the architecture of the processor:
//               0xC = ARMv6-M architecture.
#define M0PLUS_CPUID_ARCHITECTURE_RESET  _u(0xc)
#define M0PLUS_CPUID_ARCHITECTURE_BITS   _u(0x000f0000)
#define M0PLUS_CPUID_ARCHITECTURE_MSB    _u(19)
#define M0PLUS_CPUID_ARCHITECTURE_LSB    _u(16)
#define M0PLUS_CPUID_ARCHITECTURE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_CPUID_PARTNO
// Description : Number of processor within family: 0xC60 = Cortex-M0+
#define M0PLUS_CPUID_PARTNO_RESET  _u(0xc60)
#define M0PLUS_CPUID_PARTNO_BITS   _u(0x0000fff0)
#define M0PLUS_CPUID_PARTNO_MSB    _u(15)
#define M0PLUS_CPUID_PARTNO_LSB    _u(4)
#define M0PLUS_CPUID_PARTNO_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_CPUID_REVISION
// Description : Minor revision number m in the rnpm revision status:
//               0x1 = Patch 1.
#define M0PLUS_CPUID_REVISION_RESET  _u(0x1)
#define M0PLUS_CPUID_REVISION_BITS   _u(0x0000000f)
#define M0PLUS_CPUID_REVISION_MSB    _u(3)
#define M0PLUS_CPUID_REVISION_LSB    _u(0)
#define M0PLUS_CPUID_REVISION_ACCESS "RO"
// =============================================================================
// Register    : M0PLUS_ICSR
// Description : Use the Interrupt Control State Register to set a pending
//               Non-Maskable Interrupt (NMI), set or clear a pending PendSV,
//               set or clear a pending SysTick, check for pending exceptions,
//               check the vector number of the highest priority pended
//               exception, check the vector number of the active exception.
#define M0PLUS_ICSR_OFFSET _u(0x0000ed04)
#define M0PLUS_ICSR_BITS   _u(0x9edff1ff)
#define M0PLUS_ICSR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_ICSR_NMIPENDSET
// Description : Setting this bit will activate an NMI. Since NMI is the highest
//               priority exception, it will activate as soon as it is
//               registered.
//               NMI set-pending bit.
//               Write:
//               0 = No effect.
//               1 = Changes NMI exception state to pending.
//               Read:
//               0 = NMI exception is not pending.
//               1 = NMI exception is pending.
//               Because NMI is the highest-priority exception, normally the
//               processor enters the NMI
//               exception handler as soon as it detects a write of 1 to this
//               bit. Entering the handler then clears
//               this bit to 0. This means a read of this bit by the NMI
//               exception handler returns 1 only if the
//               NMI signal is reasserted while the processor is executing that
//               handler.
#define M0PLUS_ICSR_NMIPENDSET_RESET  _u(0x0)
#define M0PLUS_ICSR_NMIPENDSET_BITS   _u(0x80000000)
#define M0PLUS_ICSR_NMIPENDSET_MSB    _u(31)
#define M0PLUS_ICSR_NMIPENDSET_LSB    _u(31)
#define M0PLUS_ICSR_NMIPENDSET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_ICSR_PENDSVSET
// Description : PendSV set-pending bit.
//               Write:
//               0 = No effect.
//               1 = Changes PendSV exception state to pending.
//               Read:
//               0 = PendSV exception is not pending.
//               1 = PendSV exception is pending.
//               Writing 1 to this bit is the only way to set the PendSV
//               exception state to pending.
#define M0PLUS_ICSR_PENDSVSET_RESET  _u(0x0)
#define M0PLUS_ICSR_PENDSVSET_BITS   _u(0x10000000)
#define M0PLUS_ICSR_PENDSVSET_MSB    _u(28)
#define M0PLUS_ICSR_PENDSVSET_LSB    _u(28)
#define M0PLUS_ICSR_PENDSVSET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_ICSR_PENDSVCLR
// Description : PendSV clear-pending bit.
//               Write:
//               0 = No effect.
//               1 = Removes the pending state from the PendSV exception.
#define M0PLUS_ICSR_PENDSVCLR_RESET  _u(0x0)
#define M0PLUS_ICSR_PENDSVCLR_BITS   _u(0x08000000)
#define M0PLUS_ICSR_PENDSVCLR_MSB    _u(27)
#define M0PLUS_ICSR_PENDSVCLR_LSB    _u(27)
#define M0PLUS_ICSR_PENDSVCLR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_ICSR_PENDSTSET
// Description : SysTick exception set-pending bit.
//               Write:
//               0 = No effect.
//               1 = Changes SysTick exception state to pending.
//               Read:
//               0 = SysTick exception is not pending.
//               1 = SysTick exception is pending.
#define M0PLUS_ICSR_PENDSTSET_RESET  _u(0x0)
#define M0PLUS_ICSR_PENDSTSET_BITS   _u(0x04000000)
#define M0PLUS_ICSR_PENDSTSET_MSB    _u(26)
#define M0PLUS_ICSR_PENDSTSET_LSB    _u(26)
#define M0PLUS_ICSR_PENDSTSET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_ICSR_PENDSTCLR
// Description : SysTick exception clear-pending bit.
//               Write:
//               0 = No effect.
//               1 = Removes the pending state from the SysTick exception.
//               This bit is WO. On a register read its value is Unknown.
#define M0PLUS_ICSR_PENDSTCLR_RESET  _u(0x0)
#define M0PLUS_ICSR_PENDSTCLR_BITS   _u(0x02000000)
#define M0PLUS_ICSR_PENDSTCLR_MSB    _u(25)
#define M0PLUS_ICSR_PENDSTCLR_LSB    _u(25)
#define M0PLUS_ICSR_PENDSTCLR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_ICSR_ISRPREEMPT
// Description : The system can only access this bit when the core is halted. It
//               indicates that a pending interrupt is to be taken in the next
//               running cycle. If C_MASKINTS is clear in the Debug Halting
//               Control and Status Register, the interrupt is serviced.
#define M0PLUS_ICSR_ISRPREEMPT_RESET  _u(0x0)
#define M0PLUS_ICSR_ISRPREEMPT_BITS   _u(0x00800000)
#define M0PLUS_ICSR_ISRPREEMPT_MSB    _u(23)
#define M0PLUS_ICSR_ISRPREEMPT_LSB    _u(23)
#define M0PLUS_ICSR_ISRPREEMPT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_ICSR_ISRPENDING
// Description : External interrupt pending flag
#define M0PLUS_ICSR_ISRPENDING_RESET  _u(0x0)
#define M0PLUS_ICSR_ISRPENDING_BITS   _u(0x00400000)
#define M0PLUS_ICSR_ISRPENDING_MSB    _u(22)
#define M0PLUS_ICSR_ISRPENDING_LSB    _u(22)
#define M0PLUS_ICSR_ISRPENDING_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_ICSR_VECTPENDING
// Description : Indicates the exception number for the highest priority pending
//               exception: 0 = no pending exceptions. Non zero = The pending
//               state includes the effect of memory-mapped enable and mask
//               registers. It does not include the PRIMASK special-purpose
//               register qualifier.
#define M0PLUS_ICSR_VECTPENDING_RESET  _u(0x000)
#define M0PLUS_ICSR_VECTPENDING_BITS   _u(0x001ff000)
#define M0PLUS_ICSR_VECTPENDING_MSB    _u(20)
#define M0PLUS_ICSR_VECTPENDING_LSB    _u(12)
#define M0PLUS_ICSR_VECTPENDING_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_ICSR_VECTACTIVE
// Description : Active exception number field. Reset clears the VECTACTIVE
//               field.
#define M0PLUS_ICSR_VECTACTIVE_RESET  _u(0x000)
#define M0PLUS_ICSR_VECTACTIVE_BITS   _u(0x000001ff)
#define M0PLUS_ICSR_VECTACTIVE_MSB    _u(8)
#define M0PLUS_ICSR_VECTACTIVE_LSB    _u(0)
#define M0PLUS_ICSR_VECTACTIVE_ACCESS "RO"
// =============================================================================
// Register    : M0PLUS_VTOR
// Description : The VTOR holds the vector table offset address.
#define M0PLUS_VTOR_OFFSET _u(0x0000ed08)
#define M0PLUS_VTOR_BITS   _u(0xffffff00)
#define M0PLUS_VTOR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_VTOR_TBLOFF
// Description : Bits [31:8] of the indicate the vector table offset address.
#define M0PLUS_VTOR_TBLOFF_RESET  _u(0x000000)
#define M0PLUS_VTOR_TBLOFF_BITS   _u(0xffffff00)
#define M0PLUS_VTOR_TBLOFF_MSB    _u(31)
#define M0PLUS_VTOR_TBLOFF_LSB    _u(8)
#define M0PLUS_VTOR_TBLOFF_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_AIRCR
// Description : Use the Application Interrupt and Reset Control Register to:
//               determine data endianness, clear all active state information
//               from debug halt mode, request a system reset.
#define M0PLUS_AIRCR_OFFSET _u(0x0000ed0c)
#define M0PLUS_AIRCR_BITS   _u(0xffff8006)
#define M0PLUS_AIRCR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_AIRCR_VECTKEY
// Description : Register key:
//               Reads as Unknown
//               On writes, write 0x05FA to VECTKEY, otherwise the write is
//               ignored.
#define M0PLUS_AIRCR_VECTKEY_RESET  _u(0x0000)
#define M0PLUS_AIRCR_VECTKEY_BITS   _u(0xffff0000)
#define M0PLUS_AIRCR_VECTKEY_MSB    _u(31)
#define M0PLUS_AIRCR_VECTKEY_LSB    _u(16)
#define M0PLUS_AIRCR_VECTKEY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_AIRCR_ENDIANESS
// Description : Data endianness implemented:
//               0 = Little-endian.
#define M0PLUS_AIRCR_ENDIANESS_RESET  _u(0x0)
#define M0PLUS_AIRCR_ENDIANESS_BITS   _u(0x00008000)
#define M0PLUS_AIRCR_ENDIANESS_MSB    _u(15)
#define M0PLUS_AIRCR_ENDIANESS_LSB    _u(15)
#define M0PLUS_AIRCR_ENDIANESS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_AIRCR_SYSRESETREQ
// Description : Writing 1 to this bit causes the SYSRESETREQ signal to the
//               outer system to be asserted to request a reset. The intention
//               is to force a large system reset of all major components except
//               for debug. The C_HALT bit in the DHCSR is cleared as a result
//               of the system reset requested. The debugger does not lose
//               contact with the device.
#define M0PLUS_AIRCR_SYSRESETREQ_RESET  _u(0x0)
#define M0PLUS_AIRCR_SYSRESETREQ_BITS   _u(0x00000004)
#define M0PLUS_AIRCR_SYSRESETREQ_MSB    _u(2)
#define M0PLUS_AIRCR_SYSRESETREQ_LSB    _u(2)
#define M0PLUS_AIRCR_SYSRESETREQ_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_AIRCR_VECTCLRACTIVE
// Description : Clears all active state information for fixed and configurable
//               exceptions. This bit: is self-clearing, can only be set by the
//               DAP when the core is halted.  When set: clears all active
//               exception status of the processor, forces a return to Thread
//               mode, forces an IPSR of 0. A debugger must re-initialize the
//               stack.
#define M0PLUS_AIRCR_VECTCLRACTIVE_RESET  _u(0x0)
#define M0PLUS_AIRCR_VECTCLRACTIVE_BITS   _u(0x00000002)
#define M0PLUS_AIRCR_VECTCLRACTIVE_MSB    _u(1)
#define M0PLUS_AIRCR_VECTCLRACTIVE_LSB    _u(1)
#define M0PLUS_AIRCR_VECTCLRACTIVE_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_SCR
// Description : System Control Register. Use the System Control Register for
//               power-management functions: signal to the system when the
//               processor can enter a low power state, control how the
//               processor enters and exits low power states.
#define M0PLUS_SCR_OFFSET _u(0x0000ed10)
#define M0PLUS_SCR_BITS   _u(0x00000016)
#define M0PLUS_SCR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_SCR_SEVONPEND
// Description : Send Event on Pending bit:
//               0 = Only enabled interrupts or events can wakeup the processor,
//               disabled interrupts are excluded.
//               1 = Enabled events and all interrupts, including disabled
//               interrupts, can wakeup the processor.
//               When an event or interrupt becomes pending, the event signal
//               wakes up the processor from WFE. If the
//               processor is not waiting for an event, the event is registered
//               and affects the next WFE.
//               The processor also wakes up on execution of an SEV instruction
//               or an external event.
#define M0PLUS_SCR_SEVONPEND_RESET  _u(0x0)
#define M0PLUS_SCR_SEVONPEND_BITS   _u(0x00000010)
#define M0PLUS_SCR_SEVONPEND_MSB    _u(4)
#define M0PLUS_SCR_SEVONPEND_LSB    _u(4)
#define M0PLUS_SCR_SEVONPEND_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_SCR_SLEEPDEEP
// Description : Controls whether the processor uses sleep or deep sleep as its
//               low power mode:
//               0 = Sleep.
//               1 = Deep sleep.
#define M0PLUS_SCR_SLEEPDEEP_RESET  _u(0x0)
#define M0PLUS_SCR_SLEEPDEEP_BITS   _u(0x00000004)
#define M0PLUS_SCR_SLEEPDEEP_MSB    _u(2)
#define M0PLUS_SCR_SLEEPDEEP_LSB    _u(2)
#define M0PLUS_SCR_SLEEPDEEP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_SCR_SLEEPONEXIT
// Description : Indicates sleep-on-exit when returning from Handler mode to
//               Thread mode:
//               0 = Do not sleep when returning to Thread mode.
//               1 = Enter sleep, or deep sleep, on return from an ISR to Thread
//               mode.
//               Setting this bit to 1 enables an interrupt driven application
//               to avoid returning to an empty main application.
#define M0PLUS_SCR_SLEEPONEXIT_RESET  _u(0x0)
#define M0PLUS_SCR_SLEEPONEXIT_BITS   _u(0x00000002)
#define M0PLUS_SCR_SLEEPONEXIT_MSB    _u(1)
#define M0PLUS_SCR_SLEEPONEXIT_LSB    _u(1)
#define M0PLUS_SCR_SLEEPONEXIT_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_CCR
// Description : The Configuration and Control Register permanently enables
//               stack alignment and causes unaligned accesses to result in a
//               Hard Fault.
#define M0PLUS_CCR_OFFSET _u(0x0000ed14)
#define M0PLUS_CCR_BITS   _u(0x00000208)
#define M0PLUS_CCR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_CCR_STKALIGN
// Description : Always reads as one, indicates 8-byte stack alignment on
//               exception entry. On exception entry, the processor uses bit[9]
//               of the stacked PSR to indicate the stack alignment. On return
//               from the exception it uses this stacked bit to restore the
//               correct stack alignment.
#define M0PLUS_CCR_STKALIGN_RESET  _u(0x0)
#define M0PLUS_CCR_STKALIGN_BITS   _u(0x00000200)
#define M0PLUS_CCR_STKALIGN_MSB    _u(9)
#define M0PLUS_CCR_STKALIGN_LSB    _u(9)
#define M0PLUS_CCR_STKALIGN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_CCR_UNALIGN_TRP
// Description : Always reads as one, indicates that all unaligned accesses
//               generate a HardFault.
#define M0PLUS_CCR_UNALIGN_TRP_RESET  _u(0x0)
#define M0PLUS_CCR_UNALIGN_TRP_BITS   _u(0x00000008)
#define M0PLUS_CCR_UNALIGN_TRP_MSB    _u(3)
#define M0PLUS_CCR_UNALIGN_TRP_LSB    _u(3)
#define M0PLUS_CCR_UNALIGN_TRP_ACCESS "RO"
// =============================================================================
// Register    : M0PLUS_SHPR2
// Description : System handlers are a special class of exception handler that
//               can have their priority set to any of the priority levels. Use
//               the System Handler Priority Register 2 to set the priority of
//               SVCall.
#define M0PLUS_SHPR2_OFFSET _u(0x0000ed1c)
#define M0PLUS_SHPR2_BITS   _u(0xc0000000)
#define M0PLUS_SHPR2_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_SHPR2_PRI_11
// Description : Priority of system handler 11, SVCall
#define M0PLUS_SHPR2_PRI_11_RESET  _u(0x0)
#define M0PLUS_SHPR2_PRI_11_BITS   _u(0xc0000000)
#define M0PLUS_SHPR2_PRI_11_MSB    _u(31)
#define M0PLUS_SHPR2_PRI_11_LSB    _u(30)
#define M0PLUS_SHPR2_PRI_11_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_SHPR3
// Description : System handlers are a special class of exception handler that
//               can have their priority set to any of the priority levels. Use
//               the System Handler Priority Register 3 to set the priority of
//               PendSV and SysTick.
#define M0PLUS_SHPR3_OFFSET _u(0x0000ed20)
#define M0PLUS_SHPR3_BITS   _u(0xc0c00000)
#define M0PLUS_SHPR3_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_SHPR3_PRI_15
// Description : Priority of system handler 15, SysTick
#define M0PLUS_SHPR3_PRI_15_RESET  _u(0x0)
#define M0PLUS_SHPR3_PRI_15_BITS   _u(0xc0000000)
#define M0PLUS_SHPR3_PRI_15_MSB    _u(31)
#define M0PLUS_SHPR3_PRI_15_LSB    _u(30)
#define M0PLUS_SHPR3_PRI_15_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_SHPR3_PRI_14
// Description : Priority of system handler 14, PendSV
#define M0PLUS_SHPR3_PRI_14_RESET  _u(0x0)
#define M0PLUS_SHPR3_PRI_14_BITS   _u(0x00c00000)
#define M0PLUS_SHPR3_PRI_14_MSB    _u(23)
#define M0PLUS_SHPR3_PRI_14_LSB    _u(22)
#define M0PLUS_SHPR3_PRI_14_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_SHCSR
// Description : Use the System Handler Control and State Register to determine
//               or clear the pending status of SVCall.
#define M0PLUS_SHCSR_OFFSET _u(0x0000ed24)
#define M0PLUS_SHCSR_BITS   _u(0x00008000)
#define M0PLUS_SHCSR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_SHCSR_SVCALLPENDED
// Description : Reads as 1 if SVCall is Pending.  Write 1 to set pending
//               SVCall, write 0 to clear pending SVCall.
#define M0PLUS_SHCSR_SVCALLPENDED_RESET  _u(0x0)
#define M0PLUS_SHCSR_SVCALLPENDED_BITS   _u(0x00008000)
#define M0PLUS_SHCSR_SVCALLPENDED_MSB    _u(15)
#define M0PLUS_SHCSR_SVCALLPENDED_LSB    _u(15)
#define M0PLUS_SHCSR_SVCALLPENDED_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_MPU_TYPE
// Description : Read the MPU Type Register to determine if the processor
//               implements an MPU, and how many regions the MPU supports.
#define M0PLUS_MPU_TYPE_OFFSET _u(0x0000ed90)
#define M0PLUS_MPU_TYPE_BITS   _u(0x00ffff01)
#define M0PLUS_MPU_TYPE_RESET  _u(0x00000800)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_MPU_TYPE_IREGION
// Description : Instruction region. Reads as zero as ARMv6-M only supports a
//               unified MPU.
#define M0PLUS_MPU_TYPE_IREGION_RESET  _u(0x00)
#define M0PLUS_MPU_TYPE_IREGION_BITS   _u(0x00ff0000)
#define M0PLUS_MPU_TYPE_IREGION_MSB    _u(23)
#define M0PLUS_MPU_TYPE_IREGION_LSB    _u(16)
#define M0PLUS_MPU_TYPE_IREGION_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_MPU_TYPE_DREGION
// Description : Number of regions supported by the MPU.
#define M0PLUS_MPU_TYPE_DREGION_RESET  _u(0x08)
#define M0PLUS_MPU_TYPE_DREGION_BITS   _u(0x0000ff00)
#define M0PLUS_MPU_TYPE_DREGION_MSB    _u(15)
#define M0PLUS_MPU_TYPE_DREGION_LSB    _u(8)
#define M0PLUS_MPU_TYPE_DREGION_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_MPU_TYPE_SEPARATE
// Description : Indicates support for separate instruction and data address
//               maps. Reads as 0 as ARMv6-M only supports a unified MPU.
#define M0PLUS_MPU_TYPE_SEPARATE_RESET  _u(0x0)
#define M0PLUS_MPU_TYPE_SEPARATE_BITS   _u(0x00000001)
#define M0PLUS_MPU_TYPE_SEPARATE_MSB    _u(0)
#define M0PLUS_MPU_TYPE_SEPARATE_LSB    _u(0)
#define M0PLUS_MPU_TYPE_SEPARATE_ACCESS "RO"
// =============================================================================
// Register    : M0PLUS_MPU_CTRL
// Description : Use the MPU Control Register to enable and disable the MPU, and
//               to control whether the default memory map is enabled as a
//               background region for privileged accesses, and whether the MPU
//               is enabled for HardFaults and NMIs.
#define M0PLUS_MPU_CTRL_OFFSET _u(0x0000ed94)
#define M0PLUS_MPU_CTRL_BITS   _u(0x00000007)
#define M0PLUS_MPU_CTRL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_MPU_CTRL_PRIVDEFENA
// Description : Controls whether the default memory map is enabled as a
//               background region for privileged accesses. This bit is ignored
//               when ENABLE is clear.
//               0 = If the MPU is enabled, disables use of the default memory
//               map. Any memory access to a location not
//               covered by any enabled region causes a fault.
//               1 = If the MPU is enabled, enables use of the default memory
//               map as a background region for privileged software accesses.
//               When enabled, the background region acts as if it is region
//               number -1. Any region that is defined and enabled has priority
//               over this default map.
#define M0PLUS_MPU_CTRL_PRIVDEFENA_RESET  _u(0x0)
#define M0PLUS_MPU_CTRL_PRIVDEFENA_BITS   _u(0x00000004)
#define M0PLUS_MPU_CTRL_PRIVDEFENA_MSB    _u(2)
#define M0PLUS_MPU_CTRL_PRIVDEFENA_LSB    _u(2)
#define M0PLUS_MPU_CTRL_PRIVDEFENA_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_MPU_CTRL_HFNMIENA
// Description : Controls the use of the MPU for HardFaults and NMIs. Setting
//               this bit when ENABLE is clear results in UNPREDICTABLE
//               behaviour.
//               When the MPU is enabled:
//               0 = MPU is disabled during HardFault and NMI handlers,
//               regardless of the value of the ENABLE bit.
//               1 = the MPU is enabled during HardFault and NMI handlers.
#define M0PLUS_MPU_CTRL_HFNMIENA_RESET  _u(0x0)
#define M0PLUS_MPU_CTRL_HFNMIENA_BITS   _u(0x00000002)
#define M0PLUS_MPU_CTRL_HFNMIENA_MSB    _u(1)
#define M0PLUS_MPU_CTRL_HFNMIENA_LSB    _u(1)
#define M0PLUS_MPU_CTRL_HFNMIENA_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_MPU_CTRL_ENABLE
// Description : Enables the MPU. If the MPU is disabled, privileged and
//               unprivileged accesses use the default memory map.
//               0 = MPU disabled.
//               1 = MPU enabled.
#define M0PLUS_MPU_CTRL_ENABLE_RESET  _u(0x0)
#define M0PLUS_MPU_CTRL_ENABLE_BITS   _u(0x00000001)
#define M0PLUS_MPU_CTRL_ENABLE_MSB    _u(0)
#define M0PLUS_MPU_CTRL_ENABLE_LSB    _u(0)
#define M0PLUS_MPU_CTRL_ENABLE_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_MPU_RNR
// Description : Use the MPU Region Number Register to select the region
//               currently accessed by MPU_RBAR and MPU_RASR.
#define M0PLUS_MPU_RNR_OFFSET _u(0x0000ed98)
#define M0PLUS_MPU_RNR_BITS   _u(0x0000000f)
#define M0PLUS_MPU_RNR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_MPU_RNR_REGION
// Description : Indicates the MPU region referenced by the MPU_RBAR and
//               MPU_RASR registers.
//               The MPU supports 8 memory regions, so the permitted values of
//               this field are 0-7.
#define M0PLUS_MPU_RNR_REGION_RESET  _u(0x0)
#define M0PLUS_MPU_RNR_REGION_BITS   _u(0x0000000f)
#define M0PLUS_MPU_RNR_REGION_MSB    _u(3)
#define M0PLUS_MPU_RNR_REGION_LSB    _u(0)
#define M0PLUS_MPU_RNR_REGION_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_MPU_RBAR
// Description : Read the MPU Region Base Address Register to determine the base
//               address of the region identified by MPU_RNR. Write to update
//               the base address of said region or that of a specified region,
//               with whose number MPU_RNR will also be updated.
#define M0PLUS_MPU_RBAR_OFFSET _u(0x0000ed9c)
#define M0PLUS_MPU_RBAR_BITS   _u(0xffffff1f)
#define M0PLUS_MPU_RBAR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_MPU_RBAR_ADDR
// Description : Base address of the region.
#define M0PLUS_MPU_RBAR_ADDR_RESET  _u(0x000000)
#define M0PLUS_MPU_RBAR_ADDR_BITS   _u(0xffffff00)
#define M0PLUS_MPU_RBAR_ADDR_MSB    _u(31)
#define M0PLUS_MPU_RBAR_ADDR_LSB    _u(8)
#define M0PLUS_MPU_RBAR_ADDR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_MPU_RBAR_VALID
// Description : On writes, indicates whether the write must update the base
//               address of the region identified by the REGION field, updating
//               the MPU_RNR to indicate this new region.
//               Write:
//               0 = MPU_RNR not changed, and the processor:
//               Updates the base address for the region specified in the
//               MPU_RNR.
//               Ignores the value of the REGION field.
//               1 = The processor:
//               Updates the value of the MPU_RNR to the value of the REGION
//               field.
//               Updates the base address for the region specified in the REGION
//               field.
//               Always reads as zero.
#define M0PLUS_MPU_RBAR_VALID_RESET  _u(0x0)
#define M0PLUS_MPU_RBAR_VALID_BITS   _u(0x00000010)
#define M0PLUS_MPU_RBAR_VALID_MSB    _u(4)
#define M0PLUS_MPU_RBAR_VALID_LSB    _u(4)
#define M0PLUS_MPU_RBAR_VALID_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_MPU_RBAR_REGION
// Description : On writes, specifies the number of the region whose base
//               address to update provided VALID is set written as 1. On reads,
//               returns bits [3:0] of MPU_RNR.
#define M0PLUS_MPU_RBAR_REGION_RESET  _u(0x0)
#define M0PLUS_MPU_RBAR_REGION_BITS   _u(0x0000000f)
#define M0PLUS_MPU_RBAR_REGION_MSB    _u(3)
#define M0PLUS_MPU_RBAR_REGION_LSB    _u(0)
#define M0PLUS_MPU_RBAR_REGION_ACCESS "RW"
// =============================================================================
// Register    : M0PLUS_MPU_RASR
// Description : Use the MPU Region Attribute and Size Register to define the
//               size, access behaviour and memory type of the region identified
//               by MPU_RNR, and enable that region.
#define M0PLUS_MPU_RASR_OFFSET _u(0x0000eda0)
#define M0PLUS_MPU_RASR_BITS   _u(0xffffff3f)
#define M0PLUS_MPU_RASR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : M0PLUS_MPU_RASR_ATTRS
// Description : The MPU Region Attribute field. Use to define the region
//               attribute control.
//               28 = XN: Instruction access disable bit:
//               0 = Instruction fetches enabled.
//               1 = Instruction fetches disabled.
//               26:24 = AP: Access permission field
//               18 = S: Shareable bit
//               17 = C: Cacheable bit
//               16 = B: Bufferable bit
#define M0PLUS_MPU_RASR_ATTRS_RESET  _u(0x0000)
#define M0PLUS_MPU_RASR_ATTRS_BITS   _u(0xffff0000)
#define M0PLUS_MPU_RASR_ATTRS_MSB    _u(31)
#define M0PLUS_MPU_RASR_ATTRS_LSB    _u(16)
#define M0PLUS_MPU_RASR_ATTRS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_MPU_RASR_SRD
// Description : Subregion Disable. For regions of 256 bytes or larger, each bit
//               of this field controls whether one of the eight equal
//               subregions is enabled.
#define M0PLUS_MPU_RASR_SRD_RESET  _u(0x00)
#define M0PLUS_MPU_RASR_SRD_BITS   _u(0x0000ff00)
#define M0PLUS_MPU_RASR_SRD_MSB    _u(15)
#define M0PLUS_MPU_RASR_SRD_LSB    _u(8)
#define M0PLUS_MPU_RASR_SRD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_MPU_RASR_SIZE
// Description : Indicates the region size. Region size in bytes = 2^(SIZE+1).
//               The minimum permitted value is 7 (b00111) = 256Bytes
#define M0PLUS_MPU_RASR_SIZE_RESET  _u(0x00)
#define M0PLUS_MPU_RASR_SIZE_BITS   _u(0x0000003e)
#define M0PLUS_MPU_RASR_SIZE_MSB    _u(5)
#define M0PLUS_MPU_RASR_SIZE_LSB    _u(1)
#define M0PLUS_MPU_RASR_SIZE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : M0PLUS_MPU_RASR_ENABLE
// Description : Enables the region.
#define M0PLUS_MPU_RASR_ENABLE_RESET  _u(0x0)
#define M0PLUS_MPU_RASR_ENABLE_BITS   _u(0x00000001)
#define M0PLUS_MPU_RASR_ENABLE_MSB    _u(0)
#define M0PLUS_MPU_RASR_ENABLE_LSB    _u(0)
#define M0PLUS_MPU_RASR_ENABLE_ACCESS "RW"
// =============================================================================
#endif // HARDWARE_REGS_M0PLUS_DEFINED
