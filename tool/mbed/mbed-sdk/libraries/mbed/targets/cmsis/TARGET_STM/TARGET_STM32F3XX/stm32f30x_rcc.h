/**
  ******************************************************************************
  * @file    stm32f30x_rcc.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file contains all the functions prototypes for the RCC 
  *          firmware library.
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
#ifndef __STM32F30x_RCC_H
#define __STM32F30x_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

typedef struct
{
  uint32_t SYSCLK_Frequency;
  uint32_t HCLK_Frequency;
  uint32_t PCLK1_Frequency;
  uint32_t PCLK2_Frequency;
  uint32_t ADC12CLK_Frequency;
  uint32_t ADC34CLK_Frequency;
  uint32_t I2C1CLK_Frequency;
  uint32_t I2C2CLK_Frequency;
  uint32_t I2C3CLK_Frequency;
  uint32_t TIM1CLK_Frequency;
  uint32_t HRTIM1CLK_Frequency;
  uint32_t TIM8CLK_Frequency;
  uint32_t USART1CLK_Frequency;
  uint32_t USART2CLK_Frequency;
  uint32_t USART3CLK_Frequency;
  uint32_t UART4CLK_Frequency;
  uint32_t UART5CLK_Frequency;
  uint32_t TIM15CLK_Frequency;
  uint32_t TIM16CLK_Frequency;
  uint32_t TIM17CLK_Frequency;  
}RCC_ClocksTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup RCC_Exported_Constants
  * @{
  */

/** @defgroup RCC_HSE_configuration 
  * @{
  */

#define RCC_HSE_OFF                      ((uint8_t)0x00)
#define RCC_HSE_ON                       ((uint8_t)0x01)
#define RCC_HSE_Bypass                   ((uint8_t)0x05)
#define IS_RCC_HSE(HSE) (((HSE) == RCC_HSE_OFF) || ((HSE) == RCC_HSE_ON) || \
                         ((HSE) == RCC_HSE_Bypass))

/**
  * @}
  */ 
 
/** @defgroup RCC_PLL_Clock_Source 
  * @{
  */

#define RCC_PLLSource_HSI_Div2           RCC_CFGR_PLLSRC_HSI_Div2
#define RCC_PLLSource_PREDIV1            RCC_CFGR_PLLSRC_PREDIV1
 
#define IS_RCC_PLL_SOURCE(SOURCE) (((SOURCE) == RCC_PLLSource_HSI_Div2) || \
                                   ((SOURCE) == RCC_PLLSource_PREDIV1))
/**
  * @}
  */ 

/** @defgroup RCC_PLL_Multiplication_Factor 
  * @{
  */

#define RCC_PLLMul_2                    RCC_CFGR_PLLMULL2
#define RCC_PLLMul_3                    RCC_CFGR_PLLMULL3
#define RCC_PLLMul_4                    RCC_CFGR_PLLMULL4
#define RCC_PLLMul_5                    RCC_CFGR_PLLMULL5
#define RCC_PLLMul_6                    RCC_CFGR_PLLMULL6
#define RCC_PLLMul_7                    RCC_CFGR_PLLMULL7
#define RCC_PLLMul_8                    RCC_CFGR_PLLMULL8
#define RCC_PLLMul_9                    RCC_CFGR_PLLMULL9
#define RCC_PLLMul_10                   RCC_CFGR_PLLMULL10
#define RCC_PLLMul_11                   RCC_CFGR_PLLMULL11
#define RCC_PLLMul_12                   RCC_CFGR_PLLMULL12
#define RCC_PLLMul_13                   RCC_CFGR_PLLMULL13
#define RCC_PLLMul_14                   RCC_CFGR_PLLMULL14
#define RCC_PLLMul_15                   RCC_CFGR_PLLMULL15
#define RCC_PLLMul_16                   RCC_CFGR_PLLMULL16
#define IS_RCC_PLL_MUL(MUL) (((MUL) == RCC_PLLMul_2) || ((MUL) == RCC_PLLMul_3)   || \
                             ((MUL) == RCC_PLLMul_4) || ((MUL) == RCC_PLLMul_5)   || \
                             ((MUL) == RCC_PLLMul_6) || ((MUL) == RCC_PLLMul_7)   || \
                             ((MUL) == RCC_PLLMul_8) || ((MUL) == RCC_PLLMul_9)   || \
                             ((MUL) == RCC_PLLMul_10) || ((MUL) == RCC_PLLMul_11) || \
                             ((MUL) == RCC_PLLMul_12) || ((MUL) == RCC_PLLMul_13) || \
                             ((MUL) == RCC_PLLMul_14) || ((MUL) == RCC_PLLMul_15) || \
                             ((MUL) == RCC_PLLMul_16))
/**
  * @}
  */

/** @defgroup RCC_PREDIV1_division_factor
  * @{
  */
#define  RCC_PREDIV1_Div1               RCC_CFGR2_PREDIV1_DIV1
#define  RCC_PREDIV1_Div2               RCC_CFGR2_PREDIV1_DIV2
#define  RCC_PREDIV1_Div3               RCC_CFGR2_PREDIV1_DIV3
#define  RCC_PREDIV1_Div4               RCC_CFGR2_PREDIV1_DIV4
#define  RCC_PREDIV1_Div5               RCC_CFGR2_PREDIV1_DIV5
#define  RCC_PREDIV1_Div6               RCC_CFGR2_PREDIV1_DIV6
#define  RCC_PREDIV1_Div7               RCC_CFGR2_PREDIV1_DIV7
#define  RCC_PREDIV1_Div8               RCC_CFGR2_PREDIV1_DIV8
#define  RCC_PREDIV1_Div9               RCC_CFGR2_PREDIV1_DIV9
#define  RCC_PREDIV1_Div10              RCC_CFGR2_PREDIV1_DIV10
#define  RCC_PREDIV1_Div11              RCC_CFGR2_PREDIV1_DIV11
#define  RCC_PREDIV1_Div12              RCC_CFGR2_PREDIV1_DIV12
#define  RCC_PREDIV1_Div13              RCC_CFGR2_PREDIV1_DIV13
#define  RCC_PREDIV1_Div14              RCC_CFGR2_PREDIV1_DIV14
#define  RCC_PREDIV1_Div15              RCC_CFGR2_PREDIV1_DIV15
#define  RCC_PREDIV1_Div16              RCC_CFGR2_PREDIV1_DIV16

#define IS_RCC_PREDIV1(PREDIV1) (((PREDIV1) == RCC_PREDIV1_Div1) || ((PREDIV1) == RCC_PREDIV1_Div2) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div3) || ((PREDIV1) == RCC_PREDIV1_Div4) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div5) || ((PREDIV1) == RCC_PREDIV1_Div6) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div7) || ((PREDIV1) == RCC_PREDIV1_Div8) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div9) || ((PREDIV1) == RCC_PREDIV1_Div10) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div11) || ((PREDIV1) == RCC_PREDIV1_Div12) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div13) || ((PREDIV1) == RCC_PREDIV1_Div14) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div15) || ((PREDIV1) == RCC_PREDIV1_Div16))
/**
  * @}
  */ 
 
/** @defgroup RCC_System_Clock_Source 
  * @{
  */

#define RCC_SYSCLKSource_HSI             RCC_CFGR_SW_HSI
#define RCC_SYSCLKSource_HSE             RCC_CFGR_SW_HSE
#define RCC_SYSCLKSource_PLLCLK          RCC_CFGR_SW_PLL
#define IS_RCC_SYSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSource_HSI) || \
                                      ((SOURCE) == RCC_SYSCLKSource_HSE) || \
                                      ((SOURCE) == RCC_SYSCLKSource_PLLCLK))
/**
  * @}
  */

/** @defgroup RCC_AHB_Clock_Source
  * @{
  */

#define RCC_SYSCLK_Div1                  RCC_CFGR_HPRE_DIV1
#define RCC_SYSCLK_Div2                  RCC_CFGR_HPRE_DIV2
#define RCC_SYSCLK_Div4                  RCC_CFGR_HPRE_DIV4
#define RCC_SYSCLK_Div8                  RCC_CFGR_HPRE_DIV8
#define RCC_SYSCLK_Div16                 RCC_CFGR_HPRE_DIV16
#define RCC_SYSCLK_Div64                 RCC_CFGR_HPRE_DIV64
#define RCC_SYSCLK_Div128                RCC_CFGR_HPRE_DIV128
#define RCC_SYSCLK_Div256                RCC_CFGR_HPRE_DIV256
#define RCC_SYSCLK_Div512                RCC_CFGR_HPRE_DIV512
#define IS_RCC_HCLK(HCLK) (((HCLK) == RCC_SYSCLK_Div1) || ((HCLK) == RCC_SYSCLK_Div2) || \
                           ((HCLK) == RCC_SYSCLK_Div4) || ((HCLK) == RCC_SYSCLK_Div8) || \
                           ((HCLK) == RCC_SYSCLK_Div16) || ((HCLK) == RCC_SYSCLK_Div64) || \
                           ((HCLK) == RCC_SYSCLK_Div128) || ((HCLK) == RCC_SYSCLK_Div256) || \
                           ((HCLK) == RCC_SYSCLK_Div512))
/**
  * @}
  */ 

/** @defgroup RCC_APB1_APB2_clock_source 
  * @{
  */

#define RCC_HCLK_Div1                    ((uint32_t)0x00000000)
#define RCC_HCLK_Div2                    ((uint32_t)0x00000400)
#define RCC_HCLK_Div4                    ((uint32_t)0x00000500)
#define RCC_HCLK_Div8                    ((uint32_t)0x00000600)
#define RCC_HCLK_Div16                   ((uint32_t)0x00000700)
#define IS_RCC_PCLK(PCLK) (((PCLK) == RCC_HCLK_Div1) || ((PCLK) == RCC_HCLK_Div2) || \
                           ((PCLK) == RCC_HCLK_Div4) || ((PCLK) == RCC_HCLK_Div8) || \
                           ((PCLK) == RCC_HCLK_Div16))
/**
  * @}
  */
  
/** @defgroup RCC_ADC_clock_source 
  * @{
  */
  
/* ADC1 & ADC2 */
#define RCC_ADC12PLLCLK_OFF                    ((uint32_t)0x00000000)
#define RCC_ADC12PLLCLK_Div1                   ((uint32_t)0x00000100)
#define RCC_ADC12PLLCLK_Div2                   ((uint32_t)0x00000110)
#define RCC_ADC12PLLCLK_Div4                   ((uint32_t)0x00000120)
#define RCC_ADC12PLLCLK_Div6                   ((uint32_t)0x00000130)
#define RCC_ADC12PLLCLK_Div8                   ((uint32_t)0x00000140)
#define RCC_ADC12PLLCLK_Div10                  ((uint32_t)0x00000150)
#define RCC_ADC12PLLCLK_Div12                  ((uint32_t)0x00000160)
#define RCC_ADC12PLLCLK_Div16                  ((uint32_t)0x00000170)
#define RCC_ADC12PLLCLK_Div32                  ((uint32_t)0x00000180)
#define RCC_ADC12PLLCLK_Div64                  ((uint32_t)0x00000190)
#define RCC_ADC12PLLCLK_Div128                 ((uint32_t)0x000001A0)
#define RCC_ADC12PLLCLK_Div256                 ((uint32_t)0x000001B0)

/* ADC3 & ADC4 */
#define RCC_ADC34PLLCLK_OFF                    ((uint32_t)0x10000000)
#define RCC_ADC34PLLCLK_Div1                   ((uint32_t)0x10002000)
#define RCC_ADC34PLLCLK_Div2                   ((uint32_t)0x10002200)
#define RCC_ADC34PLLCLK_Div4                   ((uint32_t)0x10002400)
#define RCC_ADC34PLLCLK_Div6                   ((uint32_t)0x10002600)
#define RCC_ADC34PLLCLK_Div8                   ((uint32_t)0x10002800)
#define RCC_ADC34PLLCLK_Div10                  ((uint32_t)0x10002A00)
#define RCC_ADC34PLLCLK_Div12                  ((uint32_t)0x10002C00)
#define RCC_ADC34PLLCLK_Div16                  ((uint32_t)0x10002E00)
#define RCC_ADC34PLLCLK_Div32                  ((uint32_t)0x10003000)
#define RCC_ADC34PLLCLK_Div64                  ((uint32_t)0x10003200)
#define RCC_ADC34PLLCLK_Div128                 ((uint32_t)0x10003400)
#define RCC_ADC34PLLCLK_Div256                 ((uint32_t)0x10003600)

#define IS_RCC_ADCCLK(ADCCLK) (((ADCCLK) == RCC_ADC12PLLCLK_OFF) || ((ADCCLK) == RCC_ADC12PLLCLK_Div1) || \
                               ((ADCCLK) == RCC_ADC12PLLCLK_Div2) || ((ADCCLK) == RCC_ADC12PLLCLK_Div4) || \
                               ((ADCCLK) == RCC_ADC12PLLCLK_Div6) || ((ADCCLK) == RCC_ADC12PLLCLK_Div8) || \
                               ((ADCCLK) == RCC_ADC12PLLCLK_Div10) || ((ADCCLK) == RCC_ADC12PLLCLK_Div12) || \
                               ((ADCCLK) == RCC_ADC12PLLCLK_Div16) || ((ADCCLK) == RCC_ADC12PLLCLK_Div32) || \
                               ((ADCCLK) == RCC_ADC12PLLCLK_Div64) || ((ADCCLK) == RCC_ADC12PLLCLK_Div128) || \
                               ((ADCCLK) == RCC_ADC12PLLCLK_Div256) || ((ADCCLK) == RCC_ADC34PLLCLK_OFF) || \
                               ((ADCCLK) == RCC_ADC34PLLCLK_Div1) || ((ADCCLK) == RCC_ADC34PLLCLK_Div2) || \
                               ((ADCCLK) == RCC_ADC34PLLCLK_Div4) || ((ADCCLK) == RCC_ADC34PLLCLK_Div6) || \
                               ((ADCCLK) == RCC_ADC34PLLCLK_Div8) || ((ADCCLK) == RCC_ADC34PLLCLK_Div10) || \
                               ((ADCCLK) == RCC_ADC34PLLCLK_Div12) || ((ADCCLK) == RCC_ADC34PLLCLK_Div16) || \
                               ((ADCCLK) == RCC_ADC34PLLCLK_Div32) || ((ADCCLK) == RCC_ADC34PLLCLK_Div64) || \
                               ((ADCCLK) == RCC_ADC34PLLCLK_Div128) || ((ADCCLK) == RCC_ADC34PLLCLK_Div256))

/**
  * @}
  */

/** @defgroup RCC_TIM_clock_source 
  * @{
  */

#define RCC_TIM1CLK_HCLK                  ((uint32_t)0x00000000)
#define RCC_TIM1CLK_PLLCLK                RCC_CFGR3_TIM1SW

#define RCC_TIM8CLK_HCLK                  ((uint32_t)0x10000000)
#define RCC_TIM8CLK_PLLCLK                ((uint32_t)0x10000200)

#define RCC_TIM15CLK_HCLK                  ((uint32_t)0x20000000)
#define RCC_TIM15CLK_PLLCLK                ((uint32_t)0x20000400)

#define RCC_TIM16CLK_HCLK                  ((uint32_t)0x30000000)
#define RCC_TIM16CLK_PLLCLK                ((uint32_t)0x30000800)

#define RCC_TIM17CLK_HCLK                  ((uint32_t)0x40000000)
#define RCC_TIM17CLK_PLLCLK                ((uint32_t)0x40002000)

#define IS_RCC_TIMCLK(TIMCLK) (((TIMCLK) == RCC_TIM1CLK_HCLK) || ((TIMCLK) == RCC_TIM1CLK_PLLCLK) || \
                               ((TIMCLK) == RCC_TIM8CLK_HCLK) || ((TIMCLK) == RCC_TIM8CLK_PLLCLK) || \
                               ((TIMCLK) == RCC_TIM15CLK_HCLK) || ((TIMCLK) == RCC_TIM15CLK_PLLCLK) || \
                               ((TIMCLK) == RCC_TIM16CLK_HCLK) || ((TIMCLK) == RCC_TIM16CLK_PLLCLK) || \
                               ((TIMCLK) == RCC_TIM17CLK_HCLK) || ((TIMCLK) == RCC_TIM17CLK_PLLCLK))

/**
  * @}
  */

/** @defgroup RCC_HRTIM_clock_source 
  * @{
  */

#define RCC_HRTIM1CLK_HCLK                  ((uint32_t)0x00000000)
#define RCC_HRTIM1CLK_PLLCLK                RCC_CFGR3_HRTIM1SW

#define IS_RCC_HRTIMCLK(HRTIMCLK) (((HRTIMCLK) == RCC_HRTIM1CLK_HCLK) || ((HRTIMCLK) == RCC_HRTIM1CLK_PLLCLK))

/**
  * @}
  */
  
/** @defgroup RCC_I2C_clock_source 
  * @{
  */

#define RCC_I2C1CLK_HSI                   ((uint32_t)0x00000000)
#define RCC_I2C1CLK_SYSCLK                RCC_CFGR3_I2C1SW

#define RCC_I2C2CLK_HSI                   ((uint32_t)0x10000000)
#define RCC_I2C2CLK_SYSCLK                ((uint32_t)0x10000020)

#define RCC_I2C3CLK_HSI                   ((uint32_t)0x20000000)
#define RCC_I2C3CLK_SYSCLK                ((uint32_t)0x20000040)

#define IS_RCC_I2CCLK(I2CCLK) (((I2CCLK) == RCC_I2C1CLK_HSI) || ((I2CCLK) == RCC_I2C1CLK_SYSCLK) || \
                               ((I2CCLK) == RCC_I2C2CLK_HSI) || ((I2CCLK) == RCC_I2C2CLK_SYSCLK) || \
                               ((I2CCLK) == RCC_I2C3CLK_HSI) || ((I2CCLK) == RCC_I2C3CLK_SYSCLK))

/**
  * @}
  */

/** @defgroup RCC_USART_clock_source 
  * @{
  */

#define RCC_USART1CLK_PCLK                  ((uint32_t)0x10000000)
#define RCC_USART1CLK_SYSCLK                ((uint32_t)0x10000001)
#define RCC_USART1CLK_LSE                   ((uint32_t)0x10000002)
#define RCC_USART1CLK_HSI                   ((uint32_t)0x10000003)

#define RCC_USART2CLK_PCLK                  ((uint32_t)0x20000000)
#define RCC_USART2CLK_SYSCLK                ((uint32_t)0x20010000)
#define RCC_USART2CLK_LSE                   ((uint32_t)0x20020000)
#define RCC_USART2CLK_HSI                   ((uint32_t)0x20030000)

#define RCC_USART3CLK_PCLK                  ((uint32_t)0x30000000)
#define RCC_USART3CLK_SYSCLK                ((uint32_t)0x30040000)
#define RCC_USART3CLK_LSE                   ((uint32_t)0x30080000)
#define RCC_USART3CLK_HSI                   ((uint32_t)0x300C0000)

#define RCC_UART4CLK_PCLK                   ((uint32_t)0x40000000)
#define RCC_UART4CLK_SYSCLK                 ((uint32_t)0x40100000)
#define RCC_UART4CLK_LSE                    ((uint32_t)0x40200000)
#define RCC_UART4CLK_HSI                    ((uint32_t)0x40300000)

#define RCC_UART5CLK_PCLK                   ((uint32_t)0x50000000)
#define RCC_UART5CLK_SYSCLK                 ((uint32_t)0x50400000)
#define RCC_UART5CLK_LSE                    ((uint32_t)0x50800000)
#define RCC_UART5CLK_HSI                    ((uint32_t)0x50C00000)

#define IS_RCC_USARTCLK(USARTCLK) (((USARTCLK) == RCC_USART1CLK_PCLK) || ((USARTCLK) == RCC_USART1CLK_SYSCLK) || \
                                   ((USARTCLK) == RCC_USART1CLK_LSE) || ((USARTCLK) == RCC_USART1CLK_HSI) ||\
                                   ((USARTCLK) == RCC_USART2CLK_PCLK) || ((USARTCLK) == RCC_USART2CLK_SYSCLK) || \
                                   ((USARTCLK) == RCC_USART2CLK_LSE) || ((USARTCLK) == RCC_USART2CLK_HSI) || \
                                   ((USARTCLK) == RCC_USART3CLK_PCLK) || ((USARTCLK) == RCC_USART3CLK_SYSCLK) || \
                                   ((USARTCLK) == RCC_USART3CLK_LSE) || ((USARTCLK) == RCC_USART3CLK_HSI) || \
                                   ((USARTCLK) == RCC_UART4CLK_PCLK) || ((USARTCLK) == RCC_UART4CLK_SYSCLK) || \
                                   ((USARTCLK) == RCC_UART4CLK_LSE) || ((USARTCLK) == RCC_UART4CLK_HSI) || \
                                   ((USARTCLK) == RCC_UART5CLK_PCLK) || ((USARTCLK) == RCC_UART5CLK_SYSCLK) || \
                                   ((USARTCLK) == RCC_UART5CLK_LSE) || ((USARTCLK) == RCC_UART5CLK_HSI))

/**
  * @}
  */
       
/** @defgroup RCC_Interrupt_Source 
  * @{
  */

#define RCC_IT_LSIRDY                    ((uint8_t)0x01)
#define RCC_IT_LSERDY                    ((uint8_t)0x02)
#define RCC_IT_HSIRDY                    ((uint8_t)0x04)
#define RCC_IT_HSERDY                    ((uint8_t)0x08)
#define RCC_IT_PLLRDY                    ((uint8_t)0x10)
#define RCC_IT_CSS                       ((uint8_t)0x80)

#define IS_RCC_IT(IT) ((((IT) & (uint8_t)0xC0) == 0x00) && ((IT) != 0x00))

#define IS_RCC_GET_IT(IT) (((IT) == RCC_IT_LSIRDY) || ((IT) == RCC_IT_LSERDY) || \
                           ((IT) == RCC_IT_HSIRDY) || ((IT) == RCC_IT_HSERDY) || \
                           ((IT) == RCC_IT_PLLRDY) || ((IT) == RCC_IT_CSS))
                           

#define IS_RCC_CLEAR_IT(IT) ((((IT) & (uint8_t)0x40) == 0x00) && ((IT) != 0x00))

/**
  * @}
  */
  
/** @defgroup RCC_LSE_configuration 
  * @{
  */

#define RCC_LSE_OFF                      ((uint32_t)0x00000000)
#define RCC_LSE_ON                       RCC_BDCR_LSEON
#define RCC_LSE_Bypass                   ((uint32_t)(RCC_BDCR_LSEON | RCC_BDCR_LSEBYP))
#define IS_RCC_LSE(LSE) (((LSE) == RCC_LSE_OFF) || ((LSE) == RCC_LSE_ON) || \
                         ((LSE) == RCC_LSE_Bypass))
/**
  * @}
  */

/** @defgroup RCC_RTC_Clock_Source
  * @{
  */

#define RCC_RTCCLKSource_LSE             RCC_BDCR_RTCSEL_LSE
#define RCC_RTCCLKSource_LSI             RCC_BDCR_RTCSEL_LSI
#define RCC_RTCCLKSource_HSE_Div32       RCC_BDCR_RTCSEL_HSE

#define IS_RCC_RTCCLK_SOURCE(SOURCE) (((SOURCE) == RCC_RTCCLKSource_LSE) || \
                                      ((SOURCE) == RCC_RTCCLKSource_LSI) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div32))
/**
  * @}
  */

/** @defgroup RCC_I2S_Clock_Source
  * @{
  */
#define RCC_I2S2CLKSource_SYSCLK             ((uint8_t)0x00)
#define RCC_I2S2CLKSource_Ext                ((uint8_t)0x01)

#define IS_RCC_I2SCLK_SOURCE(SOURCE) (((SOURCE) == RCC_I2S2CLKSource_SYSCLK) || ((SOURCE) == RCC_I2S2CLKSource_Ext)) 

/** @defgroup RCC_LSE_Drive_Configuration 
  * @{
  */

#define RCC_LSEDrive_Low                 ((uint32_t)0x00000000)
#define RCC_LSEDrive_MediumLow           RCC_BDCR_LSEDRV_0
#define RCC_LSEDrive_MediumHigh          RCC_BDCR_LSEDRV_1
#define RCC_LSEDrive_High                RCC_BDCR_LSEDRV
#define IS_RCC_LSE_DRIVE(DRIVE) (((DRIVE) == RCC_LSEDrive_Low) || ((DRIVE) == RCC_LSEDrive_MediumLow) || \
                                 ((DRIVE) == RCC_LSEDrive_MediumHigh) || ((DRIVE) == RCC_LSEDrive_High))
/**
  * @}
  */
  
/** @defgroup RCC_AHB_Peripherals 
  * @{
  */

#define RCC_AHBPeriph_ADC34               RCC_AHBENR_ADC34EN
#define RCC_AHBPeriph_ADC12               RCC_AHBENR_ADC12EN
#define RCC_AHBPeriph_GPIOA               RCC_AHBENR_GPIOAEN
#define RCC_AHBPeriph_GPIOB               RCC_AHBENR_GPIOBEN
#define RCC_AHBPeriph_GPIOC               RCC_AHBENR_GPIOCEN
#define RCC_AHBPeriph_GPIOD               RCC_AHBENR_GPIODEN
#define RCC_AHBPeriph_GPIOE               RCC_AHBENR_GPIOEEN
#define RCC_AHBPeriph_GPIOF               RCC_AHBENR_GPIOFEN
#define RCC_AHBPeriph_TS                  RCC_AHBENR_TSEN
#define RCC_AHBPeriph_CRC                 RCC_AHBENR_CRCEN
#define RCC_AHBPeriph_FLITF               RCC_AHBENR_FLITFEN
#define RCC_AHBPeriph_SRAM                RCC_AHBENR_SRAMEN
#define RCC_AHBPeriph_DMA2                RCC_AHBENR_DMA2EN
#define RCC_AHBPeriph_DMA1                RCC_AHBENR_DMA1EN

#define IS_RCC_AHB_PERIPH(PERIPH) ((((PERIPH) & 0xCE81FFA8) == 0x00) && ((PERIPH) != 0x00))
#define IS_RCC_AHB_RST_PERIPH(PERIPH) ((((PERIPH) & 0xCE81FFFF) == 0x00) && ((PERIPH) != 0x00))

/**
  * @}
  */

/** @defgroup RCC_APB2_Peripherals 
  * @{
  */

#define RCC_APB2Periph_SYSCFG            RCC_APB2ENR_SYSCFGEN
#define RCC_APB2Periph_TIM1              RCC_APB2ENR_TIM1EN
#define RCC_APB2Periph_SPI1              RCC_APB2ENR_SPI1EN
#define RCC_APB2Periph_TIM8              RCC_APB2ENR_TIM8EN
#define RCC_APB2Periph_USART1            RCC_APB2ENR_USART1EN
#define RCC_APB2Periph_TIM15             RCC_APB2ENR_TIM15EN
#define RCC_APB2Periph_TIM16             RCC_APB2ENR_TIM16EN
#define RCC_APB2Periph_TIM17             RCC_APB2ENR_TIM17EN
#define RCC_APB2Periph_HRTIM1            RCC_APB2ENR_HRTIM1

#define IS_RCC_APB2_PERIPH(PERIPH) ((((PERIPH) & 0xDFF887FE) == 0x00) && ((PERIPH) != 0x00))

/**
  * @}
  */ 

/** @defgroup RCC_APB1_Peripherals 
  * @{
  */
#define RCC_APB1Periph_TIM2              RCC_APB1ENR_TIM2EN
#define RCC_APB1Periph_TIM3              RCC_APB1ENR_TIM3EN
#define RCC_APB1Periph_TIM4              RCC_APB1ENR_TIM4EN
#define RCC_APB1Periph_TIM6              RCC_APB1ENR_TIM6EN
#define RCC_APB1Periph_TIM7              RCC_APB1ENR_TIM7EN
#define RCC_APB1Periph_WWDG              RCC_APB1ENR_WWDGEN
#define RCC_APB1Periph_SPI2              RCC_APB1ENR_SPI2EN
#define RCC_APB1Periph_SPI3              RCC_APB1ENR_SPI3EN
#define RCC_APB1Periph_USART2            RCC_APB1ENR_USART2EN
#define RCC_APB1Periph_USART3            RCC_APB1ENR_USART3EN
#define RCC_APB1Periph_UART4             RCC_APB1ENR_UART4EN
#define RCC_APB1Periph_UART5             RCC_APB1ENR_UART5EN
#define RCC_APB1Periph_I2C1              RCC_APB1ENR_I2C1EN
#define RCC_APB1Periph_I2C2              RCC_APB1ENR_I2C2EN
#define RCC_APB1Periph_USB               RCC_APB1ENR_USBEN
#define RCC_APB1Periph_CAN1              RCC_APB1ENR_CAN1EN
#define RCC_APB1Periph_PWR               RCC_APB1ENR_PWREN
#define RCC_APB1Periph_DAC1              RCC_APB1ENR_DAC1EN
#define RCC_APB1Periph_I2C3              RCC_APB1ENR_I2C3EN
#define RCC_APB1Periph_DAC2              RCC_APB1ENR_DAC2EN
#define RCC_APB1Periph_DAC               RCC_APB1Periph_DAC1


#define IS_RCC_APB1_PERIPH(PERIPH) ((((PERIPH) & 0x890137C8) == 0x00) && ((PERIPH) != 0x00))
/**
  * @}
  */

/** @defgroup RCC_MCO_Clock_Source
  * @{
  */

#define RCC_MCOSource_NoClock            ((uint8_t)0x00)
#define RCC_MCOSource_LSI                ((uint8_t)0x02)
#define RCC_MCOSource_LSE                ((uint8_t)0x03)
#define RCC_MCOSource_SYSCLK             ((uint8_t)0x04)
#define RCC_MCOSource_HSI                ((uint8_t)0x05)
#define RCC_MCOSource_HSE                ((uint8_t)0x06)
#define RCC_MCOSource_PLLCLK_Div2        ((uint8_t)0x07)

#define IS_RCC_MCO_SOURCE(SOURCE) (((SOURCE) == RCC_MCOSource_NoClock) ||((SOURCE) == RCC_MCOSource_SYSCLK) ||\
                                    ((SOURCE) == RCC_MCOSource_HSI)  || ((SOURCE) == RCC_MCOSource_HSE) || \
                                    ((SOURCE) == RCC_MCOSource_LSI)  || ((SOURCE) == RCC_MCOSource_LSE) || \
                                    ((SOURCE) == RCC_MCOSource_PLLCLK_Div2))
/**
  * @}
  */ 

/** @defgroup RCC_MCOPrescaler
  * @{
  */

#define RCC_MCOPrescaler_1            RCC_CFGR_MCO_PRE_1
#define RCC_MCOPrescaler_2            RCC_CFGR_MCO_PRE_2
#define RCC_MCOPrescaler_4            RCC_CFGR_MCO_PRE_4
#define RCC_MCOPrescaler_8            RCC_CFGR_MCO_PRE_8
#define RCC_MCOPrescaler_16           RCC_CFGR_MCO_PRE_16
#define RCC_MCOPrescaler_32           RCC_CFGR_MCO_PRE_32
#define RCC_MCOPrescaler_64           RCC_CFGR_MCO_PRE_64
#define RCC_MCOPrescaler_128          RCC_CFGR_MCO_PRE_128

#define IS_RCC_MCO_PRESCALER(PRESCALER) (((PRESCALER) == RCC_MCOPrescaler_1)  || \
                                         ((PRESCALER) == RCC_MCOPrescaler_2)  || \
                                         ((PRESCALER) == RCC_MCOPrescaler_4)  || \
                                         ((PRESCALER) == RCC_MCOPrescaler_8)  || \
                                         ((PRESCALER) == RCC_MCOPrescaler_16) || \
                                         ((PRESCALER) == RCC_MCOPrescaler_32) || \
                                         ((PRESCALER) == RCC_MCOPrescaler_64) || \
                                         ((PRESCALER) == RCC_MCOPrescaler_128))
/**
  * @}
  */ 

/** @defgroup RCC_USB_Device_clock_source 
  * @{
  */

#define RCC_USBCLKSource_PLLCLK_1Div5   ((uint8_t)0x00)
#define RCC_USBCLKSource_PLLCLK_Div1    ((uint8_t)0x01)

#define IS_RCC_USBCLK_SOURCE(SOURCE) (((SOURCE) == RCC_USBCLKSource_PLLCLK_1Div5) || \
                                      ((SOURCE) == RCC_USBCLKSource_PLLCLK_Div1))
/**
  * @}
  */

/** @defgroup RCC_Flag 
  * @{
  */
#define RCC_FLAG_HSIRDY                  ((uint8_t)0x01)
#define RCC_FLAG_HSERDY                  ((uint8_t)0x11)
#define RCC_FLAG_PLLRDY                  ((uint8_t)0x19)
#define RCC_FLAG_MCOF                    ((uint8_t)0x9C)
#define RCC_FLAG_LSERDY                  ((uint8_t)0x21)
#define RCC_FLAG_LSIRDY                  ((uint8_t)0x41)
#define RCC_FLAG_OBLRST                  ((uint8_t)0x59)
#define RCC_FLAG_PINRST                  ((uint8_t)0x5A)
#define RCC_FLAG_PORRST                  ((uint8_t)0x5B)
#define RCC_FLAG_SFTRST                  ((uint8_t)0x5C)
#define RCC_FLAG_IWDGRST                 ((uint8_t)0x5D)
#define RCC_FLAG_WWDGRST                 ((uint8_t)0x5E)
#define RCC_FLAG_LPWRRST                 ((uint8_t)0x5F)

#define IS_RCC_FLAG(FLAG) (((FLAG) == RCC_FLAG_HSIRDY) || ((FLAG) == RCC_FLAG_HSERDY) || \
                           ((FLAG) == RCC_FLAG_PLLRDY) || ((FLAG) == RCC_FLAG_LSERDY) || \
                           ((FLAG) == RCC_FLAG_LSIRDY) || ((FLAG) == RCC_FLAG_OBLRST) || \
                           ((FLAG) == RCC_FLAG_PINRST) || ((FLAG) == RCC_FLAG_PORRST) || \
                           ((FLAG) == RCC_FLAG_SFTRST) || ((FLAG) == RCC_FLAG_IWDGRST)|| \
                           ((FLAG) == RCC_FLAG_WWDGRST)|| ((FLAG) == RCC_FLAG_LPWRRST)|| \
                           ((FLAG) == RCC_FLAG_MCOF))

#define IS_RCC_HSI_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x1F)

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Function used to set the RCC clock configuration to the default reset state */
void RCC_DeInit(void);

/* Internal/external clocks, PLL, CSS and MCO configuration functions *********/
void RCC_HSEConfig(uint8_t RCC_HSE);
ErrorStatus RCC_WaitForHSEStartUp(void);
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue);
void RCC_HSICmd(FunctionalState NewState);
void RCC_LSEConfig(uint32_t RCC_LSE);
void RCC_LSEDriveConfig(uint32_t RCC_LSEDrive);
void RCC_LSICmd(FunctionalState NewState);
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul);
void RCC_PLLCmd(FunctionalState NewState);
void RCC_PREDIV1Config(uint32_t RCC_PREDIV1_Div);
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);
#ifdef STM32F303xC
 void RCC_MCOConfig(uint8_t RCC_MCOSource);
#else
 void RCC_MCOConfig(uint8_t RCC_MCOSource,uint32_t RCC_MCOPrescaler);
#endif /* STM32F303xC */

/* System, AHB and APB busses clocks configuration functions ******************/
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource);
uint8_t RCC_GetSYSCLKSource(void);
void RCC_HCLKConfig(uint32_t RCC_SYSCLK);
void RCC_PCLK1Config(uint32_t RCC_HCLK);
void RCC_PCLK2Config(uint32_t RCC_HCLK);
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);

/* Peripheral clocks configuration functions **********************************/
void RCC_ADCCLKConfig(uint32_t RCC_PLLCLK);
void RCC_I2CCLKConfig(uint32_t RCC_I2CCLK);
void RCC_TIMCLKConfig(uint32_t RCC_TIMCLK);
void RCC_HRTIM1CLKConfig(uint32_t RCC_HRTIMCLK);
void RCC_I2SCLKConfig(uint32_t RCC_I2SCLKSource); 
void RCC_USARTCLKConfig(uint32_t RCC_USARTCLK);
void RCC_USBCLKConfig(uint32_t RCC_USBCLKSource);

void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource);
void RCC_RTCCLKCmd(FunctionalState NewState);
void RCC_BackupResetCmd(FunctionalState NewState);

void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);

void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);

/* Interrupts and flags management functions **********************************/
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState);
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG);
void RCC_ClearFlag(void);
ITStatus RCC_GetITStatus(uint8_t RCC_IT);
void RCC_ClearITPendingBit(uint8_t RCC_IT);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F30x_RCC_H */

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
