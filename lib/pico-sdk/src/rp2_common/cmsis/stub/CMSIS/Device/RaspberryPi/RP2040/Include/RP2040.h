/*************************************************************************//**
 * @file     RP2040.h
 * @brief    CMSIS-Core(M) Device Peripheral Access Layer Header File for
 *           Device RP2040
 * @version  V1.0.0
 * @date     5. May 2021
 *****************************************************************************/
/*
 * Copyright (c) 2009-2021 Arm Limited. All rights reserved.
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _CMSIS_RP2040_H_
#define _CMSIS_RP2040_H_

#ifdef __cplusplus
extern "C" {
#endif

/* =========================================================================================================================== */
/* ================                                Interrupt Number Definition                                ================ */
/* =========================================================================================================================== */

typedef enum
{
  /* =======================================  ARM Cortex-M0+ Specific Interrupt Numbers  ======================================= */
    Reset_IRQn                = -15,              /*!< -15  Reset Vector, invoked on Power up and warm reset                     */
    NonMaskableInt_IRQn       = -14,              /*!< -14  Non maskable Interrupt, cannot be stopped or preempted               */
    HardFault_IRQn            = -13,              /*!< -13  Hard Fault, all classes of Fault                                     */
    SVCall_IRQn               =  -5,              /*!< -5 System Service Call via SVC instruction                                */
    PendSV_IRQn               =  -2,              /*!< -2 Pendable request for system service                                    */
    SysTick_IRQn              =  -1,              /*!< -1 System Tick Timer                                                      */
  /* ===========================================  RP2040 Specific Interrupt Numbers  =========================================== */
    TIMER_IRQ_0_IRQn          =   0,              /*!< 0  TIMER_IRQ_0                                                            */
    TIMER_IRQ_1_IRQn          =   1,              /*!< 1  TIMER_IRQ_1                                                            */
    TIMER_IRQ_2_IRQn          =   2,              /*!< 2  TIMER_IRQ_2                                                            */
    TIMER_IRQ_3_IRQn          =   3,              /*!< 3  TIMER_IRQ_3                                                            */
    PWM_IRQ_WRAP_IRQn         =   4,              /*!< 4  PWM_IRQ_WRAP                                                           */
    USBCTRL_IRQ_IRQn          =   5,              /*!< 5  USBCTRL_IRQ                                                            */
    XIP_IRQ_IRQn              =   6,              /*!< 6  XIP_IRQ                                                                */
    PIO0_IRQ_0_IRQn           =   7,              /*!< 7  PIO0_IRQ_0                                                             */
    PIO0_IRQ_1_IRQn           =   8,              /*!< 8  PIO0_IRQ_1                                                             */
    PIO1_IRQ_0_IRQn           =   9,              /*!< 9  PIO1_IRQ_0                                                             */
    PIO1_IRQ_1_IRQn           =  10,              /*!< 10 PIO1_IRQ_1                                                             */
    DMA_IRQ_0_IRQn            =  11,              /*!< 11 DMA_IRQ_0                                                              */
    DMA_IRQ_1_IRQn            =  12,              /*!< 12 DMA_IRQ_1                                                              */
    IO_IRQ_BANK0_IRQn         =  13,              /*!< 13 IO_IRQ_BANK0                                                           */
    IO_IRQ_QSPI_IRQn          =  14,              /*!< 14 IO_IRQ_QSPI                                                            */
    SIO_IRQ_PROC0_IRQn        =  15,              /*!< 15 SIO_IRQ_PROC0                                                          */
    SIO_IRQ_PROC1_IRQn        =  16,              /*!< 16 SIO_IRQ_PROC1                                                          */
    CLOCKS_IRQ_IRQn           =  17,              /*!< 17 CLOCKS_IRQ                                                             */
    SPI0_IRQ_IRQn             =  18,              /*!< 18 SPI0_IRQ                                                               */
    SPI1_IRQ_IRQn             =  19,              /*!< 19 SPI1_IRQ                                                               */
    UART0_IRQ_IRQn            =  20,              /*!< 20 UART0_IRQ                                                              */
    UART1_IRQ_IRQn            =  21,              /*!< 21 UART1_IRQ                                                              */
    ADC_IRQ_FIFO_IRQn         =  22,              /*!< 22 ADC_IRQ_FIFO                                                           */
    I2C0_IRQ_IRQn             =  23,              /*!< 23 I2C0_IRQ                                                               */
    I2C1_IRQ_IRQn             =  24,              /*!< 24 I2C1_IRQ                                                               */
    RTC_IRQ_IRQn              =  25               /*!< 25 RTC_IRQ                                                                */
} IRQn_Type;

/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */

/* ==========================  Configuration of the ARM Cortex-M0+ Processor and Core Peripherals  =========================== */
#define __CM0PLUS_REV                  0x0001U  /*!< CM0PLUS Core Revision                                                     */
#define __NVIC_PRIO_BITS               2        /*!< Number of Bits used for Priority Levels                                   */
#define __Vendor_SysTickConfig         0        /*!< Set to 1 if different SysTick Config is used                              */
#define __VTOR_PRESENT                 1        /*!< Set to 1 if CPU supports Vector Table Offset Register                     */
#define __MPU_PRESENT                  1        /*!< MPU present                                                               */
#define __FPU_PRESENT                  0        /*!< FPU present                                                               */

/** @} */ /* End of group Configuration_of_CMSIS */

#include "core_cm0plus.h"                       /*!< ARM Cortex-M0+ processor and core peripherals                             */
#include "system_RP2040.h"                      /*!< RP2040 System                                                             */

#ifndef __IM                                    /*!< Fallback for older CMSIS versions                                         */
#define __IM   __I
#endif
#ifndef __OM                                    /*!< Fallback for older CMSIS versions                                         */
#define __OM   __O
#endif
#ifndef __IOM                                   /*!< Fallback for older CMSIS versions                                         */
#define __IOM  __IO
#endif

#ifdef __cplusplus
}
#endif

#endif /* _CMSIS_RP2040_H */
