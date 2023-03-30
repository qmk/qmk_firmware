/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_PLATFORM_DEFS_H
#define _HARDWARE_PLATFORM_DEFS_H

// This header is included from C and assembler - intended mostly for #defines; guard other stuff with #ifdef __ASSEMBLER__

#ifndef _u
#ifdef __ASSEMBLER__
#define _u(x) x
#else
#define _u(x) x ## u
#endif
#endif

#define NUM_CORES _u(2)
#define NUM_DMA_CHANNELS _u(12)
#define NUM_DMA_TIMERS _u(4)
#define NUM_IRQS _u(32)
#define NUM_USER_IRQS _u(6)
#define NUM_PIOS _u(2)
#define NUM_PIO_STATE_MACHINES _u(4)
#define NUM_PWM_SLICES _u(8)
#define NUM_SPIN_LOCKS _u(32)
#define NUM_UARTS _u(2)
#define NUM_I2CS _u(2)
#define NUM_SPIS _u(2)
#define NUM_TIMERS _u(4)
#define NUM_ADC_CHANNELS _u(5)

#define NUM_BANK0_GPIOS _u(30)
#define NUM_QSPI_GPIOS _u(6)

#define PIO_INSTRUCTION_COUNT _u(32)

// PICO_CONFIG: XOSC_MHZ, The crystal oscillator frequency in Mhz, type=int, default=12, advanced=true, group=hardware_base
#ifndef XOSC_MHZ
#define XOSC_MHZ _u(12)
#endif

#define FIRST_USER_IRQ (NUM_IRQS - NUM_USER_IRQS)
#define VTABLE_FIRST_IRQ 16

#endif

