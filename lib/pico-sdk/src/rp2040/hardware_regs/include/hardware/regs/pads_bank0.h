/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : PADS_BANK0
// Version        : 1
// Bus type       : apb
// Description    : None
// =============================================================================
#ifndef HARDWARE_REGS_PADS_BANK0_DEFINED
#define HARDWARE_REGS_PADS_BANK0_DEFINED
// =============================================================================
// Register    : PADS_BANK0_VOLTAGE_SELECT
// Description : Voltage select. Per bank control
//               0x0 -> Set voltage to 3.3V (DVDD >= 2V5)
//               0x1 -> Set voltage to 1.8V (DVDD <= 1V8)
#define PADS_BANK0_VOLTAGE_SELECT_OFFSET    _u(0x00000000)
#define PADS_BANK0_VOLTAGE_SELECT_BITS      _u(0x00000001)
#define PADS_BANK0_VOLTAGE_SELECT_RESET     _u(0x00000000)
#define PADS_BANK0_VOLTAGE_SELECT_MSB       _u(0)
#define PADS_BANK0_VOLTAGE_SELECT_LSB       _u(0)
#define PADS_BANK0_VOLTAGE_SELECT_ACCESS    "RW"
#define PADS_BANK0_VOLTAGE_SELECT_VALUE_3V3 _u(0x0)
#define PADS_BANK0_VOLTAGE_SELECT_VALUE_1V8 _u(0x1)
// =============================================================================
// Register    : PADS_BANK0_GPIO0
// Description : Pad control register
#define PADS_BANK0_GPIO0_OFFSET _u(0x00000004)
#define PADS_BANK0_GPIO0_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO0_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO0_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO0_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO0_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO0_OD_MSB    _u(7)
#define PADS_BANK0_GPIO0_OD_LSB    _u(7)
#define PADS_BANK0_GPIO0_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO0_IE
// Description : Input enable
#define PADS_BANK0_GPIO0_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO0_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO0_IE_MSB    _u(6)
#define PADS_BANK0_GPIO0_IE_LSB    _u(6)
#define PADS_BANK0_GPIO0_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO0_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO0_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO0_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO0_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO0_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO0_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO0_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO0_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO0_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO0_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO0_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO0_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO0_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO0_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO0_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO0_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO0_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO0_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO0_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO0_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO0_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO0_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO0_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO0_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO0_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO0_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO0_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO0_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO0_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO0_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO0_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO0_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO0_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO0_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO1
// Description : Pad control register
#define PADS_BANK0_GPIO1_OFFSET _u(0x00000008)
#define PADS_BANK0_GPIO1_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO1_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO1_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO1_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO1_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO1_OD_MSB    _u(7)
#define PADS_BANK0_GPIO1_OD_LSB    _u(7)
#define PADS_BANK0_GPIO1_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO1_IE
// Description : Input enable
#define PADS_BANK0_GPIO1_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO1_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO1_IE_MSB    _u(6)
#define PADS_BANK0_GPIO1_IE_LSB    _u(6)
#define PADS_BANK0_GPIO1_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO1_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO1_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO1_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO1_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO1_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO1_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO1_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO1_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO1_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO1_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO1_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO1_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO1_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO1_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO1_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO1_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO1_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO1_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO1_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO1_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO1_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO1_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO1_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO1_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO1_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO1_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO1_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO1_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO1_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO1_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO1_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO1_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO1_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO1_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO2
// Description : Pad control register
#define PADS_BANK0_GPIO2_OFFSET _u(0x0000000c)
#define PADS_BANK0_GPIO2_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO2_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO2_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO2_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO2_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO2_OD_MSB    _u(7)
#define PADS_BANK0_GPIO2_OD_LSB    _u(7)
#define PADS_BANK0_GPIO2_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO2_IE
// Description : Input enable
#define PADS_BANK0_GPIO2_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO2_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO2_IE_MSB    _u(6)
#define PADS_BANK0_GPIO2_IE_LSB    _u(6)
#define PADS_BANK0_GPIO2_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO2_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO2_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO2_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO2_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO2_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO2_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO2_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO2_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO2_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO2_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO2_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO2_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO2_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO2_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO2_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO2_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO2_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO2_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO2_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO2_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO2_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO2_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO2_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO2_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO2_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO2_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO2_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO2_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO2_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO2_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO2_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO2_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO2_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO2_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO3
// Description : Pad control register
#define PADS_BANK0_GPIO3_OFFSET _u(0x00000010)
#define PADS_BANK0_GPIO3_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO3_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO3_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO3_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO3_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO3_OD_MSB    _u(7)
#define PADS_BANK0_GPIO3_OD_LSB    _u(7)
#define PADS_BANK0_GPIO3_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO3_IE
// Description : Input enable
#define PADS_BANK0_GPIO3_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO3_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO3_IE_MSB    _u(6)
#define PADS_BANK0_GPIO3_IE_LSB    _u(6)
#define PADS_BANK0_GPIO3_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO3_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO3_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO3_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO3_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO3_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO3_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO3_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO3_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO3_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO3_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO3_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO3_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO3_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO3_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO3_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO3_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO3_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO3_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO3_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO3_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO3_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO3_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO3_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO3_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO3_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO3_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO3_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO3_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO3_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO3_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO3_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO3_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO3_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO3_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO4
// Description : Pad control register
#define PADS_BANK0_GPIO4_OFFSET _u(0x00000014)
#define PADS_BANK0_GPIO4_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO4_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO4_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO4_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO4_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO4_OD_MSB    _u(7)
#define PADS_BANK0_GPIO4_OD_LSB    _u(7)
#define PADS_BANK0_GPIO4_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO4_IE
// Description : Input enable
#define PADS_BANK0_GPIO4_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO4_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO4_IE_MSB    _u(6)
#define PADS_BANK0_GPIO4_IE_LSB    _u(6)
#define PADS_BANK0_GPIO4_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO4_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO4_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO4_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO4_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO4_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO4_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO4_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO4_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO4_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO4_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO4_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO4_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO4_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO4_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO4_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO4_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO4_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO4_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO4_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO4_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO4_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO4_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO4_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO4_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO4_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO4_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO4_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO4_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO4_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO4_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO4_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO4_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO4_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO4_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO5
// Description : Pad control register
#define PADS_BANK0_GPIO5_OFFSET _u(0x00000018)
#define PADS_BANK0_GPIO5_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO5_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO5_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO5_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO5_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO5_OD_MSB    _u(7)
#define PADS_BANK0_GPIO5_OD_LSB    _u(7)
#define PADS_BANK0_GPIO5_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO5_IE
// Description : Input enable
#define PADS_BANK0_GPIO5_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO5_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO5_IE_MSB    _u(6)
#define PADS_BANK0_GPIO5_IE_LSB    _u(6)
#define PADS_BANK0_GPIO5_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO5_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO5_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO5_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO5_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO5_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO5_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO5_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO5_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO5_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO5_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO5_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO5_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO5_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO5_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO5_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO5_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO5_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO5_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO5_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO5_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO5_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO5_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO5_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO5_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO5_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO5_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO5_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO5_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO5_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO5_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO5_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO5_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO5_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO5_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO6
// Description : Pad control register
#define PADS_BANK0_GPIO6_OFFSET _u(0x0000001c)
#define PADS_BANK0_GPIO6_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO6_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO6_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO6_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO6_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO6_OD_MSB    _u(7)
#define PADS_BANK0_GPIO6_OD_LSB    _u(7)
#define PADS_BANK0_GPIO6_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO6_IE
// Description : Input enable
#define PADS_BANK0_GPIO6_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO6_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO6_IE_MSB    _u(6)
#define PADS_BANK0_GPIO6_IE_LSB    _u(6)
#define PADS_BANK0_GPIO6_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO6_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO6_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO6_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO6_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO6_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO6_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO6_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO6_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO6_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO6_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO6_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO6_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO6_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO6_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO6_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO6_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO6_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO6_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO6_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO6_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO6_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO6_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO6_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO6_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO6_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO6_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO6_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO6_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO6_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO6_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO6_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO6_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO6_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO6_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO7
// Description : Pad control register
#define PADS_BANK0_GPIO7_OFFSET _u(0x00000020)
#define PADS_BANK0_GPIO7_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO7_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO7_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO7_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO7_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO7_OD_MSB    _u(7)
#define PADS_BANK0_GPIO7_OD_LSB    _u(7)
#define PADS_BANK0_GPIO7_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO7_IE
// Description : Input enable
#define PADS_BANK0_GPIO7_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO7_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO7_IE_MSB    _u(6)
#define PADS_BANK0_GPIO7_IE_LSB    _u(6)
#define PADS_BANK0_GPIO7_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO7_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO7_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO7_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO7_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO7_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO7_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO7_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO7_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO7_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO7_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO7_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO7_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO7_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO7_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO7_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO7_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO7_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO7_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO7_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO7_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO7_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO7_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO7_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO7_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO7_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO7_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO7_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO7_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO7_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO7_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO7_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO7_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO7_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO7_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO8
// Description : Pad control register
#define PADS_BANK0_GPIO8_OFFSET _u(0x00000024)
#define PADS_BANK0_GPIO8_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO8_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO8_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO8_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO8_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO8_OD_MSB    _u(7)
#define PADS_BANK0_GPIO8_OD_LSB    _u(7)
#define PADS_BANK0_GPIO8_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO8_IE
// Description : Input enable
#define PADS_BANK0_GPIO8_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO8_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO8_IE_MSB    _u(6)
#define PADS_BANK0_GPIO8_IE_LSB    _u(6)
#define PADS_BANK0_GPIO8_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO8_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO8_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO8_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO8_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO8_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO8_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO8_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO8_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO8_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO8_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO8_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO8_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO8_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO8_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO8_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO8_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO8_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO8_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO8_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO8_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO8_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO8_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO8_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO8_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO8_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO8_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO8_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO8_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO8_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO8_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO8_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO8_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO8_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO8_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO9
// Description : Pad control register
#define PADS_BANK0_GPIO9_OFFSET _u(0x00000028)
#define PADS_BANK0_GPIO9_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO9_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO9_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO9_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO9_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO9_OD_MSB    _u(7)
#define PADS_BANK0_GPIO9_OD_LSB    _u(7)
#define PADS_BANK0_GPIO9_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO9_IE
// Description : Input enable
#define PADS_BANK0_GPIO9_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO9_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO9_IE_MSB    _u(6)
#define PADS_BANK0_GPIO9_IE_LSB    _u(6)
#define PADS_BANK0_GPIO9_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO9_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO9_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO9_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO9_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO9_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO9_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO9_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO9_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO9_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO9_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO9_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO9_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO9_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO9_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO9_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO9_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO9_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO9_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO9_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO9_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO9_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO9_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO9_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO9_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO9_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO9_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO9_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO9_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO9_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO9_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO9_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO9_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO9_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO9_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO10
// Description : Pad control register
#define PADS_BANK0_GPIO10_OFFSET _u(0x0000002c)
#define PADS_BANK0_GPIO10_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO10_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO10_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO10_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO10_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO10_OD_MSB    _u(7)
#define PADS_BANK0_GPIO10_OD_LSB    _u(7)
#define PADS_BANK0_GPIO10_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO10_IE
// Description : Input enable
#define PADS_BANK0_GPIO10_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO10_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO10_IE_MSB    _u(6)
#define PADS_BANK0_GPIO10_IE_LSB    _u(6)
#define PADS_BANK0_GPIO10_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO10_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO10_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO10_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO10_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO10_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO10_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO10_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO10_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO10_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO10_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO10_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO10_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO10_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO10_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO10_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO10_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO10_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO10_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO10_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO10_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO10_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO10_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO10_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO10_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO10_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO10_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO10_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO10_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO10_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO10_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO10_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO10_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO10_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO10_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO11
// Description : Pad control register
#define PADS_BANK0_GPIO11_OFFSET _u(0x00000030)
#define PADS_BANK0_GPIO11_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO11_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO11_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO11_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO11_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO11_OD_MSB    _u(7)
#define PADS_BANK0_GPIO11_OD_LSB    _u(7)
#define PADS_BANK0_GPIO11_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO11_IE
// Description : Input enable
#define PADS_BANK0_GPIO11_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO11_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO11_IE_MSB    _u(6)
#define PADS_BANK0_GPIO11_IE_LSB    _u(6)
#define PADS_BANK0_GPIO11_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO11_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO11_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO11_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO11_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO11_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO11_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO11_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO11_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO11_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO11_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO11_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO11_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO11_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO11_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO11_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO11_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO11_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO11_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO11_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO11_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO11_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO11_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO11_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO11_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO11_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO11_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO11_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO11_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO11_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO11_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO11_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO11_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO11_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO11_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO12
// Description : Pad control register
#define PADS_BANK0_GPIO12_OFFSET _u(0x00000034)
#define PADS_BANK0_GPIO12_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO12_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO12_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO12_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO12_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO12_OD_MSB    _u(7)
#define PADS_BANK0_GPIO12_OD_LSB    _u(7)
#define PADS_BANK0_GPIO12_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO12_IE
// Description : Input enable
#define PADS_BANK0_GPIO12_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO12_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO12_IE_MSB    _u(6)
#define PADS_BANK0_GPIO12_IE_LSB    _u(6)
#define PADS_BANK0_GPIO12_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO12_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO12_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO12_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO12_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO12_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO12_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO12_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO12_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO12_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO12_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO12_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO12_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO12_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO12_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO12_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO12_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO12_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO12_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO12_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO12_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO12_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO12_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO12_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO12_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO12_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO12_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO12_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO12_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO12_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO12_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO12_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO12_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO12_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO12_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO13
// Description : Pad control register
#define PADS_BANK0_GPIO13_OFFSET _u(0x00000038)
#define PADS_BANK0_GPIO13_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO13_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO13_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO13_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO13_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO13_OD_MSB    _u(7)
#define PADS_BANK0_GPIO13_OD_LSB    _u(7)
#define PADS_BANK0_GPIO13_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO13_IE
// Description : Input enable
#define PADS_BANK0_GPIO13_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO13_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO13_IE_MSB    _u(6)
#define PADS_BANK0_GPIO13_IE_LSB    _u(6)
#define PADS_BANK0_GPIO13_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO13_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO13_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO13_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO13_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO13_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO13_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO13_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO13_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO13_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO13_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO13_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO13_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO13_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO13_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO13_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO13_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO13_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO13_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO13_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO13_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO13_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO13_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO13_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO13_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO13_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO13_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO13_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO13_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO13_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO13_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO13_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO13_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO13_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO13_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO14
// Description : Pad control register
#define PADS_BANK0_GPIO14_OFFSET _u(0x0000003c)
#define PADS_BANK0_GPIO14_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO14_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO14_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO14_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO14_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO14_OD_MSB    _u(7)
#define PADS_BANK0_GPIO14_OD_LSB    _u(7)
#define PADS_BANK0_GPIO14_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO14_IE
// Description : Input enable
#define PADS_BANK0_GPIO14_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO14_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO14_IE_MSB    _u(6)
#define PADS_BANK0_GPIO14_IE_LSB    _u(6)
#define PADS_BANK0_GPIO14_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO14_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO14_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO14_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO14_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO14_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO14_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO14_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO14_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO14_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO14_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO14_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO14_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO14_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO14_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO14_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO14_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO14_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO14_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO14_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO14_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO14_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO14_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO14_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO14_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO14_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO14_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO14_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO14_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO14_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO14_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO14_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO14_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO14_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO14_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO15
// Description : Pad control register
#define PADS_BANK0_GPIO15_OFFSET _u(0x00000040)
#define PADS_BANK0_GPIO15_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO15_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO15_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO15_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO15_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO15_OD_MSB    _u(7)
#define PADS_BANK0_GPIO15_OD_LSB    _u(7)
#define PADS_BANK0_GPIO15_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO15_IE
// Description : Input enable
#define PADS_BANK0_GPIO15_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO15_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO15_IE_MSB    _u(6)
#define PADS_BANK0_GPIO15_IE_LSB    _u(6)
#define PADS_BANK0_GPIO15_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO15_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO15_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO15_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO15_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO15_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO15_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO15_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO15_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO15_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO15_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO15_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO15_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO15_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO15_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO15_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO15_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO15_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO15_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO15_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO15_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO15_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO15_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO15_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO15_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO15_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO15_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO15_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO15_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO15_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO15_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO15_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO15_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO15_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO15_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO16
// Description : Pad control register
#define PADS_BANK0_GPIO16_OFFSET _u(0x00000044)
#define PADS_BANK0_GPIO16_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO16_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO16_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO16_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO16_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO16_OD_MSB    _u(7)
#define PADS_BANK0_GPIO16_OD_LSB    _u(7)
#define PADS_BANK0_GPIO16_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO16_IE
// Description : Input enable
#define PADS_BANK0_GPIO16_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO16_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO16_IE_MSB    _u(6)
#define PADS_BANK0_GPIO16_IE_LSB    _u(6)
#define PADS_BANK0_GPIO16_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO16_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO16_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO16_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO16_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO16_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO16_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO16_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO16_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO16_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO16_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO16_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO16_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO16_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO16_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO16_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO16_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO16_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO16_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO16_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO16_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO16_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO16_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO16_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO16_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO16_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO16_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO16_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO16_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO16_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO16_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO16_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO16_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO16_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO16_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO17
// Description : Pad control register
#define PADS_BANK0_GPIO17_OFFSET _u(0x00000048)
#define PADS_BANK0_GPIO17_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO17_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO17_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO17_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO17_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO17_OD_MSB    _u(7)
#define PADS_BANK0_GPIO17_OD_LSB    _u(7)
#define PADS_BANK0_GPIO17_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO17_IE
// Description : Input enable
#define PADS_BANK0_GPIO17_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO17_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO17_IE_MSB    _u(6)
#define PADS_BANK0_GPIO17_IE_LSB    _u(6)
#define PADS_BANK0_GPIO17_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO17_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO17_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO17_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO17_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO17_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO17_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO17_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO17_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO17_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO17_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO17_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO17_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO17_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO17_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO17_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO17_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO17_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO17_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO17_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO17_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO17_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO17_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO17_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO17_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO17_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO17_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO17_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO17_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO17_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO17_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO17_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO17_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO17_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO17_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO18
// Description : Pad control register
#define PADS_BANK0_GPIO18_OFFSET _u(0x0000004c)
#define PADS_BANK0_GPIO18_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO18_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO18_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO18_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO18_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO18_OD_MSB    _u(7)
#define PADS_BANK0_GPIO18_OD_LSB    _u(7)
#define PADS_BANK0_GPIO18_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO18_IE
// Description : Input enable
#define PADS_BANK0_GPIO18_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO18_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO18_IE_MSB    _u(6)
#define PADS_BANK0_GPIO18_IE_LSB    _u(6)
#define PADS_BANK0_GPIO18_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO18_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO18_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO18_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO18_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO18_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO18_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO18_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO18_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO18_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO18_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO18_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO18_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO18_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO18_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO18_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO18_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO18_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO18_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO18_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO18_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO18_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO18_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO18_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO18_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO18_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO18_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO18_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO18_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO18_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO18_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO18_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO18_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO18_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO18_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO19
// Description : Pad control register
#define PADS_BANK0_GPIO19_OFFSET _u(0x00000050)
#define PADS_BANK0_GPIO19_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO19_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO19_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO19_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO19_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO19_OD_MSB    _u(7)
#define PADS_BANK0_GPIO19_OD_LSB    _u(7)
#define PADS_BANK0_GPIO19_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO19_IE
// Description : Input enable
#define PADS_BANK0_GPIO19_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO19_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO19_IE_MSB    _u(6)
#define PADS_BANK0_GPIO19_IE_LSB    _u(6)
#define PADS_BANK0_GPIO19_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO19_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO19_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO19_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO19_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO19_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO19_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO19_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO19_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO19_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO19_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO19_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO19_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO19_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO19_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO19_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO19_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO19_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO19_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO19_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO19_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO19_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO19_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO19_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO19_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO19_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO19_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO19_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO19_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO19_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO19_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO19_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO19_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO19_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO19_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO20
// Description : Pad control register
#define PADS_BANK0_GPIO20_OFFSET _u(0x00000054)
#define PADS_BANK0_GPIO20_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO20_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO20_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO20_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO20_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO20_OD_MSB    _u(7)
#define PADS_BANK0_GPIO20_OD_LSB    _u(7)
#define PADS_BANK0_GPIO20_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO20_IE
// Description : Input enable
#define PADS_BANK0_GPIO20_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO20_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO20_IE_MSB    _u(6)
#define PADS_BANK0_GPIO20_IE_LSB    _u(6)
#define PADS_BANK0_GPIO20_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO20_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO20_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO20_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO20_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO20_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO20_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO20_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO20_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO20_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO20_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO20_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO20_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO20_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO20_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO20_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO20_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO20_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO20_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO20_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO20_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO20_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO20_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO20_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO20_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO20_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO20_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO20_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO20_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO20_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO20_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO20_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO20_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO20_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO20_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO21
// Description : Pad control register
#define PADS_BANK0_GPIO21_OFFSET _u(0x00000058)
#define PADS_BANK0_GPIO21_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO21_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO21_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO21_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO21_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO21_OD_MSB    _u(7)
#define PADS_BANK0_GPIO21_OD_LSB    _u(7)
#define PADS_BANK0_GPIO21_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO21_IE
// Description : Input enable
#define PADS_BANK0_GPIO21_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO21_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO21_IE_MSB    _u(6)
#define PADS_BANK0_GPIO21_IE_LSB    _u(6)
#define PADS_BANK0_GPIO21_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO21_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO21_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO21_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO21_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO21_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO21_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO21_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO21_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO21_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO21_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO21_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO21_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO21_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO21_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO21_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO21_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO21_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO21_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO21_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO21_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO21_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO21_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO21_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO21_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO21_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO21_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO21_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO21_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO21_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO21_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO21_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO21_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO21_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO21_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO22
// Description : Pad control register
#define PADS_BANK0_GPIO22_OFFSET _u(0x0000005c)
#define PADS_BANK0_GPIO22_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO22_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO22_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO22_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO22_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO22_OD_MSB    _u(7)
#define PADS_BANK0_GPIO22_OD_LSB    _u(7)
#define PADS_BANK0_GPIO22_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO22_IE
// Description : Input enable
#define PADS_BANK0_GPIO22_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO22_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO22_IE_MSB    _u(6)
#define PADS_BANK0_GPIO22_IE_LSB    _u(6)
#define PADS_BANK0_GPIO22_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO22_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO22_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO22_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO22_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO22_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO22_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO22_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO22_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO22_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO22_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO22_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO22_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO22_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO22_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO22_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO22_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO22_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO22_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO22_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO22_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO22_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO22_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO22_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO22_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO22_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO22_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO22_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO22_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO22_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO22_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO22_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO22_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO22_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO22_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO23
// Description : Pad control register
#define PADS_BANK0_GPIO23_OFFSET _u(0x00000060)
#define PADS_BANK0_GPIO23_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO23_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO23_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO23_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO23_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO23_OD_MSB    _u(7)
#define PADS_BANK0_GPIO23_OD_LSB    _u(7)
#define PADS_BANK0_GPIO23_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO23_IE
// Description : Input enable
#define PADS_BANK0_GPIO23_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO23_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO23_IE_MSB    _u(6)
#define PADS_BANK0_GPIO23_IE_LSB    _u(6)
#define PADS_BANK0_GPIO23_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO23_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO23_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO23_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO23_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO23_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO23_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO23_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO23_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO23_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO23_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO23_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO23_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO23_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO23_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO23_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO23_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO23_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO23_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO23_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO23_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO23_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO23_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO23_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO23_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO23_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO23_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO23_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO23_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO23_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO23_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO23_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO23_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO23_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO23_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO24
// Description : Pad control register
#define PADS_BANK0_GPIO24_OFFSET _u(0x00000064)
#define PADS_BANK0_GPIO24_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO24_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO24_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO24_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO24_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO24_OD_MSB    _u(7)
#define PADS_BANK0_GPIO24_OD_LSB    _u(7)
#define PADS_BANK0_GPIO24_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO24_IE
// Description : Input enable
#define PADS_BANK0_GPIO24_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO24_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO24_IE_MSB    _u(6)
#define PADS_BANK0_GPIO24_IE_LSB    _u(6)
#define PADS_BANK0_GPIO24_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO24_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO24_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO24_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO24_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO24_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO24_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO24_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO24_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO24_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO24_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO24_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO24_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO24_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO24_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO24_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO24_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO24_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO24_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO24_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO24_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO24_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO24_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO24_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO24_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO24_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO24_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO24_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO24_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO24_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO24_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO24_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO24_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO24_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO24_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO25
// Description : Pad control register
#define PADS_BANK0_GPIO25_OFFSET _u(0x00000068)
#define PADS_BANK0_GPIO25_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO25_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO25_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO25_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO25_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO25_OD_MSB    _u(7)
#define PADS_BANK0_GPIO25_OD_LSB    _u(7)
#define PADS_BANK0_GPIO25_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO25_IE
// Description : Input enable
#define PADS_BANK0_GPIO25_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO25_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO25_IE_MSB    _u(6)
#define PADS_BANK0_GPIO25_IE_LSB    _u(6)
#define PADS_BANK0_GPIO25_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO25_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO25_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO25_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO25_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO25_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO25_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO25_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO25_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO25_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO25_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO25_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO25_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO25_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO25_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO25_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO25_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO25_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO25_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO25_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO25_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO25_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO25_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO25_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO25_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO25_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO25_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO25_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO25_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO25_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO25_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO25_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO25_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO25_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO25_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO26
// Description : Pad control register
#define PADS_BANK0_GPIO26_OFFSET _u(0x0000006c)
#define PADS_BANK0_GPIO26_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO26_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO26_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO26_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO26_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO26_OD_MSB    _u(7)
#define PADS_BANK0_GPIO26_OD_LSB    _u(7)
#define PADS_BANK0_GPIO26_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO26_IE
// Description : Input enable
#define PADS_BANK0_GPIO26_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO26_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO26_IE_MSB    _u(6)
#define PADS_BANK0_GPIO26_IE_LSB    _u(6)
#define PADS_BANK0_GPIO26_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO26_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO26_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO26_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO26_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO26_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO26_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO26_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO26_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO26_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO26_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO26_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO26_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO26_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO26_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO26_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO26_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO26_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO26_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO26_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO26_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO26_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO26_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO26_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO26_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO26_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO26_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO26_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO26_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO26_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO26_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO26_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO26_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO26_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO26_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO27
// Description : Pad control register
#define PADS_BANK0_GPIO27_OFFSET _u(0x00000070)
#define PADS_BANK0_GPIO27_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO27_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO27_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO27_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO27_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO27_OD_MSB    _u(7)
#define PADS_BANK0_GPIO27_OD_LSB    _u(7)
#define PADS_BANK0_GPIO27_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO27_IE
// Description : Input enable
#define PADS_BANK0_GPIO27_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO27_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO27_IE_MSB    _u(6)
#define PADS_BANK0_GPIO27_IE_LSB    _u(6)
#define PADS_BANK0_GPIO27_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO27_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO27_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO27_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO27_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO27_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO27_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO27_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO27_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO27_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO27_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO27_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO27_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO27_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO27_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO27_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO27_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO27_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO27_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO27_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO27_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO27_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO27_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO27_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO27_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO27_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO27_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO27_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO27_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO27_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO27_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO27_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO27_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO27_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO27_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO28
// Description : Pad control register
#define PADS_BANK0_GPIO28_OFFSET _u(0x00000074)
#define PADS_BANK0_GPIO28_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO28_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO28_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO28_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO28_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO28_OD_MSB    _u(7)
#define PADS_BANK0_GPIO28_OD_LSB    _u(7)
#define PADS_BANK0_GPIO28_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO28_IE
// Description : Input enable
#define PADS_BANK0_GPIO28_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO28_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO28_IE_MSB    _u(6)
#define PADS_BANK0_GPIO28_IE_LSB    _u(6)
#define PADS_BANK0_GPIO28_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO28_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO28_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO28_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO28_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO28_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO28_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO28_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO28_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO28_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO28_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO28_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO28_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO28_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO28_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO28_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO28_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO28_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO28_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO28_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO28_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO28_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO28_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO28_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO28_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO28_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO28_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO28_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO28_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO28_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO28_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO28_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO28_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO28_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO28_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_GPIO29
// Description : Pad control register
#define PADS_BANK0_GPIO29_OFFSET _u(0x00000078)
#define PADS_BANK0_GPIO29_BITS   _u(0x000000ff)
#define PADS_BANK0_GPIO29_RESET  _u(0x00000056)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO29_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_GPIO29_OD_RESET  _u(0x0)
#define PADS_BANK0_GPIO29_OD_BITS   _u(0x00000080)
#define PADS_BANK0_GPIO29_OD_MSB    _u(7)
#define PADS_BANK0_GPIO29_OD_LSB    _u(7)
#define PADS_BANK0_GPIO29_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO29_IE
// Description : Input enable
#define PADS_BANK0_GPIO29_IE_RESET  _u(0x1)
#define PADS_BANK0_GPIO29_IE_BITS   _u(0x00000040)
#define PADS_BANK0_GPIO29_IE_MSB    _u(6)
#define PADS_BANK0_GPIO29_IE_LSB    _u(6)
#define PADS_BANK0_GPIO29_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO29_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_GPIO29_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_GPIO29_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_GPIO29_DRIVE_MSB        _u(5)
#define PADS_BANK0_GPIO29_DRIVE_LSB        _u(4)
#define PADS_BANK0_GPIO29_DRIVE_ACCESS     "RW"
#define PADS_BANK0_GPIO29_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_GPIO29_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_GPIO29_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_GPIO29_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO29_PUE
// Description : Pull up enable
#define PADS_BANK0_GPIO29_PUE_RESET  _u(0x0)
#define PADS_BANK0_GPIO29_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_GPIO29_PUE_MSB    _u(3)
#define PADS_BANK0_GPIO29_PUE_LSB    _u(3)
#define PADS_BANK0_GPIO29_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO29_PDE
// Description : Pull down enable
#define PADS_BANK0_GPIO29_PDE_RESET  _u(0x1)
#define PADS_BANK0_GPIO29_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_GPIO29_PDE_MSB    _u(2)
#define PADS_BANK0_GPIO29_PDE_LSB    _u(2)
#define PADS_BANK0_GPIO29_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO29_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_GPIO29_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_GPIO29_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_GPIO29_SCHMITT_MSB    _u(1)
#define PADS_BANK0_GPIO29_SCHMITT_LSB    _u(1)
#define PADS_BANK0_GPIO29_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_GPIO29_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_GPIO29_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_GPIO29_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_GPIO29_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_GPIO29_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_GPIO29_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_SWCLK
// Description : Pad control register
#define PADS_BANK0_SWCLK_OFFSET _u(0x0000007c)
#define PADS_BANK0_SWCLK_BITS   _u(0x000000ff)
#define PADS_BANK0_SWCLK_RESET  _u(0x000000da)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_SWCLK_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_SWCLK_OD_RESET  _u(0x1)
#define PADS_BANK0_SWCLK_OD_BITS   _u(0x00000080)
#define PADS_BANK0_SWCLK_OD_MSB    _u(7)
#define PADS_BANK0_SWCLK_OD_LSB    _u(7)
#define PADS_BANK0_SWCLK_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_SWCLK_IE
// Description : Input enable
#define PADS_BANK0_SWCLK_IE_RESET  _u(0x1)
#define PADS_BANK0_SWCLK_IE_BITS   _u(0x00000040)
#define PADS_BANK0_SWCLK_IE_MSB    _u(6)
#define PADS_BANK0_SWCLK_IE_LSB    _u(6)
#define PADS_BANK0_SWCLK_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_SWCLK_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_SWCLK_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_SWCLK_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_SWCLK_DRIVE_MSB        _u(5)
#define PADS_BANK0_SWCLK_DRIVE_LSB        _u(4)
#define PADS_BANK0_SWCLK_DRIVE_ACCESS     "RW"
#define PADS_BANK0_SWCLK_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_SWCLK_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_SWCLK_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_SWCLK_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_SWCLK_PUE
// Description : Pull up enable
#define PADS_BANK0_SWCLK_PUE_RESET  _u(0x1)
#define PADS_BANK0_SWCLK_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_SWCLK_PUE_MSB    _u(3)
#define PADS_BANK0_SWCLK_PUE_LSB    _u(3)
#define PADS_BANK0_SWCLK_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_SWCLK_PDE
// Description : Pull down enable
#define PADS_BANK0_SWCLK_PDE_RESET  _u(0x0)
#define PADS_BANK0_SWCLK_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_SWCLK_PDE_MSB    _u(2)
#define PADS_BANK0_SWCLK_PDE_LSB    _u(2)
#define PADS_BANK0_SWCLK_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_SWCLK_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_SWCLK_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_SWCLK_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_SWCLK_SCHMITT_MSB    _u(1)
#define PADS_BANK0_SWCLK_SCHMITT_LSB    _u(1)
#define PADS_BANK0_SWCLK_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_SWCLK_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_SWCLK_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_SWCLK_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_SWCLK_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_SWCLK_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_SWCLK_SLEWFAST_ACCESS "RW"
// =============================================================================
// Register    : PADS_BANK0_SWD
// Description : Pad control register
#define PADS_BANK0_SWD_OFFSET _u(0x00000080)
#define PADS_BANK0_SWD_BITS   _u(0x000000ff)
#define PADS_BANK0_SWD_RESET  _u(0x0000005a)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_SWD_OD
// Description : Output disable. Has priority over output enable from
//               peripherals
#define PADS_BANK0_SWD_OD_RESET  _u(0x0)
#define PADS_BANK0_SWD_OD_BITS   _u(0x00000080)
#define PADS_BANK0_SWD_OD_MSB    _u(7)
#define PADS_BANK0_SWD_OD_LSB    _u(7)
#define PADS_BANK0_SWD_OD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_SWD_IE
// Description : Input enable
#define PADS_BANK0_SWD_IE_RESET  _u(0x1)
#define PADS_BANK0_SWD_IE_BITS   _u(0x00000040)
#define PADS_BANK0_SWD_IE_MSB    _u(6)
#define PADS_BANK0_SWD_IE_LSB    _u(6)
#define PADS_BANK0_SWD_IE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_SWD_DRIVE
// Description : Drive strength.
//               0x0 -> 2mA
//               0x1 -> 4mA
//               0x2 -> 8mA
//               0x3 -> 12mA
#define PADS_BANK0_SWD_DRIVE_RESET      _u(0x1)
#define PADS_BANK0_SWD_DRIVE_BITS       _u(0x00000030)
#define PADS_BANK0_SWD_DRIVE_MSB        _u(5)
#define PADS_BANK0_SWD_DRIVE_LSB        _u(4)
#define PADS_BANK0_SWD_DRIVE_ACCESS     "RW"
#define PADS_BANK0_SWD_DRIVE_VALUE_2MA  _u(0x0)
#define PADS_BANK0_SWD_DRIVE_VALUE_4MA  _u(0x1)
#define PADS_BANK0_SWD_DRIVE_VALUE_8MA  _u(0x2)
#define PADS_BANK0_SWD_DRIVE_VALUE_12MA _u(0x3)
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_SWD_PUE
// Description : Pull up enable
#define PADS_BANK0_SWD_PUE_RESET  _u(0x1)
#define PADS_BANK0_SWD_PUE_BITS   _u(0x00000008)
#define PADS_BANK0_SWD_PUE_MSB    _u(3)
#define PADS_BANK0_SWD_PUE_LSB    _u(3)
#define PADS_BANK0_SWD_PUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_SWD_PDE
// Description : Pull down enable
#define PADS_BANK0_SWD_PDE_RESET  _u(0x0)
#define PADS_BANK0_SWD_PDE_BITS   _u(0x00000004)
#define PADS_BANK0_SWD_PDE_MSB    _u(2)
#define PADS_BANK0_SWD_PDE_LSB    _u(2)
#define PADS_BANK0_SWD_PDE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_SWD_SCHMITT
// Description : Enable schmitt trigger
#define PADS_BANK0_SWD_SCHMITT_RESET  _u(0x1)
#define PADS_BANK0_SWD_SCHMITT_BITS   _u(0x00000002)
#define PADS_BANK0_SWD_SCHMITT_MSB    _u(1)
#define PADS_BANK0_SWD_SCHMITT_LSB    _u(1)
#define PADS_BANK0_SWD_SCHMITT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PADS_BANK0_SWD_SLEWFAST
// Description : Slew rate control. 1 = Fast, 0 = Slow
#define PADS_BANK0_SWD_SLEWFAST_RESET  _u(0x0)
#define PADS_BANK0_SWD_SLEWFAST_BITS   _u(0x00000001)
#define PADS_BANK0_SWD_SLEWFAST_MSB    _u(0)
#define PADS_BANK0_SWD_SLEWFAST_LSB    _u(0)
#define PADS_BANK0_SWD_SLEWFAST_ACCESS "RW"
// =============================================================================
#endif // HARDWARE_REGS_PADS_BANK0_DEFINED
