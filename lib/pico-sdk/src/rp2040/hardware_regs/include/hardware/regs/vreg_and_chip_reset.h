/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : VREG_AND_CHIP_RESET
// Version        : 1
// Bus type       : apb
// Description    : control and status for on-chip voltage regulator and chip
//                  level reset subsystem
// =============================================================================
#ifndef HARDWARE_REGS_VREG_AND_CHIP_RESET_DEFINED
#define HARDWARE_REGS_VREG_AND_CHIP_RESET_DEFINED
// =============================================================================
// Register    : VREG_AND_CHIP_RESET_VREG
// Description : Voltage regulator control and status
#define VREG_AND_CHIP_RESET_VREG_OFFSET _u(0x00000000)
#define VREG_AND_CHIP_RESET_VREG_BITS   _u(0x000010f3)
#define VREG_AND_CHIP_RESET_VREG_RESET  _u(0x000000b1)
// -----------------------------------------------------------------------------
// Field       : VREG_AND_CHIP_RESET_VREG_ROK
// Description : regulation status
//               0=not in regulation, 1=in regulation
#define VREG_AND_CHIP_RESET_VREG_ROK_RESET  _u(0x0)
#define VREG_AND_CHIP_RESET_VREG_ROK_BITS   _u(0x00001000)
#define VREG_AND_CHIP_RESET_VREG_ROK_MSB    _u(12)
#define VREG_AND_CHIP_RESET_VREG_ROK_LSB    _u(12)
#define VREG_AND_CHIP_RESET_VREG_ROK_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : VREG_AND_CHIP_RESET_VREG_VSEL
// Description : output voltage select
//               0000 to 0101 - 0.80V
//               0110         - 0.85V
//               0111         - 0.90V
//               1000         - 0.95V
//               1001         - 1.00V
//               1010         - 1.05V
//               1011         - 1.10V (default)
//               1100         - 1.15V
//               1101         - 1.20V
//               1110         - 1.25V
//               1111         - 1.30V
#define VREG_AND_CHIP_RESET_VREG_VSEL_RESET  _u(0xb)
#define VREG_AND_CHIP_RESET_VREG_VSEL_BITS   _u(0x000000f0)
#define VREG_AND_CHIP_RESET_VREG_VSEL_MSB    _u(7)
#define VREG_AND_CHIP_RESET_VREG_VSEL_LSB    _u(4)
#define VREG_AND_CHIP_RESET_VREG_VSEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : VREG_AND_CHIP_RESET_VREG_HIZ
// Description : high impedance mode select
//               0=not in high impedance mode, 1=in high impedance mode
#define VREG_AND_CHIP_RESET_VREG_HIZ_RESET  _u(0x0)
#define VREG_AND_CHIP_RESET_VREG_HIZ_BITS   _u(0x00000002)
#define VREG_AND_CHIP_RESET_VREG_HIZ_MSB    _u(1)
#define VREG_AND_CHIP_RESET_VREG_HIZ_LSB    _u(1)
#define VREG_AND_CHIP_RESET_VREG_HIZ_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : VREG_AND_CHIP_RESET_VREG_EN
// Description : enable
//               0=not enabled, 1=enabled
#define VREG_AND_CHIP_RESET_VREG_EN_RESET  _u(0x1)
#define VREG_AND_CHIP_RESET_VREG_EN_BITS   _u(0x00000001)
#define VREG_AND_CHIP_RESET_VREG_EN_MSB    _u(0)
#define VREG_AND_CHIP_RESET_VREG_EN_LSB    _u(0)
#define VREG_AND_CHIP_RESET_VREG_EN_ACCESS "RW"
// =============================================================================
// Register    : VREG_AND_CHIP_RESET_BOD
// Description : brown-out detection control
#define VREG_AND_CHIP_RESET_BOD_OFFSET _u(0x00000004)
#define VREG_AND_CHIP_RESET_BOD_BITS   _u(0x000000f1)
#define VREG_AND_CHIP_RESET_BOD_RESET  _u(0x00000091)
// -----------------------------------------------------------------------------
// Field       : VREG_AND_CHIP_RESET_BOD_VSEL
// Description : threshold select
//               0000 - 0.473V
//               0001 - 0.516V
//               0010 - 0.559V
//               0011 - 0.602V
//               0100 - 0.645V
//               0101 - 0.688V
//               0110 - 0.731V
//               0111 - 0.774V
//               1000 - 0.817V
//               1001 - 0.860V (default)
//               1010 - 0.903V
//               1011 - 0.946V
//               1100 - 0.989V
//               1101 - 1.032V
//               1110 - 1.075V
//               1111 - 1.118V
#define VREG_AND_CHIP_RESET_BOD_VSEL_RESET  _u(0x9)
#define VREG_AND_CHIP_RESET_BOD_VSEL_BITS   _u(0x000000f0)
#define VREG_AND_CHIP_RESET_BOD_VSEL_MSB    _u(7)
#define VREG_AND_CHIP_RESET_BOD_VSEL_LSB    _u(4)
#define VREG_AND_CHIP_RESET_BOD_VSEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : VREG_AND_CHIP_RESET_BOD_EN
// Description : enable
//               0=not enabled, 1=enabled
#define VREG_AND_CHIP_RESET_BOD_EN_RESET  _u(0x1)
#define VREG_AND_CHIP_RESET_BOD_EN_BITS   _u(0x00000001)
#define VREG_AND_CHIP_RESET_BOD_EN_MSB    _u(0)
#define VREG_AND_CHIP_RESET_BOD_EN_LSB    _u(0)
#define VREG_AND_CHIP_RESET_BOD_EN_ACCESS "RW"
// =============================================================================
// Register    : VREG_AND_CHIP_RESET_CHIP_RESET
// Description : Chip reset control and status
#define VREG_AND_CHIP_RESET_CHIP_RESET_OFFSET _u(0x00000008)
#define VREG_AND_CHIP_RESET_CHIP_RESET_BITS   _u(0x01110100)
#define VREG_AND_CHIP_RESET_CHIP_RESET_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : VREG_AND_CHIP_RESET_CHIP_RESET_PSM_RESTART_FLAG
// Description : This is set by psm_restart from the debugger.
//               Its purpose is to branch bootcode to a safe mode when the
//               debugger has issued a psm_restart in order to recover from a
//               boot lock-up.
//               In the safe mode the debugger can repair the boot code, clear
//               this flag then reboot the processor.
#define VREG_AND_CHIP_RESET_CHIP_RESET_PSM_RESTART_FLAG_RESET  _u(0x0)
#define VREG_AND_CHIP_RESET_CHIP_RESET_PSM_RESTART_FLAG_BITS   _u(0x01000000)
#define VREG_AND_CHIP_RESET_CHIP_RESET_PSM_RESTART_FLAG_MSB    _u(24)
#define VREG_AND_CHIP_RESET_CHIP_RESET_PSM_RESTART_FLAG_LSB    _u(24)
#define VREG_AND_CHIP_RESET_CHIP_RESET_PSM_RESTART_FLAG_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : VREG_AND_CHIP_RESET_CHIP_RESET_HAD_PSM_RESTART
// Description : Last reset was from the debug port
#define VREG_AND_CHIP_RESET_CHIP_RESET_HAD_PSM_RESTART_RESET  _u(0x0)
#define VREG_AND_CHIP_RESET_CHIP_RESET_HAD_PSM_RESTART_BITS   _u(0x00100000)
#define VREG_AND_CHIP_RESET_CHIP_RESET_HAD_PSM_RESTART_MSB    _u(20)
#define VREG_AND_CHIP_RESET_CHIP_RESET_HAD_PSM_RESTART_LSB    _u(20)
#define VREG_AND_CHIP_RESET_CHIP_RESET_HAD_PSM_RESTART_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : VREG_AND_CHIP_RESET_CHIP_RESET_HAD_RUN
// Description : Last reset was from the RUN pin
#define VREG_AND_CHIP_RESET_CHIP_RESET_HAD_RUN_RESET  _u(0x0)
#define VREG_AND_CHIP_RESET_CHIP_RESET_HAD_RUN_BITS   _u(0x00010000)
#define VREG_AND_CHIP_RESET_CHIP_RESET_HAD_RUN_MSB    _u(16)
#define VREG_AND_CHIP_RESET_CHIP_RESET_HAD_RUN_LSB    _u(16)
#define VREG_AND_CHIP_RESET_CHIP_RESET_HAD_RUN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : VREG_AND_CHIP_RESET_CHIP_RESET_HAD_POR
// Description : Last reset was from the power-on reset or brown-out detection
//               blocks
#define VREG_AND_CHIP_RESET_CHIP_RESET_HAD_POR_RESET  _u(0x0)
#define VREG_AND_CHIP_RESET_CHIP_RESET_HAD_POR_BITS   _u(0x00000100)
#define VREG_AND_CHIP_RESET_CHIP_RESET_HAD_POR_MSB    _u(8)
#define VREG_AND_CHIP_RESET_CHIP_RESET_HAD_POR_LSB    _u(8)
#define VREG_AND_CHIP_RESET_CHIP_RESET_HAD_POR_ACCESS "RO"
// =============================================================================
#endif // HARDWARE_REGS_VREG_AND_CHIP_RESET_DEFINED
