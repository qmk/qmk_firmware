/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : PADS_QSPI
// Version        : 1
// Bus type       : apb
// Description    : None
// =============================================================================
#ifndef HARDWARE_REGS_PADS_QSPI_DEFINED
#define HARDWARE_REGS_PADS_QSPI_DEFINED
// =============================================================================
// Register    : PADS_QSPI_VOLTAGE_SELECT
// Description : Voltage select. Per bank control
//               0x0 -> Set voltage to 3.3V (DVDD >= 2V5)
//               0x1 -> Set voltage to 1.8V (DVDD <= 1V8)
#define PADS_QSPI_VOLTAGE_SELECT_OFFSET    _u(0x00000000)
#define PADS_QSPI_VOLTAGE_SELECT_BITS      _u(0x00000001)
#define PADS_QSPI_VOLTAGE_SELECT_RESET     _u(0x00000000)
#define PADS_QSPI_VOLTAGE_SELECT_MSB       _u(0)
#define PADS_QSPI_VOLTAGE_SELECT_LSB       _u(0)
#define PADS_QSPI_VOLTAGE_SELECT_ACCESS    "RW"
#define PADS_QSPI_VOLTAGE_SELECT_VALUE_3V3 _u(0x0)
#define PADS_QSPI_VOLTAGE_SELECT_VALUE_1V8 _u(0x1)
// =============================================================================
// Register    : PADS_QSPI_GPIO_QSPI_SCLK
// Description : Pad control register
#define PADS_QSPI_GPIO_QSPI_SCLK_OFFSET _u(0x00000004)
#define PADS_QSPI_GPIO_QSPI_SCLK_BITS   _u(0x000000ff)
#define PADS_QSPI_GPIO_QSPI_SCLK_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SCLK_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_QSPI_GPIO_QSPI_SCLK_OD_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SCLK_OD_BITS   _u(0x00000080)
#define PADS_QSPI_GPIO_QSPI_SCLK_OD_MSB    _u(7)
#define PADS_QSPI_GPIO_QSPI_SCLK_OD_LSB    _u(7)
#define PADS_QSPI_GPIO_QSPI_SCLK_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SCLK_IE
// Description : Input enable
#define PADS_QSPI_GPIO_QSPI_SCLK_IE_RESET  _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SCLK_IE_BITS   _u(0x00000040)
#define PADS_QSPI_GPIO_QSPI_SCLK_IE_MSB    _u(6)
#define PADS_QSPI_GPIO_QSPI_SCLK_IE_LSB    _u(6)
#define PADS_QSPI_GPIO_QSPI_SCLK_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SCLK_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_QSPI_GPIO_QSPI_SCLK_DRIVE_RESET      _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SCLK_DRIVE_BITS       _u(0x00000030)
#define PADS_QSPI_GPIO_QSPI_SCLK_DRIVE_MSB        _u(5)
#define PADS_QSPI_GPIO_QSPI_SCLK_DRIVE_LSB        _u(4)
#define PADS_QSPI_GPIO_QSPI_SCLK_DRIVE_ACCESS     "RW"
#define PADS_QSPI_GPIO_QSPI_SCLK_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SCLK_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SCLK_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_QSPI_GPIO_QSPI_SCLK_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SCLK_PUE
// Description : Pull up enable
#define PADS_QSPI_GPIO_QSPI_SCLK_PUE_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SCLK_PUE_BITS   _u(0x00000008)
#define PADS_QSPI_GPIO_QSPI_SCLK_PUE_MSB    _u(3)
#define PADS_QSPI_GPIO_QSPI_SCLK_PUE_LSB    _u(3)
#define PADS_QSPI_GPIO_QSPI_SCLK_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SCLK_PDE
// Description : Pull down enable
#define PADS_QSPI_GPIO_QSPI_SCLK_PDE_RESET  _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SCLK_PDE_BITS   _u(0x00000004)
#define PADS_QSPI_GPIO_QSPI_SCLK_PDE_MSB    _u(2)
#define PADS_QSPI_GPIO_QSPI_SCLK_PDE_LSB    _u(2)
#define PADS_QSPI_GPIO_QSPI_SCLK_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SCLK_SCHMITT
// Description : Enable schmitt trigger
#define PADS_QSPI_GPIO_QSPI_SCLK_SCHMITT_RESET  _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SCLK_SCHMITT_BITS   _u(0x00000002)
#define PADS_QSPI_GPIO_QSPI_SCLK_SCHMITT_MSB    _u(1)
#define PADS_QSPI_GPIO_QSPI_SCLK_SCHMITT_LSB    _u(1)
#define PADS_QSPI_GPIO_QSPI_SCLK_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SCLK_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_QSPI_GPIO_QSPI_SCLK_SLEWFAST_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SCLK_SLEWFAST_BITS   _u(0x00000001)
#define PADS_QSPI_GPIO_QSPI_SCLK_SLEWFAST_MSB    _u(0)
#define PADS_QSPI_GPIO_QSPI_SCLK_SLEWFAST_LSB    _u(0)
#define PADS_QSPI_GPIO_QSPI_SCLK_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_QSPI_GPIO_QSPI_SD0
// Description : Pad control register
#define PADS_QSPI_GPIO_QSPI_SD0_OFFSET _u(0x00000008)
#define PADS_QSPI_GPIO_QSPI_SD0_BITS   _u(0x000000ff)
#define PADS_QSPI_GPIO_QSPI_SD0_RESET  _u(0x00000052)
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD0_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_QSPI_GPIO_QSPI_SD0_OD_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SD0_OD_BITS   _u(0x00000080)
#define PADS_QSPI_GPIO_QSPI_SD0_OD_MSB    _u(7)
#define PADS_QSPI_GPIO_QSPI_SD0_OD_LSB    _u(7)
#define PADS_QSPI_GPIO_QSPI_SD0_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD0_IE
// Description : Input enable
#define PADS_QSPI_GPIO_QSPI_SD0_IE_RESET  _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SD0_IE_BITS   _u(0x00000040)
#define PADS_QSPI_GPIO_QSPI_SD0_IE_MSB    _u(6)
#define PADS_QSPI_GPIO_QSPI_SD0_IE_LSB    _u(6)
#define PADS_QSPI_GPIO_QSPI_SD0_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD0_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_QSPI_GPIO_QSPI_SD0_DRIVE_RESET      _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SD0_DRIVE_BITS       _u(0x00000030)
#define PADS_QSPI_GPIO_QSPI_SD0_DRIVE_MSB        _u(5)
#define PADS_QSPI_GPIO_QSPI_SD0_DRIVE_LSB        _u(4)
#define PADS_QSPI_GPIO_QSPI_SD0_DRIVE_ACCESS     "RW"
#define PADS_QSPI_GPIO_QSPI_SD0_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SD0_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SD0_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_QSPI_GPIO_QSPI_SD0_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD0_PUE
// Description : Pull up enable
#define PADS_QSPI_GPIO_QSPI_SD0_PUE_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SD0_PUE_BITS   _u(0x00000008)
#define PADS_QSPI_GPIO_QSPI_SD0_PUE_MSB    _u(3)
#define PADS_QSPI_GPIO_QSPI_SD0_PUE_LSB    _u(3)
#define PADS_QSPI_GPIO_QSPI_SD0_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD0_PDE
// Description : Pull down enable
#define PADS_QSPI_GPIO_QSPI_SD0_PDE_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SD0_PDE_BITS   _u(0x00000004)
#define PADS_QSPI_GPIO_QSPI_SD0_PDE_MSB    _u(2)
#define PADS_QSPI_GPIO_QSPI_SD0_PDE_LSB    _u(2)
#define PADS_QSPI_GPIO_QSPI_SD0_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD0_SCHMITT
// Description : Enable schmitt trigger
#define PADS_QSPI_GPIO_QSPI_SD0_SCHMITT_RESET  _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SD0_SCHMITT_BITS   _u(0x00000002)
#define PADS_QSPI_GPIO_QSPI_SD0_SCHMITT_MSB    _u(1)
#define PADS_QSPI_GPIO_QSPI_SD0_SCHMITT_LSB    _u(1)
#define PADS_QSPI_GPIO_QSPI_SD0_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD0_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_QSPI_GPIO_QSPI_SD0_SLEWFAST_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SD0_SLEWFAST_BITS   _u(0x00000001)
#define PADS_QSPI_GPIO_QSPI_SD0_SLEWFAST_MSB    _u(0)
#define PADS_QSPI_GPIO_QSPI_SD0_SLEWFAST_LSB    _u(0)
#define PADS_QSPI_GPIO_QSPI_SD0_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_QSPI_GPIO_QSPI_SD1
// Description : Pad control register
#define PADS_QSPI_GPIO_QSPI_SD1_OFFSET _u(0x0000000c)
#define PADS_QSPI_GPIO_QSPI_SD1_BITS   _u(0x000000ff)
#define PADS_QSPI_GPIO_QSPI_SD1_RESET  _u(0x00000052)
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD1_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_QSPI_GPIO_QSPI_SD1_OD_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SD1_OD_BITS   _u(0x00000080)
#define PADS_QSPI_GPIO_QSPI_SD1_OD_MSB    _u(7)
#define PADS_QSPI_GPIO_QSPI_SD1_OD_LSB    _u(7)
#define PADS_QSPI_GPIO_QSPI_SD1_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD1_IE
// Description : Input enable
#define PADS_QSPI_GPIO_QSPI_SD1_IE_RESET  _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SD1_IE_BITS   _u(0x00000040)
#define PADS_QSPI_GPIO_QSPI_SD1_IE_MSB    _u(6)
#define PADS_QSPI_GPIO_QSPI_SD1_IE_LSB    _u(6)
#define PADS_QSPI_GPIO_QSPI_SD1_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD1_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_QSPI_GPIO_QSPI_SD1_DRIVE_RESET      _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SD1_DRIVE_BITS       _u(0x00000030)
#define PADS_QSPI_GPIO_QSPI_SD1_DRIVE_MSB        _u(5)
#define PADS_QSPI_GPIO_QSPI_SD1_DRIVE_LSB        _u(4)
#define PADS_QSPI_GPIO_QSPI_SD1_DRIVE_ACCESS     "RW"
#define PADS_QSPI_GPIO_QSPI_SD1_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SD1_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SD1_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_QSPI_GPIO_QSPI_SD1_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD1_PUE
// Description : Pull up enable
#define PADS_QSPI_GPIO_QSPI_SD1_PUE_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SD1_PUE_BITS   _u(0x00000008)
#define PADS_QSPI_GPIO_QSPI_SD1_PUE_MSB    _u(3)
#define PADS_QSPI_GPIO_QSPI_SD1_PUE_LSB    _u(3)
#define PADS_QSPI_GPIO_QSPI_SD1_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD1_PDE
// Description : Pull down enable
#define PADS_QSPI_GPIO_QSPI_SD1_PDE_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SD1_PDE_BITS   _u(0x00000004)
#define PADS_QSPI_GPIO_QSPI_SD1_PDE_MSB    _u(2)
#define PADS_QSPI_GPIO_QSPI_SD1_PDE_LSB    _u(2)
#define PADS_QSPI_GPIO_QSPI_SD1_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD1_SCHMITT
// Description : Enable schmitt trigger
#define PADS_QSPI_GPIO_QSPI_SD1_SCHMITT_RESET  _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SD1_SCHMITT_BITS   _u(0x00000002)
#define PADS_QSPI_GPIO_QSPI_SD1_SCHMITT_MSB    _u(1)
#define PADS_QSPI_GPIO_QSPI_SD1_SCHMITT_LSB    _u(1)
#define PADS_QSPI_GPIO_QSPI_SD1_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD1_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_QSPI_GPIO_QSPI_SD1_SLEWFAST_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SD1_SLEWFAST_BITS   _u(0x00000001)
#define PADS_QSPI_GPIO_QSPI_SD1_SLEWFAST_MSB    _u(0)
#define PADS_QSPI_GPIO_QSPI_SD1_SLEWFAST_LSB    _u(0)
#define PADS_QSPI_GPIO_QSPI_SD1_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_QSPI_GPIO_QSPI_SD2
// Description : Pad control register
#define PADS_QSPI_GPIO_QSPI_SD2_OFFSET _u(0x00000010)
#define PADS_QSPI_GPIO_QSPI_SD2_BITS   _u(0x000000ff)
#define PADS_QSPI_GPIO_QSPI_SD2_RESET  _u(0x00000052)
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD2_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_QSPI_GPIO_QSPI_SD2_OD_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SD2_OD_BITS   _u(0x00000080)
#define PADS_QSPI_GPIO_QSPI_SD2_OD_MSB    _u(7)
#define PADS_QSPI_GPIO_QSPI_SD2_OD_LSB    _u(7)
#define PADS_QSPI_GPIO_QSPI_SD2_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD2_IE
// Description : Input enable
#define PADS_QSPI_GPIO_QSPI_SD2_IE_RESET  _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SD2_IE_BITS   _u(0x00000040)
#define PADS_QSPI_GPIO_QSPI_SD2_IE_MSB    _u(6)
#define PADS_QSPI_GPIO_QSPI_SD2_IE_LSB    _u(6)
#define PADS_QSPI_GPIO_QSPI_SD2_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD2_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_QSPI_GPIO_QSPI_SD2_DRIVE_RESET      _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SD2_DRIVE_BITS       _u(0x00000030)
#define PADS_QSPI_GPIO_QSPI_SD2_DRIVE_MSB        _u(5)
#define PADS_QSPI_GPIO_QSPI_SD2_DRIVE_LSB        _u(4)
#define PADS_QSPI_GPIO_QSPI_SD2_DRIVE_ACCESS     "RW"
#define PADS_QSPI_GPIO_QSPI_SD2_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SD2_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SD2_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_QSPI_GPIO_QSPI_SD2_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD2_PUE
// Description : Pull up enable
#define PADS_QSPI_GPIO_QSPI_SD2_PUE_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SD2_PUE_BITS   _u(0x00000008)
#define PADS_QSPI_GPIO_QSPI_SD2_PUE_MSB    _u(3)
#define PADS_QSPI_GPIO_QSPI_SD2_PUE_LSB    _u(3)
#define PADS_QSPI_GPIO_QSPI_SD2_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD2_PDE
// Description : Pull down enable
#define PADS_QSPI_GPIO_QSPI_SD2_PDE_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SD2_PDE_BITS   _u(0x00000004)
#define PADS_QSPI_GPIO_QSPI_SD2_PDE_MSB    _u(2)
#define PADS_QSPI_GPIO_QSPI_SD2_PDE_LSB    _u(2)
#define PADS_QSPI_GPIO_QSPI_SD2_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD2_SCHMITT
// Description : Enable schmitt trigger
#define PADS_QSPI_GPIO_QSPI_SD2_SCHMITT_RESET  _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SD2_SCHMITT_BITS   _u(0x00000002)
#define PADS_QSPI_GPIO_QSPI_SD2_SCHMITT_MSB    _u(1)
#define PADS_QSPI_GPIO_QSPI_SD2_SCHMITT_LSB    _u(1)
#define PADS_QSPI_GPIO_QSPI_SD2_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD2_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_QSPI_GPIO_QSPI_SD2_SLEWFAST_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SD2_SLEWFAST_BITS   _u(0x00000001)
#define PADS_QSPI_GPIO_QSPI_SD2_SLEWFAST_MSB    _u(0)
#define PADS_QSPI_GPIO_QSPI_SD2_SLEWFAST_LSB    _u(0)
#define PADS_QSPI_GPIO_QSPI_SD2_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_QSPI_GPIO_QSPI_SD3
// Description : Pad control register
#define PADS_QSPI_GPIO_QSPI_SD3_OFFSET _u(0x00000014)
#define PADS_QSPI_GPIO_QSPI_SD3_BITS   _u(0x000000ff)
#define PADS_QSPI_GPIO_QSPI_SD3_RESET  _u(0x00000052)
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD3_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_QSPI_GPIO_QSPI_SD3_OD_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SD3_OD_BITS   _u(0x00000080)
#define PADS_QSPI_GPIO_QSPI_SD3_OD_MSB    _u(7)
#define PADS_QSPI_GPIO_QSPI_SD3_OD_LSB    _u(7)
#define PADS_QSPI_GPIO_QSPI_SD3_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD3_IE
// Description : Input enable
#define PADS_QSPI_GPIO_QSPI_SD3_IE_RESET  _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SD3_IE_BITS   _u(0x00000040)
#define PADS_QSPI_GPIO_QSPI_SD3_IE_MSB    _u(6)
#define PADS_QSPI_GPIO_QSPI_SD3_IE_LSB    _u(6)
#define PADS_QSPI_GPIO_QSPI_SD3_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD3_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_QSPI_GPIO_QSPI_SD3_DRIVE_RESET      _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SD3_DRIVE_BITS       _u(0x00000030)
#define PADS_QSPI_GPIO_QSPI_SD3_DRIVE_MSB        _u(5)
#define PADS_QSPI_GPIO_QSPI_SD3_DRIVE_LSB        _u(4)
#define PADS_QSPI_GPIO_QSPI_SD3_DRIVE_ACCESS     "RW"
#define PADS_QSPI_GPIO_QSPI_SD3_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SD3_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SD3_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_QSPI_GPIO_QSPI_SD3_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD3_PUE
// Description : Pull up enable
#define PADS_QSPI_GPIO_QSPI_SD3_PUE_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SD3_PUE_BITS   _u(0x00000008)
#define PADS_QSPI_GPIO_QSPI_SD3_PUE_MSB    _u(3)
#define PADS_QSPI_GPIO_QSPI_SD3_PUE_LSB    _u(3)
#define PADS_QSPI_GPIO_QSPI_SD3_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD3_PDE
// Description : Pull down enable
#define PADS_QSPI_GPIO_QSPI_SD3_PDE_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SD3_PDE_BITS   _u(0x00000004)
#define PADS_QSPI_GPIO_QSPI_SD3_PDE_MSB    _u(2)
#define PADS_QSPI_GPIO_QSPI_SD3_PDE_LSB    _u(2)
#define PADS_QSPI_GPIO_QSPI_SD3_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD3_SCHMITT
// Description : Enable schmitt trigger
#define PADS_QSPI_GPIO_QSPI_SD3_SCHMITT_RESET  _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SD3_SCHMITT_BITS   _u(0x00000002)
#define PADS_QSPI_GPIO_QSPI_SD3_SCHMITT_MSB    _u(1)
#define PADS_QSPI_GPIO_QSPI_SD3_SCHMITT_LSB    _u(1)
#define PADS_QSPI_GPIO_QSPI_SD3_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SD3_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_QSPI_GPIO_QSPI_SD3_SLEWFAST_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SD3_SLEWFAST_BITS   _u(0x00000001)
#define PADS_QSPI_GPIO_QSPI_SD3_SLEWFAST_MSB    _u(0)
#define PADS_QSPI_GPIO_QSPI_SD3_SLEWFAST_LSB    _u(0)
#define PADS_QSPI_GPIO_QSPI_SD3_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_QSPI_GPIO_QSPI_SS
// Description : Pad control register
#define PADS_QSPI_GPIO_QSPI_SS_OFFSET _u(0x00000018)
#define PADS_QSPI_GPIO_QSPI_SS_BITS   _u(0x000000ff)
#define PADS_QSPI_GPIO_QSPI_SS_RESET  _u(0x0000005a)
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SS_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_QSPI_GPIO_QSPI_SS_OD_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SS_OD_BITS   _u(0x00000080)
#define PADS_QSPI_GPIO_QSPI_SS_OD_MSB    _u(7)
#define PADS_QSPI_GPIO_QSPI_SS_OD_LSB    _u(7)
#define PADS_QSPI_GPIO_QSPI_SS_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SS_IE
// Description : Input enable
#define PADS_QSPI_GPIO_QSPI_SS_IE_RESET  _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SS_IE_BITS   _u(0x00000040)
#define PADS_QSPI_GPIO_QSPI_SS_IE_MSB    _u(6)
#define PADS_QSPI_GPIO_QSPI_SS_IE_LSB    _u(6)
#define PADS_QSPI_GPIO_QSPI_SS_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SS_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_QSPI_GPIO_QSPI_SS_DRIVE_RESET      _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SS_DRIVE_BITS       _u(0x00000030)
#define PADS_QSPI_GPIO_QSPI_SS_DRIVE_MSB        _u(5)
#define PADS_QSPI_GPIO_QSPI_SS_DRIVE_LSB        _u(4)
#define PADS_QSPI_GPIO_QSPI_SS_DRIVE_ACCESS     "RW"
#define PADS_QSPI_GPIO_QSPI_SS_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SS_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SS_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_QSPI_GPIO_QSPI_SS_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SS_PUE
// Description : Pull up enable
#define PADS_QSPI_GPIO_QSPI_SS_PUE_RESET  _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SS_PUE_BITS   _u(0x00000008)
#define PADS_QSPI_GPIO_QSPI_SS_PUE_MSB    _u(3)
#define PADS_QSPI_GPIO_QSPI_SS_PUE_LSB    _u(3)
#define PADS_QSPI_GPIO_QSPI_SS_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SS_PDE
// Description : Pull down enable
#define PADS_QSPI_GPIO_QSPI_SS_PDE_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SS_PDE_BITS   _u(0x00000004)
#define PADS_QSPI_GPIO_QSPI_SS_PDE_MSB    _u(2)
#define PADS_QSPI_GPIO_QSPI_SS_PDE_LSB    _u(2)
#define PADS_QSPI_GPIO_QSPI_SS_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SS_SCHMITT
// Description : Enable schmitt trigger
#define PADS_QSPI_GPIO_QSPI_SS_SCHMITT_RESET  _u(0x1)
#define PADS_QSPI_GPIO_QSPI_SS_SCHMITT_BITS   _u(0x00000002)
#define PADS_QSPI_GPIO_QSPI_SS_SCHMITT_MSB    _u(1)
#define PADS_QSPI_GPIO_QSPI_SS_SCHMITT_LSB    _u(1)
#define PADS_QSPI_GPIO_QSPI_SS_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_QSPI_GPIO_QSPI_SS_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_QSPI_GPIO_QSPI_SS_SLEWFAST_RESET  _u(0x0)
#define PADS_QSPI_GPIO_QSPI_SS_SLEWFAST_BITS   _u(0x00000001)
#define PADS_QSPI_GPIO_QSPI_SS_SLEWFAST_MSB    _u(0)
#define PADS_QSPI_GPIO_QSPI_SS_SLEWFAST_LSB    _u(0)
#define PADS_QSPI_GPIO_QSPI_SS_SLEWFAST_ACCESS "RW"
// =============================================================================
#endif // HARDWARE_REGS_PADS_QSPI_DEFINED
