/**
  ******************************************************************************
  * @file    stm32l1xx_hal_rcc.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   Header file of RCC HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
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
#ifndef __STM32L1xx_HAL_RCC_H
#define __STM32L1xx_HAL_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 

/** @defgroup RCC_Exported_Types RCC Exported Types
  * @{
  */

/** 
  * @brief  RCC PLL configuration structure definition  
  */
typedef struct
{
  uint32_t PLLState;     /*!< The new state of the PLL.
                              This parameter can be a value of @ref RCC_PLL_Config */

  uint32_t PLLSource;    /*!< PLLSource: PLL entry clock source.
                              This parameter must be a value of @ref RCC_PLL_Clock_Source */           

  uint32_t PLLMUL;         /*!< PLLMUL: Multiplication factor for PLL VCO input clock
                              This parameter must be a value of @ref RCC_PLL_Multiplication_Factor*/        

  uint32_t PLLDIV;         /*!< PLLDIV: Division factor for PLL VCO input clock
                              This parameter must be a value of @ref RCC_PLL_Division_Factor*/        
} RCC_PLLInitTypeDef;
   
/** 
  * @brief  RCC Internal/External Oscillator (HSE, HSI, LSE and LSI) configuration structure definition  
  */
typedef struct
{
  uint32_t OscillatorType;       /*!< The oscillators to be configured.
                                       This parameter can be a value of @ref RCC_Oscillator_Type */

  uint32_t HSEState;              /*!< The new state of the HSE.
                                       This parameter can be a value of @ref RCC_HSE_Config */
                          
  uint32_t LSEState;              /*!<  The new state of the LSE.
                                        This parameter can be a value of @ref RCC_LSE_Config */
                                          
  uint32_t HSIState;              /*!< The new state of the HSI.
                                       This parameter can be a value of @ref RCC_HSI_Config */

  uint32_t HSICalibrationValue;   /*!< The HSI calibration trimming value (default is RCC_HSICALIBRATION_DEFAULT).
                                       This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x1F */
                               
  uint32_t LSIState;              /*!<  The new state of the LSI.
                                        This parameter can be a value of @ref RCC_LSI_Config */

  uint32_t MSIState;              /*!<  The new state of the MSI.
                                        This parameter can be a value of @ref RCC_MSI_Config */

  uint32_t MSICalibrationValue;   /*!< The MSI calibration trimming value. (default is RCC_MSICALIBRATION_DEFAULT).
                                       This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF */
                               
  uint32_t MSIClockRange;         /*!< The MSI  frequency  range.
                                        This parameter can be a value of @ref RCC_MSI_Clock_Range */

  RCC_PLLInitTypeDef PLL;         /*!< PLL structure parameters */      

} RCC_OscInitTypeDef;

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

} RCC_ClkInitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_Exported_Constants RCC Exported Constants
  * @{
  */
#define DBP_TIMEOUT_VALUE          ((uint32_t)100)
#define LSE_TIMEOUT_VALUE          LSE_STARTUP_TIMEOUT

/** @defgroup RCC_BitAddress_AliasRegion RCC BitAddress AliasRegion
  * @brief RCC registers bit address in the alias region
  * @{
  */
#define RCC_OFFSET                (RCC_BASE - PERIPH_BASE)
#define RCC_CR_OFFSET             0x00
#define RCC_CFGR_OFFSET           0x08
#define RCC_CIR_OFFSET            0x0C
#define RCC_CSR_OFFSET            0x34
#define RCC_CR_OFFSET_BB          (RCC_OFFSET + RCC_CR_OFFSET)
#define RCC_CFGR_OFFSET_BB        (RCC_OFFSET + RCC_CFGR_OFFSET)
#define RCC_CIR_OFFSET_BB         (RCC_OFFSET + RCC_CIR_OFFSET)
#define RCC_CSR_OFFSET_BB         (RCC_OFFSET + RCC_CSR_OFFSET)

/* --- CR Register ---*/
/* Alias word address of HSION bit */
#define HSION_BITNUMBER           POSITION_VAL(RCC_CR_HSION)
#define CR_HSION_BB               ((uint32_t)(PERIPH_BB_BASE + (RCC_CR_OFFSET_BB * 32) + (HSION_BITNUMBER * 4)))
/* Alias word address of MSION bit */
#define MSION_BITNUMBER           POSITION_VAL(RCC_CR_MSION)
#define CR_MSION_BB               ((uint32_t)(PERIPH_BB_BASE + (RCC_CR_OFFSET_BB * 32) + (MSION_BITNUMBER * 4)))
/* Alias word address of HSEON bit */
#define HSEON_BITNUMBER           POSITION_VAL(RCC_CR_HSEON)
#define CR_HSEON_BB               ((uint32_t)(PERIPH_BB_BASE + (RCC_CR_OFFSET_BB * 32) + (HSEON_BITNUMBER * 4)))
/* Alias word address of CSSON bit */
#define CSSON_BITNUMBER           POSITION_VAL(RCC_CR_CSSON)
#define CR_CSSON_BB               ((uint32_t)(PERIPH_BB_BASE + (RCC_CR_OFFSET_BB * 32) + (CSSON_BITNUMBER * 4)))
/* Alias word address of PLLON bit */
#define PLLON_BITNUMBER           POSITION_VAL(RCC_CR_PLLON)
#define CR_PLLON_BB               ((uint32_t)(PERIPH_BB_BASE + (RCC_CR_OFFSET_BB * 32) + (PLLON_BITNUMBER * 4)))

/* --- CSR Register ---*/
/* Alias word address of LSION bit */
#define LSION_BITNUMBER           POSITION_VAL(RCC_CSR_LSION)
#define CSR_LSION_BB              ((uint32_t)(PERIPH_BB_BASE + (RCC_CSR_OFFSET_BB * 32) + (LSION_BITNUMBER * 4)))

/* Alias word address of LSEON bit */
#define LSEON_BITNUMBER           POSITION_VAL(RCC_CSR_LSEON)
#define CSR_LSEON_BB              ((uint32_t)(PERIPH_BB_BASE + (RCC_CSR_OFFSET_BB * 32) + (LSEON_BITNUMBER * 4)))

/* Alias word address of LSEON bit */
#define LSEBYP_BITNUMBER          POSITION_VAL(RCC_CSR_LSEBYP)
#define CSR_LSEBYP_BB             ((uint32_t)(PERIPH_BB_BASE + (RCC_CSR_OFFSET_BB * 32) + (LSEBYP_BITNUMBER * 4)))

/* Alias word address of RTCEN bit */
#define RTCEN_BITNUMBER           POSITION_VAL(RCC_CSR_RTCEN)
#define CSR_RTCEN_BB              ((uint32_t)(PERIPH_BB_BASE + (RCC_CSR_OFFSET_BB * 32) + (RTCEN_BITNUMBER * 4)))

/* Alias word address of RTCRST bit */
#define RTCRST_BITNUMBER          POSITION_VAL(RCC_CSR_RTCRST)
#define CSR_RTCRST_BB             ((uint32_t)(PERIPH_BB_BASE + (RCC_CSR_OFFSET_BB * 32) + (RTCRST_BITNUMBER * 4)))

/* CR register byte 2 (Bits[23:16]) base address */
#define CR_BYTE2_ADDRESS          ((uint32_t)(RCC_BASE + RCC_CR_OFFSET + 0x02))

/* CIR register byte 1 (Bits[15:8]) base address */
#define CIR_BYTE1_ADDRESS         ((uint32_t)(RCC_BASE + RCC_CIR_OFFSET + 0x01))

/* CIR register byte 2 (Bits[23:16]) base address */
#define CIR_BYTE2_ADDRESS         ((uint32_t)(RCC_BASE + RCC_CIR_OFFSET + 0x02))

/**
  * @}
  */

/** @defgroup RCC_PLL_Clock_Source RCC PLL Clock Source
  * @{
  */

#define RCC_PLLSOURCE_HSI           RCC_CFGR_PLLSRC_HSI
#define RCC_PLLSOURCE_HSE           RCC_CFGR_PLLSRC_HSE
 
#define IS_RCC_PLLSOURCE(__SOURCE__) (((__SOURCE__) == RCC_PLLSOURCE_HSI) || \
                                      ((__SOURCE__) == RCC_PLLSOURCE_HSE))
/**
  * @}
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

#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__) (((__OSCILLATOR__) == RCC_OSCILLATORTYPE_NONE)                           || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_MSI) == RCC_OSCILLATORTYPE_MSI))
/**
  * @}
  */

/** @defgroup RCC_HSE_Config RCC HSE Config
  * @{
  */
#define RCC_HSE_OFF                      ((uint32_t)0x00000000)
#define RCC_HSE_ON                       ((uint32_t)0x00000001)
#define RCC_HSE_BYPASS                   ((uint32_t)0x00000005)

#define IS_RCC_HSE(__HSE__) (((__HSE__) == RCC_HSE_OFF) || ((__HSE__) == RCC_HSE_ON) || \
                             ((__HSE__) == RCC_HSE_BYPASS))
/**
  * @}
  */

/** @defgroup RCC_LSE_Config RCC LSE Config
  * @{
  */
#define RCC_LSE_OFF                      ((uint32_t)0x00000000)
#define RCC_LSE_ON                       ((uint32_t)0x00000001)
#define RCC_LSE_BYPASS                   ((uint32_t)0x00000005)

#define IS_RCC_LSE(__LSE__) (((__LSE__) == RCC_LSE_OFF) || ((__LSE__) == RCC_LSE_ON) || \
                             ((__LSE__) == RCC_LSE_BYPASS))
/**
  * @}
  */

/** @defgroup RCC_HSI_Config RCC HSI Config
  * @{
  */
#define RCC_HSI_OFF                      ((uint32_t)0x00000000)
#define RCC_HSI_ON                       ((uint32_t)0x00000001)

#define IS_RCC_HSI(__HSI__) (((__HSI__) == RCC_HSI_OFF) || ((__HSI__) == RCC_HSI_ON))

#define RCC_HSICALIBRATION_DEFAULT       ((uint32_t)0x10)   /* Default HSI calibration trimming value */

#define IS_RCC_CALIBRATION_VALUE(__VALUE__) ((__VALUE__) <= 0x1F)
/**
  * @}
  */

/** @defgroup RCC_MSI_Clock_Range RCC MSI Clock Range
  * @{
  */

#define RCC_MSIRANGE_0                   ((uint32_t)RCC_ICSCR_MSIRANGE_0) /*!< MSI = 65.536 KHz  */
#define RCC_MSIRANGE_1                   ((uint32_t)RCC_ICSCR_MSIRANGE_1) /*!< MSI = 131.072 KHz */
#define RCC_MSIRANGE_2                   ((uint32_t)RCC_ICSCR_MSIRANGE_2) /*!< MSI = 262.144 KHz */
#define RCC_MSIRANGE_3                   ((uint32_t)RCC_ICSCR_MSIRANGE_3) /*!< MSI = 524.288 KHz */
#define RCC_MSIRANGE_4                   ((uint32_t)RCC_ICSCR_MSIRANGE_4) /*!< MSI = 1.048 MHz   */
#define RCC_MSIRANGE_5                   ((uint32_t)RCC_ICSCR_MSIRANGE_5) /*!< MSI = 2.097 MHz   */
#define RCC_MSIRANGE_6                   ((uint32_t)RCC_ICSCR_MSIRANGE_6) /*!< MSI = 4.194 MHz   */

#define IS_RCC_MSIRANGE(__RANGE__)  (((__RANGE__) == RCC_MSIRANGE_0) || \
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
#define RCC_LSI_OFF                      ((uint32_t)0x00000000)
#define RCC_LSI_ON                       ((uint32_t)0x00000001)

#define IS_RCC_LSI(__LSI__) (((__LSI__) == RCC_LSI_OFF) || ((__LSI__) == RCC_LSI_ON))
/**
  * @}
  */

    
/** @defgroup RCC_MSI_Config RCC MSI Config
  * @{
  */
#define RCC_MSI_OFF                      ((uint32_t)0x00000000)
#define RCC_MSI_ON                       ((uint32_t)0x00000001)

#define IS_RCC_MSI(__MSI__) (((__MSI__) == RCC_MSI_OFF) || ((__MSI__) == RCC_MSI_ON))

#define RCC_MSICALIBRATION_DEFAULT       ((uint32_t)0x00)   /* Default MSI calibration trimming value */

/**
  * @}
  */

/** @defgroup RCC_PLL_Config RCC PLL Config
  * @{
  */
#define RCC_PLL_NONE                      ((uint32_t)0x00000000)
#define RCC_PLL_OFF                       ((uint32_t)0x00000001)
#define RCC_PLL_ON                        ((uint32_t)0x00000002)

#define IS_RCC_PLL(__PLL__) (((__PLL__) == RCC_PLL_NONE) || ((__PLL__) == RCC_PLL_OFF) || \
                             ((__PLL__) == RCC_PLL_ON))
/**
  * @}
  */

/** @defgroup RCC_PLL_Division_Factor RCC PLL Division Factor
  * @{
  */

#define RCC_PLL_DIV2                    RCC_CFGR_PLLDIV2
#define RCC_PLL_DIV3                    RCC_CFGR_PLLDIV3
#define RCC_PLL_DIV4                    RCC_CFGR_PLLDIV4

#define IS_RCC_PLL_DIV(__DIV__) (((__DIV__) == RCC_PLL_DIV2) || \
                                 ((__DIV__) == RCC_PLL_DIV3) || ((__DIV__) == RCC_PLL_DIV4))

/**
  * @}
  */

/** @defgroup RCC_PLL_Multiplication_Factor RCC PLL Multiplication Factor
  * @{
  */

#define RCC_PLL_MUL3                    RCC_CFGR_PLLMUL3
#define RCC_PLL_MUL4                    RCC_CFGR_PLLMUL4
#define RCC_PLL_MUL6                    RCC_CFGR_PLLMUL6
#define RCC_PLL_MUL8                    RCC_CFGR_PLLMUL8
#define RCC_PLL_MUL12                   RCC_CFGR_PLLMUL12
#define RCC_PLL_MUL16                   RCC_CFGR_PLLMUL16
#define RCC_PLL_MUL24                   RCC_CFGR_PLLMUL24
#define RCC_PLL_MUL32                   RCC_CFGR_PLLMUL32
#define RCC_PLL_MUL48                   RCC_CFGR_PLLMUL48

#define IS_RCC_PLL_MUL(__MUL__) (((__MUL__) == RCC_PLL_MUL3)  || ((__MUL__) == RCC_PLL_MUL4)  || \
                                 ((__MUL__) == RCC_PLL_MUL6)  || ((__MUL__) == RCC_PLL_MUL8)  || \
                                 ((__MUL__) == RCC_PLL_MUL12) || ((__MUL__) == RCC_PLL_MUL16) || \
                                 ((__MUL__) == RCC_PLL_MUL24) || ((__MUL__) == RCC_PLL_MUL32) || \
                                 ((__MUL__) == RCC_PLL_MUL48))
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
#define RCC_SYSCLKSOURCE_MSI             ((uint32_t)RCC_CFGR_SW_MSI)
#define RCC_SYSCLKSOURCE_HSI             ((uint32_t)RCC_CFGR_SW_HSI)
#define RCC_SYSCLKSOURCE_HSE             ((uint32_t)RCC_CFGR_SW_HSE)
#define RCC_SYSCLKSOURCE_PLLCLK          ((uint32_t)RCC_CFGR_SW_PLL)

#define IS_RCC_SYSCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_SYSCLKSOURCE_MSI) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_HSI) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_HSE) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_PLLCLK))
/**
  * @}
  */ 

/** @defgroup RCC_AHB_Clock_Source RCC AHB Clock Source
  * @{
  */
#define RCC_SYSCLK_DIV1                  ((uint32_t)RCC_CFGR_HPRE_DIV1)
#define RCC_SYSCLK_DIV2                  ((uint32_t)RCC_CFGR_HPRE_DIV2)
#define RCC_SYSCLK_DIV4                  ((uint32_t)RCC_CFGR_HPRE_DIV4)
#define RCC_SYSCLK_DIV8                  ((uint32_t)RCC_CFGR_HPRE_DIV8)
#define RCC_SYSCLK_DIV16                 ((uint32_t)RCC_CFGR_HPRE_DIV16)
#define RCC_SYSCLK_DIV64                 ((uint32_t)RCC_CFGR_HPRE_DIV64)
#define RCC_SYSCLK_DIV128                ((uint32_t)RCC_CFGR_HPRE_DIV128)
#define RCC_SYSCLK_DIV256                ((uint32_t)RCC_CFGR_HPRE_DIV256)
#define RCC_SYSCLK_DIV512                ((uint32_t)RCC_CFGR_HPRE_DIV512)

#define IS_RCC_HCLK(__HCLK__) (((__HCLK__) == RCC_SYSCLK_DIV1) || ((__HCLK__) == RCC_SYSCLK_DIV2) || \
                               ((__HCLK__) == RCC_SYSCLK_DIV4) || ((__HCLK__) == RCC_SYSCLK_DIV8) || \
                               ((__HCLK__) == RCC_SYSCLK_DIV16) || ((__HCLK__) == RCC_SYSCLK_DIV64) || \
                               ((__HCLK__) == RCC_SYSCLK_DIV128) || ((__HCLK__) == RCC_SYSCLK_DIV256) || \
                               ((__HCLK__) == RCC_SYSCLK_DIV512))
/**
  * @}
  */ 
  
/** @defgroup RCC_APB1_APB2_Clock_Source RCC APB1 APB2 Clock Source
  * @{
  */
#define RCC_HCLK_DIV1                    ((uint32_t)RCC_CFGR_PPRE1_DIV1)
#define RCC_HCLK_DIV2                    ((uint32_t)RCC_CFGR_PPRE1_DIV2)
#define RCC_HCLK_DIV4                    ((uint32_t)RCC_CFGR_PPRE1_DIV4)
#define RCC_HCLK_DIV8                    ((uint32_t)RCC_CFGR_PPRE1_DIV8)
#define RCC_HCLK_DIV16                   ((uint32_t)RCC_CFGR_PPRE1_DIV16)

#define IS_RCC_PCLK(__PCLK__) (((__PCLK__) == RCC_HCLK_DIV1) || ((__PCLK__) == RCC_HCLK_DIV2) || \
                               ((__PCLK__) == RCC_HCLK_DIV4) || ((__PCLK__) == RCC_HCLK_DIV8) || \
                               ((__PCLK__) == RCC_HCLK_DIV16))
/**
  * @}
  */ 

/** @defgroup RCC_RTC_LCD_Clock_Source RCC RTC LCD Clock Source
  * @{
  */
#define RCC_RTCCLKSOURCE_LSE             ((uint32_t)RCC_CSR_RTCSEL_LSE)
#define RCC_RTCCLKSOURCE_LSI             ((uint32_t)RCC_CSR_RTCSEL_LSI)
#define RCC_RTCCLKSOURCE_HSE_DIV2        ((uint32_t)RCC_CSR_RTCSEL_HSE)
#define RCC_RTCCLKSOURCE_HSE_DIV4        ((uint32_t)(RCC_CR_RTCPRE_0 | RCC_CSR_RTCSEL_HSE))
#define RCC_RTCCLKSOURCE_HSE_DIV8        ((uint32_t)(RCC_CR_RTCPRE_1 | RCC_CSR_RTCSEL_HSE))
#define RCC_RTCCLKSOURCE_HSE_DIV16       ((uint32_t)(RCC_CR_RTCPRE | RCC_CSR_RTCSEL_HSE))
/**
  * @}
  */ 

/** @defgroup RCC_MCO_Index RCC MCO Index
  * @{
  */
#define RCC_MCO1                         ((uint32_t)0x00000000)
#define RCC_MCO                          RCC_MCO1

#define IS_RCC_MCO(__MCO__) (((__MCO__) == RCC_MCO))
/**
  * @}
  */

/** @defgroup RCC_MCOx_Clock_Prescaler RCC MCO1 Clock Prescaler
  * @{
  */
#define RCC_MCODIV_1                    ((uint32_t)RCC_CFGR_MCO_DIV1)
#define RCC_MCODIV_2                    ((uint32_t)RCC_CFGR_MCO_DIV2)
#define RCC_MCODIV_4                    ((uint32_t)RCC_CFGR_MCO_DIV4)
#define RCC_MCODIV_8                    ((uint32_t)RCC_CFGR_MCO_DIV8)
#define RCC_MCODIV_16                   ((uint32_t)RCC_CFGR_MCO_DIV16)

#define IS_RCC_MCODIV(__DIV__) (((__DIV__) == RCC_MCODIV_1) || ((__DIV__) == RCC_MCODIV_2) || \
                                ((__DIV__) == RCC_MCODIV_4) || ((__DIV__) == RCC_MCODIV_8) || \
                                ((__DIV__) == RCC_MCODIV_16)) 
/**
  * @}
  */ 

/** @defgroup RCC_MCO1_Clock_Source RCC MCO1 Clock Source
  * @{
  */
#define RCC_MCO1SOURCE_NOCLOCK           ((uint32_t)RCC_CFGR_MCO_NOCLOCK)
#define RCC_MCO1SOURCE_SYSCLK            ((uint32_t)RCC_CFGR_MCO_SYSCLK)
#define RCC_MCO1SOURCE_MSI               ((uint32_t)RCC_CFGR_MCO_MSI)
#define RCC_MCO1SOURCE_HSI               ((uint32_t)RCC_CFGR_MCO_HSI)
#define RCC_MCO1SOURCE_LSE               ((uint32_t)RCC_CFGR_MCO_LSE)
#define RCC_MCO1SOURCE_LSI               ((uint32_t)RCC_CFGR_MCO_LSI)
#define RCC_MCO1SOURCE_HSE               ((uint32_t)RCC_CFGR_MCO_HSE)
#define RCC_MCO1SOURCE_PLLCLK            ((uint32_t)RCC_CFGR_MCO_PLL)

#define IS_RCC_MCO1SOURCE(__SOURCE__) (((__SOURCE__) == RCC_MCO1SOURCE_SYSCLK) || ((__SOURCE__) == RCC_MCO1SOURCE_MSI) \
                                    || ((__SOURCE__) == RCC_MCO1SOURCE_HSI)    || ((__SOURCE__) == RCC_MCO1SOURCE_LSE) \
                                    || ((__SOURCE__) == RCC_MCO1SOURCE_LSI)    || ((__SOURCE__) == RCC_MCO1SOURCE_HSE) \
                                    || ((__SOURCE__) == RCC_MCO1SOURCE_PLLCLK) || ((__SOURCE__) == RCC_MCO1SOURCE_NOCLOCK))
/**
  * @}
  */

/** @defgroup RCC_Interrupt RCC Interrupt
  * @{
  */
#define RCC_IT_LSIRDY                    ((uint8_t)RCC_CIR_LSIRDYF)
#define RCC_IT_LSERDY                    ((uint8_t)RCC_CIR_LSERDYF)
#define RCC_IT_HSIRDY                    ((uint8_t)RCC_CIR_HSIRDYF)
#define RCC_IT_HSERDY                    ((uint8_t)RCC_CIR_HSERDYF)
#define RCC_IT_PLLRDY                    ((uint8_t)RCC_CIR_PLLRDYF)
#define RCC_IT_MSIRDY                    ((uint8_t)RCC_CIR_MSIRDYF)
#define RCC_IT_LSECSS                    ((uint8_t)RCC_CIR_LSECSS)
#define RCC_IT_CSS                       ((uint8_t)RCC_CIR_CSSF)
/**
  * @}
  */  
  
/** @defgroup RCC_Flag RCC Flag
  *        Elements values convention: 0XXYYYYYb
  *           - YYYYY  : Flag position in the register
  *           - XX  : Register index
  *                 - 01: CR register
  *                 - 11: CSR register
  * @{
  */
#define CR_REG_INDEX                     ((uint8_t)1)    
#define CSR_REG_INDEX                    ((uint8_t)3)

/* Flags in the CR register */
#define RCC_FLAG_HSIRDY                  ((uint8_t)((CR_REG_INDEX << 5) | POSITION_VAL(RCC_CR_HSIRDY)))
#define RCC_FLAG_MSIRDY                  ((uint8_t)((CR_REG_INDEX << 5) | POSITION_VAL(RCC_CR_MSIRDY)))
#define RCC_FLAG_HSERDY                  ((uint8_t)((CR_REG_INDEX << 5) | POSITION_VAL(RCC_CR_HSERDY)))
#define RCC_FLAG_PLLRDY                  ((uint8_t)((CR_REG_INDEX << 5) | POSITION_VAL(RCC_CR_PLLRDY)))

/* Flags in the CSR register */
#define RCC_FLAG_LSIRDY                  ((uint8_t)((CSR_REG_INDEX << 5) | POSITION_VAL(RCC_CSR_LSIRDY)))
#define RCC_FLAG_LSERDY                  ((uint8_t)((CSR_REG_INDEX << 5) | POSITION_VAL(RCC_CSR_LSERDY)))
#define RCC_FLAG_LSECSS                  ((uint8_t)((CSR_REG_INDEX << 5) | POSITION_VAL(RCC_CSR_LSECSSD)))
#define RCC_FLAG_RMV                     ((uint8_t)((CSR_REG_INDEX << 5) | POSITION_VAL(RCC_CSR_RMVF)))
#define RCC_FLAG_OBLRST                  ((uint8_t)((CSR_REG_INDEX << 5) | POSITION_VAL(RCC_CSR_OBLRSTF)))
#define RCC_FLAG_PINRST                  ((uint8_t)((CSR_REG_INDEX << 5) | POSITION_VAL(RCC_CSR_PINRSTF)))
#define RCC_FLAG_PORRST                  ((uint8_t)((CSR_REG_INDEX << 5) | POSITION_VAL(RCC_CSR_PORRSTF)))
#define RCC_FLAG_SFTRST                  ((uint8_t)((CSR_REG_INDEX << 5) | POSITION_VAL(RCC_CSR_SFTRSTF)))
#define RCC_FLAG_IWDGRST                 ((uint8_t)((CSR_REG_INDEX << 5) | POSITION_VAL(RCC_CSR_IWDGRSTF)))
#define RCC_FLAG_WWDGRST                 ((uint8_t)((CSR_REG_INDEX << 5) | POSITION_VAL(RCC_CSR_WWDGRSTF)))
#define RCC_FLAG_LPWRRST                 ((uint8_t)((CSR_REG_INDEX << 5) | POSITION_VAL(RCC_CSR_LPWRRSTF)))

#define RCC_FLAG_MASK                    ((uint8_t)0x1F)

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

/** @defgroup RCC_Peripheral_Clock_Enable_Disable RCC Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.   
  * @{
  */
#define __GPIOA_CLK_ENABLE()      (RCC->AHBENR |= (RCC_AHBENR_GPIOAEN))
#define __GPIOB_CLK_ENABLE()      (RCC->AHBENR |= (RCC_AHBENR_GPIOBEN))
#define __GPIOC_CLK_ENABLE()      (RCC->AHBENR |= (RCC_AHBENR_GPIOCEN))
#define __GPIOD_CLK_ENABLE()      (RCC->AHBENR |= (RCC_AHBENR_GPIODEN))
#define __GPIOH_CLK_ENABLE()      (RCC->AHBENR |= (RCC_AHBENR_GPIOHEN))

#define __CRC_CLK_ENABLE()        (RCC->AHBENR |= (RCC_AHBENR_CRCEN))
#define __FLITF_CLK_ENABLE()      (RCC->AHBENR |= (RCC_AHBENR_FLITFEN))
#define __DMA1_CLK_ENABLE()       (RCC->AHBENR |= (RCC_AHBENR_DMA1EN))

#define __GPIOA_CLK_DISABLE()     (RCC->AHBENR &= ~(RCC_AHBENR_GPIOAEN))
#define __GPIOB_CLK_DISABLE()     (RCC->AHBENR &= ~(RCC_AHBENR_GPIOBEN))
#define __GPIOC_CLK_DISABLE()     (RCC->AHBENR &= ~(RCC_AHBENR_GPIOCEN))
#define __GPIOD_CLK_DISABLE()     (RCC->AHBENR &= ~(RCC_AHBENR_GPIODEN))
#define __GPIOH_CLK_DISABLE()     (RCC->AHBENR &= ~(RCC_AHBENR_GPIOHEN))

#define __CRC_CLK_DISABLE()       (RCC->AHBENR &= ~(RCC_AHBENR_CRCEN))
#define __FLITF_CLK_DISABLE()     (RCC->AHBENR &= ~(RCC_AHBENR_FLITFEN))
#define __DMA1_CLK_DISABLE()      (RCC->AHBENR &= ~(RCC_AHBENR_DMA1EN))

/** @brief  Enable or disable the Low Speed APB (APB1) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it. 
  */
#define __TIM2_CLK_ENABLE()       (RCC->APB1ENR |= (RCC_APB1ENR_TIM2EN))
#define __TIM3_CLK_ENABLE()       (RCC->APB1ENR |= (RCC_APB1ENR_TIM3EN))
#define __TIM4_CLK_ENABLE()       (RCC->APB1ENR |= (RCC_APB1ENR_TIM4EN))
#define __TIM6_CLK_ENABLE()       (RCC->APB1ENR |= (RCC_APB1ENR_TIM6EN))
#define __TIM7_CLK_ENABLE()       (RCC->APB1ENR |= (RCC_APB1ENR_TIM7EN))
#define __WWDG_CLK_ENABLE()       (RCC->APB1ENR |= (RCC_APB1ENR_WWDGEN))
#define __SPI2_CLK_ENABLE()       (RCC->APB1ENR |= (RCC_APB1ENR_SPI2EN))
#define __USART2_CLK_ENABLE()     (RCC->APB1ENR |= (RCC_APB1ENR_USART2EN))
#define __USART3_CLK_ENABLE()     (RCC->APB1ENR |= (RCC_APB1ENR_USART3EN))
#define __I2C1_CLK_ENABLE()       (RCC->APB1ENR |= (RCC_APB1ENR_I2C1EN))
#define __I2C2_CLK_ENABLE()       (RCC->APB1ENR |= (RCC_APB1ENR_I2C2EN))
#define __USB_CLK_ENABLE()        (RCC->APB1ENR |= (RCC_APB1ENR_USBEN))
#define __PWR_CLK_ENABLE()        (RCC->APB1ENR |= (RCC_APB1ENR_PWREN))
#define __DAC_CLK_ENABLE()        (RCC->APB1ENR |= (RCC_APB1ENR_DACEN))
#define __COMP_CLK_ENABLE()       (RCC->APB1ENR |= (RCC_APB1ENR_COMPEN))

#define __TIM2_CLK_DISABLE()      (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM2EN))
#define __TIM3_CLK_DISABLE()      (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM3EN))
#define __TIM4_CLK_DISABLE()      (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM4EN))
#define __TIM6_CLK_DISABLE()      (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM6EN))
#define __TIM7_CLK_DISABLE()      (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM7EN))
#define __WWDG_CLK_DISABLE()      (RCC->APB1ENR &= ~(RCC_APB1ENR_WWDGEN))
#define __SPI2_CLK_DISABLE()      (RCC->APB1ENR &= ~(RCC_APB1ENR_SPI2EN))
#define __USART2_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_USART2EN))
#define __USART3_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_USART3EN))
#define __I2C1_CLK_DISABLE()      (RCC->APB1ENR &= ~(RCC_APB1ENR_I2C1EN))
#define __I2C2_CLK_DISABLE()      (RCC->APB1ENR &= ~(RCC_APB1ENR_I2C2EN))
#define __USB_CLK_DISABLE()       (RCC->APB1ENR &= ~(RCC_APB1ENR_USBEN))
#define __PWR_CLK_DISABLE()       (RCC->APB1ENR &= ~(RCC_APB1ENR_PWREN))
#define __DAC_CLK_DISABLE()       (RCC->APB1ENR &= ~(RCC_APB1ENR_DACEN))
#define __COMP_CLK_DISABLE()      (RCC->APB1ENR &= ~(RCC_APB1ENR_COMPEN))

/** @brief  Enable or disable the High Speed APB (APB2) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.
  */
#define __SYSCFG_CLK_ENABLE()     (RCC->APB2ENR |= (RCC_APB2ENR_SYSCFGEN))
#define __TIM9_CLK_ENABLE()       (RCC->APB2ENR |= (RCC_APB2ENR_TIM9EN))
#define __TIM10_CLK_ENABLE()      (RCC->APB2ENR |= (RCC_APB2ENR_TIM10EN))
#define __TIM11_CLK_ENABLE()      (RCC->APB2ENR |= (RCC_APB2ENR_TIM11EN))
#define __ADC1_CLK_ENABLE()       (RCC->APB2ENR |= (RCC_APB2ENR_ADC1EN))
#define __SPI1_CLK_ENABLE()       (RCC->APB2ENR |= (RCC_APB2ENR_SPI1EN))
#define __USART1_CLK_ENABLE()     (RCC->APB2ENR |= (RCC_APB2ENR_USART1EN))

#define __SYSCFG_CLK_DISABLE()    (RCC->APB2ENR &= ~(RCC_APB2ENR_SYSCFGEN))
#define __TIM9_CLK_DISABLE()      (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM9EN))
#define __TIM10_CLK_DISABLE()     (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM10EN))
#define __TIM11_CLK_DISABLE()     (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM11EN))
#define __ADC1_CLK_DISABLE()      (RCC->APB2ENR &= ~(RCC_APB2ENR_ADC1EN))
#define __SPI1_CLK_DISABLE()      (RCC->APB2ENR &= ~(RCC_APB2ENR_SPI1EN))
#define __USART1_CLK_DISABLE()    (RCC->APB2ENR &= ~(RCC_APB2ENR_USART1EN))

/**
  * @}
  */
  
/** @defgroup RCC_Peripheral_Clock_Force_Release RCC Peripheral Clock Force Release
  * @brief  Force or release AHB peripheral reset.
  * @{
  */  
#define __AHB_FORCE_RESET()       (RCC->AHBRSTR = 0xFFFFFFFF)
#define __GPIOA_FORCE_RESET()     (RCC->AHBRSTR |= (RCC_AHBRSTR_GPIOARST))
#define __GPIOB_FORCE_RESET()     (RCC->AHBRSTR |= (RCC_AHBRSTR_GPIOBRST))
#define __GPIOC_FORCE_RESET()     (RCC->AHBRSTR |= (RCC_AHBRSTR_GPIOCRST))
#define __GPIOD_FORCE_RESET()     (RCC->AHBRSTR |= (RCC_AHBRSTR_GPIODRST))
#define __GPIOH_FORCE_RESET()     (RCC->AHBRSTR |= (RCC_AHBRSTR_GPIOHRST))

#define __CRC_FORCE_RESET()       (RCC->AHBRSTR |= (RCC_AHBRSTR_CRCRST))
#define __FLITF_FORCE_RESET()     (RCC->AHBRSTR |= (RCC_AHBRSTR_FLITFRST))
#define __DMA1_FORCE_RESET()      (RCC->AHBRSTR |= (RCC_AHBRSTR_DMA1RST))

#define __AHB_RELEASE_RESET()     (RCC->AHBRSTR = 0x00)
#define __GPIOA_RELEASE_RESET()   (RCC->AHBRSTR &= ~(RCC_AHBRSTR_GPIOARST))
#define __GPIOB_RELEASE_RESET()   (RCC->AHBRSTR &= ~(RCC_AHBRSTR_GPIOBRST))
#define __GPIOC_RELEASE_RESET()   (RCC->AHBRSTR &= ~(RCC_AHBRSTR_GPIOCRST))
#define __GPIOD_RELEASE_RESET()   (RCC->AHBRSTR &= ~(RCC_AHBRSTR_GPIODRST))
#define __GPIOH_RELEASE_RESET()   (RCC->AHBRSTR &= ~(RCC_AHBRSTR_GPIOHRST))

#define __CRC_RELEASE_RESET()     (RCC->AHBRSTR &= ~(RCC_AHBRSTR_CRCRST))
#define __FLITF_RELEASE_RESET()   (RCC->AHBRSTR &= ~(RCC_AHBRSTR_FLITFRST))
#define __DMA1_RELEASE_RESET()    (RCC->AHBRSTR &= ~(RCC_AHBRSTR_DMA1RST))

/** @brief  Force or release APB1 peripheral reset.
  */
#define __APB1_FORCE_RESET()      (RCC->APB1RSTR = 0xFFFFFFFF)  
#define __TIM2_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM2RST))
#define __TIM3_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM3RST))
#define __TIM4_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM4RST))
#define __TIM6_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM6RST))
#define __TIM7_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM7RST))
#define __WWDG_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_WWDGRST))
#define __SPI2_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_SPI2RST))
#define __USART2_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_USART2RST))
#define __USART3_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_USART3RST))
#define __I2C1_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_I2C1RST))
#define __I2C2_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_I2C2RST))
#define __USB_FORCE_RESET()       (RCC->APB1RSTR |= (RCC_APB1RSTR_USBRST))
#define __PWR_FORCE_RESET()       (RCC->APB1RSTR |= (RCC_APB1RSTR_PWRRST))
#define __DAC_FORCE_RESET()       (RCC->APB1RSTR |= (RCC_APB1RSTR_DACRST))
#define __COMP_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_COMPRST))

#define __APB1_RELEASE_RESET()    (RCC->APB1RSTR = 0x00) 
#define __TIM2_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM2RST))
#define __TIM3_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM3RST))
#define __TIM4_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM4RST))
#define __TIM6_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM6RST))
#define __TIM7_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM7RST))
#define __WWDG_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_WWDGRST))
#define __SPI2_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_SPI2RST))
#define __USART2_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_USART2RST))
#define __USART3_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_USART3RST))
#define __I2C1_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C1RST))
#define __I2C2_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C2RST))
#define __USB_RELEASE_RESET()     (RCC->APB1RSTR &= ~(RCC_APB1RSTR_USBRST))
#define __PWR_RELEASE_RESET()     (RCC->APB1RSTR &= ~(RCC_APB1RSTR_PWRRST))
#define __DAC_RELEASE_RESET()     (RCC->APB1RSTR &= ~(RCC_APB1RSTR_DACRST))
#define __COMP_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_COMPRST))

/** @brief  Force or release APB2 peripheral reset.
  */
#define __APB2_FORCE_RESET()      (RCC->APB2RSTR = 0xFFFFFFFF)  
#define __SYSCFG_FORCE_RESET()    (RCC->APB2RSTR |= (RCC_APB2RSTR_SYSCFGRST))
#define __TIM9_FORCE_RESET()      (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM9RST))
#define __TIM10_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM10RST))
#define __TIM11_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM11RST))
#define __ADC1_FORCE_RESET()      (RCC->APB2RSTR |= (RCC_APB2RSTR_ADC1RST))
#define __SPI1_FORCE_RESET()      (RCC->APB2RSTR |= (RCC_APB2RSTR_SPI1RST))
#define __USART1_FORCE_RESET()    (RCC->APB2RSTR |= (RCC_APB2RSTR_USART1RST))

#define __APB2_RELEASE_RESET()    (RCC->APB2RSTR = 0x00)
#define __SYSCFG_RELEASE_RESET()  (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SYSCFGRST))
#define __TIM9_RELEASE_RESET()    (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM9RST))
#define __TIM10_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM10RST))
#define __TIM11_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM11RST))
#define __ADC1_RELEASE_RESET()    (RCC->APB2RSTR &= ~(RCC_APB2RSTR_ADC1RST))
#define __SPI1_RELEASE_RESET()    (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI1RST))
#define __USART1_RELEASE_RESET()  (RCC->APB2RSTR &= ~(RCC_APB2RSTR_USART1RST))

/**
  * @}
  */

/** @defgroup RCC_Peripheral_Clock_Sleep_Enable_Disable RCC Peripheral Clock Sleep Enable Disable
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */
#define __GPIOA_CLK_SLEEP_ENABLE()    (RCC->AHBLPENR |= (RCC_AHBLPENR_GPIOALPEN))
#define __GPIOB_CLK_SLEEP_ENABLE()    (RCC->AHBLPENR |= (RCC_AHBLPENR_GPIOBLPEN))
#define __GPIOC_CLK_SLEEP_ENABLE()    (RCC->AHBLPENR |= (RCC_AHBLPENR_GPIOCLPEN))
#define __GPIOD_CLK_SLEEP_ENABLE()    (RCC->AHBLPENR |= (RCC_AHBLPENR_GPIODLPEN))
#define __GPIOH_CLK_SLEEP_ENABLE()    (RCC->AHBLPENR |= (RCC_AHBLPENR_GPIOHLPEN))

#define __CRC_CLK_SLEEP_ENABLE()      (RCC->AHBLPENR |= (RCC_AHBLPENR_CRCLPEN))
#define __FLITF_CLK_SLEEP_ENABLE()    (RCC->AHBLPENR |= (RCC_AHBLPENR_FLITFLPEN))
#define __DMA1_CLK_SLEEP_ENABLE()     (RCC->AHBLPENR |= (RCC_AHBLPENR_DMA1LPEN))

#define __GPIOA_CLK_SLEEP_DISABLE()   (RCC->AHBLPENR &= ~(RCC_AHBLPENR_GPIOALPEN))
#define __GPIOB_CLK_SLEEP_DISABLE()   (RCC->AHBLPENR &= ~(RCC_AHBLPENR_GPIOBLPEN))
#define __GPIOC_CLK_SLEEP_DISABLE()   (RCC->AHBLPENR &= ~(RCC_AHBLPENR_GPIOCLPEN))
#define __GPIOD_CLK_SLEEP_DISABLE()   (RCC->AHBLPENR &= ~(RCC_AHBLPENR_GPIODLPEN))
#define __GPIOH_CLK_SLEEP_DISABLE()   (RCC->AHBLPENR &= ~(RCC_AHBLPENR_GPIOHLPEN))

#define __CRC_CLK_SLEEP_DISABLE()     (RCC->AHBLPENR &= ~(RCC_AHBLPENR_CRCLPEN))
#define __FLITF_CLK_SLEEP_DISABLE()   (RCC->AHBLPENR &= ~(RCC_AHBLPENR_FLITFLPEN))
#define __DMA1_CLK_SLEEP_DISABLE()    (RCC->AHBLPENR &= ~(RCC_AHBLPENR_DMA1LPEN))

/** @brief  Enable or disable the APB1 peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *           power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  */
#define __TIM2_CLK_SLEEP_ENABLE()     (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM2LPEN))
#define __TIM3_CLK_SLEEP_ENABLE()     (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM3LPEN))
#define __TIM4_CLK_SLEEP_ENABLE()     (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM4LPEN))
#define __TIM6_CLK_SLEEP_ENABLE()     (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM6LPEN))
#define __TIM7_CLK_SLEEP_ENABLE()     (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM7LPEN))
#define __WWDG_CLK_SLEEP_ENABLE()     (RCC->APB1LPENR |= (RCC_APB1LPENR_WWDGLPEN))
#define __SPI2_CLK_SLEEP_ENABLE()     (RCC->APB1LPENR |= (RCC_APB1LPENR_SPI2LPEN))
#define __USART2_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_USART2LPEN))
#define __USART3_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_USART3LPEN))
#define __I2C1_CLK_SLEEP_ENABLE()     (RCC->APB1LPENR |= (RCC_APB1LPENR_I2C1LPEN))
#define __I2C2_CLK_SLEEP_ENABLE()     (RCC->APB1LPENR |= (RCC_APB1LPENR_I2C2LPEN))
#define __USB_CLK_SLEEP_ENABLE()      (RCC->APB1LPENR |= (RCC_APB1LPENR_USBLPEN))
#define __PWR_CLK_SLEEP_ENABLE()      (RCC->APB1LPENR |= (RCC_APB1LPENR_PWRLPEN))
#define __DAC_CLK_SLEEP_ENABLE()      (RCC->APB1LPENR |= (RCC_APB1LPENR_DACLPEN))
#define __COMP_CLK_SLEEP_ENABLE()     (RCC->APB1LPENR |= (RCC_APB1LPENR_COMPLPEN))

#define __TIM2_CLK_SLEEP_DISABLE()    (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM2LPEN))
#define __TIM3_CLK_SLEEP_DISABLE()    (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM3LPEN))
#define __TIM4_CLK_SLEEP_DISABLE()    (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM4LPEN))
#define __TIM6_CLK_SLEEP_DISABLE()    (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM6LPEN))
#define __TIM7_CLK_SLEEP_DISABLE()    (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM7LPEN))
#define __WWDG_CLK_SLEEP_DISABLE()    (RCC->APB1LPENR &= ~(RCC_APB1LPENR_WWDGLPEN))
#define __SPI2_CLK_SLEEP_DISABLE()    (RCC->APB1LPENR &= ~(RCC_APB1LPENR_SPI2LPEN))
#define __USART2_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_USART2LPEN))
#define __USART3_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_USART3LPEN))
#define __I2C1_CLK_SLEEP_DISABLE()    (RCC->APB1LPENR &= ~(RCC_APB1LPENR_I2C1LPEN))
#define __I2C2_CLK_SLEEP_DISABLE()    (RCC->APB1LPENR &= ~(RCC_APB1LPENR_I2C2LPEN))
#define __USB_CLK_SLEEP_DISABLE()     (RCC->APB1LPENR &= ~(RCC_APB1LPENR_USBLPEN))
#define __PWR_CLK_SLEEP_DISABLE()     (RCC->APB1LPENR &= ~(RCC_APB1LPENR_PWRLPEN))
#define __DAC_CLK_SLEEP_DISABLE()     (RCC->APB1LPENR &= ~(RCC_APB1LPENR_DACLPEN))
#define __COMP_CLK_SLEEP_DISABLE()    (RCC->APB1LPENR &= ~(RCC_APB1LPENR_COMPLPEN))

/** @brief  Enable or disable the APB2 peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *           power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  */
#define __SYSCFG_CLK_SLEEP_ENABLE()   (RCC->APB2LPENR |= (RCC_APB2LPENR_SYSCFGLPEN))
#define __TIM9_CLK_SLEEP_ENABLE()     (RCC->APB2LPENR |= (RCC_APB2LPENR_TIM9LPEN))
#define __TIM10_CLK_SLEEP_ENABLE()    (RCC->APB2LPENR |= (RCC_APB2LPENR_TIM10LPEN))
#define __TIM11_CLK_SLEEP_ENABLE()    (RCC->APB2LPENR |= (RCC_APB2LPENR_TIM11LPEN))
#define __ADC1_CLK_SLEEP_ENABLE()     (RCC->APB2LPENR |= (RCC_APB2LPENR_ADC1LPEN))
#define __SPI1_CLK_SLEEP_ENABLE()     (RCC->APB2LPENR |= (RCC_APB2LPENR_SPI1LPEN))
#define __USART1_CLK_SLEEP_ENABLE()   (RCC->APB2LPENR |= (RCC_APB2LPENR_USART1LPEN))

#define __SYSCFG_CLK_SLEEP_DISABLE()  (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SYSCFGLPEN))
#define __TIM9_CLK_SLEEP_DISABLE()    (RCC->APB2LPENR &= ~(RCC_APB2LPENR_TIM9LPEN))
#define __TIM10_CLK_SLEEP_DISABLE()   (RCC->APB2LPENR &= ~(RCC_APB2LPENR_TIM10LPEN))
#define __TIM11_CLK_SLEEP_DISABLE()   (RCC->APB2LPENR &= ~(RCC_APB2LPENR_TIM11LPEN))
#define __ADC1_CLK_SLEEP_DISABLE()    (RCC->APB2LPENR &= ~(RCC_APB2LPENR_ADC1LPEN))
#define __SPI1_CLK_SLEEP_DISABLE()    (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SPI1LPEN))
#define __USART1_CLK_SLEEP_DISABLE()  (RCC->APB2LPENR &= ~(RCC_APB2LPENR_USART1LPEN))

/**
  * @}
  */

/** @brief  Macros to enable or disable the Internal High Speed oscillator (HSI).
  * @note   The HSI is stopped by hardware when entering STOP and STANDBY modes.
  * @note   HSI can not be stopped if it is used as system clock source. In this case,
  *         you have to select another source of the system clock then stop the HSI.  
  * @note   After enabling the HSI, the application software should wait on HSIRDY
  *         flag to be set indicating that HSI clock is stable and can be used as
  *         system clock source.  
  * @note   When the HSI is stopped, HSIRDY flag goes low after 6 HSI oscillator
  *         clock cycles.  
  */
#define __HAL_RCC_HSI_ENABLE()  (*(__IO uint32_t *) CR_HSION_BB = ENABLE)
#define __HAL_RCC_HSI_DISABLE() (*(__IO uint32_t *) CR_HSION_BB = DISABLE)

/** @brief Macros to enable or disable the External High Speed oscillator (HSE).
  * @param  __HSE_STATE__: specifies the new state of the HSE.
  *          This parameter can be one of the following values:
  *            @arg RCC_HSE_OFF: turn OFF the HSE oscillator, HSERDY flag goes low after
  *                              6 HSE oscillator clock cycles.
  *            @arg RCC_HSE_ON: turn ON the HSE oscillator
  *            @arg RCC_HSE_BYPASS: HSE oscillator bypassed with external clock
  */
#define __HAL_RCC_HSE_CONFIG(__HSE_STATE__) (*(__IO uint8_t *) CR_BYTE2_ADDRESS = (__HSE_STATE__))

/** @brief Macros to enable or disable the Internal Multi Speed oscillator (MSI).
  * @note   The MSI is stopped by hardware when entering STOP and STANDBY modes.
  *         It is used (enabled by hardware) as system clock source after startup
  *         from Reset, wakeup from STOP and STANDBY mode, or in case of failure
  *         of the HSE used directly or indirectly as system clock (if the Clock
  *         Security System CSS is enabled).             
  * @note   MSI can not be stopped if it is used as system clock source. In this case,
  *         you have to select another source of the system clock then stop the MSI.  
  * @note   After enabling the MSI, the application software should wait on MSIRDY
  *         flag to be set indicating that MSI clock is stable and can be used as
  *         system clock source.  
  * @note   When the MSI is stopped, MSIRDY flag goes low after 6 MSI oscillator
  *         clock cycles.  
  */
#define __HAL_RCC_MSI_ENABLE()  (*(__IO uint32_t *) CR_MSION_BB = ENABLE)
#define __HAL_RCC_MSI_DISABLE() (*(__IO uint32_t *) CR_MSION_BB = DISABLE)
                                       
/** @brief  macro to adjust the Internal High Speed oscillator (HSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  * @param  _HSICALIBRATIONVALUE_: specifies the calibration trimming value.
  *         (default is RCC_HSICALIBRATION_DEFAULT).
  *         This parameter must be a number between 0 and 0x1F.
  */   
#define __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(_HSICALIBRATIONVALUE_) \
          (MODIFY_REG(RCC->ICSCR, RCC_ICSCR_HSITRIM, (uint32_t)(_HSICALIBRATIONVALUE_) << POSITION_VAL(RCC_ICSCR_HSITRIM)))

/** @brief  macro to adjust the Internal Multi Speed oscillator (MSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal MSI RC.
  * @param  _MSICALIBRATIONVALUE_: specifies the calibration trimming value.
  *         (default is RCC_MSICALIBRATION_DEFAULT).
  *         This parameter must be a number between 0 and 0x1F.
  */   
#define __HAL_RCC_MSI_CALIBRATIONVALUE_ADJUST(_MSICALIBRATIONVALUE_) \
          (MODIFY_REG(RCC->ICSCR, RCC_ICSCR_MSITRIM, (uint32_t)(_MSICALIBRATIONVALUE_) << POSITION_VAL(RCC_ICSCR_MSITRIM)))

/* @brief  Macro to configures the Internal Multi Speed oscillator (MSI) clock range.
  * @note     After restart from Reset or wakeup from STANDBY, the MSI clock is 
  *           around 2.097 MHz. The MSI clock does not change after wake-up from
  *           STOP mode.
  * @note    The MSI clock range can be modified on the fly.     
  * @param  _MSIRANGEVALUE_: specifies the MSI Clock range.
  *   This parameter must be one of the following values:
  *     @arg RCC_MSIRANGE_0: MSI clock is around 65.536 KHz
  *     @arg RCC_MSIRANGE_1: MSI clock is around 131.072 KHz
  *     @arg RCC_MSIRANGE_2: MSI clock is around 262.144 KHz
  *     @arg RCC_MSIRANGE_3: MSI clock is around 524.288 KHz
  *     @arg RCC_MSIRANGE_4: MSI clock is around 1.048 MHz
  *     @arg RCC_MSIRANGE_5: MSI clock is around 2.097 MHz (default after Reset or wake-up from STANDBY)
  *     @arg RCC_MSIRANGE_6: MSI clock is around 4.194 MHz
  */   
#define __HAL_RCC_MSI_RANGE_CONFIG(_MSIRANGEVALUE_) (MODIFY_REG(RCC->ICSCR, RCC_ICSCR_MSIRANGE, (uint32_t)(_MSIRANGEVALUE_)))

                                       
/** @brief Macros to enable or disable  the Internal Low Speed oscillator (LSI).
  * @note   After enabling the LSI, the application software should wait on 
  *         LSIRDY flag to be set indicating that LSI clock is stable and can
  *         be used to clock the IWDG and/or the RTC.
  * @note   LSI can not be disabled if the IWDG is running.  
  * @note   When the LSI is stopped, LSIRDY flag goes low after 6 LSI oscillator
  *         clock cycles. 
  */
#define __HAL_RCC_LSI_ENABLE()  (*(__IO uint32_t *) CSR_LSION_BB = ENABLE)
#define __HAL_RCC_LSI_DISABLE() (*(__IO uint32_t *) CSR_LSION_BB = DISABLE)
                                       
/** @brief Macros to enable or disable the Internal Low Speed oscillator (LSE).
  */
#define __HAL_RCC_LSE_CONFIG(__LSE_STATE__) \
                                       do{ \
                                         if ((__LSE_STATE__) == RCC_LSE_OFF) \
                                         { \
                                           *(__IO uint32_t *) CSR_LSEON_BB = DISABLE; \
                                           *(__IO uint32_t *) CSR_LSEBYP_BB = DISABLE; \
                                         } \
                                         else if ((__LSE_STATE__) == RCC_LSE_ON) \
                                         { \
                                           *(__IO uint32_t *) CSR_LSEBYP_BB = DISABLE; \
                                           *(__IO uint32_t *) CSR_LSEON_BB = ENABLE; \
                                         } \
                                         else \
                                         { \
                                           *(__IO uint32_t *) CSR_LSEON_BB = DISABLE; \
                                           *(__IO uint32_t *) CSR_LSEBYP_BB = ENABLE; \
                                         } \
                                       }while(0)
                                       
/** @brief Macros to enable or disable the the RTC clock.
  * @note   These macros must be used only after the RTC clock source was selected.
  */
#define __HAL_RCC_RTC_ENABLE()          (*(__IO uint32_t *) CSR_RTCEN_BB = ENABLE)
#define __HAL_RCC_RTC_DISABLE()         (*(__IO uint32_t *) CSR_RTCEN_BB = DISABLE)

/** @brief  Macros to force or release the Backup domain reset.
  * @note   This function resets the RTC peripheral (including the backup registers)
  *         and the RTC clock source selection in RCC_CSR register.
  * @note   The BKPSRAM is not affected by this reset.   
  */
#define __HAL_RCC_BACKUPRESET_FORCE()   (*(__IO uint32_t *) CSR_RTCRST_BB = ENABLE)
#define __HAL_RCC_BACKUPRESET_RELEASE() (*(__IO uint32_t *) CSR_RTCRST_BB = DISABLE)


/** @brief Macro to configures the RTC clock (RTCCLK).
  * @note   As the RTC clock configuration bits are in the Backup domain and write
  *         access is denied to this domain after reset, you have to enable write
  *         access using the Power Backup Access macro before to configure
  *         the RTC clock source (to be done once after reset).    
  * @note   Once the RTC clock is configured it can't be changed unless the  
  *         Backup domain is reset using __HAL_RCC_BACKUPRESET_FORCE() macro, or by
  *         a Power On Reset (POR).
  * @note   RTC prescaler cannot be modified if HSE is enabled (HSEON = 1).
  *
  * @param  __RTC_CLKSOURCE__: specifies the RTC clock source.
  *          This parameter can be one of the following values:
  *             @arg RCC_RTCCLKSOURCE_LSE: LSE selected as RTC clock
  *             @arg RCC_RTCCLKSOURCE_LSI: LSI selected as RTC clock
  *             @arg RCC_RTCCLKSOURCE_HSE_DIV2: HSE divided by 2 selected as RTC clock
  *             @arg RCC_RTCCLKSOURCE_HSE_DIV4: HSE divided by 4 selected as RTC clock
  *             @arg RCC_RTCCLKSOURCE_HSE_DIV8: HSE divided by 8 selected as RTC clock
  *             @arg RCC_RTCCLKSOURCE_HSE_DIV16: HSE divided by 16 selected as RTC clock
  * @note   If the LSE or LSI is used as RTC clock source, the RTC continues to
  *         work in STOP and STANDBY modes, and can be used as wakeup source.
  *         However, when the HSE clock is used as RTC clock source, the RTC
  *         cannot be used in STOP and STANDBY modes.    
  * @note   The maximum input clock frequency for RTC is 1MHz (when using HSE as
  *         RTC clock source).
  */
#define __HAL_RCC_RTC_CLKPRESCALER(__RTC_CLKSOURCE__) do { \
            if(((__RTC_CLKSOURCE__) & RCC_CSR_RTCSEL_HSE) == RCC_CSR_RTCSEL_HSE)          \
            {                                                                             \
              MODIFY_REG(RCC->CR, RCC_CR_RTCPRE, ((__RTC_CLKSOURCE__) & RCC_CR_RTCPRE));  \
            }                                                                             \
          } while (0)

#define __HAL_RCC_RTC_CONFIG(__RTC_CLKSOURCE__) do { \
                                      __HAL_RCC_RTC_CLKPRESCALER(__RTC_CLKSOURCE__);      \
                                      RCC->CSR |= ((__RTC_CLKSOURCE__) & RCC_CSR_RTCSEL); \
                                    } while (0)
                                                   
/** @brief macros to get the RTC clock source.
  */
#define __HAL_RCC_GET_RTC_SOURCE() (READ_BIT(RCC->CSR, RCC_CSR_RTCSEL))

/** @brief Macros to enable or disable the main PLL.
  * @note   After enabling the main PLL, the application software should wait on 
  *         PLLRDY flag to be set indicating that PLL clock is stable and can
  *         be used as system clock source.
  * @note   The main PLL can not be disabled if it is used as system clock source
  * @note   The main PLL is disabled by hardware when entering STOP and STANDBY modes.
  */
#define __HAL_RCC_PLL_ENABLE()          (*(__IO uint32_t *) CR_PLLON_BB = ENABLE)
#define __HAL_RCC_PLL_DISABLE()         (*(__IO uint32_t *) CR_PLLON_BB = DISABLE)

/** @brief macros to configure the main PLL clock source, multiplication and division factors.
  * @note   This function must be used only when the main PLL is disabled.
  *  
  * @param  __RCC_PLLSOURCE__: specifies the PLL entry clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_PLLSOURCE_HSI: HSI oscillator clock selected as PLL clock entry
  *            @arg RCC_PLLSOURCE_HSE: HSE oscillator clock selected as PLL clock entry
  * @param  __PLLMUL__: specifies the multiplication factor for PLL VCO output clock
  *          This parameter can be one of the following values:
  *             @arg RCC_PLL_MUL3: PLLVCO = PLL clock entry x 3
  *             @arg RCC_PLL_MUL4: PLLVCO = PLL clock entry x 4
  *             @arg RCC_PLL_MUL6: PLLVCO = PLL clock entry x 6
  *             @arg RCC_PLL_MUL8: PLLVCO = PLL clock entry x 8
  *             @arg RCC_PLL_MUL12: PLLVCO = PLL clock entry x 12
  *             @arg RCC_PLL_MUL16: PLLVCO = PLL clock entry x 16
  *             @arg RCC_PLL_MUL24: PLLVCO = PLL clock entry x 24
  *             @arg RCC_PLL_MUL32: PLLVCO = PLL clock entry x 32
  *             @arg RCC_PLL_MUL48: PLLVCO = PLL clock entry x 48
  * @note The PLL VCO clock frequency must not exceed 96 MHz when the product is in
  *          Range 1, 48 MHz when the product is in Range 2 and 24 MHz when the product is
  *          in Range 3.
  *   
  * @param  __PLLDIV__: specifies the division factor for PLL VCO input clock
  *          This parameter can be one of the following values:
  *             @arg RCC_PLL_DIV2: PLL clock output = PLLVCO / 2
  *             @arg RCC_PLL_DIV3: PLL clock output = PLLVCO / 3
  *             @arg RCC_PLL_DIV4: PLL clock output = PLLVCO / 4
  *  
  */
#define __HAL_RCC_PLL_CONFIG(__RCC_PLLSOURCE__, __PLLMUL__, __PLLDIV__)\
          MODIFY_REG(RCC->CFGR, (RCC_CFGR_PLLSRC|RCC_CFGR_PLLMUL|RCC_CFGR_PLLDIV),((__RCC_PLLSOURCE__) | (__PLLMUL__) | (__PLLDIV__)))

/** @brief  Macro to get the clock source used as system clock.
  * @retval The clock source used as system clock. The returned value can be one
  *         of the following:
  *             @arg RCC_CFGR_SWS_MSI: MSI used as system clock
  *             @arg RCC_CFGR_SWS_HSI: HSI used as system clock
  *             @arg RCC_CFGR_SWS_HSE: HSE used as system clock
  *             @arg RCC_CFGR_SWS_PLL: PLL used as system clock
  */     
#define __HAL_RCC_GET_SYSCLK_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR,RCC_CFGR_SWS)))
                              
/** @brief macros to manage the specified RCC Flags and interrupts.
  */

/** @brief Enable RCC interrupt (Perform Byte access to RCC_CIR[14:8] bits to enable
  *        the selected interrupts.).
  * @param  __INTERRUPT__: specifies the RCC interrupt sources to be enabled.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_IT_LSIRDY: LSI ready interrupt
  *            @arg RCC_IT_LSERDY: LSE ready interrupt
  *            @arg RCC_IT_HSIRDY: HSI ready interrupt
  *            @arg RCC_IT_HSERDY: HSE ready interrupt
  *            @arg RCC_IT_PLLRDY: main PLL ready interrupt
  *            @arg RCC_IT_MSIRDY: MSI ready interrupt
  *            @arg RCC_IT_LSECSS: LSE CSS interrupt (not available for STM32L100xB || STM32L151xB || STM32L152xB device)
  */
#define __HAL_RCC_ENABLE_IT(__INTERRUPT__) (*(__IO uint8_t *) CIR_BYTE1_ADDRESS |= (__INTERRUPT__))

/** @brief Disable RCC interrupt (Perform Byte access to RCC_CIR[14:8] bits to disable 
  *        the selected interrupts).
  * @param  __INTERRUPT__: specifies the RCC interrupt sources to be disabled.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_IT_LSIRDY: LSI ready interrupt
  *            @arg RCC_IT_LSERDY: LSE ready interrupt
  *            @arg RCC_IT_HSIRDY: HSI ready interrupt
  *            @arg RCC_IT_HSERDY: HSE ready interrupt
  *            @arg RCC_IT_PLLRDY: main PLL ready interrupt
  *            @arg RCC_IT_MSIRDY: MSI ready interrupt
  *            @arg RCC_IT_LSECSS: LSE CSS interrupt (not available for STM32L100xB || STM32L151xB || STM32L152xB device)
  */
#define __HAL_RCC_DISABLE_IT(__INTERRUPT__) (*(__IO uint8_t *) CIR_BYTE1_ADDRESS &= ~(__INTERRUPT__))

/** @brief Clear the RCC's interrupt pending bits ( Perform Byte access to RCC_CIR[23:16]
  *        bits to clear the selected interrupt pending bits.
  * @param  __INTERRUPT__: specifies the interrupt pending bit to clear.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_IT_LSIRDY: LSI ready interrupt.
  *            @arg RCC_IT_LSERDY: LSE ready interrupt.
  *            @arg RCC_IT_HSIRDY: HSI ready interrupt.
  *            @arg RCC_IT_HSERDY: HSE ready interrupt.
  *            @arg RCC_IT_PLLRDY: Main PLL ready interrupt.
  *            @arg RCC_IT_MSIRDY: MSI ready interrupt.
  *            @arg RCC_IT_LSECSS: LSE CSS interrupt (not available for STM32L100xB || STM32L151xB || STM32L152xB device)
  *            @arg RCC_IT_CSS: Clock Security System interrupt
  */
#define __HAL_RCC_CLEAR_IT(__INTERRUPT__) (*(__IO uint8_t *) CIR_BYTE2_ADDRESS = (__INTERRUPT__))

/** @brief Check the RCC's interrupt has occurred or not.
  * @param  __INTERRUPT__: specifies the RCC interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg RCC_IT_LSIRDY: LSI ready interrupt.
  *            @arg RCC_IT_LSERDY: LSE ready interrupt.
  *            @arg RCC_IT_HSIRDY: HSI ready interrupt.
  *            @arg RCC_IT_HSERDY: HSE ready interrupt.
  *            @arg RCC_IT_PLLRDY: Main PLL ready interrupt.
  *            @arg RCC_IT_MSIRDY: MSI ready interrupt.
  *            @arg RCC_IT_LSECSS: LSE CSS interrupt (not available for STM32L100xB || STM32L151xB || STM32L152xB device)
  *            @arg RCC_IT_CSS: Clock Security System interrupt
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_IT(__INTERRUPT__) ((RCC->CIR & (__INTERRUPT__)) == (__INTERRUPT__))

/** @brief Set RMVF bit to clear the reset flags: RCC_FLAG_PINRST, RCC_FLAG_PORRST, RCC_FLAG_SFTRST,
  * RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST, RCC_FLAG_LPWRRST
  */
#define __HAL_RCC_CLEAR_RESET_FLAGS() (RCC->CSR |= RCC_CSR_RMVF)

/** @brief  Check RCC flag is set or not.
  * @param  __FLAG__: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg RCC_FLAG_HSIRDY: HSI oscillator clock ready.
  *            @arg RCC_FLAG_MSIRDY: MSI oscillator clock ready.
  *            @arg RCC_FLAG_HSERDY: HSE oscillator clock ready.
  *            @arg RCC_FLAG_PLLRDY: Main PLL clock ready.
  *            @arg RCC_FLAG_LSERDY: LSE oscillator clock ready.
  *            @arg RCC_FLAG_LSECSS: CSS on LSE failure Detection (*)
  *            @arg RCC_FLAG_LSIRDY: LSI oscillator clock ready.
  *            @arg RCC_FLAG_BORRST: POR/PDR or BOR reset.
  *            @arg RCC_FLAG_PINRST: Pin reset.
  *            @arg RCC_FLAG_PORRST: POR/PDR reset.
  *            @arg RCC_FLAG_SFTRST: Software reset.
  *            @arg RCC_FLAG_IWDGRST: Independent Watchdog reset.
  *            @arg RCC_FLAG_WWDGRST: Window Watchdog reset.
  *            @arg RCC_FLAG_LPWRRST: Low Power reset.
  * @note (*) This bit is available in high and medium+ density devices only.
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_FLAG(__FLAG__) (((((__FLAG__) >> 5) == CR_REG_INDEX)? RCC->CR :RCC->CSR) & ((uint32_t)1 << ((__FLAG__) & RCC_FLAG_MASK)))   

     
/** @brief  Get oscillator clock selected as PLL input clock
  * @retval The clock source used for PLL entry. The returned value can be one
  *         of the following:
  *             @arg RCC_PLLSOURCE_HSI: HSI oscillator clock selected as PLL input clock
  *             @arg RCC_PLLSOURCE_HSE: HSE oscillator clock selected as PLL input clock
  */
#define __HAL_RCC_GET_PLL_OSCSOURCE() ((RCC->CFGR & RCC_CFGR_PLLSRC))

/**
  * @}
  */   

/* Include RCC HAL Extension module */
#include "stm32l1xx_hal_rcc_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCC_Private_Functions
  * @{
  */

/** @addtogroup RCC_Exported_Functions_Group1
  * @{
  */

/* Initialization and de-initialization functions  ******************************/
void              HAL_RCC_DeInit(void);
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct, uint32_t FLatency);

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group2
  * @{
  */

/* Peripheral Control functions  ************************************************/
void              HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
void              HAL_RCC_EnableCSS(void);
void              HAL_RCC_DisableCSS(void);
uint32_t          HAL_RCC_GetSysClockFreq(void);
uint32_t          HAL_RCC_GetHCLKFreq(void);
uint32_t          HAL_RCC_GetPCLK1Freq(void);
uint32_t          HAL_RCC_GetPCLK2Freq(void);
void              HAL_RCC_GetOscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct);
void              HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct, uint32_t *pFLatency);

/* CSS NMI IRQ handler */
void              HAL_RCC_NMI_IRQHandler(void);

/* User Callbacks in non blocking mode (IT mode) */ 
void              HAL_RCC_CCSCallback(void);

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

#endif /* __STM32L1xx_HAL_RCC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

