/**
  ******************************************************************************
  * @file    stm32l0xx_hal_rcc.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   Header file of RCC HAL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L0xx_HAL_RCC_H
#define __STM32L0xx_HAL_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup RCC RCC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  RCC PLL configuration structure definition
  */
typedef struct
{
  uint32_t PLLState;   /*!< The new state of the PLL.
                            This parameter can be a value of @ref RCC_PLL_Config */

  uint32_t PLLSource;  /*!< RCC_PLLSource: PLL entry clock source.
                            This parameter must be a value of @ref RCC_PLL_Clock_Source */

  uint32_t PLLMUL;       /*!< PLLMUL: Multiplication factor for PLL VCO output clock
                              This parameter must of @ref RCC_PLLMultiplication_Factor */

  uint32_t PLLDIV;       /*!< PLLDIV: Division factor for main system clock (SYSCLK)
                            This parameter must be a value of @ref RCC_PLLDivider_Factor */

}RCC_PLLInitTypeDef;

/**
  * @brief  RCC Internal/External Oscillator (HSE, HSI, LSE and LSI) configuration structure definition  
  */
typedef struct
{
  uint32_t OscillatorType;       /*!< The oscillators to be configured.
                                      This parameter can be a value of @ref RCC_Oscillator_Type */

  uint32_t HSEState;             /*!< The new state of the HSE.
                                      This parameter can be a value of @ref RCC_HSE_Config */

  uint32_t LSEState;             /*!< The new state of the LSE.
                                      This parameter can be a value of @ref RCC_LSE_Config */

  uint32_t HSIState;             /*!< The new state of the HSI.
                                      This parameter can be a value of @ref RCC_HSI_Config */

  uint32_t HSICalibrationValue;  /*!< The calibration trimming value.
                                      This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x1F */

  uint32_t LSIState;             /*!< The new state of the LSI.
                                      This parameter can be a value of @ref RCC_LSI_Config */

#if !defined (STM32L031xx) && !defined (STM32L041xx) && !defined(STM32L051xx) && !defined(STM32L061xx) && !defined(STM32L071xx)  && !defined(STM32L081xx)
  uint32_t HSI48State;             /*!< The new state of the HSI48.
                                      This parameter can be a value of @ref RCC_HSI48_Config */
#endif

  uint32_t MSIState;             /*!< The new state of the MSI.
                                      This parameter can be a value of @ref RCC_MSI_Config */

  uint32_t MSICalibrationValue;  /*!< The calibration trimming value.
                                      This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF */

  uint32_t MSIClockRange;         /*!< The MSI  frequency  range.
                                      This parameter can be a value of @ref RCC_MSI_Clock_Range  */

  RCC_PLLInitTypeDef PLL;        /*!< PLL structure parameters */

}RCC_OscInitTypeDef;

/**
  * @brief  RCC System, AHB and APB busses clock configuration structure definition  
  */
typedef struct
{
  uint32_t ClockType;             /*!< The clock to be configured.
                                       This parameter can be a value of @ref RCC_System_Clock_Type */

  uint32_t SYSCLKSource;          /*!< The clock source (SYSCLKS) used as system clock.
                                       This parameter can be a value of @ref RCC_System_Clock_Source */

  uint32_t AHBCLKDivider;         /*!< The AHB clock (HCLK) divider. This clock is derived from the system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_AHB_Clock_Source */

  uint32_t APB1CLKDivider;        /*!< The APB1 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_APB1_APB2_Clock_Source */

  uint32_t APB2CLKDivider;        /*!< The APB2 clock (PCLK2) divider. This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_APB1_APB2_Clock_Source */

}RCC_ClkInitTypeDef;


/** @defgroup RCC_Private_Constants RCC Private constatnts
  * @brief RCC registers bit address in the alias region
  * @{
  */
#define RCC_OFFSET                (RCC_BASE - PERIPH_BASE)
/* --- CR Register ---*/
/* Alias word address of HSION bit */
#define RCC_CR_OFFSET             (RCC_OFFSET + 0x00)
/* --- CFGR Register ---*/
/* Alias word address of I2SSRC bit */
#define RCC_CFGR_OFFSET           (RCC_OFFSET + 0x08)
/* --- CSR Register ---*/
#define RCC_CSR_OFFSET            (RCC_OFFSET + 0x74)

/* CR register byte 3 (Bits[23:16]) base address */
#define RCC_CR_BYTE2_ADDRESS          ((uint32_t)0x40023802)

/* CIER register byte 0 (Bits[0:8]) base address */
#define CIER_BYTE0_ADDRESS         ((uint32_t)(RCC_BASE + 0x10 + 0x00))

#define RCC_LSE_TIMEOUT_VALUE          LSE_STARTUP_TIMEOUT
#define RCC_DBP_TIMEOUT_VALUE          ((uint32_t)100)  /* 100 ms */

/**
  * @}
  */

/** @defgroup RCC_Exported_Constants RCC Exported Constants
  * @{
  */

/** @defgroup RCC_Oscillator_Type RCC Oscillator Type
  * @{
  */
#define RCC_OSCILLATORTYPE_NONE            ((uint32_t)0x00000000)
#define RCC_OSCILLATORTYPE_HSE             ((uint32_t)0x00000001)
#define RCC_OSCILLATORTYPE_HSI             ((uint32_t)0x00000002)
#define RCC_OSCILLATORTYPE_LSE             ((uint32_t)0x00000004)
#define RCC_OSCILLATORTYPE_LSI             ((uint32_t)0x00000008)
#define RCC_OSCILLATORTYPE_MSI             ((uint32_t)0x00000010)
#if !defined(STM32L051xx) && !defined(STM32L061xx) && !defined(STM32L071xx)  && !defined(STM32L081xx)
#define RCC_OSCILLATORTYPE_HSI48           ((uint32_t)0x00000020)
#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__) ((__OSCILLATOR__) <= 0x3F)
#else 
#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__) ((__OSCILLATOR__) <= 0x1F)
#endif /* !defined(STM32L051xx) && !defined(STM32L061xx) && !defined(STM32L071xx)  && !defined(STM32L081xx) */

/**
  * @}
  */

/** @defgroup RCC_HSE_Config RCC HSE Config
  * @{
  */
#define RCC_HSE_OFF                     ((uint32_t)0x00000000)
#define RCC_HSE_ON                      RCC_CR_HSEON
#define RCC_HSE_BYPASS                  ((uint32_t)(RCC_CR_HSEBYP | RCC_CR_HSEON))

#define IS_RCC_HSE(__HSE__) (((__HSE__) == RCC_HSE_OFF) || ((__HSE__) == RCC_HSE_ON) || \
                             ((__HSE__) == RCC_HSE_BYPASS))
/**
  * @}
  */

/** @defgroup RCC_LSE_Config RCC LSE Config
  * @{
  */
#define RCC_LSE_OFF                      ((uint32_t)0x00000000)
#define RCC_LSE_ON                       RCC_CSR_LSEON
#define RCC_LSE_BYPASS                   ((uint32_t)(RCC_CSR_LSEBYP | RCC_CSR_LSEON))

#define IS_RCC_LSE(__LSE__) (((__LSE__) == RCC_LSE_OFF) || ((__LSE__) == RCC_LSE_ON) || \
                             ((__LSE__) == RCC_LSE_BYPASS))
/**
  * @}
  */



/** @defgroup RCC_MSI_Clock_Range RCC MSI Clock Range
  * @{
  */

#define RCC_MSIRANGE_0                   RCC_ICSCR_MSIRANGE_0 /*!< MSI = 65.536 KHz  */
#define RCC_MSIRANGE_1                   RCC_ICSCR_MSIRANGE_1 /*!< MSI = 131.072 KHz */
#define RCC_MSIRANGE_2                   RCC_ICSCR_MSIRANGE_2 /*!< MSI = 262.144 KHz */
#define RCC_MSIRANGE_3                   RCC_ICSCR_MSIRANGE_3 /*!< MSI = 524.288 KHz */
#define RCC_MSIRANGE_4                   RCC_ICSCR_MSIRANGE_4 /*!< MSI = 1.048 MHz   */
#define RCC_MSIRANGE_5                   RCC_ICSCR_MSIRANGE_5 /*!< MSI = 2.097 MHz   */
#define RCC_MSIRANGE_6                   RCC_ICSCR_MSIRANGE_6 /*!< MSI = 4.194 MHz   */

#define IS_RCC_MSI_CLOCK_RANGE(__RANGE__) (((__RANGE__) == RCC_MSIRANGE_0) || \
                                          ((__RANGE__) == RCC_MSIRANGE_1) || \
                                          ((__RANGE__) == RCC_MSIRANGE_2) || \
                                          ((__RANGE__) == RCC_MSIRANGE_3) || \
                                          ((__RANGE__) == RCC_MSIRANGE_4) || \
                                          ((__RANGE__) == RCC_MSIRANGE_5) || \
                                          ((__RANGE__) == RCC_MSIRANGE_6))

/**
  * @}
  */ 

/** @defgroup RCC_LSI_Config RCC LSI Config
  * @{
  */
#define RCC_LSI_OFF                      ((uint8_t)0x00)
#define RCC_LSI_ON                       ((uint8_t)0x01)

#define RCC_MSICALIBRATION_DEFAULT     ((uint32_t)0)   /* Default MSI calibration trimming value */

#define IS_RCC_LSI(__LSI__) (((__LSI__) == RCC_LSI_OFF) || ((__LSI__) == RCC_LSI_ON))
/**
  * @}
  */

    
/** @defgroup RCC_MSI_Config RCC MSI Config
  * @{
  */
#define RCC_MSI_OFF                      ((uint8_t)0x00)
#define RCC_MSI_ON                       ((uint8_t)0x01)

#define RCC_HSICALIBRATION_DEFAULT     ((uint32_t)0x10)   /* Default HSI calibration trimming value */

#define IS_RCC_MSI(__MSI__) (((__MSI__) == RCC_MSI_OFF) || ((__MSI__) == RCC_MSI_ON))
/**
  * @}
  */

#if !defined(STM32L051xx) && !defined(STM32L061xx) && !defined(STM32L071xx)  && !defined(STM32L081xx)
/** @defgroup RCC_HSI48_Config
  * @{
  */
#define RCC_HSI48_OFF                      ((uint8_t)0x00)
#define RCC_HSI48_ON                       ((uint8_t)0x01)

#define IS_RCC_HSI48(__HSI48__) (((__HSI48__) == RCC_HSI48_OFF) || ((__HSI48__) == RCC_HSI48_ON))
/**
  * @}
  */
#endif /* !defined(STM32L051xx) && !defined(STM32L061xx) && !defined(STM32L071xx)  && !defined(STM32L081xx) */

/** @defgroup RCC_PLL_Config RCC PLL Config
  * @{
  */
#define RCC_PLL_NONE                      ((uint8_t)0x00)
#define RCC_PLL_OFF                       ((uint8_t)0x01)
#define RCC_PLL_ON                        ((uint8_t)0x02)

#define IS_RCC_PLL(__PLL__) (((__PLL__) == RCC_PLL_NONE) ||((__PLL__) == RCC_PLL_OFF) || ((__PLL__) == RCC_PLL_ON))
/**
  * @}
  */

/** @defgroup RCC_PLL_Clock_Source PCC PLL Clock Source
  * @{
  */
#define RCC_PLLSOURCE_HSI                RCC_CFGR_PLLSRC_HSI
#define RCC_PLLSOURCE_HSE                RCC_CFGR_PLLSRC_HSE

#define IS_RCC_PLLSOURCE(__SOURCE__) (((__SOURCE__) == RCC_PLLSOURCE_HSI) || \
                                      ((__SOURCE__) == RCC_PLLSOURCE_HSE))

/**
  * @}
  */

/** @defgroup RCC_PLLMultiplication_Factor RCC PLL Multipliers
  * @{
  */

#define RCC_PLLMUL_3                     RCC_CFGR_PLLMUL3
#define RCC_PLLMUL_4                     RCC_CFGR_PLLMUL4
#define RCC_PLLMUL_6                     RCC_CFGR_PLLMUL6
#define RCC_PLLMUL_8                     RCC_CFGR_PLLMUL8
#define RCC_PLLMUL_12                    RCC_CFGR_PLLMUL12
#define RCC_PLLMUL_16                    RCC_CFGR_PLLMUL16
#define RCC_PLLMUL_24                    RCC_CFGR_PLLMUL24
#define RCC_PLLMUL_32                    RCC_CFGR_PLLMUL32
#define RCC_PLLMUL_48                    RCC_CFGR_PLLMUL48
#define IS_RCC_PLL_MUL(__MUL__) (((__MUL__) == RCC_PLLMUL_3) || ((__MUL__) == RCC_PLLMUL_4) || \
                                 ((__MUL__) == RCC_PLLMUL_6) || ((__MUL__) == RCC_PLLMUL_8) || \
                                 ((__MUL__) == RCC_PLLMUL_12) || ((__MUL__) == RCC_PLLMUL_16) || \
                                 ((__MUL__) == RCC_PLLMUL_24) || ((__MUL__) == RCC_PLLMUL_32) || \
                                 ((__MUL__) == RCC_PLLMUL_48))
/**
  * @}
  */

/** @defgroup RCC_PLLDivider_Factor RCC PLL Dividers
  * @{
  */

#define RCC_PLLDIV_2                     RCC_CFGR_PLLDIV2
#define RCC_PLLDIV_3                     RCC_CFGR_PLLDIV3
#define RCC_PLLDIV_4                     RCC_CFGR_PLLDIV4
#define IS_RCC_PLL_DIV(__DIV__) (((__DIV__) == RCC_PLLDIV_2) || ((__DIV__) == RCC_PLLDIV_3) || \
                                 ((__DIV__) == RCC_PLLDIV_4))
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Type RCC System Clock Type
  * @{
  */
#define RCC_CLOCKTYPE_SYSCLK             ((uint32_t)0x00000001)
#define RCC_CLOCKTYPE_HCLK               ((uint32_t)0x00000002)
#define RCC_CLOCKTYPE_PCLK1              ((uint32_t)0x00000004)
#define RCC_CLOCKTYPE_PCLK2              ((uint32_t)0x00000008)

#define IS_RCC_CLOCKTYPE(__CLK__) ((1 <= (__CLK__)) && ((__CLK__) <= 15))
/**
  * @}
  */
  
/** @defgroup RCC_System_Clock_Source RCC System Clock Source
  * @{
  */
#define RCC_SYSCLKSOURCE_MSI             RCC_CFGR_SW_MSI
#define RCC_SYSCLKSOURCE_HSI             RCC_CFGR_SW_HSI
#define RCC_SYSCLKSOURCE_HSE             RCC_CFGR_SW_HSE
#define RCC_SYSCLKSOURCE_PLLCLK          RCC_CFGR_SW_PLL

#define IS_RCC_SYSCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_SYSCLKSOURCE_HSI) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_HSE) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_MSI) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_PLLCLK))
/**
  * @}
  */ 

/** @defgroup RCC_System_Clock_Source_Status System Clock Source Status
  * @{
  */
#define RCC_SYSCLKSOURCE_STATUS_HSI      RCC_CFGR_SWS_HSI
#define RCC_SYSCLKSOURCE_STATUS_HSE      RCC_CFGR_SWS_HSE
#define RCC_SYSCLKSOURCE_STATUS_PLLCLK   RCC_CFGR_SWS_PLL

/**
  * @}
  */

/** @defgroup RCC_AHB_Clock_Source RCC AHB Clock SOurce
  * @{
  */
#define RCC_SYSCLK_DIV1                  RCC_CFGR_HPRE_DIV1
#define RCC_SYSCLK_DIV2                  RCC_CFGR_HPRE_DIV2
#define RCC_SYSCLK_DIV4                  RCC_CFGR_HPRE_DIV4
#define RCC_SYSCLK_DIV8                  RCC_CFGR_HPRE_DIV8
#define RCC_SYSCLK_DIV16                 RCC_CFGR_HPRE_DIV16
#define RCC_SYSCLK_DIV64                 RCC_CFGR_HPRE_DIV64
#define RCC_SYSCLK_DIV128                RCC_CFGR_HPRE_DIV128
#define RCC_SYSCLK_DIV256                RCC_CFGR_HPRE_DIV256
#define RCC_SYSCLK_DIV512                RCC_CFGR_HPRE_DIV512

#define IS_RCC_HCLK(__HCLK__) (((__HCLK__) == RCC_SYSCLK_DIV1)   || ((__HCLK__) == RCC_SYSCLK_DIV2)   || \
                               ((__HCLK__) == RCC_SYSCLK_DIV4)   || ((__HCLK__) == RCC_SYSCLK_DIV8)   || \
                               ((__HCLK__) == RCC_SYSCLK_DIV16)  || ((__HCLK__) == RCC_SYSCLK_DIV64)  || \
                               ((__HCLK__) == RCC_SYSCLK_DIV128) || ((__HCLK__) == RCC_SYSCLK_DIV256) || \
                               ((__HCLK__) == RCC_SYSCLK_DIV512))
/**
  * @}
  */ 
  
/** @defgroup RCC_APB1_APB2_Clock_Source RCC APB1 Clock Source
  * @{
  */
#define RCC_HCLK_DIV1                    RCC_CFGR_PPRE1_DIV1
#define RCC_HCLK_DIV2                    RCC_CFGR_PPRE1_DIV2
#define RCC_HCLK_DIV4                    RCC_CFGR_PPRE1_DIV4
#define RCC_HCLK_DIV8                    RCC_CFGR_PPRE1_DIV8
#define RCC_HCLK_DIV16                   RCC_CFGR_PPRE1_DIV16

#define IS_RCC_PCLK(__PCLK__) (((__PCLK__) == RCC_HCLK_DIV1) || ((__PCLK__) == RCC_HCLK_DIV2) || \
                               ((__PCLK__) == RCC_HCLK_DIV4) || ((__PCLK__) == RCC_HCLK_DIV8) || \
                               ((__PCLK__) == RCC_HCLK_DIV16))
/**
  * @}
  */ 

/** @defgroup RCC_RTC_Clock_Source RCC RTC Clock Source
  * @{
  */
#define RCC_RTCCLKSOURCE_NO_CLK          ((uint32_t)0x00000000)
#define RCC_RTCCLKSOURCE_LSE             RCC_CSR_RTCSEL_LSE
#define RCC_RTCCLKSOURCE_LSI             RCC_CSR_RTCSEL_LSI
#define RCC_RTCCLKSOURCE_HSE_DIV2        RCC_CSR_RTCSEL_HSE
#define RCC_RTCCLKSOURCE_HSE_DIV4        ((uint32_t)RCC_CSR_RTCSEL_HSE | RCC_CR_RTCPRE_0)
#define RCC_RTCCLKSOURCE_HSE_DIV8        ((uint32_t)RCC_CSR_RTCSEL_HSE | RCC_CR_RTCPRE_1)
#define RCC_RTCCLKSOURCE_HSE_DIV16       ((uint32_t)RCC_CSR_RTCSEL_HSE | RCC_CR_RTCPRE)
#define IS_RCC_RTCCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_RTCCLKSOURCE_LSE) || \
                                          ((__SOURCE__) == RCC_RTCCLKSOURCE_LSI) || \
                                          ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV2) || \
                                          ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV4) || \
                                          ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV8) || \
                                          ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV16))
/**
  * @}
  */

/** @defgroup RCC_MCO_Clock_Source RCC MCo Clock Source
  * @{
  */

#define RCC_MCO1SOURCE_NOCLOCK            RCC_CFGR_MCO_NOCLOCK
#define RCC_MCO1SOURCE_SYSCLK             RCC_CFGR_MCO_SYSCLK
#define RCC_MCO1SOURCE_HSI                RCC_CFGR_MCO_HSI
#define RCC_MCO1SOURCE_MSI                RCC_CFGR_MCO_MSI
#define RCC_MCO1SOURCE_HSE                RCC_CFGR_MCO_HSE
#define RCC_MCO1SOURCE_PLLCLK             RCC_CFGR_MCO_PLL
#define RCC_MCO1SOURCE_LSI                RCC_CFGR_MCO_LSI
#define RCC_MCO1SOURCE_LSE                RCC_CFGR_MCO_LSE
#if  !defined (STM32L031xx) && !defined (STM32L041xx) && !defined(STM32L051xx) && !defined(STM32L061xx) && !defined(STM32L071xx)  && !defined(STM32L081xx)
#define RCC_MCO1SOURCE_HSI48              RCC_CFGR_MCO_HSI48
#endif

#if  !defined (STM32L031xx) && !defined (STM32L041xx) && !defined(STM32L051xx) && !defined(STM32L061xx) && !defined(STM32L071xx)  && !defined(STM32L081xx)
#define IS_RCC_MCO1SOURCE(__SOURCE__) (((__SOURCE__) == RCC_MCO1SOURCE_NOCLOCK) || ((__SOURCE__) == RCC_MCO1SOURCE_SYSCLK) || \
                                      ((__SOURCE__) == RCC_MCO1SOURCE_HSI)  || ((__SOURCE__) == RCC_MCO1SOURCE_MSI) || \
                                      ((__SOURCE__) == RCC_MCO1SOURCE_HSE)  || ((__SOURCE__) == RCC_MCO1SOURCE_PLLCLK) || \
                                      ((__SOURCE__) == RCC_MCO1SOURCE_LSI) || ((__SOURCE__) == RCC_MCO1SOURCE_LSE) || \
                                      ((__SOURCE__) == RCC_MCO1SOURCE_HSI48))
#else
#define IS_RCC_MCO1SOURCE(__SOURCE__) (((__SOURCE__) == RCC_MCO1SOURCE_NOCLOCK) || ((__SOURCE__) == RCC_MCO1SOURCE_SYSCLK) || \
                                      ((__SOURCE__) == RCC_MCO1SOURCE_HSI)  || ((__SOURCE__) == RCC_MCO1SOURCE_MSI) || \
                                      ((__SOURCE__) == RCC_MCO1SOURCE_HSE)  || ((__SOURCE__) == RCC_MCO1SOURCE_PLLCLK) || \
                                      ((__SOURCE__) == RCC_MCO1SOURCE_LSI) || ((__SOURCE__) == RCC_MCO1SOURCE_LSE))
#endif                                      
                                      
/**
  * @}
  */

/** @defgroup RCC_MCOPrescaler RCC MCO Prescaler
  * @{
  */

#define RCC_MCODIV_1            RCC_CFGR_MCO_PRE_1
#define RCC_MCODIV_2            RCC_CFGR_MCO_PRE_2
#define RCC_MCODIV_4            RCC_CFGR_MCO_PRE_4
#define RCC_MCODIV_8            RCC_CFGR_MCO_PRE_8
#define RCC_MCODIV_16           RCC_CFGR_MCO_PRE_16

#define IS_RCC_MCODIV(__DIV__) (((__DIV__) == RCC_MCODIV_1)  || \
                                ((__DIV__) == RCC_MCODIV_2)  || \
                                ((__DIV__) == RCC_MCODIV_4)  || \
                                ((__DIV__) == RCC_MCODIV_8)  || \
                                ((__DIV__) == RCC_MCODIV_16))
/**
  * @}
  */  

/** @defgroup RCC_MCO_Index RCC MCO Index
  * @{
  */
#define RCC_MCO1                         ((uint32_t)0x00000000)
#define RCC_MCO2                         ((uint32_t)0x00000001)

#define IS_RCC_MCO(__MCOx__) (((__MCOx__) == RCC_MCO1) || ((__MCOx__) == RCC_MCO2))
/**
  * @}
  */

/** @defgroup RCC_Interrupt RCC Interruptions
  * @{
  */
#define RCC_IT_LSIRDY                    RCC_CIFR_LSIRDYF
#define RCC_IT_LSERDY                    RCC_CIFR_LSERDYF
#define RCC_IT_HSIRDY                    RCC_CIFR_HSIRDYF
#define RCC_IT_HSERDY                    RCC_CIFR_HSERDYF
#define RCC_IT_PLLRDY                    RCC_CIFR_PLLRDYF
#define RCC_IT_MSIRDY                    RCC_CIFR_MSIRDYF

#define RCC_IT_LSECSS                    RCC_CIFR_LSECSSF
#define RCC_IT_CSS                       RCC_CIFR_CSSF
#if !defined(STM32L051xx) && !defined(STM32L061xx) && !defined(STM32L071xx)  && !defined(STM32L081xx)
#define RCC_IT_HSI48RDY                  RCC_CIFR_HSI48RDYF

#define IS_RCC_IT(__IT__) (((__IT__) == RCC_IT_LSIRDY) || ((__IT__) == RCC_IT_LSERDY) || \
                           ((__IT__) == RCC_IT_HSIRDY) || ((__IT__) == RCC_IT_HSERDY) || \
                           ((__IT__) == RCC_IT_PLLRDY) || ((__IT__) == RCC_IT_MSIRDY) || \
                           ((__IT__) == RCC_IT_HSI48RDY)  || ((__IT__) == RCC_IT_LSECSS))

#define IS_RCC_GET_IT(__IT__) (((__IT__) == RCC_IT_LSIRDY) || ((__IT__) == RCC_IT_LSERDY) || \
                               ((__IT__) == RCC_IT_HSIRDY) || ((__IT__) == RCC_IT_HSERDY) || \
                               ((__IT__) == RCC_IT_PLLRDY) || ((__IT__) == RCC_IT_MSIRDY) || \
                               ((__IT__) == RCC_IT_CSS)    || ((__IT__) == RCC_IT_HSI48RDY) || \
                               ((__IT__) == RCC_IT_LSECSS))

#define IS_RCC_CLEAR_IT(__IT__) (((__IT__) == RCC_IT_LSIRDY) || ((__IT__) == RCC_IT_LSERDY) || \
                                 ((__IT__) == RCC_IT_HSIRDY) || ((__IT__) == RCC_IT_HSERDY) || \
                                 ((__IT__) == RCC_IT_PLLRDY) || ((__IT__) == RCC_IT_MSIRDY) || \
                                 ((__IT__) == RCC_IT_CSS)    || ((__IT__) == RCC_IT_HSI48RDY) || \
                                 ((__IT__) == RCC_IT_LSECSS))
#else
#define IS_RCC_IT(__IT__) (((__IT__) == RCC_IT_LSIRDY) || ((__IT__) == RCC_IT_LSERDY) || \
                           ((__IT__) == RCC_IT_HSIRDY) || ((__IT__) == RCC_IT_HSERDY) || \
                           ((__IT__) == RCC_IT_PLLRDY) || ((__IT__) == RCC_IT_MSIRDY) || \
                           ((__IT__) == RCC_IT_LSECSS))

#define IS_RCC_GET_IT(__IT__) (((__IT__) == RCC_IT_LSIRDY) || ((__IT__) == RCC_IT_LSERDY) || \
                               ((__IT__) == RCC_IT_HSIRDY) || ((__IT__) == RCC_IT_HSERDY) || \
                               ((__IT__) == RCC_IT_PLLRDY) || ((__IT__) == RCC_IT_MSIRDY) || \
                               ((__IT__) == RCC_IT_CSS)    ||  ((__IT__) == RCC_IT_LSECSS))
                               

#define IS_RCC_CLEAR_IT(__IT__) (((__IT__) == RCC_IT_LSIRDY) || ((__IT__) == RCC_IT_LSERDY) || \
                                 ((__IT__) == RCC_IT_HSIRDY) || ((__IT__) == RCC_IT_HSERDY) || \
                                 ((__IT__) == RCC_IT_PLLRDY) || ((__IT__) == RCC_IT_MSIRDY) || \
                                 ((__IT__) == RCC_IT_CSS)    || ((__IT__) == RCC_IT_LSECSS))
                                 
#endif /* !defined(STM32L051xx) && !defined(STM32L061xx) && !defined(STM32L071xx)  && !defined(STM32L081xx) */
/**
  * @}
  */

/** @defgroup RCC_Flag
  *        Elements values convention: 0XXYYYYYb
  *           - YYYYY  : Flag position in the register
  *           - 0XX  : Register index
  *                 - 01: CR register
  *                 - 10: CSR register
  *                 - 11: CRRCR register
  * @{
  */
/* Flags in the CR register */
#define RCC_FLAG_HSIRDY                  ((uint8_t)0x22)
#define RCC_FLAG_HSIDIV                  ((uint8_t)0x24)
#define RCC_FLAG_MSIRDY                  ((uint8_t)0x29)
#define RCC_FLAG_HSERDY                  ((uint8_t)0x31)
#define RCC_FLAG_PLLRDY                  ((uint8_t)0x39)

/* Flags in the CSR register */
#define RCC_FLAG_LSERDY                  ((uint8_t)0x49)
#define RCC_FLAG_LSECSS                  ((uint8_t)0x4E)
#define RCC_FLAG_LSIRDY                  ((uint8_t)0x41)
#define RCC_FLAG_FWRST                   ((uint8_t)0x58)
#define RCC_FLAG_OBLRST                  ((uint8_t)0x59)
#define RCC_FLAG_PINRST                  ((uint8_t)0x5A)
#define RCC_FLAG_PORRST                  ((uint8_t)0x5B)
#define RCC_FLAG_SFTRST                  ((uint8_t)0x5C)
#define RCC_FLAG_IWDGRST                 ((uint8_t)0x5D)
#define RCC_FLAG_WWDGRST                 ((uint8_t)0x5E)
#define RCC_FLAG_LPWRRST                 ((uint8_t)0x5F)

#if !defined(STM32L051xx) && !defined(STM32L061xx) && !defined(STM32L071xx)  && !defined(STM32L081xx)
/* Flags in the CRRCR register */
#define RCC_FLAG_HSI48RDY                ((uint8_t)0x61)
#endif /* !defined(STM32L051xx) && !defined(STM32L061xx) && !defined(STM32L071xx)  && !defined(STM32L081xx) */

#define IS_RCC_CALIBRATION_VALUE(__VALUE__) ((__VALUE__) <= 0x1F)
#define IS_RCC_MSICALIBRATION_VALUE(__VALUE__) ((__VALUE__) <= 0xFF)

/**
  * @}
  */ 

/**
  * @}
  */   
/* Exported macro ------------------------------------------------------------*/
/** @defgroup RCC_Exported_Macros RCC Exported Macros
 * @{
 */

/** @brief  Enable or disable the AHB peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.
  */
#define __HAL_RCC_DMA1_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->AHBENR, RCC_AHBENR_DMA1EN);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_DMA1EN);\
                                        UNUSED(tmpreg); \
                                      } while(0)
                                      
#define __HAL_RCC_MIF_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->AHBENR, RCC_AHBENR_MIFEN);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_MIFEN);\
                                        UNUSED(tmpreg); \
                                      } while(0)
                                      
#define __HAL_RCC_CRC_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->AHBENR, RCC_AHBENR_CRCEN);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_CRCEN);\
                                        UNUSED(tmpreg); \
                                      } while(0)


#define __HAL_RCC_DMA1_CLK_DISABLE()          (RCC->AHBENR  &= ~ (RCC_AHBENR_DMA1EN))
#define __HAL_RCC_MIF_CLK_DISABLE()           (RCC->AHBENR  &= ~ (RCC_AHBENR_MIFEN))
#define __HAL_RCC_CRC_CLK_DISABLE()           (RCC->AHBENR  &= ~ (RCC_AHBENR_CRCEN))


/** @brief  Enable or disable the IOPORT peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.
  */
#define __HAL_RCC_GPIOA_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN);\
                                        UNUSED(tmpreg); \
                                      } while(0)
                                      
#define __HAL_RCC_GPIOB_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN);\
                                        UNUSED(tmpreg); \
                                      } while(0)
                                      
#define __HAL_RCC_GPIOC_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOCEN);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOCEN);\
                                        UNUSED(tmpreg); \
                                      } while(0)

#define __HAL_RCC_GPIOD_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIODEN);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIODEN);\
                                        UNUSED(tmpreg); \
                                      } while(0)

#define __HAL_RCC_GPIOH_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOHEN);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOHEN);\
                                        UNUSED(tmpreg); \
                                      } while(0)


#define __HAL_RCC_GPIOA_CLK_DISABLE()        (RCC->IOPENR &= ~(RCC_IOPENR_GPIOAEN))
#define __HAL_RCC_GPIOB_CLK_DISABLE()        (RCC->IOPENR &= ~(RCC_IOPENR_GPIOBEN))
#define __HAL_RCC_GPIOC_CLK_DISABLE()        (RCC->IOPENR &= ~(RCC_IOPENR_GPIOCEN))
#define __HAL_RCC_GPIOD_CLK_DISABLE()        (RCC->IOPENR &= ~(RCC_IOPENR_GPIODEN))
#define __HAL_RCC_GPIOH_CLK_DISABLE()        (RCC->IOPENR &= ~(RCC_IOPENR_GPIOHEN))


/** @brief  Enable or disable the Low Speed APB (APB1) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  */
#define __HAL_RCC_WWDG_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_WWDGEN))
#define __HAL_RCC_PWR_CLK_ENABLE()     (RCC->APB1ENR |= (RCC_APB1ENR_PWREN))

#define __HAL_RCC_WWDG_CLK_DISABLE()    (RCC->APB1ENR &= ~ (RCC_APB1ENR_WWDGEN))
#define __HAL_RCC_PWR_CLK_DISABLE()     (RCC->APB1ENR &= ~ (RCC_APB1ENR_PWREN))

/** @brief  Enable or disable the High Speed APB (APB2) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.
  */
#define __HAL_RCC_SYSCFG_CLK_ENABLE()   (RCC->APB2ENR |= (RCC_APB2ENR_SYSCFGEN))
#define __HAL_RCC_DBGMCU_CLK_ENABLE()   (RCC->APB2ENR |= (RCC_APB2ENR_DBGMCUEN))

#define __HAL_RCC_SYSCFG_CLK_DISABLE()   (RCC->APB2ENR &= ~  (RCC_APB2ENR_SYSCFGEN))
#define __HAL_RCC_DBGMCU_CLK_DISABLE()   (RCC->APB2ENR &= ~  (RCC_APB2ENR_DBGMCUEN))

/** @brief  Force or release AHB peripheral reset.
  */
#define __HAL_RCC_AHB_FORCE_RESET()     (RCC->AHBRSTR = 0xFFFFFFFF)
#define __HAL_RCC_DMA1_FORCE_RESET()    (RCC->AHBRSTR |= (RCC_AHBRSTR_DMA1RST))
#define __HAL_RCC_MIF_FORCE_RESET()     (RCC->AHBRSTR |= (RCC_AHBRSTR_MIFRST))
#define __HAL_RCC_CRC_FORCE_RESET()     (RCC->AHBRSTR |= (RCC_AHBRSTR_CRCRST))

#define __HAL_RCC_AHB_RELEASE_RESET()     (RCC->AHBRSTR = 0x00)
#define __HAL_RCC_CRC_RELEASE_RESET()     (RCC->AHBRSTR &= ~ (RCC_AHBRSTR_CRCRST))
#define __HAL_RCC_DMA1_RELEASE_RESET()    (RCC->AHBRSTR &= ~ (RCC_AHBRSTR_DMA1RST))
#define __HAL_RCC_MIF_RELEASE_RESET()     (RCC->AHBRSTR &= ~ (RCC_AHBRSTR_MIFRST))


/** @brief  Force or release IOPORT peripheral reset.
  */
#define __HAL_RCC_IOP_FORCE_RESET()     (RCC->IOPRSTR = 0xFFFFFFFF) 
#define __HAL_RCC_GPIOA_FORCE_RESET()   (RCC->IOPRSTR |= (RCC_IOPRSTR_GPIOARST))
#define __HAL_RCC_GPIOB_FORCE_RESET()   (RCC->IOPRSTR |= (RCC_IOPRSTR_GPIOBRST))
#define __HAL_RCC_GPIOC_FORCE_RESET()   (RCC->IOPRSTR |= (RCC_IOPRSTR_GPIOCRST))
#define __HAL_RCC_GPIOD_FORCE_RESET()   (RCC->IOPRSTR |= (RCC_IOPRSTR_GPIODRST))
#define __HAL_RCC_GPIOH_FORCE_RESET()   (RCC->IOPRSTR |= (RCC_IOPRSTR_GPIOHRST))

#define __HAL_RCC_IOP_RELEASE_RESET()   (RCC->IOPRSTR = 0x00) 
#define __HAL_RCC_GPIOA_RELEASE_RESET() (RCC->IOPRSTR &= ~(RCC_IOPRSTR_GPIOARST))
#define __HAL_RCC_GPIOB_RELEASE_RESET() (RCC->IOPRSTR &= ~(RCC_IOPRSTR_GPIOBRST))
#define __HAL_RCC_GPIOC_RELEASE_RESET() (RCC->IOPRSTR &= ~(RCC_IOPRSTR_GPIOCRST))
#define __HAL_RCC_GPIOD_RELEASE_RESET() (RCC->IOPRSTR &= ~(RCC_IOPRSTR_GPIODRST))
#define __HAL_RCC_GPIOH_RELEASE_RESET() (RCC->IOPRSTR &= ~(RCC_IOPRSTR_GPIOHRST))

/** @brief  Force or release APB1 peripheral reset.
  */
#define __HAL_RCC_APB1_FORCE_RESET()     (RCC->APB1RSTR = 0xFFFFFFFF)  
#define __HAL_RCC_WWDG_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_WWDGRST))
#define __HAL_RCC_PWR_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_PWRRST))

#define __HAL_RCC_APB1_RELEASE_RESET()   (RCC->APB1RSTR = 0x00)
#define __HAL_RCC_WWDG_RELEASE_RESET()   (RCC->APB1RSTR &= ~ (RCC_APB1RSTR_WWDGRST))
#define __HAL_RCC_PWR_RELEASE_RESET()    (RCC->APB1RSTR &= ~ (RCC_APB1RSTR_PWRRST))

/** @brief  Force or release APB2 peripheral reset.
  */
#define __HAL_RCC_APB2_FORCE_RESET()     (RCC->APB2RSTR = 0xFFFFFFFF)  
#define __HAL_RCC_DBGMCU_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_DBGMCURST))
#define __HAL_RCC_SYSCFG_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_SYSCFGRST))

#define __HAL_RCC_APB2_RELEASE_RESET()   (RCC->APB2RSTR = 0x00)
#define __HAL_RCC_DBGMCU_RELEASE_RESET() (RCC->APB2RSTR &= ~ (RCC_APB2RSTR_DBGMCURST))
#define __HAL_RCC_SYSCFG_RELEASE_RESET() (RCC->APB2RSTR &= ~ (RCC_APB2RSTR_SYSCFGRST))

/** @brief  Enable or disable the AHB peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral activated clocks remain enabled during SLEEP mode.
  */
#define __HAL_RCC_CRC_CLK_SLEEP_ENABLE()      (RCC->AHBSMENR |= (RCC_AHBSMENR_CRCSMEN))
#define __HAL_RCC_MIF_CLK_SLEEP_ENABLE()      (RCC->AHBSMENR |= (RCC_AHBSMENR_MIFSMEN))
#define __HAL_RCC_SRAM_CLK_SLEEP_ENABLE()     (RCC->AHBSMENR |= (RCC_AHBSMENR_SRAMSMEN))
#define __HAL_RCC_DMA1_CLK_SLEEP_ENABLE()     (RCC->AHBSMENR |= (RCC_AHBSMENR_DMA1SMEN))

#define __HAL_RCC_CRC_CLK_SLEEP_DISABLE()     (RCC->AHBSMENR  &= ~ (RCC_AHBSMENR_CRCSMEN))
#define __HAL_RCC_MIF_CLK_SLEEP_DISABLE()     (RCC->AHBSMENR  &= ~ (RCC_AHBSMENR_MIFSMEN))
#define __HAL_RCC_SRAM_CLK_SLEEP_DISABLE()    (RCC->AHBSMENR  &= ~ (RCC_AHBSMENR_SRAMSMEN))
#define __HAL_RCC_DMA1_CLK_SLEEP_DISABLE()    (RCC->AHBSMENR  &= ~ (RCC_AHBSMENR_DMA1SMEN))

/** @brief  Enable or disable the IOPORT peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral activated clocks remain enabled during SLEEP mode.
  */

#define __HAL_RCC_GPIOA_CLK_SLEEP_ENABLE()    (RCC->IOPSMENR |= (RCC_IOPSMENR_GPIOASMEN))
#define __HAL_RCC_GPIOB_CLK_SLEEP_ENABLE()    (RCC->IOPSMENR |= (RCC_IOPSMENR_GPIOBSMEN))
#define __HAL_RCC_GPIOC_CLK_SLEEP_ENABLE()    (RCC->IOPSMENR |= (RCC_IOPSMENR_GPIOCSMEN))
#define __HAL_RCC_GPIOD_CLK_SLEEP_ENABLE()    (RCC->IOPSMENR |= (RCC_IOPSMENR_GPIODSMEN))
#define __HAL_RCC_GPIOH_CLK_SLEEP_ENABLE()    (RCC->IOPSMENR |= (RCC_IOPSMENR_GPIOHSMEN))

#define __HAL_RCC_GPIOA_CLK_SLEEP_DISABLE()   (RCC->IOPSMENR &= ~(RCC_IOPSMENR_GPIOASMEN))
#define __HAL_RCC_GPIOB_CLK_SLEEP_DISABLE()   (RCC->IOPSMENR &= ~(RCC_IOPSMENR_GPIOBSMEN))
#define __HAL_RCC_GPIOC_CLK_SLEEP_DISABLE()   (RCC->IOPSMENR &= ~(RCC_IOPSMENR_GPIOCSMEN))
#define __HAL_RCC_GPIOD_CLK_SLEEP_DISABLE()   (RCC->IOPSMENR &= ~(RCC_IOPSMENR_GPIODSMEN))
#define __HAL_RCC_GPIOH_CLK_SLEEP_DISABLE()   (RCC->IOPSMENR &= ~(RCC_IOPSMENR_GPIOHSMEN))

/** @brief  Enable or disable the APB1 peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral activated clocks remain enabled during SLEEP mode.
  */
#define __HAL_RCC_WWDG_CLK_SLEEP_ENABLE()    (RCC->APB1SMENR |= (RCC_APB1SMENR_WWDGSMEN))
#define __HAL_RCC_PWR_CLK_SLEEP_ENABLE()     (RCC->APB1SMENR |= (RCC_APB1SMENR_PWRSMEN))

#define __HAL_RCC_WWDG_CLK_SLEEP_DISABLE()   (RCC->APB1SMENR &= ~ (RCC_APB1SMENR_WWDGSMEN))
#define __HAL_RCC_PWR_CLK_SLEEP_DISABLE()    (RCC->APB1SMENR &= ~ (RCC_APB1SMENR_PWRSMEN))

/** @brief  Enable or disable the APB2 peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral actiated clocks remain enabled during SLEEP mode.
  */
#define __HAL_RCC_SYSCFG_CLK_SLEEP_ENABLE()   (RCC->APB2SMENR |= (RCC_APB2SMENR_SYSCFGSMEN))
#define __HAL_RCC_DBGMCU_CLK_SLEEP_ENABLE()   (RCC->APB2SMENR |= (RCC_APB2SMENR_DBGMCUSMEN))

#define __HAL_RCC_SYSCFG_CLK_SLEEP_DISABLE()   (RCC->APB2SMENR &= ~  (RCC_APB2SMENR_SYSCFGSMEN))
#define __HAL_RCC_DBGMCU_CLK_SLEEP_DISABLE()   (RCC->APB2SMENR &= ~  (RCC_APB2SMENR_DBGMCUSMEN))

/** @brief  Macro to enable or disable the Internal High Speed oscillator (HSI).
  * @note     After enabling the HSI, the application software should wait on 
  *           HSIRDY flag to be set indicating that HSI clock is stable and can
  *           be used to clock the PLL and/or system clock.
  * @note     HSI can not be stopped if it is used directly or through the PLL
  *           as system clock. In this case, you have to select another source 
  *           of the system clock then stop the HSI.
  * @note     The HSI is stopped by hardware when entering STOP and STANDBY modes. 
  * @param    __STATE__: specifies the new state of the HSI.
  *           This parameter can be one of the following values:
  *            @arg RCC_HSI_OFF: turn OFF the HSI oscillator
  *            @arg RCC_HSI_ON: turn ON the HSI oscillator
  *            @arg RCC_HSI_DIV4: turn ON the HSI oscillator and divide it by 4
  * @note   When the HSI is stopped, HSIRDY flag goes low after 6 HSI oscillator
  *         clock cycles. 
  */
#define __HAL_RCC_HSI_CONFIG(__STATE__) \
                  MODIFY_REG(RCC->CR, RCC_CR_HSION | RCC_CR_HSIDIVEN , (uint32_t)(__STATE__))

/** @brief  Macros to enable or disable the Internal High Speed oscillator (HSI).
  * @note   The HSI is stopped by hardware when entering STOP and STANDBY modes.
  *         It is used (enabled by hardware) as system clock source after startup
  *         from Reset, wakeup from STOP and STANDBY mode, or in case of failure
  *         of the HSE used directly or indirectly as system clock (if the Clock
  *         Security System CSS is enabled).
  * @note   HSI can not be stopped if it is used as system clock source. In this case,
  *         you have to select another source of the system clock then stop the HSI.  
  * @note   After enabling the HSI, the application software should wait on HSIRDY
  *         flag to be set indicating that HSI clock is stable and can be used as
  *         system clock source.
  * @note   When the HSI is stopped, HSIRDY flag goes low after 6 HSI oscillator
  *         clock cycles.  
  */
#define __HAL_RCC_HSI_ENABLE()  SET_BIT(RCC->CR, RCC_CR_HSION)
#define __HAL_RCC_HSI_DISABLE() CLEAR_BIT(RCC->CR, RCC_CR_HSION)

/**
  * @brief  Macros to enable or disable the Internal Multi Speed oscillator (MSI).
  * @note     The MSI is stopped by hardware when entering STOP and STANDBY modes.
  *           It is used (enabled by hardware) as system clock source after
  *           startup from Reset, wakeup from STOP and STANDBY mode, or in case
  *           of failure of the HSE used directly or indirectly as system clock
  *           (if the Clock Security System CSS is enabled).
  * @note     MSI can not be stopped if it is used as system clock source.
  *           In this case, you have to select another source of the system
  *           clock then stop the MSI.
  * @note     After enabling the MSI, the application software should wait on
  *           MSIRDY flag to be set indicating that MSI clock is stable and can
  *           be used as system clock source.
  * @note   When the MSI is stopped, MSIRDY flag goes low after 6 MSI oscillator
  *         clock cycles.
  */
#define __HAL_RCC_MSI_ENABLE()  SET_BIT(RCC->CR, RCC_CR_MSION)
#define __HAL_RCC_MSI_DISABLE() CLEAR_BIT(RCC->CR, RCC_CR_MSION)

/** @brief  Macro to adjust the Internal High Speed oscillator (HSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  * @param  __HSICalibrationValue__: specifies the calibration trimming value.
  *         This parameter must be a number between 0 and 0x1F.
  */
#define __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(__HSICalibrationValue__) (MODIFY_REG(RCC->ICSCR,\
        RCC_ICSCR_HSITRIM, (uint32_t)(__HSICalibrationValue__) << 8))

/** @brief  Macro Adjusts the Internal Multi Speed oscillator (MSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal MSI RC.
  *         Refer to the Application Note AN3300 for more details on how to  
  *         calibrate the MSI.
  * @param  __MSICalibrationValue__: specifies the calibration trimming value.
  *         This parameter must be a number between 0 and 0xFF.
  */
#define __HAL_RCC_MSI_CALIBRATIONVALUE_ADJUST(__MSICalibrationValue__) (MODIFY_REG(RCC->ICSCR,\
        RCC_ICSCR_MSITRIM, (uint32_t)(__MSICalibrationValue__) << 24))

/**
  * @brief  Macro to configures the Internal Multi Speed oscillator (MSI) clock range.
  * @note     After restart from Reset or wakeup from STANDBY, the MSI clock is 
  *           around 2.097 MHz. The MSI clock does not change after wake-up from
  *           STOP mode.
  * @note    The MSI clock range can be modified on the fly.
  * @param  RCC_MSIRange: specifies the MSI Clock range.
  *   This parameter must be one of the following values:
  *     @arg RCC_MSIRANGE_0: MSI clock is around 65.536 KHz
  *     @arg RCC_MSIRANGE_1: MSI clock is around 131.072 KHz
  *     @arg RCC_MSIRANGE_2: MSI clock is around 262.144 KHz
  *     @arg RCC_MSIRANGE_3: MSI clock is around 524.288 KHz
  *     @arg RCC_MSIRANGE_4: MSI clock is around 1.048 MHz
  *     @arg RCC_MSIRANGE_5: MSI clock is around 2.097 MHz (default after Reset or wake-up from STANDBY)
  *     @arg RCC_MSIRANGE_6: MSI clock is around 4.194 MHz
  */
#define __HAL_RCC_MSI_RANGE_CONFIG(__RCC_MSIRange__) (MODIFY_REG(RCC->ICSCR,\
        RCC_ICSCR_MSIRANGE, (uint32_t)(__RCC_MSIRange__) ))

/** @brief  Macros to enable or disable the Internal Low Speed oscillator (LSI).
  * @note   After enabling the LSI, the application software should wait on 
  *         LSIRDY flag to be set indicating that LSI clock is stable and can
  *         be used to clock the IWDG and/or the RTC.
  * @note   LSI can not be disabled if the IWDG is running.
  * @note   When the LSI is stopped, LSIRDY flag goes low after 6 LSI oscillator
  *         clock cycles. 
  */
#define __HAL_RCC_LSI_ENABLE() SET_BIT(RCC->CSR, RCC_CSR_LSION)
#define __HAL_RCC_LSI_DISABLE() CLEAR_BIT(RCC->CSR, RCC_CSR_LSION)

/**
  * @brief  Macro to configure the External High Speed oscillator (HSE).
  * @note   After enabling the HSE (RCC_HSE_ON or RCC_HSE_Bypass), the application
  *         software should wait on HSERDY flag to be set indicating that HSE clock
  *         is stable and can be used to clock the PLL and/or system clock.
  * @note   HSE state can not be changed if it is used directly or through the
  *         PLL as system clock. In this case, you have to select another source
  *         of the system clock then change the HSE state (ex. disable it).
  * @note   The HSE is stopped by hardware when entering STOP and STANDBY modes.  
  * @note   This function reset the CSSON bit, so if the clock security system(CSS)
  *         was previously enabled you have to enable it again after calling this
  *         function.    
  * @param  __STATE__: specifies the new state of the HSE.
  *         This parameter can be one of the following values:
  *            @arg RCC_HSE_OFF: turn OFF the HSE oscillator, HSERDY flag goes low after
  *                              6 HSE oscillator clock cycles.
  *            @arg RCC_HSE_ON: turn ON the HSE oscillator.
  *            @arg RCC_HSE_BYPASS: HSE oscillator bypassed with external clock.
  */
#define __HAL_RCC_HSE_CONFIG(__STATE__) \
                    do {                                     \
                      CLEAR_BIT(RCC->CR, RCC_CR_HSEON);      \
                      if((__STATE__) == RCC_HSE_ON)          \
                      {                                      \
                        CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);   \
                        SET_BIT(RCC->CR, RCC_CR_HSEON);      \
                      }                                      \
                      else if((__STATE__) == RCC_HSE_BYPASS) \
                      {                                      \
                        SET_BIT(RCC->CR, RCC_CR_HSEBYP);     \
                        SET_BIT(RCC->CR, RCC_CR_HSEON);      \
                      }                                      \
                      else                                   \
                      {                                      \
                        CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);   \
                      }                                      \
                    } while(0)
                      
/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE).
  * @note   As the LSE is in the Backup domain and write access is denied to
  *         this domain after reset, you have to enable write access using 
  *         HAL_PWR_EnableBkUpAccess() function before to configure the LSE
  *         (to be done once after reset).  
  * @note   After enabling the LSE (RCC_LSE_ON or RCC_LSE_BYPASS), the application
  *         software should wait on LSERDY flag to be set indicating that LSE clock
  *         is stable and can be used to clock the RTC.
  * @param  __STATE__: specifies the new state of the LSE.
  *         This parameter can be one of the following values:
  *            @arg RCC_LSE_OFF: turn OFF the LSE oscillator, LSERDY flag goes low after
  *                              6 LSE oscillator clock cycles.
  *            @arg RCC_LSE_ON: turn ON the LSE oscillator.
  *            @arg RCC_LSE_BYPASS: LSE oscillator bypassed with external clock.
  */
#define __HAL_RCC_LSE_CONFIG(__STATE__) \
                    do {                                       \
                      if((__STATE__) == RCC_LSE_ON)            \
                      {                                        \
                        SET_BIT(RCC->CSR, RCC_CSR_LSEON);      \
                      }                                        \
                      else if((__STATE__) == RCC_LSE_OFF)      \
                      {                                        \
                        CLEAR_BIT(RCC->CSR, RCC_CSR_LSEON);    \
                      }                                        \
                      else if((__STATE__) == RCC_LSE_BYPASS)   \
                      {                                        \
                        CLEAR_BIT(RCC->CSR, RCC_CSR_LSEON);    \
                        SET_BIT(RCC->CSR, RCC_CSR_LSEBYP);     \
                        SET_BIT(RCC->CSR, RCC_CSR_LSEON);      \
                      }                                        \
                      else                                     \
                      {                                        \
                        CLEAR_BIT(RCC->CSR, RCC_CSR_LSEON);    \
                        CLEAR_BIT(RCC->CSR, RCC_CSR_LSEBYP);   \
                      }                                        \
                    } while(0)

/** @brief  Macros to enable or disable the the RTC clock.
  * @note   These macros must be used only after the RTC clock source was selected.
  */
#define __HAL_RCC_RTC_ENABLE() SET_BIT(RCC->CSR, RCC_CSR_RTCEN)
#define __HAL_RCC_RTC_DISABLE() CLEAR_BIT(RCC->CSR, RCC_CSR_RTCEN)

/**
  * @brief  Configures  or  Get the RTC and LCD clock (RTCCLK / LCDCLK).
  * @note     As the RTC clock configuration bits are in the RTC domain and write
  *           access is denied to this domain after reset, you have to enable write
  *           access using PWR_RTCAccessCmd(ENABLE) function before to configure
  *           the RTC clock source (to be done once after reset).    
  * @note     Once the RTC clock is configured it cannot be changed unless the RTC
  *           is reset using RCC_RTCResetCmd function, or by a Power On Reset (POR)
  * @note     The RTC clock (RTCCLK) is used also to clock the LCD (LCDCLK).
  *
  * @param  RCC_RTCCLKSource: specifies the RTC clock source.
  *   This parameter can be one of the following values:
  *     @arg RCC_RTCCLKSOURCE_LSE: LSE selected as RTC clock
  *     @arg RCC_RTCCLKSOURCE_LSI: LSI selected as RTC clock
  *     @arg RCC_RTCCLKSOURCE_HSE_DIV2: HSE divided by 2 selected as RTC clock
  *     @arg RCC_RTCCLKSOURCE_HSE_DIV4: HSE divided by 4 selected as RTC clock
  *     @arg RCC_RTCCLKSOURCE_HSE_DIV8: HSE divided by 8 selected as RTC clock
  *     @arg RCC_RTCCLKSOURCE_HSE_DIV16: HSE divided by 16 selected as RTC clock
  *
  * @note     If the LSE or LSI is used as RTC clock source, the RTC continues to
  *           work in STOP and STANDBY modes, and can be used as wakeup source.
  *           However, when the HSE clock is used as RTC clock source, the RTC
  *           cannot be used in STOP and STANDBY modes.          
  * @note     The maximum input clock frequency for RTC is 1MHz (when using HSE as
  *           RTC clock source).
  */
#define __HAL_RCC_RTC_CLKPRESCALER(__RTCCLKSource__) (((__RTCCLKSource__) & RCC_CSR_RTCSEL) == RCC_CSR_RTCSEL) ?    \
                                                 MODIFY_REG(RCC->CR, RCC_CR_RTCPRE, ((__RTCCLKSource__) & 0xFFFCFFFF)) : CLEAR_BIT(RCC->CR, RCC_CR_RTCPRE)

#define __HAL_RCC_RTC_CONFIG(__RTCCLKSource__) do { __HAL_RCC_RTC_CLKPRESCALER(__RTCCLKSource__);    \
                                                   MODIFY_REG( RCC->CSR, RCC_CSR_RTCSEL, (uint32_t)(__RTCCLKSource__));  \
                                                   } while (0)

#define  __HAL_RCC_GET_RTC_SOURCE() ((uint32_t)(READ_BIT(RCC->CSR, RCC_CSR_RTCSEL)))

/** @brief  Macros to force or release the Backup domain reset.
  * @note   This function resets the RTC peripheral (including the backup registers)
  *         and the RTC clock source selection in RCC_CSR register.
  * @note   The BKPSRAM is not affected by this reset.   
  */
#define __HAL_RCC_BACKUPRESET_FORCE()  SET_BIT(RCC->CSR, RCC_CSR_RTCRST) 
#define __HAL_RCC_BACKUPRESET_RELEASE() CLEAR_BIT(RCC->CSR, RCC_CSR_RTCRST) 

/** @brief  Macros to enable or disable the main PLL.
  * @note   After enabling the main PLL, the application software should wait on 
  *         PLLRDY flag to be set indicating that PLL clock is stable and can
  *         be used as system clock source.
  * @note   The main PLL can not be disabled if it is used as system clock source
  * @note   The main PLL is disabled by hardware when entering STOP and STANDBY modes.
  */
#define __HAL_RCC_PLL_ENABLE() SET_BIT(RCC->CR, RCC_CR_PLLON)
#define __HAL_RCC_PLL_DISABLE() CLEAR_BIT(RCC->CR, RCC_CR_PLLON)

/** @brief  Macro to configure the main PLL clock source, multiplication and division factors.
  * @note   This function must be used only when the main PLL is disabled.
  * @param  __RCC_PLLSource__: specifies the PLL entry clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_PLLSOURCE_HSI: HSI oscillator clock selected as PLL clock entry
  *            @arg RCC_PLLSOURCE_HSE: HSE oscillator clock selected as PLL clock entry
  * @param  __PLLMUL__: specifies the multiplication factor to generate the PLL VCO clock
  *         This parameter must be one of the following values:
  *            @arg RCC_CFGR_PLLMUL3: PLLVCO = PLL clock entry x 3
  *            @arg RCC_CFGR_PLLMUL4: PLLVCO = PLL clock entry x 4
  *            @arg RCC_CFGR_PLLMUL6: PLLVCO = PLL clock entry x 6
  *            @arg RCC_CFGR_PLLMUL8: PLLVCO = PLL clock entry x 8
  *            @arg RCC_CFGR_PLLMUL12: PLLVCO = PLL clock entry x 12
  *            @arg RCC_CFGR_PLLMUL16: PLLVCO = PLL clock entry x 16
  *            @arg RCC_CFGR_PLLMUL24: PLLVCO = PLL clock entry x 24  
  *            @arg RCC_CFGR_PLLMUL32: PLLVCO = PLL clock entry x 32
  *            @arg RCC_CFGR_PLLMUL48: PLLVCO = PLL clock entry x 48
  * @note   The PLL VCO clock frequency must not exceed 96 MHz when the product is in
  *         Range 1, 48 MHz when the product is in Range 2 and 24 MHz when the product is
  *         in Range 3.
  * @param  __PLLDIV__: specifies the PLL output clock division from PLL VCO clock
  *         This parameter must be one of the following values:
  *            @arg RCC_PLLDIV_2: PLL clock output = PLLVCO / 2
  *            @arg RCC_PLLDIV_3: PLL clock output = PLLVCO / 3
  *            @arg RCC_PLLDIV_4: PLL clock output = PLLVCO / 4
  */

#define __HAL_RCC_PLL_CONFIG(__RCC_PLLSource__ , __PLLMUL__ ,__PLLDIV__ ) \
            MODIFY_REG(RCC->CFGR, RCC_CFGR_PLLMUL | RCC_CFGR_PLLDIV | RCC_CFGR_PLLSRC, (uint32_t)((__PLLMUL__)| (__PLLDIV__)| (__RCC_PLLSource__)))

/** @brief  Macro to get the clock source used as system clock.
  * @retval The clock source used as system clock. The returned value can be one
  *         of the following:
  *              - RCC_CFGR_SWS_HSI: HSI used as system clock.
  *              - RCC_CFGR_SWS_HSE: HSE used as system clock.
  *              - RCC_CFGR_SWS_PLL: PLL used as system clock.
  */
#define __HAL_RCC_GET_SYSCLK_SOURCE() ((uint32_t)(RCC->CFGR & RCC_CFGR_SWS))

/** @brief  Macro to get the oscillator used as PLL clock source.
  * @retval The oscillator used as PLL clock source. The returned value can be one
  *         of the following:
  *              - RCC_PLLSOURCE_HSI: HSI oscillator is used as PLL clock source.
  *              - RCC_PLLSOURCE_HSE: HSE oscillator is used as PLL clock source.
  */
#define __HAL_RCC_GET_PLL_OSCSOURCE() ((uint32_t)(RCC->CFGR & RCC_CFGR_PLLSRC))

/** @defgroup RCC_Flags_Interrupts_Management
  * @brief macros to manage the specified RCC Flags and interrupts.
  * @{
  */

/** @brief  Enable RCC interrupt (Perform Byte access to RCC_CIER[0:7] bits to enable
  *         the selected interrupts).
  * @note   The CSS interrupt doesn't have an enable bit; once the CSS is enabled
  *         and if the HSE clock fails, the CSS interrupt occurs and an NMI is
  *         automatically generated. The NMI will be executed indefinitely, and 
  *         since NMI has higher priority than any other IRQ (and main program)
  *         the application will be stacked in the NMI ISR unless the CSS interrupt
  *         pending bit is cleared.            
  * @param  __INTERRUPT__: specifies the RCC interrupt sources to be enabled.
  *         This parameter can be any combination of the following values:
  *     @arg RCC_IT_LSIRDY: LSI ready interrupt
  *     @arg RCC_IT_LSERDY: LSE ready interrupt
  *     @arg RCC_IT_HSIRDY: HSI ready interrupt
  *     @arg RCC_IT_HSERDY: HSE ready interrupt
  *     @arg RCC_IT_PLLRDY: PLL ready interrupt
  *     @arg RCC_IT_MSIRDY: MSI ready interrupt
  *     @arg RCC_IT_LSECSS: LSE CSS interrupt  
  *     @arg RCC_IT_HSI48RDY: HSI48 ready interrupt   
  */
#define __HAL_RCC_ENABLE_IT(__INTERRUPT__) (RCC->CIER |= (__INTERRUPT__))

/** @brief Disable RCC interrupt (Perform Byte access to RCC_CIER[0:7] bits to disable 
  *        the selected interrupts).
  * @note   The CSS interrupt doesn't have an enable bit; once the CSS is enabled
  *         and if the HSE clock fails, the CSS interrupt occurs and an NMI is
  *         automatically generated. The NMI will be executed indefinitely, and 
  *         since NMI has higher priority than any other IRQ (and main program)
  *         the application will be stacked in the NMI ISR unless the CSS interrupt
  *         pending bit is cleared.
  * @param  __INTERRUPT__: specifies the RCC interrupt sources to be disabled.
  *         This parameter can be any combination of the following values:
  *     @arg RCC_IT_LSIRDY: LSI ready interrupt
  *     @arg RCC_IT_LSERDY: LSE ready interrupt
  *     @arg RCC_IT_HSIRDY: HSI ready interrupt
  *     @arg RCC_IT_HSERDY: HSE ready interrupt
  *     @arg RCC_IT_PLLRDY: PLL ready interrupt
  *     @arg RCC_IT_MSIRDY: MSI ready interrupt
  *     @arg RCC_IT_HSI48RDY: HSI48 ready interrupt   
  *     @arg RCC_IT_LSECSS: LSE CSS interrupt  

  */
#define __HAL_RCC_DISABLE_IT(__INTERRUPT__) (RCC->CIER &= ~(__INTERRUPT__))

/** @brief  Clear the RCC's interrupt pending bits (Perform Byte access to RCC_CIR[23:16]
  *         bits to clear the selected interrupt pending bits.
  * @param  __INTERRUPT__: specifies the interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *     @arg RCC_IT_LSIRDY: LSI ready interrupt
  *     @arg RCC_IT_LSERDY: LSE ready interrupt
  *     @arg RCC_IT_HSIRDY: HSI ready interrupt
  *     @arg RCC_IT_HSERDY: HSE ready interrupt
  *     @arg RCC_IT_PLLRDY: PLL ready interrupt
  *     @arg RCC_IT_MSIRDY: MSI ready interrupt
  *     @arg RCC_IT_HSI48RDY: HSI48 ready interrupt   
  *     @arg RCC_IT_LSECSS: LSE CSS interrupt
  *     @arg RCC_IT_CSS: Clock Security System interrupt
  */
 #define __HAL_RCC_CLEAR_IT(__INTERRUPT__) (RCC->CICR = (__INTERRUPT__))

/** @brief  Check the RCC's interrupt has occurred or not.
  * @param  __INTERRUPT__: specifies the RCC interrupt source to check.
  *         This parameter can be one of the following values:
  *     @arg RCC_IT_LSIRDY: LSI ready interrupt
  *     @arg RCC_IT_LSERDY: LSE ready interrupt  
  *     @arg RCC_IT_HSIRDY: HSI ready interrupt
  *     @arg RCC_IT_HSERDY: HSE ready interrupt
  *     @arg RCC_IT_PLLRDY: PLL ready interrupt
  *     @arg RCC_IT_MSIRDY: MSI ready interrupt
  *     @arg RCC_IT_LSECSS: LSE CSS interrupt 
  *     @arg RCC_IT_CSS: Clock Security System interrupt
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_IT_SOURCE(__INTERRUPT__) ((RCC->CIFR & (__INTERRUPT__)) == (__INTERRUPT__))

/** @brief Set RMVF bit to clear the reset flags.
  *         The reset flags are: RCC_FLAG_OBLRST, RCC_FLAG_PINRST, RCC_FLAG_PORRST, 
  *         RCC_FLAG_SFTRST, RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST, RCC_FLAG_LPWRRST.
  */
#define __HAL_RCC_CLEAR_RESET_FLAGS() (RCC->CSR |= RCC_CSR_RMVF)

/** @brief  Check RCC flag is set or not.
  * @param  __FLAG__: specifies the flag to check.
  *         This parameter can be one of the following values:
  *     @arg RCC_FLAG_HSIRDY: HSI oscillator clock ready
  *     @arg RCC_FLAG_MSIRDY: MSI oscillator clock ready  
  *     @arg RCC_FLAG_HSERDY: HSE oscillator clock ready
  *     @arg RCC_FLAG_PLLRDY: PLL clock ready
  *     @arg RCC_FLAG_LSECSS: LSE oscillator clock CSS detected  
  *     @arg RCC_FLAG_LSERDY: LSE oscillator clock ready
  *     @arg RCC_FLAG_LSIRDY: LSI oscillator clock ready
  *     @arg RCC_FLAG_FWRST: Firewall reset
  *     @arg RCC_FLAG_OBLRST: Option Byte Loader (OBL) reset 
  *     @arg RCC_FLAG_PINRST: Pin reset
  *     @arg RCC_FLAG_PORRST: POR/PDR reset
  *     @arg RCC_FLAG_SFTRST: Software reset
  *     @arg RCC_FLAG_IWDGRST: Independent Watchdog reset
  *     @arg RCC_FLAG_WWDGRST: Window Watchdog reset
  *     @arg RCC_FLAG_LPWRRST: Low Power reset
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define RCC_FLAG_MASK  ((uint8_t)0x1F)
#define __HAL_RCC_GET_FLAG(__FLAG__) (((((((__FLAG__) >> 5) == 1)? RCC->CR :((((__FLAG__) >> 5) == 2) ? RCC->CSR :((((__FLAG__) >> 5) == 3)? \
              RCC->CRRCR :RCC->CIFR))) & ((uint32_t)1 << ((__FLAG__) & RCC_FLAG_MASK))) != 0 ) ? 1 : 0 )  

/**
  * @}
  */

/**
 * @}
 */

/* Include RCC HAL Extension module */
#include "stm32l0xx_hal_rcc_ex.h"

/** @defgroup RCC_Exported_Functions RCC Exported Functions
  * @{
  */

/** @defgroup RCC_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
void HAL_RCC_DeInit(void);
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency);
/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group2 Peripheral Control functions
  * @{
  */
void     HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
void     HAL_RCC_EnableCSS(void);
uint32_t HAL_RCC_GetSysClockFreq(void);
uint32_t HAL_RCC_GetHCLKFreq(void);
uint32_t HAL_RCC_GetPCLK1Freq(void);
uint32_t HAL_RCC_GetPCLK2Freq(void);
void     HAL_RCC_GetOscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
void     HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t *pFLatency);
/* CSS NMI IRQ handler */
void HAL_RCC_NMI_IRQHandler(void);

/* User Callbacks in non blocking mode (IT mode) */ 
void HAL_RCC_CSSCallback(void);
/**
  * @}
  */
  
/**
  * @}
  */ 
  
/**
  * @}
  */ 

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32l0xx_HAL_RCC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

