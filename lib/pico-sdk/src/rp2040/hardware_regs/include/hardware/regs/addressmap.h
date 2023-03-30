/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _ADDRESSMAP_H_
#define _ADDRESSMAP_H_

#include "hardware/platform_defs.h"

// Register address offsets for atomic RMW aliases
#define REG_ALIAS_RW_BITS  (0x0u << 12u)
#define REG_ALIAS_XOR_BITS (0x1u << 12u)
#define REG_ALIAS_SET_BITS (0x2u << 12u)
#define REG_ALIAS_CLR_BITS (0x3u << 12u)

#define ROM_BASE _u(0x00000000)
#define XIP_BASE _u(0x10000000)
#define XIP_MAIN_BASE _u(0x10000000)
#define XIP_NOALLOC_BASE _u(0x11000000)
#define XIP_NOCACHE_BASE _u(0x12000000)
#define XIP_NOCACHE_NOALLOC_BASE _u(0x13000000)
#define XIP_CTRL_BASE _u(0x14000000)
#define XIP_SRAM_BASE _u(0x15000000)
#define XIP_SRAM_END _u(0x15004000)
#define XIP_SSI_BASE _u(0x18000000)
#define SRAM_BASE _u(0x20000000)
#define SRAM_STRIPED_BASE _u(0x20000000)
#define SRAM_STRIPED_END _u(0x20040000)
#define SRAM4_BASE _u(0x20040000)
#define SRAM5_BASE _u(0x20041000)
#define SRAM_END _u(0x20042000)
#define SRAM0_BASE _u(0x21000000)
#define SRAM1_BASE _u(0x21010000)
#define SRAM2_BASE _u(0x21020000)
#define SRAM3_BASE _u(0x21030000)
#define SYSINFO_BASE _u(0x40000000)
#define SYSCFG_BASE _u(0x40004000)
#define CLOCKS_BASE _u(0x40008000)
#define RESETS_BASE _u(0x4000c000)
#define PSM_BASE _u(0x40010000)
#define IO_BANK0_BASE _u(0x40014000)
#define IO_QSPI_BASE _u(0x40018000)
#define PADS_BANK0_BASE _u(0x4001c000)
#define PADS_QSPI_BASE _u(0x40020000)
#define XOSC_BASE _u(0x40024000)
#define PLL_SYS_BASE _u(0x40028000)
#define PLL_USB_BASE _u(0x4002c000)
#define BUSCTRL_BASE _u(0x40030000)
#define UART0_BASE _u(0x40034000)
#define UART1_BASE _u(0x40038000)
#define SPI0_BASE _u(0x4003c000)
#define SPI1_BASE _u(0x40040000)
#define I2C0_BASE _u(0x40044000)
#define I2C1_BASE _u(0x40048000)
#define ADC_BASE _u(0x4004c000)
#define PWM_BASE _u(0x40050000)
#define TIMER_BASE _u(0x40054000)
#define WATCHDOG_BASE _u(0x40058000)
#define RTC_BASE _u(0x4005c000)
#define ROSC_BASE _u(0x40060000)
#define VREG_AND_CHIP_RESET_BASE _u(0x40064000)
#define TBMAN_BASE _u(0x4006c000)
#define DMA_BASE _u(0x50000000)
#define USBCTRL_DPRAM_BASE _u(0x50100000)
#define USBCTRL_BASE _u(0x50100000)
#define USBCTRL_REGS_BASE _u(0x50110000)
#define PIO0_BASE _u(0x50200000)
#define PIO1_BASE _u(0x50300000)
#define XIP_AUX_BASE _u(0x50400000)
#define SIO_BASE _u(0xd0000000)
#define PPB_BASE _u(0xe0000000)

#endif // _ADDRESSMAP_H_
