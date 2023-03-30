/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _CMSIS_RENAME_EXCEPTIONS_H
#define _CMSIS_RENAME_EXCEPTIONS_H

#if LIB_CMSIS_CORE
// PICO_CONFIG: PICO_CMSIS_RENAME_EXCEPTIONS, Whether to rename SDK exceptions such as isr_nmi to their CMSIS equivalent i.e. NMI_Handler, type=bool, default=1, group=cmsis_core

// Note that since this header is included at the config stage, if you wish to override this you should do so via build compiler define
#ifndef PICO_CMSIS_RENAME_EXCEPTIONS
#define PICO_CMSIS_RENAME_EXCEPTIONS 1
#endif

#if PICO_CMSIS_RENAME_EXCEPTIONS
#define isr_nmi NMI_Handler
#define isr_hardfault HardFault_Handler
#define isr_svcall SVC_Handler
#define isr_pendsv PendSV_Handler
#define isr_systick SysTick_Handler
#define isr_irq0 TIMER_IRQ_0_Handler
#define isr_irq1 TIMER_IRQ_1_Handler
#define isr_irq2 TIMER_IRQ_2_Handler
#define isr_irq3 TIMER_IRQ_3_Handler
#define isr_irq4 PWM_IRQ_WRAP_Handler
#define isr_irq5 USBCTRL_IRQ_Handler
#define isr_irq6 XIP_IRQ_Handler
#define isr_irq7 PIO0_IRQ_0_Handler
#define isr_irq8 PIO0_IRQ_1_Handler
#define isr_irq9 PIO1_IRQ_0_Handler
#define isr_irq10 PIO1_IRQ_1_Handler
#define isr_irq11 DMA_IRQ_0_Handler
#define isr_irq12 DMA_IRQ_1_Handler
#define isr_irq13 IO_IRQ_BANK0_Handler
#define isr_irq14 IO_IRQ_QSPI_Handler
#define isr_irq15 SIO_IRQ_PROC0_Handler
#define isr_irq16 SIO_IRQ_PROC1_Handler
#define isr_irq17 CLOCKS_IRQ_Handler
#define isr_irq18 SPI0_IRQ_Handler
#define isr_irq19 SPI1_IRQ_Handler
#define isr_irq20 UART0_IRQ_Handler
#define isr_irq21 UART1_IRQ_Handler
#define isr_irq22 ADC_IRQ_FIFO_Handler
#define isr_irq23 I2C0_IRQ_Handler
#define isr_irq24 I2C1_IRQ_Handler
#define isr_irq25 RTC_IRQ_Handler
#endif

#endif
#endif /* _CMSIS_RENAME_EXCEPTIONS_H */
