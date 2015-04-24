/**
  ******************************************************************************
  * @file    stm32l053xx.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   CMSIS Cortex-M0+ Device Peripheral Access Layer Header File. 
  *          This file contains all the peripheral register's definitions, bits 
  *          definitions and memory mapping for stm32l053xx devices.  
  *          
  *          This file contains:
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *           - Macros to access peripheral's registers hardware
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32l053xx
  * @{
  */
    
#ifndef __STM32L053xx_H
#define __STM32L053xx_H

#ifdef __cplusplus
 extern "C" {
#endif 
  

/** @addtogroup Configuration_section_for_CMSIS
  * @{
  */
/**
  * @brief Configuration of the Cortex-M0+ Processor and Core Peripherals 
  */
#define __CM0PLUS_REV             0 /*!< Core Revision r0p0                            */
#define __MPU_PRESENT             1 /*!< STM32L0xx  provides an MPU                    */
#define __VTOR_PRESENT            1 /*!< Vector  Table  Register supported             */
#define __NVIC_PRIO_BITS          2 /*!< STM32L0xx uses 2 Bits for the Priority Levels */
#define __Vendor_SysTickConfig    0 /*!< Set to 1 if different SysTick Config is used  */

/**
  * @}
  */
   
/** @addtogroup Peripheral_interrupt_number_definition
  * @{
  */
   
/**
 * @brief stm32l053xx Interrupt Number Definition, according to the selected device 
 *        in @ref Library_configuration_section 
 */

/*!< Interrupt Number Definition */
typedef enum
{
/******  Cortex-M0 Processor Exceptions Numbers ******************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                */
  HardFault_IRQn              = -13,    /*!< 3 Cortex-M0+ Hard Fault Interrupt                       */
  SVC_IRQn                    = -5,     /*!< 11 Cortex-M0+ SV Call Interrupt                         */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M0+ Pend SV Interrupt                         */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M0+ System Tick Interrupt                     */

/******  STM32L-0 specific Interrupt Numbers *********************************************************/
  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                               */
  PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detect Interrupt                  */
  RTC_IRQn                    = 2,      /*!< RTC through EXTI Line Interrupt                         */
  FLASH_IRQn                  = 3,      /*!< FLASH Interrupt                                         */
  RCC_CRS_IRQn                = 4,      /*!< RCC and CRS Interrupts                                  */
  EXTI0_1_IRQn                = 5,      /*!< EXTI Line 0 and 1 Interrupts                            */
  EXTI2_3_IRQn                = 6,      /*!< EXTI Line 2 and 3 Interrupts                            */
  EXTI4_15_IRQn               = 7,      /*!< EXTI Line 4 to 15 Interrupts                            */
  TSC_IRQn                    = 8,      /*!< TSC Interrupt                                           */
  DMA1_Channel1_IRQn          = 9,      /*!< DMA1 Channel 1 Interrupt                                */
  DMA1_Channel2_3_IRQn        = 10,     /*!< DMA1 Channel 2 and Channel 3 Interrupts                 */
  DMA1_Channel4_5_6_7_IRQn    = 11,     /*!< DMA1 Channel 4, Channel 5, Channel 6 and Channel 7 Interrupts */
  ADC1_COMP_IRQn              = 12,     /*!< ADC1, COMP1 and COMP2 Interrupts                        */
  LPTIM1_IRQn                 = 13,     /*!< LPTIM1 Interrupt                                        */
  TIM2_IRQn                   = 15,     /*!< TIM2 Interrupt                                          */
  TIM6_DAC_IRQn               = 17,     /*!< TIM6 and DAC Interrupts                                 */
  TIM21_IRQn                  = 20,     /*!< TIM21 Interrupt                                         */
  TIM22_IRQn                  = 22,     /*!< TIM22 Interrupt                                         */
  I2C1_IRQn                   = 23,     /*!< I2C1 Interrupt                                          */
  I2C2_IRQn                   = 24,     /*!< I2C2 Interrupt                                          */
  SPI1_IRQn                   = 25,     /*!< SPI1 Interrupt                                          */
  SPI2_IRQn                   = 26,     /*!< SPI2 Interrupt                                          */
  USART1_IRQn                 = 27,     /*!< USART1 Interrupt                                        */
  USART2_IRQn                 = 28,     /*!< USART2 Interrupt                                        */
  RNG_LPUART1_IRQn            = 29,     /*!< RNG and LPUART1 Interrupts                              */
  LCD_IRQn                    = 30,     /*!< LCD Interrupt                                           */
  USB_IRQn                    = 31,     /*!< USB global Interrupt                                    */
} IRQn_Type;

/**
  * @}
  */

#include "core_cm0plus.h"
#include "system_stm32l0xx.h"
#include <stdint.h>

/** @addtogroup Peripheral_registers_structures
  * @{
  */   

/** 
  * @brief Analog to Digital Converter  
  */

typedef struct
{
  __IO uint32_t ISR;          /*!< ADC Interrupt and Status register,                          Address offset:0x00 */
  __IO uint32_t IER;          /*!< ADC Interrupt Enable register,                              Address offset:0x04 */
  __IO uint32_t CR;           /*!< ADC Control register,                                       Address offset:0x08 */
  __IO uint32_t CFGR1;        /*!< ADC Configuration register 1,                               Address offset:0x0C */
  __IO uint32_t CFGR2;        /*!< ADC Configuration register 2,                               Address offset:0x10 */
  __IO uint32_t SMPR;         /*!< ADC Sampling time register,                                 Address offset:0x14 */
  uint32_t   RESERVED1;       /*!< Reserved,                                                                  0x18 */
  uint32_t   RESERVED2;       /*!< Reserved,                                                                  0x1C */
  __IO uint32_t TR;           /*!< ADC watchdog threshold register,                            Address offset:0x20 */
  uint32_t   RESERVED3;       /*!< Reserved,                                                                  0x24 */
  __IO uint32_t CHSELR;       /*!< ADC channel selection register,                             Address offset:0x28 */
  uint32_t   RESERVED4[5];    /*!< Reserved,                                                                  0x2C */
  __IO uint32_t DR;           /*!< ADC data register,                                          Address offset:0x40 */
  uint32_t   RESERVED5[28];   /*!< Reserved,                                                           0x44 - 0xB0 */
  __IO uint32_t CALFACT;      /*!< ADC data register,                                          Address offset:0xB4 */
} ADC_TypeDef;

typedef struct
{
  __IO uint32_t CCR;
} ADC_Common_TypeDef;


/**
  * @brief Comparator 
  */

typedef struct
{
  __IO uint32_t CSR;     /*!< COMP comparator control and status register, Address offset: 0x18 */
} COMP_TypeDef;


/** 
  * @brief CRC calculation unit 
  */

typedef struct
{
  __IO uint32_t DR;          /*!< CRC Data register,                           Address offset: 0x00 */
  __IO uint32_t  IDR;        /*!< CRC Independent data register,               Address offset: 0x04 */
  __IO uint32_t CR;          /*!< CRC Control register,                        Address offset: 0x08 */
  uint32_t      RESERVED2;   /*!< Reserved,                                                    0x0C */
  __IO uint32_t INIT;        /*!< Initial CRC value register,                  Address offset: 0x10 */
  __IO uint32_t POL;         /*!< CRC polynomial register,                     Address offset: 0x14 */
} CRC_TypeDef;

/**
  * @brief Clock Recovery System 
  */

typedef struct 
{
__IO uint32_t CR;     /*!< CRS ccontrol register,              Address offset: 0x00 */
__IO uint32_t CFGR;   /*!< CRS configuration register,         Address offset: 0x04 */
__IO uint32_t ISR;    /*!< CRS interrupt and status register,  Address offset: 0x08 */
__IO uint32_t ICR;    /*!< CRS interrupt flag clear register,  Address offset: 0x0C */
} CRS_TypeDef;

/** 
  * @brief Digital to Analog Converter
  */

typedef struct
{
  __IO uint32_t CR;            /*!< DAC control register,                                    Address offset: 0x00 */
  __IO uint32_t SWTRIGR;       /*!< DAC software trigger register,                           Address offset: 0x04 */
  __IO uint32_t DHR12R1;       /*!< DAC channel1 12-bit right-aligned data holding register, Address offset: 0x08 */
  __IO uint32_t DHR12L1;       /*!< DAC channel1 12-bit left aligned data holding register,  Address offset: 0x0C */
  __IO uint32_t DHR8R1;        /*!< DAC channel1 8-bit right aligned data holding register,  Address offset: 0x10 */
  uint32_t      RESERVED0[6];  /*!<                                                                     0x14-0x28 */
  __IO uint32_t DOR1;          /*!< DAC channel1 data output register,                       Address offset: 0x2C */
  uint32_t      RESERVED1;     /*!<                                                                          0x30 */
  __IO uint32_t SR;            /*!< DAC status register,                                     Address offset: 0x34 */
} DAC_TypeDef;

/** 
  * @brief Debug MCU
  */

typedef struct
{
  __IO uint32_t IDCODE;       /*!< MCU device ID code,                          Address offset: 0x00 */
  __IO uint32_t CR;           /*!< Debug MCU configuration register,            Address offset: 0x04 */
  __IO uint32_t APB1FZ;       /*!< Debug MCU APB1 freeze register,              Address offset: 0x08 */
  __IO uint32_t APB2FZ;       /*!< Debug MCU APB2 freeze register,              Address offset: 0x0C */
}DBGMCU_TypeDef;

/** 
  * @brief DMA Controller
  */

typedef struct
{
  __IO uint32_t CCR;          /*!< DMA channel x configuration register */
  __IO uint32_t CNDTR;        /*!< DMA channel x number of data register */
  __IO uint32_t CPAR;         /*!< DMA channel x peripheral address register */
  __IO uint32_t CMAR;         /*!< DMA channel x memory address register */
} DMA_Channel_TypeDef;

typedef struct
{
  __IO uint32_t ISR;          /*!< DMA interrupt status register,               Address offset: 0x00 */
  __IO uint32_t IFCR;         /*!< DMA interrupt flag clear register,           Address offset: 0x04 */
} DMA_TypeDef;                                                                  
                                                                                
typedef struct                                                                  
{                                                                               
  __IO uint32_t CSELR;        /*!< DMA channel selection register,              Address offset: 0xA8 */
} DMA_Request_TypeDef;                                                          
                                                                                
/**                                                                             
  * @brief External Interrupt/Event Controller                                  
  */                                                                            
                                                                                
typedef struct                                                                  
{                                                                               
  __IO uint32_t IMR;          /*!<EXTI Interrupt mask register,                 Address offset: 0x00 */
  __IO uint32_t EMR;          /*!<EXTI Event mask register,                     Address offset: 0x04 */
  __IO uint32_t RTSR;         /*!<EXTI Rising trigger selection register ,      Address offset: 0x08 */
  __IO uint32_t FTSR;         /*!<EXTI Falling trigger selection register,      Address offset: 0x0C */
  __IO uint32_t SWIER;        /*!<EXTI Software interrupt event register,       Address offset: 0x10 */
  __IO uint32_t PR;           /*!<EXTI Pending register,                        Address offset: 0x14 */
}EXTI_TypeDef;

/** 
  * @brief FLASH Registers
  */
typedef struct
{
  __IO uint32_t ACR;           /*!< Access control register,                     Address offset: 0x00 */
  __IO uint32_t PECR;          /*!< Program/erase control register,              Address offset: 0x04 */
  __IO uint32_t PDKEYR;        /*!< Power down key register,                     Address offset: 0x08 */
  __IO uint32_t PEKEYR;        /*!< Program/erase key register,                  Address offset: 0x0c */
  __IO uint32_t PRGKEYR;       /*!< Program memory key register,                 Address offset: 0x10 */
  __IO uint32_t OPTKEYR;       /*!< Option byte key register,                    Address offset: 0x14 */
  __IO uint32_t SR;            /*!< Status register,                             Address offset: 0x18 */
  __IO uint32_t OPTR;          /*!< Option byte register,                        Address offset: 0x1c */
  __IO uint32_t WRPR;          /*!< Write protection register,                   Address offset: 0x20 */
} FLASH_TypeDef;


/** 
  * @brief Option Bytes Registers
  */
typedef struct
{
  __IO uint32_t RDP;               /*!< Read protection register,               Address offset: 0x00 */
  __IO uint32_t USER;              /*!< user register,                          Address offset: 0x04 */
  __IO uint32_t WRP01;             /*!< write protection Bytes 0 and 1          Address offset: 0x08 */
} OB_TypeDef;
  

/** 
  * @brief General Purpose IO
  */

typedef struct
{
  __IO uint32_t MODER;        /*!< GPIO port mode register,                     Address offset: 0x00 */
  __IO uint32_t OTYPER;       /*!< GPIO port output type register,              Address offset: 0x04 */
  __IO uint32_t OSPEEDR;      /*!< GPIO port output speed register,             Address offset: 0x08 */
  __IO uint32_t PUPDR;        /*!< GPIO port pull-up/pull-down register,        Address offset: 0x0C */
  __IO uint32_t IDR;          /*!< GPIO port input data register,               Address offset: 0x10 */
  __IO uint32_t ODR;          /*!< GPIO port output data register,              Address offset: 0x14 */
  __IO uint32_t BSRR;         /*!< GPIO port bit set/reset registerBSRR,        Address offset: 0x18 */
  __IO uint32_t LCKR;         /*!< GPIO port configuration lock register,       Address offset: 0x1C */
  __IO uint32_t AFR[2];       /*!< GPIO alternate function register,            Address offset: 0x20-0x24 */
  __IO uint32_t BRR;          /*!< GPIO bit reset register,                     Address offset: 0x28 */
}GPIO_TypeDef;

/** 
  * @brief LPTIMIMER
  */
typedef struct
{
  __IO uint32_t ISR;      /*!< LPTIM Interrupt and Status register,             Address offset: 0x00 */
  __IO uint32_t ICR;      /*!< LPTIM Interrupt Clear register,                  Address offset: 0x04 */
  __IO uint32_t IER;      /*!< LPTIM Interrupt Enable register,                 Address offset: 0x08 */
  __IO uint32_t CFGR;     /*!< LPTIM Configuration register,                    Address offset: 0x0C */
  __IO uint32_t CR;       /*!< LPTIM Control register,                          Address offset: 0x10 */
  __IO uint32_t CMP;      /*!< LPTIM Compare register,                          Address offset: 0x14 */
  __IO uint32_t ARR;      /*!< LPTIM Autoreload register,                       Address offset: 0x18 */
  __IO uint32_t CNT;      /*!< LPTIM Counter register,                          Address offset: 0x1C */
} LPTIM_TypeDef;

/** 
  * @brief SysTem Configuration
  */

typedef struct
{
  __IO uint32_t CFGR1;         /*!< SYSCFG configuration register 1,                    Address offset: 0x00 */
  __IO uint32_t CFGR2;         /*!< SYSCFG configuration register 2,                    Address offset: 0x04 */
  __IO uint32_t EXTICR[4];     /*!< SYSCFG external interrupt configuration register,   Address offset: 0x14-0x08 */
       uint32_t RESERVED[2];   /*!< Reserved,                                           0x18-0x1C */
  __IO uint32_t CFGR3;         /*!< SYSCFG configuration register 3,                    Address offset: 0x20 */       
} SYSCFG_TypeDef;



/** 
  * @brief Inter-integrated Circuit Interface
  */

typedef struct
{
  __IO uint32_t CR1;      /*!< I2C Control register 1,            Address offset: 0x00 */
  __IO uint32_t CR2;      /*!< I2C Control register 2,            Address offset: 0x04 */
  __IO uint32_t OAR1;     /*!< I2C Own address 1 register,        Address offset: 0x08 */
  __IO uint32_t OAR2;     /*!< I2C Own address 2 register,        Address offset: 0x0C */
  __IO uint32_t TIMINGR;  /*!< I2C Timing register,               Address offset: 0x10 */
  __IO uint32_t TIMEOUTR; /*!< I2C Timeout register,              Address offset: 0x14 */
  __IO uint32_t ISR;      /*!< I2C Interrupt and status register, Address offset: 0x18 */
  __IO uint32_t ICR;      /*!< I2C Interrupt clear register,      Address offset: 0x1C */
  __IO uint32_t PECR;     /*!< I2C PEC register,                  Address offset: 0x20 */
  __IO uint32_t RXDR;     /*!< I2C Receive data register,         Address offset: 0x24 */
  __IO uint32_t TXDR;     /*!< I2C Transmit data register,        Address offset: 0x28 */
}I2C_TypeDef;


/** 
  * @brief Independent WATCHDOG
  */
typedef struct
{
  __IO uint32_t KR;   /*!< IWDG Key register,       Address offset: 0x00 */
  __IO uint32_t PR;   /*!< IWDG Prescaler register, Address offset: 0x04 */
  __IO uint32_t RLR;  /*!< IWDG Reload register,    Address offset: 0x08 */
  __IO uint32_t SR;   /*!< IWDG Status register,    Address offset: 0x0C */
  __IO uint32_t WINR; /*!< IWDG Window register,    Address offset: 0x10 */
} IWDG_TypeDef;

/** 
  * @brief LCD
  */

typedef struct
{
  __IO uint32_t CR;        /*!< LCD control register,              Address offset: 0x00 */
  __IO uint32_t FCR;       /*!< LCD frame control register,        Address offset: 0x04 */
  __IO uint32_t SR;        /*!< LCD status register,               Address offset: 0x08 */
  __IO uint32_t CLR;       /*!< LCD clear register,                Address offset: 0x0C */
  uint32_t RESERVED;       /*!< Reserved,                          Address offset: 0x10 */
  __IO uint32_t RAM[16];   /*!< LCD display memory,                Address offset: 0x14-0x50 */
} LCD_TypeDef;

/** 
  * @brief MIFARE Firewall
  */

typedef struct
{
  __IO uint32_t CSSA;     /*!< Code Segment Start Address register,               Address offset: 0x00 */
  __IO uint32_t CSL;      /*!< Code Segment Length register,                      Address offset: 0x04 */
  __IO uint32_t NVDSSA;   /*!< NON volatile data Segment Start Address register,  Address offset: 0x08 */
  __IO uint32_t NVDSL;    /*!< NON volatile data Segment Length register,         Address offset: 0x0C */
  __IO uint32_t VDSSA ;   /*!< Volatile data Segment Start Address register,      Address offset: 0x10 */
  __IO uint32_t VDSL ;    /*!< Volatile data Segment Length register,             Address offset: 0x14 */
  __IO uint32_t LSSA ;    /*!< Library Segment Start Address register,            Address offset: 0x18 */
  __IO uint32_t LSL ;     /*!< Library Segment Length register,                   Address offset: 0x1C */
  __IO uint32_t CR ;      /*!< Configuration  register,                           Address offset: 0x20 */
 
} FW_TypeDef;

/** 
  * @brief Power Control
  */

typedef struct
{
  __IO uint32_t CR;   /*!< PWR power control register,        Address offset: 0x00 */
  __IO uint32_t CSR;  /*!< PWR power control/status register, Address offset: 0x04 */
} PWR_TypeDef;

/** 
  * @brief Reset and Clock Control
  */
typedef struct
{
  __IO uint32_t CR;            /*!< RCC clock control register,                                   Address offset: 0x00 */
  __IO uint32_t ICSCR;         /*!< RCC Internal clock sources calibration register,              Address offset: 0x04 */
  __IO uint32_t CRRCR;         /*!< RCC Clock recovery RC register,                               Address offset: 0x08 */
  __IO uint32_t CFGR;          /*!< RCC Clock configuration register,                             Address offset: 0x0C */
  __IO uint32_t CIER;          /*!< RCC Clock interrupt enable register,                          Address offset: 0x10 */
  __IO uint32_t CIFR;          /*!< RCC Clock interrupt flag register,                            Address offset: 0x14 */
  __IO uint32_t CICR;          /*!< RCC Clock interrupt clear register,                           Address offset: 0x18 */
  __IO uint32_t IOPRSTR;       /*!< RCC IO port reset register,                                   Address offset: 0x1C */
  __IO uint32_t AHBRSTR;       /*!< RCC AHB peripheral reset register,                            Address offset: 0x20 */
  __IO uint32_t APB2RSTR;      /*!< RCC APB2 peripheral reset register,                           Address offset: 0x24 */
  __IO uint32_t APB1RSTR;      /*!< RCC APB1 peripheral reset register,                           Address offset: 0x28 */
  __IO uint32_t IOPENR;        /*!< RCC Clock IO port enable register,                            Address offset: 0x2C */
  __IO uint32_t AHBENR;        /*!< RCC AHB peripheral clock enable register,                     Address offset: 0x30 */
  __IO uint32_t APB2ENR;       /*!< RCC APB2 peripheral enable register,                          Address offset: 0x34 */
  __IO uint32_t APB1ENR;       /*!< RCC APB1 peripheral enable register,                          Address offset: 0x38 */
  __IO uint32_t IOPSMENR;      /*!< RCC IO port clock enable in sleep mode register,              Address offset: 0x3C */
  __IO uint32_t AHBSMENR;      /*!< RCC AHB peripheral clock enable in sleep mode register,       Address offset: 0x40 */
  __IO uint32_t APB2SMENR;     /*!< RCC APB2 peripheral clock enable in sleep mode register,      Address offset: 0x44 */
  __IO uint32_t APB1SMENR;     /*!< RCC APB1 peripheral clock enable in sleep mode register,      Address offset: 0x48 */
  __IO uint32_t CCIPR;         /*!< RCC clock configuration register,                             Address offset: 0x4C */
  __IO uint32_t CSR;           /*!< RCC Control/status register,                                  Address offset: 0x50 */
} RCC_TypeDef;

/** 
  * @brief Random numbers generator
  */
typedef struct 
{
  __IO uint32_t CR;  /*!< RNG control register, Address offset: 0x00 */
  __IO uint32_t SR;  /*!< RNG status register,  Address offset: 0x04 */
  __IO uint32_t DR;  /*!< RNG data register,    Address offset: 0x08 */
} RNG_TypeDef;

/** 
  * @brief Real-Time Clock
  */
typedef struct
{
  __IO uint32_t TR;         /*!< RTC time register,                                         Address offset: 0x00 */
  __IO uint32_t DR;         /*!< RTC date register,                                         Address offset: 0x04 */
  __IO uint32_t CR;         /*!< RTC control register,                                      Address offset: 0x08 */
  __IO uint32_t ISR;        /*!< RTC initialization and status register,                    Address offset: 0x0C */
  __IO uint32_t PRER;       /*!< RTC prescaler register,                                    Address offset: 0x10 */
  __IO uint32_t WUTR;       /*!< RTC wakeup timer register,                                 Address offset: 0x14 */
       uint32_t RESERVED;   /*!< Reserved,                                                  Address offset: 0x18 */
  __IO uint32_t ALRMAR;     /*!< RTC alarm A register,                                      Address offset: 0x1C */
  __IO uint32_t ALRMBR;     /*!< RTC alarm B register,                                      Address offset: 0x20 */
  __IO uint32_t WPR;        /*!< RTC write protection register,                             Address offset: 0x24 */
  __IO uint32_t SSR;        /*!< RTC sub second register,                                   Address offset: 0x28 */
  __IO uint32_t SHIFTR;     /*!< RTC shift control register,                                Address offset: 0x2C */
  __IO uint32_t TSTR;       /*!< RTC time stamp time register,                              Address offset: 0x30 */
  __IO uint32_t TSDR;       /*!< RTC time stamp date register,                              Address offset: 0x34 */
  __IO uint32_t TSSSR;      /*!< RTC time-stamp sub second register,                        Address offset: 0x38 */
  __IO uint32_t CALR;       /*!< RTC calibration register,                                  Address offset: 0x3C */
  __IO uint32_t TAMPCR;     /*!< RTC tamper configuration register,                         Address offset: 0x40 */
  __IO uint32_t ALRMASSR;   /*!< RTC alarm A sub second register,                           Address offset: 0x44 */
  __IO uint32_t ALRMBSSR;   /*!< RTC alarm B sub second register,                           Address offset: 0x48 */
  __IO uint32_t OR;         /*!< RTC option register,                                       Address offset  0x4C */
  __IO uint32_t BKP0R;      /*!< RTC backup register 0,                                     Address offset: 0x50 */
  __IO uint32_t BKP1R;      /*!< RTC backup register 1,                                     Address offset: 0x54 */
  __IO uint32_t BKP2R;      /*!< RTC backup register 2,                                     Address offset: 0x58 */
  __IO uint32_t BKP3R;      /*!< RTC backup register 3,                                     Address offset: 0x5C */
  __IO uint32_t BKP4R;      /*!< RTC backup register 4,                                     Address offset: 0x60 */
} RTC_TypeDef;


/** 
  * @brief Serial Peripheral Interface
  */
  
typedef struct
{
  __IO uint32_t CR1;      /*!< SPI Control register 1 (not used in I2S mode),       Address offset: 0x00 */
  __IO uint32_t CR2;      /*!< SPI Control register 2,                              Address offset: 0x04 */
  __IO uint32_t SR;       /*!< SPI Status register,                                 Address offset: 0x08 */
  __IO uint32_t DR;       /*!< SPI data register,                                   Address offset: 0x0C */
  __IO uint32_t CRCPR;    /*!< SPI CRC polynomial register (not used in I2S mode),  Address offset: 0x10 */
  __IO uint32_t RXCRCR;   /*!< SPI Rx CRC register (not used in I2S mode),          Address offset: 0x14 */
  __IO uint32_t TXCRCR;   /*!< SPI Tx CRC register (not used in I2S mode),          Address offset: 0x18 */
  __IO uint32_t I2SCFGR;  /*!< SPI_I2S configuration register,                      Address offset: 0x1C */
  __IO uint32_t I2SPR;    /*!< SPI_I2S prescaler register,                          Address offset: 0x20 */
} SPI_TypeDef;

/** 
  * @brief TIM
  */
typedef struct
{
  __IO uint32_t CR1;      /*!< TIM control register 1,                       Address offset: 0x00 */
  __IO uint32_t CR2;      /*!< TIM control register 2,                       Address offset: 0x04 */
  __IO uint32_t SMCR;     /*!< TIM slave Mode Control register,              Address offset: 0x08 */
  __IO uint32_t DIER;     /*!< TIM DMA/interrupt enable register,            Address offset: 0x0C */
  __IO uint32_t SR;       /*!< TIM status register,                          Address offset: 0x10 */
  __IO uint32_t EGR;      /*!< TIM event generation register,                Address offset: 0x14 */
  __IO uint32_t CCMR1;    /*!< TIM  capture/compare mode register 1,         Address offset: 0x18 */
  __IO uint32_t CCMR2;    /*!< TIM  capture/compare mode register 2,         Address offset: 0x1C */
  __IO uint32_t CCER;     /*!< TIM capture/compare enable register,          Address offset: 0x20 */
  __IO uint32_t CNT;      /*!< TIM counter register,                         Address offset: 0x24 */
  __IO uint32_t PSC;      /*!< TIM prescaler register,                       Address offset: 0x28 */
  __IO uint32_t ARR;      /*!< TIM auto-reload register,                     Address offset: 0x2C */
  __IO uint32_t RCR;      /*!< TIM  repetition counter register,             Address offset: 0x30 */
  __IO uint32_t CCR1;     /*!< TIM capture/compare register 1,               Address offset: 0x34 */
  __IO uint32_t CCR2;     /*!< TIM capture/compare register 2,               Address offset: 0x38 */
  __IO uint32_t CCR3;     /*!< TIM capture/compare register 3,               Address offset: 0x3C */
  __IO uint32_t CCR4;     /*!< TIM capture/compare register 4,               Address offset: 0x40 */
  __IO uint32_t BDTR;     /*!< TIM break and dead-time register,             Address offset: 0x44 */
  __IO uint32_t DCR;      /*!< TIM DMA control register,                     Address offset: 0x48 */
  __IO uint32_t DMAR;     /*!< TIM DMA address for full transfer register,   Address offset: 0x4C */
  __IO uint32_t OR;       /*!< TIM option register,                          Address offset: 0x50 */
} TIM_TypeDef;

/**
  * @brief Touch Sensing Controller (TSC)
  */
typedef struct
{
  __IO uint32_t CR;            /*!< TSC control register,                     Address offset: 0x00 */
  __IO uint32_t IER;           /*!< TSC interrupt enable register,            Address offset: 0x04 */
  __IO uint32_t ICR;           /*!< TSC interrupt clear register,             Address offset: 0x08 */
  __IO uint32_t ISR;           /*!< TSC interrupt status register,            Address offset: 0x0C */
  __IO uint32_t IOHCR;         /*!< TSC I/O hysteresis control register,      Address offset: 0x10 */
  uint32_t      RESERVED1;     /*!< Reserved,                                 Address offset: 0x14 */
  __IO uint32_t IOASCR;        /*!< TSC I/O analog switch control register,   Address offset: 0x18 */
  uint32_t      RESERVED2;     /*!< Reserved,                                 Address offset: 0x1C */
  __IO uint32_t IOSCR;         /*!< TSC I/O sampling control register,        Address offset: 0x20 */
  uint32_t      RESERVED3;     /*!< Reserved,                                 Address offset: 0x24 */
  __IO uint32_t IOCCR;         /*!< TSC I/O channel control register,         Address offset: 0x28 */
  uint32_t      RESERVED4;     /*!< Reserved,                                 Address offset: 0x2C */
  __IO uint32_t IOGCSR;        /*!< TSC I/O group control status register,    Address offset: 0x30 */
  __IO uint32_t IOGXCR[8];     /*!< TSC I/O group x counter register,         Address offset: 0x34-50 */
} TSC_TypeDef;

/** 
  * @brief Universal Synchronous Asynchronous Receiver Transmitter
  */
  
typedef struct
{
  __IO uint32_t CR1;    /*!< USART Control register 1,                 Address offset: 0x00 */ 
  __IO uint32_t CR2;    /*!< USART Control register 2,                 Address offset: 0x04 */ 
  __IO uint32_t CR3;    /*!< USART Control register 3,                 Address offset: 0x08 */
  __IO uint32_t BRR;    /*!< USART Baud rate register,                 Address offset: 0x0C */  
  __IO uint32_t GTPR;   /*!< USART Guard time and prescaler register,  Address offset: 0x10 */
  __IO uint32_t RTOR;   /*!< USART Receiver Time Out register,         Address offset: 0x14 */  
  __IO uint32_t RQR;    /*!< USART Request register,                   Address offset: 0x18 */
  __IO uint32_t ISR;    /*!< USART Interrupt and status register,      Address offset: 0x1C */
  __IO uint32_t ICR;    /*!< USART Interrupt flag Clear register,      Address offset: 0x20 */
  __IO uint32_t RDR;    /*!< USART Receive Data register,              Address offset: 0x24 */
  __IO uint32_t TDR;    /*!< USART Transmit Data register,             Address offset: 0x28 */
} USART_TypeDef;

/** 
  * @brief Window WATCHDOG
  */
typedef struct
{
  __IO uint32_t CR;   /*!< WWDG Control register,       Address offset: 0x00 */
  __IO uint32_t CFR;  /*!< WWDG Configuration register, Address offset: 0x04 */
  __IO uint32_t SR;   /*!< WWDG Status register,        Address offset: 0x08 */
} WWDG_TypeDef;

/** 
  * @brief Universal Serial Bus Full Speed Device
  */
  
typedef struct
{
  __IO uint16_t EP0R;            /*!< USB Endpoint 0 register,                Address offset: 0x00 */ 
  __IO uint16_t RESERVED0;       /*!< Reserved */     
  __IO uint16_t EP1R;            /*!< USB Endpoint 1 register,                Address offset: 0x04 */
  __IO uint16_t RESERVED1;       /*!< Reserved */       
  __IO uint16_t EP2R;            /*!< USB Endpoint 2 register,                Address offset: 0x08 */
  __IO uint16_t RESERVED2;       /*!< Reserved */       
  __IO uint16_t EP3R;            /*!< USB Endpoint 3 register,                Address offset: 0x0C */ 
  __IO uint16_t RESERVED3;       /*!< Reserved */       
  __IO uint16_t EP4R;            /*!< USB Endpoint 4 register,                Address offset: 0x10 */
  __IO uint16_t RESERVED4;       /*!< Reserved */       
  __IO uint16_t EP5R;            /*!< USB Endpoint 5 register,                Address offset: 0x14 */
  __IO uint16_t RESERVED5;       /*!< Reserved */       
  __IO uint16_t EP6R;            /*!< USB Endpoint 6 register,                Address offset: 0x18 */
  __IO uint16_t RESERVED6;       /*!< Reserved */       
  __IO uint16_t EP7R;            /*!< USB Endpoint 7 register,                Address offset: 0x1C */
  __IO uint16_t RESERVED7[17];   /*!< Reserved */     
  __IO uint16_t CNTR;            /*!< Control register,                       Address offset: 0x40 */
  __IO uint16_t RESERVED8;       /*!< Reserved */       
  __IO uint16_t ISTR;            /*!< Interrupt status register,              Address offset: 0x44 */
  __IO uint16_t RESERVED9;       /*!< Reserved */       
  __IO uint16_t FNR;             /*!< Frame number register,                  Address offset: 0x48 */
  __IO uint16_t RESERVEDA;       /*!< Reserved */       
  __IO uint16_t DADDR;           /*!< Device address register,                Address offset: 0x4C */
  __IO uint16_t RESERVEDB;       /*!< Reserved */       
  __IO uint16_t BTABLE;          /*!< Buffer Table address register,          Address offset: 0x50 */
  __IO uint16_t RESERVEDC;       /*!< Reserved */       
  __IO uint16_t LPMCSR;          /*!< LPM Control and Status register,        Address offset: 0x54 */
  __IO uint16_t RESERVEDD;       /*!< Reserved */       
  __IO uint16_t BCDR;            /*!< Battery Charging detector register,     Address offset: 0x58 */
  __IO uint16_t RESERVEDE;       /*!< Reserved */       
} USB_TypeDef;

/**
  * @}
  */
  
/** @addtogroup Peripheral_memory_map
  * @{
  */

#define FLASH_BASE             ((uint32_t)0x08000000) /*!< FLASH base address in the alias region */
#define FLASH_END              ((uint32_t)0x0800FFFF) /*!< FLASH end address in the alias region */
#define DATA_EEPROM_BASE       ((uint32_t)0x08080000) /*!< DATA_EEPROM base address in the alias region */
#define DATA_EEPROM_END        ((uint32_t)0x080807FF) /*!< DATA EEPROM end address in the alias region */
#define SRAM_BASE              ((uint32_t)0x20000000) /*!< SRAM base address in the alias region */
#define PERIPH_BASE            ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region */

/*!< Peripheral memory map */
#define APBPERIPH_BASE        PERIPH_BASE
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x00020000)
#define IOPPERIPH_BASE        (PERIPH_BASE + 0x10000000)

#define TIM2_BASE             (APBPERIPH_BASE + 0x00000000)
#define TIM6_BASE             (APBPERIPH_BASE + 0x00001000)
#define LCD_BASE              (APBPERIPH_BASE + 0x00002400)
#define RTC_BASE              (APBPERIPH_BASE + 0x00002800)
#define WWDG_BASE             (APBPERIPH_BASE + 0x00002C00)
#define IWDG_BASE             (APBPERIPH_BASE + 0x00003000)
#define SPI2_BASE             (APBPERIPH_BASE + 0x00003800)
#define USART2_BASE           (APBPERIPH_BASE + 0x00004400)
#define LPUART1_BASE          (APBPERIPH_BASE + 0x00004800)
#define I2C1_BASE             (APBPERIPH_BASE + 0x00005400)
#define I2C2_BASE             (APBPERIPH_BASE + 0x00005800)
#define CRS_BASE              (APBPERIPH_BASE + 0x00006C00)
#define PWR_BASE              (APBPERIPH_BASE + 0x00007000)
#define DAC_BASE              (APBPERIPH_BASE + 0x00007400)
#define LPTIM1_BASE           (APBPERIPH_BASE + 0x00007C00)

#define SYSCFG_BASE           (APBPERIPH_BASE + 0x00010000)
#define COMP1_BASE            (APBPERIPH_BASE + 0x00010018)
#define COMP2_BASE            (APBPERIPH_BASE + 0x0001001C)
#define EXTI_BASE             (APBPERIPH_BASE + 0x00010400)
#define TIM21_BASE            (APBPERIPH_BASE + 0x00010800)
#define TIM22_BASE            (APBPERIPH_BASE + 0x00011400)
#define FW_BASE               (APBPERIPH_BASE + 0x00011C00)
#define ADC1_BASE             (APBPERIPH_BASE + 0x00012400)
#define ADC_BASE              (APBPERIPH_BASE + 0x00012708)
#define SPI1_BASE             (APBPERIPH_BASE + 0x00013000)
#define USART1_BASE           (APBPERIPH_BASE + 0x00013800)
#define DBGMCU_BASE           (APBPERIPH_BASE + 0x00015800)

#define DMA1_BASE             (AHBPERIPH_BASE + 0x00000000)
#define DMA1_Channel1_BASE    (DMA1_BASE + 0x00000008)
#define DMA1_Channel2_BASE    (DMA1_BASE + 0x0000001C)
#define DMA1_Channel3_BASE    (DMA1_BASE + 0x00000030)
#define DMA1_Channel4_BASE    (DMA1_BASE + 0x00000044)
#define DMA1_Channel5_BASE    (DMA1_BASE + 0x00000058)
#define DMA1_Channel6_BASE    (DMA1_BASE + 0x0000006C)
#define DMA1_Channel7_BASE    (DMA1_BASE + 0x00000080)
#define DMA1_CSELR_BASE       (DMA1_BASE + 0x000000A8)


#define RCC_BASE              (AHBPERIPH_BASE + 0x00001000)
#define FLASH_R_BASE          (AHBPERIPH_BASE + 0x00002000) /*!< FLASH registers base address */
#define OB_BASE               ((uint32_t)0x1FF80000)        /*!< FLASH Option Bytes base address */
#define CRC_BASE              (AHBPERIPH_BASE + 0x00003000)
#define TSC_BASE              (AHBPERIPH_BASE + 0x00004000)
#define RNG_BASE              (AHBPERIPH_BASE + 0x00005000)

#define GPIOA_BASE            (IOPPERIPH_BASE + 0x00000000)
#define GPIOB_BASE            (IOPPERIPH_BASE + 0x00000400)
#define GPIOC_BASE            (IOPPERIPH_BASE + 0x00000800)
#define GPIOD_BASE            (IOPPERIPH_BASE + 0x00000C00)
#define GPIOH_BASE            (IOPPERIPH_BASE + 0x00001C00)

/**
  * @}
  */
  
/** @addtogroup Peripheral_declaration
  * @{
  */  

#define TIM2                ((TIM_TypeDef *) TIM2_BASE)
#define TIM6                ((TIM_TypeDef *) TIM6_BASE)
#define RTC                 ((RTC_TypeDef *) RTC_BASE)
#define WWDG                ((WWDG_TypeDef *) WWDG_BASE)
#define IWDG                ((IWDG_TypeDef *) IWDG_BASE)
#define SPI2                ((SPI_TypeDef *) SPI2_BASE)
#define USART2              ((USART_TypeDef *) USART2_BASE)
#define LPUART1             ((USART_TypeDef *) LPUART1_BASE)
#define I2C1                ((I2C_TypeDef *) I2C1_BASE)
#define I2C2                ((I2C_TypeDef *) I2C2_BASE)
#define CRS                 ((CRS_TypeDef *) CRS_BASE)
#define PWR                 ((PWR_TypeDef *) PWR_BASE)
#define DAC                 ((DAC_TypeDef *) DAC_BASE)
#define LPTIM1              ((LPTIM_TypeDef *) LPTIM1_BASE)
#define LCD                 ((LCD_TypeDef *) LCD_BASE)

#define SYSCFG              ((SYSCFG_TypeDef *) SYSCFG_BASE)
#define COMP1               ((COMP_TypeDef *) COMP1_BASE)
#define COMP2               ((COMP_TypeDef *) COMP2_BASE)
#define EXTI                ((EXTI_TypeDef *) EXTI_BASE)
#define TIM21               ((TIM_TypeDef *) TIM21_BASE)
#define TIM22               ((TIM_TypeDef *) TIM22_BASE)
#define FW                  ((FW_TypeDef *) FW_BASE)
#define ADC1                ((ADC_TypeDef *) ADC1_BASE)
#define ADC                 ((ADC_Common_TypeDef *) ADC_BASE)
#define SPI1                ((SPI_TypeDef *) SPI1_BASE)
#define USART1              ((USART_TypeDef *) USART1_BASE)
#define DBGMCU              ((DBGMCU_TypeDef *) DBGMCU_BASE)

#define DMA1                ((DMA_TypeDef *) DMA1_BASE)
#define DMA1_Channel1       ((DMA_Channel_TypeDef *) DMA1_Channel1_BASE)
#define DMA1_Channel2       ((DMA_Channel_TypeDef *) DMA1_Channel2_BASE)
#define DMA1_Channel3       ((DMA_Channel_TypeDef *) DMA1_Channel3_BASE)
#define DMA1_Channel4       ((DMA_Channel_TypeDef *) DMA1_Channel4_BASE)
#define DMA1_Channel5       ((DMA_Channel_TypeDef *) DMA1_Channel5_BASE)
#define DMA1_Channel6       ((DMA_Channel_TypeDef *) DMA1_Channel6_BASE)
#define DMA1_Channel7       ((DMA_Channel_TypeDef *) DMA1_Channel7_BASE)
#define DMA1_CSELR          ((DMA_Request_TypeDef *) DMA1_CSELR_BASE)


#define FLASH               ((FLASH_TypeDef *) FLASH_R_BASE)
#define OB                  ((OB_TypeDef *) OB_BASE) 
#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define CRC                 ((CRC_TypeDef *) CRC_BASE)
#define TSC                 ((TSC_TypeDef *) TSC_BASE)
#define RNG                 ((RNG_TypeDef *) RNG_BASE)

#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOH               ((GPIO_TypeDef *) GPIOH_BASE)

#define USB                 ((USB_TypeDef *) USB_BASE)

/**
  * @}
  */

/** @addtogroup Exported_constants
  * @{
  */
  
  /** @addtogroup Peripheral_Registers_Bits_Definition
  * @{
  */
    
/******************************************************************************/
/*                         Peripheral Registers Bits Definition               */
/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/*                      Analog to Digital Converter (ADC)                     */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for ADC_ISR register  ******************/
#define ADC_ISR_EOCAL                       ((uint32_t)0x00000800)     /*!< End of calibration flag */
#define ADC_ISR_AWD                         ((uint32_t)0x00000080)     /*!< Analog watchdog flag */
#define ADC_ISR_OVR                         ((uint32_t)0x00000010)     /*!< Overrun flag */
#define ADC_ISR_EOSEQ                       ((uint32_t)0x00000008)     /*!< End of Sequence flag */
#define ADC_ISR_EOC                         ((uint32_t)0x00000004)     /*!< End of Conversion */
#define ADC_ISR_EOSMP                       ((uint32_t)0x00000002)     /*!< End of sampling flag */
#define ADC_ISR_ADRDY                       ((uint32_t)0x00000001)     /*!< ADC Ready */

/* Old EOSEQ bit definition, maintained for legacy purpose */
#define ADC_ISR_EOS                          ADC_ISR_EOSEQ

/********************  Bits definition for ADC_IER register  ******************/
#define ADC_IER_EOCALIE                     ((uint32_t)0x00000800)     /*!< Enf Of Calibration interrupt enable */
#define ADC_IER_AWDIE                       ((uint32_t)0x00000080)     /*!< Analog Watchdog interrupt enable */
#define ADC_IER_OVRIE                       ((uint32_t)0x00000010)     /*!< Overrun interrupt enable */
#define ADC_IER_EOSEQIE                     ((uint32_t)0x00000008)     /*!< End of Sequence of conversion interrupt enable */
#define ADC_IER_EOCIE                       ((uint32_t)0x00000004)     /*!< End of Conversion interrupt enable */
#define ADC_IER_EOSMPIE                     ((uint32_t)0x00000002)     /*!< End of sampling interrupt enable */
#define ADC_IER_ADRDYIE                     ((uint32_t)0x00000001)     /*!< ADC Ready interrupt enable */

/* Old EOSEQIE bit definition, maintained for legacy purpose */
#define ADC_IER_EOSIE                        ADC_IER_EOSEQIE

/********************  Bits definition for ADC_CR register  *******************/
#define ADC_CR_ADCAL                        ((uint32_t)0x80000000)     /*!< ADC calibration */
#define ADC_CR_ADVREGEN                     ((uint32_t)0x10000000)     /*!< ADC Voltage Regulator Enable */
#define ADC_CR_ADSTP                        ((uint32_t)0x00000010)     /*!< ADC stop of conversion command */
#define ADC_CR_ADSTART                      ((uint32_t)0x00000004)     /*!< ADC start of conversion */
#define ADC_CR_ADDIS                        ((uint32_t)0x00000002)     /*!< ADC disable command */
#define ADC_CR_ADEN                         ((uint32_t)0x00000001)     /*!< ADC enable control */ /*####   TBV  */

/*******************  Bits definition for ADC_CFGR1 register  *****************/
#define ADC_CFGR1_AWDCH                     ((uint32_t)0x7C000000)     /*!< AWDCH[4:0] bits (Analog watchdog channel select bits) */
#define ADC_CFGR1_AWDCH_0                   ((uint32_t)0x04000000)     /*!< Bit 0 */
#define ADC_CFGR1_AWDCH_1                   ((uint32_t)0x08000000)     /*!< Bit 1 */
#define ADC_CFGR1_AWDCH_2                   ((uint32_t)0x10000000)     /*!< Bit 2 */
#define ADC_CFGR1_AWDCH_3                   ((uint32_t)0x20000000)     /*!< Bit 3 */
#define ADC_CFGR1_AWDCH_4                   ((uint32_t)0x40000000)     /*!< Bit 4 */
#define ADC_CFGR1_AWDEN                     ((uint32_t)0x00800000)     /*!< Analog watchdog enable on regular channels */
#define ADC_CFGR1_AWDSGL                    ((uint32_t)0x00400000)     /*!< Enable the watchdog on a single channel or on all channels  */
#define ADC_CFGR1_DISCEN                    ((uint32_t)0x00010000)     /*!< Discontinuous mode on regular channels */
#define ADC_CFGR1_AUTOFF                    ((uint32_t)0x00008000)     /*!< ADC auto power off */
#define ADC_CFGR1_WAIT                      ((uint32_t)0x00004000)     /*!< ADC wait conversion mode */
#define ADC_CFGR1_CONT                      ((uint32_t)0x00002000)     /*!< Continuous Conversion */
#define ADC_CFGR1_OVRMOD                    ((uint32_t)0x00001000)     /*!< Overrun mode */
#define ADC_CFGR1_EXTEN                     ((uint32_t)0x00000C00)     /*!< EXTEN[1:0] bits (External Trigger Conversion mode for regular channels) */
#define ADC_CFGR1_EXTEN_0                   ((uint32_t)0x00000400)     /*!< Bit 0 */
#define ADC_CFGR1_EXTEN_1                   ((uint32_t)0x00000800)     /*!< Bit 1 */
#define ADC_CFGR1_EXTSEL                    ((uint32_t)0x000001C0)     /*!< EXTSEL[2:0] bits (External Event Select for regular group) */
#define ADC_CFGR1_EXTSEL_0                  ((uint32_t)0x00000040)     /*!< Bit 0 */
#define ADC_CFGR1_EXTSEL_1                  ((uint32_t)0x00000080)     /*!< Bit 1 */
#define ADC_CFGR1_EXTSEL_2                  ((uint32_t)0x00000100)     /*!< Bit 2 */
#define ADC_CFGR1_ALIGN                     ((uint32_t)0x00000020)     /*!< Data Alignment */
#define ADC_CFGR1_RES                       ((uint32_t)0x00000018)     /*!< RES[1:0] bits (Resolution) */
#define ADC_CFGR1_RES_0                     ((uint32_t)0x00000008)     /*!< Bit 0 */
#define ADC_CFGR1_RES_1                     ((uint32_t)0x00000010)     /*!< Bit 1 */
#define ADC_CFGR1_SCANDIR                   ((uint32_t)0x00000004)     /*!< Sequence scan direction */
#define ADC_CFGR1_DMACFG                    ((uint32_t)0x00000002)     /*!< Direct memory access configuration */
#define ADC_CFGR1_DMAEN                     ((uint32_t)0x00000001)     /*!< Direct memory access enable */

/* Old WAIT bit definition, maintained for legacy purpose */
#define ADC_CFGR1_AUTDLY                    ADC_CFGR1_WAIT

/*******************  Bits definition for ADC_CFGR2 register  *****************/
#define ADC_CFGR2_TOVS                      ((uint32_t)0x80000200)     /*!< Triggered Oversampling */
#define ADC_CFGR2_OVSS                      ((uint32_t)0x000001E0)     /*!< OVSS [3:0] bits (Oversampling shift) */
#define ADC_CFGR2_OVSS_0                    ((uint32_t)0x00000020)     /*!< Bit 0 */
#define ADC_CFGR2_OVSS_1                    ((uint32_t)0x00000040)     /*!< Bit 1 */
#define ADC_CFGR2_OVSS_2                    ((uint32_t)0x00000080)     /*!< Bit 2 */
#define ADC_CFGR2_OVSS_3                    ((uint32_t)0x00000100)     /*!< Bit 3 */
#define ADC_CFGR2_OVSR                      ((uint32_t)0x0000001C)     /*!< OVSR  [2:0] bits (Oversampling ratio) */
#define ADC_CFGR2_OVSR_0                    ((uint32_t)0x00000004)     /*!< Bit 0 */
#define ADC_CFGR2_OVSR_1                    ((uint32_t)0x00000008)     /*!< Bit 1 */
#define ADC_CFGR2_OVSR_2                    ((uint32_t)0x00000010)     /*!< Bit 2 */
#define ADC_CFGR2_OVSE                      ((uint32_t)0x00000001)     /*!< Oversampler Enable */
#define ADC_CFGR2_CKMODE                    ((uint32_t)0xC0000000)     /*!< CKMODE [1:0] bits (ADC clock mode) */
#define ADC_CFGR2_CKMODE_0                  ((uint32_t)0x40000000)     /*!< Bit 0 */
#define ADC_CFGR2_CKMODE_1                  ((uint32_t)0x80000000)     /*!< Bit 1 */


/******************  Bit definition for ADC_SMPR register  ********************/
#define ADC_SMPR_SMP                        ((uint32_t)0x00000007)     /*!< SMPR[2:0] bits (Sampling time selection) */
#define ADC_SMPR_SMP_0                      ((uint32_t)0x00000001)     /*!< Bit 0 */
#define ADC_SMPR_SMP_1                      ((uint32_t)0x00000002)     /*!< Bit 1 */
#define ADC_SMPR_SMP_2                      ((uint32_t)0x00000004)     /*!< Bit 2 */

/* Bit names aliases maintained for legacy */
#define ADC_SMPR_SMPR                       ADC_SMPR_SMP
#define ADC_SMPR_SMPR_0                     ADC_SMPR_SMP_0
#define ADC_SMPR_SMPR_1                     ADC_SMPR_SMP_1
#define ADC_SMPR_SMPR_2                     ADC_SMPR_SMP_2

/*******************  Bit definition for ADC_TR register  ********************/
#define ADC_TR_HT                           ((uint32_t)0x0FFF0000)     /*!< Analog watchdog high threshold */
#define ADC_TR_LT                           ((uint32_t)0x00000FFF)     /*!< Analog watchdog low threshold */

/******************  Bit definition for ADC_CHSELR register  ******************/
#define ADC_CHSELR_CHSEL18                  ((uint32_t)0x00040000)     /*!< Channel 18 selection */
#define ADC_CHSELR_CHSEL17                  ((uint32_t)0x00020000)     /*!< Channel 17 selection */
#define ADC_CHSELR_CHSEL16                  ((uint32_t)0x00010000)     /*!< Channel 16 selection */
#define ADC_CHSELR_CHSEL15                  ((uint32_t)0x00008000)     /*!< Channel 15 selection */
#define ADC_CHSELR_CHSEL14                  ((uint32_t)0x00004000)     /*!< Channel 14 selection */
#define ADC_CHSELR_CHSEL13                  ((uint32_t)0x00002000)     /*!< Channel 13 selection */
#define ADC_CHSELR_CHSEL12                  ((uint32_t)0x00001000)     /*!< Channel 12 selection */
#define ADC_CHSELR_CHSEL11                  ((uint32_t)0x00000800)     /*!< Channel 11 selection */
#define ADC_CHSELR_CHSEL10                  ((uint32_t)0x00000400)     /*!< Channel 10 selection */
#define ADC_CHSELR_CHSEL9                   ((uint32_t)0x00000200)     /*!< Channel 9 selection */
#define ADC_CHSELR_CHSEL8                   ((uint32_t)0x00000100)     /*!< Channel 8 selection */
#define ADC_CHSELR_CHSEL7                   ((uint32_t)0x00000080)     /*!< Channel 7 selection */
#define ADC_CHSELR_CHSEL6                   ((uint32_t)0x00000040)     /*!< Channel 6 selection */
#define ADC_CHSELR_CHSEL5                   ((uint32_t)0x00000020)     /*!< Channel 5 selection */
#define ADC_CHSELR_CHSEL4                   ((uint32_t)0x00000010)     /*!< Channel 4 selection */
#define ADC_CHSELR_CHSEL3                   ((uint32_t)0x00000008)     /*!< Channel 3 selection */
#define ADC_CHSELR_CHSEL2                   ((uint32_t)0x00000004)     /*!< Channel 2 selection */
#define ADC_CHSELR_CHSEL1                   ((uint32_t)0x00000002)     /*!< Channel 1 selection */
#define ADC_CHSELR_CHSEL0                   ((uint32_t)0x00000001)     /*!< Channel 0 selection */

/********************  Bit definition for ADC_DR register  ********************/
#define ADC_DR_DATA                         ((uint32_t)0x0000FFFF)     /*!< Regular data */

/********************  Bit definition for ADC_CALFACT register  ********************/
#define ADC_CALFACT_CALFACT                 ((uint32_t)0x0000007F)     /*!< Calibration factor */

/*******************  Bit definition for ADC_CCR register  ********************/
#define ADC_CCR_LFMEN                       ((uint32_t)0x02000000)     /*!< Low Frequency Mode enable */
#define ADC_CCR_VLCDEN                      ((uint32_t)0x01000000)     /*!< Voltage battery enable */
#define ADC_CCR_TSEN                        ((uint32_t)0x00800000)     /*!< Temperature sensore enable */
#define ADC_CCR_VREFEN                      ((uint32_t)0x00400000)     /*!< Vrefint enable */
#define ADC_CCR_PRESC                       ((uint32_t)0x003C0000)     /*!< PRESC  [3:0] bits (ADC prescaler) */
#define ADC_CCR_PRESC_0                     ((uint32_t)0x00040000)     /*!< Bit 0 */
#define ADC_CCR_PRESC_1                     ((uint32_t)0x00080000)     /*!< Bit 1 */
#define ADC_CCR_PRESC_2                     ((uint32_t)0x00100000)     /*!< Bit 2 */
#define ADC_CCR_PRESC_3                     ((uint32_t)0x00200000)     /*!< Bit 3 */

/******************************************************************************/
/*                                                                            */
/*                      Analog Comparators (COMP)                             */
/*                                                                            */
/******************************************************************************/
/*************  Bit definition for COMP_CSR register (COMP1 and COMP2)  **************/
/* COMP1 bits definition */
#define COMP_CSR_COMP1EN                ((uint32_t)0x00000001) /*!< COMP1 enable */
#define COMP_CSR_COMP1INNSEL            ((uint32_t)0x00000030) /*!< COMP1 inverting input select */
#define COMP_CSR_COMP1INNSEL_0          ((uint32_t)0x00000010) /*!< COMP1 inverting input select bit 0 */
#define COMP_CSR_COMP1INNSEL_1          ((uint32_t)0x00000020) /*!< COMP1 inverting input select bit 1 */
#define COMP_CSR_COMP1WM                ((uint32_t)0x00000100) /*!< Comparators window mode enable */
#define COMP_CSR_COMP1LPTIM1IN1         ((uint32_t)0x00001000) /*!< COMP1 LPTIM1 IN1 connection */
#define COMP_CSR_COMP1POLARITY          ((uint32_t)0x00008000) /*!< COMP1 output polarity */
#define COMP_CSR_COMP1VALUE             ((uint32_t)0x40000000) /*!< COMP1 output level */
#define COMP_CSR_COMP1LOCK              ((uint32_t)0x80000000) /*!< COMP1 lock */
/* COMP2 bits definition */
#define COMP_CSR_COMP2EN                ((uint32_t)0x00000001) /*!< COMP2 enable */
#define COMP_CSR_COMP2SPEED             ((uint32_t)0x000C0008) /*!< COMP2 power mode */
#define COMP_CSR_COMP2INNSEL            ((uint32_t)0x00100070) /*!< COMP2 inverting input select */
#define COMP_CSR_COMP2INNSEL_0          ((uint32_t)0x00100010) /*!< COMP2 inverting input select bit 0 */
#define COMP_CSR_COMP2INNSEL_1          ((uint32_t)0x00200020) /*!< COMP2 inverting input select bit 1 */
#define COMP_CSR_COMP2INNSEL_2          ((uint32_t)0x00400040) /*!< COMP2 inverting input select bit 2 */
#define COMP_CSR_COMP2INPSEL            ((uint32_t)0x00000700) /*!< COMPx non inverting input select */
#define COMP_CSR_COMP2INPSEL_0          ((uint32_t)0x00000100) /*!< COMPx non inverting input select */
#define COMP_CSR_COMP2INPSEL_1          ((uint32_t)0x00000200) /*!< COMPx non inverting input select */
#define COMP_CSR_COMP2INPSEL_2          ((uint32_t)0x00000400) /*!< COMPx non inverting input select */
#define COMP_CSR_COMP2LPTIM1IN2         ((uint32_t)0x00001000) /*!< COMP2 LPTIM1 IN2 connection */
#define COMP_CSR_COMP2POLARITY          ((uint32_t)0x00008000) /*!< COMP2 output polarity */
#define COMP_CSR_COMP2VALUE             ((uint32_t)0x40000000) /*!< COMP2 output level */
#define COMP_CSR_COMP2LOCK              ((uint32_t)0x80000000) /*!< COMP2 lock */

/**********************  Bit definition for COMP_CSR register common  ****************/
#define COMP_CSR_COMPxEN                ((uint32_t)0x00000001) /*!< COMPx enable */
#define COMP_CSR_COMPxPOLARITY          ((uint32_t)0x00008000) /*!< COMPx output polarity */
#define COMP_CSR_COMPxOUTVALUE          ((uint32_t)0x40000000) /*!< COMPx output level */
#define COMP_CSR_COMPxLOCK              ((uint32_t)0x80000000) /*!< COMPx lock */


/******************************************************************************/
/*                                                                            */
/*                       CRC calculation unit (CRC)                           */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for CRC_DR register  *********************/
#define CRC_DR_DR                           ((uint32_t)0xFFFFFFFF) /*!< Data register bits */

/*******************  Bit definition for CRC_IDR register  ********************/
#define CRC_IDR_IDR                         ((uint32_t)0x000000FF) /*!< General-purpose 8-bit data register bits */

/********************  Bit definition for CRC_CR register  ********************/
#define CRC_CR_RESET                        ((uint32_t)0x00000001) /*!< RESET the CRC computation unit bit */
#define CRC_CR_POLYSIZE                     ((uint32_t)0x00000018) /*!< Polynomial size bits */
#define CRC_CR_POLYSIZE_0                   ((uint32_t)0x00000008) /*!< Polynomial size bit 0 */
#define CRC_CR_POLYSIZE_1                   ((uint32_t)0x00000010) /*!< Polynomial size bit 1 */
#define CRC_CR_REV_IN                       ((uint32_t)0x00000060) /*!< REV_IN Reverse Input Data bits */
#define CRC_CR_REV_IN_0                     ((uint32_t)0x00000020) /*!< Bit 0 */
#define CRC_CR_REV_IN_1                     ((uint32_t)0x00000040) /*!< Bit 1 */
#define CRC_CR_REV_OUT                      ((uint32_t)0x00000080) /*!< REV_OUT Reverse Output Data bits */

/*******************  Bit definition for CRC_INIT register  *******************/
#define CRC_INIT_INIT                       ((uint32_t)0xFFFFFFFF) /*!< Initial CRC value bits */

/*******************  Bit definition for CRC_POL register  ********************/
#define CRC_POL_POL                         ((uint32_t)0xFFFFFFFF) /*!< Coefficients of the polynomial */

/******************************************************************************/
/*                                                                            */
/*                          CRS Clock Recovery System                         */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for CRS_CR register  *********************/
#define CRS_CR_SYNCOKIE                     ((uint32_t)0x00000001) /* SYNC event OK interrupt enable        */
#define CRS_CR_SYNCWARNIE                   ((uint32_t)0x00000002) /* SYNC warning interrupt enable         */
#define CRS_CR_ERRIE                        ((uint32_t)0x00000004) /* SYNC error interrupt enable           */
#define CRS_CR_ESYNCIE                      ((uint32_t)0x00000008) /* Expected SYNC(ESYNCF) interrupt Enable*/
#define CRS_CR_CEN                          ((uint32_t)0x00000020) /* Frequency error counter enable        */
#define CRS_CR_AUTOTRIMEN                   ((uint32_t)0x00000040) /* Automatic trimming enable             */
#define CRS_CR_SWSYNC                       ((uint32_t)0x00000080) /* A Software SYNC event is generated    */
#define CRS_CR_TRIM                         ((uint32_t)0x00003F00) /* HSI48 oscillator smooth trimming      */

/*******************  Bit definition for CRS_CFGR register  *********************/
#define CRS_CFGR_RELOAD                     ((uint32_t)0x0000FFFF) /* Counter reload value               */
#define CRS_CFGR_FELIM                      ((uint32_t)0x00FF0000) /* Frequency error limit              */

#define CRS_CFGR_SYNCDIV                    ((uint32_t)0x07000000) /* SYNC divider                       */
#define CRS_CFGR_SYNCDIV_0                  ((uint32_t)0x01000000) /* Bit 0                              */
#define CRS_CFGR_SYNCDIV_1                  ((uint32_t)0x02000000) /* Bit 1                              */
#define CRS_CFGR_SYNCDIV_2                  ((uint32_t)0x04000000) /* Bit 2                              */

#define CRS_CFGR_SYNCSRC                    ((uint32_t)0x30000000) /* SYNC signal source selection       */
#define CRS_CFGR_SYNCSRC_0                  ((uint32_t)0x10000000) /* Bit 0                              */
#define CRS_CFGR_SYNCSRC_1                  ((uint32_t)0x20000000) /* Bit 1                              */

#define CRS_CFGR_SYNCPOL                    ((uint32_t)0x80000000) /* SYNC polarity selection            */
  
/*******************  Bit definition for CRS_ISR register  *********************/
#define CRS_ISR_SYNCOKF                     ((uint32_t)0x00000001) /* SYNC event OK flag             */
#define CRS_ISR_SYNCWARNF                   ((uint32_t)0x00000002) /* SYNC warning                   */
#define CRS_ISR_ERRF                        ((uint32_t)0x00000004) /* SYNC error flag                */
#define CRS_ISR_ESYNCF                      ((uint32_t)0x00000008) /* Expected SYNC flag             */
#define CRS_ISR_SYNCERR                     ((uint32_t)0x00000100) /* SYNC error                     */
#define CRS_ISR_SYNCMISS                    ((uint32_t)0x00000200) /* SYNC missed                    */
#define CRS_ISR_TRIMOVF                     ((uint32_t)0x00000400) /* Trimming overflow or underflow */
#define CRS_ISR_FEDIR                       ((uint32_t)0x00008000) /* Frequency error direction      */
#define CRS_ISR_FECAP                       ((uint32_t)0xFFFF0000) /* Frequency error capture        */

/*******************  Bit definition for CRS_ICR register  *********************/
#define CRS_ICR_SYNCOKC                     ((uint32_t)0x00000001) /* SYNC event OK clear flag     */
#define CRS_ICR_SYNCWARNC                   ((uint32_t)0x00000002) /* SYNC warning clear flag      */
#define CRS_ICR_ERRC                        ((uint32_t)0x00000004) /* Error clear flag             */
#define CRS_ICR_ESYNCC                      ((uint32_t)0x00000008) /* Expected SYNC clear flag     */

/******************************************************************************/
/*                                                                            */
/*                 Digital to Analog Converter (DAC)                          */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for DAC_CR register  ********************/
#define DAC_CR_EN1                          ((uint32_t)0x00000001)        /*!< DAC channel1 enable */
#define DAC_CR_BOFF1                        ((uint32_t)0x00000002)        /*!< DAC channel1 output buffer disable */
#define DAC_CR_TEN1                         ((uint32_t)0x00000004)        /*!< DAC channel1 Trigger enable */

#define DAC_CR_TSEL1                        ((uint32_t)0x00000038)        /*!< TSEL1[2:0] (DAC channel1 Trigger selection) */
#define DAC_CR_TSEL1_0                      ((uint32_t)0x00000008)        /*!< Bit 0 */
#define DAC_CR_TSEL1_1                      ((uint32_t)0x00000010)        /*!< Bit 1 */
#define DAC_CR_TSEL1_2                      ((uint32_t)0x00000020)        /*!< Bit 2 */

#define DAC_CR_WAVE1                        ((uint32_t)0x000000C0)        /*!< WAVE1[1:0] (DAC channel1 noise/triangle wave generation enable) */
#define DAC_CR_WAVE1_0                      ((uint32_t)0x00000040)        /*!< Bit 0 */
#define DAC_CR_WAVE1_1                      ((uint32_t)0x00000080)        /*!< Bit 1 */

#define DAC_CR_MAMP1                        ((uint32_t)0x00000F00)        /*!< MAMP1[3:0] (DAC channel1 Mask/Amplitude selector) */
#define DAC_CR_MAMP1_0                      ((uint32_t)0x00000100)        /*!< Bit 0 */
#define DAC_CR_MAMP1_1                      ((uint32_t)0x00000200)        /*!< Bit 1 */
#define DAC_CR_MAMP1_2                      ((uint32_t)0x00000400)        /*!< Bit 2 */
#define DAC_CR_MAMP1_3                      ((uint32_t)0x00000800)        /*!< Bit 3 */

#define DAC_CR_DMAEN1                       ((uint32_t)0x00001000)        /*!< DAC channel1 DMA enable */
#define DAC_CR_DMAUDRIE1                    ((uint32_t)0x00002000)        /*!< DAC channel1 DMA Underrun interrupt enable */

/*****************  Bit definition for DAC_SWTRIGR register  ******************/
#define DAC_SWTRIGR_SWTRIG1                 ((uint32_t)0x00000001)        /*!< DAC channel1 software trigger */

/*****************  Bit definition for DAC_DHR12R1 register  ******************/
#define DAC_DHR12R1_DACC1DHR                ((uint32_t)0x00000FFF)        /*!< DAC channel1 12-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12L1 register  ******************/
#define DAC_DHR12L1_DACC1DHR                ((uint32_t)0x0000FFF0)        /*!< DAC channel1 12-bit Left aligned data */

/******************  Bit definition for DAC_DHR8R1 register  ******************/
#define DAC_DHR8R1_DACC1DHR                 ((uint32_t)0x000000FF)        /*!< DAC channel1 8-bit Right aligned data */

/*******************  Bit definition for DAC_DOR1 register  *******************/
#define DAC_DOR1_DACC1DOR                   ((uint16_t)0x00000FFF)        /*!< DAC channel1 data output */

/********************  Bit definition for DAC_SR register  ********************/
#define DAC_SR_DMAUDR1                      ((uint32_t)0x00002000)        /*!< DAC channel1 DMA underrun flag */

/******************************************************************************/
/*                                                                            */
/*                           Debug MCU (DBGMCU)                               */
/*                                                                            */
/******************************************************************************/

/****************  Bit definition for DBGMCU_IDCODE register  *****************/
#define DBGMCU_IDCODE_DEV_ID                ((uint32_t)0x00000FFF)        /*!< Device Identifier */

#define DBGMCU_IDCODE_REV_ID                ((uint32_t)0xFFFF0000)        /*!< REV_ID[15:0] bits (Revision Identifier) */
#define DBGMCU_IDCODE_REV_ID_0              ((uint32_t)0x00010000)        /*!< Bit 0 */
#define DBGMCU_IDCODE_REV_ID_1              ((uint32_t)0x00020000)        /*!< Bit 1 */
#define DBGMCU_IDCODE_REV_ID_2              ((uint32_t)0x00040000)        /*!< Bit 2 */
#define DBGMCU_IDCODE_REV_ID_3              ((uint32_t)0x00080000)        /*!< Bit 3 */
#define DBGMCU_IDCODE_REV_ID_4              ((uint32_t)0x00100000)        /*!< Bit 4 */
#define DBGMCU_IDCODE_REV_ID_5              ((uint32_t)0x00200000)        /*!< Bit 5 */
#define DBGMCU_IDCODE_REV_ID_6              ((uint32_t)0x00400000)        /*!< Bit 6 */
#define DBGMCU_IDCODE_REV_ID_7              ((uint32_t)0x00800000)        /*!< Bit 7 */
#define DBGMCU_IDCODE_REV_ID_8              ((uint32_t)0x01000000)        /*!< Bit 8 */
#define DBGMCU_IDCODE_REV_ID_9              ((uint32_t)0x02000000)        /*!< Bit 9 */
#define DBGMCU_IDCODE_REV_ID_10             ((uint32_t)0x04000000)        /*!< Bit 10 */
#define DBGMCU_IDCODE_REV_ID_11             ((uint32_t)0x08000000)        /*!< Bit 11 */
#define DBGMCU_IDCODE_REV_ID_12             ((uint32_t)0x10000000)        /*!< Bit 12 */
#define DBGMCU_IDCODE_REV_ID_13             ((uint32_t)0x20000000)        /*!< Bit 13 */
#define DBGMCU_IDCODE_REV_ID_14             ((uint32_t)0x40000000)        /*!< Bit 14 */
#define DBGMCU_IDCODE_REV_ID_15             ((uint32_t)0x80000000)        /*!< Bit 15 */

/******************  Bit definition for DBGMCU_CR register  *******************/
#define DBGMCU_CR_DBG                       ((uint32_t)0x00000007)        /*!< Debug mode mask */
#define DBGMCU_CR_DBG_SLEEP                 ((uint32_t)0x00000001)        /*!< Debug Sleep Mode */
#define DBGMCU_CR_DBG_STOP                  ((uint32_t)0x00000002)        /*!< Debug Stop Mode */
#define DBGMCU_CR_DBG_STANDBY               ((uint32_t)0x00000004)        /*!< Debug Standby mode */

/******************  Bit definition for DBGMCU_APB1_FZ register  **************/
#define DBGMCU_APB1_FZ_DBG_TIM2_STOP        ((uint32_t)0x00000001)        /*!< TIM2 counter stopped when core is halted */
#define DBGMCU_APB1_FZ_DBG_TIM6_STOP        ((uint32_t)0x00000010)        /*!< TIM6 counter stopped when core is halted */
#define DBGMCU_APB1_FZ_DBG_RTC_STOP         ((uint32_t)0x00000400)        /*!< RTC Calendar frozen when core is halted */
#define DBGMCU_APB1_FZ_DBG_WWDG_STOP        ((uint32_t)0x00000800)        /*!< Debug Window Watchdog stopped when Core is halted */
#define DBGMCU_APB1_FZ_DBG_IWDG_STOP        ((uint32_t)0x00001000)        /*!< Debug Independent Watchdog stopped when Core is halted */
#define DBGMCU_APB1_FZ_DBG_I2C1_STOP        ((uint32_t)0x00200000)        /*!< I2C1 SMBUS timeout mode stopped when Core is halted */
#define DBGMCU_APB1_FZ_DBG_I2C2_STOP        ((uint32_t)0x00400000)        /*!< I2C2 SMBUS timeout mode stopped when Core is halted */
#define DBGMCU_APB1_FZ_DBG_LPTIMER_STOP     ((uint32_t)0x80000000)        /*!< LPTIM1 counter stopped when core is halted */
/******************  Bit definition for DBGMCU_APB2_FZ register  **************/
#define DBGMCU_APB2_FZ_DBG_TIM22_STOP       ((uint32_t)0x00000020)        /*!< TIM22 counter stopped when core is halted */
#define DBGMCU_APB2_FZ_DBG_TIM21_STOP       ((uint32_t)0x00000004)        /*!< TIM21 counter stopped when core is halted */

/******************************************************************************/
/*                                                                            */
/*                           DMA Controller (DMA)                             */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for DMA_ISR register  ********************/
#define DMA_ISR_GIF1                        ((uint32_t)0x00000001)        /*!< Channel 1 Global interrupt flag    */
#define DMA_ISR_TCIF1                       ((uint32_t)0x00000002)        /*!< Channel 1 Transfer Complete flag   */
#define DMA_ISR_HTIF1                       ((uint32_t)0x00000004)        /*!< Channel 1 Half Transfer flag       */
#define DMA_ISR_TEIF1                       ((uint32_t)0x00000008)        /*!< Channel 1 Transfer Error flag      */
#define DMA_ISR_GIF2                        ((uint32_t)0x00000010)        /*!< Channel 2 Global interrupt flag    */
#define DMA_ISR_TCIF2                       ((uint32_t)0x00000020)        /*!< Channel 2 Transfer Complete flag   */
#define DMA_ISR_HTIF2                       ((uint32_t)0x00000040)        /*!< Channel 2 Half Transfer flag       */
#define DMA_ISR_TEIF2                       ((uint32_t)0x00000080)        /*!< Channel 2 Transfer Error flag      */
#define DMA_ISR_GIF3                        ((uint32_t)0x00000100)        /*!< Channel 3 Global interrupt flag    */
#define DMA_ISR_TCIF3                       ((uint32_t)0x00000200)        /*!< Channel 3 Transfer Complete flag   */
#define DMA_ISR_HTIF3                       ((uint32_t)0x00000400)        /*!< Channel 3 Half Transfer flag       */
#define DMA_ISR_TEIF3                       ((uint32_t)0x00000800)        /*!< Channel 3 Transfer Error flag      */
#define DMA_ISR_GIF4                        ((uint32_t)0x00001000)        /*!< Channel 4 Global interrupt flag    */
#define DMA_ISR_TCIF4                       ((uint32_t)0x00002000)        /*!< Channel 4 Transfer Complete flag   */
#define DMA_ISR_HTIF4                       ((uint32_t)0x00004000)        /*!< Channel 4 Half Transfer flag       */
#define DMA_ISR_TEIF4                       ((uint32_t)0x00008000)        /*!< Channel 4 Transfer Error flag      */
#define DMA_ISR_GIF5                        ((uint32_t)0x00010000)        /*!< Channel 5 Global interrupt flag    */
#define DMA_ISR_TCIF5                       ((uint32_t)0x00020000)        /*!< Channel 5 Transfer Complete flag   */
#define DMA_ISR_HTIF5                       ((uint32_t)0x00040000)        /*!< Channel 5 Half Transfer flag       */
#define DMA_ISR_TEIF5                       ((uint32_t)0x00080000)        /*!< Channel 5 Transfer Error flag      */
#define DMA_ISR_GIF6                        ((uint32_t)0x00100000)        /*!< Channel 6 Global interrupt flag */
#define DMA_ISR_TCIF6                       ((uint32_t)0x00200000)        /*!< Channel 6 Transfer Complete flag */
#define DMA_ISR_HTIF6                       ((uint32_t)0x00400000)        /*!< Channel 6 Half Transfer flag */
#define DMA_ISR_TEIF6                       ((uint32_t)0x00800000)        /*!< Channel 6 Transfer Error flag */
#define DMA_ISR_GIF7                        ((uint32_t)0x01000000)        /*!< Channel 7 Global interrupt flag */
#define DMA_ISR_TCIF7                       ((uint32_t)0x02000000)        /*!< Channel 7 Transfer Complete flag */
#define DMA_ISR_HTIF7                       ((uint32_t)0x04000000)        /*!< Channel 7 Half Transfer flag */
#define DMA_ISR_TEIF7                       ((uint32_t)0x08000000)        /*!< Channel 7 Transfer Error flag */

/*******************  Bit definition for DMA_IFCR register  *******************/
#define DMA_IFCR_CGIF1                      ((uint32_t)0x00000001)        /*!< Channel 1 Global interrupt clear    */
#define DMA_IFCR_CTCIF1                     ((uint32_t)0x00000002)        /*!< Channel 1 Transfer Complete clear   */
#define DMA_IFCR_CHTIF1                     ((uint32_t)0x00000004)        /*!< Channel 1 Half Transfer clear       */
#define DMA_IFCR_CTEIF1                     ((uint32_t)0x00000008)        /*!< Channel 1 Transfer Error clear      */
#define DMA_IFCR_CGIF2                      ((uint32_t)0x00000010)        /*!< Channel 2 Global interrupt clear    */
#define DMA_IFCR_CTCIF2                     ((uint32_t)0x00000020)        /*!< Channel 2 Transfer Complete clear   */
#define DMA_IFCR_CHTIF2                     ((uint32_t)0x00000040)        /*!< Channel 2 Half Transfer clear       */
#define DMA_IFCR_CTEIF2                     ((uint32_t)0x00000080)        /*!< Channel 2 Transfer Error clear      */
#define DMA_IFCR_CGIF3                      ((uint32_t)0x00000100)        /*!< Channel 3 Global interrupt clear    */
#define DMA_IFCR_CTCIF3                     ((uint32_t)0x00000200)        /*!< Channel 3 Transfer Complete clear   */
#define DMA_IFCR_CHTIF3                     ((uint32_t)0x00000400)        /*!< Channel 3 Half Transfer clear       */
#define DMA_IFCR_CTEIF3                     ((uint32_t)0x00000800)        /*!< Channel 3 Transfer Error clear      */
#define DMA_IFCR_CGIF4                      ((uint32_t)0x00001000)        /*!< Channel 4 Global interrupt clear    */
#define DMA_IFCR_CTCIF4                     ((uint32_t)0x00002000)        /*!< Channel 4 Transfer Complete clear   */
#define DMA_IFCR_CHTIF4                     ((uint32_t)0x00004000)        /*!< Channel 4 Half Transfer clear       */
#define DMA_IFCR_CTEIF4                     ((uint32_t)0x00008000)        /*!< Channel 4 Transfer Error clear      */
#define DMA_IFCR_CGIF5                      ((uint32_t)0x00010000)        /*!< Channel 5 Global interrupt clear    */
#define DMA_IFCR_CTCIF5                     ((uint32_t)0x00020000)        /*!< Channel 5 Transfer Complete clear   */
#define DMA_IFCR_CHTIF5                     ((uint32_t)0x00040000)        /*!< Channel 5 Half Transfer clear       */
#define DMA_IFCR_CTEIF5                     ((uint32_t)0x00080000)        /*!< Channel 5 Transfer Error clear      */
#define DMA_IFCR_CGIF6                      ((uint32_t)0x00100000)        /*!< Channel 6 Global interrupt clear */
#define DMA_IFCR_CTCIF6                     ((uint32_t)0x00200000)        /*!< Channel 6 Transfer Complete clear */
#define DMA_IFCR_CHTIF6                     ((uint32_t)0x00400000)        /*!< Channel 6 Half Transfer clear */
#define DMA_IFCR_CTEIF6                     ((uint32_t)0x00800000)        /*!< Channel 6 Transfer Error clear */
#define DMA_IFCR_CGIF7                      ((uint32_t)0x01000000)        /*!< Channel 7 Global interrupt clear */
#define DMA_IFCR_CTCIF7                     ((uint32_t)0x02000000)        /*!< Channel 7 Transfer Complete clear */
#define DMA_IFCR_CHTIF7                     ((uint32_t)0x04000000)        /*!< Channel 7 Half Transfer clear */
#define DMA_IFCR_CTEIF7                     ((uint32_t)0x08000000)        /*!< Channel 7 Transfer Error clear */

/*******************  Bit definition for DMA_CCR register  ********************/
#define DMA_CCR_EN                          ((uint32_t)0x00000001)        /*!< Channel enable                      */
#define DMA_CCR_TCIE                        ((uint32_t)0x00000002)        /*!< Transfer complete interrupt enable  */
#define DMA_CCR_HTIE                        ((uint32_t)0x00000004)        /*!< Half Transfer interrupt enable      */
#define DMA_CCR_TEIE                        ((uint32_t)0x00000008)        /*!< Transfer error interrupt enable     */
#define DMA_CCR_DIR                         ((uint32_t)0x00000010)        /*!< Data transfer direction             */
#define DMA_CCR_CIRC                        ((uint32_t)0x00000020)        /*!< Circular mode                       */
#define DMA_CCR_PINC                        ((uint32_t)0x00000040)        /*!< Peripheral increment mode           */
#define DMA_CCR_MINC                        ((uint32_t)0x00000080)        /*!< Memory increment mode               */

#define DMA_CCR_PSIZE                       ((uint32_t)0x00000300)        /*!< PSIZE[1:0] bits (Peripheral size)   */
#define DMA_CCR_PSIZE_0                     ((uint32_t)0x00000100)        /*!< Bit 0                               */
#define DMA_CCR_PSIZE_1                     ((uint32_t)0x00000200)        /*!< Bit 1                               */

#define DMA_CCR_MSIZE                       ((uint32_t)0x00000C00)        /*!< MSIZE[1:0] bits (Memory size)       */
#define DMA_CCR_MSIZE_0                     ((uint32_t)0x00000400)        /*!< Bit 0                               */
#define DMA_CCR_MSIZE_1                     ((uint32_t)0x00000800)        /*!< Bit 1                               */

#define DMA_CCR_PL                          ((uint32_t)0x00003000)        /*!< PL[1:0] bits(Channel Priority level)*/
#define DMA_CCR_PL_0                        ((uint32_t)0x00001000)        /*!< Bit 0                               */
#define DMA_CCR_PL_1                        ((uint32_t)0x00002000)        /*!< Bit 1                               */

#define DMA_CCR_MEM2MEM                     ((uint32_t)0x00004000)        /*!< Memory to memory mode               */

/******************  Bit definition for DMA_CNDTR register  *******************/
#define DMA_CNDTR_NDT                       ((uint32_t)0x0000FFFF)        /*!< Number of data to Transfer          */

/******************  Bit definition for DMA_CPAR register  ********************/
#define DMA_CPAR_PA                         ((uint32_t)0xFFFFFFFF)        /*!< Peripheral Address                  */

/******************  Bit definition for DMA_CMAR register  ********************/
#define DMA_CMAR_MA                         ((uint32_t)0xFFFFFFFF)        /*!< Memory Address                      */


/*******************  Bit definition for DMA_CSELR register  *******************/
#define DMA_CSELR_C1S                       ((uint32_t)0x0000000F)          /*!< Channel 1 Selection */ 
#define DMA_CSELR_C2S                       ((uint32_t)0x000000F0)          /*!< Channel 2 Selection */ 
#define DMA_CSELR_C3S                       ((uint32_t)0x00000F00)          /*!< Channel 3 Selection */ 
#define DMA_CSELR_C4S                       ((uint32_t)0x0000F000)          /*!< Channel 4 Selection */ 
#define DMA_CSELR_C5S                       ((uint32_t)0x000F0000)          /*!< Channel 5 Selection */ 
#define DMA_CSELR_C6S                       ((uint32_t)0x00F00000)          /*!< Channel 6 Selection */ 
#define DMA_CSELR_C7S                       ((uint32_t)0x0F000000)          /*!< Channel 7 Selection */


/******************************************************************************/
/*                                                                            */
/*                 External Interrupt/Event Controller (EXTI)                 */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for EXTI_IMR register  *******************/
#define EXTI_IMR_IM0                        ((uint32_t)0x00000001)        /*!< Interrupt Mask on line 0  */
#define EXTI_IMR_IM1                        ((uint32_t)0x00000002)        /*!< Interrupt Mask on line 1  */
#define EXTI_IMR_IM2                        ((uint32_t)0x00000004)        /*!< Interrupt Mask on line 2  */
#define EXTI_IMR_IM3                        ((uint32_t)0x00000008)        /*!< Interrupt Mask on line 3  */
#define EXTI_IMR_IM4                        ((uint32_t)0x00000010)        /*!< Interrupt Mask on line 4  */
#define EXTI_IMR_IM5                        ((uint32_t)0x00000020)        /*!< Interrupt Mask on line 5  */
#define EXTI_IMR_IM6                        ((uint32_t)0x00000040)        /*!< Interrupt Mask on line 6  */
#define EXTI_IMR_IM7                        ((uint32_t)0x00000080)        /*!< Interrupt Mask on line 7  */
#define EXTI_IMR_IM8                        ((uint32_t)0x00000100)        /*!< Interrupt Mask on line 8  */
#define EXTI_IMR_IM9                        ((uint32_t)0x00000200)        /*!< Interrupt Mask on line 9  */
#define EXTI_IMR_IM10                       ((uint32_t)0x00000400)        /*!< Interrupt Mask on line 10 */
#define EXTI_IMR_IM11                       ((uint32_t)0x00000800)        /*!< Interrupt Mask on line 11 */
#define EXTI_IMR_IM12                       ((uint32_t)0x00001000)        /*!< Interrupt Mask on line 12 */
#define EXTI_IMR_IM13                       ((uint32_t)0x00002000)        /*!< Interrupt Mask on line 13 */
#define EXTI_IMR_IM14                       ((uint32_t)0x00004000)        /*!< Interrupt Mask on line 14 */
#define EXTI_IMR_IM15                       ((uint32_t)0x00008000)        /*!< Interrupt Mask on line 15 */
#define EXTI_IMR_IM16                       ((uint32_t)0x00010000)        /*!< Interrupt Mask on line 16 */
#define EXTI_IMR_IM17                       ((uint32_t)0x00020000)        /*!< Interrupt Mask on line 17 */
#define EXTI_IMR_IM18                       ((uint32_t)0x00040000)        /*!< Interrupt Mask on line 18 */
#define EXTI_IMR_IM19                       ((uint32_t)0x00080000)        /*!< Interrupt Mask on line 19 */
#define EXTI_IMR_IM20                       ((uint32_t)0x00100000)        /*!< Interrupt Mask on line 20 */
#define EXTI_IMR_IM21                       ((uint32_t)0x00200000)        /*!< Interrupt Mask on line 21 */
#define EXTI_IMR_IM22                       ((uint32_t)0x00400000)        /*!< Interrupt Mask on line 22 */
#define EXTI_IMR_IM23                       ((uint32_t)0x00800000)        /*!< Interrupt Mask on line 23 */
#define EXTI_IMR_IM25                       ((uint32_t)0x02000000)        /*!< Interrupt Mask on line 25 */
#define EXTI_IMR_IM26                       ((uint32_t)0x04000000)        /*!< Interrupt Mask on line 26 */
#define EXTI_IMR_IM28                       ((uint32_t)0x10000000)        /*!< Interrupt Mask on line 28 */
#define EXTI_IMR_IM29                       ((uint32_t)0x20000000)        /*!< Interrupt Mask on line 29 */

/******************  Bit definition for EXTI_EMR register  ********************/
#define EXTI_EMR_EM0                        ((uint32_t)0x00000001)        /*!< Event Mask on line 0  */
#define EXTI_EMR_EM1                        ((uint32_t)0x00000002)        /*!< Event Mask on line 1  */
#define EXTI_EMR_EM2                        ((uint32_t)0x00000004)        /*!< Event Mask on line 2  */
#define EXTI_EMR_EM3                        ((uint32_t)0x00000008)        /*!< Event Mask on line 3  */
#define EXTI_EMR_EM4                        ((uint32_t)0x00000010)        /*!< Event Mask on line 4  */
#define EXTI_EMR_EM5                        ((uint32_t)0x00000020)        /*!< Event Mask on line 5  */
#define EXTI_EMR_EM6                        ((uint32_t)0x00000040)        /*!< Event Mask on line 6  */
#define EXTI_EMR_EM7                        ((uint32_t)0x00000080)        /*!< Event Mask on line 7  */
#define EXTI_EMR_EM8                        ((uint32_t)0x00000100)        /*!< Event Mask on line 8  */
#define EXTI_EMR_EM9                        ((uint32_t)0x00000200)        /*!< Event Mask on line 9  */
#define EXTI_EMR_EM10                       ((uint32_t)0x00000400)        /*!< Event Mask on line 10 */
#define EXTI_EMR_EM11                       ((uint32_t)0x00000800)        /*!< Event Mask on line 11 */
#define EXTI_EMR_EM12                       ((uint32_t)0x00001000)        /*!< Event Mask on line 12 */
#define EXTI_EMR_EM13                       ((uint32_t)0x00002000)        /*!< Event Mask on line 13 */
#define EXTI_EMR_EM14                       ((uint32_t)0x00004000)        /*!< Event Mask on line 14 */
#define EXTI_EMR_EM15                       ((uint32_t)0x00008000)        /*!< Event Mask on line 15 */
#define EXTI_EMR_EM16                       ((uint32_t)0x00010000)        /*!< Event Mask on line 16 */
#define EXTI_EMR_EM17                       ((uint32_t)0x00020000)        /*!< Event Mask on line 17 */
#define EXTI_EMR_EM18                       ((uint32_t)0x00040000)        /*!< Event Mask on line 18 */
#define EXTI_EMR_EM19                       ((uint32_t)0x00080000)        /*!< Event Mask on line 19 */
#define EXTI_EMR_EM20                       ((uint32_t)0x00100000)        /*!< Event Mask on line 20 */
#define EXTI_EMR_EM21                       ((uint32_t)0x00200000)        /*!< Event Mask on line 21 */
#define EXTI_EMR_EM22                       ((uint32_t)0x00400000)        /*!< Event Mask on line 22 */
#define EXTI_EMR_EM23                       ((uint32_t)0x00800000)        /*!< Event Mask on line 23 */
#define EXTI_EMR_EM25                       ((uint32_t)0x02000000)        /*!< Event Mask on line 25 */
#define EXTI_EMR_EM26                       ((uint32_t)0x04000000)        /*!< Event Mask on line 26 */
#define EXTI_EMR_EM28                       ((uint32_t)0x10000000)        /*!< Event Mask on line 28 */
#define EXTI_EMR_EM29                       ((uint32_t)0x20000000)        /*!< Event Mask on line 29 */

/*******************  Bit definition for EXTI_RTSR register  ******************/
#define EXTI_RTSR_TR0                       ((uint32_t)0x00000001)        /*!< Rising trigger event configuration bit of line 0 */
#define EXTI_RTSR_TR1                       ((uint32_t)0x00000002)        /*!< Rising trigger event configuration bit of line 1 */
#define EXTI_RTSR_TR2                       ((uint32_t)0x00000004)        /*!< Rising trigger event configuration bit of line 2 */
#define EXTI_RTSR_TR3                       ((uint32_t)0x00000008)        /*!< Rising trigger event configuration bit of line 3 */
#define EXTI_RTSR_TR4                       ((uint32_t)0x00000010)        /*!< Rising trigger event configuration bit of line 4 */
#define EXTI_RTSR_TR5                       ((uint32_t)0x00000020)        /*!< Rising trigger event configuration bit of line 5 */
#define EXTI_RTSR_TR6                       ((uint32_t)0x00000040)        /*!< Rising trigger event configuration bit of line 6 */
#define EXTI_RTSR_TR7                       ((uint32_t)0x00000080)        /*!< Rising trigger event configuration bit of line 7 */
#define EXTI_RTSR_TR8                       ((uint32_t)0x00000100)        /*!< Rising trigger event configuration bit of line 8 */
#define EXTI_RTSR_TR9                       ((uint32_t)0x00000200)        /*!< Rising trigger event configuration bit of line 9 */
#define EXTI_RTSR_TR10                      ((uint32_t)0x00000400)        /*!< Rising trigger event configuration bit of line 10 */
#define EXTI_RTSR_TR11                      ((uint32_t)0x00000800)        /*!< Rising trigger event configuration bit of line 11 */
#define EXTI_RTSR_TR12                      ((uint32_t)0x00001000)        /*!< Rising trigger event configuration bit of line 12 */
#define EXTI_RTSR_TR13                      ((uint32_t)0x00002000)        /*!< Rising trigger event configuration bit of line 13 */
#define EXTI_RTSR_TR14                      ((uint32_t)0x00004000)        /*!< Rising trigger event configuration bit of line 14 */
#define EXTI_RTSR_TR15                      ((uint32_t)0x00008000)        /*!< Rising trigger event configuration bit of line 15 */
#define EXTI_RTSR_TR16                      ((uint32_t)0x00010000)        /*!< Rising trigger event configuration bit of line 16 */
#define EXTI_RTSR_TR17                      ((uint32_t)0x00020000)        /*!< Rising trigger event configuration bit of line 17 */
#define EXTI_RTSR_TR19                      ((uint32_t)0x00080000)        /*!< Rising trigger event configuration bit of line 19 */
#define EXTI_RTSR_TR20                      ((uint32_t)0x00100000)        /*!< Rising trigger event configuration bit of line 20 */
#define EXTI_RTSR_TR21                      ((uint32_t)0x00200000)        /*!< Rising trigger event configuration bit of line 21 */
#define EXTI_RTSR_TR22                      ((uint32_t)0x00400000)        /*!< Rising trigger event configuration bit of line 22 */

/*******************  Bit definition for EXTI_FTSR register *******************/
#define EXTI_FTSR_TR0                       ((uint32_t)0x00000001)        /*!< Falling trigger event configuration bit of line 0 */
#define EXTI_FTSR_TR1                       ((uint32_t)0x00000002)        /*!< Falling trigger event configuration bit of line 1 */
#define EXTI_FTSR_TR2                       ((uint32_t)0x00000004)        /*!< Falling trigger event configuration bit of line 2 */
#define EXTI_FTSR_TR3                       ((uint32_t)0x00000008)        /*!< Falling trigger event configuration bit of line 3 */
#define EXTI_FTSR_TR4                       ((uint32_t)0x00000010)        /*!< Falling trigger event configuration bit of line 4 */
#define EXTI_FTSR_TR5                       ((uint32_t)0x00000020)        /*!< Falling trigger event configuration bit of line 5 */
#define EXTI_FTSR_TR6                       ((uint32_t)0x00000040)        /*!< Falling trigger event configuration bit of line 6 */
#define EXTI_FTSR_TR7                       ((uint32_t)0x00000080)        /*!< Falling trigger event configuration bit of line 7 */
#define EXTI_FTSR_TR8                       ((uint32_t)0x00000100)        /*!< Falling trigger event configuration bit of line 8 */
#define EXTI_FTSR_TR9                       ((uint32_t)0x00000200)        /*!< Falling trigger event configuration bit of line 9 */
#define EXTI_FTSR_TR10                      ((uint32_t)0x00000400)        /*!< Falling trigger event configuration bit of line 10 */
#define EXTI_FTSR_TR11                      ((uint32_t)0x00000800)        /*!< Falling trigger event configuration bit of line 11 */
#define EXTI_FTSR_TR12                      ((uint32_t)0x00001000)        /*!< Falling trigger event configuration bit of line 12 */
#define EXTI_FTSR_TR13                      ((uint32_t)0x00002000)        /*!< Falling trigger event configuration bit of line 13 */
#define EXTI_FTSR_TR14                      ((uint32_t)0x00004000)        /*!< Falling trigger event configuration bit of line 14 */
#define EXTI_FTSR_TR15                      ((uint32_t)0x00008000)        /*!< Falling trigger event configuration bit of line 15 */
#define EXTI_FTSR_TR16                      ((uint32_t)0x00010000)        /*!< Falling trigger event configuration bit of line 16 */
#define EXTI_FTSR_TR17                      ((uint32_t)0x00020000)        /*!< Falling trigger event configuration bit of line 17 */
#define EXTI_FTSR_TR19                      ((uint32_t)0x00080000)        /*!< Falling trigger event configuration bit of line 19 */
#define EXTI_FTSR_TR20                      ((uint32_t)0x00100000)        /*!< Falling trigger event configuration bit of line 20 */
#define EXTI_FTSR_TR21                      ((uint32_t)0x00200000)        /*!< Falling trigger event configuration bit of line 21 */
#define EXTI_FTSR_TR22                      ((uint32_t)0x00400000)        /*!< Falling trigger event configuration bit of line 22 */

/******************* Bit definition for EXTI_SWIER register *******************/
#define EXTI_SWIER_SWIER0                   ((uint32_t)0x00000001)        /*!< Software Interrupt on line 0  */
#define EXTI_SWIER_SWIER1                   ((uint32_t)0x00000002)        /*!< Software Interrupt on line 1  */
#define EXTI_SWIER_SWIER2                   ((uint32_t)0x00000004)        /*!< Software Interrupt on line 2  */
#define EXTI_SWIER_SWIER3                   ((uint32_t)0x00000008)        /*!< Software Interrupt on line 3  */
#define EXTI_SWIER_SWIER4                   ((uint32_t)0x00000010)        /*!< Software Interrupt on line 4  */
#define EXTI_SWIER_SWIER5                   ((uint32_t)0x00000020)        /*!< Software Interrupt on line 5  */
#define EXTI_SWIER_SWIER6                   ((uint32_t)0x00000040)        /*!< Software Interrupt on line 6  */
#define EXTI_SWIER_SWIER7                   ((uint32_t)0x00000080)        /*!< Software Interrupt on line 7  */
#define EXTI_SWIER_SWIER8                   ((uint32_t)0x00000100)        /*!< Software Interrupt on line 8  */
#define EXTI_SWIER_SWIER9                   ((uint32_t)0x00000200)        /*!< Software Interrupt on line 9  */
#define EXTI_SWIER_SWIER10                  ((uint32_t)0x00000400)        /*!< Software Interrupt on line 10 */
#define EXTI_SWIER_SWIER11                  ((uint32_t)0x00000800)        /*!< Software Interrupt on line 11 */
#define EXTI_SWIER_SWIER12                  ((uint32_t)0x00001000)        /*!< Software Interrupt on line 12 */
#define EXTI_SWIER_SWIER13                  ((uint32_t)0x00002000)        /*!< Software Interrupt on line 13 */
#define EXTI_SWIER_SWIER14                  ((uint32_t)0x00004000)        /*!< Software Interrupt on line 14 */
#define EXTI_SWIER_SWIER15                  ((uint32_t)0x00008000)        /*!< Software Interrupt on line 15 */
#define EXTI_SWIER_SWIER16                  ((uint32_t)0x00010000)        /*!< Software Interrupt on line 16 */
#define EXTI_SWIER_SWIER17                  ((uint32_t)0x00020000)        /*!< Software Interrupt on line 17 */
#define EXTI_SWIER_SWIER19                  ((uint32_t)0x00080000)        /*!< Software Interrupt on line 19 */
#define EXTI_SWIER_SWIER20                  ((uint32_t)0x00100000)        /*!< Software Interrupt on line 20 */
#define EXTI_SWIER_SWIER21                  ((uint32_t)0x00200000)        /*!< Software Interrupt on line 21 */
#define EXTI_SWIER_SWIER22                  ((uint32_t)0x00400000)        /*!< Software Interrupt on line 22 */

/******************  Bit definition for EXTI_PR register  *********************/
#define EXTI_PR_PR0                         ((uint32_t)0x00000001)        /*!< Pending bit 0  */
#define EXTI_PR_PR1                         ((uint32_t)0x00000002)        /*!< Pending bit 1  */
#define EXTI_PR_PR2                         ((uint32_t)0x00000004)        /*!< Pending bit 2  */
#define EXTI_PR_PR3                         ((uint32_t)0x00000008)        /*!< Pending bit 3  */
#define EXTI_PR_PR4                         ((uint32_t)0x00000010)        /*!< Pending bit 4  */
#define EXTI_PR_PR5                         ((uint32_t)0x00000020)        /*!< Pending bit 5  */
#define EXTI_PR_PR6                         ((uint32_t)0x00000040)        /*!< Pending bit 6  */
#define EXTI_PR_PR7                         ((uint32_t)0x00000080)        /*!< Pending bit 7  */
#define EXTI_PR_PR8                         ((uint32_t)0x00000100)        /*!< Pending bit 8  */
#define EXTI_PR_PR9                         ((uint32_t)0x00000200)        /*!< Pending bit 9  */
#define EXTI_PR_PR10                        ((uint32_t)0x00000400)        /*!< Pending bit 10 */
#define EXTI_PR_PR11                        ((uint32_t)0x00000800)        /*!< Pending bit 11 */
#define EXTI_PR_PR12                        ((uint32_t)0x00001000)        /*!< Pending bit 12 */
#define EXTI_PR_PR13                        ((uint32_t)0x00002000)        /*!< Pending bit 13 */
#define EXTI_PR_PR14                        ((uint32_t)0x00004000)        /*!< Pending bit 14 */
#define EXTI_PR_PR15                        ((uint32_t)0x00008000)        /*!< Pending bit 15 */
#define EXTI_PR_PR16                        ((uint32_t)0x00010000)        /*!< Pending bit 16 */
#define EXTI_PR_PR17                        ((uint32_t)0x00020000)        /*!< Pending bit 17 */
#define EXTI_PR_PR19                        ((uint32_t)0x00080000)        /*!< Pending bit 19 */
#define EXTI_PR_PR20                        ((uint32_t)0x00100000)        /*!< Pending bit 20 */
#define EXTI_PR_PR21                        ((uint32_t)0x00200000)        /*!< Pending bit 21 */
#define EXTI_PR_PR22                        ((uint32_t)0x00400000)        /*!< Pending bit 22 */

/******************************************************************************/
/*                                                                            */
/*                      FLASH and Option Bytes Registers                      */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for FLASH_ACR register  ******************/
#define FLASH_ACR_LATENCY                   ((uint32_t)0x00000001)        /*!< LATENCY bit (Latency) */
#define FLASH_ACR_PRFTEN                    ((uint32_t)0x00000002)        /*!< Prefetch Buffer Enable */
#define FLASH_ACR_SLEEP_PD                  ((uint32_t)0x00000008)        /*!< Flash mode during sleep mode */
#define FLASH_ACR_RUN_PD                    ((uint32_t)0x00000010)        /*!< Flash mode during RUN mode */
#define FLASH_ACR_DISAB_BUF                 ((uint32_t)0x00000020)        /*!< Disable Buffer */
#define FLASH_ACR_PRE_READ                  ((uint32_t)0x00000040)        /*!< Pre-read data address */

/*******************  Bit definition for FLASH_PECR register  ******************/
#define FLASH_PECR_PELOCK                    ((uint32_t)0x00000001)        /*!< FLASH_PECR and Flash data Lock */
#define FLASH_PECR_PRGLOCK                   ((uint32_t)0x00000002)        /*!< Program matrix Lock */
#define FLASH_PECR_OPTLOCK                   ((uint32_t)0x00000004)        /*!< Option byte matrix Lock */
#define FLASH_PECR_PROG                      ((uint32_t)0x00000008)        /*!< Program matrix selection */
#define FLASH_PECR_DATA                      ((uint32_t)0x00000010)        /*!< Data matrix selection */
#define FLASH_PECR_FIX                       ((uint32_t)0x00000100)        /*!< Fixed Time Data write for Word/Half Word/Byte programming */
#define FLASH_PECR_ERASE                     ((uint32_t)0x00000200)        /*!< Page erasing mode */
#define FLASH_PECR_FPRG                      ((uint32_t)0x00000400)        /*!< Fast Page/Half Page programming mode */
#define FLASH_PECR_EOPIE                     ((uint32_t)0x00010000)        /*!< End of programming interrupt */ 
#define FLASH_PECR_ERRIE                     ((uint32_t)0x00020000)        /*!< Error interrupt */ 
#define FLASH_PECR_OBL_LAUNCH                ((uint32_t)0x00040000)        /*!< Launch the option byte loading */
#define FLASH_PECR_HALF_ARRAY                ((uint32_t)0x00080000)        /*!< Half array mode */

/******************  Bit definition for FLASH_PDKEYR register  ******************/
#define FLASH_PDKEYR_PDKEYR                 ((uint32_t)0xFFFFFFFF)       /*!< FLASH_PEC and data matrix Key */

/******************  Bit definition for FLASH_PEKEYR register  ******************/
#define FLASH_PEKEYR_PEKEYR                 ((uint32_t)0xFFFFFFFF)       /*!< FLASH_PEC and data matrix Key */

/******************  Bit definition for FLASH_PRGKEYR register  ******************/
#define FLASH_PRGKEYR_PRGKEYR               ((uint32_t)0xFFFFFFFF)        /*!< Program matrix Key */

/******************  Bit definition for FLASH_OPTKEYR register  ******************/
#define FLASH_OPTKEYR_OPTKEYR               ((uint32_t)0xFFFFFFFF)        /*!< Option bytes matrix Key */

/******************  Bit definition for FLASH_SR register  *******************/
#define FLASH_SR_BSY                        ((uint32_t)0x00000001)        /*!< Busy */
#define FLASH_SR_EOP                        ((uint32_t)0x00000002)        /*!< End Of Programming*/
#define FLASH_SR_HVOFF                      ((uint32_t)0x00000004)        /*!< End of high voltage */
#define FLASH_SR_READY                      ((uint32_t)0x00000008)        /*!< Flash ready after low power mode */

#define FLASH_SR_WRPERR                     ((uint32_t)0x00000100)        /*!< Write protection error */
#define FLASH_SR_PGAERR                     ((uint32_t)0x00000200)        /*!< Programming Alignment Error */
#define FLASH_SR_SIZERR                     ((uint32_t)0x00000400)        /*!< Size error */
#define FLASH_SR_OPTVERR                    ((uint32_t)0x00000800)        /*!< Option Valid error */
#define FLASH_SR_RDERR                      ((uint32_t)0x00002000)        /*!< Read protected error */
#define FLASH_SR_NOTZEROERR                 ((uint32_t)0x00010000)        /*!< Not Zero error */
#define FLASH_SR_FWWERR                     ((uint32_t)0x00020000)        /*!< Write/Errase operation aborted */

/* alias maintained for legacy */
#define FLASH_SR_FWWER                      FLASH_SR_FWWERR
#define FLASH_SR_ENHV                       FLASH_SR_HVOFF
#define FLASH_SR_ENDHV                      FLASH_SR_HVOFF

/******************  Bit definition for FLASH_OPTR register  *******************/
#define FLASH_OPTR_RDPROT                   ((uint32_t)0x000000FF)        /*!< Read Protection */
#define FLASH_OPTR_WPRMOD                   ((uint32_t)0x00000100)        /*!< Selection of protection mode of WPR bits */
#define FLASH_OPTR_BOR_LEV                  ((uint32_t)0x000F0000)        /*!< BOR_LEV[3:0] Brown Out Reset Threshold Level*/
#define FLASH_OPTR_IWDG_SW                  ((uint32_t)0x00100000)        /*!< IWDG_SW */
#define FLASH_OPTR_nRST_STOP                ((uint32_t)0x00200000)        /*!< nRST_STOP */
#define FLASH_OPTR_nRST_STDBY               ((uint32_t)0x00400000)        /*!< nRST_STDBY */
#define FLASH_OPTR_USER                     ((uint32_t)0x00700000)        /*!< User Option Bytes */
#define FLASH_OPTR_BOOT1                    ((uint32_t)0x80000000)        /*!< BOOT1 */

/******************  Bit definition for FLASH_WRPR register  ******************/
#define FLASH_WRPR_WRP                      ((uint32_t)0x0000FFFF)        /*!< Write Protection bits */

/******************************************************************************/
/*                                                                            */
/*                       General Purpose IOs (GPIO)                           */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for GPIO_MODER register  *****************/
#define GPIO_MODER_MODE0          ((uint32_t)0x00000003)
#define GPIO_MODER_MODE0_0        ((uint32_t)0x00000001)
#define GPIO_MODER_MODE0_1        ((uint32_t)0x00000002)
#define GPIO_MODER_MODE1          ((uint32_t)0x0000000C)
#define GPIO_MODER_MODE1_0        ((uint32_t)0x00000004)
#define GPIO_MODER_MODE1_1        ((uint32_t)0x00000008)
#define GPIO_MODER_MODE2          ((uint32_t)0x00000030)
#define GPIO_MODER_MODE2_0        ((uint32_t)0x00000010)
#define GPIO_MODER_MODE2_1        ((uint32_t)0x00000020)
#define GPIO_MODER_MODE3          ((uint32_t)0x000000C0)
#define GPIO_MODER_MODE3_0        ((uint32_t)0x00000040)
#define GPIO_MODER_MODE3_1        ((uint32_t)0x00000080)
#define GPIO_MODER_MODE4          ((uint32_t)0x00000300)
#define GPIO_MODER_MODE4_0        ((uint32_t)0x00000100)
#define GPIO_MODER_MODE4_1        ((uint32_t)0x00000200)
#define GPIO_MODER_MODE5          ((uint32_t)0x00000C00)
#define GPIO_MODER_MODE5_0        ((uint32_t)0x00000400)
#define GPIO_MODER_MODE5_1        ((uint32_t)0x00000800)
#define GPIO_MODER_MODE6          ((uint32_t)0x00003000)
#define GPIO_MODER_MODE6_0        ((uint32_t)0x00001000)
#define GPIO_MODER_MODE6_1        ((uint32_t)0x00002000)
#define GPIO_MODER_MODE7          ((uint32_t)0x0000C000)
#define GPIO_MODER_MODE7_0        ((uint32_t)0x00004000)
#define GPIO_MODER_MODE7_1        ((uint32_t)0x00008000)
#define GPIO_MODER_MODE8          ((uint32_t)0x00030000)
#define GPIO_MODER_MODE8_0        ((uint32_t)0x00010000)
#define GPIO_MODER_MODE8_1        ((uint32_t)0x00020000)
#define GPIO_MODER_MODE9          ((uint32_t)0x000C0000)
#define GPIO_MODER_MODE9_0        ((uint32_t)0x00040000)
#define GPIO_MODER_MODE9_1        ((uint32_t)0x00080000)
#define GPIO_MODER_MODE10         ((uint32_t)0x00300000)
#define GPIO_MODER_MODE10_0       ((uint32_t)0x00100000)
#define GPIO_MODER_MODE10_1       ((uint32_t)0x00200000)
#define GPIO_MODER_MODE11         ((uint32_t)0x00C00000)
#define GPIO_MODER_MODE11_0       ((uint32_t)0x00400000)
#define GPIO_MODER_MODE11_1       ((uint32_t)0x00800000)
#define GPIO_MODER_MODE12         ((uint32_t)0x03000000)
#define GPIO_MODER_MODE12_0       ((uint32_t)0x01000000)
#define GPIO_MODER_MODE12_1       ((uint32_t)0x02000000)
#define GPIO_MODER_MODE13         ((uint32_t)0x0C000000)
#define GPIO_MODER_MODE13_0       ((uint32_t)0x04000000)
#define GPIO_MODER_MODE13_1       ((uint32_t)0x08000000)
#define GPIO_MODER_MODE14         ((uint32_t)0x30000000)
#define GPIO_MODER_MODE14_0       ((uint32_t)0x10000000)
#define GPIO_MODER_MODE14_1       ((uint32_t)0x20000000)
#define GPIO_MODER_MODE15         ((uint32_t)0xC0000000)
#define GPIO_MODER_MODE15_0       ((uint32_t)0x40000000)
#define GPIO_MODER_MODE15_1       ((uint32_t)0x80000000)

/******************  Bit definition for GPIO_OTYPER register  *****************/
#define GPIO_OTYPER_OT_0          ((uint32_t)0x00000001)
#define GPIO_OTYPER_OT_1          ((uint32_t)0x00000002)
#define GPIO_OTYPER_OT_2          ((uint32_t)0x00000004)
#define GPIO_OTYPER_OT_3          ((uint32_t)0x00000008)
#define GPIO_OTYPER_OT_4          ((uint32_t)0x00000010)
#define GPIO_OTYPER_OT_5          ((uint32_t)0x00000020)
#define GPIO_OTYPER_OT_6          ((uint32_t)0x00000040)
#define GPIO_OTYPER_OT_7          ((uint32_t)0x00000080)
#define GPIO_OTYPER_OT_8          ((uint32_t)0x00000100)
#define GPIO_OTYPER_OT_9          ((uint32_t)0x00000200)
#define GPIO_OTYPER_OT_10         ((uint32_t)0x00000400)
#define GPIO_OTYPER_OT_11         ((uint32_t)0x00000800)
#define GPIO_OTYPER_OT_12         ((uint32_t)0x00001000)
#define GPIO_OTYPER_OT_13         ((uint32_t)0x00002000)
#define GPIO_OTYPER_OT_14         ((uint32_t)0x00004000)
#define GPIO_OTYPER_OT_15         ((uint32_t)0x00008000)

/****************  Bit definition for GPIO_OSPEEDR register  ******************/
#define GPIO_OSPEEDER_OSPEED0     ((uint32_t)0x00000003)
#define GPIO_OSPEEDER_OSPEED0_0   ((uint32_t)0x00000001)
#define GPIO_OSPEEDER_OSPEED0_1   ((uint32_t)0x00000002)
#define GPIO_OSPEEDER_OSPEED1     ((uint32_t)0x0000000C)
#define GPIO_OSPEEDER_OSPEED1_0   ((uint32_t)0x00000004)
#define GPIO_OSPEEDER_OSPEED1_1   ((uint32_t)0x00000008)
#define GPIO_OSPEEDER_OSPEED2     ((uint32_t)0x00000030)
#define GPIO_OSPEEDER_OSPEED2_0   ((uint32_t)0x00000010)
#define GPIO_OSPEEDER_OSPEED2_1   ((uint32_t)0x00000020)
#define GPIO_OSPEEDER_OSPEED3     ((uint32_t)0x000000C0)
#define GPIO_OSPEEDER_OSPEED3_0   ((uint32_t)0x00000040)
#define GPIO_OSPEEDER_OSPEED3_1   ((uint32_t)0x00000080)
#define GPIO_OSPEEDER_OSPEED4     ((uint32_t)0x00000300)
#define GPIO_OSPEEDER_OSPEED4_0   ((uint32_t)0x00000100)
#define GPIO_OSPEEDER_OSPEED4_1   ((uint32_t)0x00000200)
#define GPIO_OSPEEDER_OSPEED5     ((uint32_t)0x00000C00)
#define GPIO_OSPEEDER_OSPEED5_0   ((uint32_t)0x00000400)
#define GPIO_OSPEEDER_OSPEED5_1   ((uint32_t)0x00000800)
#define GPIO_OSPEEDER_OSPEED6     ((uint32_t)0x00003000)
#define GPIO_OSPEEDER_OSPEED6_0   ((uint32_t)0x00001000)
#define GPIO_OSPEEDER_OSPEED6_1   ((uint32_t)0x00002000)
#define GPIO_OSPEEDER_OSPEED7     ((uint32_t)0x0000C000)
#define GPIO_OSPEEDER_OSPEED7_0   ((uint32_t)0x00004000)
#define GPIO_OSPEEDER_OSPEED7_1   ((uint32_t)0x00008000)
#define GPIO_OSPEEDER_OSPEED8     ((uint32_t)0x00030000)
#define GPIO_OSPEEDER_OSPEED8_0   ((uint32_t)0x00010000)
#define GPIO_OSPEEDER_OSPEED8_1   ((uint32_t)0x00020000)
#define GPIO_OSPEEDER_OSPEED9     ((uint32_t)0x000C0000)
#define GPIO_OSPEEDER_OSPEED9_0   ((uint32_t)0x00040000)
#define GPIO_OSPEEDER_OSPEED9_1   ((uint32_t)0x00080000)
#define GPIO_OSPEEDER_OSPEED10    ((uint32_t)0x00300000)
#define GPIO_OSPEEDER_OSPEED10_0  ((uint32_t)0x00100000)
#define GPIO_OSPEEDER_OSPEED10_1  ((uint32_t)0x00200000)
#define GPIO_OSPEEDER_OSPEED11    ((uint32_t)0x00C00000)
#define GPIO_OSPEEDER_OSPEED11_0  ((uint32_t)0x00400000)
#define GPIO_OSPEEDER_OSPEED11_1  ((uint32_t)0x00800000)
#define GPIO_OSPEEDER_OSPEED12    ((uint32_t)0x03000000)
#define GPIO_OSPEEDER_OSPEED12_0  ((uint32_t)0x01000000)
#define GPIO_OSPEEDER_OSPEED12_1  ((uint32_t)0x02000000)
#define GPIO_OSPEEDER_OSPEED13    ((uint32_t)0x0C000000)
#define GPIO_OSPEEDER_OSPEED13_0  ((uint32_t)0x04000000)
#define GPIO_OSPEEDER_OSPEED13_1  ((uint32_t)0x08000000)
#define GPIO_OSPEEDER_OSPEED14    ((uint32_t)0x30000000)
#define GPIO_OSPEEDER_OSPEED14_0  ((uint32_t)0x10000000)
#define GPIO_OSPEEDER_OSPEED14_1  ((uint32_t)0x20000000)
#define GPIO_OSPEEDER_OSPEED15    ((uint32_t)0xC0000000)
#define GPIO_OSPEEDER_OSPEED15_0  ((uint32_t)0x40000000)
#define GPIO_OSPEEDER_OSPEED15_1  ((uint32_t)0x80000000)

/*******************  Bit definition for GPIO_PUPDR register ******************/
#define GPIO_PUPDR_PUPD0          ((uint32_t)0x00000003)
#define GPIO_PUPDR_PUPD0_0        ((uint32_t)0x00000001)
#define GPIO_PUPDR_PUPD0_1        ((uint32_t)0x00000002)
#define GPIO_PUPDR_PUPD1          ((uint32_t)0x0000000C)
#define GPIO_PUPDR_PUPD1_0        ((uint32_t)0x00000004)
#define GPIO_PUPDR_PUPD1_1        ((uint32_t)0x00000008)
#define GPIO_PUPDR_PUPD2          ((uint32_t)0x00000030)
#define GPIO_PUPDR_PUPD2_0        ((uint32_t)0x00000010)
#define GPIO_PUPDR_PUPD2_1        ((uint32_t)0x00000020)
#define GPIO_PUPDR_PUPD3          ((uint32_t)0x000000C0)
#define GPIO_PUPDR_PUPD3_0        ((uint32_t)0x00000040)
#define GPIO_PUPDR_PUPD3_1        ((uint32_t)0x00000080)
#define GPIO_PUPDR_PUPD4          ((uint32_t)0x00000300)
#define GPIO_PUPDR_PUPD4_0        ((uint32_t)0x00000100)
#define GPIO_PUPDR_PUPD4_1        ((uint32_t)0x00000200)
#define GPIO_PUPDR_PUPD5          ((uint32_t)0x00000C00)
#define GPIO_PUPDR_PUPD5_0        ((uint32_t)0x00000400)
#define GPIO_PUPDR_PUPD5_1        ((uint32_t)0x00000800)
#define GPIO_PUPDR_PUPD6          ((uint32_t)0x00003000)
#define GPIO_PUPDR_PUPD6_0        ((uint32_t)0x00001000)
#define GPIO_PUPDR_PUPD6_1        ((uint32_t)0x00002000)
#define GPIO_PUPDR_PUPD7          ((uint32_t)0x0000C000)
#define GPIO_PUPDR_PUPD7_0        ((uint32_t)0x00004000)
#define GPIO_PUPDR_PUPD7_1        ((uint32_t)0x00008000)
#define GPIO_PUPDR_PUPD8          ((uint32_t)0x00030000)
#define GPIO_PUPDR_PUPD8_0        ((uint32_t)0x00010000)
#define GPIO_PUPDR_PUPD8_1        ((uint32_t)0x00020000)
#define GPIO_PUPDR_PUPD9          ((uint32_t)0x000C0000)
#define GPIO_PUPDR_PUPD9_0        ((uint32_t)0x00040000)
#define GPIO_PUPDR_PUPD9_1        ((uint32_t)0x00080000)
#define GPIO_PUPDR_PUPD10         ((uint32_t)0x00300000)
#define GPIO_PUPDR_PUPD10_0       ((uint32_t)0x00100000)
#define GPIO_PUPDR_PUPD10_1       ((uint32_t)0x00200000)
#define GPIO_PUPDR_PUPD11         ((uint32_t)0x00C00000)
#define GPIO_PUPDR_PUPD11_0       ((uint32_t)0x00400000)
#define GPIO_PUPDR_PUPD11_1       ((uint32_t)0x00800000)
#define GPIO_PUPDR_PUPD12         ((uint32_t)0x03000000)
#define GPIO_PUPDR_PUPD12_0       ((uint32_t)0x01000000)
#define GPIO_PUPDR_PUPD12_1       ((uint32_t)0x02000000)
#define GPIO_PUPDR_PUPD13         ((uint32_t)0x0C000000)
#define GPIO_PUPDR_PUPD13_0       ((uint32_t)0x04000000)
#define GPIO_PUPDR_PUPD13_1       ((uint32_t)0x08000000)
#define GPIO_PUPDR_PUPD14         ((uint32_t)0x30000000)
#define GPIO_PUPDR_PUPD14_0       ((uint32_t)0x10000000)
#define GPIO_PUPDR_PUPD14_1       ((uint32_t)0x20000000)
#define GPIO_PUPDR_PUPD15         ((uint32_t)0xC0000000)
#define GPIO_PUPDR_PUPD15_0       ((uint32_t)0x40000000)
#define GPIO_PUPDR_PUPD15_1       ((uint32_t)0x80000000)

/*******************  Bit definition for GPIO_IDR register  *******************/
#define GPIO_IDR_ID0              ((uint32_t)0x00000001)
#define GPIO_IDR_ID1              ((uint32_t)0x00000002)
#define GPIO_IDR_ID2              ((uint32_t)0x00000004)
#define GPIO_IDR_ID3              ((uint32_t)0x00000008)
#define GPIO_IDR_ID4              ((uint32_t)0x00000010)
#define GPIO_IDR_ID5              ((uint32_t)0x00000020)
#define GPIO_IDR_ID6              ((uint32_t)0x00000040)
#define GPIO_IDR_ID7              ((uint32_t)0x00000080)
#define GPIO_IDR_ID8              ((uint32_t)0x00000100)
#define GPIO_IDR_ID9              ((uint32_t)0x00000200)
#define GPIO_IDR_ID10             ((uint32_t)0x00000400)
#define GPIO_IDR_ID11             ((uint32_t)0x00000800)
#define GPIO_IDR_ID12             ((uint32_t)0x00001000)
#define GPIO_IDR_ID13             ((uint32_t)0x00002000)
#define GPIO_IDR_ID14             ((uint32_t)0x00004000)
#define GPIO_IDR_ID15             ((uint32_t)0x00008000)

/******************  Bit definition for GPIO_ODR register  ********************/
#define GPIO_ODR_OD0              ((uint32_t)0x00000001)
#define GPIO_ODR_OD1              ((uint32_t)0x00000002)
#define GPIO_ODR_OD2              ((uint32_t)0x00000004)
#define GPIO_ODR_OD3              ((uint32_t)0x00000008)
#define GPIO_ODR_OD4              ((uint32_t)0x00000010)
#define GPIO_ODR_OD5              ((uint32_t)0x00000020)
#define GPIO_ODR_OD6              ((uint32_t)0x00000040)
#define GPIO_ODR_OD7              ((uint32_t)0x00000080)
#define GPIO_ODR_OD8              ((uint32_t)0x00000100)
#define GPIO_ODR_OD9              ((uint32_t)0x00000200)
#define GPIO_ODR_OD10             ((uint32_t)0x00000400)
#define GPIO_ODR_OD11             ((uint32_t)0x00000800)
#define GPIO_ODR_OD12             ((uint32_t)0x00001000)
#define GPIO_ODR_OD13             ((uint32_t)0x00002000)
#define GPIO_ODR_OD14             ((uint32_t)0x00004000)
#define GPIO_ODR_OD15             ((uint32_t)0x00008000)

/****************** Bit definition for GPIO_BSRR register  ********************/
#define GPIO_BSRR_BS_0            ((uint32_t)0x00000001)
#define GPIO_BSRR_BS_1            ((uint32_t)0x00000002)
#define GPIO_BSRR_BS_2            ((uint32_t)0x00000004)
#define GPIO_BSRR_BS_3            ((uint32_t)0x00000008)
#define GPIO_BSRR_BS_4            ((uint32_t)0x00000010)
#define GPIO_BSRR_BS_5            ((uint32_t)0x00000020)
#define GPIO_BSRR_BS_6            ((uint32_t)0x00000040)
#define GPIO_BSRR_BS_7            ((uint32_t)0x00000080)
#define GPIO_BSRR_BS_8            ((uint32_t)0x00000100)
#define GPIO_BSRR_BS_9            ((uint32_t)0x00000200)
#define GPIO_BSRR_BS_10           ((uint32_t)0x00000400)
#define GPIO_BSRR_BS_11           ((uint32_t)0x00000800)
#define GPIO_BSRR_BS_12           ((uint32_t)0x00001000)
#define GPIO_BSRR_BS_13           ((uint32_t)0x00002000)
#define GPIO_BSRR_BS_14           ((uint32_t)0x00004000)
#define GPIO_BSRR_BS_15           ((uint32_t)0x00008000)
#define GPIO_BSRR_BR_0            ((uint32_t)0x00010000)
#define GPIO_BSRR_BR_1            ((uint32_t)0x00020000)
#define GPIO_BSRR_BR_2            ((uint32_t)0x00040000)
#define GPIO_BSRR_BR_3            ((uint32_t)0x00080000)
#define GPIO_BSRR_BR_4            ((uint32_t)0x00100000)
#define GPIO_BSRR_BR_5            ((uint32_t)0x00200000)
#define GPIO_BSRR_BR_6            ((uint32_t)0x00400000)
#define GPIO_BSRR_BR_7            ((uint32_t)0x00800000)
#define GPIO_BSRR_BR_8            ((uint32_t)0x01000000)
#define GPIO_BSRR_BR_9            ((uint32_t)0x02000000)
#define GPIO_BSRR_BR_10           ((uint32_t)0x04000000)
#define GPIO_BSRR_BR_11           ((uint32_t)0x08000000)
#define GPIO_BSRR_BR_12           ((uint32_t)0x10000000)
#define GPIO_BSRR_BR_13           ((uint32_t)0x20000000)
#define GPIO_BSRR_BR_14           ((uint32_t)0x40000000)
#define GPIO_BSRR_BR_15           ((uint32_t)0x80000000)

/****************** Bit definition for GPIO_LCKR register  ********************/
#define GPIO_LCKR_LCK0            ((uint32_t)0x00000001)
#define GPIO_LCKR_LCK1            ((uint32_t)0x00000002)
#define GPIO_LCKR_LCK2            ((uint32_t)0x00000004)
#define GPIO_LCKR_LCK3            ((uint32_t)0x00000008)
#define GPIO_LCKR_LCK4            ((uint32_t)0x00000010)
#define GPIO_LCKR_LCK5            ((uint32_t)0x00000020)
#define GPIO_LCKR_LCK6            ((uint32_t)0x00000040)
#define GPIO_LCKR_LCK7            ((uint32_t)0x00000080)
#define GPIO_LCKR_LCK8            ((uint32_t)0x00000100)
#define GPIO_LCKR_LCK9            ((uint32_t)0x00000200)
#define GPIO_LCKR_LCK10           ((uint32_t)0x00000400)
#define GPIO_LCKR_LCK11           ((uint32_t)0x00000800)
#define GPIO_LCKR_LCK12           ((uint32_t)0x00001000)
#define GPIO_LCKR_LCK13           ((uint32_t)0x00002000)
#define GPIO_LCKR_LCK14           ((uint32_t)0x00004000)
#define GPIO_LCKR_LCK15           ((uint32_t)0x00008000)
#define GPIO_LCKR_LCKK            ((uint32_t)0x00010000)

/****************** Bit definition for GPIO_BRR register  *********************/
#define GPIO_BRR_BR_0             ((uint32_t)0x00000001)
#define GPIO_BRR_BR_1             ((uint32_t)0x00000002)
#define GPIO_BRR_BR_2             ((uint32_t)0x00000004)
#define GPIO_BRR_BR_3             ((uint32_t)0x00000008)
#define GPIO_BRR_BR_4             ((uint32_t)0x00000010)
#define GPIO_BRR_BR_5             ((uint32_t)0x00000020)
#define GPIO_BRR_BR_6             ((uint32_t)0x00000040)
#define GPIO_BRR_BR_7             ((uint32_t)0x00000080)
#define GPIO_BRR_BR_8             ((uint32_t)0x00000100)
#define GPIO_BRR_BR_9             ((uint32_t)0x00000200)
#define GPIO_BRR_BR_10            ((uint32_t)0x00000400)
#define GPIO_BRR_BR_11            ((uint32_t)0x00000800)
#define GPIO_BRR_BR_12            ((uint32_t)0x00001000)
#define GPIO_BRR_BR_13            ((uint32_t)0x00002000)
#define GPIO_BRR_BR_14            ((uint32_t)0x00004000)
#define GPIO_BRR_BR_15            ((uint32_t)0x00008000)

/******************************************************************************/
/*                                                                            */
/*                   Inter-integrated Circuit Interface (I2C)                 */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for I2C_CR1 register  *******************/
#define I2C_CR1_PE                          ((uint32_t)0x00000001)        /*!< Peripheral enable */
#define I2C_CR1_TXIE                        ((uint32_t)0x00000002)        /*!< TX interrupt enable */
#define I2C_CR1_RXIE                        ((uint32_t)0x00000004)        /*!< RX interrupt enable */
#define I2C_CR1_ADDRIE                      ((uint32_t)0x00000008)        /*!< Address match interrupt enable */
#define I2C_CR1_NACKIE                      ((uint32_t)0x00000010)        /*!< NACK received interrupt enable */
#define I2C_CR1_STOPIE                      ((uint32_t)0x00000020)        /*!< STOP detection interrupt enable */
#define I2C_CR1_TCIE                        ((uint32_t)0x00000040)        /*!< Transfer complete interrupt enable */
#define I2C_CR1_ERRIE                       ((uint32_t)0x00000080)        /*!< Errors interrupt enable */
#define I2C_CR1_DFN                         ((uint32_t)0x00000F00)        /*!< Digital noise filter */
#define I2C_CR1_ANFOFF                      ((uint32_t)0x00001000)        /*!< Analog noise filter OFF */
#define I2C_CR1_TXDMAEN                     ((uint32_t)0x00004000)        /*!< DMA transmission requests enable */
#define I2C_CR1_RXDMAEN                     ((uint32_t)0x00008000)        /*!< DMA reception requests enable */
#define I2C_CR1_SBC                         ((uint32_t)0x00010000)        /*!< Slave byte control */
#define I2C_CR1_NOSTRETCH                   ((uint32_t)0x00020000)        /*!< Clock stretching disable */
#define I2C_CR1_WUPEN                       ((uint32_t)0x00040000)        /*!< Wakeup from STOP enable */
#define I2C_CR1_GCEN                        ((uint32_t)0x00080000)        /*!< General call enable */
#define I2C_CR1_SMBHEN                      ((uint32_t)0x00100000)        /*!< SMBus host address enable */
#define I2C_CR1_SMBDEN                      ((uint32_t)0x00200000)        /*!< SMBus device default address enable */
#define I2C_CR1_ALERTEN                     ((uint32_t)0x00400000)        /*!< SMBus alert enable */
#define I2C_CR1_PECEN                       ((uint32_t)0x00800000)        /*!< PEC enable */

/******************  Bit definition for I2C_CR2 register  ********************/
#define I2C_CR2_SADD                        ((uint32_t)0x000003FF)        /*!< Slave address (master mode) */
#define I2C_CR2_RD_WRN                      ((uint32_t)0x00000400)        /*!< Transfer direction (master mode) */
#define I2C_CR2_ADD10                       ((uint32_t)0x00000800)        /*!< 10-bit addressing mode (master mode) */
#define I2C_CR2_HEAD10R                     ((uint32_t)0x00001000)        /*!< 10-bit address header only read direction (master mode) */
#define I2C_CR2_START                       ((uint32_t)0x00002000)        /*!< START generation */
#define I2C_CR2_STOP                        ((uint32_t)0x00004000)        /*!< STOP generation (master mode) */
#define I2C_CR2_NACK                        ((uint32_t)0x00008000)        /*!< NACK generation (slave mode) */
#define I2C_CR2_NBYTES                      ((uint32_t)0x00FF0000)        /*!< Number of bytes */
#define I2C_CR2_RELOAD                      ((uint32_t)0x01000000)        /*!< NBYTES reload mode */
#define I2C_CR2_AUTOEND                     ((uint32_t)0x02000000)        /*!< Automatic end mode (master mode) */
#define I2C_CR2_PECBYTE                     ((uint32_t)0x04000000)        /*!< Packet error checking byte */

/*******************  Bit definition for I2C_OAR1 register  ******************/
#define I2C_OAR1_OA1                        ((uint32_t)0x000003FF)        /*!< Interface own address 1 */
#define I2C_OAR1_OA1MODE                    ((uint32_t)0x00000400)        /*!< Own address 1 10-bit mode */
#define I2C_OAR1_OA1EN                      ((uint32_t)0x00008000)        /*!< Own address 1 enable */

/*******************  Bit definition for I2C_OAR2 register  ******************/
#define I2C_OAR2_OA2                        ((uint32_t)0x000000FE)        /*!< Interface own address 2 */
#define I2C_OAR2_OA2MSK                     ((uint32_t)0x00000700)        /*!< Own address 2 masks */
#define I2C_OAR2_OA2EN                      ((uint32_t)0x00008000)        /*!< Own address 2 enable */

/*******************  Bit definition for I2C_TIMINGR register *******************/
#define I2C_TIMINGR_SCLL                    ((uint32_t)0x000000FF)        /*!< SCL low period (master mode) */
#define I2C_TIMINGR_SCLH                    ((uint32_t)0x0000FF00)        /*!< SCL high period (master mode) */
#define I2C_TIMINGR_SDADEL                  ((uint32_t)0x000F0000)        /*!< Data hold time */
#define I2C_TIMINGR_SCLDEL                  ((uint32_t)0x00F00000)        /*!< Data setup time */
#define I2C_TIMINGR_PRESC                   ((uint32_t)0xF0000000)        /*!< Timings prescaler */

/******************* Bit definition for I2C_TIMEOUTR register *******************/
#define I2C_TIMEOUTR_TIMEOUTA               ((uint32_t)0x00000FFF)        /*!< Bus timeout A */
#define I2C_TIMEOUTR_TIDLE                  ((uint32_t)0x00001000)        /*!< Idle clock timeout detection */
#define I2C_TIMEOUTR_TIMOUTEN               ((uint32_t)0x00008000)        /*!< Clock timeout enable */
#define I2C_TIMEOUTR_TIMEOUTB               ((uint32_t)0x0FFF0000)        /*!< Bus timeout B*/
#define I2C_TIMEOUTR_TEXTEN                 ((uint32_t)0x80000000)        /*!< Extended clock timeout enable */

/******************  Bit definition for I2C_ISR register  *********************/
#define I2C_ISR_TXE                         ((uint32_t)0x00000001)        /*!< Transmit data register empty */
#define I2C_ISR_TXIS                        ((uint32_t)0x00000002)        /*!< Transmit interrupt status */
#define I2C_ISR_RXNE                        ((uint32_t)0x00000004)        /*!< Receive data register not empty */
#define I2C_ISR_ADDR                        ((uint32_t)0x00000008)        /*!< Address matched (slave mode)*/
#define I2C_ISR_NACKF                       ((uint32_t)0x00000010)        /*!< NACK received flag */
#define I2C_ISR_STOPF                       ((uint32_t)0x00000020)        /*!< STOP detection flag */
#define I2C_ISR_TC                          ((uint32_t)0x00000040)        /*!< Transfer complete (master mode) */
#define I2C_ISR_TCR                         ((uint32_t)0x00000080)        /*!< Transfer complete reload */
#define I2C_ISR_BERR                        ((uint32_t)0x00000100)        /*!< Bus error */
#define I2C_ISR_ARLO                        ((uint32_t)0x00000200)        /*!< Arbitration lost */
#define I2C_ISR_OVR                         ((uint32_t)0x00000400)        /*!< Overrun/Underrun */
#define I2C_ISR_PECERR                      ((uint32_t)0x00000800)        /*!< PEC error in reception */
#define I2C_ISR_TIMEOUT                     ((uint32_t)0x00001000)        /*!< Timeout or Tlow detection flag */
#define I2C_ISR_ALERT                       ((uint32_t)0x00002000)        /*!< SMBus alert */
#define I2C_ISR_BUSY                        ((uint32_t)0x00008000)        /*!< Bus busy */
#define I2C_ISR_DIR                         ((uint32_t)0x00010000)        /*!< Transfer direction (slave mode) */
#define I2C_ISR_ADDCODE                     ((uint32_t)0x00FE0000)        /*!< Address match code (slave mode) */

/******************  Bit definition for I2C_ICR register  *********************/
#define I2C_ICR_ADDRCF                      ((uint32_t)0x00000008)        /*!< Address matched clear flag */
#define I2C_ICR_NACKCF                      ((uint32_t)0x00000010)        /*!< NACK clear flag */
#define I2C_ICR_STOPCF                      ((uint32_t)0x00000020)        /*!< STOP detection clear flag */
#define I2C_ICR_BERRCF                      ((uint32_t)0x00000100)        /*!< Bus error clear flag */
#define I2C_ICR_ARLOCF                      ((uint32_t)0x00000200)        /*!< Arbitration lost clear flag */
#define I2C_ICR_OVRCF                       ((uint32_t)0x00000400)        /*!< Overrun/Underrun clear flag */
#define I2C_ICR_PECCF                       ((uint32_t)0x00000800)        /*!< PAC error clear flag */
#define I2C_ICR_TIMOUTCF                    ((uint32_t)0x00001000)        /*!< Timeout clear flag */
#define I2C_ICR_ALERTCF                     ((uint32_t)0x00002000)        /*!< Alert clear flag */

/******************  Bit definition for I2C_PECR register  *********************/
#define I2C_PECR_PEC                        ((uint32_t)0x000000FF)       /*!< PEC register */

/******************  Bit definition for I2C_RXDR register  *********************/
#define I2C_RXDR_RXDATA                     ((uint32_t)0x000000FF)       /*!< 8-bit receive data */

/******************  Bit definition for I2C_TXDR register  *********************/
#define I2C_TXDR_TXDATA                     ((uint32_t)0x000000FF)       /*!< 8-bit transmit data */

/******************************************************************************/
/*                                                                            */
/*                        Independent WATCHDOG (IWDG)                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for IWDG_KR register  ********************/
#define IWDG_KR_KEY                         ((uint32_t)0x0000FFFF)       /*!< Key value (write only, read 0000h) */

/*******************  Bit definition for IWDG_PR register  ********************/
#define IWDG_PR_PR                          ((uint32_t)0x00000007)       /*!< PR[2:0] (Prescaler divider) */
#define IWDG_PR_PR_0                        ((uint32_t)0x00000001)       /*!< Bit 0 */
#define IWDG_PR_PR_1                        ((uint32_t)0x00000002)       /*!< Bit 1 */
#define IWDG_PR_PR_2                        ((uint32_t)0x00000004)       /*!< Bit 2 */

/*******************  Bit definition for IWDG_RLR register  *******************/
#define IWDG_RLR_RL                         ((uint32_t)0x00000FFF)       /*!< Watchdog counter reload value */

/*******************  Bit definition for IWDG_SR register  ********************/
#define IWDG_SR_PVU                         ((uint32_t)0x00000001)       /*!< Watchdog prescaler value update */
#define IWDG_SR_RVU                         ((uint32_t)0x00000002)       /*!< Watchdog counter reload value update */
#define IWDG_SR_WVU                         ((uint32_t)0x00000004)       /*!< Watchdog counter window value update */

/*******************  Bit definition for IWDG_KR register  ********************/
#define IWDG_WINR_WIN                       ((uint32_t)0x00000FFF)       /*!< Watchdog counter window value */

/******************************************************************************/
/*                                                                            */
/*                          LCD Controller (LCD)                              */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for LCD_CR register  *********************/
#define LCD_CR_LCDEN               ((uint32_t)0x00000001)     /*!< LCD Enable Bit */
#define LCD_CR_VSEL                ((uint32_t)0x00000002)     /*!< Voltage source selector Bit */

#define LCD_CR_DUTY                ((uint32_t)0x0000001C)     /*!< DUTY[2:0] bits (Duty selector) */
#define LCD_CR_DUTY_0              ((uint32_t)0x00000004)     /*!< Duty selector Bit 0 */
#define LCD_CR_DUTY_1              ((uint32_t)0x00000008)     /*!< Duty selector Bit 1 */
#define LCD_CR_DUTY_2              ((uint32_t)0x00000010)     /*!< Duty selector Bit 2 */

#define LCD_CR_BIAS                ((uint32_t)0x00000060)     /*!< BIAS[1:0] bits (Bias selector) */
#define LCD_CR_BIAS_0              ((uint32_t)0x00000020)     /*!< Bias selector Bit 0 */
#define LCD_CR_BIAS_1              ((uint32_t)0x00000040)     /*!< Bias selector Bit 1 */

/*******************  Bit definition for LCD_FCR register  ********************/
#define LCD_FCR_HD                 ((uint32_t)0x00000001)     /*!< High Drive Enable Bit */
#define LCD_FCR_SOFIE              ((uint32_t)0x00000002)     /*!< Start of Frame Interrupt Enable Bit */
#define LCD_FCR_UDDIE              ((uint32_t)0x00000008)     /*!< Update Display Done Interrupt Enable Bit */

#define LCD_FCR_PON                ((uint32_t)0x00000070)     /*!< PON[2:0] bits (Puls ON Duration) */
#define LCD_FCR_PON_0              ((uint32_t)0x00000010)     /*!< Bit 0 */
#define LCD_FCR_PON_1              ((uint32_t)0x00000020)     /*!< Bit 1 */
#define LCD_FCR_PON_2              ((uint32_t)0x00000040)     /*!< Bit 2 */

#define LCD_FCR_DEAD               ((uint32_t)0x00000380)     /*!< DEAD[2:0] bits (DEAD Time) */
#define LCD_FCR_DEAD_0             ((uint32_t)0x00000080)     /*!< Bit 0 */
#define LCD_FCR_DEAD_1             ((uint32_t)0x00000100)     /*!< Bit 1 */
#define LCD_FCR_DEAD_2             ((uint32_t)0x00000200)     /*!< Bit 2 */

#define LCD_FCR_CC                 ((uint32_t)0x00001C00)     /*!< CC[2:0] bits (Contrast Control) */
#define LCD_FCR_CC_0               ((uint32_t)0x00000400)     /*!< Bit 0 */
#define LCD_FCR_CC_1               ((uint32_t)0x00000800)     /*!< Bit 1 */
#define LCD_FCR_CC_2               ((uint32_t)0x00001000)     /*!< Bit 2 */

#define LCD_FCR_BLINKF             ((uint32_t)0x0000E000)     /*!< BLINKF[2:0] bits (Blink Frequency) */
#define LCD_FCR_BLINKF_0           ((uint32_t)0x00002000)     /*!< Bit 0 */
#define LCD_FCR_BLINKF_1           ((uint32_t)0x00004000)     /*!< Bit 1 */
#define LCD_FCR_BLINKF_2           ((uint32_t)0x00008000)     /*!< Bit 2 */

#define LCD_FCR_BLINK              ((uint32_t)0x00030000)     /*!< BLINK[1:0] bits (Blink Enable) */
#define LCD_FCR_BLINK_0            ((uint32_t)0x00010000)     /*!< Bit 0 */
#define LCD_FCR_BLINK_1            ((uint32_t)0x00020000)     /*!< Bit 1 */

#define LCD_FCR_DIV                ((uint32_t)0x003C0000)     /*!< DIV[3:0] bits (Divider) */
#define LCD_FCR_PS                 ((uint32_t)0x03C00000)     /*!< PS[3:0] bits (Prescaler) */

/*******************  Bit definition for LCD_SR register  *********************/
#define LCD_SR_ENS                 ((uint32_t)0x00000001)     /*!< LCD Enabled Bit */
#define LCD_SR_SOF                 ((uint32_t)0x00000002)     /*!< Start Of Frame Flag Bit */
#define LCD_SR_UDR                 ((uint32_t)0x00000004)     /*!< Update Display Request Bit */
#define LCD_SR_UDD                 ((uint32_t)0x00000008)     /*!< Update Display Done Flag Bit */
#define LCD_SR_RDY                 ((uint32_t)0x00000010)     /*!< Ready Flag Bit */
#define LCD_SR_FCRSR               ((uint32_t)0x00000020)     /*!< LCD FCR Register Synchronization Flag Bit */

/*******************  Bit definition for LCD_CLR register  ********************/
#define LCD_CLR_SOFC               ((uint32_t)0x00000002)     /*!< Start Of Frame Flag Clear Bit */
#define LCD_CLR_UDDC               ((uint32_t)0x00000008)     /*!< Update Display Done Flag Clear Bit */

/*******************  Bit definition for LCD_RAM register  ********************/
#define LCD_RAM_SEGMENT_DATA       ((uint32_t)0xFFFFFFFF)     /*!< Segment Data Bits */

/******************************************************************************/
/*                                                                            */
/*                         Low Power Timer (LPTTIM)                           */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for LPTIM_ISR register  *******************/
#define LPTIM_ISR_CMPM                         ((uint32_t)0x00000001)            /*!< Compare match */
#define LPTIM_ISR_ARRM                         ((uint32_t)0x00000002)            /*!< Autoreload match */
#define LPTIM_ISR_EXTTRIG                      ((uint32_t)0x00000004)            /*!< External trigger edge event */
#define LPTIM_ISR_CMPOK                        ((uint32_t)0x00000008)            /*!< Compare register update OK */
#define LPTIM_ISR_ARROK                        ((uint32_t)0x00000010)            /*!< Autoreload register update OK */
#define LPTIM_ISR_UP                           ((uint32_t)0x00000020)            /*!< Counter direction change down to up */
#define LPTIM_ISR_DOWN                         ((uint32_t)0x00000040)            /*!< Counter direction change up to down */

/******************  Bit definition for LPTIM_ICR register  *******************/
#define LPTIM_ICR_CMPMCF                       ((uint32_t)0x00000001)            /*!< Compare match Clear Flag */
#define LPTIM_ICR_ARRMCF                       ((uint32_t)0x00000002)            /*!< Autoreload match Clear Flag */
#define LPTIM_ICR_EXTTRIGCF                    ((uint32_t)0x00000004)            /*!< External trigger edge event Clear Flag */
#define LPTIM_ICR_CMPOKCF                      ((uint32_t)0x00000008)            /*!< Compare register update OK Clear Flag */
#define LPTIM_ICR_ARROKCF                      ((uint32_t)0x00000010)            /*!< Autoreload register update OK Clear Flag */
#define LPTIM_ICR_UPCF                         ((uint32_t)0x00000020)            /*!< Counter direction change down to up Clear Flag */
#define LPTIM_ICR_DOWNCF                       ((uint32_t)0x00000040)            /*!< Counter direction change up to down Clear Flag */

/******************  Bit definition for LPTIM_IER register ********************/
#define LPTIM_IER_CMPMIE                       ((uint32_t)0x00000001)            /*!< Compare match Interrupt Enable */
#define LPTIM_IER_ARRMIE                       ((uint32_t)0x00000002)            /*!< Autoreload match Interrupt Enable */
#define LPTIM_IER_EXTTRIGIE                    ((uint32_t)0x00000004)            /*!< External trigger edge event Interrupt Enable */
#define LPTIM_IER_CMPOKIE                      ((uint32_t)0x00000008)            /*!< Compare register update OK Interrupt Enable */
#define LPTIM_IER_ARROKIE                      ((uint32_t)0x00000010)            /*!< Autoreload register update OK Interrupt Enable */
#define LPTIM_IER_UPIE                         ((uint32_t)0x00000020)            /*!< Counter direction change down to up Interrupt Enable */
#define LPTIM_IER_DOWNIE                       ((uint32_t)0x00000040)            /*!< Counter direction change up to down Interrupt Enable */

/******************  Bit definition for LPTIM_CFGR register *******************/
#define LPTIM_CFGR_CKSEL                       ((uint32_t)0x00000001)             /*!< Clock selector */

#define LPTIM_CFGR_CKPOL                       ((uint32_t)0x00000006)             /*!< CKPOL[1:0] bits (Clock polarity) */
#define LPTIM_CFGR_CKPOL_0                     ((uint32_t)0x00000002)             /*!< Bit 0 */
#define LPTIM_CFGR_CKPOL_1                     ((uint32_t)0x00000004)             /*!< Bit 1 */

#define LPTIM_CFGR_CKFLT                       ((uint32_t)0x00000018)             /*!< CKFLT[1:0] bits (Configurable digital filter for external clock) */
#define LPTIM_CFGR_CKFLT_0                     ((uint32_t)0x00000008)             /*!< Bit 0 */
#define LPTIM_CFGR_CKFLT_1                     ((uint32_t)0x00000010)             /*!< Bit 1 */

#define LPTIM_CFGR_TRGFLT                      ((uint32_t)0x000000C0)             /*!< TRGFLT[1:0] bits (Configurable digital filter for trigger) */
#define LPTIM_CFGR_TRGFLT_0                    ((uint32_t)0x00000040)             /*!< Bit 0 */
#define LPTIM_CFGR_TRGFLT_1                    ((uint32_t)0x00000080)             /*!< Bit 1 */

#define LPTIM_CFGR_PRESC                       ((uint32_t)0x00000E00)             /*!< PRESC[2:0] bits (Clock prescaler) */
#define LPTIM_CFGR_PRESC_0                     ((uint32_t)0x00000200)             /*!< Bit 0 */
#define LPTIM_CFGR_PRESC_1                     ((uint32_t)0x00000400)             /*!< Bit 1 */
#define LPTIM_CFGR_PRESC_2                     ((uint32_t)0x00000800)             /*!< Bit 2 */

#define LPTIM_CFGR_TRIGSEL                     ((uint32_t)0x0000E000)             /*!< TRIGSEL[2:0]] bits (Trigger selector) */
#define LPTIM_CFGR_TRIGSEL_0                   ((uint32_t)0x00002000)             /*!< Bit 0 */
#define LPTIM_CFGR_TRIGSEL_1                   ((uint32_t)0x00004000)             /*!< Bit 1 */
#define LPTIM_CFGR_TRIGSEL_2                   ((uint32_t)0x00008000)             /*!< Bit 2 */

#define LPTIM_CFGR_TRIGEN                      ((uint32_t)0x00060000)             /*!< TRIGEN[1:0] bits (Trigger enable and polarity) */
#define LPTIM_CFGR_TRIGEN_0                    ((uint32_t)0x00020000)             /*!< Bit 0 */
#define LPTIM_CFGR_TRIGEN_1                    ((uint32_t)0x00040000)             /*!< Bit 1 */

#define LPTIM_CFGR_TIMOUT                      ((uint32_t)0x00080000)             /*!< Timout enable */
#define LPTIM_CFGR_WAVE                        ((uint32_t)0x00100000)             /*!< Waveform shape */
#define LPTIM_CFGR_WAVPOL                      ((uint32_t)0x00200000)             /*!< Waveform shape polarity */
#define LPTIM_CFGR_PRELOAD                     ((uint32_t)0x00400000)             /*!< Reg update mode */
#define LPTIM_CFGR_COUNTMODE                   ((uint32_t)0x00800000)             /*!< Counter mode enable */
#define LPTIM_CFGR_ENC                         ((uint32_t)0x01000000)             /*!< Encoder mode enable */

/******************  Bit definition for LPTIM_CR register  ********************/
#define LPTIM_CR_ENABLE                        ((uint32_t)0x00000001)             /*!< LPTIMer enable */
#define LPTIM_CR_SNGSTRT                       ((uint32_t)0x00000002)             /*!< Timer start in single mode */
#define LPTIM_CR_CNTSTRT                       ((uint32_t)0x00000004)             /*!< Timer start in continuous mode */

/******************  Bit definition for LPTIM_CMP register  *******************/
#define LPTIM_CMP_CMP                          ((uint32_t)0x0000FFFF)             /*!< Compare register */

/******************  Bit definition for LPTIM_ARR register  *******************/
#define LPTIM_ARR_ARR                          ((uint32_t)0x0000FFFF)             /*!< Auto reload register */

/******************  Bit definition for LPTIM_CNT register  *******************/
#define LPTIM_CNT_CNT                          ((uint32_t)0x0000FFFF)             /*!< Counter register */

/******************************************************************************/
/*                                                                            */
/*                            MIFARE   Firewall                               */
/*                                                                            */
/******************************************************************************/

/*******Bit definition for CSSA;CSL;NVDSSA;NVDSL;VDSSA;VDSL register */
#define FW_CSSA_ADD                         ((uint32_t)0x00FFFF00)        /*!< Code Segment Start Address */ 
#define FW_CSL_LENG                         ((uint32_t)0x003FFF00)        /*!< Code Segment Length        */  
#define FW_NVDSSA_ADD                       ((uint32_t)0x00FFFF00)        /*!< Non Volatile Dat Segment Start Address */ 
#define FW_NVDSL_LENG                       ((uint32_t)0x003FFF00)        /*!< Non Volatile Data Segment Length */ 
#define FW_VDSSA_ADD                        ((uint32_t)0x0000FFC0)        /*!< Volatile Data Segment Start Address */ 
#define FW_VDSL_LENG                        ((uint32_t)0x0000FFC0)        /*!< Volatile Data Segment Length */ 

/**************************Bit definition for CR register *********************/
#define FW_CR_FPA                           ((uint32_t)0x00000001)         /*!< Firewall Pre Arm*/ 
#define FW_CR_VDS                           ((uint32_t)0x00000002)         /*!< Volatile Data Sharing*/ 
#define FW_CR_VDE                           ((uint32_t)0x00000004)         /*!< Volatile Data Execution*/ 

/******************************************************************************/
/*                                                                            */
/*                          Power Control (PWR)                               */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for PWR_CR register  ********************/
#define PWR_CR_LPSDSR                       ((uint32_t)0x00000001)     /*!< Low-power deepsleep/sleep/low power run */
#define PWR_CR_PDDS                         ((uint32_t)0x00000002)     /*!< Power Down Deepsleep */
#define PWR_CR_CWUF                         ((uint32_t)0x00000004)     /*!< Clear Wakeup Flag */
#define PWR_CR_CSBF                         ((uint32_t)0x00000008)     /*!< Clear Standby Flag */
#define PWR_CR_PVDE                         ((uint32_t)0x00000010)     /*!< Power Voltage Detector Enable */

#define PWR_CR_PLS                          ((uint32_t)0x000000E0)     /*!< PLS[2:0] bits (PVD Level Selection) */
#define PWR_CR_PLS_0                        ((uint32_t)0x00000020)     /*!< Bit 0 */
#define PWR_CR_PLS_1                        ((uint32_t)0x00000040)     /*!< Bit 1 */
#define PWR_CR_PLS_2                        ((uint32_t)0x00000080)     /*!< Bit 2 */

/*!< PVD level configuration */
#define PWR_CR_PLS_LEV0                     ((uint32_t)0x00000000)     /*!< PVD level 0 */
#define PWR_CR_PLS_LEV1                     ((uint32_t)0x00000020)     /*!< PVD level 1 */
#define PWR_CR_PLS_LEV2                     ((uint32_t)0x00000040)     /*!< PVD level 2 */
#define PWR_CR_PLS_LEV3                     ((uint32_t)0x00000060)     /*!< PVD level 3 */
#define PWR_CR_PLS_LEV4                     ((uint32_t)0x00000080)     /*!< PVD level 4 */
#define PWR_CR_PLS_LEV5                     ((uint32_t)0x000000A0)     /*!< PVD level 5 */
#define PWR_CR_PLS_LEV6                     ((uint32_t)0x000000C0)     /*!< PVD level 6 */
#define PWR_CR_PLS_LEV7                     ((uint32_t)0x000000E0)     /*!< PVD level 7 */

#define PWR_CR_DBP                          ((uint32_t)0x00000100)     /*!< Disable Backup Domain write protection */
#define PWR_CR_ULP                          ((uint32_t)0x00000200)     /*!< Ultra Low Power mode */
#define PWR_CR_FWU                          ((uint32_t)0x00000400)     /*!< Fast wakeup */

#define PWR_CR_VOS                          ((uint32_t)0x00001800)     /*!< VOS[1:0] bits (Voltage scaling range selection) */
#define PWR_CR_VOS_0                        ((uint32_t)0x00000800)     /*!< Bit 0 */
#define PWR_CR_VOS_1                        ((uint32_t)0x00001000)     /*!< Bit 1 */
#define PWR_CR_DSEEKOFF                     ((uint32_t)0x00002000)     /*!< Deep Sleep mode with EEPROM kept Off */
#define PWR_CR_LPRUN                        ((uint32_t)0x00004000)     /*!< Low power run mode */

/*******************  Bit definition for PWR_CSR register  ********************/
#define PWR_CSR_WUF                         ((uint32_t)0x00000001)     /*!< Wakeup Flag */
#define PWR_CSR_SBF                         ((uint32_t)0x00000002)     /*!< Standby Flag */
#define PWR_CSR_PVDO                        ((uint32_t)0x00000004)     /*!< PVD Output */
#define PWR_CSR_VREFINTRDYF                 ((uint32_t)0x00000008)     /*!< Internal voltage reference (VREFINT) ready flag */
#define PWR_CSR_VOSF                        ((uint32_t)0x00000010)     /*!< Voltage Scaling select flag */
#define PWR_CSR_REGLPF                      ((uint32_t)0x00000020)     /*!< Regulator LP flag */

#define PWR_CSR_EWUP1                       ((uint32_t)0x00000100)     /*!< Enable WKUP pin 1 */
#define PWR_CSR_EWUP2                       ((uint32_t)0x00000200)     /*!< Enable WKUP pin 2 */

/******************************************************************************/
/*                                                                            */
/*                         Reset and Clock Control                            */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for RCC_CR register  ********************/
#define RCC_CR_HSION                        ((uint32_t)0x00000001)        /*!< Internal High Speed clock enable */
#define RCC_CR_HSIKERON                     ((uint32_t)0x00000002)        /*!< Internal High Speed clock enable for some IPs Kernel */
#define RCC_CR_HSIRDY                       ((uint32_t)0x00000004)        /*!< Internal High Speed clock ready flag */
#define RCC_CR_HSIDIVEN                     ((uint32_t)0x00000008)        /*!< Internal High Speed clock divider enable */
#define RCC_CR_HSIDIVF                      ((uint32_t)0x00000010)        /*!< Internal High Speed clock divider flag */
#define RCC_CR_MSION                        ((uint32_t)0x00000100)        /*!< Internal Multi Speed clock enable */
#define RCC_CR_MSIRDY                       ((uint32_t)0x00000200)        /*!< Internal Multi Speed clock ready flag */
#define RCC_CR_HSEON                        ((uint32_t)0x00010000)        /*!< External High Speed clock enable */
#define RCC_CR_HSERDY                       ((uint32_t)0x00020000)        /*!< External High Speed clock ready flag */
#define RCC_CR_HSEBYP                       ((uint32_t)0x00040000)        /*!< External High Speed clock Bypass */
#define RCC_CR_CSSHSEON                     ((uint32_t)0x00080000)        /*!< HSE Clock Security System enable */
#define RCC_CR_RTCPRE                       ((uint32_t)0x00300000)        /*!< RTC/LCD prescaler [1:0] bits */
#define RCC_CR_RTCPRE_0                     ((uint32_t)0x00100000)        /*!< RTC/LCD prescaler Bit 0 */
#define RCC_CR_RTCPRE_1                     ((uint32_t)0x00200000)        /*!< RTC/LCD prescaler Bit 1 */
#define RCC_CR_PLLON                        ((uint32_t)0x01000000)        /*!< PLL enable */
#define RCC_CR_PLLRDY                       ((uint32_t)0x02000000)        /*!< PLL clock ready flag */

/********************  Bit definition for RCC_ICSCR register  *****************/
#define RCC_ICSCR_HSICAL                    ((uint32_t)0x000000FF)        /*!< Internal High Speed clock Calibration */
#define RCC_ICSCR_HSITRIM                   ((uint32_t)0x00001F00)        /*!< Internal High Speed clock trimming */

#define RCC_ICSCR_MSIRANGE                  ((uint32_t)0x0000E000)        /*!< Internal Multi Speed clock Range */
#define RCC_ICSCR_MSIRANGE_0                ((uint32_t)0x00000000)        /*!< Internal Multi Speed clock Range 65.536 KHz */
#define RCC_ICSCR_MSIRANGE_1                ((uint32_t)0x00002000)        /*!< Internal Multi Speed clock Range 131.072 KHz */
#define RCC_ICSCR_MSIRANGE_2                ((uint32_t)0x00004000)        /*!< Internal Multi Speed clock Range 262.144 KHz */
#define RCC_ICSCR_MSIRANGE_3                ((uint32_t)0x00006000)        /*!< Internal Multi Speed clock Range 524.288 KHz */
#define RCC_ICSCR_MSIRANGE_4                ((uint32_t)0x00008000)        /*!< Internal Multi Speed clock Range 1.048 MHz */
#define RCC_ICSCR_MSIRANGE_5                ((uint32_t)0x0000A000)        /*!< Internal Multi Speed clock Range 2.097 MHz */
#define RCC_ICSCR_MSIRANGE_6                ((uint32_t)0x0000C000)        /*!< Internal Multi Speed clock Range 4.194 MHz */
#define RCC_ICSCR_MSICAL                    ((uint32_t)0x00FF0000)        /*!< Internal Multi Speed clock Calibration */
#define RCC_ICSCR_MSITRIM                   ((uint32_t)0xFF000000)        /*!< Internal Multi Speed clock trimming */

/********************  Bit definition for RCC_CRRCR register  *****************/
#define RCC_CRRCR_HSI48ON                   ((uint32_t)0x00000001)        /*!< HSI 48MHz clock enable */
#define RCC_CRRCR_HSI48RDY                  ((uint32_t)0x00000002)        /*!< HSI 48MHz clock ready flag */
#define RCC_CRRCR_HSI48CAL                  ((uint32_t)0x0000FF00)        /*!< HSI 48MHz clock Calibration */

/*******************  Bit definition for RCC_CFGR register  *******************/
/*!< SW configuration */
#define RCC_CFGR_SW                         ((uint32_t)0x00000003)        /*!< SW[1:0] bits (System clock Switch) */
#define RCC_CFGR_SW_0                       ((uint32_t)0x00000001)        /*!< Bit 0 */
#define RCC_CFGR_SW_1                       ((uint32_t)0x00000002)        /*!< Bit 1 */

#define RCC_CFGR_SW_MSI                     ((uint32_t)0x00000000)        /*!< MSI selected as system clock */
#define RCC_CFGR_SW_HSI                     ((uint32_t)0x00000001)        /*!< HSI selected as system clock */
#define RCC_CFGR_SW_HSE                     ((uint32_t)0x00000002)        /*!< HSE selected as system clock */
#define RCC_CFGR_SW_PLL                     ((uint32_t)0x00000003)        /*!< PLL selected as system clock */

/*!< SWS configuration */
#define RCC_CFGR_SWS                        ((uint32_t)0x0000000C)        /*!< SWS[1:0] bits (System Clock Switch Status) */
#define RCC_CFGR_SWS_0                      ((uint32_t)0x00000004)        /*!< Bit 0 */
#define RCC_CFGR_SWS_1                      ((uint32_t)0x00000008)        /*!< Bit 1 */

#define RCC_CFGR_SWS_MSI                    ((uint32_t)0x00000000)        /*!< MSI oscillator used as system clock */
#define RCC_CFGR_SWS_HSI                    ((uint32_t)0x00000004)        /*!< HSI oscillator used as system clock */
#define RCC_CFGR_SWS_HSE                    ((uint32_t)0x00000008)        /*!< HSE oscillator used as system clock */
#define RCC_CFGR_SWS_PLL                    ((uint32_t)0x0000000C)        /*!< PLL used as system clock */

/*!< HPRE configuration */
#define RCC_CFGR_HPRE                       ((uint32_t)0x000000F0)        /*!< HPRE[3:0] bits (AHB prescaler) */
#define RCC_CFGR_HPRE_0                     ((uint32_t)0x00000010)        /*!< Bit 0 */
#define RCC_CFGR_HPRE_1                     ((uint32_t)0x00000020)        /*!< Bit 1 */
#define RCC_CFGR_HPRE_2                     ((uint32_t)0x00000040)        /*!< Bit 2 */
#define RCC_CFGR_HPRE_3                     ((uint32_t)0x00000080)        /*!< Bit 3 */

#define RCC_CFGR_HPRE_DIV1                  ((uint32_t)0x00000000)        /*!< SYSCLK not divided */
#define RCC_CFGR_HPRE_DIV2                  ((uint32_t)0x00000080)        /*!< SYSCLK divided by 2 */
#define RCC_CFGR_HPRE_DIV4                  ((uint32_t)0x00000090)        /*!< SYSCLK divided by 4 */
#define RCC_CFGR_HPRE_DIV8                  ((uint32_t)0x000000A0)        /*!< SYSCLK divided by 8 */
#define RCC_CFGR_HPRE_DIV16                 ((uint32_t)0x000000B0)        /*!< SYSCLK divided by 16 */
#define RCC_CFGR_HPRE_DIV64                 ((uint32_t)0x000000C0)        /*!< SYSCLK divided by 64 */
#define RCC_CFGR_HPRE_DIV128                ((uint32_t)0x000000D0)        /*!< SYSCLK divided by 128 */
#define RCC_CFGR_HPRE_DIV256                ((uint32_t)0x000000E0)        /*!< SYSCLK divided by 256 */
#define RCC_CFGR_HPRE_DIV512                ((uint32_t)0x000000F0)        /*!< SYSCLK divided by 512 */

/*!< PPRE1 configuration */
#define RCC_CFGR_PPRE1                      ((uint32_t)0x00000700)        /*!< PRE1[2:0] bits (APB1 prescaler) */
#define RCC_CFGR_PPRE1_0                    ((uint32_t)0x00000100)        /*!< Bit 0 */
#define RCC_CFGR_PPRE1_1                    ((uint32_t)0x00000200)        /*!< Bit 1 */
#define RCC_CFGR_PPRE1_2                    ((uint32_t)0x00000400)        /*!< Bit 2 */

#define RCC_CFGR_PPRE1_DIV1                 ((uint32_t)0x00000000)        /*!< HCLK not divided */
#define RCC_CFGR_PPRE1_DIV2                 ((uint32_t)0x00000400)        /*!< HCLK divided by 2 */
#define RCC_CFGR_PPRE1_DIV4                 ((uint32_t)0x00000500)        /*!< HCLK divided by 4 */
#define RCC_CFGR_PPRE1_DIV8                 ((uint32_t)0x00000600)        /*!< HCLK divided by 8 */
#define RCC_CFGR_PPRE1_DIV16                ((uint32_t)0x00000700)        /*!< HCLK divided by 16 */

/*!< PPRE2 configuration */
#define RCC_CFGR_PPRE2                      ((uint32_t)0x00003800)        /*!< PRE2[2:0] bits (APB2 prescaler) */
#define RCC_CFGR_PPRE2_0                    ((uint32_t)0x00000800)        /*!< Bit 0 */
#define RCC_CFGR_PPRE2_1                    ((uint32_t)0x00001000)        /*!< Bit 1 */
#define RCC_CFGR_PPRE2_2                    ((uint32_t)0x00002000)        /*!< Bit 2 */

#define RCC_CFGR_PPRE2_DIV1                 ((uint32_t)0x00000000)        /*!< HCLK not divided */
#define RCC_CFGR_PPRE2_DIV2                 ((uint32_t)0x00002000)        /*!< HCLK divided by 2 */
#define RCC_CFGR_PPRE2_DIV4                 ((uint32_t)0x00002800)        /*!< HCLK divided by 4 */
#define RCC_CFGR_PPRE2_DIV8                 ((uint32_t)0x00003000)        /*!< HCLK divided by 8 */
#define RCC_CFGR_PPRE2_DIV16                ((uint32_t)0x00003800)        /*!< HCLK divided by 16 */

#define RCC_CFGR_STOPWUCK                   ((uint32_t)0x00008000)        /*!< Wake Up from Stop Clock selection */

/*!< PLL entry clock source*/
#define RCC_CFGR_PLLSRC                     ((uint32_t)0x00010000)        /*!< PLL entry clock source */

#define RCC_CFGR_PLLSRC_HSI                 ((uint32_t)0x00000000)        /*!< HSI as PLL entry clock source */
#define RCC_CFGR_PLLSRC_HSE                 ((uint32_t)0x00010000)        /*!< HSE as PLL entry clock source */


/*!< PLLMUL configuration */
#define RCC_CFGR_PLLMUL                     ((uint32_t)0x003C0000)        /*!< PLLMUL[3:0] bits (PLL multiplication factor) */
#define RCC_CFGR_PLLMUL_0                   ((uint32_t)0x00040000)        /*!< Bit 0 */
#define RCC_CFGR_PLLMUL_1                   ((uint32_t)0x00080000)        /*!< Bit 1 */
#define RCC_CFGR_PLLMUL_2                   ((uint32_t)0x00100000)        /*!< Bit 2 */
#define RCC_CFGR_PLLMUL_3                   ((uint32_t)0x00200000)        /*!< Bit 3 */

#define RCC_CFGR_PLLMUL3                    ((uint32_t)0x00000000)        /*!< PLL input clock * 3 */
#define RCC_CFGR_PLLMUL4                    ((uint32_t)0x00040000)        /*!< PLL input clock * 4 */
#define RCC_CFGR_PLLMUL6                    ((uint32_t)0x00080000)        /*!< PLL input clock * 6 */
#define RCC_CFGR_PLLMUL8                    ((uint32_t)0x000C0000)        /*!< PLL input clock * 8 */
#define RCC_CFGR_PLLMUL12                   ((uint32_t)0x00100000)        /*!< PLL input clock * 12 */
#define RCC_CFGR_PLLMUL16                   ((uint32_t)0x00140000)        /*!< PLL input clock * 16 */
#define RCC_CFGR_PLLMUL24                   ((uint32_t)0x00180000)        /*!< PLL input clock * 24 */
#define RCC_CFGR_PLLMUL32                   ((uint32_t)0x001C0000)        /*!< PLL input clock * 32 */
#define RCC_CFGR_PLLMUL48                   ((uint32_t)0x00200000)        /*!< PLL input clock * 48 */

/*!< PLLDIV configuration */
#define RCC_CFGR_PLLDIV                     ((uint32_t)0x00C00000)        /*!< PLLDIV[1:0] bits (PLL Output Division) */
#define RCC_CFGR_PLLDIV_0                   ((uint32_t)0x00400000)        /*!< Bit0 */
#define RCC_CFGR_PLLDIV_1                   ((uint32_t)0x00800000)        /*!< Bit1 */

#define RCC_CFGR_PLLDIV2                    ((uint32_t)0x00400000)        /*!< PLL clock output = CKVCO / 2 */
#define RCC_CFGR_PLLDIV3                    ((uint32_t)0x00800000)        /*!< PLL clock output = CKVCO / 3 */
#define RCC_CFGR_PLLDIV4                    ((uint32_t)0x00C00000)        /*!< PLL clock output = CKVCO / 4 */

/*!< MCO configuration */
#define RCC_CFGR_MCOSEL                     ((uint32_t)0x0F000000)        /*!< MCO[3:0] bits (Microcontroller Clock Output) */
#define RCC_CFGR_MCOSEL_0                   ((uint32_t)0x01000000)        /*!< Bit 0 */
#define RCC_CFGR_MCOSEL_1                   ((uint32_t)0x02000000)        /*!< Bit 1 */
#define RCC_CFGR_MCOSEL_2                   ((uint32_t)0x04000000)        /*!< Bit 2 */
#define RCC_CFGR_MCOSEL_3                   ((uint32_t)0x08000000)        /*!< Bit 3 */

#define RCC_CFGR_MCO_NOCLOCK                ((uint32_t)0x00000000)        /*!< No clock */
#define RCC_CFGR_MCO_SYSCLK                 ((uint32_t)0x01000000)        /*!< System clock selected as MCO source */
#define RCC_CFGR_MCO_HSI                    ((uint32_t)0x02000000)        /*!< Internal 16 MHz RC oscillator clock selected */
#define RCC_CFGR_MCO_MSI                    ((uint32_t)0x03000000)        /*!< Internal Medium Speed RC oscillator clock selected */
#define RCC_CFGR_MCO_HSE                    ((uint32_t)0x04000000)        /*!< External 1-25 MHz oscillator clock selected */
#define RCC_CFGR_MCO_PLL                    ((uint32_t)0x05000000)        /*!< PLL clock divided */
#define RCC_CFGR_MCO_LSI                    ((uint32_t)0x06000000)        /*!< LSI selected */
#define RCC_CFGR_MCO_LSE                    ((uint32_t)0x07000000)        /*!< LSE selected */
#define RCC_CFGR_MCO_HSI48                  ((uint32_t)0x08000000)        /*!< HSI48 clock selected as MCO source */

#define RCC_CFGR_MCO_PRE                    ((uint32_t)0x70000000)        /*!< MCO prescaler */
#define RCC_CFGR_MCO_PRE_1                  ((uint32_t)0x00000000)        /*!< MCO is divided by 1 */
#define RCC_CFGR_MCO_PRE_2                  ((uint32_t)0x10000000)        /*!< MCO is divided by 2 */
#define RCC_CFGR_MCO_PRE_4                  ((uint32_t)0x20000000)        /*!< MCO is divided by 4 */
#define RCC_CFGR_MCO_PRE_8                  ((uint32_t)0x30000000)        /*!< MCO is divided by 8 */
#define RCC_CFGR_MCO_PRE_16                 ((uint32_t)0x40000000)        /*!< MCO is divided by 16 */

/*!<******************  Bit definition for RCC_CIER register  ********************/
#define RCC_CIER_LSIRDYIE                   ((uint32_t)0x00000001)        /*!< LSI Ready Interrupt Enable */
#define RCC_CIER_LSERDYIE                   ((uint32_t)0x00000002)        /*!< LSE Ready Interrupt Enable */
#define RCC_CIER_HSIRDYIE                   ((uint32_t)0x00000004)        /*!< HSI Ready Interrupt Enable */
#define RCC_CIER_HSERDYIE                   ((uint32_t)0x00000008)        /*!< HSE Ready Interrupt Enable */
#define RCC_CIER_PLLRDYIE                   ((uint32_t)0x00000010)        /*!< PLL Ready Interrupt Enable */
#define RCC_CIER_MSIRDYIE                   ((uint32_t)0x00000020)        /*!< MSI Ready Interrupt Enable */
#define RCC_CIER_HSI48RDYIE                 ((uint32_t)0x00000040)        /*!< HSI48 Ready Interrupt Enable */
#define RCC_CIER_LSECSSIE                   ((uint32_t)0x00000080)        /*!< LSE CSS Interrupt Enable */

/*!<******************  Bit definition for RCC_CIFR register  ********************/
#define RCC_CIFR_LSIRDYF                    ((uint32_t)0x00000001)        /*!< LSI Ready Interrupt flag */
#define RCC_CIFR_LSERDYF                    ((uint32_t)0x00000002)        /*!< LSE Ready Interrupt flag */
#define RCC_CIFR_HSIRDYF                    ((uint32_t)0x00000004)        /*!< HSI Ready Interrupt flag */
#define RCC_CIFR_HSERDYF                    ((uint32_t)0x00000008)        /*!< HSE Ready Interrupt flag */
#define RCC_CIFR_PLLRDYF                    ((uint32_t)0x00000010)        /*!< PLL Ready Interrupt flag */
#define RCC_CIFR_MSIRDYF                    ((uint32_t)0x00000020)        /*!< MSI Ready Interrupt flag */
#define RCC_CIFR_HSI48RDYF                  ((uint32_t)0x00000040)        /*!< HSI48 Ready Interrupt flag */
#define RCC_CIFR_LSECSSF                    ((uint32_t)0x00000080)        /*!< LSE Clock Security System Interrupt flag */
#define RCC_CIFR_CSSF                       ((uint32_t)0x00000100)        /*!< Clock Security System Interrupt flag */

/*!<******************  Bit definition for RCC_CICR register  ********************/
#define RCC_CICR_LSIRDYC                    ((uint32_t)0x00000001)        /*!< LSI Ready Interrupt Clear */
#define RCC_CICR_LSERDYC                    ((uint32_t)0x00000002)        /*!< LSE Ready Interrupt Clear */
#define RCC_CICR_HSIRDYC                    ((uint32_t)0x00000004)        /*!< HSI Ready Interrupt Clear */
#define RCC_CICR_HSERDYC                    ((uint32_t)0x00000008)        /*!< HSE Ready Interrupt Clear */
#define RCC_CICR_PLLRDYC                    ((uint32_t)0x00000010)        /*!< PLL Ready Interrupt Clear */
#define RCC_CICR_MSIRDYC                    ((uint32_t)0x00000020)        /*!< MSI Ready Interrupt Clear */
#define RCC_CICR_HSI48RDYC                  ((uint32_t)0x00000040)        /*!< HSI48 Ready Interrupt Clear */
#define RCC_CICR_LSECSSC                    ((uint32_t)0x00000080)        /*!< LSE Clock Security System Interrupt Clear */
#define RCC_CICR_CSSC                       ((uint32_t)0x00000100)        /*!< Clock Security System Interrupt Clear */

/*****************  Bit definition for RCC_IOPRSTR register  ******************/
#define RCC_IOPRSTR_GPIOARST                ((uint32_t)0x00000001)        /*!< GPIO port A reset */
#define RCC_IOPRSTR_GPIOBRST                ((uint32_t)0x00000002)        /*!< GPIO port B reset */
#define RCC_IOPRSTR_GPIOCRST                ((uint32_t)0x00000004)        /*!< GPIO port C reset */
#define RCC_IOPRSTR_GPIODRST                ((uint32_t)0x00000008)        /*!< GPIO port D reset */
#define RCC_IOPRSTR_GPIOHRST                ((uint32_t)0x00000080)        /*!< GPIO port H reset */

/******************  Bit definition for RCC_AHBRST register  ******************/
#define RCC_AHBRSTR_DMA1RST                 ((uint32_t)0x00000001)        /*!< DMA1 reset */
#define RCC_AHBRSTR_MIFRST                  ((uint32_t)0x00000100)        /*!< Memory interface reset reset */
#define RCC_AHBRSTR_CRCRST                  ((uint32_t)0x00001000)        /*!< CRC reset */
#define RCC_AHBRSTR_TSCRST                  ((uint32_t)0x00010000)        /*!< TSC reset */
#define RCC_AHBRSTR_RNGRST                  ((uint32_t)0x00100000)        /*!< RNG reset */

/*****************  Bit definition for RCC_APB2RSTR register  *****************/
#define RCC_APB2RSTR_SYSCFGRST              ((uint32_t)0x00000001)        /*!< SYSCFG clock reset */
#define RCC_APB2RSTR_TIM21RST               ((uint32_t)0x00000004)        /*!< TIM21 clock reset */
#define RCC_APB2RSTR_TIM22RST               ((uint32_t)0x00000020)        /*!< TIM22 clock reset */
#define RCC_APB2RSTR_ADC1RST                ((uint32_t)0x00000200)        /*!< ADC1 clock reset */
#define RCC_APB2RSTR_SPI1RST                ((uint32_t)0x00001000)        /*!< SPI1 clock reset */
#define RCC_APB2RSTR_USART1RST              ((uint32_t)0x00004000)        /*!< USART1 clock reset */
#define RCC_APB2RSTR_DBGMCURST              ((uint32_t)0x00400000)        /*!< DBGMCU clock reset */

/*****************  Bit definition for RCC_APB1RSTR register  *****************/
#define RCC_APB1RSTR_TIM2RST                ((uint32_t)0x00000001)        /*!< Timer 2 clock reset */
#define RCC_APB1RSTR_TIM6RST                ((uint32_t)0x00000010)        /*!< Timer 6 clock reset */
#define RCC_APB1RSTR_LCDRST                 ((uint32_t)0x00000200)        /*!< LCD clock reset */
#define RCC_APB1RSTR_WWDGRST                ((uint32_t)0x00000800)        /*!< Window Watchdog clock reset */
#define RCC_APB1RSTR_SPI2RST                ((uint32_t)0x00004000)        /*!< SPI2 clock reset */
#define RCC_APB1RSTR_USART2RST              ((uint32_t)0x00020000)        /*!< USART 2 clock reset */
#define RCC_APB1RSTR_LPUART1RST             ((uint32_t)0x00040000)        /*!< LPUART1 clock reset */
#define RCC_APB1RSTR_I2C1RST                ((uint32_t)0x00200000)        /*!< I2C 1 clock reset */
#define RCC_APB1RSTR_I2C2RST                ((uint32_t)0x00400000)        /*!< I2C 2 clock reset */
#define RCC_APB1RSTR_USBRST                 ((uint32_t)0x00800000)        /*!< USB clock reset */
#define RCC_APB1RSTR_CRSRST                 ((uint32_t)0x08000000)        /*!< CRS clock reset */
#define RCC_APB1RSTR_PWRRST                 ((uint32_t)0x10000000)        /*!< PWR clock reset */
#define RCC_APB1RSTR_DACRST                 ((uint32_t)0x20000000)        /*!< DAC clock reset */
#define RCC_APB1RSTR_LPTIM1RST              ((uint32_t)0x80000000)        /*!< LPTIM1 clock reset */

/*****************  Bit definition for RCC_IOPENR register  ******************/
#define RCC_IOPENR_GPIOAEN                  ((uint32_t)0x00000001)        /*!< GPIO port A clock enable */
#define RCC_IOPENR_GPIOBEN                  ((uint32_t)0x00000002)        /*!< GPIO port B clock enable */
#define RCC_IOPENR_GPIOCEN                  ((uint32_t)0x00000004)        /*!< GPIO port C clock enable */
#define RCC_IOPENR_GPIODEN                  ((uint32_t)0x00000008)        /*!< GPIO port D clock enable */
#define RCC_IOPENR_GPIOHEN                  ((uint32_t)0x00000080)        /*!< GPIO port H clock enable */

/*****************  Bit definition for RCC_AHBENR register  ******************/
#define RCC_AHBENR_DMA1EN                   ((uint32_t)0x00000001)        /*!< DMA1 clock enable */
#define RCC_AHBENR_MIFEN                    ((uint32_t)0x00000100)        /*!< NVM interface clock enable bit */
#define RCC_AHBENR_CRCEN                    ((uint32_t)0x00001000)        /*!< CRC clock enable */
#define RCC_AHBENR_TSCEN                    ((uint32_t)0x00010000)        /*!< TSC clock enable */
#define RCC_AHBENR_RNGEN                    ((uint32_t)0x00100000)        /*!< RNG clock enable */

/*****************  Bit definition for RCC_APB2ENR register  ******************/
#define RCC_APB2ENR_SYSCFGEN                ((uint32_t)0x00000001)        /*!< SYSCFG clock enable */
#define RCC_APB2ENR_TIM21EN                 ((uint32_t)0x00000004)        /*!< TIM21 clock enable */
#define RCC_APB2ENR_TIM22EN                 ((uint32_t)0x00000020)        /*!< TIM22 clock enable */
#define RCC_APB2ENR_MIFIEN                  ((uint32_t)0x00000080)        /*!< MiFare Firewall clock enable */
#define RCC_APB2ENR_ADC1EN                  ((uint32_t)0x00000200)        /*!< ADC1 clock enable */
#define RCC_APB2ENR_SPI1EN                  ((uint32_t)0x00001000)        /*!< SPI1 clock enable */
#define RCC_APB2ENR_USART1EN                ((uint32_t)0x00004000)        /*!< USART1 clock enable */
#define RCC_APB2ENR_DBGMCUEN                ((uint32_t)0x00400000)        /*!< DBGMCU clock enable */

/*****************  Bit definition for RCC_APB1ENR register  ******************/
#define RCC_APB1ENR_TIM2EN                  ((uint32_t)0x00000001)        /*!< Timer 2 clock enable */
#define RCC_APB1ENR_TIM6EN                  ((uint32_t)0x00000010)        /*!< Timer 6 clock enable */
#define RCC_APB1ENR_LCDEN                   ((uint32_t)0x00000200)        /*!< LCD clock enable */
#define RCC_APB1ENR_WWDGEN                  ((uint32_t)0x00000800)        /*!< Window Watchdog clock enable */
#define RCC_APB1ENR_SPI2EN                  ((uint32_t)0x00004000)        /*!< SPI2 clock enable */
#define RCC_APB1ENR_USART2EN                ((uint32_t)0x00020000)        /*!< USART2 clock enable */
#define RCC_APB1ENR_LPUART1EN               ((uint32_t)0x00040000)        /*!< LPUART1 clock enable */
#define RCC_APB1ENR_I2C1EN                  ((uint32_t)0x00200000)        /*!< I2C1 clock enable */
#define RCC_APB1ENR_I2C2EN                  ((uint32_t)0x00400000)        /*!< I2C2 clock enable */
#define RCC_APB1ENR_USBEN                   ((uint32_t)0x00800000)        /*!< USB clock enable */
#define RCC_APB1ENR_CRSEN                   ((uint32_t)0x08000000)        /*!< CRS clock enable */
#define RCC_APB1ENR_PWREN                   ((uint32_t)0x10000000)        /*!< PWR clock enable */
#define RCC_APB1ENR_DACEN                   ((uint32_t)0x20000000)        /*!< DAC clock enable */
#define RCC_APB1ENR_LPTIM1EN                ((uint32_t)0x80000000)        /*!< LPTIM1 clock enable */

/******************  Bit definition for RCC_IOPSMENR register  ****************/
#define RCC_IOPSMENR_GPIOASMEN              ((uint32_t)0x00000001)        /*!< GPIO port A clock enabled in sleep mode */
#define RCC_IOPSMENR_GPIOBSMEN              ((uint32_t)0x00000002)        /*!< GPIO port B clock enabled in sleep mode */
#define RCC_IOPSMENR_GPIOCSMEN              ((uint32_t)0x00000004)        /*!< GPIO port C clock enabled in sleep mode */
#define RCC_IOPSMENR_GPIODSMEN              ((uint32_t)0x00000008)        /*!< GPIO port D clock enabled in sleep mode */
#define RCC_IOPSMENR_GPIOHSMEN              ((uint32_t)0x00000080)        /*!< GPIO port H clock enabled in sleep mode */

/*****************  Bit definition for RCC_AHBSMENR register  ******************/
#define RCC_AHBSMENR_DMA1SMEN               ((uint32_t)0x00000001)        /*!< DMA1 clock enabled in sleep mode */
#define RCC_AHBSMENR_MIFSMEN                ((uint32_t)0x00000100)        /*!< NVM interface clock enable during sleep mode */
#define RCC_AHBSMENR_SRAMSMEN               ((uint32_t)0x00000200)        /*!< SRAM clock enabled in sleep mode */
#define RCC_AHBSMENR_CRCSMEN                ((uint32_t)0x00001000)        /*!< CRC clock enabled in sleep mode */
#define RCC_AHBSMENR_TSCSMEN                ((uint32_t)0x00010000)        /*!< TSC clock enabled in sleep mode */
#define RCC_AHBSMENR_RNGSMEN                ((uint32_t)0x00100000)        /*!< RNG clock enabled in sleep mode */

/*****************  Bit definition for RCC_APB2SMENR register  ******************/
#define RCC_APB2SMENR_SYSCFGSMEN            ((uint32_t)0x00000001)        /*!< SYSCFG clock enabled in sleep mode */
#define RCC_APB2SMENR_TIM21SMEN             ((uint32_t)0x00000004)        /*!< TIM21 clock enabled in sleep mode */
#define RCC_APB2SMENR_TIM22SMEN             ((uint32_t)0x00000020)        /*!< TIM22 clock enabled in sleep mode */
#define RCC_APB2SMENR_ADC1SMEN              ((uint32_t)0x00000200)        /*!< ADC1 clock enabled in sleep mode */
#define RCC_APB2SMENR_SPI1SMEN              ((uint32_t)0x00001000)        /*!< SPI1 clock enabled in sleep mode */
#define RCC_APB2SMENR_USART1SMEN            ((uint32_t)0x00004000)        /*!< USART1 clock enabled in sleep mode */
#define RCC_APB2SMENR_DBGMCUSMEN            ((uint32_t)0x00400000)        /*!< DBGMCU clock enabled in sleep mode */

/*****************  Bit definition for RCC_APB1SMENR register  ******************/
#define RCC_APB1SMENR_TIM2SMEN              ((uint32_t)0x00000001)        /*!< Timer 2 clock enabled in sleep mode */
#define RCC_APB1SMENR_TIM6SMEN              ((uint32_t)0x00000010)        /*!< Timer 6 clock enabled in sleep mode */
#define RCC_APB1SMENR_LCDSMEN               ((uint32_t)0x00000200)        /*!< LCD clock enabled in sleep mode */
#define RCC_APB1SMENR_WWDGSMEN              ((uint32_t)0x00000800)        /*!< Window Watchdog clock enabled in sleep mode */
#define RCC_APB1SMENR_SPI2SMEN              ((uint32_t)0x00004000)        /*!< SPI2 clock enabled in sleep mode */
#define RCC_APB1SMENR_USART2SMEN            ((uint32_t)0x00020000)        /*!< USART2 clock enabled in sleep mode */
#define RCC_APB1SMENR_LPUART1SMEN           ((uint32_t)0x00040000)        /*!< LPUART1 clock enabled in sleep mode */
#define RCC_APB1SMENR_I2C1SMEN              ((uint32_t)0x00200000)        /*!< I2C1 clock enabled in sleep mode */
#define RCC_APB1SMENR_I2C2SMEN              ((uint32_t)0x00400000)        /*!< I2C2 clock enabled in sleep mode */
#define RCC_APB1SMENR_USBSMEN               ((uint32_t)0x00800000)        /*!< USB clock enabled in sleep mode */
#define RCC_APB1SMENR_CRSSMEN               ((uint32_t)0x08000000)        /*!< CRS clock enabled in sleep mode */
#define RCC_APB1SMENR_PWRSMEN                ((uint32_t)0x10000000)       /*!< PWR clock enabled in sleep mode */
#define RCC_APB1SMENR_DACSMEN               ((uint32_t)0x20000000)        /*!< DAC clock enabled in sleep mode */
#define RCC_APB1SMENR_LPTIM1SMEN            ((uint32_t)0x80000000)        /*!< LPTIM1 clock enabled in sleep mode */

/*******************  Bit definition for RCC_CCIPR register  *******************/
/*!< USART1 Clock source selection */
#define RCC_CCIPR_USART1SEL                 ((uint32_t)0x00000003)        /*!< USART1SEL[1:0] bits */
#define RCC_CCIPR_USART1SEL_0               ((uint32_t)0x00000001)        /*!< Bit 0 */
#define RCC_CCIPR_USART1SEL_1               ((uint32_t)0x00000002)        /*!< Bit 1 */

/*!< USART2 Clock source selection */
#define RCC_CCIPR_USART2SEL                 ((uint32_t)0x0000000C)        /*!< USART2SEL[1:0] bits */
#define RCC_CCIPR_USART2SEL_0               ((uint32_t)0x00000004)        /*!< Bit 0 */
#define RCC_CCIPR_USART2SEL_1               ((uint32_t)0x00000008)        /*!< Bit 1 */

/*!< LPUART1 Clock source selection */ 
#define RCC_CCIPR_LPUART1SEL                ((uint32_t)0x0000C00)         /*!< LPUART1SEL[1:0] bits */
#define RCC_CCIPR_LPUART1SEL_0              ((uint32_t)0x0000400)         /*!< Bit 0 */
#define RCC_CCIPR_LPUART1SEL_1              ((uint32_t)0x0000800)         /*!< Bit 1 */

/*!< I2C1 Clock source selection */
#define RCC_CCIPR_I2C1SEL                   ((uint32_t)0x00003000)        /*!< I2C1SEL [1:0] bits */
#define RCC_CCIPR_I2C1SEL_0                 ((uint32_t)0x00001000)        /*!< Bit 0 */
#define RCC_CCIPR_I2C1SEL_1                 ((uint32_t)0x00002000)        /*!< Bit 1 */


/*!< LPTIM1 Clock source selection */ 
#define RCC_CCIPR_LPTIM1SEL                 ((uint32_t)0x000C0000)        /*!< LPTIM1SEL [1:0] bits */
#define RCC_CCIPR_LPTIM1SEL_0               ((uint32_t)0x00040000)        /*!< Bit 0 */
#define RCC_CCIPR_LPTIM1SEL_1               ((uint32_t)0x00080000)        /*!< Bit 1 */

/*!< HSI48 Clock source selection */ 
#define RCC_CCIPR_HSI48SEL                  ((uint32_t)0x04000000)        /*!< HSI48 RC clock source selection bit for USB and RNG*/

/* Bit name alias maintained for legacy */
#define RCC_CCIPR_HSI48MSEL                 RCC_CCIPR_HSI48SEL

/*******************  Bit definition for RCC_CSR register  *******************/
#define RCC_CSR_LSION                       ((uint32_t)0x00000001)        /*!< Internal Low Speed oscillator enable */
#define RCC_CSR_LSIRDY                      ((uint32_t)0x00000002)        /*!< Internal Low Speed oscillator Ready */

#define RCC_CSR_LSEON                       ((uint32_t)0x00000100)        /*!< External Low Speed oscillator enable */
#define RCC_CSR_LSERDY                      ((uint32_t)0x00000200)        /*!< External Low Speed oscillator Ready */
#define RCC_CSR_LSEBYP                      ((uint32_t)0x00000400)        /*!< External Low Speed oscillator Bypass */
                                             
#define RCC_CSR_LSEDRV                      ((uint32_t)0x00001800)        /*!< LSEDRV[1:0] bits (LSE Osc. drive capability) */
#define RCC_CSR_LSEDRV_0                    ((uint32_t)0x00000800)        /*!< Bit 0 */
#define RCC_CSR_LSEDRV_1                    ((uint32_t)0x00001000)        /*!< Bit 1 */
                                             
#define RCC_CSR_LSECSSON                    ((uint32_t)0x00002000)        /*!< External Low Speed oscillator CSS Enable */
#define RCC_CSR_LSECSSD                     ((uint32_t)0x00004000)        /*!< External Low Speed oscillator CSS Detected */
                                             
/*!< RTC congiguration */                    
#define RCC_CSR_RTCSEL                      ((uint32_t)0x00030000)        /*!< RTCSEL[1:0] bits (RTC clock source selection) */
#define RCC_CSR_RTCSEL_0                    ((uint32_t)0x00010000)        /*!< Bit 0 */
#define RCC_CSR_RTCSEL_1                    ((uint32_t)0x00020000)        /*!< Bit 1 */
                                             
#define RCC_CSR_RTCSEL_NOCLOCK              ((uint32_t)0x00000000)        /*!< No clock */
#define RCC_CSR_RTCSEL_LSE                  ((uint32_t)0x00010000)        /*!< LSE oscillator clock used as RTC clock */
#define RCC_CSR_RTCSEL_LSI                  ((uint32_t)0x00020000)        /*!< LSI oscillator clock used as RTC clock */
#define RCC_CSR_RTCSEL_HSE                  ((uint32_t)0x00030000)        /*!< HSE oscillator clock used as RTC clock */
                                             
#define RCC_CSR_RTCEN                       ((uint32_t)0x00040000)        /*!< RTC clock enable */
#define RCC_CSR_RTCRST                      ((uint32_t)0x00080000)        /*!< RTC software reset  */

#define RCC_CSR_RMVF                        ((uint32_t)0x00800000)        /*!< Remove reset flag */
#define RCC_CSR_FWRSTF                      ((uint32_t)0x01000000)        /*!< Mifare Firewall reset flag */
#define RCC_CSR_OBL                         ((uint32_t)0x02000000)        /*!< OBL reset flag */
#define RCC_CSR_PINRSTF                     ((uint32_t)0x04000000)        /*!< PIN reset flag */
#define RCC_CSR_PORRSTF                     ((uint32_t)0x08000000)        /*!< POR/PDR reset flag */
#define RCC_CSR_SFTRSTF                     ((uint32_t)0x10000000)        /*!< Software Reset flag */
#define RCC_CSR_IWDGRSTF                    ((uint32_t)0x20000000)        /*!< Independent Watchdog reset flag */
#define RCC_CSR_WWDGRSTF                    ((uint32_t)0x40000000)        /*!< Window watchdog reset flag */
#define RCC_CSR_LPWRRSTF                    ((uint32_t)0x80000000)        /*!< Low-Power reset flag */

/******************************************************************************/
/*                                                                            */
/*                                    RNG                                     */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for RNG_CR register  *******************/
#define RNG_CR_RNGEN                         ((uint32_t)0x00000004)
#define RNG_CR_IE                            ((uint32_t)0x00000008)

/********************  Bits definition for RNG_SR register  *******************/
#define RNG_SR_DRDY                          ((uint32_t)0x00000001)
#define RNG_SR_CECS                          ((uint32_t)0x00000002)
#define RNG_SR_SECS                          ((uint32_t)0x00000004)
#define RNG_SR_CEIS                          ((uint32_t)0x00000020)
#define RNG_SR_SEIS                          ((uint32_t)0x00000040)

/******************************************************************************/
/*                                                                            */
/*                           Real-Time Clock (RTC)                            */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for RTC_TR register  *******************/
#define RTC_TR_PM                            ((uint32_t)0x00400000)        /*!<  */
#define RTC_TR_HT                            ((uint32_t)0x00300000)        /*!<  */
#define RTC_TR_HT_0                          ((uint32_t)0x00100000)        /*!<  */
#define RTC_TR_HT_1                          ((uint32_t)0x00200000)        /*!<  */
#define RTC_TR_HU                            ((uint32_t)0x000F0000)        /*!<  */
#define RTC_TR_HU_0                          ((uint32_t)0x00010000)        /*!<  */
#define RTC_TR_HU_1                          ((uint32_t)0x00020000)        /*!<  */
#define RTC_TR_HU_2                          ((uint32_t)0x00040000)        /*!<  */
#define RTC_TR_HU_3                          ((uint32_t)0x00080000)        /*!<  */
#define RTC_TR_MNT                           ((uint32_t)0x00007000)        /*!<  */
#define RTC_TR_MNT_0                         ((uint32_t)0x00001000)        /*!<  */
#define RTC_TR_MNT_1                         ((uint32_t)0x00002000)        /*!<  */
#define RTC_TR_MNT_2                         ((uint32_t)0x00004000)        /*!<  */
#define RTC_TR_MNU                           ((uint32_t)0x00000F00)        /*!<  */
#define RTC_TR_MNU_0                         ((uint32_t)0x00000100)        /*!<  */
#define RTC_TR_MNU_1                         ((uint32_t)0x00000200)        /*!<  */
#define RTC_TR_MNU_2                         ((uint32_t)0x00000400)        /*!<  */
#define RTC_TR_MNU_3                         ((uint32_t)0x00000800)        /*!<  */
#define RTC_TR_ST                            ((uint32_t)0x00000070)        /*!<  */
#define RTC_TR_ST_0                          ((uint32_t)0x00000010)        /*!<  */
#define RTC_TR_ST_1                          ((uint32_t)0x00000020)        /*!<  */
#define RTC_TR_ST_2                          ((uint32_t)0x00000040)        /*!<  */
#define RTC_TR_SU                            ((uint32_t)0x0000000F)        /*!<  */
#define RTC_TR_SU_0                          ((uint32_t)0x00000001)        /*!<  */
#define RTC_TR_SU_1                          ((uint32_t)0x00000002)        /*!<  */
#define RTC_TR_SU_2                          ((uint32_t)0x00000004)        /*!<  */
#define RTC_TR_SU_3                          ((uint32_t)0x00000008)        /*!<  */

/********************  Bits definition for RTC_DR register  *******************/
#define RTC_DR_YT                            ((uint32_t)0x00F00000)        /*!<  */
#define RTC_DR_YT_0                          ((uint32_t)0x00100000)        /*!<  */
#define RTC_DR_YT_1                          ((uint32_t)0x00200000)        /*!<  */
#define RTC_DR_YT_2                          ((uint32_t)0x00400000)        /*!<  */
#define RTC_DR_YT_3                          ((uint32_t)0x00800000)        /*!<  */
#define RTC_DR_YU                            ((uint32_t)0x000F0000)        /*!<  */
#define RTC_DR_YU_0                          ((uint32_t)0x00010000)        /*!<  */
#define RTC_DR_YU_1                          ((uint32_t)0x00020000)        /*!<  */
#define RTC_DR_YU_2                          ((uint32_t)0x00040000)        /*!<  */
#define RTC_DR_YU_3                          ((uint32_t)0x00080000)        /*!<  */
#define RTC_DR_WDU                           ((uint32_t)0x0000E000)        /*!<  */
#define RTC_DR_WDU_0                         ((uint32_t)0x00002000)        /*!<  */
#define RTC_DR_WDU_1                         ((uint32_t)0x00004000)        /*!<  */
#define RTC_DR_WDU_2                         ((uint32_t)0x00008000)        /*!<  */
#define RTC_DR_MT                            ((uint32_t)0x00001000)        /*!<  */
#define RTC_DR_MU                            ((uint32_t)0x00000F00)        /*!<  */
#define RTC_DR_MU_0                          ((uint32_t)0x00000100)        /*!<  */
#define RTC_DR_MU_1                          ((uint32_t)0x00000200)        /*!<  */
#define RTC_DR_MU_2                          ((uint32_t)0x00000400)        /*!<  */
#define RTC_DR_MU_3                          ((uint32_t)0x00000800)        /*!<  */
#define RTC_DR_DT                            ((uint32_t)0x00000030)        /*!<  */
#define RTC_DR_DT_0                          ((uint32_t)0x00000010)        /*!<  */
#define RTC_DR_DT_1                          ((uint32_t)0x00000020)        /*!<  */
#define RTC_DR_DU                            ((uint32_t)0x0000000F)        /*!<  */
#define RTC_DR_DU_0                          ((uint32_t)0x00000001)        /*!<  */
#define RTC_DR_DU_1                          ((uint32_t)0x00000002)        /*!<  */
#define RTC_DR_DU_2                          ((uint32_t)0x00000004)        /*!<  */
#define RTC_DR_DU_3                          ((uint32_t)0x00000008)        /*!<  */

/********************  Bits definition for RTC_CR register  *******************/
#define RTC_CR_COE                           ((uint32_t)0x00800000)        /*!<  */
#define RTC_CR_OSEL                          ((uint32_t)0x00600000)        /*!<  */
#define RTC_CR_OSEL_0                        ((uint32_t)0x00200000)        /*!<  */
#define RTC_CR_OSEL_1                        ((uint32_t)0x00400000)        /*!<  */
#define RTC_CR_POL                           ((uint32_t)0x00100000)        /*!<  */
#define RTC_CR_COSEL                         ((uint32_t)0x00080000)        /*!<  */
#define RTC_CR_BCK                           ((uint32_t)0x00040000)        /*!<  */
#define RTC_CR_SUB1H                         ((uint32_t)0x00020000)        /*!<  */
#define RTC_CR_ADD1H                         ((uint32_t)0x00010000)        /*!<  */
#define RTC_CR_TSIE                          ((uint32_t)0x00008000)        /*!<  */
#define RTC_CR_WUTIE                         ((uint32_t)0x00004000)        /*!<  */
#define RTC_CR_ALRBIE                        ((uint32_t)0x00002000)        /*!<  */
#define RTC_CR_ALRAIE                        ((uint32_t)0x00001000)        /*!<  */
#define RTC_CR_TSE                           ((uint32_t)0x00000800)        /*!<  */
#define RTC_CR_WUTE                          ((uint32_t)0x00000400)        /*!<  */
#define RTC_CR_ALRBE                         ((uint32_t)0x00000200)        /*!<  */
#define RTC_CR_ALRAE                         ((uint32_t)0x00000100)        /*!<  */
#define RTC_CR_FMT                           ((uint32_t)0x00000040)        /*!<  */
#define RTC_CR_BYPSHAD                       ((uint32_t)0x00000020)        /*!<  */
#define RTC_CR_REFCKON                       ((uint32_t)0x00000010)        /*!<  */
#define RTC_CR_TSEDGE                        ((uint32_t)0x00000008)        /*!<  */
#define RTC_CR_WUCKSEL                       ((uint32_t)0x00000007)        /*!<  */
#define RTC_CR_WUCKSEL_0                     ((uint32_t)0x00000001)        /*!<  */
#define RTC_CR_WUCKSEL_1                     ((uint32_t)0x00000002)        /*!<  */
#define RTC_CR_WUCKSEL_2                     ((uint32_t)0x00000004)        /*!<  */

/********************  Bits definition for RTC_ISR register  ******************/
#define RTC_ISR_RECALPF                      ((uint32_t)0x00010000)        /*!<  */
#define RTC_ISR_TAMP2F                       ((uint32_t)0x00004000)        /*!<  */
#define RTC_ISR_TAMP1F                       ((uint32_t)0x00002000)        /*!<  */
#define RTC_ISR_TSOVF                        ((uint32_t)0x00001000)        /*!<  */
#define RTC_ISR_TSF                          ((uint32_t)0x00000800)        /*!<  */
#define RTC_ISR_WUTF                         ((uint32_t)0x00000400)        /*!<  */
#define RTC_ISR_ALRBF                        ((uint32_t)0x00000200)        /*!<  */
#define RTC_ISR_ALRAF                        ((uint32_t)0x00000100)        /*!<  */
#define RTC_ISR_INIT                         ((uint32_t)0x00000080)        /*!<  */
#define RTC_ISR_INITF                        ((uint32_t)0x00000040)        /*!<  */
#define RTC_ISR_RSF                          ((uint32_t)0x00000020)        /*!<  */
#define RTC_ISR_INITS                        ((uint32_t)0x00000010)        /*!<  */
#define RTC_ISR_SHPF                         ((uint32_t)0x00000008)        /*!<  */
#define RTC_ISR_WUTWF                        ((uint32_t)0x00000004)        /*!<  */
#define RTC_ISR_ALRBWF                       ((uint32_t)0x00000002)        /*!<  */
#define RTC_ISR_ALRAWF                       ((uint32_t)0x00000001)        /*!<  */

/********************  Bits definition for RTC_PRER register  *****************/
#define RTC_PRER_PREDIV_A                    ((uint32_t)0x007F0000)        /*!<  */
#define RTC_PRER_PREDIV_S                    ((uint32_t)0x00007FFF)        /*!<  */

/********************  Bits definition for RTC_WUTR register  *****************/
#define RTC_WUTR_WUT                         ((uint32_t)0x0000FFFF)

/********************  Bits definition for RTC_ALRMAR register  ***************/
#define RTC_ALRMAR_MSK4                      ((uint32_t)0x80000000)        /*!<  */
#define RTC_ALRMAR_WDSEL                     ((uint32_t)0x40000000)        /*!<  */
#define RTC_ALRMAR_DT                        ((uint32_t)0x30000000)        /*!<  */
#define RTC_ALRMAR_DT_0                      ((uint32_t)0x10000000)        /*!<  */
#define RTC_ALRMAR_DT_1                      ((uint32_t)0x20000000)        /*!<  */
#define RTC_ALRMAR_DU                        ((uint32_t)0x0F000000)        /*!<  */
#define RTC_ALRMAR_DU_0                      ((uint32_t)0x01000000)        /*!<  */
#define RTC_ALRMAR_DU_1                      ((uint32_t)0x02000000)        /*!<  */
#define RTC_ALRMAR_DU_2                      ((uint32_t)0x04000000)        /*!<  */
#define RTC_ALRMAR_DU_3                      ((uint32_t)0x08000000)        /*!<  */
#define RTC_ALRMAR_MSK3                      ((uint32_t)0x00800000)        /*!<  */
#define RTC_ALRMAR_PM                        ((uint32_t)0x00400000)        /*!<  */
#define RTC_ALRMAR_HT                        ((uint32_t)0x00300000)        /*!<  */
#define RTC_ALRMAR_HT_0                      ((uint32_t)0x00100000)        /*!<  */
#define RTC_ALRMAR_HT_1                      ((uint32_t)0x00200000)        /*!<  */
#define RTC_ALRMAR_HU                        ((uint32_t)0x000F0000)        /*!<  */
#define RTC_ALRMAR_HU_0                      ((uint32_t)0x00010000)        /*!<  */
#define RTC_ALRMAR_HU_1                      ((uint32_t)0x00020000)        /*!<  */
#define RTC_ALRMAR_HU_2                      ((uint32_t)0x00040000)        /*!<  */
#define RTC_ALRMAR_HU_3                      ((uint32_t)0x00080000)        /*!<  */
#define RTC_ALRMAR_MSK2                      ((uint32_t)0x00008000)        /*!<  */
#define RTC_ALRMAR_MNT                       ((uint32_t)0x00007000)        /*!<  */
#define RTC_ALRMAR_MNT_0                     ((uint32_t)0x00001000)        /*!<  */
#define RTC_ALRMAR_MNT_1                     ((uint32_t)0x00002000)        /*!<  */
#define RTC_ALRMAR_MNT_2                     ((uint32_t)0x00004000)        /*!<  */
#define RTC_ALRMAR_MNU                       ((uint32_t)0x00000F00)        /*!<  */
#define RTC_ALRMAR_MNU_0                     ((uint32_t)0x00000100)        /*!<  */
#define RTC_ALRMAR_MNU_1                     ((uint32_t)0x00000200)        /*!<  */
#define RTC_ALRMAR_MNU_2                     ((uint32_t)0x00000400)        /*!<  */
#define RTC_ALRMAR_MNU_3                     ((uint32_t)0x00000800)        /*!<  */
#define RTC_ALRMAR_MSK1                      ((uint32_t)0x00000080)        /*!<  */
#define RTC_ALRMAR_ST                        ((uint32_t)0x00000070)        /*!<  */
#define RTC_ALRMAR_ST_0                      ((uint32_t)0x00000010)        /*!<  */
#define RTC_ALRMAR_ST_1                      ((uint32_t)0x00000020)        /*!<  */
#define RTC_ALRMAR_ST_2                      ((uint32_t)0x00000040)        /*!<  */
#define RTC_ALRMAR_SU                        ((uint32_t)0x0000000F)        /*!<  */
#define RTC_ALRMAR_SU_0                      ((uint32_t)0x00000001)        /*!<  */
#define RTC_ALRMAR_SU_1                      ((uint32_t)0x00000002)        /*!<  */
#define RTC_ALRMAR_SU_2                      ((uint32_t)0x00000004)        /*!<  */
#define RTC_ALRMAR_SU_3                      ((uint32_t)0x00000008)        /*!<  */

/********************  Bits definition for RTC_ALRMBR register  ***************/
#define RTC_ALRMBR_MSK4                      ((uint32_t)0x80000000)        /*!<  */
#define RTC_ALRMBR_WDSEL                     ((uint32_t)0x40000000)        /*!<  */
#define RTC_ALRMBR_DT                        ((uint32_t)0x30000000)        /*!<  */
#define RTC_ALRMBR_DT_0                      ((uint32_t)0x10000000)        /*!<  */
#define RTC_ALRMBR_DT_1                      ((uint32_t)0x20000000)        /*!<  */
#define RTC_ALRMBR_DU                        ((uint32_t)0x0F000000)        /*!<  */
#define RTC_ALRMBR_DU_0                      ((uint32_t)0x01000000)        /*!<  */
#define RTC_ALRMBR_DU_1                      ((uint32_t)0x02000000)        /*!<  */
#define RTC_ALRMBR_DU_2                      ((uint32_t)0x04000000)        /*!<  */
#define RTC_ALRMBR_DU_3                      ((uint32_t)0x08000000)        /*!<  */
#define RTC_ALRMBR_MSK3                      ((uint32_t)0x00800000)        /*!<  */
#define RTC_ALRMBR_PM                        ((uint32_t)0x00400000)        /*!<  */
#define RTC_ALRMBR_HT                        ((uint32_t)0x00300000)        /*!<  */
#define RTC_ALRMBR_HT_0                      ((uint32_t)0x00100000)        /*!<  */
#define RTC_ALRMBR_HT_1                      ((uint32_t)0x00200000)        /*!<  */
#define RTC_ALRMBR_HU                        ((uint32_t)0x000F0000)        /*!<  */
#define RTC_ALRMBR_HU_0                      ((uint32_t)0x00010000)        /*!<  */
#define RTC_ALRMBR_HU_1                      ((uint32_t)0x00020000)        /*!<  */
#define RTC_ALRMBR_HU_2                      ((uint32_t)0x00040000)        /*!<  */
#define RTC_ALRMBR_HU_3                      ((uint32_t)0x00080000)        /*!<  */
#define RTC_ALRMBR_MSK2                      ((uint32_t)0x00008000)        /*!<  */
#define RTC_ALRMBR_MNT                       ((uint32_t)0x00007000)        /*!<  */
#define RTC_ALRMBR_MNT_0                     ((uint32_t)0x00001000)        /*!<  */
#define RTC_ALRMBR_MNT_1                     ((uint32_t)0x00002000)        /*!<  */
#define RTC_ALRMBR_MNT_2                     ((uint32_t)0x00004000)        /*!<  */
#define RTC_ALRMBR_MNU                       ((uint32_t)0x00000F00)        /*!<  */
#define RTC_ALRMBR_MNU_0                     ((uint32_t)0x00000100)        /*!<  */
#define RTC_ALRMBR_MNU_1                     ((uint32_t)0x00000200)        /*!<  */
#define RTC_ALRMBR_MNU_2                     ((uint32_t)0x00000400)        /*!<  */
#define RTC_ALRMBR_MNU_3                     ((uint32_t)0x00000800)        /*!<  */
#define RTC_ALRMBR_MSK1                      ((uint32_t)0x00000080)        /*!<  */
#define RTC_ALRMBR_ST                        ((uint32_t)0x00000070)        /*!<  */
#define RTC_ALRMBR_ST_0                      ((uint32_t)0x00000010)        /*!<  */
#define RTC_ALRMBR_ST_1                      ((uint32_t)0x00000020)        /*!<  */
#define RTC_ALRMBR_ST_2                      ((uint32_t)0x00000040)        /*!<  */
#define RTC_ALRMBR_SU                        ((uint32_t)0x0000000F)        /*!<  */
#define RTC_ALRMBR_SU_0                      ((uint32_t)0x00000001)        /*!<  */
#define RTC_ALRMBR_SU_1                      ((uint32_t)0x00000002)        /*!<  */
#define RTC_ALRMBR_SU_2                      ((uint32_t)0x00000004)        /*!<  */
#define RTC_ALRMBR_SU_3                      ((uint32_t)0x00000008)        /*!<  */

/********************  Bits definition for RTC_WPR register  ******************/
#define RTC_WPR_KEY                          ((uint32_t)0x000000FF)        /*!<  */

/********************  Bits definition for RTC_SSR register  ******************/
#define RTC_SSR_SS                           ((uint32_t)0x0000FFFF)        /*!<  */

/********************  Bits definition for RTC_SHIFTR register  ***************/
#define RTC_SHIFTR_SUBFS                     ((uint32_t)0x00007FFF)        /*!<  */
#define RTC_SHIFTR_ADD1S                     ((uint32_t)0x80000000)        /*!<  */

/********************  Bits definition for RTC_TSTR register  *****************/
#define RTC_TSTR_PM                          ((uint32_t)0x00400000)        /*!<  */
#define RTC_TSTR_HT                          ((uint32_t)0x00300000)        /*!<  */
#define RTC_TSTR_HT_0                        ((uint32_t)0x00100000)        /*!<  */
#define RTC_TSTR_HT_1                        ((uint32_t)0x00200000)        /*!<  */
#define RTC_TSTR_HU                          ((uint32_t)0x000F0000)        /*!<  */
#define RTC_TSTR_HU_0                        ((uint32_t)0x00010000)        /*!<  */
#define RTC_TSTR_HU_1                        ((uint32_t)0x00020000)        /*!<  */
#define RTC_TSTR_HU_2                        ((uint32_t)0x00040000)        /*!<  */
#define RTC_TSTR_HU_3                        ((uint32_t)0x00080000)        /*!<  */
#define RTC_TSTR_MNT                         ((uint32_t)0x00007000)        /*!<  */
#define RTC_TSTR_MNT_0                       ((uint32_t)0x00001000)        /*!<  */
#define RTC_TSTR_MNT_1                       ((uint32_t)0x00002000)        /*!<  */
#define RTC_TSTR_MNT_2                       ((uint32_t)0x00004000)        /*!<  */
#define RTC_TSTR_MNU                         ((uint32_t)0x00000F00)        /*!<  */
#define RTC_TSTR_MNU_0                       ((uint32_t)0x00000100)        /*!<  */
#define RTC_TSTR_MNU_1                       ((uint32_t)0x00000200)        /*!<  */
#define RTC_TSTR_MNU_2                       ((uint32_t)0x00000400)        /*!<  */
#define RTC_TSTR_MNU_3                       ((uint32_t)0x00000800)        /*!<  */
#define RTC_TSTR_ST                          ((uint32_t)0x00000070)        /*!<  */
#define RTC_TSTR_ST_0                        ((uint32_t)0x00000010)        /*!<  */
#define RTC_TSTR_ST_1                        ((uint32_t)0x00000020)        /*!<  */
#define RTC_TSTR_ST_2                        ((uint32_t)0x00000040)        /*!<  */
#define RTC_TSTR_SU                          ((uint32_t)0x0000000F)        /*!<  */
#define RTC_TSTR_SU_0                        ((uint32_t)0x00000001)        /*!<  */
#define RTC_TSTR_SU_1                        ((uint32_t)0x00000002)        /*!<  */
#define RTC_TSTR_SU_2                        ((uint32_t)0x00000004)        /*!<  */
#define RTC_TSTR_SU_3                        ((uint32_t)0x00000008)        /*!<  */

/********************  Bits definition for RTC_TSDR register  *****************/
#define RTC_TSDR_WDU                         ((uint32_t)0x0000E000)        /*!<  */
#define RTC_TSDR_WDU_0                       ((uint32_t)0x00002000)        /*!<  */
#define RTC_TSDR_WDU_1                       ((uint32_t)0x00004000)        /*!<  */
#define RTC_TSDR_WDU_2                       ((uint32_t)0x00008000)        /*!<  */
#define RTC_TSDR_MT                          ((uint32_t)0x00001000)        /*!<  */
#define RTC_TSDR_MU                          ((uint32_t)0x00000F00)        /*!<  */
#define RTC_TSDR_MU_0                        ((uint32_t)0x00000100)        /*!<  */
#define RTC_TSDR_MU_1                        ((uint32_t)0x00000200)        /*!<  */
#define RTC_TSDR_MU_2                        ((uint32_t)0x00000400)        /*!<  */
#define RTC_TSDR_MU_3                        ((uint32_t)0x00000800)        /*!<  */
#define RTC_TSDR_DT                          ((uint32_t)0x00000030)        /*!<  */
#define RTC_TSDR_DT_0                        ((uint32_t)0x00000010)        /*!<  */
#define RTC_TSDR_DT_1                        ((uint32_t)0x00000020)        /*!<  */
#define RTC_TSDR_DU                          ((uint32_t)0x0000000F)        /*!<  */
#define RTC_TSDR_DU_0                        ((uint32_t)0x00000001)        /*!<  */
#define RTC_TSDR_DU_1                        ((uint32_t)0x00000002)        /*!<  */
#define RTC_TSDR_DU_2                        ((uint32_t)0x00000004)        /*!<  */
#define RTC_TSDR_DU_3                        ((uint32_t)0x00000008)        /*!<  */

/********************  Bits definition for RTC_TSSSR register  ****************/
#define RTC_TSSSR_SS                         ((uint32_t)0x0000FFFF)

/********************  Bits definition for RTC_CAL register  *****************/
#define RTC_CAL_CALP                         ((uint32_t)0x00008000)        /*!<  */
#define RTC_CAL_CALW8                        ((uint32_t)0x00004000)        /*!<  */
#define RTC_CAL_CALW16                       ((uint32_t)0x00002000)        /*!<  */
#define RTC_CAL_CALM                         ((uint32_t)0x000001FF)        /*!<  */
#define RTC_CAL_CALM_0                       ((uint32_t)0x00000001)        /*!<  */
#define RTC_CAL_CALM_1                       ((uint32_t)0x00000002)        /*!<  */
#define RTC_CAL_CALM_2                       ((uint32_t)0x00000004)        /*!<  */
#define RTC_CAL_CALM_3                       ((uint32_t)0x00000008)        /*!<  */
#define RTC_CAL_CALM_4                       ((uint32_t)0x00000010)        /*!<  */
#define RTC_CAL_CALM_5                       ((uint32_t)0x00000020)        /*!<  */
#define RTC_CAL_CALM_6                       ((uint32_t)0x00000040)        /*!<  */
#define RTC_CAL_CALM_7                       ((uint32_t)0x00000080)        /*!<  */
#define RTC_CAL_CALM_8                       ((uint32_t)0x00000100)        /*!<  */

/********************  Bits definition for RTC_TAMPCR register  ****************/
#define RTC_TAMPCR_TAMP2MF                   ((uint32_t)0x00200000)        /*!<  */
#define RTC_TAMPCR_TAMP2NOERASE              ((uint32_t)0x00100000)        /*!<  */
#define RTC_TAMPCR_TAMP2IE                   ((uint32_t)0x00080000)        /*!<  */
#define RTC_TAMPCR_TAMP1MF                   ((uint32_t)0x00040000)        /*!<  */
#define RTC_TAMPCR_TAMP1NOERASE              ((uint32_t)0x00020000)        /*!<  */
#define RTC_TAMPCR_TAMP1IE                   ((uint32_t)0x00010000)        /*!<  */
#define RTC_TAMPCR_TAMPPUDIS                 ((uint32_t)0x00008000)        /*!<  */
#define RTC_TAMPCR_TAMPPRCH                  ((uint32_t)0x00006000)        /*!<  */
#define RTC_TAMPCR_TAMPPRCH_0                ((uint32_t)0x00002000)        /*!<  */
#define RTC_TAMPCR_TAMPPRCH_1                ((uint32_t)0x00004000)        /*!<  */
#define RTC_TAMPCR_TAMPFLT                   ((uint32_t)0x00001800)        /*!<  */
#define RTC_TAMPCR_TAMPFLT_0                 ((uint32_t)0x00000800)        /*!<  */
#define RTC_TAMPCR_TAMPFLT_1                 ((uint32_t)0x00001000)        /*!<  */
#define RTC_TAMPCR_TAMPFREQ                  ((uint32_t)0x00000700)        /*!<  */
#define RTC_TAMPCR_TAMPFREQ_0                ((uint32_t)0x00000100)        /*!<  */
#define RTC_TAMPCR_TAMPFREQ_1                ((uint32_t)0x00000200)        /*!<  */
#define RTC_TAMPCR_TAMPFREQ_2                ((uint32_t)0x00000400)        /*!<  */
#define RTC_TAMPCR_TAMPTS                    ((uint32_t)0x00000080)        /*!<  */
#define RTC_TAMPCR_TAMP2TRG                  ((uint32_t)0x00000010)        /*!<  */
#define RTC_TAMPCR_TAMP2E                    ((uint32_t)0x00000008)        /*!<  */
#define RTC_TAMPCR_TAMPIE                    ((uint32_t)0x00000004)        /*!<  */
#define RTC_TAMPCR_TAMP1TRG                  ((uint32_t)0x00000002)        /*!<  */
#define RTC_TAMPCR_TAMP1E                    ((uint32_t)0x00000001)        /*!<  */

/********************  Bits definition for RTC_ALRMASSR register  *************/
#define RTC_ALRMASSR_MASKSS                  ((uint32_t)0x0F000000)
#define RTC_ALRMASSR_MASKSS_0                ((uint32_t)0x01000000)
#define RTC_ALRMASSR_MASKSS_1                ((uint32_t)0x02000000)
#define RTC_ALRMASSR_MASKSS_2                ((uint32_t)0x04000000)
#define RTC_ALRMASSR_MASKSS_3                ((uint32_t)0x08000000)
#define RTC_ALRMASSR_SS                      ((uint32_t)0x00007FFF)

/********************  Bits definition for RTC_ALRMBSSR register  *************/
#define RTC_ALRMBSSR_MASKSS                  ((uint32_t)0x0F000000)
#define RTC_ALRMBSSR_MASKSS_0                ((uint32_t)0x01000000)
#define RTC_ALRMBSSR_MASKSS_1                ((uint32_t)0x02000000)
#define RTC_ALRMBSSR_MASKSS_2                ((uint32_t)0x04000000)
#define RTC_ALRMBSSR_MASKSS_3                ((uint32_t)0x08000000)
#define RTC_ALRMBSSR_SS                      ((uint32_t)0x00007FFF)

/********************  Bits definition for RTC_OR register  ****************/
#define RTC_OR_OUT_RMP                       ((uint32_t)0x00000002)        /*!<  */
#define RTC_OR_ALARMOUTTYPE                  ((uint32_t)0x00000001)        /*!<  */

/* Bit names aliases maintained for legacy */
#define RTC_OR_RTC_OUT_RMP                   RTC_OR_OUT_RMP

/********************  Bits definition for RTC_BKP0R register  ****************/
#define RTC_BKP0R                            ((uint32_t)0xFFFFFFFF)        /*!<  */

/********************  Bits definition for RTC_BKP1R register  ****************/
#define RTC_BKP1R                            ((uint32_t)0xFFFFFFFF)        /*!<  */

/********************  Bits definition for RTC_BKP2R register  ****************/
#define RTC_BKP2R                            ((uint32_t)0xFFFFFFFF)        /*!<  */

/********************  Bits definition for RTC_BKP3R register  ****************/
#define RTC_BKP3R                            ((uint32_t)0xFFFFFFFF)        /*!<  */

/********************  Bits definition for RTC_BKP4R register  ****************/
#define RTC_BKP4R                            ((uint32_t)0xFFFFFFFF)        /*!<  */

/******************************************************************************/
/*                                                                            */
/*                        Serial Peripheral Interface (SPI)                   */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for SPI_CR1 register  ********************/
#define SPI_CR1_CPHA                        ((uint32_t)0x00000001)            /*!< Clock Phase */
#define SPI_CR1_CPOL                        ((uint32_t)0x00000002)            /*!< Clock Polarity */
#define SPI_CR1_MSTR                        ((uint32_t)0x00000004)            /*!< Master Selection */
#define SPI_CR1_BR                          ((uint32_t)0x00000038)            /*!< BR[2:0] bits (Baud Rate Control) */
#define SPI_CR1_BR_0                        ((uint32_t)0x00000008)            /*!< Bit 0 */
#define SPI_CR1_BR_1                        ((uint32_t)0x00000010)            /*!< Bit 1 */
#define SPI_CR1_BR_2                        ((uint32_t)0x00000020)            /*!< Bit 2 */
#define SPI_CR1_SPE                         ((uint32_t)0x00000040)            /*!< SPI Enable */
#define SPI_CR1_LSBFIRST                    ((uint32_t)0x00000080)            /*!< Frame Format */
#define SPI_CR1_SSI                         ((uint32_t)0x00000100)            /*!< Internal slave select */
#define SPI_CR1_SSM                         ((uint32_t)0x00000200)            /*!< Software slave management */
#define SPI_CR1_RXONLY                      ((uint32_t)0x00000400)            /*!< Receive only */
#define SPI_CR1_DFF                         ((uint32_t)0x00000800)            /*!< Data Frame Format */
#define SPI_CR1_CRCNEXT                     ((uint32_t)0x00001000)            /*!< Transmit CRC next */
#define SPI_CR1_CRCEN                       ((uint32_t)0x00002000)            /*!< Hardware CRC calculation enable */
#define SPI_CR1_BIDIOE                      ((uint32_t)0x00004000)            /*!< Output enable in bidirectional mode */
#define SPI_CR1_BIDIMODE                    ((uint32_t)0x00008000)            /*!< Bidirectional data mode enable */

/*******************  Bit definition for SPI_CR2 register  ********************/
#define SPI_CR2_RXDMAEN                     ((uint32_t)0x00000001)            /*!< Rx Buffer DMA Enable */
#define SPI_CR2_TXDMAEN                     ((uint32_t)0x00000002)            /*!< Tx Buffer DMA Enable */
#define SPI_CR2_SSOE                        ((uint32_t)0x00000004)            /*!< SS Output Enable */
#define SPI_CR2_FRF                         ((uint32_t)0x00000010)            /*!< Frame Format Enable */
#define SPI_CR2_ERRIE                       ((uint32_t)0x00000020)            /*!< Error Interrupt Enable */
#define SPI_CR2_RXNEIE                      ((uint32_t)0x00000040)            /*!< RX buffer Not Empty Interrupt Enable */
#define SPI_CR2_TXEIE                       ((uint32_t)0x00000080)            /*!< Tx buffer Empty Interrupt Enable */

/********************  Bit definition for SPI_SR register  ********************/
#define SPI_SR_RXNE                         ((uint32_t)0x00000001)            /*!< Receive buffer Not Empty */
#define SPI_SR_TXE                          ((uint32_t)0x00000002)            /*!< Transmit buffer Empty */
#define SPI_SR_CHSIDE                       ((uint32_t)0x00000004)            /*!< Channel side */
#define SPI_SR_UDR                          ((uint32_t)0x00000008)            /*!< Underrun flag */
#define SPI_SR_CRCERR                       ((uint32_t)0x00000010)            /*!< CRC Error flag */
#define SPI_SR_MODF                         ((uint32_t)0x00000020)            /*!< Mode fault */
#define SPI_SR_OVR                          ((uint32_t)0x00000040)            /*!< Overrun flag */
#define SPI_SR_BSY                          ((uint32_t)0x00000080)            /*!< Busy flag */
#define SPI_SR_FRE                          ((uint32_t)0x00000100)            /*!< TI frame format error */  

/********************  Bit definition for SPI_DR register  ********************/
#define SPI_DR_DR                           ((uint32_t)0x0000FFFF)            /*!< Data Register */

/*******************  Bit definition for SPI_CRCPR register  ******************/
#define SPI_CRCPR_CRCPOLY                   ((uint32_t)0x0000FFFF)            /*!< CRC polynomial register */

/******************  Bit definition for SPI_RXCRCR register  ******************/
#define SPI_RXCRCR_RXCRC                    ((uint32_t)0x0000FFFF)            /*!< Rx CRC Register */

/******************  Bit definition for SPI_TXCRCR register  ******************/
#define SPI_TXCRCR_TXCRC                    ((uint32_t)0x0000FFFF)            /*!< Tx CRC Register */

/******************  Bit definition for SPI_I2SCFGR register  *****************/
#define SPI_I2SCFGR_CHLEN                   ((uint32_t)0x00000001)            /*!<Channel length (number of bits per audio channel) */
#define SPI_I2SCFGR_DATLEN                  ((uint32_t)0x00000006)            /*!<DATLEN[1:0] bits (Data length to be transferred) */
#define SPI_I2SCFGR_DATLEN_0                ((uint32_t)0x00000002)            /*!<Bit 0 */
#define SPI_I2SCFGR_DATLEN_1                ((uint32_t)0x00000004)            /*!<Bit 1 */
#define SPI_I2SCFGR_CKPOL                   ((uint32_t)0x00000008)            /*!<steady state clock polarity */
#define SPI_I2SCFGR_I2SSTD                  ((uint32_t)0x00000030)            /*!<I2SSTD[1:0] bits (I2S standard selection) */
#define SPI_I2SCFGR_I2SSTD_0                ((uint32_t)0x00000010)            /*!<Bit 0 */
#define SPI_I2SCFGR_I2SSTD_1                ((uint32_t)0x00000020)            /*!<Bit 1 */
#define SPI_I2SCFGR_PCMSYNC                 ((uint32_t)0x00000080)            /*!<PCM frame synchronization */
#define SPI_I2SCFGR_I2SCFG                  ((uint32_t)0x00000300)            /*!<I2SCFG[1:0] bits (I2S configuration mode) */
#define SPI_I2SCFGR_I2SCFG_0                ((uint32_t)0x00000100)            /*!<Bit 0 */
#define SPI_I2SCFGR_I2SCFG_1                ((uint32_t)0x00000200)            /*!<Bit 1 */
#define SPI_I2SCFGR_I2SE                    ((uint32_t)0x00000400)            /*!<I2S Enable */
#define SPI_I2SCFGR_I2SMOD                  ((uint32_t)0x00000800)            /*!<I2S mode selection */
/******************  Bit definition for SPI_I2SPR register  *******************/
#define SPI_I2SPR_I2SDIV                    ((uint32_t)0x000000FF)            /*!<I2S Linear prescaler */
#define SPI_I2SPR_ODD                       ((uint32_t)0x00000100)            /*!<Odd factor for the prescaler */
#define SPI_I2SPR_MCKOE                     ((uint32_t)0x00000200)            /*!<Master Clock Output Enable */

/******************************************************************************/
/*                                                                            */
/*                       System Configuration (SYSCFG)                        */
/*                                                                            */
/******************************************************************************/
/*****************  Bit definition for SYSCFG_CFGR1 register  ****************/
#define SYSCFG_CFGR1_MEM_MODE               ((uint32_t)0x00000003) /*!< SYSCFG_Memory Remap Config */
#define SYSCFG_CFGR1_MEM_MODE_0             ((uint32_t)0x00000001) /*!< SYSCFG_Memory Remap Config Bit 0 */
#define SYSCFG_CFGR1_MEM_MODE_1             ((uint32_t)0x00000002) /*!< SYSCFG_Memory Remap Config Bit 1 */
#define SYSCFG_CFGR1_BOOT_MODE              ((uint32_t)0x00000300) /*!< SYSCFG_Boot mode Config */
#define SYSCFG_CFGR1_BOOT_MOD_0             ((uint32_t)0x00000100) /*!< SYSCFG_Boot mode Config Bit 0 */
#define SYSCFG_CFGR1_BOOT_MODE_1            ((uint32_t)0x00000200) /*!< SYSCFG_Boot mode Config Bit 1 */

/*****************  Bit definition for SYSCFG_CFGR2 register  ****************/
#define SYSCFG_CFGR2_FWDISEN                ((uint32_t)0x00000001) /*!< Firewall disable bit */
#define SYSCFG_CFGR2_CAPA                   ((uint32_t)0x0000000E) /*!< Connection of internal Vlcd rail to external capacitors */
#define SYSCFG_CFGR2_CAPA_0                 ((uint32_t)0x00000002)
#define SYSCFG_CFGR2_CAPA_1                 ((uint32_t)0x00000004)
#define SYSCFG_CFGR2_CAPA_2                 ((uint32_t)0x00000008)
#define SYSCFG_CFGR2_I2C_PB6_FMP            ((uint32_t)0x00000100) /*!< I2C PB6 Fast mode plus */
#define SYSCFG_CFGR2_I2C_PB7_FMP            ((uint32_t)0x00000200) /*!< I2C PB7 Fast mode plus */
#define SYSCFG_CFGR2_I2C_PB8_FMP            ((uint32_t)0x00000400) /*!< I2C PB8 Fast mode plus */
#define SYSCFG_CFGR2_I2C_PB9_FMP            ((uint32_t)0x00000800) /*!< I2C PB9 Fast mode plus */
#define SYSCFG_CFGR2_I2C1_FMP               ((uint32_t)0x00001000) /*!< I2C1 Fast mode plus */
#define SYSCFG_CFGR2_I2C2_FMP               ((uint32_t)0x00002000) /*!< I2C2 Fast mode plus */

/*****************  Bit definition for SYSCFG_EXTICR1 register  ***************/
#define SYSCFG_EXTICR1_EXTI0            ((uint32_t)0x0000000F) /*!< EXTI 0 configuration */
#define SYSCFG_EXTICR1_EXTI1            ((uint32_t)0x000000F0) /*!< EXTI 1 configuration */
#define SYSCFG_EXTICR1_EXTI2            ((uint32_t)0x00000F00) /*!< EXTI 2 configuration */
#define SYSCFG_EXTICR1_EXTI3            ((uint32_t)0x0000F000) /*!< EXTI 3 configuration */

/** 
  * @brief  EXTI0 configuration  
  */
#define SYSCFG_EXTICR1_EXTI0_PA         ((uint32_t)0x00000000) /*!< PA[0] pin */
#define SYSCFG_EXTICR1_EXTI0_PB         ((uint32_t)0x00000001) /*!< PB[0] pin */
#define SYSCFG_EXTICR1_EXTI0_PC         ((uint32_t)0x00000002) /*!< PC[0] pin */
#define SYSCFG_EXTICR1_EXTI0_PH         ((uint32_t)0x00000005) /*!< PH[0] pin */

/** 
  * @brief  EXTI1 configuration  
  */ 
#define SYSCFG_EXTICR1_EXTI1_PA         ((uint32_t)0x00000000) /*!< PA[1] pin */
#define SYSCFG_EXTICR1_EXTI1_PB         ((uint32_t)0x00000010) /*!< PB[1] pin */
#define SYSCFG_EXTICR1_EXTI1_PC         ((uint32_t)0x00000020) /*!< PC[1] pin */
#define SYSCFG_EXTICR1_EXTI1_PH         ((uint32_t)0x00000050) /*!< PH[1] pin */

/** 
  * @brief  EXTI2 configuration  
  */
#define SYSCFG_EXTICR1_EXTI2_PA         ((uint32_t)0x00000000) /*!< PA[2] pin */
#define SYSCFG_EXTICR1_EXTI2_PB         ((uint32_t)0x00000100) /*!< PB[2] pin */
#define SYSCFG_EXTICR1_EXTI2_PC         ((uint32_t)0x00000200) /*!< PC[2] pin */
#define SYSCFG_EXTICR1_EXTI2_PD         ((uint32_t)0x00000300) /*!< PD[2] pin */

/** 
  * @brief  EXTI3 configuration  
  */
#define SYSCFG_EXTICR1_EXTI3_PA         ((uint32_t)0x00000000) /*!< PA[3] pin */
#define SYSCFG_EXTICR1_EXTI3_PB         ((uint32_t)0x00001000) /*!< PB[3] pin */
#define SYSCFG_EXTICR1_EXTI3_PC         ((uint32_t)0x00002000) /*!< PC[3] pin */

/*****************  Bit definition for SYSCFG_EXTICR2 register  *****************/
#define SYSCFG_EXTICR2_EXTI4            ((uint32_t)0x0000000F) /*!< EXTI 4 configuration */
#define SYSCFG_EXTICR2_EXTI5            ((uint32_t)0x000000F0) /*!< EXTI 5 configuration */
#define SYSCFG_EXTICR2_EXTI6            ((uint32_t)0x00000F00) /*!< EXTI 6 configuration */
#define SYSCFG_EXTICR2_EXTI7            ((uint32_t)0x0000F000) /*!< EXTI 7 configuration */

/** 
  * @brief  EXTI4 configuration  
  */
#define SYSCFG_EXTICR2_EXTI4_PA         ((uint32_t)0x00000000) /*!< PA[4] pin */
#define SYSCFG_EXTICR2_EXTI4_PB         ((uint32_t)0x00000001) /*!< PB[4] pin */
#define SYSCFG_EXTICR2_EXTI4_PC         ((uint32_t)0x00000002) /*!< PC[4] pin */

/** 
  * @brief  EXTI5 configuration  
  */
#define SYSCFG_EXTICR2_EXTI5_PA         ((uint32_t)0x00000000) /*!< PA[5] pin */
#define SYSCFG_EXTICR2_EXTI5_PB         ((uint32_t)0x00000010) /*!< PB[5] pin */
#define SYSCFG_EXTICR2_EXTI5_PC         ((uint32_t)0x00000020) /*!< PC[5] pin */

/** 
  * @brief  EXTI6 configuration  
  */
#define SYSCFG_EXTICR2_EXTI6_PA         ((uint32_t)0x00000000) /*!< PA[6] pin */
#define SYSCFG_EXTICR2_EXTI6_PB         ((uint32_t)0x00000100) /*!< PB[6] pin */
#define SYSCFG_EXTICR2_EXTI6_PC         ((uint32_t)0x00000200) /*!< PC[6] pin */

/** 
  * @brief  EXTI7 configuration  
  */
#define SYSCFG_EXTICR2_EXTI7_PA         ((uint32_t)0x00000000) /*!< PA[7] pin */
#define SYSCFG_EXTICR2_EXTI7_PB         ((uint32_t)0x00001000) /*!< PB[7] pin */
#define SYSCFG_EXTICR2_EXTI7_PC         ((uint32_t)0x00002000) /*!< PC[7] pin */

/*****************  Bit definition for SYSCFG_EXTICR3 register  *****************/
#define SYSCFG_EXTICR3_EXTI8            ((uint32_t)0x0000000F) /*!< EXTI 8 configuration */
#define SYSCFG_EXTICR3_EXTI9            ((uint32_t)0x000000F0) /*!< EXTI 9 configuration */
#define SYSCFG_EXTICR3_EXTI10           ((uint32_t)0x00000F00) /*!< EXTI 10 configuration */
#define SYSCFG_EXTICR3_EXTI11           ((uint32_t)0x0000F000) /*!< EXTI 11 configuration */

/** 
  * @brief  EXTI8 configuration  
  */
#define SYSCFG_EXTICR3_EXTI8_PA         ((uint32_t)0x00000000) /*!< PA[8] pin */
#define SYSCFG_EXTICR3_EXTI8_PB         ((uint32_t)0x00000001) /*!< PB[8] pin */
#define SYSCFG_EXTICR3_EXTI8_PC         ((uint32_t)0x00000002) /*!< PC[8] pin */

/** 
  * @brief  EXTI9 configuration  
  */
#define SYSCFG_EXTICR3_EXTI9_PA         ((uint32_t)0x00000000) /*!< PA[9] pin */
#define SYSCFG_EXTICR3_EXTI9_PB         ((uint32_t)0x00000010) /*!< PB[9] pin */
#define SYSCFG_EXTICR3_EXTI9_PC         ((uint32_t)0x00000020) /*!< PC[9] pin */

/** 
  * @brief  EXTI10 configuration  
  */
#define SYSCFG_EXTICR3_EXTI10_PA        ((uint32_t)0x00000000) /*!< PA[10] pin */
#define SYSCFG_EXTICR3_EXTI10_PB        ((uint32_t)0x00000100) /*!< PB[10] pin */
#define SYSCFG_EXTICR3_EXTI10_PC        ((uint32_t)0x00000200) /*!< PC[10] pin */

/** 
  * @brief  EXTI11 configuration  
  */
#define SYSCFG_EXTICR3_EXTI11_PA        ((uint32_t)0x00000000) /*!< PA[11] pin */
#define SYSCFG_EXTICR3_EXTI11_PB        ((uint32_t)0x00001000) /*!< PB[11] pin */
#define SYSCFG_EXTICR3_EXTI11_PC        ((uint32_t)0x00002000) /*!< PC[11] pin */

/*****************  Bit definition for SYSCFG_EXTICR4 register  *****************/
#define SYSCFG_EXTICR4_EXTI12           ((uint32_t)0x0000000F) /*!< EXTI 12 configuration */
#define SYSCFG_EXTICR4_EXTI13           ((uint32_t)0x000000F0) /*!< EXTI 13 configuration */
#define SYSCFG_EXTICR4_EXTI14           ((uint32_t)0x00000F00) /*!< EXTI 14 configuration */
#define SYSCFG_EXTICR4_EXTI15           ((uint32_t)0x0000F000) /*!< EXTI 15 configuration */

/** 
  * @brief  EXTI12 configuration  
  */
#define SYSCFG_EXTICR4_EXTI12_PA        ((uint32_t)0x00000000) /*!< PA[12] pin */
#define SYSCFG_EXTICR4_EXTI12_PB        ((uint32_t)0x00000001) /*!< PB[12] pin */
#define SYSCFG_EXTICR4_EXTI12_PC        ((uint32_t)0x00000002) /*!< PC[12] pin */

/** 
  * @brief  EXTI13 configuration  
  */
#define SYSCFG_EXTICR4_EXTI13_PA        ((uint32_t)0x00000000) /*!< PA[13] pin */
#define SYSCFG_EXTICR4_EXTI13_PB        ((uint32_t)0x00000010) /*!< PB[13] pin */
#define SYSCFG_EXTICR4_EXTI13_PC        ((uint32_t)0x00000020) /*!< PC[13] pin */

/** 
  * @brief  EXTI14 configuration  
  */
#define SYSCFG_EXTICR4_EXTI14_PA        ((uint32_t)0x00000000) /*!< PA[14] pin */
#define SYSCFG_EXTICR4_EXTI14_PB        ((uint32_t)0x00000100) /*!< PB[14] pin */
#define SYSCFG_EXTICR4_EXTI14_PC        ((uint32_t)0x00000200) /*!< PC[14] pin */

/** 
  * @brief  EXTI15 configuration  
  */
#define SYSCFG_EXTICR4_EXTI15_PA        ((uint32_t)0x00000000) /*!< PA[15] pin */
#define SYSCFG_EXTICR4_EXTI15_PB        ((uint32_t)0x00001000) /*!< PB[15] pin */
#define SYSCFG_EXTICR4_EXTI15_PC        ((uint32_t)0x00002000) /*!< PC[15] pin */


/*****************  Bit definition for SYSCFG_CFGR3 register  ****************/
#define SYSCFG_CFGR3_EN_VREFINT               ((uint32_t)0x00000001) /*!< Vref Enable bit*/
#define SYSCFG_CFGR3_VREF_OUT                 ((uint32_t)0x00000030) /*!< Verf_ADC connection bit */
#define SYSCFG_CFGR3_VREF_OUT_0               ((uint32_t)0x00000010) /*!< Bit 0 */
#define SYSCFG_CFGR3_VREF_OUT_1               ((uint32_t)0x00000020) /*!< Bit 1 */
#define SYSCFG_CFGR3_ENBUF_VREFINT_ADC        ((uint32_t)0x00000100) /*!< VREFINT reference for ADC enable bit */
#define SYSCFG_CFGR3_ENBUF_SENSOR_ADC         ((uint32_t)0x00000200) /*!< Sensor reference for ADC enable bit */
#define SYSCFG_CFGR3_ENBUFLP_VREFINT_COMP     ((uint32_t)0x00001000) /*!< VREFINT reference for comparator 2 enable bit */
#define SYSCFG_CFGR3_ENREF_HSI48              ((uint32_t)0x00002000) /*!< VREFINT reference or 48 MHz RC oscillator enable bit */
#define SYSCFG_CFGR3_REF_HSI48_RDYF           ((uint32_t)0x04000000) /*!< VREFINT for 48 MHz RC oscillator ready flag */
#define SYSCFG_CFGR3_SENSOR_ADC_RDYF          ((uint32_t)0x08000000) /*!< Sensor for ADC ready flag */
#define SYSCFG_CFGR3_VREFINT_ADC_RDYF         ((uint32_t)0x10000000) /*!< VREFINT for ADC ready flag */
#define SYSCFG_CFGR3_VREFINT_COMP_RDYF        ((uint32_t)0x20000000) /*!< VREFINT for comparator ready flag */
#define SYSCFG_CFGR3_VREFINT_RDYF             ((uint32_t)0x40000000) /*!< VREFINT ready flag */
#define SYSCFG_CFGR3_REF_LOCK                 ((uint32_t)0x80000000) /*!< CFGR3 lock bit */

/* Bit names aliases maintained for legacy */

#define SYSCFG_CFGR3_EN_BGAP                  SYSCFG_CFGR3_EN_VREFINT
#define SYSCFG_CFGR3_ENBUF_BGAP_ADC           SYSCFG_CFGR3_ENBUF_VREFINT_ADC
#define SYSCFG_CFGR3_ENBUFLP_BGAP_COMP        SYSCFG_CFGR3_ENBUFLP_VREFINT_COMP
#define SYSCFG_CFGR3_ENREF_RC48MHz            SYSCFG_CFGR3_ENREF_HSI48
#define SYSCFG_CFGR3_REF_RC48MHz_RDYF         SYSCFG_CFGR3_REF_HSI48_RDYF
#define SYSCFG_VREFINT_ADC_RDYF               SYSCFG_CFGR3_VREFINT_ADC_RDYF

/******************************************************************************/
/*                                                                            */
/*                               Timers (TIM)                                 */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for TIM_CR1 register  ********************/
#define TIM_CR1_CEN                         ((uint32_t)0x00000001)            /*!<Counter enable */
#define TIM_CR1_UDIS                        ((uint32_t)0x00000002)            /*!<Update disable */
#define TIM_CR1_URS                         ((uint32_t)0x00000004)            /*!<Update request source */
#define TIM_CR1_OPM                         ((uint32_t)0x00000008)            /*!<One pulse mode */
#define TIM_CR1_DIR                         ((uint32_t)0x00000010)            /*!<Direction */

#define TIM_CR1_CMS                         ((uint32_t)0x00000060)            /*!<CMS[1:0] bits (Center-aligned mode selection) */
#define TIM_CR1_CMS_0                       ((uint32_t)0x00000020)            /*!<Bit 0 */
#define TIM_CR1_CMS_1                       ((uint32_t)0x00000040)            /*!<Bit 1 */

#define TIM_CR1_ARPE                        ((uint32_t)0x00000080)            /*!<Auto-reload preload enable */

#define TIM_CR1_CKD                         ((uint32_t)0x00000300)            /*!<CKD[1:0] bits (clock division) */
#define TIM_CR1_CKD_0                       ((uint32_t)0x00000100)            /*!<Bit 0 */
#define TIM_CR1_CKD_1                       ((uint32_t)0x00000200)            /*!<Bit 1 */

/*******************  Bit definition for TIM_CR2 register  ********************/
#define TIM_CR2_CCPC                        ((uint32_t)0x00000001)            /*!<Capture/Compare Preloaded Control */
#define TIM_CR2_CCUS                        ((uint32_t)0x00000004)            /*!<Capture/Compare Control Update Selection */
#define TIM_CR2_CCDS                        ((uint32_t)0x00000008)            /*!<Capture/Compare DMA Selection */

#define TIM_CR2_MMS                         ((uint32_t)0x00000070)            /*!<MMS[2:0] bits (Master Mode Selection) */
#define TIM_CR2_MMS_0                       ((uint32_t)0x00000010)            /*!<Bit 0 */
#define TIM_CR2_MMS_1                       ((uint32_t)0x00000020)            /*!<Bit 1 */
#define TIM_CR2_MMS_2                       ((uint32_t)0x00000040)            /*!<Bit 2 */

#define TIM_CR2_TI1S                        ((uint32_t)0x00000080)            /*!<TI1 Selection */
#define TIM_CR2_OIS1                        ((uint32_t)0x00000100)            /*!<Output Idle state 1 (OC1 output) */
#define TIM_CR2_OIS1N                       ((uint32_t)0x00000200)            /*!<Output Idle state 1 (OC1N output) */
#define TIM_CR2_OIS2                        ((uint32_t)0x00000400)            /*!<Output Idle state 2 (OC2 output) */
#define TIM_CR2_OIS2N                       ((uint32_t)0x00000800)            /*!<Output Idle state 2 (OC2N output) */
#define TIM_CR2_OIS3                        ((uint32_t)0x00001000)            /*!<Output Idle state 3 (OC3 output) */
#define TIM_CR2_OIS3N                       ((uint32_t)0x00002000)            /*!<Output Idle state 3 (OC3N output) */
#define TIM_CR2_OIS4                        ((uint32_t)0x00004000)            /*!<Output Idle state 4 (OC4 output) */

/*******************  Bit definition for TIM_SMCR register  *******************/
#define TIM_SMCR_SMS                        ((uint32_t)0x00000007)            /*!<SMS[2:0] bits (Slave mode selection) */
#define TIM_SMCR_SMS_0                      ((uint32_t)0x00000001)            /*!<Bit 0 */
#define TIM_SMCR_SMS_1                      ((uint32_t)0x00000002)            /*!<Bit 1 */
#define TIM_SMCR_SMS_2                      ((uint32_t)0x00000004)            /*!<Bit 2 */

#define TIM_SMCR_OCCS                       ((uint32_t)0x00000008)            /*!< OCREF clear selection */

#define TIM_SMCR_TS                         ((uint32_t)0x00000070)            /*!<TS[2:0] bits (Trigger selection) */
#define TIM_SMCR_TS_0                       ((uint32_t)0x00000010)            /*!<Bit 0 */
#define TIM_SMCR_TS_1                       ((uint32_t)0x00000020)            /*!<Bit 1 */
#define TIM_SMCR_TS_2                       ((uint32_t)0x00000040)            /*!<Bit 2 */

#define TIM_SMCR_MSM                        ((uint32_t)0x00000080)            /*!<Master/slave mode */

#define TIM_SMCR_ETF                        ((uint32_t)0x00000F00)            /*!<ETF[3:0] bits (External trigger filter) */
#define TIM_SMCR_ETF_0                      ((uint32_t)0x00000100)            /*!<Bit 0 */
#define TIM_SMCR_ETF_1                      ((uint32_t)0x00000200)            /*!<Bit 1 */
#define TIM_SMCR_ETF_2                      ((uint32_t)0x00000400)            /*!<Bit 2 */
#define TIM_SMCR_ETF_3                      ((uint32_t)0x00000800)            /*!<Bit 3 */

#define TIM_SMCR_ETPS                       ((uint32_t)0x00003000)            /*!<ETPS[1:0] bits (External trigger prescaler) */
#define TIM_SMCR_ETPS_0                     ((uint32_t)0x00001000)            /*!<Bit 0 */
#define TIM_SMCR_ETPS_1                     ((uint32_t)0x00002000)            /*!<Bit 1 */

#define TIM_SMCR_ECE                        ((uint32_t)0x00004000)            /*!<External clock enable */
#define TIM_SMCR_ETP                        ((uint32_t)0x00008000)            /*!<External trigger polarity */

/*******************  Bit definition for TIM_DIER register  *******************/
#define TIM_DIER_UIE                        ((uint32_t)0x00000001)            /*!<Update interrupt enable */
#define TIM_DIER_CC1IE                      ((uint32_t)0x00000002)            /*!<Capture/Compare 1 interrupt enable */
#define TIM_DIER_CC2IE                      ((uint32_t)0x00000004)            /*!<Capture/Compare 2 interrupt enable */
#define TIM_DIER_CC3IE                      ((uint32_t)0x00000008)            /*!<Capture/Compare 3 interrupt enable */
#define TIM_DIER_CC4IE                      ((uint32_t)0x00000010)            /*!<Capture/Compare 4 interrupt enable */
#define TIM_DIER_TIE                        ((uint32_t)0x00000040)            /*!<Trigger interrupt enable */
#define TIM_DIER_UDE                        ((uint32_t)0x00000100)            /*!<Update DMA request enable */
#define TIM_DIER_CC1DE                      ((uint32_t)0x00000200)            /*!<Capture/Compare 1 DMA request enable */
#define TIM_DIER_CC2DE                      ((uint32_t)0x00000400)            /*!<Capture/Compare 2 DMA request enable */
#define TIM_DIER_CC3DE                      ((uint32_t)0x00000800)            /*!<Capture/Compare 3 DMA request enable */
#define TIM_DIER_CC4DE                      ((uint32_t)0x00001000)            /*!<Capture/Compare 4 DMA request enable */
#define TIM_DIER_TDE                        ((uint32_t)0x00004000)            /*!<Trigger DMA request enable */

/********************  Bit definition for TIM_SR register  ********************/
#define TIM_SR_UIF                          ((uint32_t)0x00000001)            /*!<Update interrupt Flag */
#define TIM_SR_CC1IF                        ((uint32_t)0x00000002)            /*!<Capture/Compare 1 interrupt Flag */
#define TIM_SR_CC2IF                        ((uint32_t)0x00000004)            /*!<Capture/Compare 2 interrupt Flag */
#define TIM_SR_CC3IF                        ((uint32_t)0x00000008)            /*!<Capture/Compare 3 interrupt Flag */
#define TIM_SR_CC4IF                        ((uint32_t)0x00000010)            /*!<Capture/Compare 4 interrupt Flag */
#define TIM_SR_COMIF                        ((uint32_t)0x00000020)            /*!<COM interrupt Flag */
#define TIM_SR_TIF                          ((uint32_t)0x00000040)            /*!<Trigger interrupt Flag */
#define TIM_SR_BIF                          ((uint32_t)0x00000080)            /*!<Break interrupt Flag */
#define TIM_SR_CC1OF                        ((uint32_t)0x00000200)            /*!<Capture/Compare 1 Overcapture Flag */
#define TIM_SR_CC2OF                        ((uint32_t)0x00000400)            /*!<Capture/Compare 2 Overcapture Flag */
#define TIM_SR_CC3OF                        ((uint32_t)0x00000800)            /*!<Capture/Compare 3 Overcapture Flag */
#define TIM_SR_CC4OF                        ((uint32_t)0x00001000)            /*!<Capture/Compare 4 Overcapture Flag */

/*******************  Bit definition for TIM_EGR register  ********************/
#define TIM_EGR_UG                          ((uint32_t)0x00000001)               /*!<Update Generation */
#define TIM_EGR_CC1G                        ((uint32_t)0x00000002)               /*!<Capture/Compare 1 Generation */
#define TIM_EGR_CC2G                        ((uint32_t)0x00000004)               /*!<Capture/Compare 2 Generation */
#define TIM_EGR_CC3G                        ((uint32_t)0x00000008)               /*!<Capture/Compare 3 Generation */
#define TIM_EGR_CC4G                        ((uint32_t)0x00000010)               /*!<Capture/Compare 4 Generation */
#define TIM_EGR_COMG                        ((uint32_t)0x00000020)               /*!<Capture/Compare Control Update Generation */
#define TIM_EGR_TG                          ((uint32_t)0x00000040)               /*!<Trigger Generation */
#define TIM_EGR_BG                          ((uint32_t)0x00000080)               /*!<Break Generation */

/******************  Bit definition for TIM_CCMR1 register  *******************/
#define TIM_CCMR1_CC1S                      ((uint32_t)0x00000003)            /*!<CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define TIM_CCMR1_CC1S_0                    ((uint32_t)0x00000001)            /*!<Bit 0 */
#define TIM_CCMR1_CC1S_1                    ((uint32_t)0x00000002)            /*!<Bit 1 */

#define TIM_CCMR1_OC1FE                     ((uint32_t)0x00000004)            /*!<Output Compare 1 Fast enable */
#define TIM_CCMR1_OC1PE                     ((uint32_t)0x00000008)            /*!<Output Compare 1 Preload enable */

#define TIM_CCMR1_OC1M                      ((uint32_t)0x00000070)            /*!<OC1M[2:0] bits (Output Compare 1 Mode) */
#define TIM_CCMR1_OC1M_0                    ((uint32_t)0x00000010)            /*!<Bit 0 */
#define TIM_CCMR1_OC1M_1                    ((uint32_t)0x00000020)            /*!<Bit 1 */
#define TIM_CCMR1_OC1M_2                    ((uint32_t)0x00000040)            /*!<Bit 2 */

#define TIM_CCMR1_OC1CE                     ((uint32_t)0x00000080)            /*!<Output Compare 1Clear Enable */

#define TIM_CCMR1_CC2S                      ((uint32_t)0x00000300)            /*!<CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define TIM_CCMR1_CC2S_0                    ((uint32_t)0x00000100)            /*!<Bit 0 */
#define TIM_CCMR1_CC2S_1                    ((uint32_t)0x00000200)            /*!<Bit 1 */

#define TIM_CCMR1_OC2FE                     ((uint32_t)0x00000400)            /*!<Output Compare 2 Fast enable */
#define TIM_CCMR1_OC2PE                     ((uint32_t)0x00000800)            /*!<Output Compare 2 Preload enable */

#define TIM_CCMR1_OC2M                      ((uint32_t)0x00007000)            /*!<OC2M[2:0] bits (Output Compare 2 Mode) */
#define TIM_CCMR1_OC2M_0                    ((uint32_t)0x00001000)            /*!<Bit 0 */
#define TIM_CCMR1_OC2M_1                    ((uint32_t)0x00002000)            /*!<Bit 1 */
#define TIM_CCMR1_OC2M_2                    ((uint32_t)0x00004000)            /*!<Bit 2 */

#define TIM_CCMR1_OC2CE                     ((uint32_t)0x00008000)            /*!<Output Compare 2 Clear Enable */

/*----------------------------------------------------------------------------*/

#define TIM_CCMR1_IC1PSC                    ((uint32_t)0x0000000C)            /*!<IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define TIM_CCMR1_IC1PSC_0                  ((uint32_t)0x00000004)            /*!<Bit 0 */
#define TIM_CCMR1_IC1PSC_1                  ((uint32_t)0x00000008)            /*!<Bit 1 */

#define TIM_CCMR1_IC1F                      ((uint32_t)0x000000F0)            /*!<IC1F[3:0] bits (Input Capture 1 Filter) */
#define TIM_CCMR1_IC1F_0                    ((uint32_t)0x00000010)            /*!<Bit 0 */
#define TIM_CCMR1_IC1F_1                    ((uint32_t)0x00000020)            /*!<Bit 1 */
#define TIM_CCMR1_IC1F_2                    ((uint32_t)0x00000040)            /*!<Bit 2 */
#define TIM_CCMR1_IC1F_3                    ((uint32_t)0x00000080)            /*!<Bit 3 */

#define TIM_CCMR1_IC2PSC                    ((uint32_t)0x00000C00)            /*!<IC2PSC[1:0] bits (Input Capture 2 Prescaler) */
#define TIM_CCMR1_IC2PSC_0                  ((uint32_t)0x00000400)            /*!<Bit 0 */
#define TIM_CCMR1_IC2PSC_1                  ((uint32_t)0x00000800)            /*!<Bit 1 */

#define TIM_CCMR1_IC2F                      ((uint32_t)0x0000F000)            /*!<IC2F[3:0] bits (Input Capture 2 Filter) */
#define TIM_CCMR1_IC2F_0                    ((uint32_t)0x00001000)            /*!<Bit 0 */
#define TIM_CCMR1_IC2F_1                    ((uint32_t)0x00002000)            /*!<Bit 1 */
#define TIM_CCMR1_IC2F_2                    ((uint32_t)0x00004000)            /*!<Bit 2 */
#define TIM_CCMR1_IC2F_3                    ((uint32_t)0x00008000)            /*!<Bit 3 */

/******************  Bit definition for TIM_CCMR2 register  *******************/
#define TIM_CCMR2_CC3S                      ((uint32_t)0x00000003)            /*!<CC3S[1:0] bits (Capture/Compare 3 Selection) */
#define TIM_CCMR2_CC3S_0                    ((uint32_t)0x00000001)            /*!<Bit 0 */
#define TIM_CCMR2_CC3S_1                    ((uint32_t)0x00000002)            /*!<Bit 1 */

#define TIM_CCMR2_OC3FE                     ((uint32_t)0x00000004)            /*!<Output Compare 3 Fast enable */
#define TIM_CCMR2_OC3PE                     ((uint32_t)0x00000008)            /*!<Output Compare 3 Preload enable */

#define TIM_CCMR2_OC3M                      ((uint32_t)0x00000070)            /*!<OC3M[2:0] bits (Output Compare 3 Mode) */
#define TIM_CCMR2_OC3M_0                    ((uint32_t)0x00000010)            /*!<Bit 0 */
#define TIM_CCMR2_OC3M_1                    ((uint32_t)0x00000020)            /*!<Bit 1 */
#define TIM_CCMR2_OC3M_2                    ((uint32_t)0x00000040)            /*!<Bit 2 */

#define TIM_CCMR2_OC3CE                     ((uint32_t)0x00000080)            /*!<Output Compare 3 Clear Enable */

#define TIM_CCMR2_CC4S                      ((uint32_t)0x00000300)            /*!<CC4S[1:0] bits (Capture/Compare 4 Selection) */
#define TIM_CCMR2_CC4S_0                    ((uint32_t)0x00000100)            /*!<Bit 0 */
#define TIM_CCMR2_CC4S_1                    ((uint32_t)0x00000200)            /*!<Bit 1 */

#define TIM_CCMR2_OC4FE                     ((uint32_t)0x00000400)            /*!<Output Compare 4 Fast enable */
#define TIM_CCMR2_OC4PE                     ((uint32_t)0x00000800)            /*!<Output Compare 4 Preload enable */

#define TIM_CCMR2_OC4M                      ((uint32_t)0x00007000)            /*!<OC4M[2:0] bits (Output Compare 4 Mode) */
#define TIM_CCMR2_OC4M_0                    ((uint32_t)0x00001000)            /*!<Bit 0 */
#define TIM_CCMR2_OC4M_1                    ((uint32_t)0x00002000)            /*!<Bit 1 */
#define TIM_CCMR2_OC4M_2                    ((uint32_t)0x00004000)            /*!<Bit 2 */

#define TIM_CCMR2_OC4CE                     ((uint32_t)0x00008000)            /*!<Output Compare 4 Clear Enable */

/*----------------------------------------------------------------------------*/

#define TIM_CCMR2_IC3PSC                    ((uint32_t)0x0000000C)            /*!<IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define TIM_CCMR2_IC3PSC_0                  ((uint32_t)0x00000004)            /*!<Bit 0 */
#define TIM_CCMR2_IC3PSC_1                  ((uint32_t)0x00000008)            /*!<Bit 1 */

#define TIM_CCMR2_IC3F                      ((uint32_t)0x000000F0)            /*!<IC3F[3:0] bits (Input Capture 3 Filter) */
#define TIM_CCMR2_IC3F_0                    ((uint32_t)0x00000010)            /*!<Bit 0 */
#define TIM_CCMR2_IC3F_1                    ((uint32_t)0x00000020)            /*!<Bit 1 */
#define TIM_CCMR2_IC3F_2                    ((uint32_t)0x00000040)            /*!<Bit 2 */
#define TIM_CCMR2_IC3F_3                    ((uint32_t)0x00000080)            /*!<Bit 3 */

#define TIM_CCMR2_IC4PSC                    ((uint32_t)0x00000C00)            /*!<IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define TIM_CCMR2_IC4PSC_0                  ((uint32_t)0x00000400)            /*!<Bit 0 */
#define TIM_CCMR2_IC4PSC_1                  ((uint32_t)0x00000800)            /*!<Bit 1 */

#define TIM_CCMR2_IC4F                      ((uint32_t)0x0000F000)            /*!<IC4F[3:0] bits (Input Capture 4 Filter) */
#define TIM_CCMR2_IC4F_0                    ((uint32_t)0x00001000)            /*!<Bit 0 */
#define TIM_CCMR2_IC4F_1                    ((uint32_t)0x00002000)            /*!<Bit 1 */
#define TIM_CCMR2_IC4F_2                    ((uint32_t)0x00004000)            /*!<Bit 2 */
#define TIM_CCMR2_IC4F_3                    ((uint32_t)0x00008000)            /*!<Bit 3 */

/*******************  Bit definition for TIM_CCER register  *******************/
#define TIM_CCER_CC1E                       ((uint32_t)0x00000001)            /*!<Capture/Compare 1 output enable */
#define TIM_CCER_CC1P                       ((uint32_t)0x00000002)            /*!<Capture/Compare 1 output Polarity */
#define TIM_CCER_CC1NE                      ((uint32_t)0x00000004)            /*!<Capture/Compare 1 Complementary output enable */
#define TIM_CCER_CC1NP                      ((uint32_t)0x00000008)            /*!<Capture/Compare 1 Complementary output Polarity */
#define TIM_CCER_CC2E                       ((uint32_t)0x00000010)            /*!<Capture/Compare 2 output enable */
#define TIM_CCER_CC2P                       ((uint32_t)0x00000020)            /*!<Capture/Compare 2 output Polarity */
#define TIM_CCER_CC2NE                      ((uint32_t)0x00000040)            /*!<Capture/Compare 2 Complementary output enable */
#define TIM_CCER_CC2NP                      ((uint32_t)0x00000080)            /*!<Capture/Compare 2 Complementary output Polarity */
#define TIM_CCER_CC3E                       ((uint32_t)0x00000100)            /*!<Capture/Compare 3 output enable */
#define TIM_CCER_CC3P                       ((uint32_t)0x00000200)            /*!<Capture/Compare 3 output Polarity */
#define TIM_CCER_CC3NE                      ((uint32_t)0x00000400)            /*!<Capture/Compare 3 Complementary output enable */
#define TIM_CCER_CC3NP                      ((uint32_t)0x00000800)            /*!<Capture/Compare 3 Complementary output Polarity */
#define TIM_CCER_CC4E                       ((uint32_t)0x00001000)            /*!<Capture/Compare 4 output enable */
#define TIM_CCER_CC4P                       ((uint32_t)0x00002000)            /*!<Capture/Compare 4 output Polarity */
#define TIM_CCER_CC4NP                      ((uint32_t)0x00008000)            /*!<Capture/Compare 4 Complementary output Polarity */

/*******************  Bit definition for TIM_CNT register  ********************/
#define TIM_CNT_CNT                         ((uint32_t)0x0000FFFF)            /*!<Counter Value */

/*******************  Bit definition for TIM_PSC register  ********************/
#define TIM_PSC_PSC                         ((uint32_t)0x0000FFFF)            /*!<Prescaler Value */

/*******************  Bit definition for TIM_ARR register  ********************/
#define TIM_ARR_ARR                         ((uint32_t)0x0000FFFF)            /*!<actual auto-reload Value */

/*******************  Bit definition for TIM_RCR register  ********************/
#define TIM_RCR_REP                         ((uint32_t)0x000000FF)            /*!<Repetition Counter Value */

/*******************  Bit definition for TIM_CCR1 register  *******************/
#define TIM_CCR1_CCR1                       ((uint32_t)0x0000FFFF)            /*!<Capture/Compare 1 Value */

/*******************  Bit definition for TIM_CCR2 register  *******************/
#define TIM_CCR2_CCR2                       ((uint32_t)0x0000FFFF)            /*!<Capture/Compare 2 Value */

/*******************  Bit definition for TIM_CCR3 register  *******************/
#define TIM_CCR3_CCR3                       ((uint32_t)0x0000FFFF)            /*!<Capture/Compare 3 Value */

/*******************  Bit definition for TIM_CCR4 register  *******************/
#define TIM_CCR4_CCR4                       ((uint32_t)0x0000FFFF)            /*!<Capture/Compare 4 Value */

/*******************  Bit definition for TIM_BDTR register  *******************/
#define TIM_BDTR_DTG                        ((uint32_t)0x000000FF)            /*!<DTG[0:7] bits (Dead-Time Generator set-up) */
#define TIM_BDTR_DTG_0                      ((uint32_t)0x00000001)            /*!<Bit 0 */
#define TIM_BDTR_DTG_1                      ((uint32_t)0x00000002)            /*!<Bit 1 */
#define TIM_BDTR_DTG_2                      ((uint32_t)0x00000004)            /*!<Bit 2 */
#define TIM_BDTR_DTG_3                      ((uint32_t)0x00000008)            /*!<Bit 3 */
#define TIM_BDTR_DTG_4                      ((uint32_t)0x00000010)            /*!<Bit 4 */
#define TIM_BDTR_DTG_5                      ((uint32_t)0x00000020)            /*!<Bit 5 */
#define TIM_BDTR_DTG_6                      ((uint32_t)0x00000040)            /*!<Bit 6 */
#define TIM_BDTR_DTG_7                      ((uint32_t)0x00000080)            /*!<Bit 7 */

#define TIM_BDTR_LOCK                       ((uint32_t)0x00000300)            /*!<LOCK[1:0] bits (Lock Configuration) */
#define TIM_BDTR_LOCK_0                     ((uint32_t)0x00000100)            /*!<Bit 0 */
#define TIM_BDTR_LOCK_1                     ((uint32_t)0x00000200)            /*!<Bit 1 */

#define TIM_BDTR_OSSI                       ((uint32_t)0x00000400)            /*!<Off-State Selection for Idle mode */
#define TIM_BDTR_OSSR                       ((uint32_t)0x00000800)            /*!<Off-State Selection for Run mode */
#define TIM_BDTR_BKE                        ((uint32_t)0x00001000)            /*!<Break enable */
#define TIM_BDTR_BKP                        ((uint32_t)0x00002000)            /*!<Break Polarity */
#define TIM_BDTR_AOE                        ((uint32_t)0x00004000)            /*!<Automatic Output enable */
#define TIM_BDTR_MOE                        ((uint32_t)0x00008000)            /*!<Main Output enable */

/*******************  Bit definition for TIM_DCR register  ********************/
#define TIM_DCR_DBA                         ((uint32_t)0x0000001F)            /*!<DBA[4:0] bits (DMA Base Address) */
#define TIM_DCR_DBA_0                       ((uint32_t)0x00000001)            /*!<Bit 0 */
#define TIM_DCR_DBA_1                       ((uint32_t)0x00000002)            /*!<Bit 1 */
#define TIM_DCR_DBA_2                       ((uint32_t)0x00000004)            /*!<Bit 2 */
#define TIM_DCR_DBA_3                       ((uint32_t)0x00000008)            /*!<Bit 3 */
#define TIM_DCR_DBA_4                       ((uint32_t)0x00000010)            /*!<Bit 4 */

#define TIM_DCR_DBL                         ((uint32_t)0x00001F00)            /*!<DBL[4:0] bits (DMA Burst Length) */
#define TIM_DCR_DBL_0                       ((uint32_t)0x00000100)            /*!<Bit 0 */
#define TIM_DCR_DBL_1                       ((uint32_t)0x00000200)            /*!<Bit 1 */
#define TIM_DCR_DBL_2                       ((uint32_t)0x00000400)            /*!<Bit 2 */
#define TIM_DCR_DBL_3                       ((uint32_t)0x00000800)            /*!<Bit 3 */
#define TIM_DCR_DBL_4                       ((uint32_t)0x00001000)            /*!<Bit 4 */

/*******************  Bit definition for TIM_DMAR register  *******************/
#define TIM_DMAR_DMAB                       ((uint32_t)0x0000FFFF)            /*!<DMA register for burst accesses */

/*******************  Bit definition for TIM_OR register  *********************/
#define TIM2_OR_ETR_RMP                     ((uint32_t)0x00000007)            /*!<ETR_RMP[1:0] bits (TIM2 ETR remap) */
#define TIM2_OR_ETR_RMP_0                   ((uint32_t)0x00000001)            /*!<Bit 0 */
#define TIM2_OR_ETR_RMP_1                   ((uint32_t)0x00000002)            /*!<Bit 1 */
#define TIM2_OR_ETR_RMP_2                   ((uint32_t)0x00000004)            /*!<Bit 2 */
#define TIM2_OR_TI4_RMP                     ((uint32_t)0x0000018)             /*!<TI4_RMP[1:0] bits (TIM2 Input 4 remap) */
#define TIM2_OR_TI4_RMP_0                   ((uint32_t)0x00000008)            /*!<Bit 0 */
#define TIM2_OR_TI4_RMP_1                   ((uint32_t)0x00000010)            /*!<Bit 1 */

#define TIM21_OR_ETR_RMP                    ((uint32_t)0x00000003)            /*!<ETR_RMP[1:0] bits (TIM21 ETR remap) */
#define TIM21_OR_ETR_RMP_0                  ((uint32_t)0x00000001)            /*!<Bit 0 */
#define TIM21_OR_ETR_RMP_1                  ((uint32_t)0x00000002)            /*!<Bit 1 */
#define TIM21_OR_TI1_RMP                    ((uint32_t)0x0000001C)            /*!<TI1_RMP[2:0] bits (TIM21 Input 1 remap) */
#define TIM21_OR_TI1_RMP_0                  ((uint32_t)0x00000004)            /*!<Bit 0 */
#define TIM21_OR_TI1_RMP_1                  ((uint32_t)0x00000008)            /*!<Bit 1 */
#define TIM21_OR_TI1_RMP_2                  ((uint32_t)0x00000010)            /*!<Bit 2 */
#define TIM21_OR_TI2_RMP                    ((uint32_t)0x00000020)            /*!<TI2_RMP bit (TIM21 Input 2 remap) */

#define TIM22_OR_ETR_RMP                    ((uint32_t)0x00000003)            /*!<ETR_RMP[1:0] bits (TIM22 ETR remap) */
#define TIM22_OR_ETR_RMP_0                  ((uint32_t)0x00000001)            /*!<Bit 0 */
#define TIM22_OR_ETR_RMP_1                  ((uint32_t)0x00000002)            /*!<Bit 1 */
#define TIM22_OR_TI1_RMP                    ((uint32_t)0x0000000C)            /*!<TI1_RMP[2:0] bits (TIM22 Input 1 remap) */
#define TIM22_OR_TI1_RMP_0                  ((uint32_t)0x00000004)            /*!<Bit 0 */
#define TIM22_OR_TI1_RMP_1                  ((uint32_t)0x00000008)            /*!<Bit 1 */


/******************************************************************************/
/*                                                                            */
/*                          Touch Sensing Controller (TSC)                    */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for TSC_CR register  *********************/
#define TSC_CR_TSCE                         ((uint32_t)0x00000001)            /*!<Touch sensing controller enable */
#define TSC_CR_START                        ((uint32_t)0x00000002)            /*!<Start acquisition */
#define TSC_CR_AM                           ((uint32_t)0x00000004)            /*!<Acquisition mode */
#define TSC_CR_SYNCPOL                      ((uint32_t)0x00000008)            /*!<Synchronization pin polarity */
#define TSC_CR_IODEF                        ((uint32_t)0x00000010)            /*!<IO default mode */

#define TSC_CR_MCV                          ((uint32_t)0x000000E0)            /*!<MCV[2:0] bits (Max Count Value) */
#define TSC_CR_MCV_0                        ((uint32_t)0x00000020)            /*!<Bit 0 */
#define TSC_CR_MCV_1                        ((uint32_t)0x00000040)            /*!<Bit 1 */
#define TSC_CR_MCV_2                        ((uint32_t)0x00000080)            /*!<Bit 2 */

#define TSC_CR_PGPSC                        ((uint32_t)0x00007000)            /*!<PGPSC[2:0] bits (Pulse Generator Prescaler) */
#define TSC_CR_PGPSC_0                      ((uint32_t)0x00001000)            /*!<Bit 0 */
#define TSC_CR_PGPSC_1                      ((uint32_t)0x00002000)            /*!<Bit 1 */
#define TSC_CR_PGPSC_2                      ((uint32_t)0x00004000)            /*!<Bit 2 */

#define TSC_CR_SSPSC                        ((uint32_t)0x00008000)            /*!<Spread Spectrum Prescaler */
#define TSC_CR_SSE                          ((uint32_t)0x00010000)            /*!<Spread Spectrum Enable */

#define TSC_CR_SSD                          ((uint32_t)0x00FE0000)            /*!<SSD[6:0] bits (Spread Spectrum Deviation) */
#define TSC_CR_SSD_0                        ((uint32_t)0x00020000)            /*!<Bit 0 */
#define TSC_CR_SSD_1                        ((uint32_t)0x00040000)            /*!<Bit 1 */
#define TSC_CR_SSD_2                        ((uint32_t)0x00080000)            /*!<Bit 2 */
#define TSC_CR_SSD_3                        ((uint32_t)0x00100000)            /*!<Bit 3 */
#define TSC_CR_SSD_4                        ((uint32_t)0x00200000)            /*!<Bit 4 */
#define TSC_CR_SSD_5                        ((uint32_t)0x00400000)            /*!<Bit 5 */
#define TSC_CR_SSD_6                        ((uint32_t)0x00800000)            /*!<Bit 6 */

#define TSC_CR_CTPL                         ((uint32_t)0x0F000000)            /*!<CTPL[3:0] bits (Charge Transfer pulse low) */
#define TSC_CR_CTPL_0                       ((uint32_t)0x01000000)            /*!<Bit 0 */
#define TSC_CR_CTPL_1                       ((uint32_t)0x02000000)            /*!<Bit 1 */
#define TSC_CR_CTPL_2                       ((uint32_t)0x04000000)            /*!<Bit 2 */
#define TSC_CR_CTPL_3                       ((uint32_t)0x08000000)            /*!<Bit 3 */

#define TSC_CR_CTPH                         ((uint32_t)0xF0000000)            /*!<CTPH[3:0] bits (Charge Transfer pulse high) */
#define TSC_CR_CTPH_0                       ((uint32_t)0x10000000)            /*!<Bit 0 */
#define TSC_CR_CTPH_1                       ((uint32_t)0x20000000)            /*!<Bit 1 */
#define TSC_CR_CTPH_2                       ((uint32_t)0x40000000)            /*!<Bit 2 */
#define TSC_CR_CTPH_3                       ((uint32_t)0x80000000)            /*!<Bit 3 */

/*******************  Bit definition for TSC_IER register  ********************/
#define TSC_IER_EOAIE                       ((uint32_t)0x00000001)            /*!<End of acquisition interrupt enable */
#define TSC_IER_MCEIE                       ((uint32_t)0x00000002)            /*!<Max count error interrupt enable */

/*******************  Bit definition for TSC_ICR register  ********************/
#define TSC_ICR_EOAIC                       ((uint32_t)0x00000001)            /*!<End of acquisition interrupt clear */
#define TSC_ICR_MCEIC                       ((uint32_t)0x00000002)            /*!<Max count error interrupt clear */

/*******************  Bit definition for TSC_ISR register  ********************/
#define TSC_ISR_EOAF                        ((uint32_t)0x00000001)            /*!<End of acquisition flag */
#define TSC_ISR_MCEF                        ((uint32_t)0x00000002)            /*!<Max count error flag */

/*******************  Bit definition for TSC_IOHCR register  ******************/
#define TSC_IOHCR_G1_IO1                    ((uint32_t)0x00000001)            /*!<GROUP1_IO1 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G1_IO2                    ((uint32_t)0x00000002)            /*!<GROUP1_IO2 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G1_IO3                    ((uint32_t)0x00000004)            /*!<GROUP1_IO3 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G1_IO4                    ((uint32_t)0x00000008)            /*!<GROUP1_IO4 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G2_IO1                    ((uint32_t)0x00000010)            /*!<GROUP2_IO1 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G2_IO2                    ((uint32_t)0x00000020)            /*!<GROUP2_IO2 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G2_IO3                    ((uint32_t)0x00000040)            /*!<GROUP2_IO3 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G2_IO4                    ((uint32_t)0x00000080)            /*!<GROUP2_IO4 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G3_IO1                    ((uint32_t)0x00000100)            /*!<GROUP3_IO1 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G3_IO2                    ((uint32_t)0x00000200)            /*!<GROUP3_IO2 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G3_IO3                    ((uint32_t)0x00000400)            /*!<GROUP3_IO3 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G3_IO4                    ((uint32_t)0x00000800)            /*!<GROUP3_IO4 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G4_IO1                    ((uint32_t)0x00001000)            /*!<GROUP4_IO1 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G4_IO2                    ((uint32_t)0x00002000)            /*!<GROUP4_IO2 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G4_IO3                    ((uint32_t)0x00004000)            /*!<GROUP4_IO3 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G4_IO4                    ((uint32_t)0x00008000)            /*!<GROUP4_IO4 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G5_IO1                    ((uint32_t)0x00010000)            /*!<GROUP5_IO1 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G5_IO2                    ((uint32_t)0x00020000)            /*!<GROUP5_IO2 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G5_IO3                    ((uint32_t)0x00040000)            /*!<GROUP5_IO3 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G5_IO4                    ((uint32_t)0x00080000)            /*!<GROUP5_IO4 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G6_IO1                    ((uint32_t)0x00100000)            /*!<GROUP6_IO1 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G6_IO2                    ((uint32_t)0x00200000)            /*!<GROUP6_IO2 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G6_IO3                    ((uint32_t)0x00400000)            /*!<GROUP6_IO3 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G6_IO4                    ((uint32_t)0x00800000)            /*!<GROUP6_IO4 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G7_IO1                    ((uint32_t)0x01000000)            /*!<GROUP7_IO1 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G7_IO2                    ((uint32_t)0x02000000)            /*!<GROUP7_IO2 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G7_IO3                    ((uint32_t)0x04000000)            /*!<GROUP7_IO3 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G7_IO4                    ((uint32_t)0x08000000)            /*!<GROUP7_IO4 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G8_IO1                    ((uint32_t)0x10000000)            /*!<GROUP8_IO1 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G8_IO2                    ((uint32_t)0x20000000)            /*!<GROUP8_IO2 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G8_IO3                    ((uint32_t)0x40000000)            /*!<GROUP8_IO3 schmitt trigger hysteresis mode */
#define TSC_IOHCR_G8_IO4                    ((uint32_t)0x80000000)            /*!<GROUP8_IO4 schmitt trigger hysteresis mode */

/*******************  Bit definition for TSC_IOASCR register  *****************/
#define TSC_IOASCR_G1_IO1                   ((uint32_t)0x00000001)            /*!<GROUP1_IO1 analog switch enable */
#define TSC_IOASCR_G1_IO2                   ((uint32_t)0x00000002)            /*!<GROUP1_IO2 analog switch enable */
#define TSC_IOASCR_G1_IO3                   ((uint32_t)0x00000004)            /*!<GROUP1_IO3 analog switch enable */
#define TSC_IOASCR_G1_IO4                   ((uint32_t)0x00000008)            /*!<GROUP1_IO4 analog switch enable */
#define TSC_IOASCR_G2_IO1                   ((uint32_t)0x00000010)            /*!<GROUP2_IO1 analog switch enable */
#define TSC_IOASCR_G2_IO2                   ((uint32_t)0x00000020)            /*!<GROUP2_IO2 analog switch enable */
#define TSC_IOASCR_G2_IO3                   ((uint32_t)0x00000040)            /*!<GROUP2_IO3 analog switch enable */
#define TSC_IOASCR_G2_IO4                   ((uint32_t)0x00000080)            /*!<GROUP2_IO4 analog switch enable */
#define TSC_IOASCR_G3_IO1                   ((uint32_t)0x00000100)            /*!<GROUP3_IO1 analog switch enable */
#define TSC_IOASCR_G3_IO2                   ((uint32_t)0x00000200)            /*!<GROUP3_IO2 analog switch enable */
#define TSC_IOASCR_G3_IO3                   ((uint32_t)0x00000400)            /*!<GROUP3_IO3 analog switch enable */
#define TSC_IOASCR_G3_IO4                   ((uint32_t)0x00000800)            /*!<GROUP3_IO4 analog switch enable */
#define TSC_IOASCR_G4_IO1                   ((uint32_t)0x00001000)            /*!<GROUP4_IO1 analog switch enable */
#define TSC_IOASCR_G4_IO2                   ((uint32_t)0x00002000)            /*!<GROUP4_IO2 analog switch enable */
#define TSC_IOASCR_G4_IO3                   ((uint32_t)0x00004000)            /*!<GROUP4_IO3 analog switch enable */
#define TSC_IOASCR_G4_IO4                   ((uint32_t)0x00008000)            /*!<GROUP4_IO4 analog switch enable */
#define TSC_IOASCR_G5_IO1                   ((uint32_t)0x00010000)            /*!<GROUP5_IO1 analog switch enable */
#define TSC_IOASCR_G5_IO2                   ((uint32_t)0x00020000)            /*!<GROUP5_IO2 analog switch enable */
#define TSC_IOASCR_G5_IO3                   ((uint32_t)0x00040000)            /*!<GROUP5_IO3 analog switch enable */
#define TSC_IOASCR_G5_IO4                   ((uint32_t)0x00080000)            /*!<GROUP5_IO4 analog switch enable */
#define TSC_IOASCR_G6_IO1                   ((uint32_t)0x00100000)            /*!<GROUP6_IO1 analog switch enable */
#define TSC_IOASCR_G6_IO2                   ((uint32_t)0x00200000)            /*!<GROUP6_IO2 analog switch enable */
#define TSC_IOASCR_G6_IO3                   ((uint32_t)0x00400000)            /*!<GROUP6_IO3 analog switch enable */
#define TSC_IOASCR_G6_IO4                   ((uint32_t)0x00800000)            /*!<GROUP6_IO4 analog switch enable */
#define TSC_IOASCR_G7_IO1                   ((uint32_t)0x01000000)            /*!<GROUP7_IO1 analog switch enable */
#define TSC_IOASCR_G7_IO2                   ((uint32_t)0x02000000)            /*!<GROUP7_IO2 analog switch enable */
#define TSC_IOASCR_G7_IO3                   ((uint32_t)0x04000000)            /*!<GROUP7_IO3 analog switch enable */
#define TSC_IOASCR_G7_IO4                   ((uint32_t)0x08000000)            /*!<GROUP7_IO4 analog switch enable */
#define TSC_IOASCR_G8_IO1                   ((uint32_t)0x10000000)            /*!<GROUP8_IO1 analog switch enable */
#define TSC_IOASCR_G8_IO2                   ((uint32_t)0x20000000)            /*!<GROUP8_IO2 analog switch enable */
#define TSC_IOASCR_G8_IO3                   ((uint32_t)0x40000000)            /*!<GROUP8_IO3 analog switch enable */
#define TSC_IOASCR_G8_IO4                   ((uint32_t)0x80000000)            /*!<GROUP8_IO4 analog switch enable */

/*******************  Bit definition for TSC_IOSCR register  ******************/
#define TSC_IOSCR_G1_IO1                    ((uint32_t)0x00000001)            /*!<GROUP1_IO1 sampling mode */
#define TSC_IOSCR_G1_IO2                    ((uint32_t)0x00000002)            /*!<GROUP1_IO2 sampling mode */
#define TSC_IOSCR_G1_IO3                    ((uint32_t)0x00000004)            /*!<GROUP1_IO3 sampling mode */
#define TSC_IOSCR_G1_IO4                    ((uint32_t)0x00000008)            /*!<GROUP1_IO4 sampling mode */
#define TSC_IOSCR_G2_IO1                    ((uint32_t)0x00000010)            /*!<GROUP2_IO1 sampling mode */
#define TSC_IOSCR_G2_IO2                    ((uint32_t)0x00000020)            /*!<GROUP2_IO2 sampling mode */
#define TSC_IOSCR_G2_IO3                    ((uint32_t)0x00000040)            /*!<GROUP2_IO3 sampling mode */
#define TSC_IOSCR_G2_IO4                    ((uint32_t)0x00000080)            /*!<GROUP2_IO4 sampling mode */
#define TSC_IOSCR_G3_IO1                    ((uint32_t)0x00000100)            /*!<GROUP3_IO1 sampling mode */
#define TSC_IOSCR_G3_IO2                    ((uint32_t)0x00000200)            /*!<GROUP3_IO2 sampling mode */
#define TSC_IOSCR_G3_IO3                    ((uint32_t)0x00000400)            /*!<GROUP3_IO3 sampling mode */
#define TSC_IOSCR_G3_IO4                    ((uint32_t)0x00000800)            /*!<GROUP3_IO4 sampling mode */
#define TSC_IOSCR_G4_IO1                    ((uint32_t)0x00001000)            /*!<GROUP4_IO1 sampling mode */
#define TSC_IOSCR_G4_IO2                    ((uint32_t)0x00002000)            /*!<GROUP4_IO2 sampling mode */
#define TSC_IOSCR_G4_IO3                    ((uint32_t)0x00004000)            /*!<GROUP4_IO3 sampling mode */
#define TSC_IOSCR_G4_IO4                    ((uint32_t)0x00008000)            /*!<GROUP4_IO4 sampling mode */
#define TSC_IOSCR_G5_IO1                    ((uint32_t)0x00010000)            /*!<GROUP5_IO1 sampling mode */
#define TSC_IOSCR_G5_IO2                    ((uint32_t)0x00020000)            /*!<GROUP5_IO2 sampling mode */
#define TSC_IOSCR_G5_IO3                    ((uint32_t)0x00040000)            /*!<GROUP5_IO3 sampling mode */
#define TSC_IOSCR_G5_IO4                    ((uint32_t)0x00080000)            /*!<GROUP5_IO4 sampling mode */
#define TSC_IOSCR_G6_IO1                    ((uint32_t)0x00100000)            /*!<GROUP6_IO1 sampling mode */
#define TSC_IOSCR_G6_IO2                    ((uint32_t)0x00200000)            /*!<GROUP6_IO2 sampling mode */
#define TSC_IOSCR_G6_IO3                    ((uint32_t)0x00400000)            /*!<GROUP6_IO3 sampling mode */
#define TSC_IOSCR_G6_IO4                    ((uint32_t)0x00800000)            /*!<GROUP6_IO4 sampling mode */
#define TSC_IOSCR_G7_IO1                    ((uint32_t)0x01000000)            /*!<GROUP7_IO1 sampling mode */
#define TSC_IOSCR_G7_IO2                    ((uint32_t)0x02000000)            /*!<GROUP7_IO2 sampling mode */
#define TSC_IOSCR_G7_IO3                    ((uint32_t)0x04000000)            /*!<GROUP7_IO3 sampling mode */
#define TSC_IOSCR_G7_IO4                    ((uint32_t)0x08000000)            /*!<GROUP7_IO4 sampling mode */
#define TSC_IOSCR_G8_IO1                    ((uint32_t)0x10000000)            /*!<GROUP8_IO1 sampling mode */
#define TSC_IOSCR_G8_IO2                    ((uint32_t)0x20000000)            /*!<GROUP8_IO2 sampling mode */
#define TSC_IOSCR_G8_IO3                    ((uint32_t)0x40000000)            /*!<GROUP8_IO3 sampling mode */
#define TSC_IOSCR_G8_IO4                    ((uint32_t)0x80000000)            /*!<GROUP8_IO4 sampling mode */

/*******************  Bit definition for TSC_IOCCR register  ******************/
#define TSC_IOCCR_G1_IO1                    ((uint32_t)0x00000001)            /*!<GROUP1_IO1 channel mode */
#define TSC_IOCCR_G1_IO2                    ((uint32_t)0x00000002)            /*!<GROUP1_IO2 channel mode */
#define TSC_IOCCR_G1_IO3                    ((uint32_t)0x00000004)            /*!<GROUP1_IO3 channel mode */
#define TSC_IOCCR_G1_IO4                    ((uint32_t)0x00000008)            /*!<GROUP1_IO4 channel mode */
#define TSC_IOCCR_G2_IO1                    ((uint32_t)0x00000010)            /*!<GROUP2_IO1 channel mode */
#define TSC_IOCCR_G2_IO2                    ((uint32_t)0x00000020)            /*!<GROUP2_IO2 channel mode */
#define TSC_IOCCR_G2_IO3                    ((uint32_t)0x00000040)            /*!<GROUP2_IO3 channel mode */
#define TSC_IOCCR_G2_IO4                    ((uint32_t)0x00000080)            /*!<GROUP2_IO4 channel mode */
#define TSC_IOCCR_G3_IO1                    ((uint32_t)0x00000100)            /*!<GROUP3_IO1 channel mode */
#define TSC_IOCCR_G3_IO2                    ((uint32_t)0x00000200)            /*!<GROUP3_IO2 channel mode */
#define TSC_IOCCR_G3_IO3                    ((uint32_t)0x00000400)            /*!<GROUP3_IO3 channel mode */
#define TSC_IOCCR_G3_IO4                    ((uint32_t)0x00000800)            /*!<GROUP3_IO4 channel mode */
#define TSC_IOCCR_G4_IO1                    ((uint32_t)0x00001000)            /*!<GROUP4_IO1 channel mode */
#define TSC_IOCCR_G4_IO2                    ((uint32_t)0x00002000)            /*!<GROUP4_IO2 channel mode */
#define TSC_IOCCR_G4_IO3                    ((uint32_t)0x00004000)            /*!<GROUP4_IO3 channel mode */
#define TSC_IOCCR_G4_IO4                    ((uint32_t)0x00008000)            /*!<GROUP4_IO4 channel mode */
#define TSC_IOCCR_G5_IO1                    ((uint32_t)0x00010000)            /*!<GROUP5_IO1 channel mode */
#define TSC_IOCCR_G5_IO2                    ((uint32_t)0x00020000)            /*!<GROUP5_IO2 channel mode */
#define TSC_IOCCR_G5_IO3                    ((uint32_t)0x00040000)            /*!<GROUP5_IO3 channel mode */
#define TSC_IOCCR_G5_IO4                    ((uint32_t)0x00080000)            /*!<GROUP5_IO4 channel mode */
#define TSC_IOCCR_G6_IO1                    ((uint32_t)0x00100000)            /*!<GROUP6_IO1 channel mode */
#define TSC_IOCCR_G6_IO2                    ((uint32_t)0x00200000)            /*!<GROUP6_IO2 channel mode */
#define TSC_IOCCR_G6_IO3                    ((uint32_t)0x00400000)            /*!<GROUP6_IO3 channel mode */
#define TSC_IOCCR_G6_IO4                    ((uint32_t)0x00800000)            /*!<GROUP6_IO4 channel mode */
#define TSC_IOCCR_G7_IO1                    ((uint32_t)0x01000000)            /*!<GROUP7_IO1 channel mode */
#define TSC_IOCCR_G7_IO2                    ((uint32_t)0x02000000)            /*!<GROUP7_IO2 channel mode */
#define TSC_IOCCR_G7_IO3                    ((uint32_t)0x04000000)            /*!<GROUP7_IO3 channel mode */
#define TSC_IOCCR_G7_IO4                    ((uint32_t)0x08000000)            /*!<GROUP7_IO4 channel mode */
#define TSC_IOCCR_G8_IO1                    ((uint32_t)0x10000000)            /*!<GROUP8_IO1 channel mode */
#define TSC_IOCCR_G8_IO2                    ((uint32_t)0x20000000)            /*!<GROUP8_IO2 channel mode */
#define TSC_IOCCR_G8_IO3                    ((uint32_t)0x40000000)            /*!<GROUP8_IO3 channel mode */
#define TSC_IOCCR_G8_IO4                    ((uint32_t)0x80000000)            /*!<GROUP8_IO4 channel mode */

/*******************  Bit definition for TSC_IOGCSR register  *****************/
#define TSC_IOGCSR_G1E                      ((uint32_t)0x00000001)            /*!<Analog IO GROUP1 enable */
#define TSC_IOGCSR_G2E                      ((uint32_t)0x00000002)            /*!<Analog IO GROUP2 enable */
#define TSC_IOGCSR_G3E                      ((uint32_t)0x00000004)            /*!<Analog IO GROUP3 enable */
#define TSC_IOGCSR_G4E                      ((uint32_t)0x00000008)            /*!<Analog IO GROUP4 enable */
#define TSC_IOGCSR_G5E                      ((uint32_t)0x00000010)            /*!<Analog IO GROUP5 enable */
#define TSC_IOGCSR_G6E                      ((uint32_t)0x00000020)            /*!<Analog IO GROUP6 enable */
#define TSC_IOGCSR_G7E                      ((uint32_t)0x00000040)            /*!<Analog IO GROUP7 enable */
#define TSC_IOGCSR_G8E                      ((uint32_t)0x00000080)            /*!<Analog IO GROUP8 enable */
#define TSC_IOGCSR_G1S                      ((uint32_t)0x00010000)            /*!<Analog IO GROUP1 status */
#define TSC_IOGCSR_G2S                      ((uint32_t)0x00020000)            /*!<Analog IO GROUP2 status */
#define TSC_IOGCSR_G3S                      ((uint32_t)0x00040000)            /*!<Analog IO GROUP3 status */
#define TSC_IOGCSR_G4S                      ((uint32_t)0x00080000)            /*!<Analog IO GROUP4 status */
#define TSC_IOGCSR_G5S                      ((uint32_t)0x00100000)            /*!<Analog IO GROUP5 status */
#define TSC_IOGCSR_G6S                      ((uint32_t)0x00200000)            /*!<Analog IO GROUP6 status */
#define TSC_IOGCSR_G7S                      ((uint32_t)0x00400000)            /*!<Analog IO GROUP7 status */
#define TSC_IOGCSR_G8S                      ((uint32_t)0x00800000)            /*!<Analog IO GROUP8 status */

/*******************  Bit definition for TSC_IOGXCR register  *****************/
#define TSC_IOGXCR_CNT                      ((uint32_t)0x00003FFF)            /*!<CNT[13:0] bits (Counter value) */

/******************************************************************************/
/*                                                                            */
/*      Universal Synchronous Asynchronous Receiver Transmitter (USART)       */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for USART_CR1 register  *******************/
#define USART_CR1_UE                        ((uint32_t)0x00000001)            /*!< USART Enable */
#define USART_CR1_UESM                      ((uint32_t)0x00000002)            /*!< USART Enable in STOP Mode */
#define USART_CR1_RE                        ((uint32_t)0x00000004)            /*!< Receiver Enable */
#define USART_CR1_TE                        ((uint32_t)0x00000008)            /*!< Transmitter Enable */
#define USART_CR1_IDLEIE                    ((uint32_t)0x00000010)            /*!< IDLE Interrupt Enable */
#define USART_CR1_RXNEIE                    ((uint32_t)0x00000020)            /*!< RXNE Interrupt Enable */
#define USART_CR1_TCIE                      ((uint32_t)0x00000040)            /*!< Transmission Complete Interrupt Enable */
#define USART_CR1_TXEIE                     ((uint32_t)0x00000080)            /*!< TXE Interrupt Enable */
#define USART_CR1_PEIE                      ((uint32_t)0x00000100)            /*!< PE Interrupt Enable */
#define USART_CR1_PS                        ((uint32_t)0x00000200)            /*!< Parity Selection */
#define USART_CR1_PCE                       ((uint32_t)0x00000400)            /*!< Parity Control Enable */
#define USART_CR1_WAKE                      ((uint32_t)0x00000800)            /*!< Receiver Wakeup method */
#define USART_CR1_M                         ((uint32_t)0x10001000)            /*!< Word length */
#define USART_CR1_M_0                       ((uint32_t)0x00001000)            /*!< Word length - Bit 0 */
#define USART_CR1_MME                       ((uint32_t)0x00002000)            /*!< Mute Mode Enable */
#define USART_CR1_CMIE                      ((uint32_t)0x00004000)            /*!< Character match interrupt enable */
#define USART_CR1_OVER8                     ((uint32_t)0x00008000)            /*!< Oversampling by 8-bit or 16-bit mode */
#define USART_CR1_DEDT                      ((uint32_t)0x001F0000)            /*!< DEDT[4:0] bits (Driver Enable Deassertion Time) */
#define USART_CR1_DEDT_0                    ((uint32_t)0x00010000)            /*!< Bit 0 */
#define USART_CR1_DEDT_1                    ((uint32_t)0x00020000)            /*!< Bit 1 */
#define USART_CR1_DEDT_2                    ((uint32_t)0x00040000)            /*!< Bit 2 */
#define USART_CR1_DEDT_3                    ((uint32_t)0x00080000)            /*!< Bit 3 */
#define USART_CR1_DEDT_4                    ((uint32_t)0x00100000)            /*!< Bit 4 */
#define USART_CR1_DEAT                      ((uint32_t)0x03E00000)            /*!< DEAT[4:0] bits (Driver Enable Assertion Time) */
#define USART_CR1_DEAT_0                    ((uint32_t)0x00200000)            /*!< Bit 0 */
#define USART_CR1_DEAT_1                    ((uint32_t)0x00400000)            /*!< Bit 1 */
#define USART_CR1_DEAT_2                    ((uint32_t)0x00800000)            /*!< Bit 2 */
#define USART_CR1_DEAT_3                    ((uint32_t)0x01000000)            /*!< Bit 3 */
#define USART_CR1_DEAT_4                    ((uint32_t)0x02000000)            /*!< Bit 4 */
#define USART_CR1_RTOIE                     ((uint32_t)0x04000000)            /*!< Receive Time Out interrupt enable */
#define USART_CR1_EOBIE                     ((uint32_t)0x08000000)            /*!< End of Block interrupt enable */
#define USART_CR1_M_1                       ((uint32_t)0x10000000)            /*!< Word length - Bit 1 */
/******************  Bit definition for USART_CR2 register  *******************/
#define USART_CR2_ADDM7                     ((uint32_t)0x00000010)            /*!< 7-bit or 4-bit Address Detection */
#define USART_CR2_LBDL                      ((uint32_t)0x00000020)            /*!< LIN Break Detection Length */
#define USART_CR2_LBDIE                     ((uint32_t)0x00000040)            /*!< LIN Break Detection Interrupt Enable */
#define USART_CR2_LBCL                      ((uint32_t)0x00000100)            /*!< Last Bit Clock pulse */
#define USART_CR2_CPHA                      ((uint32_t)0x00000200)            /*!< Clock Phase */
#define USART_CR2_CPOL                      ((uint32_t)0x00000400)            /*!< Clock Polarity */
#define USART_CR2_CLKEN                     ((uint32_t)0x00000800)            /*!< Clock Enable */
#define USART_CR2_STOP                      ((uint32_t)0x00003000)            /*!< STOP[1:0] bits (STOP bits) */
#define USART_CR2_STOP_0                    ((uint32_t)0x00001000)            /*!< Bit 0 */
#define USART_CR2_STOP_1                    ((uint32_t)0x00002000)            /*!< Bit 1 */
#define USART_CR2_LINEN                     ((uint32_t)0x00004000)            /*!< LIN mode enable */
#define USART_CR2_SWAP                      ((uint32_t)0x00008000)            /*!< SWAP TX/RX pins */
#define USART_CR2_RXINV                     ((uint32_t)0x00010000)            /*!< RX pin active level inversion */
#define USART_CR2_TXINV                     ((uint32_t)0x00020000)            /*!< TX pin active level inversion */
#define USART_CR2_DATAINV                   ((uint32_t)0x00040000)            /*!< Binary data inversion */
#define USART_CR2_MSBFIRST                  ((uint32_t)0x00080000)            /*!< Most Significant Bit First */
#define USART_CR2_ABREN                     ((uint32_t)0x00100000)            /*!< Auto Baud-Rate Enable*/
#define USART_CR2_ABRMODE                   ((uint32_t)0x00600000)            /*!< ABRMOD[1:0] bits (Auto Baud-Rate Mode) */
#define USART_CR2_ABRMODE_0                 ((uint32_t)0x00200000)            /*!< Bit 0 */
#define USART_CR2_ABRMODE_1                 ((uint32_t)0x00400000)            /*!< Bit 1 */
#define USART_CR2_RTOEN                     ((uint32_t)0x00800000)            /*!< Receiver Time-Out enable */
#define USART_CR2_ADD                       ((uint32_t)0xFF000000)            /*!< Address of the USART node */

/******************  Bit definition for USART_CR3 register  *******************/
#define USART_CR3_EIE                       ((uint32_t)0x00000001)            /*!< Error Interrupt Enable */
#define USART_CR3_IREN                      ((uint32_t)0x00000002)            /*!< IrDA mode Enable */
#define USART_CR3_IRLP                      ((uint32_t)0x00000004)            /*!< IrDA Low-Power */
#define USART_CR3_HDSEL                     ((uint32_t)0x00000008)            /*!< Half-Duplex Selection */
#define USART_CR3_NACK                      ((uint32_t)0x00000010)            /*!< SmartCard NACK enable */
#define USART_CR3_SCEN                      ((uint32_t)0x00000020)            /*!< SmartCard mode enable */
#define USART_CR3_DMAR                      ((uint32_t)0x00000040)            /*!< DMA Enable Receiver */
#define USART_CR3_DMAT                      ((uint32_t)0x00000080)            /*!< DMA Enable Transmitter */
#define USART_CR3_RTSE                      ((uint32_t)0x00000100)            /*!< RTS Enable */
#define USART_CR3_CTSE                      ((uint32_t)0x00000200)            /*!< CTS Enable */
#define USART_CR3_CTSIE                     ((uint32_t)0x00000400)            /*!< CTS Interrupt Enable */
#define USART_CR3_ONEBIT                    ((uint32_t)0x00000800)            /*!< One sample bit method enable */
#define USART_CR3_OVRDIS                    ((uint32_t)0x00001000)            /*!< Overrun Disable */
#define USART_CR3_DDRE                      ((uint32_t)0x00002000)            /*!< DMA Disable on Reception Error */
#define USART_CR3_DEM                       ((uint32_t)0x00004000)            /*!< Driver Enable Mode */
#define USART_CR3_DEP                       ((uint32_t)0x00008000)            /*!< Driver Enable Polarity Selection */
#define USART_CR3_SCARCNT                   ((uint32_t)0x000E0000)            /*!< SCARCNT[2:0] bits (SmartCard Auto-Retry Count) */
#define USART_CR3_SCARCNT_0                 ((uint32_t)0x00020000)            /*!< Bit 0 */
#define USART_CR3_SCARCNT_1                 ((uint32_t)0x00040000)            /*!< Bit 1 */
#define USART_CR3_SCARCNT_2                 ((uint32_t)0x00080000)            /*!< Bit 2 */
#define USART_CR3_WUS                       ((uint32_t)0x00300000)            /*!< WUS[1:0] bits (Wake UP Interrupt Flag Selection) */
#define USART_CR3_WUS_0                     ((uint32_t)0x00100000)            /*!< Bit 0 */
#define USART_CR3_WUS_1                     ((uint32_t)0x00200000)            /*!< Bit 1 */
#define USART_CR3_WUFIE                     ((uint32_t)0x00400000)            /*!< Wake Up Interrupt Enable */
#define USART_CR3_UCESM                     ((uint32_t)0x00800000)            /*!< Clock Enable in Stop mode */ 

/******************  Bit definition for USART_BRR register  *******************/
#define USART_BRR_DIV_FRACTION              ((uint32_t)0x0000000F)            /*!< Fraction of USARTDIV */
#define USART_BRR_DIV_MANTISSA              ((uint32_t)0x0000FFF0)            /*!< Mantissa of USARTDIV */

/******************  Bit definition for USART_GTPR register  ******************/
#define USART_GTPR_PSC                      ((uint32_t)0x000000FF)            /*!< PSC[7:0] bits (Prescaler value) */
#define USART_GTPR_GT                       ((uint32_t)0x0000FF00)            /*!< GT[7:0] bits (Guard time value) */


/*******************  Bit definition for USART_RTOR register  *****************/
#define USART_RTOR_RTO                      ((uint32_t)0x00FFFFFF)            /*!< Receiver Time Out Value */
#define USART_RTOR_BLEN                     ((uint32_t)0xFF000000)            /*!< Block Length */

/*******************  Bit definition for USART_RQR register  ******************/
#define USART_RQR_ABRRQ                     ((uint32_t)0x00000001)            /*!< Auto-Baud Rate Request */
#define USART_RQR_SBKRQ                     ((uint32_t)0x00000002)            /*!< Send Break Request */
#define USART_RQR_MMRQ                      ((uint32_t)0x00000004)            /*!< Mute Mode Request */
#define USART_RQR_RXFRQ                     ((uint32_t)0x00000008)            /*!< Receive Data flush Request */
#define USART_RQR_TXFRQ                     ((uint32_t)0x00000010)            /*!< Transmit data flush Request */

/*******************  Bit definition for USART_ISR register  ******************/
#define USART_ISR_PE                        ((uint32_t)0x00000001)            /*!< Parity Error */
#define USART_ISR_FE                        ((uint32_t)0x00000002)            /*!< Framing Error */
#define USART_ISR_NE                        ((uint32_t)0x00000004)            /*!< Noise detected Flag */
#define USART_ISR_ORE                       ((uint32_t)0x00000008)            /*!< OverRun Error */
#define USART_ISR_IDLE                      ((uint32_t)0x00000010)            /*!< IDLE line detected */
#define USART_ISR_RXNE                      ((uint32_t)0x00000020)            /*!< Read Data Register Not Empty */
#define USART_ISR_TC                        ((uint32_t)0x00000040)            /*!< Transmission Complete */
#define USART_ISR_TXE                       ((uint32_t)0x00000080)            /*!< Transmit Data Register Empty */
#define USART_ISR_LBD                       ((uint32_t)0x00000100)            /*!< LIN Break Detection Flag */
#define USART_ISR_CTSIF                     ((uint32_t)0x00000200)            /*!< CTS interrupt flag */
#define USART_ISR_CTS                       ((uint32_t)0x00000400)            /*!< CTS flag */
#define USART_ISR_RTOF                      ((uint32_t)0x00000800)            /*!< Receiver Time Out */
#define USART_ISR_EOBF                      ((uint32_t)0x00001000)            /*!< End Of Block Flag */
#define USART_ISR_ABRE                      ((uint32_t)0x00004000)            /*!< Auto-Baud Rate Error */
#define USART_ISR_ABRF                      ((uint32_t)0x00008000)            /*!< Auto-Baud Rate Flag */
#define USART_ISR_BUSY                      ((uint32_t)0x00010000)            /*!< Busy Flag */
#define USART_ISR_CMF                       ((uint32_t)0x00020000)            /*!< Character Match Flag */
#define USART_ISR_SBKF                      ((uint32_t)0x00040000)            /*!< Send Break Flag */
#define USART_ISR_RWU                       ((uint32_t)0x00080000)            /*!< Receive Wake Up from mute mode Flag */
#define USART_ISR_WUF                       ((uint32_t)0x00100000)            /*!< Wake Up from stop mode Flag */
#define USART_ISR_TEACK                     ((uint32_t)0x00200000)            /*!< Transmit Enable Acknowledge Flag */
#define USART_ISR_REACK                     ((uint32_t)0x00400000)            /*!< Receive Enable Acknowledge Flag */

/*******************  Bit definition for USART_ICR register  ******************/
#define USART_ICR_PECF                      ((uint32_t)0x00000001)            /*!< Parity Error Clear Flag */
#define USART_ICR_FECF                      ((uint32_t)0x00000002)            /*!< Framing Error Clear Flag */
#define USART_ICR_NCF                       ((uint32_t)0x00000004)            /*!< Noise detected Clear Flag */
#define USART_ICR_ORECF                     ((uint32_t)0x00000008)            /*!< OverRun Error Clear Flag */
#define USART_ICR_IDLECF                    ((uint32_t)0x00000010)            /*!< IDLE line detected Clear Flag */
#define USART_ICR_TCCF                      ((uint32_t)0x00000040)            /*!< Transmission Complete Clear Flag */
#define USART_ICR_LBDCF                     ((uint32_t)0x00000100)            /*!< LIN Break Detection Clear Flag */
#define USART_ICR_CTSCF                     ((uint32_t)0x00000200)            /*!< CTS Interrupt Clear Flag */
#define USART_ICR_RTOCF                     ((uint32_t)0x00000800)            /*!< Receiver Time Out Clear Flag */
#define USART_ICR_EOBCF                     ((uint32_t)0x00001000)            /*!< End Of Block Clear Flag */
#define USART_ICR_CMCF                      ((uint32_t)0x00020000)            /*!< Character Match Clear Flag */
#define USART_ICR_WUCF                      ((uint32_t)0x00100000)            /*!< Wake Up from stop mode Clear Flag */

/*******************  Bit definition for USART_RDR register  ******************/
#define USART_RDR_RDR                       ((uint32_t)0x000001FF)            /*!< RDR[8:0] bits (Receive Data value) */

/*******************  Bit definition for USART_TDR register  ******************/
#define USART_TDR_TDR                       ((uint32_t)0x000001FF)            /*!< TDR[8:0] bits (Transmit Data value) */

/******************************************************************************/
/*                                                                            */
/*                         USB Device General registers                       */
/*                                                                            */
/******************************************************************************/
#define USB_BASE                             ((uint32_t)0x40005C00)      /*!< USB_IP Peripheral Registers base address */
#define USB_PMAADDR                          ((uint32_t)0x40006000)      /*!< USB_IP Packet Memory Area base address */
                                             
#define USB_CNTR                             (USB_BASE + 0x40)           /*!< Control register */
#define USB_ISTR                             (USB_BASE + 0x44)           /*!< Interrupt status register */
#define USB_FNR                              (USB_BASE + 0x48)           /*!< Frame number register */
#define USB_DADDR                            (USB_BASE + 0x4C)           /*!< Device address register */
#define USB_BTABLE                           (USB_BASE + 0x50)           /*!< Buffer Table address register */
#define USB_LPMCSR                           (USB_BASE + 0x54)           /*!< LPM Control and Status register */
#define USB_BCDR                             (USB_BASE + 0x58)           /*!< Battery Charging detector register*/

/****************************  ISTR interrupt events  *************************/
#define USB_ISTR_CTR                         ((uint16_t)0x8000)          /*!< Correct TRansfer (clear-only bit) */
#define USB_ISTR_PMAOVR                      ((uint16_t)0x4000)          /*!< DMA OVeR/underrun (clear-only bit) */
#define USB_ISTR_ERR                         ((uint16_t)0x2000)          /*!< ERRor (clear-only bit) */
#define USB_ISTR_WKUP                        ((uint16_t)0x1000)          /*!< WaKe UP (clear-only bit) */
#define USB_ISTR_SUSP                        ((uint16_t)0x0800)          /*!< SUSPend (clear-only bit) */
#define USB_ISTR_RESET                       ((uint16_t)0x0400)          /*!< RESET (clear-only bit) */
#define USB_ISTR_SOF                         ((uint16_t)0x0200)          /*!< Start Of Frame (clear-only bit) */
#define USB_ISTR_ESOF                        ((uint16_t)0x0100)          /*!< Expected Start Of Frame (clear-only bit) */
#define USB_ISTR_L1REQ                       ((uint16_t)0x0080)          /*!< LPM L1 state request  */
#define USB_ISTR_DIR                         ((uint16_t)0x0010)          /*!< DIRection of transaction (read-only bit)  */
#define USB_ISTR_EP_ID                       ((uint16_t)0x000F)          /*!< EndPoint IDentifier (read-only bit)  */

#define USB_CLR_CTR                          (~USB_ISTR_CTR)             /*!< clear Correct TRansfer bit */
#define USB_CLR_PMAOVR                       (~USB_ISTR_PMAOVR)          /*!< clear DMA OVeR/underrun bit*/
#define USB_CLR_ERR                          (~USB_ISTR_ERR)             /*!< clear ERRor bit */
#define USB_CLR_WKUP                         (~USB_ISTR_WKUP)            /*!< clear WaKe UP bit */
#define USB_CLR_SUSP                         (~USB_ISTR_SUSP)            /*!< clear SUSPend bit */
#define USB_CLR_RESET                        (~USB_ISTR_RESET)           /*!< clear RESET bit */
#define USB_CLR_SOF                          (~USB_ISTR_SOF)             /*!< clear Start Of Frame bit */
#define USB_CLR_ESOF                         (~USB_ISTR_ESOF)            /*!< clear Expected Start Of Frame bit */
#define USB_CLR_L1REQ                        (~USB_ISTR_L1REQ)           /*!< clear LPM L1  bit */
/*************************  CNTR control register bits definitions  ***********/
#define USB_CNTR_CTRM                        ((uint16_t)0x8000)          /*!< Correct TRansfer Mask */
#define USB_CNTR_PMAOVRM                     ((uint16_t)0x4000)          /*!< DMA OVeR/underrun Mask */
#define USB_CNTR_ERRM                        ((uint16_t)0x2000)          /*!< ERRor Mask */
#define USB_CNTR_WKUPM                       ((uint16_t)0x1000)          /*!< WaKe UP Mask */
#define USB_CNTR_SUSPM                       ((uint16_t)0x0800)          /*!< SUSPend Mask */
#define USB_CNTR_RESETM                      ((uint16_t)0x0400)          /*!< RESET Mask   */
#define USB_CNTR_SOFM                        ((uint16_t)0x0200)          /*!< Start Of Frame Mask */
#define USB_CNTR_ESOFM                       ((uint16_t)0x0100)          /*!< Expected Start Of Frame Mask */
#define USB_CNTR_L1REQM                      ((uint16_t)0x0080)          /*!< LPM L1 state request interrupt mask */
#define USB_CNTR_L1RESUME                    ((uint16_t)0x0020)          /*!< LPM L1 Resume request */
#define USB_CNTR_RESUME                      ((uint16_t)0x0010)          /*!< RESUME request */
#define USB_CNTR_FSUSP                       ((uint16_t)0x0008)          /*!< Force SUSPend */
#define USB_CNTR_LPMODE                      ((uint16_t)0x0004)          /*!< Low-power MODE */
#define USB_CNTR_PDWN                        ((uint16_t)0x0002)          /*!< Power DoWN */
#define USB_CNTR_FRES                        ((uint16_t)0x0001)          /*!< Force USB RESet */
/*************************  BCDR control register bits definitions  ***********/
#define USB_BCDR_DPPU                        ((uint16_t)0x8000)          /*!< DP Pull-up Enable */  
#define USB_BCDR_PS2DET                      ((uint16_t)0x0080)          /*!< PS2 port or proprietary charger detected */  
#define USB_BCDR_SDET                        ((uint16_t)0x0040)          /*!< Secondary detection (SD) status */  
#define USB_BCDR_PDET                        ((uint16_t)0x0020)          /*!< Primary detection (PD) status */ 
#define USB_BCDR_DCDET                       ((uint16_t)0x0010)          /*!< Data contact detection (DCD) status */ 
#define USB_BCDR_SDEN                        ((uint16_t)0x0008)          /*!< Secondary detection (SD) mode enable */ 
#define USB_BCDR_PDEN                        ((uint16_t)0x0004)          /*!< Primary detection (PD) mode enable */  
#define USB_BCDR_DCDEN                       ((uint16_t)0x0002)          /*!< Data contact detection (DCD) mode enable */
#define USB_BCDR_BCDEN                       ((uint16_t)0x0001)          /*!< Battery charging detector (BCD) enable */
/***************************  LPM register bits definitions  ******************/
#define USB_LPMCSR_BESL                      ((uint16_t)0x00F0)          /*!< BESL value received with last ACKed LPM Token  */ 
#define USB_LPMCSR_REMWAKE                   ((uint16_t)0x0008)          /*!< bRemoteWake value received with last ACKed LPM Token */ 
#define USB_LPMCSR_LPMACK                    ((uint16_t)0x0002)          /*!< LPM Token acknowledge enable*/
#define USB_LPMCSR_LMPEN                     ((uint16_t)0x0001)          /*!< LPM support enable  */
/********************  FNR Frame Number Register bit definitions   ************/
#define USB_FNR_RXDP                         ((uint16_t)0x8000)          /*!< status of D+ data line */
#define USB_FNR_RXDM                         ((uint16_t)0x4000)          /*!< status of D- data line */
#define USB_FNR_LCK                          ((uint16_t)0x2000)          /*!< LoCKed */
#define USB_FNR_LSOF                         ((uint16_t)0x1800)          /*!< Lost SOF */
#define USB_FNR_FN                           ((uint16_t)0x07FF)          /*!< Frame Number */
/********************  DADDR Device ADDRess bit definitions    ****************/
#define USB_DADDR_EF                         ((uint8_t)0x80)             /*!< USB device address Enable Function */
#define USB_DADDR_ADD                        ((uint8_t)0x7F)             /*!< USB device address */
/******************************  Endpoint register    *************************/
#define USB_EP0R                              USB_BASE                   /*!< endpoint 0 register address */
#define USB_EP1R                             (USB_BASE + 0x04)           /*!< endpoint 1 register address */
#define USB_EP2R                             (USB_BASE + 0x08)           /*!< endpoint 2 register address */
#define USB_EP3R                             (USB_BASE + 0x0C)           /*!< endpoint 3 register address */
#define USB_EP4R                             (USB_BASE + 0x10)           /*!< endpoint 4 register address */
#define USB_EP5R                             (USB_BASE + 0x14)           /*!< endpoint 5 register address */
#define USB_EP6R                             (USB_BASE + 0x18)           /*!< endpoint 6 register address */
#define USB_EP7R                             (USB_BASE + 0x1C)           /*!< endpoint 7 register address */
/* bit positions */ 
#define USB_EP_CTR_RX                        ((uint16_t)0x8000)          /*!<  EndPoint Correct TRansfer RX */
#define USB_EP_DTOG_RX                       ((uint16_t)0x4000)          /*!<  EndPoint Data TOGGLE RX */
#define USB_EPRX_STAT                        ((uint16_t)0x3000)          /*!<  EndPoint RX STATus bit field */
#define USB_EP_SETUP                         ((uint16_t)0x0800)          /*!<  EndPoint SETUP */
#define USB_EP_T_FIELD                       ((uint16_t)0x0600)          /*!<  EndPoint TYPE */
#define USB_EP_KIND                          ((uint16_t)0x0100)          /*!<  EndPoint KIND */
#define USB_EP_CTR_TX                        ((uint16_t)0x0080)          /*!<  EndPoint Correct TRansfer TX */
#define USB_EP_DTOG_TX                       ((uint16_t)0x0040)          /*!<  EndPoint Data TOGGLE TX */
#define USB_EPTX_STAT                        ((uint16_t)0x0030)          /*!<  EndPoint TX STATus bit field */
#define USB_EPADDR_FIELD                     ((uint16_t)0x000F)          /*!<  EndPoint ADDRess FIELD */

/* EndPoint REGister MASK (no toggle fields) */
#define USB_EPREG_MASK     (USB_EP_CTR_RX|USB_EP_SETUP|USB_EP_T_FIELD|USB_EP_KIND|USB_EP_CTR_TX|USB_EPADDR_FIELD)
                                                                         /*!< EP_TYPE[1:0] EndPoint TYPE */
#define USB_EP_TYPE_MASK                     ((uint16_t)0x0600)          /*!< EndPoint TYPE Mask */
#define USB_EP_BULK                          ((uint16_t)0x0000)          /*!< EndPoint BULK */
#define USB_EP_CONTROL                       ((uint16_t)0x0200)          /*!< EndPoint CONTROL */
#define USB_EP_ISOCHRONOUS                   ((uint16_t)0x0400)          /*!< EndPoint ISOCHRONOUS */
#define USB_EP_INTERRUPT                     ((uint16_t)0x0600)          /*!< EndPoint INTERRUPT */
#define USB_EP_T_MASK      (~USB_EP_T_FIELD & USB_EPREG_MASK)
                                                                 
#define USB_EPKIND_MASK    (~USB_EP_KIND & USB_EPREG_MASK)               /*!< EP_KIND EndPoint KIND */
                                                                         /*!< STAT_TX[1:0] STATus for TX transfer */
#define USB_EP_TX_DIS                        ((uint16_t)0x0000)          /*!< EndPoint TX DISabled */
#define USB_EP_TX_STALL                      ((uint16_t)0x0010)          /*!< EndPoint TX STALLed */
#define USB_EP_TX_NAK                        ((uint16_t)0x0020)          /*!< EndPoint TX NAKed */
#define USB_EP_TX_VALID                      ((uint16_t)0x0030)          /*!< EndPoint TX VALID */
#define USB_EPTX_DTOG1                       ((uint16_t)0x0010)          /*!< EndPoint TX Data TOGgle bit1 */
#define USB_EPTX_DTOG2                       ((uint16_t)0x0020)          /*!< EndPoint TX Data TOGgle bit2 */
#define USB_EPTX_DTOGMASK  (USB_EPTX_STAT|USB_EPREG_MASK)
                                                                         /*!< STAT_RX[1:0] STATus for RX transfer */
#define USB_EP_RX_DIS                        ((uint16_t)0x0000)          /*!< EndPoint RX DISabled */
#define USB_EP_RX_STALL                      ((uint16_t)0x1000)          /*!< EndPoint RX STALLed */
#define USB_EP_RX_NAK                        ((uint16_t)0x2000)          /*!< EndPoint RX NAKed */
#define USB_EP_RX_VALID                      ((uint16_t)0x3000)          /*!< EndPoint RX VALID */
#define USB_EPRX_DTOG1                       ((uint16_t)0x1000)          /*!< EndPoint RX Data TOGgle bit1 */
#define USB_EPRX_DTOG2                       ((uint16_t)0x2000)          /*!< EndPoint RX Data TOGgle bit1 */
#define USB_EPRX_DTOGMASK  (USB_EPRX_STAT|USB_EPREG_MASK)

/******************************************************************************/
/*                                                                            */
/*                         Window WATCHDOG (WWDG)                             */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for WWDG_CR register  ********************/
#define WWDG_CR_T                           ((uint32_t)0x0000007F)      /*!< T[6:0] bits (7-Bit counter (MSB to LSB)) */
#define WWDG_CR_T0                          ((uint32_t)0x00000001)      /*!< Bit 0 */
#define WWDG_CR_T1                          ((uint32_t)0x00000002)      /*!< Bit 1 */
#define WWDG_CR_T2                          ((uint32_t)0x00000004)      /*!< Bit 2 */
#define WWDG_CR_T3                          ((uint32_t)0x00000008)      /*!< Bit 3 */
#define WWDG_CR_T4                          ((uint32_t)0x00000010)      /*!< Bit 4 */
#define WWDG_CR_T5                          ((uint32_t)0x00000020)      /*!< Bit 5 */
#define WWDG_CR_T6                          ((uint32_t)0x00000040)      /*!< Bit 6 */

#define WWDG_CR_WDGA                        ((uint32_t)0x00000080)      /*!< Activation bit */

/*******************  Bit definition for WWDG_CFR register  *******************/
#define WWDG_CFR_W                          ((uint32_t)0x0000007F)      /*!< W[6:0] bits (7-bit window value) */
#define WWDG_CFR_W0                         ((uint32_t)0x00000001)      /*!< Bit 0 */
#define WWDG_CFR_W1                         ((uint32_t)0x00000002)      /*!< Bit 1 */
#define WWDG_CFR_W2                         ((uint32_t)0x00000004)      /*!< Bit 2 */
#define WWDG_CFR_W3                         ((uint32_t)0x00000008)      /*!< Bit 3 */
#define WWDG_CFR_W4                         ((uint32_t)0x00000010)      /*!< Bit 4 */
#define WWDG_CFR_W5                         ((uint32_t)0x00000020)      /*!< Bit 5 */
#define WWDG_CFR_W6                         ((uint32_t)0x00000040)      /*!< Bit 6 */
                                                                         
#define WWDG_CFR_WDGTB                      ((uint32_t)0x00000180)      /*!< WDGTB[1:0] bits (Timer Base) */
#define WWDG_CFR_WDGTB0                     ((uint32_t)0x00000080)      /*!< Bit 0 */
#define WWDG_CFR_WDGTB1                     ((uint32_t)0x00000100)      /*!< Bit 1 */

#define WWDG_CFR_EWI                        ((uint32_t)0x00000200)      /*!< Early Wakeup Interrupt */

/*******************  Bit definition for WWDG_SR register  ********************/
#define WWDG_SR_EWIF                        ((uint32_t)0x00000001)      /*!< Early Wakeup Interrupt Flag */

/**
  * @}
  */ 

/**
  * @}
  */

/** @addtogroup Exported_macros
  * @{
  */

/******************************* ADC Instances ********************************/
#define IS_ADC_ALL_INSTANCE(INSTANCE) ((INSTANCE) == ADC1)

/******************************* COMP Instances *******************************/
#define IS_COMP_ALL_INSTANCE(INSTANCE) (((INSTANCE) == COMP1) || \
                                       ((INSTANCE) == COMP2))

/******************************* CRC Instances ********************************/
#define IS_CRC_ALL_INSTANCE(INSTANCE) ((INSTANCE) == CRC)

/******************************* DAC Instances *********************************/
#define IS_DAC_ALL_INSTANCE(INSTANCE) ((INSTANCE) == DAC)

/******************************* DMA Instances *********************************/
#define IS_DMA_STREAM_ALL_INSTANCE(INSTANCE) (((INSTANCE) == DMA1_Stream0) || \
                                              ((INSTANCE) == DMA1_Stream1) || \
                                              ((INSTANCE) == DMA1_Stream2) || \
                                              ((INSTANCE) == DMA1_Stream3) || \
                                              ((INSTANCE) == DMA1_Stream4) || \
                                              ((INSTANCE) == DMA1_Stream5) || \
                                              ((INSTANCE) == DMA1_Stream6) || \
                                              ((INSTANCE) == DMA1_Stream7))

/******************************* GPIO Instances *******************************/
#define IS_GPIO_ALL_INSTANCE(INSTANCE) (((INSTANCE) == GPIOA) || \
                                        ((INSTANCE) == GPIOB) || \
                                        ((INSTANCE) == GPIOC) || \
                                        ((INSTANCE) == GPIOD) || \
                                        ((INSTANCE) == GPIOH))

/******************************** I2C Instances *******************************/
#define IS_I2C_ALL_INSTANCE(INSTANCE) (((INSTANCE) == I2C1) || \
                                       ((INSTANCE) == I2C2))

/******************************** I2S Instances *******************************/
#define IS_I2S_ALL_INSTANCE(INSTANCE)  ((INSTANCE) == SPI2)

/******************************* RNG Instances ********************************/
#define IS_RNG_ALL_INSTANCE(INSTANCE)  ((INSTANCE) == RNG)

/****************************** RTC Instances *********************************/
#define IS_RTC_ALL_INSTANCE(INSTANCE)  ((INSTANCE) == RTC)

/******************************** SMBUS Instances *****************************/
#define IS_SMBUS_INSTANCE(INSTANCE)  ((INSTANCE) == I2C1)

/******************************** SPI Instances *******************************/
#define IS_SPI_ALL_INSTANCE(INSTANCE) (((INSTANCE) == SPI1) || \
                                       ((INSTANCE) == SPI2))

/****************** LPTIM Instances : All supported instances *****************/
#define IS_LPTIM_INSTANCE(INSTANCE)       ((INSTANCE) == LPTIM1)

/****************** TIM Instances : All supported instances *******************/
#define IS_TIM_INSTANCE(INSTANCE)       (((INSTANCE) == TIM2)   || \
                                         ((INSTANCE) == TIM6)   || \
                                         ((INSTANCE) == TIM21)  || \
                                         ((INSTANCE) == TIM22))

/************* TIM Instances : at least 1 capture/compare channel *************/
#define IS_TIM_CC1_INSTANCE(INSTANCE)   (((INSTANCE) == TIM2)  || \
                                         ((INSTANCE) == TIM21) || \
                                         ((INSTANCE) == TIM22))

/************ TIM Instances : at least 2 capture/compare channels *************/
#define IS_TIM_CC2_INSTANCE(INSTANCE)  (((INSTANCE) == TIM2)  || \
                                        ((INSTANCE) == TIM21) || \
                                        ((INSTANCE) == TIM22))

/************ TIM Instances : at least 3 capture/compare channels *************/
#define IS_TIM_CC3_INSTANCE(INSTANCE)   ((INSTANCE) == TIM2)

/************ TIM Instances : at least 4 capture/compare channels *************/
#define IS_TIM_CC4_INSTANCE(INSTANCE)   ((INSTANCE) == TIM2)

/******************** TIM Instances : Advanced-control timers *****************/

/******************* TIM Instances : Timer input XOR function *****************/
#define IS_TIM_XOR_INSTANCE(INSTANCE)   ((INSTANCE) == TIM2)

/****************** TIM Instances : DMA requests generation (UDE) *************/
#define IS_TIM_DMA_INSTANCE(INSTANCE)      (((INSTANCE) == TIM2) || \
                                            ((INSTANCE) == TIM6))

/************ TIM Instances : DMA requests generation (CCxDE) *****************/
#define IS_TIM_DMA_CC_INSTANCE(INSTANCE)   ((INSTANCE) == TIM2)

/************ TIM Instances : DMA requests generation (COMDE) *****************/
#define IS_TIM_CCDMA_INSTANCE(INSTANCE)    ((INSTANCE) == TIM2)

/******************** TIM Instances : DMA burst feature ***********************/
#define IS_TIM_DMABURST_INSTANCE(INSTANCE)  ((INSTANCE) == TIM2)

/****** TIM Instances : master mode available (TIMx_CR2.MMS available )********/
#define IS_TIM_MASTER_INSTANCE(INSTANCE)   (((INSTANCE) == TIM2)  || \
                                            ((INSTANCE) == TIM6)  || \
                                            ((INSTANCE) == TIM21) || \
                                            ((INSTANCE) == TIM22))

/*********** TIM Instances : Slave mode available (TIMx_SMCR available )*******/
#define IS_TIM_SLAVE_INSTANCE(INSTANCE)    (((INSTANCE) == TIM2)  || \
                                            ((INSTANCE) == TIM21) || \
                                            ((INSTANCE) == TIM22))

/********************** TIM Instances : 32 bit Counter ************************/

/***************** TIM Instances : external trigger input availabe ************/
#define IS_TIM_ETR_INSTANCE(INSTANCE)      (((INSTANCE) == TIM2)  || \
                                            ((INSTANCE) == TIM21) || \
                                            ((INSTANCE) == TIM22))

/****************** TIM Instances : remapping capability **********************/
#define IS_TIM_REMAP_INSTANCE(INSTANCE) (((INSTANCE) == TIM2)   || \
                                         ((INSTANCE) == TIM21)  || \
                                         ((INSTANCE) == TIM22))

/******************* TIM Instances : output(s) available **********************/
#define IS_TIM_CCX_INSTANCE(INSTANCE, CHANNEL) \
    ((((INSTANCE) == TIM2) &&                  \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4)))           \
     ||                                        \
     (((INSTANCE) == TIM21) &&                 \
      (((CHANNEL) == TIM_CHANNEL_1) ||         \
       ((CHANNEL) == TIM_CHANNEL_2)))          \
     ||                                        \
     (((INSTANCE) == TIM22) &&                 \
      (((CHANNEL) == TIM_CHANNEL_1) ||         \
       ((CHANNEL) == TIM_CHANNEL_2))))

/******************** UART Instances : Asynchronous mode **********************/
#define IS_UART_INSTANCE(INSTANCE) (((INSTANCE) == USART1) || \
                                    ((INSTANCE) == USART2) || \
                                    ((INSTANCE) == LPUART1))

/******************** USART Instances : Synchronous mode **********************/
#define IS_USART_INSTANCE(INSTANCE) (((INSTANCE) == USART1) || \
                                     ((INSTANCE) == USART2))

/****************** USART Instances : Auto Baud Rate detection ****************/

#define IS_USART_AUTOBAUDRATE_DETECTION_INSTANCE(INSTANCE) (((INSTANCE) == USART1) || \
                                                            ((INSTANCE) == USART2))

/******************** UART Instances : Half-Duplex mode **********************/
#define IS_UART_HALFDUPLEX_INSTANCE(INSTANCE)    (((INSTANCE) == USART1) || \
                                                  ((INSTANCE) == USART2) || \
                                                  ((INSTANCE) == LPUART1))

/******************** UART Instances : LIN mode **********************/
#define IS_UART_LIN_INSTANCE(INSTANCE)    (((INSTANCE) == USART1) || \
                                           ((INSTANCE) == USART2))

/******************** UART Instances : Wake-up from Stop mode **********************/

#define IS_UART_WAKEUP_FROMSTOP_INSTANCE(INSTANCE)   (((INSTANCE) == USART1) || \
                                                      ((INSTANCE) == USART2) || \
                                                      ((INSTANCE) == LPUART1))

/****************** UART Instances : Hardware Flow control ********************/
#define IS_UART_HWFLOW_INSTANCE(INSTANCE) (((INSTANCE) == USART1) || \
                                           ((INSTANCE) == USART2) || \
                                           ((INSTANCE) == LPUART1))

/********************* UART Instances : Smard card mode ***********************/
#define IS_SMARTCARD_INSTANCE(INSTANCE) (((INSTANCE) == USART1) || \
                                         ((INSTANCE) == USART2))

/*********************** UART Instances : IRDA mode ***************************/
#define IS_IRDA_INSTANCE(INSTANCE) (((INSTANCE) == USART1) || \
                                    ((INSTANCE) == USART2))

/****************************** IWDG Instances ********************************/
#define IS_IWDG_ALL_INSTANCE(INSTANCE)  ((INSTANCE) == IWDG)

/****************************** USB Instances ********************************/
#define IS_USB_ALL_INSTANCE(INSTANCE) ((INSTANCE) == USB)

/****************************** WWDG Instances ********************************/
#define IS_WWDG_ALL_INSTANCE(INSTANCE)  ((INSTANCE) == WWDG)

/****************************** LCD Instances ********************************/
#define IS_LCD_ALL_INSTANCE(INSTANCE) ((INSTANCE) == LCD)

/**
  * @}
  */

/******************************************************************************/
/*  For a painless codes migration between the STM32L0xx device product       */
/*  lines, the aliases defined below are put in place to overcome the         */
/*  differences in the interrupt handlers and IRQn definitions.               */
/*  No need to update developed interrupt code when moving across             */ 
/*  product lines within the same STM32L0 Family                              */
/******************************************************************************/

/* Aliases for __IRQn */

#define LPUART1_IRQn                   RNG_LPUART1_IRQn
#define AES_LPUART1_IRQn               RNG_LPUART1_IRQn
#define AES_RNG_LPUART1_IRQn           RNG_LPUART1_IRQn
#define TIM6_IRQn                      TIM6_DAC_IRQn
#define RCC_IRQn                       RCC_CRS_IRQn

/* Aliases for __IRQHandler */
#define LPUART1_IRQHandler             RNG_LPUART1_IRQHandler
#define AES_LPUART1_IRQHandler         RNG_LPUART1_IRQHandler
#define AES_RNG_LPUART1_IRQHandler     RNG_LPUART1_IRQHandler
#define TIM6_IRQHandler                TIM6_DAC_IRQHandler
#define RCC_IRQHandler                 RCC_CRS_IRQHandler

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STM32L053xx_H */



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
