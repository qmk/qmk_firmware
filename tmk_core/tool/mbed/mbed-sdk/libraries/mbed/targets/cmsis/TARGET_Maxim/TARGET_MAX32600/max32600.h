/*******************************************************************************
 * Copyright (C) 2015 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *******************************************************************************
 */

#ifndef _MAX32600_H_
#define _MAX32600_H_

#include <stdint.h>

typedef enum IRQn_Type {
    NonMaskableInt_IRQn = -14,
    HardFault_IRQn = -13,
    MemoryManagement_IRQn = -12,
    BusFault_IRQn = -11,
    UsageFault_IRQn = -10,
    SVCall_IRQn = -5,
    DebugMonitor_IRQn = -4,
    PendSV_IRQn = -2,
    SysTick_IRQn = -1,

    /* Externals interrupts */
    UART0_IRQn = 0,      /* 16:01 UART0 */
    UART1_IRQn,          /* 17: 2 UART1 */
    I2CM0_IRQn,          /* 18: 3 I2C Master 0 */
    I2CS_IRQn,           /* 19: 4 I2C Slave */
    USB_IRQn,            /* 20: 5 USB */
    PMU_IRQn,            /* 21: 6 DMA */
    AFE_IRQn,            /* 22: 7 AFE */
    MAA_IRQn,            /* 23: 8 MAA */
    AES_IRQn,            /* 24: 9 AES */
    SPI0_IRQn,           /* 25:10 SPI0 */
    SPI1_IRQn,           /* 26:11 SPI1 */
    SPI2_IRQn,           /* 27:12 SPI2 */
    TMR0_IRQn,           /* 28:13 Timer32-0 */
    TMR1_IRQn,           /* 29:14 Timer32-1 */
    TMR2_IRQn,           /* 30:15 Timer32-1 */
    TMR3_IRQn,           /* 31:16 Timer32-2 */
    RSVD0_IRQn,          /* 32:17 RSVD */
    RSVD1_IRQn,          /* 33:18 RSVD */
    DAC0_IRQn,           /* 34:19 DAC0  (12-bit DAC) */
    DAC1_IRQn,           /* 35:20 DAC1  (12-bit DAC) */
    DAC2_IRQn,           /* 36:21 DAC2  (8-bit DAC) */
    DAC3_IRQn,           /* 37:22 DAC3  (8-bit DAC) */
    ADC_IRQn,            /* 38:23 ADC */
    FLC_IRQn,            /* 39:24 Flash Controller */
    PWRMAN_IRQn,         /* 40:25 PWRMAN */
    CLKMAN_IRQn,         /* 41:26 CLKMAN */
    RTC0_IRQn,           /* 42:27 RTC INT0 */
    RTC1_IRQn,           /* 43:28 RTC INT1 */
    RTC2_IRQn,           /* 44:29 RTC INT2 */
    RTC3_IRQn,           /* 45:30 RTC INT3 */
    WDT0_IRQn,           /* 46:31 WATCHDOG0 */
    WDT0_P_IRQn,         /* 47:32 WATCHDOG0 PRE-WINDOW */
    WDT1_IRQn,           /* 48:33 WATCHDOG1 */
    WDT1_P_IRQn,         /* 49:34 WATCHDOG1 PRE-WINDOW */
    GPIO_P0_IRQn,        /* 50:35 GPIO Port 0  */
    GPIO_P1_IRQn,        /* 51:36 GPIO Port 1  */
    GPIO_P2_IRQn,        /* 52:37 GPIO Port 2  */
    GPIO_P3_IRQn,        /* 53:38 GPIO Port 3  */
    GPIO_P4_IRQn,        /* 54:39 GPIO Port 4  */
    GPIO_P5_IRQn,        /* 55:40 GPIO Port 5  */
    GPIO_P6_IRQn,        /* 56:41 GPIO Port 6  */
    GPIO_P7_IRQn,        /* 57:42 GPIO Port 7  */
    TMR16_0_IRQn,        /* 58:43 Timer16-s0 */
    TMR16_1_IRQn,        /* 59:44 Timer16-s1 */
    TMR16_2_IRQn,        /* 60:45 Timer16-s2 */
    TMR16_3_IRQn,        /* 61:46 Timer16-s3 */
    I2CM1_IRQn,          /* 62:47 I2C Master 1 */
    MXC_IRQ_EXT_COUNT,
} IRQn_Type;

#define MXC_IRQ_COUNT (MXC_IRQ_EXT_COUNT + 16)

/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

#define __NVIC_PRIO_BITS          3         /*!< Number of Bits used for Priority Levels         */

#include <core_cm3.h>                       /* Processor and core peripherals */
#include "system_max32600.h"                /* System Header */

/* ================================================================================ */
/* ==================       Device Specific Memory Section       ================== */
/* ================================================================================ */

#define MXC_FLASH_MEM_BASE    0x00000000UL
#define MXC_FLASH_PAGE_SIZE   0x1000        // 256 x 128b = 4KB
#define MXC_FLASH_MEM_SIZE    0x00040000UL
#define MXC_SYS_MEM_BASE      0x20000000UL

/* ================================================================================ */
/* ================       Device Specific Peripheral Section       ================ */
/* ================================================================================ */

/*******************************************************************************/
/*                                            General Purpose I/O Ports (GPIO) */

#define MXC_BASE_GPIO                   ((uint32_t)0x40000000UL)
#define MXC_GPIO                        ((mxc_gpio_regs_t *)MXC_BASE_GPIO)
#define MXC_BASE_GPIO_BITBAND           ((uint32_t)0x42000000UL)

#define MXC_GPIO_GET_IRQ(i)             (((unsigned int)i) + GPIO_P0_IRQn)


/*******************************************************************************/
/*                                                      Pulse Train Generation */

#define MXC_CFG_PT_INSTANCES             (13)

#define MXC_BASE_PTG                     ((uint32_t)0x40001000UL)
#define MXC_PTG                          ((mxc_ptg_regs_t *)MXC_BASE_PTG)
#define MXC_BASE_PT                      ((uint32_t)0x40001008UL)
#define MXC_PT                           ((mxc_pt_regs_t *)MXC_BASE_PT)
#define MXC_BASE_PT0                     ((uint32_t)0x40001008UL)
#define MXC_PT0                          ((mxc_pt_regs_t *)MXC_BASE_PT0)
#define MXC_BASE_PT1                     ((uint32_t)0x40001010UL)
#define MXC_PT1                          ((mxc_pt_regs_t *)MXC_BASE_PT1)
#define MXC_BASE_PT2                     ((uint32_t)0x40001018UL)
#define MXC_PT2                          ((mxc_pt_regs_t *)MXC_BASE_PT2)
#define MXC_BASE_PT3                     ((uint32_t)0x40001020UL)
#define MXC_PT3                          ((mxc_pt_regs_t *)MXC_BASE_PT3)
#define MXC_BASE_PT4                     ((uint32_t)0x40001028UL)
#define MXC_PT4                          ((mxc_pt_regs_t *)MXC_BASE_PT4)
#define MXC_BASE_PT5                     ((uint32_t)0x40001030UL)
#define MXC_PT5                          ((mxc_pt_regs_t *)MXC_BASE_PT5)
#define MXC_BASE_PT6                     ((uint32_t)0x40001038UL)
#define MXC_PT6                          ((mxc_pt_regs_t *)MXC_BASE_PT6)
#define MXC_BASE_PT7                     ((uint32_t)0x40001040UL)
#define MXC_PT7                          ((mxc_pt_regs_t *)MXC_BASE_PT7)
#define MXC_BASE_PT8                     ((uint32_t)0x40001048UL)
#define MXC_PT8                          ((mxc_pt_regs_t *)MXC_BASE_PT8)
#define MXC_BASE_PT9                     ((uint32_t)0x40001050UL)
#define MXC_PT9                          ((mxc_pt_regs_t *)MXC_BASE_PT9)
#define MXC_BASE_PT10                    ((uint32_t)0x40001058UL)
#define MXC_PT10                         ((mxc_pt_regs_t *)MXC_BASE_PT10)
#define MXC_BASE_PT11                    ((uint32_t)0x40001060UL)
#define MXC_PT11                         ((mxc_pt_regs_t *)MXC_BASE_PT11)

/*                                       PT12, PT13, PT14 are not used         */

/*******************************************************************************/
/*                                                        CRC-16/CRC-32 Engine */

#define MXC_BASE_CRC                    ((uint32_t)0x40010000UL)
#define MXC_CRC_REGS                    ((mxc_crc_regs_t *)MXC_BASE_CRC)

#define MXC_BASE_CRC_DATA               ((uint32_t)0x4010B000UL)
#define MXC_CRC_DATA                    ((mxc_crc_data_regs_t *)MXC_BASE_CRC_DATA)

/*******************************************************************************/
/*                                                 Trust Protection Unit (TPU) */

#define MXC_BASE_TPU                     ((uint32_t)0x40011000UL)
#define MXC_TPU                          ((mxc_tpu_regs_t *)MXC_BASE_TPU)

#define MXC_BASE_TPU_TSR                 ((uint32_t)0x40011C00UL)
#define MXC_TPU_TSR                      ((mxc_tpu_tsr_regs_t *)MXC_BASE_TPU_TSR)

/*******************************************************************************/
/*                                                    AES Cryptographic Engine */

#define MXC_BASE_AES                     ((uint32_t)0x40011400UL)
#define MXC_AES                          ((mxc_aes_regs_t *)MXC_BASE_AES)

#define MXC_BASE_AES_MEM                 ((uint32_t)0x4010A000UL)
#define MXC_AES_MEM                      ((mxc_aes_mem_regs_t *)MXC_BASE_AES_MEM)


/*******************************************************************************/
/*                                                    MAA Cryptographic Engine */

#define MXC_BASE_MAA                     ((uint32_t)0x40011800UL)
#define MXC_MAA                          ((mxc_maa_regs_t *)MXC_BASE_MAA)

#define MXC_BASE_MAA_MEM                 ((uint32_t)0x4010A800UL)
#define MXC_MAA_MEM                      ((mxc_maa_mem_regs_t *)MXC_BASE_MAA_MEM)

/*******************************************************************************/
/*                                                    32-Bit PWM Timer/Counter */

#define MXC_CFG_TMR_INSTANCES            (4)

#define MXC_BASE_TMR0                    ((uint32_t)0x40012000UL)
#define MXC_BASE_TMR0_BITBAND            ((uint32_t)0x42240000UL)
#define MXC_TMR0                         ((mxc_tmr_regs_t *) MXC_BASE_TMR0)

#define MXC_BASE_TMR1                    ((uint32_t)0x40013000UL)
#define MXC_BASE_TMR1_BITBAND            ((uint32_t)0x42260000UL)
#define MXC_TMR1                         ((mxc_tmr_regs_t *) MXC_BASE_TMR1)

#define MXC_BASE_TMR2                    ((uint32_t)0x40014000UL)
#define MXC_BASE_TMR2_BITBAND            ((uint32_t)0x42280000UL)
#define MXC_TMR2                         ((mxc_tmr_regs_t *) MXC_BASE_TMR2)

#define MXC_BASE_TMR3                    ((uint32_t)0x40015000UL)
#define MXC_BASE_TMR3_BITBAND            ((uint32_t)0x422A0000UL)
#define MXC_TMR3                         ((mxc_tmr_regs_t *) MXC_BASE_TMR3)


#define MXC_TMR_GET_IRQ_32(i)            ((i) == 0 ? TMR0_IRQn :    \
                                          (i) == 1 ? TMR1_IRQn :    \
                                          (i) == 2 ? TMR2_IRQn :    \
                                          (i) == 3 ? TMR3_IRQn : 0)

#define MXC_TMR_GET_IRQ_16(i)            ((i) == 0 ? TMR0_IRQn :    \
                                          (i) == 1 ? TMR1_IRQn :    \
                                          (i) == 2 ? TMR2_IRQn :    \
                                          (i) == 3 ? TMR3_IRQn :    \
                                          (i) == 4 ? TMR16_0_IRQn :    \
                                          (i) == 5 ? TMR16_1_IRQn :    \
                                          (i) == 6 ? TMR16_2_IRQn :    \
                                          (i) == 7 ? TMR16_3_IRQn : 0)

#define MXC_TMR_GET_BASE(i)              ((i) == 0 ? MXC_BASE_TMR0 : \
                                          (i) == 1 ? MXC_BASE_TMR1 : \
                                          (i) == 2 ? MXC_BASE_TMR2 : \
                                          (i) == 3 ? MXC_BASE_TMR3 : 0)

#define MXC_TMR_GET_TMR(i)               ((i) == 0 ? MXC_TMR0 : \
                                          (i) == 1 ? MXC_TMR1 : \
                                          (i) == 2 ? MXC_TMR2 : \
                                          (i) == 3 ? MXC_TMR3 : 0)
/*******************************************************************************/
/*                                                              Watchdog Timer */

#define MXC_CFG_WDT_INSTANCES            (2)

#define MXC_BASE_WDT0                    ((uint32_t)0x40021000UL)
#define MXC_BASE_WDT0_BITBAND            ((uint32_t)0x42420000UL)
#define MXC_WDT0                         ((mxc_wdt_regs_t *)MXC_BASE_WDT0)

#define MXC_BASE_WDT1                    ((uint32_t)0x40022000UL)
#define MXC_BASE_WDT1_BITBAND            ((uint32_t)0x42440000UL)
#define MXC_WDT1                         ((mxc_wdt_regs_t *)MXC_BASE_WDT1)

#define MXC_WDT_GET_IRQ(i)               ((i) == 0 ? WDT0_IRQn : \
                                          (i) == 1 ? WDT1_IRQn : 0)

#define MXC_WDT_GET_IRQ_P(i)             ((i) == 0 ? WDT0_P_IRQn : \
                                          (i) == 1 ? WDT1_P_IRQn : 0)

#define MXC_WDT_GET_BASE(i)              ((i) == 0 ? MXC_BASE_WDT0 : \
                                          (i) == 1 ? MXC_BASE_WDT1 : 0)

#define MXC_WDT_GET_WDT(i)               ((i) == 0 ? MXC_WDT0 : \
                                          (i) == 1 ? MXC_WDT1 : 0)

/*******************************************************************************/
/*                                                               SPI Interface */

#define MXC_CFG_SPI_INSTANCES            (3)
#define MXC_CFG_SPI_FIFO_DEPTH           (16)

#define MXC_BASE_SPI0                    ((uint32_t)0x40030000UL)
#define MXC_SPI0                         ((mxc_spi_regs_t *)MXC_BASE_SPI0)

#define MXC_BASE_SPI0_TXFIFO             ((uint32_t)0x40100000UL)
#define MXC_SPI0_TXFIFO                  ((mxc_spi_txfifo_regs_t *)MXC_BASE_SPI0_TXFIFO)
#define MXC_BASE_SPI0_RXFIFO             ((uint32_t)0x40100800UL)
#define MXC_SPI0_RXFIFO                  ((mxc_spi_rxfifo_regs_t *)MXC_BASE_SPI0_RXFIFO)

#define MXC_BASE_SPI1                    ((uint32_t)0x40031000UL)
#define MXC_SPI1                         ((mxc_spi_regs_t *)MXC_BASE_SPI1)

#define MXC_BASE_SPI1_TXFIFO             ((uint32_t)0x40101000UL)
#define MXC_SPI1_TXFIFO                  ((mxc_spi_txfifo_regs_t *)MXC_BASE_SPI1_TXFIFO)
#define MXC_BASE_SPI1_RXFIFO             ((uint32_t)0x40101800UL)
#define MXC_SPI1_RXFIFO                  ((mxc_spi_rxfifo_regs_t *)MXC_BASE_SPI1_RXFIFO)

#define MXC_BASE_SPI2                    ((uint32_t)0x40032000UL)
#define MXC_SPI2                         ((mxc_spi_regs_t *)MXC_BASE_SPI2)

#define MXC_BASE_SPI2_TXFIFO             ((uint32_t)0x40102000UL)
#define MXC_SPI2_TXFIFO                  ((mxc_spi_txfifo_regs_t *)MXC_BASE_SPI2_TXFIFO)
#define MXC_BASE_SPI2_RXFIFO             ((uint32_t)0x40102800UL)
#define MXC_SPI2_RXFIFO                  ((mxc_spi_rxfifo_regs_t *)MXC_BASE_SPI2_RXFIFO)


#define MXC_SPI_GET_IRQ(i)               ((i) == 0 ? SPI0_IRQn :       \
                                          (i) == 1 ? SPI1_IRQn :       \
                                          (i) == 2 ? SPI2_IRQn : 0)

#define MXC_SPI_GET_BASE(i)              ((i) == 0 ? MXC_BASE_SPI0 :      \
                                          (i) == 1 ? MXC_BASE_SPI1 :      \
                                          (i) == 2 ? MXC_BASE_SPI2 : 0)

#define MXC_SPI_GET_SPI(i)               ((i) == 0 ? MXC_SPI0 :      \
                                          (i) == 1 ? MXC_SPI1 :      \
                                          (i) == 2 ? MXC_SPI2 : 0)

#define MXC_SPI_GET_RXFIFO(i)            ((i) == 0 ? MXC_SPI0_RXFIFO :      \
                                          (i) == 1 ? MXC_SPI1_RXFIFO :      \
                                          (i) == 2 ? MXC_SPI2_RXFIFO : 0)

#define MXC_SPI_GET_TXFIFO(i)            ((i) == 0 ? MXC_SPI0_TXFIFO :      \
                                          (i) == 1 ? MXC_SPI1_TXFIFO :      \
                                          (i) == 2 ? MXC_SPI2_TXFIFO : 0)

#define MXC_SPI_INSTANCE_TO_BASE(instance) (((uint32_t)(instance) << 12) + MXC_BASE_SPI0)
#define MXC_SPI_BASE_TO_INSTANCE(base)     (((uint32_t)(base) & 0x00003000) >> 12)


/*******************************************************************************/
/*                                                              UART Interface */

#define MXC_CFG_UART_INSTANCES           (2)

#define MXC_BASE_UART0                   ((uint32_t)0x40038000UL)
#define MXC_BASE_UART0_BITBAND           ((uint32_t)0x42700000UL)
#define MXC_UART0                        ((mxc_uart_regs_t *)MXC_BASE_UART0)

#define MXC_BASE_UART1                   ((uint32_t)0x40039000UL)
#define MXC_BASE_UART1_BITBAND           ((uint32_t)0x42720000UL)
#define MXC_UART1                        ((mxc_uart_regs_t *)MXC_BASE_UART1)


#define MXC_UART_GET_IRQ(i)              ((i) == 0 ? UART0_IRQn :      \
                                          (i) == 1 ? UART1_IRQn : 0)

#define MXC_UART_GET_BASE(i)             ((i) == 0 ? MXC_BASE_UART0 :     \
                                          (i) == 1 ? MXC_BASE_UART1 : 0)

#define MXC_UART_GET_UART(i)             ((i) == 0 ? MXC_UART0 :     \
                                          (i) == 1 ? MXC_UART1 : 0)

#define MXC_UART_INSTANCE_TO_BASE(instance) (((uint32_t)(instance) << 12) + MXC_BASE_UART0)
#define MXC_UART_BASE_TO_INSTANCE(base)     (((uint32_t)(base) & 0x00001000) >> 12)


/*******************************************************************************/
/*                                                        I2C Master Interface */

#define MXC_CFG_I2CM_INSTANCES           (2)

#define MXC_BASE_I2CM0                   ((uint32_t)0x40040000UL)
#define MXC_BASE_I2CM0_BITBAND           ((uint32_t)0x42800000UL)
#define MXC_I2CM0                        ((mxc_i2cm_regs_t *)MXC_BASE_I2CM0)
#define MXC_BASE_I2CM0_TX_FIFO           ((uint32_t)0x40103000UL)
#define MXC_BASE_I2CM0_RX_FIFO           ((uint32_t)0x40103800UL)

#define MXC_BASE_I2CM1                   ((uint32_t)0x40042000UL)
#define MXC_BASE_I2CM1_BITBAND           ((uint32_t)0x42840000UL)
#define MXC_I2CM1                        ((mxc_i2cm_regs_t *)MXC_BASE_I2CM1)
#define MXC_BASE_I2CM1_TX_FIFO           ((uint32_t)0x4010D000UL)
#define MXC_BASE_I2CM1_RX_FIFO           ((uint32_t)0x4010D800UL)

#define MXC_I2CM_GET_IRQ(i)              ((i) == 0 ? I2CM0_IRQn :      \
                                          (i) == 1 ? I2CM1_IRQn : 0)

#define MXC_I2CM_GET_BASE(i)             ((i) == 0 ? MXC_BASE_I2CM0 :     \
                                          (i) == 1 ? MXC_BASE_I2CM1 : 0)

#define MXC_I2CM_GET_I2CM(i)             ((i) == 0 ? MXC_I2CM0 :     \
                                          (i) == 1 ? MXC_I2CM1 : 0)

#define MXC_I2CM_GET_BASE_TX_FIFO(i)     ((i) == 0 ? MXC_BASE_I2CM0_TX_FIFO :  \
                                          (i) == 1 ? MXC_BASE_I2CM1_TX_FIFO : 0)

#define MXC_I2CM_GET_BASE_RX_FIFO(i)     ((i) == 0 ? MXC_BASE_I2CM0_RX_FIFO :  \
                                          (i) == 1 ? MXC_BASE_I2CM1_RX_FIFO : 0)

#define MXC_I2CM_INSTANCE_TO_BASE(instance)   (((uint32_t)(instance) << 13) + MXC_BASE_I2CM0)
#define MXC_I2CM_BASE_TO_INSTANCE(base)       (((uint32_t)(base) & 0x00002000) >> 13)


/*******************************************************************************/
/*                                                         I2C Slave Interface */

#define MXC_CFG_I2CS_INSTANCES           (1)

#define MXC_BASE_I2CS0                   ((uint32_t)0x40041000UL)
#define MXC_BASE_I2CS0_BITBAND           ((uint32_t)0x42820000UL)
#define MXC_I2CS0                        ((mxc_i2cs_regs_t *)MXC_BASE_I2CS0)

#define MXC_BASE_I2CS0_FIFO              ((uint32_t)0x40104000UL)
#define MXC_I2CS0_FIFO                   ((mxc_i2cs_fifo_regs_t *)MXC_BASE_I2CS0)



/*******************************************************************************/
/*                                                                        DACs */

#define MXC_CFG_DAC_INSTANCES            (4)
#define MXC_CFG_DAC_FIFO_DEPTH           (32)

#define MXC_BASE_DAC0                    ((uint32_t)0x40050000UL)
#define MXC_DAC0                         ((mxc_dac_regs_t *)MXC_BASE_DAC0)
#define MXC_BASE_DAC0_FIFO               ((uint32_t)0x40105000UL)
#define MXC_DAC0_FIFO                    ((mxc_dac_fifo_regs_t *)MXC_BASE_DAC0_FIFO)
#define MXC_DAC0_WIDTH                   ((uint8_t)(2))

#define MXC_BASE_DAC1                    ((uint32_t)0x40051000UL)
#define MXC_DAC1                         ((mxc_dac_regs_t *)MXC_BASE_DAC1)
#define MXC_BASE_DAC1_FIFO               ((uint32_t)0x40106000UL)
#define MXC_DAC1_FIFO                    ((mxc_dac_fifo_regs_t *)MXC_BASE_DAC1_FIFO)
#define MXC_DAC1_WIDTH                   ((uint8_t)(2))

#define MXC_BASE_DAC2                    ((uint32_t)0x40052000UL)
#define MXC_DAC2                         ((mxc_dac_regs_t *)MXC_BASE_DAC2)
#define MXC_BASE_DAC2_FIFO               ((uint32_t)0x40107000UL)
#define MXC_DAC2_FIFO                    ((mxc_dac_fifo_regs_t *)MXC_BASE_DAC2_FIFO)
#define MXC_DAC2_WIDTH                   ((uint8_t)(1))

#define MXC_BASE_DAC3                    ((uint32_t)0x40053000UL)
#define MXC_DAC3                         ((mxc_dac_regs_t *)MXC_BASE_DAC3)
#define MXC_BASE_DAC3_FIFO               ((uint32_t)0x40108000UL)
#define MXC_DAC3_FIFO                    ((mxc_dac_fifo_regs_t *)MXC_BASE_DAC3_FIFO)
#define MXC_DAC3_WIDTH                   ((uint8_t)(1))


#define MXC_DAC_GET_IRQ(i)               ((i) == 0 ? DAC0_IRQn :     \
                                          (i) == 1 ? DAC1_IRQn :     \
                                          (i) == 2 ? DAC2_IRQn :     \
                                          (i) == 3 ? DAC3_IRQn : 0)


#define MXC_DAC_GET_BASE(i) (i == 0 ? MXC_BASE_DAC0 : \
                             i == 1 ? MXC_BASE_DAC1 : \
                             i == 2 ? MXC_BASE_DAC2 : \
                             i == 3 ? MXC_BASE_DAC3 : 0)

#define MXC_DAC_GET_FIFO(i) (i == 0 ? MXC_BASE_DAC0_FIFO : \
                             i == 1 ? MXC_BASE_DAC1_FIFO : \
                             i == 2 ? MXC_BASE_DAC2_FIFO  : \
                             i == 3 ? MXC_BASE_DAC3_FIFO  : 0)

#define MXC_DAC_GET_PMU_FIFO_IRQ(i) (i == 0 ? PMU_IRQ_DAC0_FIFO_AE : \
                                     i == 1 ? PMU_IRQ_DAC1_FIFO_AE : \
                                     i == 2 ? PMU_IRQ_DAC2_FIFO_AE  : \
                                     i == 3 ? PMU_IRQ_DAC3_FIFO_AE  : 0)

#define MXC_DAC_GET_DAC(i)  (i == 0 ? MXC_DAC0 : \
                             i == 1 ? MXC_DAC1 : \
                             i == 2 ? MXC_DAC2 : \
                             i == 3 ? MXC_DAC3 : 0)

#define MXC_DAC_GET_WIDTH(i)  (i == 0 ? MXC_DAC0_WIDTH : \
                               i == 1 ? MXC_DAC1_WIDTH : \
                               i == 2 ? MXC_DAC2_WIDTH : \
                               i == 3 ? MXC_DAC3_WIDTH : 0)


/*******************************************************************************/
/*                                                            Analog Front End */

#define MXC_BASE_AFE                     ((uint32_t)0x4005401CUL)
#define MXC_AFE                          ((mxc_afe_regs_t *)MXC_BASE_AFE)



/*******************************************************************************/
/*                                                                         ADC */

#define MXC_CFG_ADC_FIFO_DEPTH           ((uint32_t)(32))

#define MXC_BASE_ADC                     ((uint32_t)0x40054000UL)
#define MXC_ADC                          ((mxc_adc_regs_t *)MXC_BASE_ADC)

#define MXC_BASE_ADCCFG                  ((uint32_t)0x40054038UL)
#define MXC_ADCCFG                       ((mxc_adccfg_regs_t *)MXC_BASE_ADCCFG)

#define MXC_BASE_ADC_FIFO                ((uint32_t)0x40109000UL)
#define MXC_ADC_FIFO                     ((mxc_adc_fifo_regs_t *)MXC_BASE_ADC_FIFO)



/*******************************************************************************/
/*                                                                         LCD */
#define MXC_BASE_LCD                     ((uint32_t)0x40060000)
#define MXC_LCD                          ((mxc_lcd_regs_t *)MXC_BASE_LCD)

/*******************************************************************************/
/*                  Peripheral Management Unit (PMU) - formerly DMA Controller */

#define MXC_CFG_PMU_CHANNELS             (6)

#define MXC_BASE_PMU0                    ((uint32_t)0x40070000UL)
#define MXC_PMU0                         ((mxc_pmu_regs_t *)MXC_BASE_PMU0)
#define MXC_BASE_PMU1                    ((uint32_t)0x40070020UL)
#define MXC_PMU1                         ((mxc_pmu_regs_t *)MXC_BASE_PMU1)
#define MXC_BASE_PMU2                    ((uint32_t)0x40070040UL)
#define MXC_PMU2                         ((mxc_pmu_regs_t *)MXC_BASE_PMU2)
#define MXC_BASE_PMU3                    ((uint32_t)0x40070060UL)
#define MXC_PMU3                         ((mxc_pmu_regs_t *)MXC_BASE_PMU3)
#define MXC_BASE_PMU4                    ((uint32_t)0x40070080UL)
#define MXC_PMU4                         ((mxc_pmu_regs_t *)MXC_BASE_PMU4)
#define MXC_BASE_PMU5                    ((uint32_t)0x400700A0UL)
#define MXC_PMU5                         ((mxc_pmu_regs_t *)MXC_BASE_PMU5)

#define MXC_BASE_PMU_BITBAND            ((uint32_t)0x42E00000UL)
#define MXC_BASE_PMU_BITBAND_CHOFFSET   ((uint32_t)0x00000400UL)
/*******************************************************************************/

typedef enum {
    PMU_IRQ_DAC0_FIFO_AE,
    PMU_IRQ_DAC1_FIFO_AE,
    PMU_IRQ_DAC2_FIFO_AE,
    PMU_IRQ_DAC3_FIFO_AE,
    PMU_IRQ_DAC0_DONE,
    PMU_IRQ_DAC1_DONE,
    PMU_IRQ_DAC2_DONE,
    PMU_IRQ_DAC3_DONE,
    PMU_IRQ_ADC_FIFO_AF,
    PMU_IRQ_ADC_DONE,
    PMU_IRQ_I2C_MST0_DONE,
    PMU_IRQ_I2C_MST1_DONE,
    PMU_IRQ_SPI0_RSLTS_DONE,
    PMU_IRQ_SPI1_RSLTS_DONE,
    PMU_IRQ_SPI2_RSLTS_DONE,
    PMU_IRQ_MAA_DONE,
    PMU_IRQ_SPI0_TX_FIFO_AE,
    PMU_IRQ_SPI0_RSLTS_FIFO_AF,
    PMU_IRQ_SPI1_TX_FIFO_AE,
    PMU_IRQ_SPI1_RSLTS_FIFO_AF,
    PMU_IRQ_SPI2_TX_FIFO_AE,
    PMU_IRQ_SPI3_RSLTS_FIFO_AF,
    PMU_IRQ_I2C_MST0_TRANS_FIFO,
    PMU_IRQ_I2C_MST0_RSLT_FIFO,
    PMU_IRQ_I2C_MST1_TRANS_FIFO,
    PMU_IRQ_I2C_MST2_RSLT_FIFO,
    PMU_IRQ_I2C_SLV_TRANS_FIFO,
    PMU_IRQ_I2C_SLV_RSLT_FIFO,
    PMU_IRQ_UART0_TX_FIFO,
    PMU_IRQ_UART0_RX_FIFO,
    PMU_IRQ_UART1_TX_FIFO,
    PMU_IRQ_UART1_RX_FIFO,
    PMU_IRQ_SPI0_EXCP,
    PMU_IRQ_SPI1_EXCP,
    PMU_IRQ_SPI2_EXCP,
    PMU_IRQ_RSVD0,
    PMU_IRQ_I2C_MST0_EXCP,
    PMU_IRQ_I2C_MST1_EXCP,
    PMU_IRQ_I2C_SLV_EXCP,
    PMU_IRQ_RSVD1,
    PMU_IRQ_GPIO0,
    PMU_IRQ_GPIO1,
    PMU_IRQ_GPIO2,
    PMU_IRQ_GPIO3,
    PMU_IRQ_GPIO4,
    PMU_IRQ_GPIO5,
    PMU_IRQ_GPIO6,
    PMU_IRQ_GPIO7,
    PMU_IRQ_GPIO8,
    PMU_IRQ_AFE_COMP_NMI,
    PMU_IRQ_AES_ENGINE,
} pmu_int_mask_t;

/*******************************************************************************/
/*                                                                         USB */

#define MXC_BASE_USB                     ((uint32_t)0x4010C000UL)
#define MXC_USB                          ((mxc_usb_regs_t *)MXC_BASE_USB)

#define MXC_USB_MAX_PACKET               (64)
#define MXC_USB_NUM_EP                   (8)


/*******************************************************************************/
/*                                                Instruction Cache Controller */

#define MXC_BASE_ICC                     ((uint32_t)0x40080000UL)
#define MXC_ICC                          ((mxc_icc_regs_t *)MXC_BASE_ICC)

/*                                                              System Manager */

#define MXC_BASE_SYSMAN                 ((uint32_t)0x40090000UL)

/*******************************************************************************/
/*                                                               Clock Manager */

#define MXC_BASE_CLKMAN                  ((uint32_t)0x40090400UL)
#define MXC_CLKMAN                       ((mxc_clkman_regs_t *)MXC_BASE_CLKMAN)


/*******************************************************************************/
/*                                                               Power Manager */

#define MXC_BASE_PWRMAN                  ((uint32_t)0x40090800UL)
#define MXC_PWRMAN                       ((mxc_pwrman_regs_t *)MXC_BASE_PWRMAN)

/*******************************************************************************/
/*                                                                 I/O Manager */

#define MXC_BASE_IOMAN                   ((uint32_t)0x40090C00UL)
#define MXC_IOMAN                        ((mxc_ioman_regs_t *)MXC_BASE_IOMAN)


/*******************************************************************************/
/*                                                           RTC: Timer/Alarms */

#define MXC_BASE_RTCTMR                 ((uint32_t)0x40090A00UL)
#define MXC_RTCTMR                       ((mxc_rtctmr_regs_t *)MXC_BASE_RTCTMR)

#define MXC_RTCTMR_GET_IRQ(i) (i == 0 ? RTC0_IRQn :    \
                               i == 1 ? RTC1_IRQn :    \
                               i == 2 ? RTC2_IRQn :    \
                               i == 3 ? RTC3_IRQn : 0)

#define MXC_BASE_RTCCFG                  ((uint32_t)0x40090A70UL)
#define MXC_RTCCFG                       ((mxc_rtccfg_regs_t *)MXC_BASE_RTCCFG)
/*******************************************************************************/
/*                                                        RTC: Power Sequencer */

#define MXC_BASE_PWRSEQ                  ((uint32_t)0x40090A30UL)
#define MXC_PWRSEQ                       ((mxc_pwrseq_regs_t *)MXC_BASE_PWRSEQ)

/*******************************************************************************/
/*                                                       Trim Shadow Registers */

#define MXC_BASE_TRIM                    ((uint32_t)0x400E0000UL)
#define MXC_TRIM                         ((mxc_ftr_regs_t *)MXC_BASE_TRIM)

/*******************************************************************************/
/*                                          Flash Memory Controller / Security */

#define MXC_BASE_FLC                     ((uint32_t)0x400F0000UL)
#define MXC_FLC                          ((mxc_flc_regs_t *)MXC_BASE_FLC)
#define MXC_BASE_FLC_BITBAND             ((uint32_t)0x43E00000UL)
#define MXC_FLC_PAGE_SIZE_SHIFT          11
#define MXC_FLC_PAGE_SIZE                (1 << MXC_FLC_PAGE_SIZE_SHIFT)
#define MXC_FLC_PAGE_ERASE_MSK           ((~(1 << (MXC_FLC_PAGE_SIZE_SHIFT - 1))) >> MXC_FLC_PAGE_SIZE_SHIFT) << MXC_FLC_PAGE_SIZE_SHIFT

/*******************************************************************************/

#define MXC_SET_FIELD(reg, clr, set) (*(volatile uint32_t *)reg = ((*(volatile uint32_t *)reg & ~clr) | set))

/*******************************************************************************/

#define BITBAND(reg, bit)        ((0xf0000000 & (uint32_t)(reg)) + 0x2000000 + (((uint32_t)(reg) & 0x0fffffff) << 5) + ((bit) << 2))
#define BITBAND_ClrBit(reg, bit) *(volatile uint32_t *)BITBAND(reg, bit) = 0
#define BITBAND_SetBit(reg, bit) *(volatile uint32_t *)BITBAND(reg, bit) = 1
#define BITBAND_GetBit(reg, bit) (*(volatile uint32_t *)BITBAND(reg, bit))

/*******************************************************************************/

#endif  /* _MAX32600_H_ */
