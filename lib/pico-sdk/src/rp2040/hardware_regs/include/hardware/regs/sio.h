/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : SIO
// Version        : 1
// Bus type       : apb
// Description    : Single-cycle IO block
//                  Provides core-local and inter-core hardware for the two
//                  processors, with single-cycle access.
// =============================================================================
#ifndef HARDWARE_REGS_SIO_DEFINED
#define HARDWARE_REGS_SIO_DEFINED
// =============================================================================
// Register    : SIO_CPUID
// Description : Processor core identifier
//               Value is 0 when read from processor core 0, and 1 when read
//               from processor core 1.
#define SIO_CPUID_OFFSET _u(0x00000000)
#define SIO_CPUID_BITS   _u(0xffffffff)
#define SIO_CPUID_RESET  "-"
#define SIO_CPUID_MSB    _u(31)
#define SIO_CPUID_LSB    _u(0)
#define SIO_CPUID_ACCESS "RO"
// =============================================================================
// Register    : SIO_GPIO_IN
// Description : Input value for GPIO pins
//               Input value for GPIO0...29
#define SIO_GPIO_IN_OFFSET _u(0x00000004)
#define SIO_GPIO_IN_BITS   _u(0x3fffffff)
#define SIO_GPIO_IN_RESET  _u(0x00000000)
#define SIO_GPIO_IN_MSB    _u(29)
#define SIO_GPIO_IN_LSB    _u(0)
#define SIO_GPIO_IN_ACCESS "RO"
// =============================================================================
// Register    : SIO_GPIO_HI_IN
// Description : Input value for QSPI pins
//               Input value on QSPI IO in order 0..5: SCLK, SSn, SD0, SD1, SD2,
//               SD3
#define SIO_GPIO_HI_IN_OFFSET _u(0x00000008)
#define SIO_GPIO_HI_IN_BITS   _u(0x0000003f)
#define SIO_GPIO_HI_IN_RESET  _u(0x00000000)
#define SIO_GPIO_HI_IN_MSB    _u(5)
#define SIO_GPIO_HI_IN_LSB    _u(0)
#define SIO_GPIO_HI_IN_ACCESS "RO"
// =============================================================================
// Register    : SIO_GPIO_OUT
// Description : GPIO output value
//               Set output level (1/0 -> high/low) for GPIO0...29.
//               Reading back gives the last value written, NOT the input value
//               from the pins.
//               If core 0 and core 1 both write to GPIO_OUT simultaneously (or
//               to a SET/CLR/XOR alias),
//               the result is as though the write from core 0 took place first,
//               and the write from core 1 was then applied to that intermediate
//               result.
#define SIO_GPIO_OUT_OFFSET _u(0x00000010)
#define SIO_GPIO_OUT_BITS   _u(0x3fffffff)
#define SIO_GPIO_OUT_RESET  _u(0x00000000)
#define SIO_GPIO_OUT_MSB    _u(29)
#define SIO_GPIO_OUT_LSB    _u(0)
#define SIO_GPIO_OUT_ACCESS "RW"
// =============================================================================
// Register    : SIO_GPIO_OUT_SET
// Description : GPIO output value set
//               Perform an atomic bit-set on GPIO_OUT, i.e. `GPIO_OUT |= wdata`
#define SIO_GPIO_OUT_SET_OFFSET _u(0x00000014)
#define SIO_GPIO_OUT_SET_BITS   _u(0x3fffffff)
#define SIO_GPIO_OUT_SET_RESET  _u(0x00000000)
#define SIO_GPIO_OUT_SET_MSB    _u(29)
#define SIO_GPIO_OUT_SET_LSB    _u(0)
#define SIO_GPIO_OUT_SET_ACCESS "WO"
// =============================================================================
// Register    : SIO_GPIO_OUT_CLR
// Description : GPIO output value clear
//               Perform an atomic bit-clear on GPIO_OUT, i.e. `GPIO_OUT &=
//               ~wdata`
#define SIO_GPIO_OUT_CLR_OFFSET _u(0x00000018)
#define SIO_GPIO_OUT_CLR_BITS   _u(0x3fffffff)
#define SIO_GPIO_OUT_CLR_RESET  _u(0x00000000)
#define SIO_GPIO_OUT_CLR_MSB    _u(29)
#define SIO_GPIO_OUT_CLR_LSB    _u(0)
#define SIO_GPIO_OUT_CLR_ACCESS "WO"
// =============================================================================
// Register    : SIO_GPIO_OUT_XOR
// Description : GPIO output value XOR
//               Perform an atomic bitwise XOR on GPIO_OUT, i.e. `GPIO_OUT ^=
//               wdata`
#define SIO_GPIO_OUT_XOR_OFFSET _u(0x0000001c)
#define SIO_GPIO_OUT_XOR_BITS   _u(0x3fffffff)
#define SIO_GPIO_OUT_XOR_RESET  _u(0x00000000)
#define SIO_GPIO_OUT_XOR_MSB    _u(29)
#define SIO_GPIO_OUT_XOR_LSB    _u(0)
#define SIO_GPIO_OUT_XOR_ACCESS "WO"
// =============================================================================
// Register    : SIO_GPIO_OE
// Description : GPIO output enable
//               Set output enable (1/0 -> output/input) for GPIO0...29.
//               Reading back gives the last value written.
//               If core 0 and core 1 both write to GPIO_OE simultaneously (or
//               to a SET/CLR/XOR alias),
//               the result is as though the write from core 0 took place first,
//               and the write from core 1 was then applied to that intermediate
//               result.
#define SIO_GPIO_OE_OFFSET _u(0x00000020)
#define SIO_GPIO_OE_BITS   _u(0x3fffffff)
#define SIO_GPIO_OE_RESET  _u(0x00000000)
#define SIO_GPIO_OE_MSB    _u(29)
#define SIO_GPIO_OE_LSB    _u(0)
#define SIO_GPIO_OE_ACCESS "RW"
// =============================================================================
// Register    : SIO_GPIO_OE_SET
// Description : GPIO output enable set
//               Perform an atomic bit-set on GPIO_OE, i.e. `GPIO_OE |= wdata`
#define SIO_GPIO_OE_SET_OFFSET _u(0x00000024)
#define SIO_GPIO_OE_SET_BITS   _u(0x3fffffff)
#define SIO_GPIO_OE_SET_RESET  _u(0x00000000)
#define SIO_GPIO_OE_SET_MSB    _u(29)
#define SIO_GPIO_OE_SET_LSB    _u(0)
#define SIO_GPIO_OE_SET_ACCESS "WO"
// =============================================================================
// Register    : SIO_GPIO_OE_CLR
// Description : GPIO output enable clear
//               Perform an atomic bit-clear on GPIO_OE, i.e. `GPIO_OE &=
//               ~wdata`
#define SIO_GPIO_OE_CLR_OFFSET _u(0x00000028)
#define SIO_GPIO_OE_CLR_BITS   _u(0x3fffffff)
#define SIO_GPIO_OE_CLR_RESET  _u(0x00000000)
#define SIO_GPIO_OE_CLR_MSB    _u(29)
#define SIO_GPIO_OE_CLR_LSB    _u(0)
#define SIO_GPIO_OE_CLR_ACCESS "WO"
// =============================================================================
// Register    : SIO_GPIO_OE_XOR
// Description : GPIO output enable XOR
//               Perform an atomic bitwise XOR on GPIO_OE, i.e. `GPIO_OE ^=
//               wdata`
#define SIO_GPIO_OE_XOR_OFFSET _u(0x0000002c)
#define SIO_GPIO_OE_XOR_BITS   _u(0x3fffffff)
#define SIO_GPIO_OE_XOR_RESET  _u(0x00000000)
#define SIO_GPIO_OE_XOR_MSB    _u(29)
#define SIO_GPIO_OE_XOR_LSB    _u(0)
#define SIO_GPIO_OE_XOR_ACCESS "WO"
// =============================================================================
// Register    : SIO_GPIO_HI_OUT
// Description : QSPI output value
//               Set output level (1/0 -> high/low) for QSPI IO0...5.
//               Reading back gives the last value written, NOT the input value
//               from the pins.
//               If core 0 and core 1 both write to GPIO_HI_OUT simultaneously
//               (or to a SET/CLR/XOR alias),
//               the result is as though the write from core 0 took place first,
//               and the write from core 1 was then applied to that intermediate
//               result.
#define SIO_GPIO_HI_OUT_OFFSET _u(0x00000030)
#define SIO_GPIO_HI_OUT_BITS   _u(0x0000003f)
#define SIO_GPIO_HI_OUT_RESET  _u(0x00000000)
#define SIO_GPIO_HI_OUT_MSB    _u(5)
#define SIO_GPIO_HI_OUT_LSB    _u(0)
#define SIO_GPIO_HI_OUT_ACCESS "RW"
// =============================================================================
// Register    : SIO_GPIO_HI_OUT_SET
// Description : QSPI output value set
//               Perform an atomic bit-set on GPIO_HI_OUT, i.e. `GPIO_HI_OUT |=
//               wdata`
#define SIO_GPIO_HI_OUT_SET_OFFSET _u(0x00000034)
#define SIO_GPIO_HI_OUT_SET_BITS   _u(0x0000003f)
#define SIO_GPIO_HI_OUT_SET_RESET  _u(0x00000000)
#define SIO_GPIO_HI_OUT_SET_MSB    _u(5)
#define SIO_GPIO_HI_OUT_SET_LSB    _u(0)
#define SIO_GPIO_HI_OUT_SET_ACCESS "WO"
// =============================================================================
// Register    : SIO_GPIO_HI_OUT_CLR
// Description : QSPI output value clear
//               Perform an atomic bit-clear on GPIO_HI_OUT, i.e. `GPIO_HI_OUT
//               &= ~wdata`
#define SIO_GPIO_HI_OUT_CLR_OFFSET _u(0x00000038)
#define SIO_GPIO_HI_OUT_CLR_BITS   _u(0x0000003f)
#define SIO_GPIO_HI_OUT_CLR_RESET  _u(0x00000000)
#define SIO_GPIO_HI_OUT_CLR_MSB    _u(5)
#define SIO_GPIO_HI_OUT_CLR_LSB    _u(0)
#define SIO_GPIO_HI_OUT_CLR_ACCESS "WO"
// =============================================================================
// Register    : SIO_GPIO_HI_OUT_XOR
// Description : QSPI output value XOR
//               Perform an atomic bitwise XOR on GPIO_HI_OUT, i.e. `GPIO_HI_OUT
//               ^= wdata`
#define SIO_GPIO_HI_OUT_XOR_OFFSET _u(0x0000003c)
#define SIO_GPIO_HI_OUT_XOR_BITS   _u(0x0000003f)
#define SIO_GPIO_HI_OUT_XOR_RESET  _u(0x00000000)
#define SIO_GPIO_HI_OUT_XOR_MSB    _u(5)
#define SIO_GPIO_HI_OUT_XOR_LSB    _u(0)
#define SIO_GPIO_HI_OUT_XOR_ACCESS "WO"
// =============================================================================
// Register    : SIO_GPIO_HI_OE
// Description : QSPI output enable
//               Set output enable (1/0 -> output/input) for QSPI IO0...5.
//               Reading back gives the last value written.
//               If core 0 and core 1 both write to GPIO_HI_OE simultaneously
//               (or to a SET/CLR/XOR alias),
//               the result is as though the write from core 0 took place first,
//               and the write from core 1 was then applied to that intermediate
//               result.
#define SIO_GPIO_HI_OE_OFFSET _u(0x00000040)
#define SIO_GPIO_HI_OE_BITS   _u(0x0000003f)
#define SIO_GPIO_HI_OE_RESET  _u(0x00000000)
#define SIO_GPIO_HI_OE_MSB    _u(5)
#define SIO_GPIO_HI_OE_LSB    _u(0)
#define SIO_GPIO_HI_OE_ACCESS "RW"
// =============================================================================
// Register    : SIO_GPIO_HI_OE_SET
// Description : QSPI output enable set
//               Perform an atomic bit-set on GPIO_HI_OE, i.e. `GPIO_HI_OE |=
//               wdata`
#define SIO_GPIO_HI_OE_SET_OFFSET _u(0x00000044)
#define SIO_GPIO_HI_OE_SET_BITS   _u(0x0000003f)
#define SIO_GPIO_HI_OE_SET_RESET  _u(0x00000000)
#define SIO_GPIO_HI_OE_SET_MSB    _u(5)
#define SIO_GPIO_HI_OE_SET_LSB    _u(0)
#define SIO_GPIO_HI_OE_SET_ACCESS "WO"
// =============================================================================
// Register    : SIO_GPIO_HI_OE_CLR
// Description : QSPI output enable clear
//               Perform an atomic bit-clear on GPIO_HI_OE, i.e. `GPIO_HI_OE &=
//               ~wdata`
#define SIO_GPIO_HI_OE_CLR_OFFSET _u(0x00000048)
#define SIO_GPIO_HI_OE_CLR_BITS   _u(0x0000003f)
#define SIO_GPIO_HI_OE_CLR_RESET  _u(0x00000000)
#define SIO_GPIO_HI_OE_CLR_MSB    _u(5)
#define SIO_GPIO_HI_OE_CLR_LSB    _u(0)
#define SIO_GPIO_HI_OE_CLR_ACCESS "WO"
// =============================================================================
// Register    : SIO_GPIO_HI_OE_XOR
// Description : QSPI output enable XOR
//               Perform an atomic bitwise XOR on GPIO_HI_OE, i.e. `GPIO_HI_OE
//               ^= wdata`
#define SIO_GPIO_HI_OE_XOR_OFFSET _u(0x0000004c)
#define SIO_GPIO_HI_OE_XOR_BITS   _u(0x0000003f)
#define SIO_GPIO_HI_OE_XOR_RESET  _u(0x00000000)
#define SIO_GPIO_HI_OE_XOR_MSB    _u(5)
#define SIO_GPIO_HI_OE_XOR_LSB    _u(0)
#define SIO_GPIO_HI_OE_XOR_ACCESS "WO"
// =============================================================================
// Register    : SIO_FIFO_ST
// Description : Status register for inter-core FIFOs (mailboxes).
//               There is one FIFO in the core 0 -> core 1 direction, and one
//               core 1 -> core 0. Both are 32 bits wide and 8 words deep.
//               Core 0 can see the read side of the 1->0 FIFO (RX), and the
//               write side of 0->1 FIFO (TX).
//               Core 1 can see the read side of the 0->1 FIFO (RX), and the
//               write side of 1->0 FIFO (TX).
//               The SIO IRQ for each core is the logical OR of the VLD, WOF and
//               ROE fields of its FIFO_ST register.
#define SIO_FIFO_ST_OFFSET _u(0x00000050)
#define SIO_FIFO_ST_BITS   _u(0x0000000f)
#define SIO_FIFO_ST_RESET  _u(0x00000002)
// -----------------------------------------------------------------------------
// Field       : SIO_FIFO_ST_ROE
// Description : Sticky flag indicating the RX FIFO was read when empty. This
//               read was ignored by the FIFO.
#define SIO_FIFO_ST_ROE_RESET  _u(0x0)
#define SIO_FIFO_ST_ROE_BITS   _u(0x00000008)
#define SIO_FIFO_ST_ROE_MSB    _u(3)
#define SIO_FIFO_ST_ROE_LSB    _u(3)
#define SIO_FIFO_ST_ROE_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : SIO_FIFO_ST_WOF
// Description : Sticky flag indicating the TX FIFO was written when full. This
//               write was ignored by the FIFO.
#define SIO_FIFO_ST_WOF_RESET  _u(0x0)
#define SIO_FIFO_ST_WOF_BITS   _u(0x00000004)
#define SIO_FIFO_ST_WOF_MSB    _u(2)
#define SIO_FIFO_ST_WOF_LSB    _u(2)
#define SIO_FIFO_ST_WOF_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : SIO_FIFO_ST_RDY
// Description : Value is 1 if this core's TX FIFO is not full (i.e. if FIFO_WR
//               is ready for more data)
#define SIO_FIFO_ST_RDY_RESET  _u(0x1)
#define SIO_FIFO_ST_RDY_BITS   _u(0x00000002)
#define SIO_FIFO_ST_RDY_MSB    _u(1)
#define SIO_FIFO_ST_RDY_LSB    _u(1)
#define SIO_FIFO_ST_RDY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SIO_FIFO_ST_VLD
// Description : Value is 1 if this core's RX FIFO is not empty (i.e. if FIFO_RD
//               is valid)
#define SIO_FIFO_ST_VLD_RESET  _u(0x0)
#define SIO_FIFO_ST_VLD_BITS   _u(0x00000001)
#define SIO_FIFO_ST_VLD_MSB    _u(0)
#define SIO_FIFO_ST_VLD_LSB    _u(0)
#define SIO_FIFO_ST_VLD_ACCESS "RO"
// =============================================================================
// Register    : SIO_FIFO_WR
// Description : Write access to this core's TX FIFO
#define SIO_FIFO_WR_OFFSET _u(0x00000054)
#define SIO_FIFO_WR_BITS   _u(0xffffffff)
#define SIO_FIFO_WR_RESET  _u(0x00000000)
#define SIO_FIFO_WR_MSB    _u(31)
#define SIO_FIFO_WR_LSB    _u(0)
#define SIO_FIFO_WR_ACCESS "WF"
// =============================================================================
// Register    : SIO_FIFO_RD
// Description : Read access to this core's RX FIFO
#define SIO_FIFO_RD_OFFSET _u(0x00000058)
#define SIO_FIFO_RD_BITS   _u(0xffffffff)
#define SIO_FIFO_RD_RESET  "-"
#define SIO_FIFO_RD_MSB    _u(31)
#define SIO_FIFO_RD_LSB    _u(0)
#define SIO_FIFO_RD_ACCESS "RF"
// =============================================================================
// Register    : SIO_SPINLOCK_ST
// Description : Spinlock state
//               A bitmap containing the state of all 32 spinlocks (1=locked).
//               Mainly intended for debugging.
#define SIO_SPINLOCK_ST_OFFSET _u(0x0000005c)
#define SIO_SPINLOCK_ST_BITS   _u(0xffffffff)
#define SIO_SPINLOCK_ST_RESET  _u(0x00000000)
#define SIO_SPINLOCK_ST_MSB    _u(31)
#define SIO_SPINLOCK_ST_LSB    _u(0)
#define SIO_SPINLOCK_ST_ACCESS "RO"
// =============================================================================
// Register    : SIO_DIV_UDIVIDEND
// Description : Divider unsigned dividend
//               Write to the DIVIDEND operand of the divider, i.e. the p in `p
//               / q`.
//               Any operand write starts a new calculation. The results appear
//               in QUOTIENT, REMAINDER.
//               UDIVIDEND/SDIVIDEND are aliases of the same internal register.
//               The U alias starts an
//               unsigned calculation, and the S alias starts a signed
//               calculation.
#define SIO_DIV_UDIVIDEND_OFFSET _u(0x00000060)
#define SIO_DIV_UDIVIDEND_BITS   _u(0xffffffff)
#define SIO_DIV_UDIVIDEND_RESET  _u(0x00000000)
#define SIO_DIV_UDIVIDEND_MSB    _u(31)
#define SIO_DIV_UDIVIDEND_LSB    _u(0)
#define SIO_DIV_UDIVIDEND_ACCESS "RW"
// =============================================================================
// Register    : SIO_DIV_UDIVISOR
// Description : Divider unsigned divisor
//               Write to the DIVISOR operand of the divider, i.e. the q in `p /
//               q`.
//               Any operand write starts a new calculation. The results appear
//               in QUOTIENT, REMAINDER.
//               UDIVISOR/SDIVISOR are aliases of the same internal register.
//               The U alias starts an
//               unsigned calculation, and the S alias starts a signed
//               calculation.
#define SIO_DIV_UDIVISOR_OFFSET _u(0x00000064)
#define SIO_DIV_UDIVISOR_BITS   _u(0xffffffff)
#define SIO_DIV_UDIVISOR_RESET  _u(0x00000000)
#define SIO_DIV_UDIVISOR_MSB    _u(31)
#define SIO_DIV_UDIVISOR_LSB    _u(0)
#define SIO_DIV_UDIVISOR_ACCESS "RW"
// =============================================================================
// Register    : SIO_DIV_SDIVIDEND
// Description : Divider signed dividend
//               The same as UDIVIDEND, but starts a signed calculation, rather
//               than unsigned.
#define SIO_DIV_SDIVIDEND_OFFSET _u(0x00000068)
#define SIO_DIV_SDIVIDEND_BITS   _u(0xffffffff)
#define SIO_DIV_SDIVIDEND_RESET  _u(0x00000000)
#define SIO_DIV_SDIVIDEND_MSB    _u(31)
#define SIO_DIV_SDIVIDEND_LSB    _u(0)
#define SIO_DIV_SDIVIDEND_ACCESS "RW"
// =============================================================================
// Register    : SIO_DIV_SDIVISOR
// Description : Divider signed divisor
//               The same as UDIVISOR, but starts a signed calculation, rather
//               than unsigned.
#define SIO_DIV_SDIVISOR_OFFSET _u(0x0000006c)
#define SIO_DIV_SDIVISOR_BITS   _u(0xffffffff)
#define SIO_DIV_SDIVISOR_RESET  _u(0x00000000)
#define SIO_DIV_SDIVISOR_MSB    _u(31)
#define SIO_DIV_SDIVISOR_LSB    _u(0)
#define SIO_DIV_SDIVISOR_ACCESS "RW"
// =============================================================================
// Register    : SIO_DIV_QUOTIENT
// Description : Divider result quotient
//               The result of `DIVIDEND / DIVISOR` (division). Contents
//               undefined while CSR_READY is low.
//               For signed calculations, QUOTIENT is negative when the signs of
//               DIVIDEND and DIVISOR differ.
//               This register can be written to directly, for context
//               save/restore purposes. This halts any
//               in-progress calculation and sets the CSR_READY and CSR_DIRTY
//               flags.
//               Reading from QUOTIENT clears the CSR_DIRTY flag, so should read
//               results in the order
//               REMAINDER, QUOTIENT if CSR_DIRTY is used.
#define SIO_DIV_QUOTIENT_OFFSET _u(0x00000070)
#define SIO_DIV_QUOTIENT_BITS   _u(0xffffffff)
#define SIO_DIV_QUOTIENT_RESET  _u(0x00000000)
#define SIO_DIV_QUOTIENT_MSB    _u(31)
#define SIO_DIV_QUOTIENT_LSB    _u(0)
#define SIO_DIV_QUOTIENT_ACCESS "RW"
// =============================================================================
// Register    : SIO_DIV_REMAINDER
// Description : Divider result remainder
//               The result of `DIVIDEND % DIVISOR` (modulo). Contents undefined
//               while CSR_READY is low.
//               For signed calculations, REMAINDER is negative only when
//               DIVIDEND is negative.
//               This register can be written to directly, for context
//               save/restore purposes. This halts any
//               in-progress calculation and sets the CSR_READY and CSR_DIRTY
//               flags.
#define SIO_DIV_REMAINDER_OFFSET _u(0x00000074)
#define SIO_DIV_REMAINDER_BITS   _u(0xffffffff)
#define SIO_DIV_REMAINDER_RESET  _u(0x00000000)
#define SIO_DIV_REMAINDER_MSB    _u(31)
#define SIO_DIV_REMAINDER_LSB    _u(0)
#define SIO_DIV_REMAINDER_ACCESS "RW"
// =============================================================================
// Register    : SIO_DIV_CSR
// Description : Control and status register for divider.
#define SIO_DIV_CSR_OFFSET _u(0x00000078)
#define SIO_DIV_CSR_BITS   _u(0x00000003)
#define SIO_DIV_CSR_RESET  _u(0x00000001)
// -----------------------------------------------------------------------------
// Field       : SIO_DIV_CSR_DIRTY
// Description : Changes to 1 when any register is written, and back to 0 when
//               QUOTIENT is read.
//               Software can use this flag to make save/restore more efficient
//               (skip if not DIRTY).
//               If the flag is used in this way, it's recommended to either
//               read QUOTIENT only,
//               or REMAINDER and then QUOTIENT, to prevent data loss on context
//               switch.
#define SIO_DIV_CSR_DIRTY_RESET  _u(0x0)
#define SIO_DIV_CSR_DIRTY_BITS   _u(0x00000002)
#define SIO_DIV_CSR_DIRTY_MSB    _u(1)
#define SIO_DIV_CSR_DIRTY_LSB    _u(1)
#define SIO_DIV_CSR_DIRTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SIO_DIV_CSR_READY
// Description : Reads as 0 when a calculation is in progress, 1 otherwise.
//               Writing an operand (xDIVIDEND, xDIVISOR) will immediately start
//               a new calculation, no
//               matter if one is already in progress.
//               Writing to a result register will immediately terminate any
//               in-progress calculation
//               and set the READY and DIRTY flags.
#define SIO_DIV_CSR_READY_RESET  _u(0x1)
#define SIO_DIV_CSR_READY_BITS   _u(0x00000001)
#define SIO_DIV_CSR_READY_MSB    _u(0)
#define SIO_DIV_CSR_READY_LSB    _u(0)
#define SIO_DIV_CSR_READY_ACCESS "RO"
// =============================================================================
// Register    : SIO_INTERP0_ACCUM0
// Description : Read/write access to accumulator 0
#define SIO_INTERP0_ACCUM0_OFFSET _u(0x00000080)
#define SIO_INTERP0_ACCUM0_BITS   _u(0xffffffff)
#define SIO_INTERP0_ACCUM0_RESET  _u(0x00000000)
#define SIO_INTERP0_ACCUM0_MSB    _u(31)
#define SIO_INTERP0_ACCUM0_LSB    _u(0)
#define SIO_INTERP0_ACCUM0_ACCESS "RW"
// =============================================================================
// Register    : SIO_INTERP0_ACCUM1
// Description : Read/write access to accumulator 1
#define SIO_INTERP0_ACCUM1_OFFSET _u(0x00000084)
#define SIO_INTERP0_ACCUM1_BITS   _u(0xffffffff)
#define SIO_INTERP0_ACCUM1_RESET  _u(0x00000000)
#define SIO_INTERP0_ACCUM1_MSB    _u(31)
#define SIO_INTERP0_ACCUM1_LSB    _u(0)
#define SIO_INTERP0_ACCUM1_ACCESS "RW"
// =============================================================================
// Register    : SIO_INTERP0_BASE0
// Description : Read/write access to BASE0 register.
#define SIO_INTERP0_BASE0_OFFSET _u(0x00000088)
#define SIO_INTERP0_BASE0_BITS   _u(0xffffffff)
#define SIO_INTERP0_BASE0_RESET  _u(0x00000000)
#define SIO_INTERP0_BASE0_MSB    _u(31)
#define SIO_INTERP0_BASE0_LSB    _u(0)
#define SIO_INTERP0_BASE0_ACCESS "RW"
// =============================================================================
// Register    : SIO_INTERP0_BASE1
// Description : Read/write access to BASE1 register.
#define SIO_INTERP0_BASE1_OFFSET _u(0x0000008c)
#define SIO_INTERP0_BASE1_BITS   _u(0xffffffff)
#define SIO_INTERP0_BASE1_RESET  _u(0x00000000)
#define SIO_INTERP0_BASE1_MSB    _u(31)
#define SIO_INTERP0_BASE1_LSB    _u(0)
#define SIO_INTERP0_BASE1_ACCESS "RW"
// =============================================================================
// Register    : SIO_INTERP0_BASE2
// Description : Read/write access to BASE2 register.
#define SIO_INTERP0_BASE2_OFFSET _u(0x00000090)
#define SIO_INTERP0_BASE2_BITS   _u(0xffffffff)
#define SIO_INTERP0_BASE2_RESET  _u(0x00000000)
#define SIO_INTERP0_BASE2_MSB    _u(31)
#define SIO_INTERP0_BASE2_LSB    _u(0)
#define SIO_INTERP0_BASE2_ACCESS "RW"
// =============================================================================
// Register    : SIO_INTERP0_POP_LANE0
// Description : Read LANE0 result, and simultaneously write lane results to
//               both accumulators (POP).
#define SIO_INTERP0_POP_LANE0_OFFSET _u(0x00000094)
#define SIO_INTERP0_POP_LANE0_BITS   _u(0xffffffff)
#define SIO_INTERP0_POP_LANE0_RESET  _u(0x00000000)
#define SIO_INTERP0_POP_LANE0_MSB    _u(31)
#define SIO_INTERP0_POP_LANE0_LSB    _u(0)
#define SIO_INTERP0_POP_LANE0_ACCESS "RO"
// =============================================================================
// Register    : SIO_INTERP0_POP_LANE1
// Description : Read LANE1 result, and simultaneously write lane results to
//               both accumulators (POP).
#define SIO_INTERP0_POP_LANE1_OFFSET _u(0x00000098)
#define SIO_INTERP0_POP_LANE1_BITS   _u(0xffffffff)
#define SIO_INTERP0_POP_LANE1_RESET  _u(0x00000000)
#define SIO_INTERP0_POP_LANE1_MSB    _u(31)
#define SIO_INTERP0_POP_LANE1_LSB    _u(0)
#define SIO_INTERP0_POP_LANE1_ACCESS "RO"
// =============================================================================
// Register    : SIO_INTERP0_POP_FULL
// Description : Read FULL result, and simultaneously write lane results to both
//               accumulators (POP).
#define SIO_INTERP0_POP_FULL_OFFSET _u(0x0000009c)
#define SIO_INTERP0_POP_FULL_BITS   _u(0xffffffff)
#define SIO_INTERP0_POP_FULL_RESET  _u(0x00000000)
#define SIO_INTERP0_POP_FULL_MSB    _u(31)
#define SIO_INTERP0_POP_FULL_LSB    _u(0)
#define SIO_INTERP0_POP_FULL_ACCESS "RO"
// =============================================================================
// Register    : SIO_INTERP0_PEEK_LANE0
// Description : Read LANE0 result, without altering any internal state (PEEK).
#define SIO_INTERP0_PEEK_LANE0_OFFSET _u(0x000000a0)
#define SIO_INTERP0_PEEK_LANE0_BITS   _u(0xffffffff)
#define SIO_INTERP0_PEEK_LANE0_RESET  _u(0x00000000)
#define SIO_INTERP0_PEEK_LANE0_MSB    _u(31)
#define SIO_INTERP0_PEEK_LANE0_LSB    _u(0)
#define SIO_INTERP0_PEEK_LANE0_ACCESS "RO"
// =============================================================================
// Register    : SIO_INTERP0_PEEK_LANE1
// Description : Read LANE1 result, without altering any internal state (PEEK).
#define SIO_INTERP0_PEEK_LANE1_OFFSET _u(0x000000a4)
#define SIO_INTERP0_PEEK_LANE1_BITS   _u(0xffffffff)
#define SIO_INTERP0_PEEK_LANE1_RESET  _u(0x00000000)
#define SIO_INTERP0_PEEK_LANE1_MSB    _u(31)
#define SIO_INTERP0_PEEK_LANE1_LSB    _u(0)
#define SIO_INTERP0_PEEK_LANE1_ACCESS "RO"
// =============================================================================
// Register    : SIO_INTERP0_PEEK_FULL
// Description : Read FULL result, without altering any internal state (PEEK).
#define SIO_INTERP0_PEEK_FULL_OFFSET _u(0x000000a8)
#define SIO_INTERP0_PEEK_FULL_BITS   _u(0xffffffff)
#define SIO_INTERP0_PEEK_FULL_RESET  _u(0x00000000)
#define SIO_INTERP0_PEEK_FULL_MSB    _u(31)
#define SIO_INTERP0_PEEK_FULL_LSB    _u(0)
#define SIO_INTERP0_PEEK_FULL_ACCESS "RO"
// =============================================================================
// Register    : SIO_INTERP0_CTRL_LANE0
// Description : Control register for lane 0
#define SIO_INTERP0_CTRL_LANE0_OFFSET _u(0x000000ac)
#define SIO_INTERP0_CTRL_LANE0_BITS   _u(0x03bfffff)
#define SIO_INTERP0_CTRL_LANE0_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP0_CTRL_LANE0_OVERF
// Description : Set if either OVERF0 or OVERF1 is set.
#define SIO_INTERP0_CTRL_LANE0_OVERF_RESET  _u(0x0)
#define SIO_INTERP0_CTRL_LANE0_OVERF_BITS   _u(0x02000000)
#define SIO_INTERP0_CTRL_LANE0_OVERF_MSB    _u(25)
#define SIO_INTERP0_CTRL_LANE0_OVERF_LSB    _u(25)
#define SIO_INTERP0_CTRL_LANE0_OVERF_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP0_CTRL_LANE0_OVERF1
// Description : Indicates if any masked-off MSBs in ACCUM1 are set.
#define SIO_INTERP0_CTRL_LANE0_OVERF1_RESET  _u(0x0)
#define SIO_INTERP0_CTRL_LANE0_OVERF1_BITS   _u(0x01000000)
#define SIO_INTERP0_CTRL_LANE0_OVERF1_MSB    _u(24)
#define SIO_INTERP0_CTRL_LANE0_OVERF1_LSB    _u(24)
#define SIO_INTERP0_CTRL_LANE0_OVERF1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP0_CTRL_LANE0_OVERF0
// Description : Indicates if any masked-off MSBs in ACCUM0 are set.
#define SIO_INTERP0_CTRL_LANE0_OVERF0_RESET  _u(0x0)
#define SIO_INTERP0_CTRL_LANE0_OVERF0_BITS   _u(0x00800000)
#define SIO_INTERP0_CTRL_LANE0_OVERF0_MSB    _u(23)
#define SIO_INTERP0_CTRL_LANE0_OVERF0_LSB    _u(23)
#define SIO_INTERP0_CTRL_LANE0_OVERF0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP0_CTRL_LANE0_BLEND
// Description : Only present on INTERP0 on each core. If BLEND mode is enabled:
//               - LANE1 result is a linear interpolation between BASE0 and
//               BASE1, controlled
//               by the 8 LSBs of lane 1 shift and mask value (a fractional
//               number between
//               0 and 255/256ths)
//               - LANE0 result does not have BASE0 added (yields only the 8
//               LSBs of lane 1 shift+mask value)
//               - FULL result does not have lane 1 shift+mask value added
//               (BASE2 + lane 0 shift+mask)
//               LANE1 SIGNED flag controls whether the interpolation is signed
//               or unsigned.
#define SIO_INTERP0_CTRL_LANE0_BLEND_RESET  _u(0x0)
#define SIO_INTERP0_CTRL_LANE0_BLEND_BITS   _u(0x00200000)
#define SIO_INTERP0_CTRL_LANE0_BLEND_MSB    _u(21)
#define SIO_INTERP0_CTRL_LANE0_BLEND_LSB    _u(21)
#define SIO_INTERP0_CTRL_LANE0_BLEND_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP0_CTRL_LANE0_FORCE_MSB
// Description : ORed into bits 29:28 of the lane result presented to the
//               processor on the bus.
//               No effect on the internal 32-bit datapath. Handy for using a
//               lane to generate sequence
//               of pointers into flash or SRAM.
#define SIO_INTERP0_CTRL_LANE0_FORCE_MSB_RESET  _u(0x0)
#define SIO_INTERP0_CTRL_LANE0_FORCE_MSB_BITS   _u(0x00180000)
#define SIO_INTERP0_CTRL_LANE0_FORCE_MSB_MSB    _u(20)
#define SIO_INTERP0_CTRL_LANE0_FORCE_MSB_LSB    _u(19)
#define SIO_INTERP0_CTRL_LANE0_FORCE_MSB_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP0_CTRL_LANE0_ADD_RAW
// Description : If 1, mask + shift is bypassed for LANE0 result. This does not
//               affect FULL result.
#define SIO_INTERP0_CTRL_LANE0_ADD_RAW_RESET  _u(0x0)
#define SIO_INTERP0_CTRL_LANE0_ADD_RAW_BITS   _u(0x00040000)
#define SIO_INTERP0_CTRL_LANE0_ADD_RAW_MSB    _u(18)
#define SIO_INTERP0_CTRL_LANE0_ADD_RAW_LSB    _u(18)
#define SIO_INTERP0_CTRL_LANE0_ADD_RAW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP0_CTRL_LANE0_CROSS_RESULT
// Description : If 1, feed the opposite lane's result into this lane's
//               accumulator on POP.
#define SIO_INTERP0_CTRL_LANE0_CROSS_RESULT_RESET  _u(0x0)
#define SIO_INTERP0_CTRL_LANE0_CROSS_RESULT_BITS   _u(0x00020000)
#define SIO_INTERP0_CTRL_LANE0_CROSS_RESULT_MSB    _u(17)
#define SIO_INTERP0_CTRL_LANE0_CROSS_RESULT_LSB    _u(17)
#define SIO_INTERP0_CTRL_LANE0_CROSS_RESULT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP0_CTRL_LANE0_CROSS_INPUT
// Description : If 1, feed the opposite lane's accumulator into this lane's
//               shift + mask hardware.
//               Takes effect even if ADD_RAW is set (the CROSS_INPUT mux is
//               before the shift+mask bypass)
#define SIO_INTERP0_CTRL_LANE0_CROSS_INPUT_RESET  _u(0x0)
#define SIO_INTERP0_CTRL_LANE0_CROSS_INPUT_BITS   _u(0x00010000)
#define SIO_INTERP0_CTRL_LANE0_CROSS_INPUT_MSB    _u(16)
#define SIO_INTERP0_CTRL_LANE0_CROSS_INPUT_LSB    _u(16)
#define SIO_INTERP0_CTRL_LANE0_CROSS_INPUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP0_CTRL_LANE0_SIGNED
// Description : If SIGNED is set, the shifted and masked accumulator value is
//               sign-extended to 32 bits
//               before adding to BASE0, and LANE0 PEEK/POP appear extended to
//               32 bits when read by processor.
#define SIO_INTERP0_CTRL_LANE0_SIGNED_RESET  _u(0x0)
#define SIO_INTERP0_CTRL_LANE0_SIGNED_BITS   _u(0x00008000)
#define SIO_INTERP0_CTRL_LANE0_SIGNED_MSB    _u(15)
#define SIO_INTERP0_CTRL_LANE0_SIGNED_LSB    _u(15)
#define SIO_INTERP0_CTRL_LANE0_SIGNED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP0_CTRL_LANE0_MASK_MSB
// Description : The most-significant bit allowed to pass by the mask
//               (inclusive)
//               Setting MSB < LSB may cause chip to turn inside-out
#define SIO_INTERP0_CTRL_LANE0_MASK_MSB_RESET  _u(0x00)
#define SIO_INTERP0_CTRL_LANE0_MASK_MSB_BITS   _u(0x00007c00)
#define SIO_INTERP0_CTRL_LANE0_MASK_MSB_MSB    _u(14)
#define SIO_INTERP0_CTRL_LANE0_MASK_MSB_LSB    _u(10)
#define SIO_INTERP0_CTRL_LANE0_MASK_MSB_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP0_CTRL_LANE0_MASK_LSB
// Description : The least-significant bit allowed to pass by the mask
//               (inclusive)
#define SIO_INTERP0_CTRL_LANE0_MASK_LSB_RESET  _u(0x00)
#define SIO_INTERP0_CTRL_LANE0_MASK_LSB_BITS   _u(0x000003e0)
#define SIO_INTERP0_CTRL_LANE0_MASK_LSB_MSB    _u(9)
#define SIO_INTERP0_CTRL_LANE0_MASK_LSB_LSB    _u(5)
#define SIO_INTERP0_CTRL_LANE0_MASK_LSB_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP0_CTRL_LANE0_SHIFT
// Description : Logical right-shift applied to accumulator before masking
#define SIO_INTERP0_CTRL_LANE0_SHIFT_RESET  _u(0x00)
#define SIO_INTERP0_CTRL_LANE0_SHIFT_BITS   _u(0x0000001f)
#define SIO_INTERP0_CTRL_LANE0_SHIFT_MSB    _u(4)
#define SIO_INTERP0_CTRL_LANE0_SHIFT_LSB    _u(0)
#define SIO_INTERP0_CTRL_LANE0_SHIFT_ACCESS "RW"
// =============================================================================
// Register    : SIO_INTERP0_CTRL_LANE1
// Description : Control register for lane 1
#define SIO_INTERP0_CTRL_LANE1_OFFSET _u(0x000000b0)
#define SIO_INTERP0_CTRL_LANE1_BITS   _u(0x001fffff)
#define SIO_INTERP0_CTRL_LANE1_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP0_CTRL_LANE1_FORCE_MSB
// Description : ORed into bits 29:28 of the lane result presented to the
//               processor on the bus.
//               No effect on the internal 32-bit datapath. Handy for using a
//               lane to generate sequence
//               of pointers into flash or SRAM.
#define SIO_INTERP0_CTRL_LANE1_FORCE_MSB_RESET  _u(0x0)
#define SIO_INTERP0_CTRL_LANE1_FORCE_MSB_BITS   _u(0x00180000)
#define SIO_INTERP0_CTRL_LANE1_FORCE_MSB_MSB    _u(20)
#define SIO_INTERP0_CTRL_LANE1_FORCE_MSB_LSB    _u(19)
#define SIO_INTERP0_CTRL_LANE1_FORCE_MSB_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP0_CTRL_LANE1_ADD_RAW
// Description : If 1, mask + shift is bypassed for LANE1 result. This does not
//               affect FULL result.
#define SIO_INTERP0_CTRL_LANE1_ADD_RAW_RESET  _u(0x0)
#define SIO_INTERP0_CTRL_LANE1_ADD_RAW_BITS   _u(0x00040000)
#define SIO_INTERP0_CTRL_LANE1_ADD_RAW_MSB    _u(18)
#define SIO_INTERP0_CTRL_LANE1_ADD_RAW_LSB    _u(18)
#define SIO_INTERP0_CTRL_LANE1_ADD_RAW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP0_CTRL_LANE1_CROSS_RESULT
// Description : If 1, feed the opposite lane's result into this lane's
//               accumulator on POP.
#define SIO_INTERP0_CTRL_LANE1_CROSS_RESULT_RESET  _u(0x0)
#define SIO_INTERP0_CTRL_LANE1_CROSS_RESULT_BITS   _u(0x00020000)
#define SIO_INTERP0_CTRL_LANE1_CROSS_RESULT_MSB    _u(17)
#define SIO_INTERP0_CTRL_LANE1_CROSS_RESULT_LSB    _u(17)
#define SIO_INTERP0_CTRL_LANE1_CROSS_RESULT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP0_CTRL_LANE1_CROSS_INPUT
// Description : If 1, feed the opposite lane's accumulator into this lane's
//               shift + mask hardware.
//               Takes effect even if ADD_RAW is set (the CROSS_INPUT mux is
//               before the shift+mask bypass)
#define SIO_INTERP0_CTRL_LANE1_CROSS_INPUT_RESET  _u(0x0)
#define SIO_INTERP0_CTRL_LANE1_CROSS_INPUT_BITS   _u(0x00010000)
#define SIO_INTERP0_CTRL_LANE1_CROSS_INPUT_MSB    _u(16)
#define SIO_INTERP0_CTRL_LANE1_CROSS_INPUT_LSB    _u(16)
#define SIO_INTERP0_CTRL_LANE1_CROSS_INPUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP0_CTRL_LANE1_SIGNED
// Description : If SIGNED is set, the shifted and masked accumulator value is
//               sign-extended to 32 bits
//               before adding to BASE1, and LANE1 PEEK/POP appear extended to
//               32 bits when read by processor.
#define SIO_INTERP0_CTRL_LANE1_SIGNED_RESET  _u(0x0)
#define SIO_INTERP0_CTRL_LANE1_SIGNED_BITS   _u(0x00008000)
#define SIO_INTERP0_CTRL_LANE1_SIGNED_MSB    _u(15)
#define SIO_INTERP0_CTRL_LANE1_SIGNED_LSB    _u(15)
#define SIO_INTERP0_CTRL_LANE1_SIGNED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP0_CTRL_LANE1_MASK_MSB
// Description : The most-significant bit allowed to pass by the mask
//               (inclusive)
//               Setting MSB < LSB may cause chip to turn inside-out
#define SIO_INTERP0_CTRL_LANE1_MASK_MSB_RESET  _u(0x00)
#define SIO_INTERP0_CTRL_LANE1_MASK_MSB_BITS   _u(0x00007c00)
#define SIO_INTERP0_CTRL_LANE1_MASK_MSB_MSB    _u(14)
#define SIO_INTERP0_CTRL_LANE1_MASK_MSB_LSB    _u(10)
#define SIO_INTERP0_CTRL_LANE1_MASK_MSB_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP0_CTRL_LANE1_MASK_LSB
// Description : The least-significant bit allowed to pass by the mask
//               (inclusive)
#define SIO_INTERP0_CTRL_LANE1_MASK_LSB_RESET  _u(0x00)
#define SIO_INTERP0_CTRL_LANE1_MASK_LSB_BITS   _u(0x000003e0)
#define SIO_INTERP0_CTRL_LANE1_MASK_LSB_MSB    _u(9)
#define SIO_INTERP0_CTRL_LANE1_MASK_LSB_LSB    _u(5)
#define SIO_INTERP0_CTRL_LANE1_MASK_LSB_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP0_CTRL_LANE1_SHIFT
// Description : Logical right-shift applied to accumulator before masking
#define SIO_INTERP0_CTRL_LANE1_SHIFT_RESET  _u(0x00)
#define SIO_INTERP0_CTRL_LANE1_SHIFT_BITS   _u(0x0000001f)
#define SIO_INTERP0_CTRL_LANE1_SHIFT_MSB    _u(4)
#define SIO_INTERP0_CTRL_LANE1_SHIFT_LSB    _u(0)
#define SIO_INTERP0_CTRL_LANE1_SHIFT_ACCESS "RW"
// =============================================================================
// Register    : SIO_INTERP0_ACCUM0_ADD
// Description : Values written here are atomically added to ACCUM0
//               Reading yields lane 0's raw shift and mask value (BASE0 not
//               added).
#define SIO_INTERP0_ACCUM0_ADD_OFFSET _u(0x000000b4)
#define SIO_INTERP0_ACCUM0_ADD_BITS   _u(0x00ffffff)
#define SIO_INTERP0_ACCUM0_ADD_RESET  _u(0x00000000)
#define SIO_INTERP0_ACCUM0_ADD_MSB    _u(23)
#define SIO_INTERP0_ACCUM0_ADD_LSB    _u(0)
#define SIO_INTERP0_ACCUM0_ADD_ACCESS "RW"
// =============================================================================
// Register    : SIO_INTERP0_ACCUM1_ADD
// Description : Values written here are atomically added to ACCUM1
//               Reading yields lane 1's raw shift and mask value (BASE1 not
//               added).
#define SIO_INTERP0_ACCUM1_ADD_OFFSET _u(0x000000b8)
#define SIO_INTERP0_ACCUM1_ADD_BITS   _u(0x00ffffff)
#define SIO_INTERP0_ACCUM1_ADD_RESET  _u(0x00000000)
#define SIO_INTERP0_ACCUM1_ADD_MSB    _u(23)
#define SIO_INTERP0_ACCUM1_ADD_LSB    _u(0)
#define SIO_INTERP0_ACCUM1_ADD_ACCESS "RW"
// =============================================================================
// Register    : SIO_INTERP0_BASE_1AND0
// Description : On write, the lower 16 bits go to BASE0, upper bits to BASE1
//               simultaneously.
//               Each half is sign-extended to 32 bits if that lane's SIGNED
//               flag is set.
#define SIO_INTERP0_BASE_1AND0_OFFSET _u(0x000000bc)
#define SIO_INTERP0_BASE_1AND0_BITS   _u(0xffffffff)
#define SIO_INTERP0_BASE_1AND0_RESET  _u(0x00000000)
#define SIO_INTERP0_BASE_1AND0_MSB    _u(31)
#define SIO_INTERP0_BASE_1AND0_LSB    _u(0)
#define SIO_INTERP0_BASE_1AND0_ACCESS "WO"
// =============================================================================
// Register    : SIO_INTERP1_ACCUM0
// Description : Read/write access to accumulator 0
#define SIO_INTERP1_ACCUM0_OFFSET _u(0x000000c0)
#define SIO_INTERP1_ACCUM0_BITS   _u(0xffffffff)
#define SIO_INTERP1_ACCUM0_RESET  _u(0x00000000)
#define SIO_INTERP1_ACCUM0_MSB    _u(31)
#define SIO_INTERP1_ACCUM0_LSB    _u(0)
#define SIO_INTERP1_ACCUM0_ACCESS "RW"
// =============================================================================
// Register    : SIO_INTERP1_ACCUM1
// Description : Read/write access to accumulator 1
#define SIO_INTERP1_ACCUM1_OFFSET _u(0x000000c4)
#define SIO_INTERP1_ACCUM1_BITS   _u(0xffffffff)
#define SIO_INTERP1_ACCUM1_RESET  _u(0x00000000)
#define SIO_INTERP1_ACCUM1_MSB    _u(31)
#define SIO_INTERP1_ACCUM1_LSB    _u(0)
#define SIO_INTERP1_ACCUM1_ACCESS "RW"
// =============================================================================
// Register    : SIO_INTERP1_BASE0
// Description : Read/write access to BASE0 register.
#define SIO_INTERP1_BASE0_OFFSET _u(0x000000c8)
#define SIO_INTERP1_BASE0_BITS   _u(0xffffffff)
#define SIO_INTERP1_BASE0_RESET  _u(0x00000000)
#define SIO_INTERP1_BASE0_MSB    _u(31)
#define SIO_INTERP1_BASE0_LSB    _u(0)
#define SIO_INTERP1_BASE0_ACCESS "RW"
// =============================================================================
// Register    : SIO_INTERP1_BASE1
// Description : Read/write access to BASE1 register.
#define SIO_INTERP1_BASE1_OFFSET _u(0x000000cc)
#define SIO_INTERP1_BASE1_BITS   _u(0xffffffff)
#define SIO_INTERP1_BASE1_RESET  _u(0x00000000)
#define SIO_INTERP1_BASE1_MSB    _u(31)
#define SIO_INTERP1_BASE1_LSB    _u(0)
#define SIO_INTERP1_BASE1_ACCESS "RW"
// =============================================================================
// Register    : SIO_INTERP1_BASE2
// Description : Read/write access to BASE2 register.
#define SIO_INTERP1_BASE2_OFFSET _u(0x000000d0)
#define SIO_INTERP1_BASE2_BITS   _u(0xffffffff)
#define SIO_INTERP1_BASE2_RESET  _u(0x00000000)
#define SIO_INTERP1_BASE2_MSB    _u(31)
#define SIO_INTERP1_BASE2_LSB    _u(0)
#define SIO_INTERP1_BASE2_ACCESS "RW"
// =============================================================================
// Register    : SIO_INTERP1_POP_LANE0
// Description : Read LANE0 result, and simultaneously write lane results to
//               both accumulators (POP).
#define SIO_INTERP1_POP_LANE0_OFFSET _u(0x000000d4)
#define SIO_INTERP1_POP_LANE0_BITS   _u(0xffffffff)
#define SIO_INTERP1_POP_LANE0_RESET  _u(0x00000000)
#define SIO_INTERP1_POP_LANE0_MSB    _u(31)
#define SIO_INTERP1_POP_LANE0_LSB    _u(0)
#define SIO_INTERP1_POP_LANE0_ACCESS "RO"
// =============================================================================
// Register    : SIO_INTERP1_POP_LANE1
// Description : Read LANE1 result, and simultaneously write lane results to
//               both accumulators (POP).
#define SIO_INTERP1_POP_LANE1_OFFSET _u(0x000000d8)
#define SIO_INTERP1_POP_LANE1_BITS   _u(0xffffffff)
#define SIO_INTERP1_POP_LANE1_RESET  _u(0x00000000)
#define SIO_INTERP1_POP_LANE1_MSB    _u(31)
#define SIO_INTERP1_POP_LANE1_LSB    _u(0)
#define SIO_INTERP1_POP_LANE1_ACCESS "RO"
// =============================================================================
// Register    : SIO_INTERP1_POP_FULL
// Description : Read FULL result, and simultaneously write lane results to both
//               accumulators (POP).
#define SIO_INTERP1_POP_FULL_OFFSET _u(0x000000dc)
#define SIO_INTERP1_POP_FULL_BITS   _u(0xffffffff)
#define SIO_INTERP1_POP_FULL_RESET  _u(0x00000000)
#define SIO_INTERP1_POP_FULL_MSB    _u(31)
#define SIO_INTERP1_POP_FULL_LSB    _u(0)
#define SIO_INTERP1_POP_FULL_ACCESS "RO"
// =============================================================================
// Register    : SIO_INTERP1_PEEK_LANE0
// Description : Read LANE0 result, without altering any internal state (PEEK).
#define SIO_INTERP1_PEEK_LANE0_OFFSET _u(0x000000e0)
#define SIO_INTERP1_PEEK_LANE0_BITS   _u(0xffffffff)
#define SIO_INTERP1_PEEK_LANE0_RESET  _u(0x00000000)
#define SIO_INTERP1_PEEK_LANE0_MSB    _u(31)
#define SIO_INTERP1_PEEK_LANE0_LSB    _u(0)
#define SIO_INTERP1_PEEK_LANE0_ACCESS "RO"
// =============================================================================
// Register    : SIO_INTERP1_PEEK_LANE1
// Description : Read LANE1 result, without altering any internal state (PEEK).
#define SIO_INTERP1_PEEK_LANE1_OFFSET _u(0x000000e4)
#define SIO_INTERP1_PEEK_LANE1_BITS   _u(0xffffffff)
#define SIO_INTERP1_PEEK_LANE1_RESET  _u(0x00000000)
#define SIO_INTERP1_PEEK_LANE1_MSB    _u(31)
#define SIO_INTERP1_PEEK_LANE1_LSB    _u(0)
#define SIO_INTERP1_PEEK_LANE1_ACCESS "RO"
// =============================================================================
// Register    : SIO_INTERP1_PEEK_FULL
// Description : Read FULL result, without altering any internal state (PEEK).
#define SIO_INTERP1_PEEK_FULL_OFFSET _u(0x000000e8)
#define SIO_INTERP1_PEEK_FULL_BITS   _u(0xffffffff)
#define SIO_INTERP1_PEEK_FULL_RESET  _u(0x00000000)
#define SIO_INTERP1_PEEK_FULL_MSB    _u(31)
#define SIO_INTERP1_PEEK_FULL_LSB    _u(0)
#define SIO_INTERP1_PEEK_FULL_ACCESS "RO"
// =============================================================================
// Register    : SIO_INTERP1_CTRL_LANE0
// Description : Control register for lane 0
#define SIO_INTERP1_CTRL_LANE0_OFFSET _u(0x000000ec)
#define SIO_INTERP1_CTRL_LANE0_BITS   _u(0x03dfffff)
#define SIO_INTERP1_CTRL_LANE0_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP1_CTRL_LANE0_OVERF
// Description : Set if either OVERF0 or OVERF1 is set.
#define SIO_INTERP1_CTRL_LANE0_OVERF_RESET  _u(0x0)
#define SIO_INTERP1_CTRL_LANE0_OVERF_BITS   _u(0x02000000)
#define SIO_INTERP1_CTRL_LANE0_OVERF_MSB    _u(25)
#define SIO_INTERP1_CTRL_LANE0_OVERF_LSB    _u(25)
#define SIO_INTERP1_CTRL_LANE0_OVERF_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP1_CTRL_LANE0_OVERF1
// Description : Indicates if any masked-off MSBs in ACCUM1 are set.
#define SIO_INTERP1_CTRL_LANE0_OVERF1_RESET  _u(0x0)
#define SIO_INTERP1_CTRL_LANE0_OVERF1_BITS   _u(0x01000000)
#define SIO_INTERP1_CTRL_LANE0_OVERF1_MSB    _u(24)
#define SIO_INTERP1_CTRL_LANE0_OVERF1_LSB    _u(24)
#define SIO_INTERP1_CTRL_LANE0_OVERF1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP1_CTRL_LANE0_OVERF0
// Description : Indicates if any masked-off MSBs in ACCUM0 are set.
#define SIO_INTERP1_CTRL_LANE0_OVERF0_RESET  _u(0x0)
#define SIO_INTERP1_CTRL_LANE0_OVERF0_BITS   _u(0x00800000)
#define SIO_INTERP1_CTRL_LANE0_OVERF0_MSB    _u(23)
#define SIO_INTERP1_CTRL_LANE0_OVERF0_LSB    _u(23)
#define SIO_INTERP1_CTRL_LANE0_OVERF0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP1_CTRL_LANE0_CLAMP
// Description : Only present on INTERP1 on each core. If CLAMP mode is enabled:
//               - LANE0 result is shifted and masked ACCUM0, clamped by a lower
//               bound of
//               BASE0 and an upper bound of BASE1.
//               - Signedness of these comparisons is determined by
//               LANE0_CTRL_SIGNED
#define SIO_INTERP1_CTRL_LANE0_CLAMP_RESET  _u(0x0)
#define SIO_INTERP1_CTRL_LANE0_CLAMP_BITS   _u(0x00400000)
#define SIO_INTERP1_CTRL_LANE0_CLAMP_MSB    _u(22)
#define SIO_INTERP1_CTRL_LANE0_CLAMP_LSB    _u(22)
#define SIO_INTERP1_CTRL_LANE0_CLAMP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP1_CTRL_LANE0_FORCE_MSB
// Description : ORed into bits 29:28 of the lane result presented to the
//               processor on the bus.
//               No effect on the internal 32-bit datapath. Handy for using a
//               lane to generate sequence
//               of pointers into flash or SRAM.
#define SIO_INTERP1_CTRL_LANE0_FORCE_MSB_RESET  _u(0x0)
#define SIO_INTERP1_CTRL_LANE0_FORCE_MSB_BITS   _u(0x00180000)
#define SIO_INTERP1_CTRL_LANE0_FORCE_MSB_MSB    _u(20)
#define SIO_INTERP1_CTRL_LANE0_FORCE_MSB_LSB    _u(19)
#define SIO_INTERP1_CTRL_LANE0_FORCE_MSB_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP1_CTRL_LANE0_ADD_RAW
// Description : If 1, mask + shift is bypassed for LANE0 result. This does not
//               affect FULL result.
#define SIO_INTERP1_CTRL_LANE0_ADD_RAW_RESET  _u(0x0)
#define SIO_INTERP1_CTRL_LANE0_ADD_RAW_BITS   _u(0x00040000)
#define SIO_INTERP1_CTRL_LANE0_ADD_RAW_MSB    _u(18)
#define SIO_INTERP1_CTRL_LANE0_ADD_RAW_LSB    _u(18)
#define SIO_INTERP1_CTRL_LANE0_ADD_RAW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP1_CTRL_LANE0_CROSS_RESULT
// Description : If 1, feed the opposite lane's result into this lane's
//               accumulator on POP.
#define SIO_INTERP1_CTRL_LANE0_CROSS_RESULT_RESET  _u(0x0)
#define SIO_INTERP1_CTRL_LANE0_CROSS_RESULT_BITS   _u(0x00020000)
#define SIO_INTERP1_CTRL_LANE0_CROSS_RESULT_MSB    _u(17)
#define SIO_INTERP1_CTRL_LANE0_CROSS_RESULT_LSB    _u(17)
#define SIO_INTERP1_CTRL_LANE0_CROSS_RESULT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP1_CTRL_LANE0_CROSS_INPUT
// Description : If 1, feed the opposite lane's accumulator into this lane's
//               shift + mask hardware.
//               Takes effect even if ADD_RAW is set (the CROSS_INPUT mux is
//               before the shift+mask bypass)
#define SIO_INTERP1_CTRL_LANE0_CROSS_INPUT_RESET  _u(0x0)
#define SIO_INTERP1_CTRL_LANE0_CROSS_INPUT_BITS   _u(0x00010000)
#define SIO_INTERP1_CTRL_LANE0_CROSS_INPUT_MSB    _u(16)
#define SIO_INTERP1_CTRL_LANE0_CROSS_INPUT_LSB    _u(16)
#define SIO_INTERP1_CTRL_LANE0_CROSS_INPUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP1_CTRL_LANE0_SIGNED
// Description : If SIGNED is set, the shifted and masked accumulator value is
//               sign-extended to 32 bits
//               before adding to BASE0, and LANE0 PEEK/POP appear extended to
//               32 bits when read by processor.
#define SIO_INTERP1_CTRL_LANE0_SIGNED_RESET  _u(0x0)
#define SIO_INTERP1_CTRL_LANE0_SIGNED_BITS   _u(0x00008000)
#define SIO_INTERP1_CTRL_LANE0_SIGNED_MSB    _u(15)
#define SIO_INTERP1_CTRL_LANE0_SIGNED_LSB    _u(15)
#define SIO_INTERP1_CTRL_LANE0_SIGNED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP1_CTRL_LANE0_MASK_MSB
// Description : The most-significant bit allowed to pass by the mask
//               (inclusive)
//               Setting MSB < LSB may cause chip to turn inside-out
#define SIO_INTERP1_CTRL_LANE0_MASK_MSB_RESET  _u(0x00)
#define SIO_INTERP1_CTRL_LANE0_MASK_MSB_BITS   _u(0x00007c00)
#define SIO_INTERP1_CTRL_LANE0_MASK_MSB_MSB    _u(14)
#define SIO_INTERP1_CTRL_LANE0_MASK_MSB_LSB    _u(10)
#define SIO_INTERP1_CTRL_LANE0_MASK_MSB_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP1_CTRL_LANE0_MASK_LSB
// Description : The least-significant bit allowed to pass by the mask
//               (inclusive)
#define SIO_INTERP1_CTRL_LANE0_MASK_LSB_RESET  _u(0x00)
#define SIO_INTERP1_CTRL_LANE0_MASK_LSB_BITS   _u(0x000003e0)
#define SIO_INTERP1_CTRL_LANE0_MASK_LSB_MSB    _u(9)
#define SIO_INTERP1_CTRL_LANE0_MASK_LSB_LSB    _u(5)
#define SIO_INTERP1_CTRL_LANE0_MASK_LSB_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP1_CTRL_LANE0_SHIFT
// Description : Logical right-shift applied to accumulator before masking
#define SIO_INTERP1_CTRL_LANE0_SHIFT_RESET  _u(0x00)
#define SIO_INTERP1_CTRL_LANE0_SHIFT_BITS   _u(0x0000001f)
#define SIO_INTERP1_CTRL_LANE0_SHIFT_MSB    _u(4)
#define SIO_INTERP1_CTRL_LANE0_SHIFT_LSB    _u(0)
#define SIO_INTERP1_CTRL_LANE0_SHIFT_ACCESS "RW"
// =============================================================================
// Register    : SIO_INTERP1_CTRL_LANE1
// Description : Control register for lane 1
#define SIO_INTERP1_CTRL_LANE1_OFFSET _u(0x000000f0)
#define SIO_INTERP1_CTRL_LANE1_BITS   _u(0x001fffff)
#define SIO_INTERP1_CTRL_LANE1_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP1_CTRL_LANE1_FORCE_MSB
// Description : ORed into bits 29:28 of the lane result presented to the
//               processor on the bus.
//               No effect on the internal 32-bit datapath. Handy for using a
//               lane to generate sequence
//               of pointers into flash or SRAM.
#define SIO_INTERP1_CTRL_LANE1_FORCE_MSB_RESET  _u(0x0)
#define SIO_INTERP1_CTRL_LANE1_FORCE_MSB_BITS   _u(0x00180000)
#define SIO_INTERP1_CTRL_LANE1_FORCE_MSB_MSB    _u(20)
#define SIO_INTERP1_CTRL_LANE1_FORCE_MSB_LSB    _u(19)
#define SIO_INTERP1_CTRL_LANE1_FORCE_MSB_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP1_CTRL_LANE1_ADD_RAW
// Description : If 1, mask + shift is bypassed for LANE1 result. This does not
//               affect FULL result.
#define SIO_INTERP1_CTRL_LANE1_ADD_RAW_RESET  _u(0x0)
#define SIO_INTERP1_CTRL_LANE1_ADD_RAW_BITS   _u(0x00040000)
#define SIO_INTERP1_CTRL_LANE1_ADD_RAW_MSB    _u(18)
#define SIO_INTERP1_CTRL_LANE1_ADD_RAW_LSB    _u(18)
#define SIO_INTERP1_CTRL_LANE1_ADD_RAW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP1_CTRL_LANE1_CROSS_RESULT
// Description : If 1, feed the opposite lane's result into this lane's
//               accumulator on POP.
#define SIO_INTERP1_CTRL_LANE1_CROSS_RESULT_RESET  _u(0x0)
#define SIO_INTERP1_CTRL_LANE1_CROSS_RESULT_BITS   _u(0x00020000)
#define SIO_INTERP1_CTRL_LANE1_CROSS_RESULT_MSB    _u(17)
#define SIO_INTERP1_CTRL_LANE1_CROSS_RESULT_LSB    _u(17)
#define SIO_INTERP1_CTRL_LANE1_CROSS_RESULT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP1_CTRL_LANE1_CROSS_INPUT
// Description : If 1, feed the opposite lane's accumulator into this lane's
//               shift + mask hardware.
//               Takes effect even if ADD_RAW is set (the CROSS_INPUT mux is
//               before the shift+mask bypass)
#define SIO_INTERP1_CTRL_LANE1_CROSS_INPUT_RESET  _u(0x0)
#define SIO_INTERP1_CTRL_LANE1_CROSS_INPUT_BITS   _u(0x00010000)
#define SIO_INTERP1_CTRL_LANE1_CROSS_INPUT_MSB    _u(16)
#define SIO_INTERP1_CTRL_LANE1_CROSS_INPUT_LSB    _u(16)
#define SIO_INTERP1_CTRL_LANE1_CROSS_INPUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP1_CTRL_LANE1_SIGNED
// Description : If SIGNED is set, the shifted and masked accumulator value is
//               sign-extended to 32 bits
//               before adding to BASE1, and LANE1 PEEK/POP appear extended to
//               32 bits when read by processor.
#define SIO_INTERP1_CTRL_LANE1_SIGNED_RESET  _u(0x0)
#define SIO_INTERP1_CTRL_LANE1_SIGNED_BITS   _u(0x00008000)
#define SIO_INTERP1_CTRL_LANE1_SIGNED_MSB    _u(15)
#define SIO_INTERP1_CTRL_LANE1_SIGNED_LSB    _u(15)
#define SIO_INTERP1_CTRL_LANE1_SIGNED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP1_CTRL_LANE1_MASK_MSB
// Description : The most-significant bit allowed to pass by the mask
//               (inclusive)
//               Setting MSB < LSB may cause chip to turn inside-out
#define SIO_INTERP1_CTRL_LANE1_MASK_MSB_RESET  _u(0x00)
#define SIO_INTERP1_CTRL_LANE1_MASK_MSB_BITS   _u(0x00007c00)
#define SIO_INTERP1_CTRL_LANE1_MASK_MSB_MSB    _u(14)
#define SIO_INTERP1_CTRL_LANE1_MASK_MSB_LSB    _u(10)
#define SIO_INTERP1_CTRL_LANE1_MASK_MSB_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP1_CTRL_LANE1_MASK_LSB
// Description : The least-significant bit allowed to pass by the mask
//               (inclusive)
#define SIO_INTERP1_CTRL_LANE1_MASK_LSB_RESET  _u(0x00)
#define SIO_INTERP1_CTRL_LANE1_MASK_LSB_BITS   _u(0x000003e0)
#define SIO_INTERP1_CTRL_LANE1_MASK_LSB_MSB    _u(9)
#define SIO_INTERP1_CTRL_LANE1_MASK_LSB_LSB    _u(5)
#define SIO_INTERP1_CTRL_LANE1_MASK_LSB_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SIO_INTERP1_CTRL_LANE1_SHIFT
// Description : Logical right-shift applied to accumulator before masking
#define SIO_INTERP1_CTRL_LANE1_SHIFT_RESET  _u(0x00)
#define SIO_INTERP1_CTRL_LANE1_SHIFT_BITS   _u(0x0000001f)
#define SIO_INTERP1_CTRL_LANE1_SHIFT_MSB    _u(4)
#define SIO_INTERP1_CTRL_LANE1_SHIFT_LSB    _u(0)
#define SIO_INTERP1_CTRL_LANE1_SHIFT_ACCESS "RW"
// =============================================================================
// Register    : SIO_INTERP1_ACCUM0_ADD
// Description : Values written here are atomically added to ACCUM0
//               Reading yields lane 0's raw shift and mask value (BASE0 not
//               added).
#define SIO_INTERP1_ACCUM0_ADD_OFFSET _u(0x000000f4)
#define SIO_INTERP1_ACCUM0_ADD_BITS   _u(0x00ffffff)
#define SIO_INTERP1_ACCUM0_ADD_RESET  _u(0x00000000)
#define SIO_INTERP1_ACCUM0_ADD_MSB    _u(23)
#define SIO_INTERP1_ACCUM0_ADD_LSB    _u(0)
#define SIO_INTERP1_ACCUM0_ADD_ACCESS "RW"
// =============================================================================
// Register    : SIO_INTERP1_ACCUM1_ADD
// Description : Values written here are atomically added to ACCUM1
//               Reading yields lane 1's raw shift and mask value (BASE1 not
//               added).
#define SIO_INTERP1_ACCUM1_ADD_OFFSET _u(0x000000f8)
#define SIO_INTERP1_ACCUM1_ADD_BITS   _u(0x00ffffff)
#define SIO_INTERP1_ACCUM1_ADD_RESET  _u(0x00000000)
#define SIO_INTERP1_ACCUM1_ADD_MSB    _u(23)
#define SIO_INTERP1_ACCUM1_ADD_LSB    _u(0)
#define SIO_INTERP1_ACCUM1_ADD_ACCESS "RW"
// =============================================================================
// Register    : SIO_INTERP1_BASE_1AND0
// Description : On write, the lower 16 bits go to BASE0, upper bits to BASE1
//               simultaneously.
//               Each half is sign-extended to 32 bits if that lane's SIGNED
//               flag is set.
#define SIO_INTERP1_BASE_1AND0_OFFSET _u(0x000000fc)
#define SIO_INTERP1_BASE_1AND0_BITS   _u(0xffffffff)
#define SIO_INTERP1_BASE_1AND0_RESET  _u(0x00000000)
#define SIO_INTERP1_BASE_1AND0_MSB    _u(31)
#define SIO_INTERP1_BASE_1AND0_LSB    _u(0)
#define SIO_INTERP1_BASE_1AND0_ACCESS "WO"
// =============================================================================
// Register    : SIO_SPINLOCK0
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK0_OFFSET _u(0x00000100)
#define SIO_SPINLOCK0_BITS   _u(0xffffffff)
#define SIO_SPINLOCK0_RESET  _u(0x00000000)
#define SIO_SPINLOCK0_MSB    _u(31)
#define SIO_SPINLOCK0_LSB    _u(0)
#define SIO_SPINLOCK0_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK1
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK1_OFFSET _u(0x00000104)
#define SIO_SPINLOCK1_BITS   _u(0xffffffff)
#define SIO_SPINLOCK1_RESET  _u(0x00000000)
#define SIO_SPINLOCK1_MSB    _u(31)
#define SIO_SPINLOCK1_LSB    _u(0)
#define SIO_SPINLOCK1_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK2
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK2_OFFSET _u(0x00000108)
#define SIO_SPINLOCK2_BITS   _u(0xffffffff)
#define SIO_SPINLOCK2_RESET  _u(0x00000000)
#define SIO_SPINLOCK2_MSB    _u(31)
#define SIO_SPINLOCK2_LSB    _u(0)
#define SIO_SPINLOCK2_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK3
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK3_OFFSET _u(0x0000010c)
#define SIO_SPINLOCK3_BITS   _u(0xffffffff)
#define SIO_SPINLOCK3_RESET  _u(0x00000000)
#define SIO_SPINLOCK3_MSB    _u(31)
#define SIO_SPINLOCK3_LSB    _u(0)
#define SIO_SPINLOCK3_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK4
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK4_OFFSET _u(0x00000110)
#define SIO_SPINLOCK4_BITS   _u(0xffffffff)
#define SIO_SPINLOCK4_RESET  _u(0x00000000)
#define SIO_SPINLOCK4_MSB    _u(31)
#define SIO_SPINLOCK4_LSB    _u(0)
#define SIO_SPINLOCK4_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK5
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK5_OFFSET _u(0x00000114)
#define SIO_SPINLOCK5_BITS   _u(0xffffffff)
#define SIO_SPINLOCK5_RESET  _u(0x00000000)
#define SIO_SPINLOCK5_MSB    _u(31)
#define SIO_SPINLOCK5_LSB    _u(0)
#define SIO_SPINLOCK5_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK6
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK6_OFFSET _u(0x00000118)
#define SIO_SPINLOCK6_BITS   _u(0xffffffff)
#define SIO_SPINLOCK6_RESET  _u(0x00000000)
#define SIO_SPINLOCK6_MSB    _u(31)
#define SIO_SPINLOCK6_LSB    _u(0)
#define SIO_SPINLOCK6_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK7
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK7_OFFSET _u(0x0000011c)
#define SIO_SPINLOCK7_BITS   _u(0xffffffff)
#define SIO_SPINLOCK7_RESET  _u(0x00000000)
#define SIO_SPINLOCK7_MSB    _u(31)
#define SIO_SPINLOCK7_LSB    _u(0)
#define SIO_SPINLOCK7_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK8
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK8_OFFSET _u(0x00000120)
#define SIO_SPINLOCK8_BITS   _u(0xffffffff)
#define SIO_SPINLOCK8_RESET  _u(0x00000000)
#define SIO_SPINLOCK8_MSB    _u(31)
#define SIO_SPINLOCK8_LSB    _u(0)
#define SIO_SPINLOCK8_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK9
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK9_OFFSET _u(0x00000124)
#define SIO_SPINLOCK9_BITS   _u(0xffffffff)
#define SIO_SPINLOCK9_RESET  _u(0x00000000)
#define SIO_SPINLOCK9_MSB    _u(31)
#define SIO_SPINLOCK9_LSB    _u(0)
#define SIO_SPINLOCK9_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK10
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK10_OFFSET _u(0x00000128)
#define SIO_SPINLOCK10_BITS   _u(0xffffffff)
#define SIO_SPINLOCK10_RESET  _u(0x00000000)
#define SIO_SPINLOCK10_MSB    _u(31)
#define SIO_SPINLOCK10_LSB    _u(0)
#define SIO_SPINLOCK10_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK11
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK11_OFFSET _u(0x0000012c)
#define SIO_SPINLOCK11_BITS   _u(0xffffffff)
#define SIO_SPINLOCK11_RESET  _u(0x00000000)
#define SIO_SPINLOCK11_MSB    _u(31)
#define SIO_SPINLOCK11_LSB    _u(0)
#define SIO_SPINLOCK11_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK12
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK12_OFFSET _u(0x00000130)
#define SIO_SPINLOCK12_BITS   _u(0xffffffff)
#define SIO_SPINLOCK12_RESET  _u(0x00000000)
#define SIO_SPINLOCK12_MSB    _u(31)
#define SIO_SPINLOCK12_LSB    _u(0)
#define SIO_SPINLOCK12_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK13
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK13_OFFSET _u(0x00000134)
#define SIO_SPINLOCK13_BITS   _u(0xffffffff)
#define SIO_SPINLOCK13_RESET  _u(0x00000000)
#define SIO_SPINLOCK13_MSB    _u(31)
#define SIO_SPINLOCK13_LSB    _u(0)
#define SIO_SPINLOCK13_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK14
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK14_OFFSET _u(0x00000138)
#define SIO_SPINLOCK14_BITS   _u(0xffffffff)
#define SIO_SPINLOCK14_RESET  _u(0x00000000)
#define SIO_SPINLOCK14_MSB    _u(31)
#define SIO_SPINLOCK14_LSB    _u(0)
#define SIO_SPINLOCK14_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK15
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK15_OFFSET _u(0x0000013c)
#define SIO_SPINLOCK15_BITS   _u(0xffffffff)
#define SIO_SPINLOCK15_RESET  _u(0x00000000)
#define SIO_SPINLOCK15_MSB    _u(31)
#define SIO_SPINLOCK15_LSB    _u(0)
#define SIO_SPINLOCK15_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK16
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK16_OFFSET _u(0x00000140)
#define SIO_SPINLOCK16_BITS   _u(0xffffffff)
#define SIO_SPINLOCK16_RESET  _u(0x00000000)
#define SIO_SPINLOCK16_MSB    _u(31)
#define SIO_SPINLOCK16_LSB    _u(0)
#define SIO_SPINLOCK16_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK17
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK17_OFFSET _u(0x00000144)
#define SIO_SPINLOCK17_BITS   _u(0xffffffff)
#define SIO_SPINLOCK17_RESET  _u(0x00000000)
#define SIO_SPINLOCK17_MSB    _u(31)
#define SIO_SPINLOCK17_LSB    _u(0)
#define SIO_SPINLOCK17_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK18
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK18_OFFSET _u(0x00000148)
#define SIO_SPINLOCK18_BITS   _u(0xffffffff)
#define SIO_SPINLOCK18_RESET  _u(0x00000000)
#define SIO_SPINLOCK18_MSB    _u(31)
#define SIO_SPINLOCK18_LSB    _u(0)
#define SIO_SPINLOCK18_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK19
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK19_OFFSET _u(0x0000014c)
#define SIO_SPINLOCK19_BITS   _u(0xffffffff)
#define SIO_SPINLOCK19_RESET  _u(0x00000000)
#define SIO_SPINLOCK19_MSB    _u(31)
#define SIO_SPINLOCK19_LSB    _u(0)
#define SIO_SPINLOCK19_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK20
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK20_OFFSET _u(0x00000150)
#define SIO_SPINLOCK20_BITS   _u(0xffffffff)
#define SIO_SPINLOCK20_RESET  _u(0x00000000)
#define SIO_SPINLOCK20_MSB    _u(31)
#define SIO_SPINLOCK20_LSB    _u(0)
#define SIO_SPINLOCK20_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK21
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK21_OFFSET _u(0x00000154)
#define SIO_SPINLOCK21_BITS   _u(0xffffffff)
#define SIO_SPINLOCK21_RESET  _u(0x00000000)
#define SIO_SPINLOCK21_MSB    _u(31)
#define SIO_SPINLOCK21_LSB    _u(0)
#define SIO_SPINLOCK21_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK22
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK22_OFFSET _u(0x00000158)
#define SIO_SPINLOCK22_BITS   _u(0xffffffff)
#define SIO_SPINLOCK22_RESET  _u(0x00000000)
#define SIO_SPINLOCK22_MSB    _u(31)
#define SIO_SPINLOCK22_LSB    _u(0)
#define SIO_SPINLOCK22_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK23
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK23_OFFSET _u(0x0000015c)
#define SIO_SPINLOCK23_BITS   _u(0xffffffff)
#define SIO_SPINLOCK23_RESET  _u(0x00000000)
#define SIO_SPINLOCK23_MSB    _u(31)
#define SIO_SPINLOCK23_LSB    _u(0)
#define SIO_SPINLOCK23_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK24
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK24_OFFSET _u(0x00000160)
#define SIO_SPINLOCK24_BITS   _u(0xffffffff)
#define SIO_SPINLOCK24_RESET  _u(0x00000000)
#define SIO_SPINLOCK24_MSB    _u(31)
#define SIO_SPINLOCK24_LSB    _u(0)
#define SIO_SPINLOCK24_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK25
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK25_OFFSET _u(0x00000164)
#define SIO_SPINLOCK25_BITS   _u(0xffffffff)
#define SIO_SPINLOCK25_RESET  _u(0x00000000)
#define SIO_SPINLOCK25_MSB    _u(31)
#define SIO_SPINLOCK25_LSB    _u(0)
#define SIO_SPINLOCK25_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK26
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK26_OFFSET _u(0x00000168)
#define SIO_SPINLOCK26_BITS   _u(0xffffffff)
#define SIO_SPINLOCK26_RESET  _u(0x00000000)
#define SIO_SPINLOCK26_MSB    _u(31)
#define SIO_SPINLOCK26_LSB    _u(0)
#define SIO_SPINLOCK26_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK27
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK27_OFFSET _u(0x0000016c)
#define SIO_SPINLOCK27_BITS   _u(0xffffffff)
#define SIO_SPINLOCK27_RESET  _u(0x00000000)
#define SIO_SPINLOCK27_MSB    _u(31)
#define SIO_SPINLOCK27_LSB    _u(0)
#define SIO_SPINLOCK27_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK28
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK28_OFFSET _u(0x00000170)
#define SIO_SPINLOCK28_BITS   _u(0xffffffff)
#define SIO_SPINLOCK28_RESET  _u(0x00000000)
#define SIO_SPINLOCK28_MSB    _u(31)
#define SIO_SPINLOCK28_LSB    _u(0)
#define SIO_SPINLOCK28_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK29
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK29_OFFSET _u(0x00000174)
#define SIO_SPINLOCK29_BITS   _u(0xffffffff)
#define SIO_SPINLOCK29_RESET  _u(0x00000000)
#define SIO_SPINLOCK29_MSB    _u(31)
#define SIO_SPINLOCK29_LSB    _u(0)
#define SIO_SPINLOCK29_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK30
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK30_OFFSET _u(0x00000178)
#define SIO_SPINLOCK30_BITS   _u(0xffffffff)
#define SIO_SPINLOCK30_RESET  _u(0x00000000)
#define SIO_SPINLOCK30_MSB    _u(31)
#define SIO_SPINLOCK30_LSB    _u(0)
#define SIO_SPINLOCK30_ACCESS "RW"
// =============================================================================
// Register    : SIO_SPINLOCK31
// Description : Reading from a spinlock address will:
//               - Return 0 if lock is already locked
//               - Otherwise return nonzero, and simultaneously claim the lock
//
//               Writing (any value) releases the lock.
//               If core 0 and core 1 attempt to claim the same lock
//               simultaneously, core 0 wins.
//               The value returned on success is 0x1 << lock number.
#define SIO_SPINLOCK31_OFFSET _u(0x0000017c)
#define SIO_SPINLOCK31_BITS   _u(0xffffffff)
#define SIO_SPINLOCK31_RESET  _u(0x00000000)
#define SIO_SPINLOCK31_MSB    _u(31)
#define SIO_SPINLOCK31_LSB    _u(0)
#define SIO_SPINLOCK31_ACCESS "RW"
// =============================================================================
#endif // HARDWARE_REGS_SIO_DEFINED
