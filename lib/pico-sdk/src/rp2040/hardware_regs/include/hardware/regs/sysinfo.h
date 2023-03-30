/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : SYSINFO
// Version        : 1
// Bus type       : apb
// Description    : None
// =============================================================================
#ifndef HARDWARE_REGS_SYSINFO_DEFINED
#define HARDWARE_REGS_SYSINFO_DEFINED
// =============================================================================
// Register    : SYSINFO_CHIP_ID
// Description : JEDEC JEP-106 compliant chip identifier.
#define SYSINFO_CHIP_ID_OFFSET _u(0x00000000)
#define SYSINFO_CHIP_ID_BITS   _u(0xffffffff)
#define SYSINFO_CHIP_ID_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : SYSINFO_CHIP_ID_REVISION
// Description : None
#define SYSINFO_CHIP_ID_REVISION_RESET  "-"
#define SYSINFO_CHIP_ID_REVISION_BITS   _u(0xf0000000)
#define SYSINFO_CHIP_ID_REVISION_MSB    _u(31)
#define SYSINFO_CHIP_ID_REVISION_LSB    _u(28)
#define SYSINFO_CHIP_ID_REVISION_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SYSINFO_CHIP_ID_PART
// Description : None
#define SYSINFO_CHIP_ID_PART_RESET  "-"
#define SYSINFO_CHIP_ID_PART_BITS   _u(0x0ffff000)
#define SYSINFO_CHIP_ID_PART_MSB    _u(27)
#define SYSINFO_CHIP_ID_PART_LSB    _u(12)
#define SYSINFO_CHIP_ID_PART_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SYSINFO_CHIP_ID_MANUFACTURER
// Description : None
#define SYSINFO_CHIP_ID_MANUFACTURER_RESET  "-"
#define SYSINFO_CHIP_ID_MANUFACTURER_BITS   _u(0x00000fff)
#define SYSINFO_CHIP_ID_MANUFACTURER_MSB    _u(11)
#define SYSINFO_CHIP_ID_MANUFACTURER_LSB    _u(0)
#define SYSINFO_CHIP_ID_MANUFACTURER_ACCESS "RO"
// =============================================================================
// Register    : SYSINFO_PLATFORM
// Description : Platform register. Allows software to know what environment it
//               is running in.
#define SYSINFO_PLATFORM_OFFSET _u(0x00000004)
#define SYSINFO_PLATFORM_BITS   _u(0x00000003)
#define SYSINFO_PLATFORM_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : SYSINFO_PLATFORM_ASIC
// Description : None
#define SYSINFO_PLATFORM_ASIC_RESET  _u(0x0)
#define SYSINFO_PLATFORM_ASIC_BITS   _u(0x00000002)
#define SYSINFO_PLATFORM_ASIC_MSB    _u(1)
#define SYSINFO_PLATFORM_ASIC_LSB    _u(1)
#define SYSINFO_PLATFORM_ASIC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SYSINFO_PLATFORM_FPGA
// Description : None
#define SYSINFO_PLATFORM_FPGA_RESET  _u(0x0)
#define SYSINFO_PLATFORM_FPGA_BITS   _u(0x00000001)
#define SYSINFO_PLATFORM_FPGA_MSB    _u(0)
#define SYSINFO_PLATFORM_FPGA_LSB    _u(0)
#define SYSINFO_PLATFORM_FPGA_ACCESS "RO"
// =============================================================================
// Register    : SYSINFO_GITREF_RP2040
// Description : Git hash of the chip source. Used to identify chip version.
#define SYSINFO_GITREF_RP2040_OFFSET _u(0x00000040)
#define SYSINFO_GITREF_RP2040_BITS   _u(0xffffffff)
#define SYSINFO_GITREF_RP2040_RESET  "-"
#define SYSINFO_GITREF_RP2040_MSB    _u(31)
#define SYSINFO_GITREF_RP2040_LSB    _u(0)
#define SYSINFO_GITREF_RP2040_ACCESS "RO"
// =============================================================================
#endif // HARDWARE_REGS_SYSINFO_DEFINED
