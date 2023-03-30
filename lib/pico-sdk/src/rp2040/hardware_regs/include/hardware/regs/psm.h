/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : PSM
// Version        : 1
// Bus type       : apb
// Description    : None
// =============================================================================
#ifndef HARDWARE_REGS_PSM_DEFINED
#define HARDWARE_REGS_PSM_DEFINED
// =============================================================================
// Register    : PSM_FRCE_ON
// Description : Force block out of reset (i.e. power it on)
#define PSM_FRCE_ON_OFFSET _u(0x00000000)
#define PSM_FRCE_ON_BITS   _u(0x0001ffff)
#define PSM_FRCE_ON_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_ON_PROC1
// Description : None
#define PSM_FRCE_ON_PROC1_RESET  _u(0x0)
#define PSM_FRCE_ON_PROC1_BITS   _u(0x00010000)
#define PSM_FRCE_ON_PROC1_MSB    _u(16)
#define PSM_FRCE_ON_PROC1_LSB    _u(16)
#define PSM_FRCE_ON_PROC1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_ON_PROC0
// Description : None
#define PSM_FRCE_ON_PROC0_RESET  _u(0x0)
#define PSM_FRCE_ON_PROC0_BITS   _u(0x00008000)
#define PSM_FRCE_ON_PROC0_MSB    _u(15)
#define PSM_FRCE_ON_PROC0_LSB    _u(15)
#define PSM_FRCE_ON_PROC0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_ON_SIO
// Description : None
#define PSM_FRCE_ON_SIO_RESET  _u(0x0)
#define PSM_FRCE_ON_SIO_BITS   _u(0x00004000)
#define PSM_FRCE_ON_SIO_MSB    _u(14)
#define PSM_FRCE_ON_SIO_LSB    _u(14)
#define PSM_FRCE_ON_SIO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_ON_VREG_AND_CHIP_RESET
// Description : None
#define PSM_FRCE_ON_VREG_AND_CHIP_RESET_RESET  _u(0x0)
#define PSM_FRCE_ON_VREG_AND_CHIP_RESET_BITS   _u(0x00002000)
#define PSM_FRCE_ON_VREG_AND_CHIP_RESET_MSB    _u(13)
#define PSM_FRCE_ON_VREG_AND_CHIP_RESET_LSB    _u(13)
#define PSM_FRCE_ON_VREG_AND_CHIP_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_ON_XIP
// Description : None
#define PSM_FRCE_ON_XIP_RESET  _u(0x0)
#define PSM_FRCE_ON_XIP_BITS   _u(0x00001000)
#define PSM_FRCE_ON_XIP_MSB    _u(12)
#define PSM_FRCE_ON_XIP_LSB    _u(12)
#define PSM_FRCE_ON_XIP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_ON_SRAM5
// Description : None
#define PSM_FRCE_ON_SRAM5_RESET  _u(0x0)
#define PSM_FRCE_ON_SRAM5_BITS   _u(0x00000800)
#define PSM_FRCE_ON_SRAM5_MSB    _u(11)
#define PSM_FRCE_ON_SRAM5_LSB    _u(11)
#define PSM_FRCE_ON_SRAM5_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_ON_SRAM4
// Description : None
#define PSM_FRCE_ON_SRAM4_RESET  _u(0x0)
#define PSM_FRCE_ON_SRAM4_BITS   _u(0x00000400)
#define PSM_FRCE_ON_SRAM4_MSB    _u(10)
#define PSM_FRCE_ON_SRAM4_LSB    _u(10)
#define PSM_FRCE_ON_SRAM4_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_ON_SRAM3
// Description : None
#define PSM_FRCE_ON_SRAM3_RESET  _u(0x0)
#define PSM_FRCE_ON_SRAM3_BITS   _u(0x00000200)
#define PSM_FRCE_ON_SRAM3_MSB    _u(9)
#define PSM_FRCE_ON_SRAM3_LSB    _u(9)
#define PSM_FRCE_ON_SRAM3_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_ON_SRAM2
// Description : None
#define PSM_FRCE_ON_SRAM2_RESET  _u(0x0)
#define PSM_FRCE_ON_SRAM2_BITS   _u(0x00000100)
#define PSM_FRCE_ON_SRAM2_MSB    _u(8)
#define PSM_FRCE_ON_SRAM2_LSB    _u(8)
#define PSM_FRCE_ON_SRAM2_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_ON_SRAM1
// Description : None
#define PSM_FRCE_ON_SRAM1_RESET  _u(0x0)
#define PSM_FRCE_ON_SRAM1_BITS   _u(0x00000080)
#define PSM_FRCE_ON_SRAM1_MSB    _u(7)
#define PSM_FRCE_ON_SRAM1_LSB    _u(7)
#define PSM_FRCE_ON_SRAM1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_ON_SRAM0
// Description : None
#define PSM_FRCE_ON_SRAM0_RESET  _u(0x0)
#define PSM_FRCE_ON_SRAM0_BITS   _u(0x00000040)
#define PSM_FRCE_ON_SRAM0_MSB    _u(6)
#define PSM_FRCE_ON_SRAM0_LSB    _u(6)
#define PSM_FRCE_ON_SRAM0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_ON_ROM
// Description : None
#define PSM_FRCE_ON_ROM_RESET  _u(0x0)
#define PSM_FRCE_ON_ROM_BITS   _u(0x00000020)
#define PSM_FRCE_ON_ROM_MSB    _u(5)
#define PSM_FRCE_ON_ROM_LSB    _u(5)
#define PSM_FRCE_ON_ROM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_ON_BUSFABRIC
// Description : None
#define PSM_FRCE_ON_BUSFABRIC_RESET  _u(0x0)
#define PSM_FRCE_ON_BUSFABRIC_BITS   _u(0x00000010)
#define PSM_FRCE_ON_BUSFABRIC_MSB    _u(4)
#define PSM_FRCE_ON_BUSFABRIC_LSB    _u(4)
#define PSM_FRCE_ON_BUSFABRIC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_ON_RESETS
// Description : None
#define PSM_FRCE_ON_RESETS_RESET  _u(0x0)
#define PSM_FRCE_ON_RESETS_BITS   _u(0x00000008)
#define PSM_FRCE_ON_RESETS_MSB    _u(3)
#define PSM_FRCE_ON_RESETS_LSB    _u(3)
#define PSM_FRCE_ON_RESETS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_ON_CLOCKS
// Description : None
#define PSM_FRCE_ON_CLOCKS_RESET  _u(0x0)
#define PSM_FRCE_ON_CLOCKS_BITS   _u(0x00000004)
#define PSM_FRCE_ON_CLOCKS_MSB    _u(2)
#define PSM_FRCE_ON_CLOCKS_LSB    _u(2)
#define PSM_FRCE_ON_CLOCKS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_ON_XOSC
// Description : None
#define PSM_FRCE_ON_XOSC_RESET  _u(0x0)
#define PSM_FRCE_ON_XOSC_BITS   _u(0x00000002)
#define PSM_FRCE_ON_XOSC_MSB    _u(1)
#define PSM_FRCE_ON_XOSC_LSB    _u(1)
#define PSM_FRCE_ON_XOSC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_ON_ROSC
// Description : None
#define PSM_FRCE_ON_ROSC_RESET  _u(0x0)
#define PSM_FRCE_ON_ROSC_BITS   _u(0x00000001)
#define PSM_FRCE_ON_ROSC_MSB    _u(0)
#define PSM_FRCE_ON_ROSC_LSB    _u(0)
#define PSM_FRCE_ON_ROSC_ACCESS "RW"
// =============================================================================
// Register    : PSM_FRCE_OFF
// Description : Force into reset (i.e. power it off)
#define PSM_FRCE_OFF_OFFSET _u(0x00000004)
#define PSM_FRCE_OFF_BITS   _u(0x0001ffff)
#define PSM_FRCE_OFF_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_OFF_PROC1
// Description : None
#define PSM_FRCE_OFF_PROC1_RESET  _u(0x0)
#define PSM_FRCE_OFF_PROC1_BITS   _u(0x00010000)
#define PSM_FRCE_OFF_PROC1_MSB    _u(16)
#define PSM_FRCE_OFF_PROC1_LSB    _u(16)
#define PSM_FRCE_OFF_PROC1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_OFF_PROC0
// Description : None
#define PSM_FRCE_OFF_PROC0_RESET  _u(0x0)
#define PSM_FRCE_OFF_PROC0_BITS   _u(0x00008000)
#define PSM_FRCE_OFF_PROC0_MSB    _u(15)
#define PSM_FRCE_OFF_PROC0_LSB    _u(15)
#define PSM_FRCE_OFF_PROC0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_OFF_SIO
// Description : None
#define PSM_FRCE_OFF_SIO_RESET  _u(0x0)
#define PSM_FRCE_OFF_SIO_BITS   _u(0x00004000)
#define PSM_FRCE_OFF_SIO_MSB    _u(14)
#define PSM_FRCE_OFF_SIO_LSB    _u(14)
#define PSM_FRCE_OFF_SIO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_OFF_VREG_AND_CHIP_RESET
// Description : None
#define PSM_FRCE_OFF_VREG_AND_CHIP_RESET_RESET  _u(0x0)
#define PSM_FRCE_OFF_VREG_AND_CHIP_RESET_BITS   _u(0x00002000)
#define PSM_FRCE_OFF_VREG_AND_CHIP_RESET_MSB    _u(13)
#define PSM_FRCE_OFF_VREG_AND_CHIP_RESET_LSB    _u(13)
#define PSM_FRCE_OFF_VREG_AND_CHIP_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_OFF_XIP
// Description : None
#define PSM_FRCE_OFF_XIP_RESET  _u(0x0)
#define PSM_FRCE_OFF_XIP_BITS   _u(0x00001000)
#define PSM_FRCE_OFF_XIP_MSB    _u(12)
#define PSM_FRCE_OFF_XIP_LSB    _u(12)
#define PSM_FRCE_OFF_XIP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_OFF_SRAM5
// Description : None
#define PSM_FRCE_OFF_SRAM5_RESET  _u(0x0)
#define PSM_FRCE_OFF_SRAM5_BITS   _u(0x00000800)
#define PSM_FRCE_OFF_SRAM5_MSB    _u(11)
#define PSM_FRCE_OFF_SRAM5_LSB    _u(11)
#define PSM_FRCE_OFF_SRAM5_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_OFF_SRAM4
// Description : None
#define PSM_FRCE_OFF_SRAM4_RESET  _u(0x0)
#define PSM_FRCE_OFF_SRAM4_BITS   _u(0x00000400)
#define PSM_FRCE_OFF_SRAM4_MSB    _u(10)
#define PSM_FRCE_OFF_SRAM4_LSB    _u(10)
#define PSM_FRCE_OFF_SRAM4_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_OFF_SRAM3
// Description : None
#define PSM_FRCE_OFF_SRAM3_RESET  _u(0x0)
#define PSM_FRCE_OFF_SRAM3_BITS   _u(0x00000200)
#define PSM_FRCE_OFF_SRAM3_MSB    _u(9)
#define PSM_FRCE_OFF_SRAM3_LSB    _u(9)
#define PSM_FRCE_OFF_SRAM3_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_OFF_SRAM2
// Description : None
#define PSM_FRCE_OFF_SRAM2_RESET  _u(0x0)
#define PSM_FRCE_OFF_SRAM2_BITS   _u(0x00000100)
#define PSM_FRCE_OFF_SRAM2_MSB    _u(8)
#define PSM_FRCE_OFF_SRAM2_LSB    _u(8)
#define PSM_FRCE_OFF_SRAM2_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_OFF_SRAM1
// Description : None
#define PSM_FRCE_OFF_SRAM1_RESET  _u(0x0)
#define PSM_FRCE_OFF_SRAM1_BITS   _u(0x00000080)
#define PSM_FRCE_OFF_SRAM1_MSB    _u(7)
#define PSM_FRCE_OFF_SRAM1_LSB    _u(7)
#define PSM_FRCE_OFF_SRAM1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_OFF_SRAM0
// Description : None
#define PSM_FRCE_OFF_SRAM0_RESET  _u(0x0)
#define PSM_FRCE_OFF_SRAM0_BITS   _u(0x00000040)
#define PSM_FRCE_OFF_SRAM0_MSB    _u(6)
#define PSM_FRCE_OFF_SRAM0_LSB    _u(6)
#define PSM_FRCE_OFF_SRAM0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_OFF_ROM
// Description : None
#define PSM_FRCE_OFF_ROM_RESET  _u(0x0)
#define PSM_FRCE_OFF_ROM_BITS   _u(0x00000020)
#define PSM_FRCE_OFF_ROM_MSB    _u(5)
#define PSM_FRCE_OFF_ROM_LSB    _u(5)
#define PSM_FRCE_OFF_ROM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_OFF_BUSFABRIC
// Description : None
#define PSM_FRCE_OFF_BUSFABRIC_RESET  _u(0x0)
#define PSM_FRCE_OFF_BUSFABRIC_BITS   _u(0x00000010)
#define PSM_FRCE_OFF_BUSFABRIC_MSB    _u(4)
#define PSM_FRCE_OFF_BUSFABRIC_LSB    _u(4)
#define PSM_FRCE_OFF_BUSFABRIC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_OFF_RESETS
// Description : None
#define PSM_FRCE_OFF_RESETS_RESET  _u(0x0)
#define PSM_FRCE_OFF_RESETS_BITS   _u(0x00000008)
#define PSM_FRCE_OFF_RESETS_MSB    _u(3)
#define PSM_FRCE_OFF_RESETS_LSB    _u(3)
#define PSM_FRCE_OFF_RESETS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_OFF_CLOCKS
// Description : None
#define PSM_FRCE_OFF_CLOCKS_RESET  _u(0x0)
#define PSM_FRCE_OFF_CLOCKS_BITS   _u(0x00000004)
#define PSM_FRCE_OFF_CLOCKS_MSB    _u(2)
#define PSM_FRCE_OFF_CLOCKS_LSB    _u(2)
#define PSM_FRCE_OFF_CLOCKS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_OFF_XOSC
// Description : None
#define PSM_FRCE_OFF_XOSC_RESET  _u(0x0)
#define PSM_FRCE_OFF_XOSC_BITS   _u(0x00000002)
#define PSM_FRCE_OFF_XOSC_MSB    _u(1)
#define PSM_FRCE_OFF_XOSC_LSB    _u(1)
#define PSM_FRCE_OFF_XOSC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_FRCE_OFF_ROSC
// Description : None
#define PSM_FRCE_OFF_ROSC_RESET  _u(0x0)
#define PSM_FRCE_OFF_ROSC_BITS   _u(0x00000001)
#define PSM_FRCE_OFF_ROSC_MSB    _u(0)
#define PSM_FRCE_OFF_ROSC_LSB    _u(0)
#define PSM_FRCE_OFF_ROSC_ACCESS "RW"
// =============================================================================
// Register    : PSM_WDSEL
// Description : Set to 1 if this peripheral should be reset when the watchdog
//               fires.
#define PSM_WDSEL_OFFSET _u(0x00000008)
#define PSM_WDSEL_BITS   _u(0x0001ffff)
#define PSM_WDSEL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : PSM_WDSEL_PROC1
// Description : None
#define PSM_WDSEL_PROC1_RESET  _u(0x0)
#define PSM_WDSEL_PROC1_BITS   _u(0x00010000)
#define PSM_WDSEL_PROC1_MSB    _u(16)
#define PSM_WDSEL_PROC1_LSB    _u(16)
#define PSM_WDSEL_PROC1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_WDSEL_PROC0
// Description : None
#define PSM_WDSEL_PROC0_RESET  _u(0x0)
#define PSM_WDSEL_PROC0_BITS   _u(0x00008000)
#define PSM_WDSEL_PROC0_MSB    _u(15)
#define PSM_WDSEL_PROC0_LSB    _u(15)
#define PSM_WDSEL_PROC0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_WDSEL_SIO
// Description : None
#define PSM_WDSEL_SIO_RESET  _u(0x0)
#define PSM_WDSEL_SIO_BITS   _u(0x00004000)
#define PSM_WDSEL_SIO_MSB    _u(14)
#define PSM_WDSEL_SIO_LSB    _u(14)
#define PSM_WDSEL_SIO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_WDSEL_VREG_AND_CHIP_RESET
// Description : None
#define PSM_WDSEL_VREG_AND_CHIP_RESET_RESET  _u(0x0)
#define PSM_WDSEL_VREG_AND_CHIP_RESET_BITS   _u(0x00002000)
#define PSM_WDSEL_VREG_AND_CHIP_RESET_MSB    _u(13)
#define PSM_WDSEL_VREG_AND_CHIP_RESET_LSB    _u(13)
#define PSM_WDSEL_VREG_AND_CHIP_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_WDSEL_XIP
// Description : None
#define PSM_WDSEL_XIP_RESET  _u(0x0)
#define PSM_WDSEL_XIP_BITS   _u(0x00001000)
#define PSM_WDSEL_XIP_MSB    _u(12)
#define PSM_WDSEL_XIP_LSB    _u(12)
#define PSM_WDSEL_XIP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_WDSEL_SRAM5
// Description : None
#define PSM_WDSEL_SRAM5_RESET  _u(0x0)
#define PSM_WDSEL_SRAM5_BITS   _u(0x00000800)
#define PSM_WDSEL_SRAM5_MSB    _u(11)
#define PSM_WDSEL_SRAM5_LSB    _u(11)
#define PSM_WDSEL_SRAM5_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_WDSEL_SRAM4
// Description : None
#define PSM_WDSEL_SRAM4_RESET  _u(0x0)
#define PSM_WDSEL_SRAM4_BITS   _u(0x00000400)
#define PSM_WDSEL_SRAM4_MSB    _u(10)
#define PSM_WDSEL_SRAM4_LSB    _u(10)
#define PSM_WDSEL_SRAM4_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_WDSEL_SRAM3
// Description : None
#define PSM_WDSEL_SRAM3_RESET  _u(0x0)
#define PSM_WDSEL_SRAM3_BITS   _u(0x00000200)
#define PSM_WDSEL_SRAM3_MSB    _u(9)
#define PSM_WDSEL_SRAM3_LSB    _u(9)
#define PSM_WDSEL_SRAM3_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_WDSEL_SRAM2
// Description : None
#define PSM_WDSEL_SRAM2_RESET  _u(0x0)
#define PSM_WDSEL_SRAM2_BITS   _u(0x00000100)
#define PSM_WDSEL_SRAM2_MSB    _u(8)
#define PSM_WDSEL_SRAM2_LSB    _u(8)
#define PSM_WDSEL_SRAM2_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_WDSEL_SRAM1
// Description : None
#define PSM_WDSEL_SRAM1_RESET  _u(0x0)
#define PSM_WDSEL_SRAM1_BITS   _u(0x00000080)
#define PSM_WDSEL_SRAM1_MSB    _u(7)
#define PSM_WDSEL_SRAM1_LSB    _u(7)
#define PSM_WDSEL_SRAM1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_WDSEL_SRAM0
// Description : None
#define PSM_WDSEL_SRAM0_RESET  _u(0x0)
#define PSM_WDSEL_SRAM0_BITS   _u(0x00000040)
#define PSM_WDSEL_SRAM0_MSB    _u(6)
#define PSM_WDSEL_SRAM0_LSB    _u(6)
#define PSM_WDSEL_SRAM0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_WDSEL_ROM
// Description : None
#define PSM_WDSEL_ROM_RESET  _u(0x0)
#define PSM_WDSEL_ROM_BITS   _u(0x00000020)
#define PSM_WDSEL_ROM_MSB    _u(5)
#define PSM_WDSEL_ROM_LSB    _u(5)
#define PSM_WDSEL_ROM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_WDSEL_BUSFABRIC
// Description : None
#define PSM_WDSEL_BUSFABRIC_RESET  _u(0x0)
#define PSM_WDSEL_BUSFABRIC_BITS   _u(0x00000010)
#define PSM_WDSEL_BUSFABRIC_MSB    _u(4)
#define PSM_WDSEL_BUSFABRIC_LSB    _u(4)
#define PSM_WDSEL_BUSFABRIC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_WDSEL_RESETS
// Description : None
#define PSM_WDSEL_RESETS_RESET  _u(0x0)
#define PSM_WDSEL_RESETS_BITS   _u(0x00000008)
#define PSM_WDSEL_RESETS_MSB    _u(3)
#define PSM_WDSEL_RESETS_LSB    _u(3)
#define PSM_WDSEL_RESETS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_WDSEL_CLOCKS
// Description : None
#define PSM_WDSEL_CLOCKS_RESET  _u(0x0)
#define PSM_WDSEL_CLOCKS_BITS   _u(0x00000004)
#define PSM_WDSEL_CLOCKS_MSB    _u(2)
#define PSM_WDSEL_CLOCKS_LSB    _u(2)
#define PSM_WDSEL_CLOCKS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_WDSEL_XOSC
// Description : None
#define PSM_WDSEL_XOSC_RESET  _u(0x0)
#define PSM_WDSEL_XOSC_BITS   _u(0x00000002)
#define PSM_WDSEL_XOSC_MSB    _u(1)
#define PSM_WDSEL_XOSC_LSB    _u(1)
#define PSM_WDSEL_XOSC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PSM_WDSEL_ROSC
// Description : None
#define PSM_WDSEL_ROSC_RESET  _u(0x0)
#define PSM_WDSEL_ROSC_BITS   _u(0x00000001)
#define PSM_WDSEL_ROSC_MSB    _u(0)
#define PSM_WDSEL_ROSC_LSB    _u(0)
#define PSM_WDSEL_ROSC_ACCESS "RW"
// =============================================================================
// Register    : PSM_DONE
// Description : Indicates the peripheral's registers are ready to access.
#define PSM_DONE_OFFSET _u(0x0000000c)
#define PSM_DONE_BITS   _u(0x0001ffff)
#define PSM_DONE_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : PSM_DONE_PROC1
// Description : None
#define PSM_DONE_PROC1_RESET  _u(0x0)
#define PSM_DONE_PROC1_BITS   _u(0x00010000)
#define PSM_DONE_PROC1_MSB    _u(16)
#define PSM_DONE_PROC1_LSB    _u(16)
#define PSM_DONE_PROC1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PSM_DONE_PROC0
// Description : None
#define PSM_DONE_PROC0_RESET  _u(0x0)
#define PSM_DONE_PROC0_BITS   _u(0x00008000)
#define PSM_DONE_PROC0_MSB    _u(15)
#define PSM_DONE_PROC0_LSB    _u(15)
#define PSM_DONE_PROC0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PSM_DONE_SIO
// Description : None
#define PSM_DONE_SIO_RESET  _u(0x0)
#define PSM_DONE_SIO_BITS   _u(0x00004000)
#define PSM_DONE_SIO_MSB    _u(14)
#define PSM_DONE_SIO_LSB    _u(14)
#define PSM_DONE_SIO_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PSM_DONE_VREG_AND_CHIP_RESET
// Description : None
#define PSM_DONE_VREG_AND_CHIP_RESET_RESET  _u(0x0)
#define PSM_DONE_VREG_AND_CHIP_RESET_BITS   _u(0x00002000)
#define PSM_DONE_VREG_AND_CHIP_RESET_MSB    _u(13)
#define PSM_DONE_VREG_AND_CHIP_RESET_LSB    _u(13)
#define PSM_DONE_VREG_AND_CHIP_RESET_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PSM_DONE_XIP
// Description : None
#define PSM_DONE_XIP_RESET  _u(0x0)
#define PSM_DONE_XIP_BITS   _u(0x00001000)
#define PSM_DONE_XIP_MSB    _u(12)
#define PSM_DONE_XIP_LSB    _u(12)
#define PSM_DONE_XIP_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PSM_DONE_SRAM5
// Description : None
#define PSM_DONE_SRAM5_RESET  _u(0x0)
#define PSM_DONE_SRAM5_BITS   _u(0x00000800)
#define PSM_DONE_SRAM5_MSB    _u(11)
#define PSM_DONE_SRAM5_LSB    _u(11)
#define PSM_DONE_SRAM5_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PSM_DONE_SRAM4
// Description : None
#define PSM_DONE_SRAM4_RESET  _u(0x0)
#define PSM_DONE_SRAM4_BITS   _u(0x00000400)
#define PSM_DONE_SRAM4_MSB    _u(10)
#define PSM_DONE_SRAM4_LSB    _u(10)
#define PSM_DONE_SRAM4_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PSM_DONE_SRAM3
// Description : None
#define PSM_DONE_SRAM3_RESET  _u(0x0)
#define PSM_DONE_SRAM3_BITS   _u(0x00000200)
#define PSM_DONE_SRAM3_MSB    _u(9)
#define PSM_DONE_SRAM3_LSB    _u(9)
#define PSM_DONE_SRAM3_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PSM_DONE_SRAM2
// Description : None
#define PSM_DONE_SRAM2_RESET  _u(0x0)
#define PSM_DONE_SRAM2_BITS   _u(0x00000100)
#define PSM_DONE_SRAM2_MSB    _u(8)
#define PSM_DONE_SRAM2_LSB    _u(8)
#define PSM_DONE_SRAM2_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PSM_DONE_SRAM1
// Description : None
#define PSM_DONE_SRAM1_RESET  _u(0x0)
#define PSM_DONE_SRAM1_BITS   _u(0x00000080)
#define PSM_DONE_SRAM1_MSB    _u(7)
#define PSM_DONE_SRAM1_LSB    _u(7)
#define PSM_DONE_SRAM1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PSM_DONE_SRAM0
// Description : None
#define PSM_DONE_SRAM0_RESET  _u(0x0)
#define PSM_DONE_SRAM0_BITS   _u(0x00000040)
#define PSM_DONE_SRAM0_MSB    _u(6)
#define PSM_DONE_SRAM0_LSB    _u(6)
#define PSM_DONE_SRAM0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PSM_DONE_ROM
// Description : None
#define PSM_DONE_ROM_RESET  _u(0x0)
#define PSM_DONE_ROM_BITS   _u(0x00000020)
#define PSM_DONE_ROM_MSB    _u(5)
#define PSM_DONE_ROM_LSB    _u(5)
#define PSM_DONE_ROM_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PSM_DONE_BUSFABRIC
// Description : None
#define PSM_DONE_BUSFABRIC_RESET  _u(0x0)
#define PSM_DONE_BUSFABRIC_BITS   _u(0x00000010)
#define PSM_DONE_BUSFABRIC_MSB    _u(4)
#define PSM_DONE_BUSFABRIC_LSB    _u(4)
#define PSM_DONE_BUSFABRIC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PSM_DONE_RESETS
// Description : None
#define PSM_DONE_RESETS_RESET  _u(0x0)
#define PSM_DONE_RESETS_BITS   _u(0x00000008)
#define PSM_DONE_RESETS_MSB    _u(3)
#define PSM_DONE_RESETS_LSB    _u(3)
#define PSM_DONE_RESETS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PSM_DONE_CLOCKS
// Description : None
#define PSM_DONE_CLOCKS_RESET  _u(0x0)
#define PSM_DONE_CLOCKS_BITS   _u(0x00000004)
#define PSM_DONE_CLOCKS_MSB    _u(2)
#define PSM_DONE_CLOCKS_LSB    _u(2)
#define PSM_DONE_CLOCKS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PSM_DONE_XOSC
// Description : None
#define PSM_DONE_XOSC_RESET  _u(0x0)
#define PSM_DONE_XOSC_BITS   _u(0x00000002)
#define PSM_DONE_XOSC_MSB    _u(1)
#define PSM_DONE_XOSC_LSB    _u(1)
#define PSM_DONE_XOSC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PSM_DONE_ROSC
// Description : None
#define PSM_DONE_ROSC_RESET  _u(0x0)
#define PSM_DONE_ROSC_BITS   _u(0x00000001)
#define PSM_DONE_ROSC_MSB    _u(0)
#define PSM_DONE_ROSC_LSB    _u(0)
#define PSM_DONE_ROSC_ACCESS "RO"
// =============================================================================
#endif // HARDWARE_REGS_PSM_DEFINED
