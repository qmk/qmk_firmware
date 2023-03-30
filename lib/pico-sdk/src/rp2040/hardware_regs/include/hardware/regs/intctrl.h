/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _INTCTRL_H_
#define _INTCTRL_H_

#define TIMER_IRQ_0 0
#define TIMER_IRQ_1 1
#define TIMER_IRQ_2 2
#define TIMER_IRQ_3 3
#define PWM_IRQ_WRAP 4
#define USBCTRL_IRQ 5
#define XIP_IRQ 6
#define PIO0_IRQ_0 7
#define PIO0_IRQ_1 8
#define PIO1_IRQ_0 9
#define PIO1_IRQ_1 10
#define DMA_IRQ_0 11
#define DMA_IRQ_1 12
#define IO_IRQ_BANK0 13
#define IO_IRQ_QSPI 14
#define SIO_IRQ_PROC0 15
#define SIO_IRQ_PROC1 16
#define CLOCKS_IRQ 17
#define SPI0_IRQ 18
#define SPI1_IRQ 19
#define UART0_IRQ 20
#define UART1_IRQ 21
#define ADC_IRQ_FIFO 22
#define I2C0_IRQ 23
#define I2C1_IRQ 24
#define RTC_IRQ 25

#define isr_timer_0 isr_irq0
#define isr_timer_1 isr_irq1
#define isr_timer_2 isr_irq2
#define isr_timer_3 isr_irq3
#define isr_pwm_wrap isr_irq4
#define isr_usbctrl isr_irq5
#define isr_xip isr_irq6
#define isr_pio0_0 isr_irq7
#define isr_pio0_1 isr_irq8
#define isr_pio1_0 isr_irq9
#define isr_pio1_1 isr_irq10
#define isr_dma_0 isr_irq11
#define isr_dma_1 isr_irq12
#define isr_io_bank0 isr_irq13
#define isr_io_qspi isr_irq14
#define isr_sio_proc0 isr_irq15
#define isr_sio_proc1 isr_irq16
#define isr_clocks isr_irq17
#define isr_spi0 isr_irq18
#define isr_spi1 isr_irq19
#define isr_uart0 isr_irq20
#define isr_uart1 isr_irq21
#define isr_adc_fifo isr_irq22
#define isr_i2c0 isr_irq23
#define isr_i2c1 isr_irq24
#define isr_rtc isr_irq25

#endif // _INTCTRL_H_
