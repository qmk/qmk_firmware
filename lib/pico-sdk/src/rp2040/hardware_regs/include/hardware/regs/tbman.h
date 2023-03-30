/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : TBMAN
// Version        : 1
// Bus type       : apb
// Description    : Testbench manager. Allows the programmer to know what
//                  platform their software is running on.
// =============================================================================
#ifndef HARDWARE_REGS_TBMAN_DEFINED
#define HARDWARE_REGS_TBMAN_DEFINED
// =============================================================================
// Register    : TBMAN_PLATFORM
// Description : Indicates the type of platform in use
#define TBMAN_PLATFORM_OFFSET _u(0x00000000)
#define TBMAN_PLATFORM_BITS   _u(0x00000003)
#define TBMAN_PLATFORM_RESET  _u(0x00000005)
// -----------------------------------------------------------------------------
// Field       : TBMAN_PLATFORM_FPGA
// Description : Indicates the platform is an FPGA
#define TBMAN_PLATFORM_FPGA_RESET  _u(0x0)
#define TBMAN_PLATFORM_FPGA_BITS   _u(0x00000002)
#define TBMAN_PLATFORM_FPGA_MSB    _u(1)
#define TBMAN_PLATFORM_FPGA_LSB    _u(1)
#define TBMAN_PLATFORM_FPGA_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : TBMAN_PLATFORM_ASIC
// Description : Indicates the platform is an ASIC
#define TBMAN_PLATFORM_ASIC_RESET  _u(0x1)
#define TBMAN_PLATFORM_ASIC_BITS   _u(0x00000001)
#define TBMAN_PLATFORM_ASIC_MSB    _u(0)
#define TBMAN_PLATFORM_ASIC_LSB    _u(0)
#define TBMAN_PLATFORM_ASIC_ACCESS "RO"
// =============================================================================
#endif // HARDWARE_REGS_TBMAN_DEFINED
