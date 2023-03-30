/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : SYSCFG
// Version        : 1
// Bus type       : apb
// Description    : Register block for various chip control signals
// =============================================================================
#ifndef HARDWARE_REGS_SYSCFG_DEFINED
#define HARDWARE_REGS_SYSCFG_DEFINED
// =============================================================================
// Register    : SYSCFG_PROC0_NMI_MASK
// Description : Processor core 0 NMI source mask
//               Set a bit high to enable NMI from that IRQ
#define SYSCFG_PROC0_NMI_MASK_OFFSET _u(0x00000000)
#define SYSCFG_PROC0_NMI_MASK_BITS   _u(0xffffffff)
#define SYSCFG_PROC0_NMI_MASK_RESET  _u(0x00000000)
#define SYSCFG_PROC0_NMI_MASK_MSB    _u(31)
#define SYSCFG_PROC0_NMI_MASK_LSB    _u(0)
#define SYSCFG_PROC0_NMI_MASK_ACCESS "RW"
// =============================================================================
// Register    : SYSCFG_PROC1_NMI_MASK
// Description : Processor core 1 NMI source mask
//               Set a bit high to enable NMI from that IRQ
#define SYSCFG_PROC1_NMI_MASK_OFFSET _u(0x00000004)
#define SYSCFG_PROC1_NMI_MASK_BITS   _u(0xffffffff)
#define SYSCFG_PROC1_NMI_MASK_RESET  _u(0x00000000)
#define SYSCFG_PROC1_NMI_MASK_MSB    _u(31)
#define SYSCFG_PROC1_NMI_MASK_LSB    _u(0)
#define SYSCFG_PROC1_NMI_MASK_ACCESS "RW"
// =============================================================================
// Register    : SYSCFG_PROC_CONFIG
// Description : Configuration for processors
#define SYSCFG_PROC_CONFIG_OFFSET _u(0x00000008)
#define SYSCFG_PROC_CONFIG_BITS   _u(0xff000003)
#define SYSCFG_PROC_CONFIG_RESET  _u(0x10000000)
// -----------------------------------------------------------------------------
// Field       : SYSCFG_PROC_CONFIG_PROC1_DAP_INSTID
// Description : Configure proc1 DAP instance ID.
//               Recommend that this is NOT changed until you require debug
//               access in multi-chip environment
//               WARNING: do not set to 15 as this is reserved for RescueDP
#define SYSCFG_PROC_CONFIG_PROC1_DAP_INSTID_RESET  _u(0x1)
#define SYSCFG_PROC_CONFIG_PROC1_DAP_INSTID_BITS   _u(0xf0000000)
#define SYSCFG_PROC_CONFIG_PROC1_DAP_INSTID_MSB    _u(31)
#define SYSCFG_PROC_CONFIG_PROC1_DAP_INSTID_LSB    _u(28)
#define SYSCFG_PROC_CONFIG_PROC1_DAP_INSTID_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SYSCFG_PROC_CONFIG_PROC0_DAP_INSTID
// Description : Configure proc0 DAP instance ID.
//               Recommend that this is NOT changed until you require debug
//               access in multi-chip environment
//               WARNING: do not set to 15 as this is reserved for RescueDP
#define SYSCFG_PROC_CONFIG_PROC0_DAP_INSTID_RESET  _u(0x0)
#define SYSCFG_PROC_CONFIG_PROC0_DAP_INSTID_BITS   _u(0x0f000000)
#define SYSCFG_PROC_CONFIG_PROC0_DAP_INSTID_MSB    _u(27)
#define SYSCFG_PROC_CONFIG_PROC0_DAP_INSTID_LSB    _u(24)
#define SYSCFG_PROC_CONFIG_PROC0_DAP_INSTID_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SYSCFG_PROC_CONFIG_PROC1_HALTED
// Description : Indication that proc1 has halted
#define SYSCFG_PROC_CONFIG_PROC1_HALTED_RESET  _u(0x0)
#define SYSCFG_PROC_CONFIG_PROC1_HALTED_BITS   _u(0x00000002)
#define SYSCFG_PROC_CONFIG_PROC1_HALTED_MSB    _u(1)
#define SYSCFG_PROC_CONFIG_PROC1_HALTED_LSB    _u(1)
#define SYSCFG_PROC_CONFIG_PROC1_HALTED_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SYSCFG_PROC_CONFIG_PROC0_HALTED
// Description : Indication that proc0 has halted
#define SYSCFG_PROC_CONFIG_PROC0_HALTED_RESET  _u(0x0)
#define SYSCFG_PROC_CONFIG_PROC0_HALTED_BITS   _u(0x00000001)
#define SYSCFG_PROC_CONFIG_PROC0_HALTED_MSB    _u(0)
#define SYSCFG_PROC_CONFIG_PROC0_HALTED_LSB    _u(0)
#define SYSCFG_PROC_CONFIG_PROC0_HALTED_ACCESS "RO"
// =============================================================================
// Register    : SYSCFG_PROC_IN_SYNC_BYPASS
// Description : For each bit, if 1, bypass the input synchronizer between that
//               GPIO
//               and the GPIO input register in the SIO. The input synchronizers
//               should
//               generally be unbypassed, to avoid injecting metastabilities
//               into processors.
//               If you're feeling brave, you can bypass to save two cycles of
//               input
//               latency. This register applies to GPIO 0...29.
#define SYSCFG_PROC_IN_SYNC_BYPASS_OFFSET _u(0x0000000c)
#define SYSCFG_PROC_IN_SYNC_BYPASS_BITS   _u(0x3fffffff)
#define SYSCFG_PROC_IN_SYNC_BYPASS_RESET  _u(0x00000000)
#define SYSCFG_PROC_IN_SYNC_BYPASS_MSB    _u(29)
#define SYSCFG_PROC_IN_SYNC_BYPASS_LSB    _u(0)
#define SYSCFG_PROC_IN_SYNC_BYPASS_ACCESS "RW"
// =============================================================================
// Register    : SYSCFG_PROC_IN_SYNC_BYPASS_HI
// Description : For each bit, if 1, bypass the input synchronizer between that
//               GPIO
//               and the GPIO input register in the SIO. The input synchronizers
//               should
//               generally be unbypassed, to avoid injecting metastabilities
//               into processors.
//               If you're feeling brave, you can bypass to save two cycles of
//               input
//               latency. This register applies to GPIO 30...35 (the QSPI IOs).
#define SYSCFG_PROC_IN_SYNC_BYPASS_HI_OFFSET _u(0x00000010)
#define SYSCFG_PROC_IN_SYNC_BYPASS_HI_BITS   _u(0x0000003f)
#define SYSCFG_PROC_IN_SYNC_BYPASS_HI_RESET  _u(0x00000000)
#define SYSCFG_PROC_IN_SYNC_BYPASS_HI_MSB    _u(5)
#define SYSCFG_PROC_IN_SYNC_BYPASS_HI_LSB    _u(0)
#define SYSCFG_PROC_IN_SYNC_BYPASS_HI_ACCESS "RW"
// =============================================================================
// Register    : SYSCFG_DBGFORCE
// Description : Directly control the SWD debug port of either processor
#define SYSCFG_DBGFORCE_OFFSET _u(0x00000014)
#define SYSCFG_DBGFORCE_BITS   _u(0x000000ff)
#define SYSCFG_DBGFORCE_RESET  _u(0x00000066)
// -----------------------------------------------------------------------------
// Field       : SYSCFG_DBGFORCE_PROC1_ATTACH
// Description : Attach processor 1 debug port to syscfg controls, and
//               disconnect it from external SWD pads.
#define SYSCFG_DBGFORCE_PROC1_ATTACH_RESET  _u(0x0)
#define SYSCFG_DBGFORCE_PROC1_ATTACH_BITS   _u(0x00000080)
#define SYSCFG_DBGFORCE_PROC1_ATTACH_MSB    _u(7)
#define SYSCFG_DBGFORCE_PROC1_ATTACH_LSB    _u(7)
#define SYSCFG_DBGFORCE_PROC1_ATTACH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SYSCFG_DBGFORCE_PROC1_SWCLK
// Description : Directly drive processor 1 SWCLK, if PROC1_ATTACH is set
#define SYSCFG_DBGFORCE_PROC1_SWCLK_RESET  _u(0x1)
#define SYSCFG_DBGFORCE_PROC1_SWCLK_BITS   _u(0x00000040)
#define SYSCFG_DBGFORCE_PROC1_SWCLK_MSB    _u(6)
#define SYSCFG_DBGFORCE_PROC1_SWCLK_LSB    _u(6)
#define SYSCFG_DBGFORCE_PROC1_SWCLK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SYSCFG_DBGFORCE_PROC1_SWDI
// Description : Directly drive processor 1 SWDIO input, if PROC1_ATTACH is set
#define SYSCFG_DBGFORCE_PROC1_SWDI_RESET  _u(0x1)
#define SYSCFG_DBGFORCE_PROC1_SWDI_BITS   _u(0x00000020)
#define SYSCFG_DBGFORCE_PROC1_SWDI_MSB    _u(5)
#define SYSCFG_DBGFORCE_PROC1_SWDI_LSB    _u(5)
#define SYSCFG_DBGFORCE_PROC1_SWDI_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SYSCFG_DBGFORCE_PROC1_SWDO
// Description : Observe the value of processor 1 SWDIO output.
#define SYSCFG_DBGFORCE_PROC1_SWDO_RESET  "-"
#define SYSCFG_DBGFORCE_PROC1_SWDO_BITS   _u(0x00000010)
#define SYSCFG_DBGFORCE_PROC1_SWDO_MSB    _u(4)
#define SYSCFG_DBGFORCE_PROC1_SWDO_LSB    _u(4)
#define SYSCFG_DBGFORCE_PROC1_SWDO_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SYSCFG_DBGFORCE_PROC0_ATTACH
// Description : Attach processor 0 debug port to syscfg controls, and
//               disconnect it from external SWD pads.
#define SYSCFG_DBGFORCE_PROC0_ATTACH_RESET  _u(0x0)
#define SYSCFG_DBGFORCE_PROC0_ATTACH_BITS   _u(0x00000008)
#define SYSCFG_DBGFORCE_PROC0_ATTACH_MSB    _u(3)
#define SYSCFG_DBGFORCE_PROC0_ATTACH_LSB    _u(3)
#define SYSCFG_DBGFORCE_PROC0_ATTACH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SYSCFG_DBGFORCE_PROC0_SWCLK
// Description : Directly drive processor 0 SWCLK, if PROC0_ATTACH is set
#define SYSCFG_DBGFORCE_PROC0_SWCLK_RESET  _u(0x1)
#define SYSCFG_DBGFORCE_PROC0_SWCLK_BITS   _u(0x00000004)
#define SYSCFG_DBGFORCE_PROC0_SWCLK_MSB    _u(2)
#define SYSCFG_DBGFORCE_PROC0_SWCLK_LSB    _u(2)
#define SYSCFG_DBGFORCE_PROC0_SWCLK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SYSCFG_DBGFORCE_PROC0_SWDI
// Description : Directly drive processor 0 SWDIO input, if PROC0_ATTACH is set
#define SYSCFG_DBGFORCE_PROC0_SWDI_RESET  _u(0x1)
#define SYSCFG_DBGFORCE_PROC0_SWDI_BITS   _u(0x00000002)
#define SYSCFG_DBGFORCE_PROC0_SWDI_MSB    _u(1)
#define SYSCFG_DBGFORCE_PROC0_SWDI_LSB    _u(1)
#define SYSCFG_DBGFORCE_PROC0_SWDI_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SYSCFG_DBGFORCE_PROC0_SWDO
// Description : Observe the value of processor 0 SWDIO output.
#define SYSCFG_DBGFORCE_PROC0_SWDO_RESET  "-"
#define SYSCFG_DBGFORCE_PROC0_SWDO_BITS   _u(0x00000001)
#define SYSCFG_DBGFORCE_PROC0_SWDO_MSB    _u(0)
#define SYSCFG_DBGFORCE_PROC0_SWDO_LSB    _u(0)
#define SYSCFG_DBGFORCE_PROC0_SWDO_ACCESS "RO"
// =============================================================================
// Register    : SYSCFG_MEMPOWERDOWN
// Description : Control power downs to memories. Set high to power down
//               memories.
//               Use with extreme caution
#define SYSCFG_MEMPOWERDOWN_OFFSET _u(0x00000018)
#define SYSCFG_MEMPOWERDOWN_BITS   _u(0x000000ff)
#define SYSCFG_MEMPOWERDOWN_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : SYSCFG_MEMPOWERDOWN_ROM
// Description : None
#define SYSCFG_MEMPOWERDOWN_ROM_RESET  _u(0x0)
#define SYSCFG_MEMPOWERDOWN_ROM_BITS   _u(0x00000080)
#define SYSCFG_MEMPOWERDOWN_ROM_MSB    _u(7)
#define SYSCFG_MEMPOWERDOWN_ROM_LSB    _u(7)
#define SYSCFG_MEMPOWERDOWN_ROM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SYSCFG_MEMPOWERDOWN_USB
// Description : None
#define SYSCFG_MEMPOWERDOWN_USB_RESET  _u(0x0)
#define SYSCFG_MEMPOWERDOWN_USB_BITS   _u(0x00000040)
#define SYSCFG_MEMPOWERDOWN_USB_MSB    _u(6)
#define SYSCFG_MEMPOWERDOWN_USB_LSB    _u(6)
#define SYSCFG_MEMPOWERDOWN_USB_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SYSCFG_MEMPOWERDOWN_SRAM5
// Description : None
#define SYSCFG_MEMPOWERDOWN_SRAM5_RESET  _u(0x0)
#define SYSCFG_MEMPOWERDOWN_SRAM5_BITS   _u(0x00000020)
#define SYSCFG_MEMPOWERDOWN_SRAM5_MSB    _u(5)
#define SYSCFG_MEMPOWERDOWN_SRAM5_LSB    _u(5)
#define SYSCFG_MEMPOWERDOWN_SRAM5_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SYSCFG_MEMPOWERDOWN_SRAM4
// Description : None
#define SYSCFG_MEMPOWERDOWN_SRAM4_RESET  _u(0x0)
#define SYSCFG_MEMPOWERDOWN_SRAM4_BITS   _u(0x00000010)
#define SYSCFG_MEMPOWERDOWN_SRAM4_MSB    _u(4)
#define SYSCFG_MEMPOWERDOWN_SRAM4_LSB    _u(4)
#define SYSCFG_MEMPOWERDOWN_SRAM4_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SYSCFG_MEMPOWERDOWN_SRAM3
// Description : None
#define SYSCFG_MEMPOWERDOWN_SRAM3_RESET  _u(0x0)
#define SYSCFG_MEMPOWERDOWN_SRAM3_BITS   _u(0x00000008)
#define SYSCFG_MEMPOWERDOWN_SRAM3_MSB    _u(3)
#define SYSCFG_MEMPOWERDOWN_SRAM3_LSB    _u(3)
#define SYSCFG_MEMPOWERDOWN_SRAM3_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SYSCFG_MEMPOWERDOWN_SRAM2
// Description : None
#define SYSCFG_MEMPOWERDOWN_SRAM2_RESET  _u(0x0)
#define SYSCFG_MEMPOWERDOWN_SRAM2_BITS   _u(0x00000004)
#define SYSCFG_MEMPOWERDOWN_SRAM2_MSB    _u(2)
#define SYSCFG_MEMPOWERDOWN_SRAM2_LSB    _u(2)
#define SYSCFG_MEMPOWERDOWN_SRAM2_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SYSCFG_MEMPOWERDOWN_SRAM1
// Description : None
#define SYSCFG_MEMPOWERDOWN_SRAM1_RESET  _u(0x0)
#define SYSCFG_MEMPOWERDOWN_SRAM1_BITS   _u(0x00000002)
#define SYSCFG_MEMPOWERDOWN_SRAM1_MSB    _u(1)
#define SYSCFG_MEMPOWERDOWN_SRAM1_LSB    _u(1)
#define SYSCFG_MEMPOWERDOWN_SRAM1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SYSCFG_MEMPOWERDOWN_SRAM0
// Description : None
#define SYSCFG_MEMPOWERDOWN_SRAM0_RESET  _u(0x0)
#define SYSCFG_MEMPOWERDOWN_SRAM0_BITS   _u(0x00000001)
#define SYSCFG_MEMPOWERDOWN_SRAM0_MSB    _u(0)
#define SYSCFG_MEMPOWERDOWN_SRAM0_LSB    _u(0)
#define SYSCFG_MEMPOWERDOWN_SRAM0_ACCESS "RW"
// =============================================================================
#endif // HARDWARE_REGS_SYSCFG_DEFINED
