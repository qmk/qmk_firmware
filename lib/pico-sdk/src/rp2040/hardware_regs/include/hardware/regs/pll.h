/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : PLL
// Version        : 1
// Bus type       : apb
// Description    : None
// =============================================================================
#ifndef HARDWARE_REGS_PLL_DEFINED
#define HARDWARE_REGS_PLL_DEFINED
// =============================================================================
// Register    : PLL_CS
// Description : Control and Status
//               GENERAL CONSTRAINTS:
//               Reference clock frequency min=5MHz, max=800MHz
//               Feedback divider min=16, max=320
//               VCO frequency min=750MHz, max=1600MHz
#define PLL_CS_OFFSET _u(0x00000000)
#define PLL_CS_BITS   _u(0x8000013f)
#define PLL_CS_RESET  _u(0x00000001)
// -----------------------------------------------------------------------------
// Field       : PLL_CS_LOCK
// Description : PLL is locked
#define PLL_CS_LOCK_RESET  _u(0x0)
#define PLL_CS_LOCK_BITS   _u(0x80000000)
#define PLL_CS_LOCK_MSB    _u(31)
#define PLL_CS_LOCK_LSB    _u(31)
#define PLL_CS_LOCK_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PLL_CS_BYPASS
// Description : Passes the reference clock to the output instead of the divided
//               VCO. The VCO continues to run so the user can switch between
//               the reference clock and the divided VCO but the output will
//               glitch when doing so.
#define PLL_CS_BYPASS_RESET  _u(0x0)
#define PLL_CS_BYPASS_BITS   _u(0x00000100)
#define PLL_CS_BYPASS_MSB    _u(8)
#define PLL_CS_BYPASS_LSB    _u(8)
#define PLL_CS_BYPASS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PLL_CS_REFDIV
// Description : Divides the PLL input reference clock.
//               Behaviour is undefined for div=0.
//               PLL output will be unpredictable during refdiv changes, wait
//               for lock=1 before using it.
#define PLL_CS_REFDIV_RESET  _u(0x01)
#define PLL_CS_REFDIV_BITS   _u(0x0000003f)
#define PLL_CS_REFDIV_MSB    _u(5)
#define PLL_CS_REFDIV_LSB    _u(0)
#define PLL_CS_REFDIV_ACCESS "RW"
// =============================================================================
// Register    : PLL_PWR
// Description : Controls the PLL power modes.
#define PLL_PWR_OFFSET _u(0x00000004)
#define PLL_PWR_BITS   _u(0x0000002d)
#define PLL_PWR_RESET  _u(0x0000002d)
// -----------------------------------------------------------------------------
// Field       : PLL_PWR_VCOPD
// Description : PLL VCO powerdown
//               To save power set high when PLL output not required or
//               bypass=1.
#define PLL_PWR_VCOPD_RESET  _u(0x1)
#define PLL_PWR_VCOPD_BITS   _u(0x00000020)
#define PLL_PWR_VCOPD_MSB    _u(5)
#define PLL_PWR_VCOPD_LSB    _u(5)
#define PLL_PWR_VCOPD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PLL_PWR_POSTDIVPD
// Description : PLL post divider powerdown
//               To save power set high when PLL output not required or
//               bypass=1.
#define PLL_PWR_POSTDIVPD_RESET  _u(0x1)
#define PLL_PWR_POSTDIVPD_BITS   _u(0x00000008)
#define PLL_PWR_POSTDIVPD_MSB    _u(3)
#define PLL_PWR_POSTDIVPD_LSB    _u(3)
#define PLL_PWR_POSTDIVPD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PLL_PWR_DSMPD
// Description : PLL DSM powerdown
//               Nothing is achieved by setting this low.
#define PLL_PWR_DSMPD_RESET  _u(0x1)
#define PLL_PWR_DSMPD_BITS   _u(0x00000004)
#define PLL_PWR_DSMPD_MSB    _u(2)
#define PLL_PWR_DSMPD_LSB    _u(2)
#define PLL_PWR_DSMPD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PLL_PWR_PD
// Description : PLL powerdown
//               To save power set high when PLL output not required.
#define PLL_PWR_PD_RESET  _u(0x1)
#define PLL_PWR_PD_BITS   _u(0x00000001)
#define PLL_PWR_PD_MSB    _u(0)
#define PLL_PWR_PD_LSB    _u(0)
#define PLL_PWR_PD_ACCESS "RW"
// =============================================================================
// Register    : PLL_FBDIV_INT
// Description : Feedback divisor
//               (note: this PLL does not support fractional division)
//               see ctrl reg description for constraints
#define PLL_FBDIV_INT_OFFSET _u(0x00000008)
#define PLL_FBDIV_INT_BITS   _u(0x00000fff)
#define PLL_FBDIV_INT_RESET  _u(0x00000000)
#define PLL_FBDIV_INT_MSB    _u(11)
#define PLL_FBDIV_INT_LSB    _u(0)
#define PLL_FBDIV_INT_ACCESS "RW"
// =============================================================================
// Register    : PLL_PRIM
// Description : Controls the PLL post dividers for the primary output
//               (note: this PLL does not have a secondary output)
//               the primary output is driven from VCO divided by
//               postdiv1*postdiv2
#define PLL_PRIM_OFFSET _u(0x0000000c)
#define PLL_PRIM_BITS   _u(0x00077000)
#define PLL_PRIM_RESET  _u(0x00077000)
// -----------------------------------------------------------------------------
// Field       : PLL_PRIM_POSTDIV1
// Description : divide by 1-7
#define PLL_PRIM_POSTDIV1_RESET  _u(0x7)
#define PLL_PRIM_POSTDIV1_BITS   _u(0x00070000)
#define PLL_PRIM_POSTDIV1_MSB    _u(18)
#define PLL_PRIM_POSTDIV1_LSB    _u(16)
#define PLL_PRIM_POSTDIV1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PLL_PRIM_POSTDIV2
// Description : divide by 1-7
#define PLL_PRIM_POSTDIV2_RESET  _u(0x7)
#define PLL_PRIM_POSTDIV2_BITS   _u(0x00007000)
#define PLL_PRIM_POSTDIV2_MSB    _u(14)
#define PLL_PRIM_POSTDIV2_LSB    _u(12)
#define PLL_PRIM_POSTDIV2_ACCESS "RW"
// =============================================================================
#endif // HARDWARE_REGS_PLL_DEFINED
