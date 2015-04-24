/**
  ******************************************************************************
  * @file    stm32f3xx_hal_rcc.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
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
#ifndef __STM32F3xx_HAL_RCC_H
#define __STM32F3xx_HAL_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal_def.h"

/** @addtogroup STM32F3xx_HAL_Driver
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
  * @brief  RCC System, AHB and APB busses clock configuration structure definition
  */
typedef struct
{
  uint32_t ClockType;            /*!< The clock to be configured.
                                      This parameter can be a value of @ref RCC_System_Clock_Type */

  uint32_t SYSCLKSource;         /*!< The clock source (SYSCLKS) used as system clock.
                                      This parameter can be a value of @ref RCC_System_Clock_Source */

  uint32_t AHBCLKDivider;        /*!< The AHB clock (HCLK) divider. This clock is derived from the system clock (SYSCLK).
                                      This parameter can be a value of @ref RCC_AHB_Clock_Source */

  uint32_t APB1CLKDivider;       /*!< The APB1 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).
                                      This parameter can be a value of @ref RCC_APB1_APB2_Clock_Source */

  uint32_t APB2CLKDivider;       /*!< The APB2 clock (PCLK2) divider. This clock is derived from the AHB clock (HCLK).
                                      This parameter can be a value of @ref RCC_APB1_APB2_Clock_Source */

}RCC_ClkInitTypeDef;

/**
  * @}
  */
  
/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_Exported_Constants RCC Exported Constants
  * @{
  */

/** @defgroup RCC_BitAddress_AliasRegion RCC BitAddress AliasRegion
  * @brief RCC registers bit address in the alias region
  * @{
  */
#define RCC_OFFSET                (RCC_BASE - PERIPH_BASE)
/* --- CR Register ---*/
#define RCC_CR_OFFSET             (RCC_OFFSET + 0x00)
/* Alias word address of HSION bit */
#define HSION_BitNumber           0
#define CR_HSION_BB               (PERIPH_BB_BASE + (RCC_CR_OFFSET * 32) + (HSION_BitNumber * 4))
/* Alias word address of HSEON bit */
#define HSEON_BitNumber           16
#define CR_HSEON_BB               (PERIPH_BB_BASE + (RCC_CR_OFFSET * 32) + (HSEON_BitNumber * 4))
/* Alias word address of CSSON bit */
#define CSSON_BitNumber           19
#define CR_CSSON_BB               (PERIPH_BB_BASE + (RCC_CR_OFFSET * 32) + (CSSON_BitNumber * 4))
/* Alias word address of PLLON bit */
#define PLLON_BitNumber           24
#define CR_PLLON_BB               (PERIPH_BB_BASE + (RCC_CR_OFFSET * 32) + (PLLON_BitNumber * 4))

/* --- CFGR Register ---*/
#define RCC_CFGR_OFFSET           (RCC_OFFSET + 0x04)
/* Alias word address of PLLSRC bit */
#define PLLSRC_BitNumber          16
#define CFGR_PLLSRC_BB            (PERIPH_BB_BASE + (RCC_CFGR_OFFSET * 32) + (PLLSRC_BitNumber * 4))

/* --- CIR Register ---*/
#define RCC_CIR_OFFSET           (RCC_OFFSET + 0x08)

/* --- BDCR Register ---*/
#define RCC_BDCR_OFFSET           (RCC_OFFSET + 0x20)
/* Alias word address of LSEON bit */
#define LSEON_BitNumber           0
#define BDCR_LSEON_BB             (PERIPH_BB_BASE + (RCC_BDCR_OFFSET * 32) + (LSEON_BitNumber * 4))
/* Alias word address of RTCEN bit */
#define RTCEN_BitNumber           15
#define BDCR_RTCEN_BB             (PERIPH_BB_BASE + (RCC_BDCR_OFFSET * 32) + (RTCEN_BitNumber * 4))
/* Alias word address of BDRST bit */
#define BDRST_BitNumber           16
#define BDCR_BDRST_BB             (PERIPH_BB_BASE + (RCC_BDCR_OFFSET * 32) + (BDRST_BitNumber * 4))

/* --- CSR Register ---*/
#define RCC_CSR_OFFSET            (RCC_OFFSET + 0x24)
/* Alias word address of LSION bit */
#define LSION_BitNumber           0
#define CSR_LSION_BB              (PERIPH_BB_BASE + (RCC_CSR_OFFSET * 32) + (LSION_BitNumber * 4))
/* Alias word address of RMVF bit */
#define RMVF_BitNumber            24
#define CSR_RMVF_BB               (PERIPH_BB_BASE + (RCC_CSR_OFFSET * 32) + (RMVF_BitNumber * 4))

/* CR register byte 2 (Bits[23:16]) base address */
#define CR_BYTE2_ADDRESS          (PERIPH_BASE + RCC_CR_OFFSET + 0x02)

/* CIR register byte 1 (Bits[15:8]) base address */
#define CIR_BYTE1_ADDRESS         (PERIPH_BASE + RCC_CIR_OFFSET + 0x01)

/* CIR register byte 2 (Bits[23:16]) base address */
#define CIR_BYTE2_ADDRESS         (PERIPH_BASE + RCC_CIR_OFFSET + 0x02)

/* CSR register byte 1 (Bits[15:8]) base address */
#define CSR_BYTE1_ADDRESS         (PERIPH_BASE + RCC_CSR_OFFSET + 0x01)

/* BDCR register byte 0 (Bits[7:0] base address */
#define BDCR_BYTE0_ADDRESS        (PERIPH_BASE + RCC_BDCR_OFFSET)

/**
  * @}
  */

/** @defgroup RCC_Timeout RCC Timeout
  * @{
  */  
/* LSE state change timeout */
#define LSE_TIMEOUT_VALUE          ((uint32_t)5000) /* 5 s    */

/* Disable Backup domain write protection state change timeout */
#define DBP_TIMEOUT_VALUE          ((uint32_t)100)  /* 100 ms */
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

#define IS_RCC_OSCILLATORTYPE(OSCILLATOR) (((OSCILLATOR) == RCC_OSCILLATORTYPE_NONE)                           || \
                                           (((OSCILLATOR) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE) || \
                                           (((OSCILLATOR) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI) || \
                                           (((OSCILLATOR) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI) || \
                                           (((OSCILLATOR) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE))
/**
  * @}
  */

/** @defgroup RCC_HSE_Config RCC HSE Config
  * @{
  */
#define RCC_HSE_OFF                      ((uint32_t)0x00000000)
#define RCC_HSE_ON                       ((uint32_t)0x00000001)
#define RCC_HSE_BYPASS                   ((uint32_t)0x00000005)

#define IS_RCC_HSE(HSE) (((HSE) == RCC_HSE_OFF) || ((HSE) == RCC_HSE_ON) || \
                         ((HSE) == RCC_HSE_BYPASS))
/**
  * @}
  */

/** @defgroup RCC_LSE_Config RCC_LSE_Config
  * @{
  */
#define RCC_LSE_OFF                      ((uint32_t)0x00000000)
#define RCC_LSE_ON                       ((uint32_t)0x00000001)
#define RCC_LSE_BYPASS                   ((uint32_t)0x00000005)

#define IS_RCC_LSE(LSE) (((LSE) == RCC_LSE_OFF) || ((LSE) == RCC_LSE_ON) || \
                         ((LSE) == RCC_LSE_BYPASS))
/**
  * @}
  */

/** @defgroup RCC_HSI_Config RCC HSI Config
  * @{
  */
#define RCC_HSI_OFF                      ((uint32_t)0x00000000)
#define RCC_HSI_ON                       ((uint32_t)0x00000001)

#define IS_RCC_HSI(HSI) (((HSI) == RCC_HSI_OFF) || ((HSI) == RCC_HSI_ON))

#define RCC_HSICALIBRATION_DEFAULT ((uint32_t)0x10) /* Default HSI calibration trimming value */

#define IS_RCC_CALIBRATION_VALUE(__VALUE__) ((__VALUE__) <= 0x1F)
/**
  * @}
  */

/** @defgroup RCC_LSI_Config RCC LSI Config
  * @{
  */
#define RCC_LSI_OFF                      ((uint32_t)0x00000000)
#define RCC_LSI_ON                       ((uint32_t)0x00000001)

#define IS_RCC_LSI(LSI) (((LSI) == RCC_LSI_OFF) || ((LSI) == RCC_LSI_ON))
/**
  * @}
  */

/** @defgroup RCC_PLL_Config RCC PLL Config
  * @{
  */
#define RCC_PLL_NONE                     ((uint32_t)0x00000000)
#define RCC_PLL_OFF                      ((uint32_t)0x00000001)
#define RCC_PLL_ON                       ((uint32_t)0x00000002)

#define IS_RCC_PLL(PLL) (((PLL) == RCC_PLL_NONE) ||((PLL) == RCC_PLL_OFF) || ((PLL) == RCC_PLL_ON))
/**
  * @}
  */

/** @defgroup RCC_PLL_Multiplication_Factor RCC PLL Multiplication Factor
  * @{
  */
#define RCC_PLL_MUL2                     RCC_CFGR_PLLMUL2
#define RCC_PLL_MUL3                     RCC_CFGR_PLLMUL3
#define RCC_PLL_MUL4                     RCC_CFGR_PLLMUL4
#define RCC_PLL_MUL5                     RCC_CFGR_PLLMUL5
#define RCC_PLL_MUL6                     RCC_CFGR_PLLMUL6
#define RCC_PLL_MUL7                     RCC_CFGR_PLLMUL7
#define RCC_PLL_MUL8                     RCC_CFGR_PLLMUL8
#define RCC_PLL_MUL9                     RCC_CFGR_PLLMUL9
#define RCC_PLL_MUL10                    RCC_CFGR_PLLMUL10
#define RCC_PLL_MUL11                    RCC_CFGR_PLLMUL11
#define RCC_PLL_MUL12                    RCC_CFGR_PLLMUL12
#define RCC_PLL_MUL13                    RCC_CFGR_PLLMUL13
#define RCC_PLL_MUL14                    RCC_CFGR_PLLMUL14
#define RCC_PLL_MUL15                    RCC_CFGR_PLLMUL15
#define RCC_PLL_MUL16                    RCC_CFGR_PLLMUL16

#define IS_RCC_PLL_MUL(MUL) (((MUL) == RCC_PLL_MUL2)  || ((MUL) == RCC_PLL_MUL3)   || \
                             ((MUL) == RCC_PLL_MUL4)  || ((MUL) == RCC_PLL_MUL5)   || \
                             ((MUL) == RCC_PLL_MUL6)  || ((MUL) == RCC_PLL_MUL7)   || \
                             ((MUL) == RCC_PLL_MUL8)  || ((MUL) == RCC_PLL_MUL9)   || \
                             ((MUL) == RCC_PLL_MUL10) || ((MUL) == RCC_PLL_MUL11)  || \
                             ((MUL) == RCC_PLL_MUL12) || ((MUL) == RCC_PLL_MUL13)  || \
                             ((MUL) == RCC_PLL_MUL14) || ((MUL) == RCC_PLL_MUL15)  || \
                             ((MUL) == RCC_PLL_MUL16))
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

#define IS_RCC_CLOCKTYPE(CLK) ((((CLK) & RCC_CLOCKTYPE_SYSCLK) == RCC_CLOCKTYPE_SYSCLK) || \
                               (((CLK) & RCC_CLOCKTYPE_HCLK)   == RCC_CLOCKTYPE_HCLK)   || \
                               (((CLK) & RCC_CLOCKTYPE_PCLK1)  == RCC_CLOCKTYPE_PCLK1)  || \
                               (((CLK) & RCC_CLOCKTYPE_PCLK2)  == RCC_CLOCKTYPE_PCLK2))
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source RCC System Clock Source
  * @{
  */
#define RCC_SYSCLKSOURCE_HSI             RCC_CFGR_SW_HSI
#define RCC_SYSCLKSOURCE_HSE             RCC_CFGR_SW_HSE
#define RCC_SYSCLKSOURCE_PLLCLK          RCC_CFGR_SW_PLL

#define IS_RCC_SYSCLKSOURCE(SOURCE)  (((SOURCE) == RCC_SYSCLKSOURCE_HSI) || \
                                      ((SOURCE) == RCC_SYSCLKSOURCE_HSE) || \
                                      ((SOURCE) == RCC_SYSCLKSOURCE_PLLCLK))
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source_Status RCC System Clock Source Status
  * @{
  */
#define RCC_SYSCLKSOURCE_STATUS_HSI      RCC_CFGR_SWS_HSI
#define RCC_SYSCLKSOURCE_STATUS_HSE      RCC_CFGR_SWS_HSE
#define RCC_SYSCLKSOURCE_STATUS_PLLCLK   RCC_CFGR_SWS_PLL

#define IS_RCC_SYSCLKSOURCE_STATUS(SOURCE) (((SOURCE) == RCC_SYSCLKSOURCE_STATUS_HSI) || \
                                            ((SOURCE) == RCC_SYSCLKSOURCE_STATUS_HSE) || \
                                            ((SOURCE) == RCC_SYSCLKSOURCE_STATUS_PLLCLK)))
/**
  * @}
  */

/** @defgroup RCC_AHB_Clock_Source RCC AHB Clock Source
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

#define IS_RCC_SYSCLK_DIV(DIV) (((DIV) == RCC_SYSCLK_DIV1)   || ((DIV) == RCC_SYSCLK_DIV2) || \
                                ((DIV) == RCC_SYSCLK_DIV4)   || ((DIV) == RCC_SYSCLK_DIV8) || \
                                ((DIV) == RCC_SYSCLK_DIV16)  || ((DIV) == RCC_SYSCLK_DIV64) || \
                                ((DIV) == RCC_SYSCLK_DIV128) || ((DIV) == RCC_SYSCLK_DIV256) || \
                                ((DIV) == RCC_SYSCLK_DIV512))
/**
  * @}
  */

/** @defgroup RCC_APB1_APB2_Clock_Source RCC APB1 APB2 Clock Source
  * @{
  */
#define RCC_HCLK_DIV1                    RCC_CFGR_PPRE1_DIV1
#define RCC_HCLK_DIV2                    RCC_CFGR_PPRE1_DIV2
#define RCC_HCLK_DIV4                    RCC_CFGR_PPRE1_DIV4
#define RCC_HCLK_DIV8                    RCC_CFGR_PPRE1_DIV8
#define RCC_HCLK_DIV16                   RCC_CFGR_PPRE1_DIV16

#define IS_RCC_HCLK_DIV(DIV) (((DIV) == RCC_HCLK_DIV1) || ((DIV) == RCC_HCLK_DIV2) || \
                              ((DIV) == RCC_HCLK_DIV4) || ((DIV) == RCC_HCLK_DIV8) || \
                              ((DIV) == RCC_HCLK_DIV16))
/**
  * @}
  */

/** @defgroup RCC_RTC_Clock_Source RCC RTC Clock Source
  * @{
  */
#define RCC_RTCCLKSOURCE_NONE            RCC_BDCR_RTCSEL_NOCLOCK
#define RCC_RTCCLKSOURCE_LSE             RCC_BDCR_RTCSEL_LSE
#define RCC_RTCCLKSOURCE_LSI             RCC_BDCR_RTCSEL_LSI
#define RCC_RTCCLKSOURCE_HSE_DIV32       RCC_BDCR_RTCSEL_HSE

#define IS_RCC_RTCCLKSOURCE(SOURCE)  (((SOURCE) == RCC_RTCCLKSOURCE_NONE) || \
                                      ((SOURCE) == RCC_RTCCLKSOURCE_LSE)  || \
                                      ((SOURCE) == RCC_RTCCLKSOURCE_LSI)  || \
                                      ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV32))
/**
  * @}
  */

/** @defgroup RCC_USART2_Clock_Source RCC USART2 Clock Source
  * @{
  */
#define RCC_USART2CLKSOURCE_PCLK1        RCC_CFGR3_USART2SW_PCLK
#define RCC_USART2CLKSOURCE_SYSCLK       RCC_CFGR3_USART2SW_SYSCLK
#define RCC_USART2CLKSOURCE_LSE          RCC_CFGR3_USART2SW_LSE
#define RCC_USART2CLKSOURCE_HSI          RCC_CFGR3_USART2SW_HSI

#define IS_RCC_USART2CLKSOURCE(SOURCE)  (((SOURCE) == RCC_USART2CLKSOURCE_PCLK1)  || \
                                         ((SOURCE) == RCC_USART2CLKSOURCE_SYSCLK) || \
                                         ((SOURCE) == RCC_USART2CLKSOURCE_LSE)    || \
                                         ((SOURCE) == RCC_USART2CLKSOURCE_HSI))
/**
  * @}
  */

/** @defgroup RCC_USART3_Clock_Source RCC USART3 Clock Source
  * @{
  */
#define RCC_USART3CLKSOURCE_PCLK1        RCC_CFGR3_USART3SW_PCLK
#define RCC_USART3CLKSOURCE_SYSCLK       RCC_CFGR3_USART3SW_SYSCLK
#define RCC_USART3CLKSOURCE_LSE          RCC_CFGR3_USART3SW_LSE
#define RCC_USART3CLKSOURCE_HSI          RCC_CFGR3_USART3SW_HSI

#define IS_RCC_USART3CLKSOURCE(SOURCE)  (((SOURCE) == RCC_USART3CLKSOURCE_PCLK1)  || \
                                         ((SOURCE) == RCC_USART3CLKSOURCE_SYSCLK) || \
                                         ((SOURCE) == RCC_USART3CLKSOURCE_LSE)    || \
                                         ((SOURCE) == RCC_USART3CLKSOURCE_HSI))
/**
  * @}
  */

/** @defgroup RCC_I2C1_Clock_Source RCC I2C1 Clock Source
  * @{
  */
#define RCC_I2C1CLKSOURCE_HSI            RCC_CFGR3_I2C1SW_HSI
#define RCC_I2C1CLKSOURCE_SYSCLK         RCC_CFGR3_I2C1SW_SYSCLK

#define IS_RCC_I2C1CLKSOURCE(SOURCE)  (((SOURCE) == RCC_I2C1CLKSOURCE_HSI) || \
                                       ((SOURCE) == RCC_I2C1CLKSOURCE_SYSCLK))
/**
  * @}
  */

/** @defgroup RCC_MCOx_Index RCC MCOx Index
  * @{
  */
#define RCC_MCO                          ((uint32_t)0x00000000)

#define IS_RCC_MCO(MCOx) ((MCOx) == RCC_MCO)
/**
  * @}
  */

/** @defgroup RCC_Interrupt RCC Interrupt
  * @{
  */
#define RCC_IT_LSIRDY                    ((uint32_t)0x00000001)
#define RCC_IT_LSERDY                    ((uint32_t)0x00000002)
#define RCC_IT_HSIRDY                    ((uint32_t)0x00000004)
#define RCC_IT_HSERDY                    ((uint32_t)0x00000008)
#define RCC_IT_PLLRDY                    ((uint32_t)0x00000010)
#define RCC_IT_CSS                       ((uint32_t)0x00000080)
/**
  * @}
  */  
  
/** @defgroup RCC_Flag RCC Flag
  *        Elements values convention: 0XXYYYYYb
  *           - YYYYY  : Flag position in the register
  *           - XX  : Register index
  *                 - 01: CR register
  *                 - 10: BDCR register
  *                 - 11: CSR register
  * @{
  */
#define CR_REG_INDEX                     1U
#define BDCR_REG_INDEX                   2U
#define CSR_REG_INDEX                    3U

/* Flags in the CR register */
#define RCC_FLAG_HSIRDY                  ((uint32_t)((CR_REG_INDEX << 5U) | (uint32_t)(POSITION_VAL(RCC_CR_HSIRDY))))
#define RCC_FLAG_HSERDY                  ((uint32_t)((CR_REG_INDEX << 5U) | (uint32_t)(POSITION_VAL(RCC_CR_HSERDY))))
#define RCC_FLAG_PLLRDY                  ((uint32_t)((CR_REG_INDEX << 5U) | (uint32_t)(POSITION_VAL(RCC_CR_PLLRDY))))

/* Flags in the BDCR register */
#define RCC_FLAG_LSERDY                  ((uint32_t)((BDCR_REG_INDEX << 5U) | (uint32_t)(POSITION_VAL(RCC_BDCR_LSERDY))))

/* Flags in the CSR register */
#define RCC_FLAG_LSIRDY                  ((uint32_t)((CSR_REG_INDEX << 5U) | (uint32_t)(POSITION_VAL(RCC_CSR_LSIRDY))))
#define RCC_FLAG_RMV                     ((uint32_t)((CSR_REG_INDEX << 5U) | (uint32_t)(POSITION_VAL(RCC_CSR_RMVF))))
#define RCC_FLAG_OBLRST                  ((uint32_t)((CSR_REG_INDEX << 5U) | (uint32_t)(POSITION_VAL(RCC_CSR_OBLRSTF))))
#define RCC_FLAG_PINRST                  ((uint32_t)((CSR_REG_INDEX << 5U) | (uint32_t)(POSITION_VAL(RCC_CSR_PINRSTF))))
#define RCC_FLAG_PORRST                  ((uint32_t)((CSR_REG_INDEX << 5U) | (uint32_t)(POSITION_VAL(RCC_CSR_PORRSTF))))
#define RCC_FLAG_SFTRST                  ((uint32_t)((CSR_REG_INDEX << 5U) | (uint32_t)(POSITION_VAL(RCC_CSR_SFTRSTF))))
#define RCC_FLAG_IWDGRST                 ((uint32_t)((CSR_REG_INDEX << 5U) | (uint32_t)(POSITION_VAL(RCC_CSR_IWDGRSTF))))
#define RCC_FLAG_WWDGRST                 ((uint32_t)((CSR_REG_INDEX << 5U) | (uint32_t)(POSITION_VAL(RCC_CSR_WWDGRSTF))))
#define RCC_FLAG_LPWRRST                 ((uint32_t)((CSR_REG_INDEX << 5U) | (uint32_t)(POSITION_VAL(RCC_CSR_LPWRRSTF))))
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

/** @defgroup RCC_AHB_Clock_Enable_Disable RCC AHB Clock Enable Disable
  * @brief  Enable or disable the AHB peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{  
  */
#define __GPIOA_CLK_ENABLE()         (RCC->AHBENR |= (RCC_AHBENR_GPIOAEN))
#define __GPIOB_CLK_ENABLE()         (RCC->AHBENR |= (RCC_AHBENR_GPIOBEN))
#define __GPIOC_CLK_ENABLE()         (RCC->AHBENR |= (RCC_AHBENR_GPIOCEN))
#define __GPIOD_CLK_ENABLE()         (RCC->AHBENR |= (RCC_AHBENR_GPIODEN))
#define __GPIOF_CLK_ENABLE()         (RCC->AHBENR |= (RCC_AHBENR_GPIOFEN))
#define __CRC_CLK_ENABLE()           (RCC->AHBENR |= (RCC_AHBENR_CRCEN))
#define __DMA1_CLK_ENABLE()          (RCC->AHBENR |= (RCC_AHBENR_DMA1EN))
#define __SRAM_CLK_ENABLE()          (RCC->AHBENR |= (RCC_AHBENR_SRAMEN))
#define __FLITF_CLK_ENABLE()         (RCC->AHBENR |= (RCC_AHBENR_FLITFEN))
#define __TSC_CLK_ENABLE()           (RCC->AHBENR |= (RCC_AHBENR_TSCEN))

#define __GPIOA_CLK_DISABLE()        (RCC->AHBENR &= ~(RCC_AHBENR_GPIOAEN))
#define __GPIOB_CLK_DISABLE()        (RCC->AHBENR &= ~(RCC_AHBENR_GPIOBEN))
#define __GPIOC_CLK_DISABLE()        (RCC->AHBENR &= ~(RCC_AHBENR_GPIOCEN))
#define __GPIOD_CLK_DISABLE()        (RCC->AHBENR &= ~(RCC_AHBENR_GPIODEN))
#define __GPIOF_CLK_DISABLE()        (RCC->AHBENR &= ~(RCC_AHBENR_GPIOFEN))
#define __CRC_CLK_DISABLE()          (RCC->AHBENR &= ~(RCC_AHBENR_CRCEN))
#define __DMA1_CLK_DISABLE()         (RCC->AHBENR &= ~(RCC_AHBENR_DMA1EN))
#define __SRAM_CLK_DISABLE()         (RCC->AHBENR &= ~(RCC_AHBENR_SRAMEN))
#define __FLITF_CLK_DISABLE()        (RCC->AHBENR &= ~(RCC_AHBENR_FLITFEN))
#define __TSC_CLK_DISABLE()          (RCC->AHBENR &= ~(RCC_AHBENR_TSCEN))
/**
  * @}
  */

/** @defgroup RCC_APB1_Clock_Enable_Disable RCC APB1 Clock Enable Disable
  * @brief  Enable or disable the Low Speed APB (APB1) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{   
  */
#define __TIM2_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_TIM2EN))
#define __TIM6_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_TIM6EN))
#define __WWDG_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_WWDGEN))
#define __USART2_CLK_ENABLE()  (RCC->APB1ENR |= (RCC_APB1ENR_USART2EN))
#define __USART3_CLK_ENABLE()  (RCC->APB1ENR |= (RCC_APB1ENR_USART3EN))
#define __I2C1_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_I2C1EN))
#define __PWR_CLK_ENABLE()     (RCC->APB1ENR |= (RCC_APB1ENR_PWREN))
#define __DAC1_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_DAC1EN))

#define __TIM2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM2EN))
#define __TIM6_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM6EN))
#define __WWDG_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_WWDGEN))
#define __USART2_CLK_DISABLE() (RCC->APB1ENR &= ~(RCC_APB1ENR_USART2EN))
#define __USART3_CLK_DISABLE() (RCC->APB1ENR &= ~(RCC_APB1ENR_USART3EN))
#define __I2C1_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_I2C1EN))
#define __PWR_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_PWREN))
#define __DAC1_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_DAC1EN))
/**
  * @}
  */
  
/** @defgroup RCC_APB2_Clock_Enable_Disable RCC APB2 Clock Enable Disable
  * @brief  Enable or disable the High Speed APB (APB2) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{   
  */
#define __SYSCFG_CLK_ENABLE()  (RCC->APB2ENR |= (RCC_APB2ENR_SYSCFGEN))
#define __TIM15_CLK_ENABLE()   (RCC->APB2ENR |= (RCC_APB2ENR_TIM15EN))
#define __TIM16_CLK_ENABLE()   (RCC->APB2ENR |= (RCC_APB2ENR_TIM16EN))
#define __TIM17_CLK_ENABLE()   (RCC->APB2ENR |= (RCC_APB2ENR_TIM17EN))
#define __USART1_CLK_ENABLE()  (RCC->APB2ENR |= (RCC_APB2ENR_USART1EN))

#define __SYSCFG_CLK_DISABLE() (RCC->APB2ENR &= ~(RCC_APB2ENR_SYSCFGEN))
#define __TIM15_CLK_DISABLE()  (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM15EN))
#define __TIM16_CLK_DISABLE()  (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM16EN))
#define __TIM17_CLK_DISABLE()  (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM17EN))
#define __USART1_CLK_DISABLE() (RCC->APB2ENR &= ~(RCC_APB2ENR_USART1EN))
/**
  * @}
  */

/** @defgroup RCC_AHB_Force_Release_Reset RCC AHB Force Release Reset
  * @brief  Force or release AHB peripheral reset.
  * @{   
  */
#define __AHB_FORCE_RESET()     (RCC->AHBRSTR = 0xFFFFFFFF)
#define __GPIOA_FORCE_RESET()   (RCC->AHBRSTR |= (RCC_AHBRSTR_GPIOARST))
#define __GPIOB_FORCE_RESET()   (RCC->AHBRSTR |= (RCC_AHBRSTR_GPIOBRST))
#define __GPIOC_FORCE_RESET()   (RCC->AHBRSTR |= (RCC_AHBRSTR_GPIOCRST))
#define __GPIOD_FORCE_RESET()   (RCC->AHBRSTR |= (RCC_AHBRSTR_GPIODRST))
#define __GPIOF_FORCE_RESET()   (RCC->AHBRSTR |= (RCC_AHBRSTR_GPIOFRST))
#define __TSC_FORCE_RESET()     (RCC->AHBRSTR |= (RCC_AHBRSTR_TSCRST))

#define __AHB_RELEASE_RESET()   (RCC->AHBRSTR = 0x00)
#define __GPIOA_RELEASE_RESET() (RCC->AHBRSTR &= ~(RCC_AHBRSTR_GPIOARST))
#define __GPIOB_RELEASE_RESET() (RCC->AHBRSTR &= ~(RCC_AHBRSTR_GPIOBRST))
#define __GPIOC_RELEASE_RESET() (RCC->AHBRSTR &= ~(RCC_AHBRSTR_GPIOCRST))
#define __GPIOD_RELEASE_RESET() (RCC->AHBRSTR &= ~(RCC_AHBRSTR_GPIODRST))
#define __GPIOF_RELEASE_RESET() (RCC->AHBRSTR &= ~(RCC_AHBRSTR_GPIOFRST))
#define __TSC_RELEASE_RESET()   (RCC->AHBRSTR &= ~(RCC_AHBRSTR_TSCRST))
/**
  * @}
  */

/** @defgroup RCC_APB1_Force_Release_Reset RCC APB1 Force Release Reset
  * @brief  Force or release APB1 peripheral reset.
  * @{   
  */
#define __APB1_FORCE_RESET()     (RCC->APB1RSTR = 0xFFFFFFFF)
#define __TIM2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM2RST))
#define __TIM6_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM6RST))
#define __WWDG_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_WWDGRST))
#define __USART2_FORCE_RESET()   (RCC->APB1RSTR |= (RCC_APB1RSTR_USART2RST))
#define __USART3_FORCE_RESET()   (RCC->APB1RSTR |= (RCC_APB1RSTR_USART3RST))
#define __I2C1_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_I2C1RST))
#define __PWR_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_PWRRST))
#define __DAC1_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_DAC1RST))

#define __APB1_RELEASE_RESET()   (RCC->APB1RSTR = 0x00)
#define __TIM2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM2RST))
#define __TIM6_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM6RST))
#define __WWDG_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_WWDGRST))
#define __USART2_RELEASE_RESET() (RCC->APB1RSTR &= ~(RCC_APB1RSTR_USART2RST))
#define __USART3_RELEASE_RESET() (RCC->APB1RSTR &= ~(RCC_APB1RSTR_USART3RST))
#define __I2C1_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C1RST))
#define __PWR_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_PWRRST))
#define __DAC1_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_DAC1RST))
/**
  * @}
  */

/** @defgroup RCC_APB2_Force_Release_Reset RCC APB2 Force Release Reset
  * @brief  Force or release APB2 peripheral reset.
  * @{   
  */
#define __APB2_FORCE_RESET()     (RCC->APB2RSTR = 0xFFFFFFFF)
#define __SYSCFG_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_SYSCFGRST))
#define __TIM15_FORCE_RESET()    (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM15RST))
#define __TIM16_FORCE_RESET()    (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM16RST))
#define __TIM17_FORCE_RESET()    (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM17RST))
#define __USART1_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_USART1RST))

#define __APB2_RELEASE_RESET()   (RCC->APB2RSTR = 0x00)
#define __SYSCFG_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SYSCFGRST))
#define __TIM15_RELEASE_RESET()  (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM15RST))
#define __TIM16_RELEASE_RESET()  (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM16RST))
#define __TIM17_RELEASE_RESET()  (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM17RST))
#define __USART1_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_USART1RST))
/**
  * @}
  */

/** @defgroup RCC_HSI_Configuration RCC HSI Configuration
  * @{   
  */ 

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
#define __HAL_RCC_HSI_ENABLE() (*(__IO uint32_t *)CR_HSION_BB = ENABLE)
#define __HAL_RCC_HSI_DISABLE() (*(__IO uint32_t *)CR_HSION_BB = DISABLE)


/** @brief  Macro to adjust the Internal High Speed oscillator (HSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  * @param  __HSICalibrationValue__: specifies the calibration trimming value.
  *         This parameter must be a number between 0 and 0x1F.
  */
#define __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(__HSICalibrationValue__) \
                  MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, (uint32_t)(__HSICalibrationValue__) << POSITION_VAL(RCC_CR_HSITRIM))
/**
  * @}
  */

/** @defgroup RCC_LSI_Configuration  RCC LSI Configuration
  * @{   
  */ 

/** @brief  Macro to enable or disable the Internal Low Speed oscillator (LSI).
  * @note   After enabling the LSI, the application software should wait on
  *         LSIRDY flag to be set indicating that LSI clock is stable and can
  *         be used to clock the IWDG and/or the RTC.
  * @note   LSI can not be disabled if the IWDG is running.
  * @note   When the LSI is stopped, LSIRDY flag goes low after 6 LSI oscillator
  *         clock cycles.
  */
#define __HAL_RCC_LSI_ENABLE() (*(__IO uint32_t *)CSR_LSION_BB = ENABLE)
#define __HAL_RCC_LSI_DISABLE() (*(__IO uint32_t *)CSR_LSION_BB = DISABLE)
/**
  * @}
  */

/** @defgroup RCC_HSE_Configuration RCC HSE Configuration
  * @{   
  */ 

/**
  * @brief  Macro to configure the External High Speed oscillator (HSE).
  * @note   After enabling the HSE (RCC_HSE_ON or RCC_HSE_Bypass), the application
  *         software should wait on HSERDY flag to be set indicating that HSE clock
  *         is stable and can be used to clock the PLL and/or system clock.
  * @note   HSE state can not be changed if it is used directly or through the
  *         PLL as system clock. In this case, you have to select another source
  *         of the system clock then change the HSE state (ex. disable it).
  * @note   The HSE is stopped by hardware when entering STOP and STANDBY modes.
  * @note   This function reset the CSSON bit, so if the Clock security system(CSS)
  *         was previously enabled you have to enable it again after calling this
  *         function.
  * @param  __STATE__: specifies the new state of the HSE.
  *          This parameter can be one of the following values:
  *            @arg RCC_HSE_OFF: turn OFF the HSE oscillator, HSERDY flag goes low after
  *                              6 HSE oscillator clock cycles.
  *            @arg RCC_HSE_ON: turn ON the HSE oscillator
  *            @arg RCC_HSE_BYPASS: HSE oscillator bypassed with external clock
  */
#define __HAL_RCC_HSE_CONFIG(__STATE__) (*(__IO uint8_t *)CR_BYTE2_ADDRESS = (__STATE__))
 /**
  * @}
  */

/** @defgroup RCC_LSE_Configuration RCC LSE Configuration
  * @{   
  */   
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
  *            @arg RCC_LSE_ON: turn ON the LSE oscillator
  *            @arg RCC_LSE_BYPASS: LSE oscillator bypassed with external clock
  */
#define __HAL_RCC_LSE_CONFIG(__STATE__) \
                  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSEON|RCC_BDCR_LSEBYP, (uint32_t)(__STATE__))
/**
  * @}
  */

/** @defgroup RCC_I2Cx_Clock_Config RCC I2Cx Clock Config
  * @{   
  */ 
/** @brief Macro to configure the I2C1 clock (I2C1CLK).
  * @param  __I2C1CLKSource__: specifies the I2C1 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_I2C1CLKSOURCE_HSI: HSI selected as I2C1 clock
  *            @arg RCC_I2C1CLKSOURCE_SYSCLK: System Clock selected as I2C1 clock
  */
#define __HAL_RCC_I2C1_CONFIG(__I2C1CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_I2C1SW, (uint32_t)(__I2C1CLKSource__))

/** @brief  Macro to get the I2C1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_I2C1CLKSOURCE_HSI: HSI selected as I2C1 clock
  *            @arg RCC_I2C1CLKSOURCE_SYSCLK: System Clock selected as I2C1 clock
  */
#define __HAL_RCC_GET_I2C1_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_I2C1SW)))
/**
  * @}
  */

/** @defgroup RCC_USARTx_Clock_Config RCC USARTx Clock Config
  * @{   
  */ 
    
/** @brief Macro to configure the USART1 clock (USART1CLK).
  * @param  __USART1CLKSource__: specifies the USART1 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_USART1CLKSOURCE_PCLK2 or RCC_USART1CLKSOURCE_PCLK1: PCLK2 or PCLK1 selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_HSI: HSI selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_SYSCLK: System Clock selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_LSE: LSE selected as USART1 clock
  */
#define __HAL_RCC_USART1_CONFIG(__USART1CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_USART1SW, (uint32_t)(__USART1CLKSource__))

/** @brief  Macro to get the USART1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_USART1CLKSOURCE_PCLK2 or RCC_USART1CLKSOURCE_PCLK1: PCLK2 or PCLK1 selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_HSI: HSI selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_SYSCLK: System Clock selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_LSE: LSE selected as USART1 clock
  */
#define __HAL_RCC_GET_USART1_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_USART1SW)))

/** @brief  Macro to configure the USART2 clock (USART2CLK).
  * @param  __USART2CLKSource__: specifies the USART2 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_USART2CLKSOURCE_PCLK1: PCLK1 selected as USART2 clock
  *            @arg RCC_USART2CLKSOURCE_HSI: HSI selected as USART2 clock
  *            @arg RCC_USART2CLKSOURCE_SYSCLK: System Clock selected as USART2 clock
  *            @arg RCC_USART2CLKSOURCE_LSE: LSE selected as USART2 clock
  */
#define __HAL_RCC_USART2_CONFIG(__USART2CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_USART2SW, (uint32_t)(__USART2CLKSource__))

/** @brief  Macro to get the USART2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_USART2CLKSOURCE_PCLK1: PCLK1 selected as USART2 clock
  *            @arg RCC_USART2CLKSOURCE_HSI: HSI selected as USART2 clock
  *            @arg RCC_USART2CLKSOURCE_SYSCLK: System Clock selected as USART2 clock
  *            @arg RCC_USART2CLKSOURCE_LSE: LSE selected as USART2 clock
  */
#define __HAL_RCC_GET_USART2_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_USART2SW)))

/** @brief  Macro to configure the USART3 clock (USART3CLK).
  * @param  __USART3CLKSource__: specifies the USART3 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_USART3CLKSOURCE_PCLK1: PCLK1 selected as USART3 clock
  *            @arg RCC_USART3CLKSOURCE_HSI: HSI selected as USART3 clock
  *            @arg RCC_USART3CLKSOURCE_SYSCLK: System Clock selected as USART3 clock
  *            @arg RCC_USART3CLKSOURCE_LSE: LSE selected as USART3 clock
  */
#define __HAL_RCC_USART3_CONFIG(__USART3CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_USART3SW, (uint32_t)(__USART3CLKSource__))

/** @brief  Macro to get the USART3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_USART3CLKSOURCE_PCLK1: PCLK1 selected as USART3 clock
  *            @arg RCC_USART3CLKSOURCE_HSI: HSI selected as USART3 clock
  *            @arg RCC_USART3CLKSOURCE_SYSCLK: System Clock selected as USART3 clock
  *            @arg RCC_USART3CLKSOURCE_LSE: LSE selected as USART3 clock
  */
#define __HAL_RCC_GET_USART3_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_USART3SW)))
/**
  * @}
  */

/** @defgroup RCC_RTC_Clock_Configuration RCC RTC Clock Configuration
  * @{   
  */ 
/** @brief  Macros to enable or disable the the RTC clock.
  * @note   These macros must be used only after the RTC clock source was selected.
  */
#define __HAL_RCC_RTC_ENABLE() (*(__IO uint32_t *)BDCR_RTCEN_BB = ENABLE)
#define __HAL_RCC_RTC_DISABLE() (*(__IO uint32_t *)BDCR_RTCEN_BB = DISABLE)

/** @brief  Macro to configure the RTC clock (RTCCLK).
  * @note   As the RTC clock configuration bits are in the Backup domain and write
  *         access is denied to this domain after reset, you have to enable write
  *         access using the Power Backup Access macro before to configure
  *         the RTC clock source (to be done once after reset).
  * @note   Once the RTC clock is configured it can't be changed unless the
  *         Backup domain is reset using __HAL_RCC_BackupReset_RELEASE() macro, or by
  *         a Power On Reset (POR).
  * @param  __RTCCLKSource__: specifies the RTC clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_RTCCLKSOURCE_NONE: No clock selected as RTC clock
  *            @arg RCC_RTCCLKSOURCE_LSE: LSE selected as RTC clock
  *            @arg RCC_RTCCLKSOURCE_LSI: LSI selected as RTC clock
  *            @arg RCC_RTCCLKSOURCE_HSE_DIV32: HSE clock divided by 32
  *
  * @note   If the LSE is used as RTC clock source, the RTC continues to
  *         work in STOP and STANDBY modes, and can be used as wakeup source.
  *         However, when the LSI clock and HSE clock divided by 32 is used as RTC clock source,
  *         the RTC cannot be used in STOP and STANDBY modes.
  * @note   The system must always be configured so as to get a PCLK frequency greater than or
  *             equal to the RTCCLK frequency for a proper operation of the RTC.
  */
#define __HAL_RCC_RTC_CONFIG(__RTCCLKSource__) \
                  MODIFY_REG(RCC->BDCR, RCC_BDCR_RTCSEL, (uint32_t)(__RTCCLKSource__))

/** @brief  Macro to get the RTC clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_RTCCLKSOURCE_NONE: No clock selected as RTC clock
  *            @arg RCC_RTCCLKSOURCE_LSE: LSE selected as RTC clock
  *            @arg RCC_RTCCLKSOURCE_LSI: LSI selected as RTC clock
  *            @arg RCC_RTCCLKSOURCE_HSE_DIV32: HSE clock divided by 32 selected as RTC clock
  */
#define __HAL_RCC_GET_RTC_SOURCE() ((uint32_t)(READ_BIT(RCC->BDCR, RCC_BDCR_RTCSEL)))
/**
  * @}
  */

/** @defgroup RCC_Force_Release_Backup RCC Force Release Backup
  * @{   
  */ 

/** @brief  Macro to force or release the Backup domain reset.
  * @note   These macros reset the RTC peripheral (including the backup registers)
  *         and the RTC clock source selection in RCC_CSR register.
  * @note   The BKPSRAM is not affected by this reset.
  */
#define __HAL_RCC_BACKUPRESET_FORCE() (*(__IO uint32_t *)BDCR_BDRST_BB = ENABLE)
#define __HAL_RCC_BACKUPRESET_RELEASE() (*(__IO uint32_t *)BDCR_BDRST_BB = DISABLE)
/**
  * @}
  */

/** @defgroup RCC_PLL_Configuration RCC PLL Configuration
  * @{   
  */ 

/** @brief  Macro to enable or disable the PLL.
  * @note   After enabling the PLL, the application software should wait on
  *         PLLRDY flag to be set indicating that PLL clock is stable and can
  *         be used as system clock source.
  * @note   The PLL can not be disabled if it is used as system clock source
  * @note   The PLL is disabled by hardware when entering STOP and STANDBY modes.
  */
#define __HAL_RCC_PLL_ENABLE() (*(__IO uint32_t *)CR_PLLON_BB = ENABLE)
#define __HAL_RCC_PLL_DISABLE() (*(__IO uint32_t *)CR_PLLON_BB = DISABLE)
/**
  * @}
  */                      

/** @defgroup RCC_Get_Clock_source RCC Get Clock source
  * @{   
  */ 
                      
/** @brief  Macro to get the clock source used as system clock.
  * @retval The clock source used as system clock.
  *         The returned value can be one of the following value:
  *             @arg RCC_SYSCLKSOURCE_STATUS_HSI: HSI used as system clock
  *             @arg RCC_SYSCLKSOURCE_STATUS_HSE: HSE used as system clock
  *             @arg RCC_SYSCLKSOURCE_STATUS_PLLCLK: PLL used as system clock
  */
#define __HAL_RCC_GET_SYSCLK_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_SWS)))

/** @brief  Macro to get the oscillator used as PLL clock source.
  * @retval The oscillator used as PLL clock source. The returned value can be one
  *         of the following:
  *              - RCC_PLLSOURCE_HSI: HSI oscillator is used as PLL clock source.
  *              - RCC_PLLSOURCE_HSE: HSE oscillator is used as PLL clock source.
  */
#define __HAL_RCC_GET_PLL_OSCSOURCE() ((uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_PLLSRC)))
/**
  * @}
  */ 

/** @defgroup RCC_Flags_Interrupts_Management RCC Flags Interrupts Management
  * @brief macros to manage the specified RCC Flags and interrupts.
  * @{
  */

/** @brief  Enable RCC interrupt (Perform Byte access to RCC_CIR[12:8] bits to enable
  *         the selected interrupts.).
  * @param  __INTERRUPT__: specifies the RCC interrupt sources to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_IT_LSIRDY: LSI ready interrupt enable
  *            @arg RCC_IT_LSERDY: LSE ready interrupt enable
  *            @arg RCC_IT_HSIRDY: HSI ready interrupt enable
  *            @arg RCC_IT_HSERDY: HSE ready interrupt enable
  *            @arg RCC_IT_PLLRDY:  PLL ready interrupt enable
  */
#define __HAL_RCC_ENABLE_IT(__INTERRUPT__) (*(__IO uint8_t *)CIR_BYTE1_ADDRESS |= (__INTERRUPT__))

/** @brief  Disable RCC interrupt (Perform Byte access to RCC_CIR[12:8] bits to disable
  *         the selected interrupts.).
  * @param  __INTERRUPT__: specifies the RCC interrupt sources to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_IT_LSIRDYIE: LSI ready interrupt enable
  *            @arg RCC_IT_LSERDYIE: LSE ready interrupt enable
  *            @arg RCC_IT_HSIRDYIE: HSI ready interrupt enable
  *            @arg RCC_IT_HSERDYIE: HSE ready interrupt enable
  *            @arg RCC_IT_PLLRDYIE:  PLL ready interrupt enable
  */
#define __HAL_RCC_DISABLE_IT(__INTERRUPT__) (*(__IO uint8_t *)CIR_BYTE1_ADDRESS &= ~(__INTERRUPT__))

/** @brief  Clear the RCC's interrupt pending bits ( Perform Byte access to RCC_CIR[23:16]
  *         bits to clear the selected interrupt pending bits.
  * @param  __IT__: specifies the interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_IT_LSIRDYC: LSI ready interrupt clear
  *            @arg RCC_IT_LSERDYC: LSE ready interrupt clear
  *            @arg RCC_IT_HSIRDYC: HSI ready interrupt clear
  *            @arg RCC_IT_HSERDYC: HSE ready interrupt clear
  *            @arg RCC_IT_PLLRDYC:  PLL ready interrupt clear
  *            @arg RCC_IT_CSSC:  Clock Security System interrupt clear
  */
#define __HAL_RCC_CLEAR_IT(__IT__) (*(__IO uint8_t *)CIR_BYTE2_ADDRESS = (__IT__))

/** @brief  Check the RCC's interrupt has occurred or not.
  * @param  __IT__: specifies the RCC interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg RCC_IT_LSIRDYF: LSI ready interrupt flag
  *            @arg RCC_IT_LSERDYF: LSE ready interrupt flag
  *            @arg RCC_IT_HSIRDYF: HSI ready interrupt flag
  *            @arg RCC_IT_HSERDYF: HSE ready interrupt flag
  *            @arg RCC_IT_PLLRDYF: PLL ready interrupt flag
  *            @arg RCC_IT_CSSF: Clock Security System interrupt flag
  * @retval The new state of __IT__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_IT(__IT__) ((RCC->CIR & (__IT__)) == (__IT__))

/** @brief  Set RMVF bit to clear the reset flags: RCC_FLAG_OBLRST, RCC_FLAG_PINRST, RCC_FLAG_PORRST, RCC_FLAG_SFTRST,
  * RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST, RCC_FLAG_LPWRRST
  */
#define __HAL_RCC_CLEAR_RESET_FLAGS() (*(__IO uint32_t *)CSR_RMVF_BB = ENABLE)

/** @brief  Check RCC flag is set or not.
  * @param  __FLAG__: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg RCC_FLAG_HSIRDY: HSI oscillator clock ready
  *            @arg RCC_FLAG_HSERDY: HSE oscillator clock ready
  *            @arg RCC_FLAG_PLLRDY: PLL clock ready
  *            @arg RCC_FLAG_LSERDY: LSE oscillator clock ready
  *            @arg RCC_FLAG_LSIRDY: LSI oscillator clock ready
  *            @arg RCC_FLAG_OBLRST: Option Byte Load reset
  *            @arg RCC_FLAG_PINRST: Pin reset
  *            @arg RCC_FLAG_PORRST: POR/PDR reset
  *            @arg RCC_FLAG_SFTRST: Software reset
  *            @arg RCC_FLAG_IWDGRST: Independent Watchdog reset
  *            @arg RCC_FLAG_WWDGRST: Window Watchdog reset
  *            @arg RCC_FLAG_LPWRRST: Low Power reset
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define RCC_FLAG_MASK  ((uint32_t)0x0000001F)
#define __HAL_RCC_GET_FLAG(__FLAG__) (((((__FLAG__) >> 5U) == CR_REG_INDEX)? RCC->CR : \
                                      ((((__FLAG__) >> 5U) == BDCR_REG_INDEX) ? RCC->BDCR : \
                                      RCC->CSR)) & (1U << ((__FLAG__) & RCC_FLAG_MASK)))


/**
  * @}
  */

/**
  * @}
  */

/* Include RCC HAL Extended module */
#include "stm32f3xx_hal_rcc_ex.h"

/* Exported functions --------------------------------------------------------*/

/** @addtogroup RCC_Exported_Functions
  * @{
  */

/** @addtogroup RCC_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */

/* Initialization and de-initialization functions  ***************************/
void HAL_RCC_DeInit(void);
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency);

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group2 Peripheral Control functions
  * @{
  */
  
/* Peripheral Control functions  *********************************************/
void     HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
void     HAL_RCC_EnableCSS(void);
void     HAL_RCC_DisableCSS(void);
uint32_t HAL_RCC_GetSysClockFreq(void);
uint32_t HAL_RCC_GetHCLKFreq(void);
uint32_t HAL_RCC_GetPCLK1Freq(void);
uint32_t HAL_RCC_GetPCLK2Freq(void);
void     HAL_RCC_GetOscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
void     HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t *pFLatency);

/* CSS NMI IRQ handler */
void HAL_RCC_NMI_IRQHandler(void);

/* User Callbacks in non blocking mode (IT mode) */ 
void HAL_RCC_CCSCallback(void);

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

#endif /* __STM32F3xx_HAL_RCC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
