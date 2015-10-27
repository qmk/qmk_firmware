/**
  ******************************************************************************
  * @file    stm32f3xx_hal_rcc_ex.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   Header file of RCC HAL Extended module.
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
#ifndef __STM32F3xx_HAL_RCC_EX_H
#define __STM32F3xx_HAL_RCC_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal_def.h"

/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

/** @addtogroup RCCEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup RCCEx_Exported_Types RCC Extended Exported Types
  * @{
  */
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx)
/**
  * @brief  RCC PLL configuration structure definition
  */
typedef struct
{
  uint32_t PLLState;   /*!< PLLState: The new state of the PLL.
                            This parameter can be a value of @ref RCC_PLL_Config */

  uint32_t PLLSource;  /*!< PLLSource: PLL entry clock source.
                            This parameter must be a value of @ref RCCEx_PLL_Clock_Source */

  uint32_t PLLMUL;     /*!< PLLMUL: Multiplication factor for PLL VCO input clock
                            This parameter must be a value of @ref RCC_PLL_Multiplication_Factor*/

  uint32_t PREDIV;     /*!< PREDIV: Predivision factor for PLL VCO input clock
                            This parameter must be a value of @ref RCCEx_PLL_Prediv_Factor */

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

  uint32_t LSEState;             /*!<  The new state of the LSE.
                                       This parameter can be a value of @ref RCC_LSE_Config */

  uint32_t HSIState;             /*!< The new state of the HSI.
                                      This parameter can be a value of @ref RCC_HSI_Config */

  uint32_t HSICalibrationValue;  /*!< The calibration trimming value.
                                      This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x1F */

  uint32_t LSIState;             /*!<  The new state of the LSI.
                                       This parameter can be a value of @ref RCC_LSI_Config */

  RCC_PLLInitTypeDef PLL;        /*!< PLL structure parameters */

}RCC_OscInitTypeDef;

#endif /* STM32F302xE || STM32F303xE || STM32F398xx */
   
#if defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  RCC PLL configuration structure definition
  */
typedef struct
{
  uint32_t PLLState;   /*!< PLLState: The new state of the PLL.
                            This parameter can be a value of @ref RCC_PLL_Config */

  uint32_t PLLSource;  /*!< PLLSource: PLL entry clock source.
                            This parameter must be a value of @ref RCCEx_PLL_Clock_Source */

  uint32_t PLLMUL;     /*!< PLLMUL: Multiplication factor for PLL VCO input clock
                            This parameter must be a value of @ref RCC_PLL_Multiplication_Factor*/

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

  uint32_t HSEPredivValue;       /*!<  The HSE predivision factor value.
                                       This parameter can be a value of @ref RCCEx_HSE_Predivision_Factor */

  uint32_t LSEState;             /*!<  The new state of the LSE.
                                       This parameter can be a value of @ref RCC_LSE_Config */

  uint32_t HSIState;             /*!< The new state of the HSI.
                                      This parameter can be a value of @ref RCC_HSI_Config */

  uint32_t HSICalibrationValue;  /*!< The calibration trimming value.
                                      This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x1F */

  uint32_t LSIState;             /*!<  The new state of the LSI.
                                       This parameter can be a value of @ref RCC_LSI_Config */

  RCC_PLLInitTypeDef PLL;        /*!< PLL structure parameters */

}RCC_OscInitTypeDef;
#endif /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */
       /* STM32F373xC || STM32F378xx                   */

/** 
  * @brief  RCC extended clocks structure definition  
  */
#if defined(STM32F301x8) || defined(STM32F318xx)
typedef struct
{
  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;    /*!< Specifies RTC Clock Prescalers Selection 
                                      This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t Usart1ClockSelection; /*!< USART1 clock source      
                                      This parameter can be a value of @ref RCCEx_USART1_Clock_Source */

  uint32_t Usart2ClockSelection; /*!< USART2 clock source      
                                      This parameter can be a value of @ref RCC_USART2_Clock_Source */

  uint32_t Usart3ClockSelection; /*!< USART3 clock source      
                                      This parameter can be a value of @ref RCC_USART3_Clock_Source */

  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source      
                                      This parameter can be a value of @ref RCC_I2C1_Clock_Source */

  uint32_t I2c2ClockSelection;   /*!< I2C2 clock source      
                                      This parameter can be a value of @ref RCCEx_I2C2_Clock_Source */

  uint32_t I2c3ClockSelection;   /*!< I2C3 clock source      
                                      This parameter can be a value of @ref RCCEx_I2C3_Clock_Source */

  uint32_t Adc1ClockSelection;   /*!< ADC1 clock source      
                                      This parameter can be a value of @ref RCCEx_ADC1_Clock_Source */

  uint32_t I2sClockSelection;    /*!< I2S clock source      
                                      This parameter can be a value of @ref RCCEx_I2S_Clock_Source */

  uint32_t Tim1ClockSelection;   /*!< TIM1 clock source      
                                      This parameter can be a value of @ref RCCEx_TIM1_Clock_Source */

  uint32_t Tim15ClockSelection;  /*!< TIM15 clock source      
                                      This parameter can be a value of @ref RCCEx_TIM15_Clock_Source */

  uint32_t Tim16ClockSelection;  /*!< TIM16 clock source      
                                      This parameter can be a value of @ref RCCEx_TIM16_Clock_Source */

  uint32_t Tim17ClockSelection;  /*!< TIM17 clock source      
                                      This parameter can be a value of @ref RCCEx_TIM17_Clock_Source */
}RCC_PeriphCLKInitTypeDef;
#endif /* STM32F301x8 || STM32F318xx */

#if defined(STM32F302x8)
typedef struct
{
  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;    /*!< Specifies RTC Clock Prescalers Selection 
                                      This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t Usart1ClockSelection; /*!< USART1 clock source      
                                      This parameter can be a value of @ref RCCEx_USART1_Clock_Source */

  uint32_t Usart2ClockSelection; /*!< USART2 clock source      
                                      This parameter can be a value of @ref RCC_USART2_Clock_Source */

  uint32_t Usart3ClockSelection; /*!< USART3 clock source      
                                      This parameter can be a value of @ref RCC_USART3_Clock_Source */

  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source      
                                      This parameter can be a value of @ref RCC_I2C1_Clock_Source */

  uint32_t I2c2ClockSelection;   /*!< I2C2 clock source      
                                      This parameter can be a value of @ref RCCEx_I2C2_Clock_Source */

  uint32_t I2c3ClockSelection;   /*!< I2C3 clock source      
                                      This parameter can be a value of @ref RCCEx_I2C3_Clock_Source */

  uint32_t Adc1ClockSelection;   /*!< ADC1 clock source      
                                      This parameter can be a value of @ref RCCEx_ADC1_Clock_Source */

  uint32_t I2sClockSelection;    /*!< I2S clock source      
                                      This parameter can be a value of @ref RCCEx_I2S_Clock_Source */

  uint32_t Tim1ClockSelection;   /*!< TIM1 clock source      
                                      This parameter can be a value of @ref RCCEx_TIM1_Clock_Source */

  uint32_t Tim15ClockSelection;  /*!< TIM15 clock source      
                                      This parameter can be a value of @ref RCCEx_TIM15_Clock_Source */

  uint32_t Tim16ClockSelection;  /*!< TIM16 clock source      
                                      This parameter can be a value of @ref RCCEx_TIM16_Clock_Source */

  uint32_t Tim17ClockSelection;  /*!< TIM17 clock source      
                                      This parameter can be a value of @ref RCCEx_TIM17_Clock_Source */

  uint32_t USBClockSelection;    /*!< USB clock source      
                                      This parameter can be a value of @ref RCCEx_USB_Clock_Source */

}RCC_PeriphCLKInitTypeDef;
#endif /* STM32F302x8 */

#if defined(STM32F302xC)
typedef struct
{
  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;      /*!< Specifies RTC Clock Prescalers Selection 
                                      This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t Usart1ClockSelection; /*!< USART1 clock source
                                      This parameter can be a value of @ref RCCEx_USART1_Clock_Source */

  uint32_t Usart2ClockSelection; /*!< USART2 clock source
                                      This parameter can be a value of @ref RCC_USART2_Clock_Source */

  uint32_t Usart3ClockSelection; /*!< USART3 clock source
                                      This parameter can be a value of @ref RCC_USART3_Clock_Source */

  uint32_t Uart4ClockSelection;  /*!< UART4 clock source
                                      This parameter can be a value of @ref RCCEx_UART4_Clock_Source */

  uint32_t Uart5ClockSelection;  /*!< UART5 clock source
                                      This parameter can be a value of @ref RCCEx_UART5_Clock_Source */

  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source
                                      This parameter can be a value of @ref RCC_I2C1_Clock_Source */

  uint32_t I2c2ClockSelection;   /*!< I2C2 clock source
                                      This parameter can be a value of @ref RCCEx_I2C2_Clock_Source */

  uint32_t Adc12ClockSelection;  /*!< ADC1 & ADC2 clock source
                                      This parameter can be a value of @ref RCCEx_ADC12_Clock_Source */

  uint32_t I2sClockSelection;    /*!< I2S clock source
                                      This parameter can be a value of @ref RCCEx_I2S_Clock_Source */

  uint32_t Tim1ClockSelection;   /*!< TIM1 clock source
                                      This parameter can be a value of @ref RCCEx_TIM1_Clock_Source */

  uint32_t USBClockSelection;    /*!< USB clock source      
                                      This parameter can be a value of @ref RCCEx_USB_Clock_Source */

}RCC_PeriphCLKInitTypeDef;
#endif /* STM32F302xC */

#if defined(STM32F303xC)
typedef struct
{
  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;      /*!< Specifies RTC Clock Prescalers Selection 
                                      This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t Usart1ClockSelection; /*!< USART1 clock source
                                      This parameter can be a value of @ref RCCEx_USART1_Clock_Source */

  uint32_t Usart2ClockSelection; /*!< USART2 clock source
                                      This parameter can be a value of @ref RCC_USART2_Clock_Source */

  uint32_t Usart3ClockSelection; /*!< USART3 clock source
                                      This parameter can be a value of @ref RCC_USART3_Clock_Source */

  uint32_t Uart4ClockSelection;  /*!< UART4 clock source
                                      This parameter can be a value of @ref RCCEx_UART4_Clock_Source */

  uint32_t Uart5ClockSelection;  /*!< UART5 clock source
                                      This parameter can be a value of @ref RCCEx_UART5_Clock_Source */

  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source
                                      This parameter can be a value of @ref RCC_I2C1_Clock_Source */

  uint32_t I2c2ClockSelection;   /*!< I2C2 clock source
                                      This parameter can be a value of @ref RCCEx_I2C2_Clock_Source */

  uint32_t Adc12ClockSelection;  /*!< ADC1 & ADC2 clock source
                                      This parameter can be a value of @ref RCCEx_ADC12_Clock_Source */

  uint32_t Adc34ClockSelection;  /*!< ADC3 & ADC4 clock source
                                      This parameter can be a value of @ref RCCEx_ADC34_Clock_Source */

  uint32_t I2sClockSelection;    /*!< I2S clock source
                                      This parameter can be a value of @ref RCCEx_I2S_Clock_Source */

  uint32_t Tim1ClockSelection;   /*!< TIM1 clock source
                                      This parameter can be a value of @ref RCCEx_TIM1_Clock_Source */

  uint32_t Tim8ClockSelection;   /*!< TIM8 clock source
                                      This parameter can be a value of @ref RCCEx_TIM8_Clock_Source */

  uint32_t USBClockSelection;    /*!< USB clock source      
                                      This parameter can be a value of @ref RCCEx_USB_Clock_Source */

}RCC_PeriphCLKInitTypeDef;
#endif /* STM32F303xC */

#if defined(STM32F302xE)
typedef struct
{
  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;      /*!< Specifies RTC Clock Prescalers Selection 
                                      This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t Usart1ClockSelection; /*!< USART1 clock source
                                      This parameter can be a value of @ref RCCEx_USART1_Clock_Source */

  uint32_t Usart2ClockSelection; /*!< USART2 clock source
                                      This parameter can be a value of @ref RCC_USART2_Clock_Source */

  uint32_t Usart3ClockSelection; /*!< USART3 clock source
                                      This parameter can be a value of @ref RCC_USART3_Clock_Source */

  uint32_t Uart4ClockSelection;  /*!< UART4 clock source
                                      This parameter can be a value of @ref RCCEx_UART4_Clock_Source */

  uint32_t Uart5ClockSelection;  /*!< UART5 clock source
                                      This parameter can be a value of @ref RCCEx_UART5_Clock_Source */

  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source
                                      This parameter can be a value of @ref RCC_I2C1_Clock_Source */

  uint32_t I2c2ClockSelection;   /*!< I2C2 clock source
                                      This parameter can be a value of @ref RCCEx_I2C2_Clock_Source */

  uint32_t I2c3ClockSelection;   /*!< I2C3 clock source      
                                      This parameter can be a value of @ref RCCEx_I2C3_Clock_Source */

  uint32_t Adc12ClockSelection;  /*!< ADC1 & ADC2 clock source
                                      This parameter can be a value of @ref RCCEx_ADC12_Clock_Source */

  uint32_t I2sClockSelection;    /*!< I2S clock source
                                      This parameter can be a value of @ref RCCEx_I2S_Clock_Source */

  uint32_t Tim1ClockSelection;   /*!< TIM1 clock source
                                      This parameter can be a value of @ref RCCEx_TIM1_Clock_Source */

  uint32_t Tim2ClockSelection;   /*!< TIM2 clock source
                                      This parameter can be a value of @ref RCCEx_TIM2_Clock_Source */

  uint32_t Tim34ClockSelection;   /*!< TIM3 & TIM4 clock source
                                       This parameter can be a value of @ref RCCEx_TIM34_Clock_Source */
				       
  uint32_t Tim15ClockSelection;  /*!< TIM15 clock source
                                      This parameter can be a value of @ref RCCEx_TIM15_Clock_Source */

  uint32_t Tim16ClockSelection;  /*!< TIM16 clock source
                                      This parameter can be a value of @ref RCCEx_TIM16_Clock_Source */

  uint32_t Tim17ClockSelection;  /*!< TIM17 clock source
                                      This parameter can be a value of @ref RCCEx_TIM17_Clock_Source */

  uint32_t USBClockSelection;    /*!< USB clock source      
                                      This parameter can be a value of @ref RCCEx_USB_Clock_Source */

}RCC_PeriphCLKInitTypeDef;
#endif /* STM32F302xE */

#if defined(STM32F303xE)
typedef struct
{
  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;      /*!< Specifies RTC Clock Prescalers Selection 
                                      This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t Usart1ClockSelection; /*!< USART1 clock source
                                      This parameter can be a value of @ref RCCEx_USART1_Clock_Source */

  uint32_t Usart2ClockSelection; /*!< USART2 clock source
                                      This parameter can be a value of @ref RCC_USART2_Clock_Source */

  uint32_t Usart3ClockSelection; /*!< USART3 clock source
                                      This parameter can be a value of @ref RCC_USART3_Clock_Source */

  uint32_t Uart4ClockSelection;  /*!< UART4 clock source
                                      This parameter can be a value of @ref RCCEx_UART4_Clock_Source */

  uint32_t Uart5ClockSelection;  /*!< UART5 clock source
                                      This parameter can be a value of @ref RCCEx_UART5_Clock_Source */

  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source
                                      This parameter can be a value of @ref RCC_I2C1_Clock_Source */

  uint32_t I2c2ClockSelection;   /*!< I2C2 clock source
                                      This parameter can be a value of @ref RCCEx_I2C2_Clock_Source */

  uint32_t I2c3ClockSelection;   /*!< I2C3 clock source      
                                      This parameter can be a value of @ref RCCEx_I2C3_Clock_Source */

  uint32_t Adc12ClockSelection;  /*!< ADC1 & ADC2 clock source
                                      This parameter can be a value of @ref RCCEx_ADC12_Clock_Source */

  uint32_t Adc34ClockSelection;  /*!< ADC3 & ADC4 clock source
                                      This parameter can be a value of @ref RCCEx_ADC34_Clock_Source */

  uint32_t I2sClockSelection;    /*!< I2S clock source
                                      This parameter can be a value of @ref RCCEx_I2S_Clock_Source */

  uint32_t Tim1ClockSelection;   /*!< TIM1 clock source
                                      This parameter can be a value of @ref RCCEx_TIM1_Clock_Source */

  uint32_t Tim2ClockSelection;   /*!< TIM2 clock source
                                      This parameter can be a value of @ref RCCEx_TIM2_Clock_Source */

  uint32_t Tim34ClockSelection;   /*!< TIM3 & TIM4 clock source
                                       This parameter can be a value of @ref RCCEx_TIM34_Clock_Source */

  uint32_t Tim8ClockSelection;   /*!< TIM8 clock source
                                      This parameter can be a value of @ref RCCEx_TIM8_Clock_Source */

  uint32_t Tim15ClockSelection;  /*!< TIM15 clock source
                                      This parameter can be a value of @ref RCCEx_TIM15_Clock_Source */

  uint32_t Tim16ClockSelection;  /*!< TIM16 clock source
                                      This parameter can be a value of @ref RCCEx_TIM16_Clock_Source */

  uint32_t Tim17ClockSelection;  /*!< TIM17 clock source
                                      This parameter can be a value of @ref RCCEx_TIM17_Clock_Source */

  uint32_t Tim20ClockSelection;  /*!< TIM20 clock source
                                      This parameter can be a value of @ref RCCEx_TIM20_Clock_Source */

  uint32_t USBClockSelection;    /*!< USB clock source      
                                      This parameter can be a value of @ref RCCEx_USB_Clock_Source */

}RCC_PeriphCLKInitTypeDef;
#endif /* STM32F303xE */

#if defined(STM32F398xx)
typedef struct
{
  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;      /*!< Specifies RTC Clock Prescalers Selection 
                                      This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t Usart1ClockSelection; /*!< USART1 clock source
                                      This parameter can be a value of @ref RCCEx_USART1_Clock_Source */

  uint32_t Usart2ClockSelection; /*!< USART2 clock source
                                      This parameter can be a value of @ref RCC_USART2_Clock_Source */

  uint32_t Usart3ClockSelection; /*!< USART3 clock source
                                      This parameter can be a value of @ref RCC_USART3_Clock_Source */

  uint32_t Uart4ClockSelection;  /*!< UART4 clock source
                                      This parameter can be a value of @ref RCCEx_UART4_Clock_Source */

  uint32_t Uart5ClockSelection;  /*!< UART5 clock source
                                      This parameter can be a value of @ref RCCEx_UART5_Clock_Source */

  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source
                                      This parameter can be a value of @ref RCC_I2C1_Clock_Source */

  uint32_t I2c2ClockSelection;   /*!< I2C2 clock source
                                      This parameter can be a value of @ref RCCEx_I2C2_Clock_Source */

  uint32_t I2c3ClockSelection;   /*!< I2C3 clock source      
                                      This parameter can be a value of @ref RCCEx_I2C3_Clock_Source */

  uint32_t Adc12ClockSelection;  /*!< ADC1 & ADC2 clock source
                                      This parameter can be a value of @ref RCCEx_ADC12_Clock_Source */

  uint32_t Adc34ClockSelection;  /*!< ADC3 & ADC4 clock source
                                      This parameter can be a value of @ref RCCEx_ADC34_Clock_Source */

  uint32_t I2sClockSelection;    /*!< I2S clock source
                                      This parameter can be a value of @ref RCCEx_I2S_Clock_Source */

  uint32_t Tim1ClockSelection;   /*!< TIM1 clock source
                                      This parameter can be a value of @ref RCCEx_TIM1_Clock_Source */

  uint32_t Tim2ClockSelection;   /*!< TIM2 clock source
                                      This parameter can be a value of @ref RCCEx_TIM2_Clock_Source */

  uint32_t Tim34ClockSelection;   /*!< TIM3 & TIM4 clock source
                                       This parameter can be a value of @ref RCCEx_TIM34_Clock_Source */

  uint32_t Tim8ClockSelection;   /*!< TIM8 clock source
                                      This parameter can be a value of @ref RCCEx_TIM8_Clock_Source */

  uint32_t Tim15ClockSelection;  /*!< TIM15 clock source
                                      This parameter can be a value of @ref RCCEx_TIM15_Clock_Source */

  uint32_t Tim16ClockSelection;  /*!< TIM16 clock source
                                      This parameter can be a value of @ref RCCEx_TIM16_Clock_Source */

  uint32_t Tim17ClockSelection;  /*!< TIM17 clock source
                                      This parameter can be a value of @ref RCCEx_TIM17_Clock_Source */

  uint32_t Tim20ClockSelection;  /*!< TIM20 clock source
                                      This parameter can be a value of @ref RCCEx_TIM20_Clock_Source */

}RCC_PeriphCLKInitTypeDef;
#endif /* STM32F398xx */

#if defined(STM32F358xx)
typedef struct
{
  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;      /*!< Specifies RTC Clock Prescalers Selection 
                                      This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t Usart1ClockSelection; /*!< USART1 clock source
                                      This parameter can be a value of @ref RCCEx_USART1_Clock_Source */

  uint32_t Usart2ClockSelection; /*!< USART2 clock source
                                      This parameter can be a value of @ref RCC_USART2_Clock_Source */

  uint32_t Usart3ClockSelection; /*!< USART3 clock source
                                      This parameter can be a value of @ref RCC_USART3_Clock_Source */

  uint32_t Uart4ClockSelection;  /*!< UART4 clock source
                                      This parameter can be a value of @ref RCCEx_UART4_Clock_Source */

  uint32_t Uart5ClockSelection;  /*!< UART5 clock source
                                      This parameter can be a value of @ref RCCEx_UART5_Clock_Source */

  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source
                                      This parameter can be a value of @ref RCC_I2C1_Clock_Source */

  uint32_t I2c2ClockSelection;   /*!< I2C2 clock source
                                      This parameter can be a value of @ref RCCEx_I2C2_Clock_Source */

  uint32_t Adc12ClockSelection;  /*!< ADC1 & ADC2 clock source
                                      This parameter can be a value of @ref RCCEx_ADC12_Clock_Source */

  uint32_t Adc34ClockSelection;  /*!< ADC3 & ADC4 clock source
                                      This parameter can be a value of @ref RCCEx_ADC34_Clock_Source */

  uint32_t I2sClockSelection;    /*!< I2S clock source
                                      This parameter can be a value of @ref RCCEx_I2S_Clock_Source */

  uint32_t Tim1ClockSelection;   /*!< TIM1 clock source
                                      This parameter can be a value of @ref RCCEx_TIM1_Clock_Source */

  uint32_t Tim8ClockSelection;   /*!< TIM8 clock source
                                      This parameter can be a value of @ref RCCEx_TIM8_Clock_Source */

}RCC_PeriphCLKInitTypeDef;
#endif /* STM32F358xx */

#if defined(STM32F303x8)
typedef struct
{
  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;      /*!< Specifies RTC Clock Prescalers Selection 
                                      This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t Usart1ClockSelection; /*!< USART1 clock source      
                                      This parameter can be a value of @ref RCCEx_USART1_Clock_Source */

  uint32_t Usart2ClockSelection; /*!< USART2 clock source      
                                      This parameter can be a value of @ref RCC_USART2_Clock_Source */

  uint32_t Usart3ClockSelection; /*!< USART3 clock source      
                                      This parameter can be a value of @ref RCC_USART3_Clock_Source */

  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source      
                                      This parameter can be a value of @ref RCC_I2C1_Clock_Source */

  uint32_t Adc12ClockSelection;  /*!< ADC1 & ADC2 clock source      
                                      This parameter can be a value of @ref RCCEx_ADC12_Clock_Source */

  uint32_t Tim1ClockSelection;   /*!< TIM1 clock source      
                                      This parameter can be a value of @ref RCCEx_TIM1_Clock_Source */

}RCC_PeriphCLKInitTypeDef;
#endif /* STM32F303x8 */

#if defined(STM32F334x8)
typedef struct
{
  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;      /*!< Specifies RTC Clock Prescalers Selection 
                                      This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t Usart1ClockSelection; /*!< USART1 clock source
                                      This parameter can be a value of @ref RCCEx_USART1_Clock_Source */

  uint32_t Usart2ClockSelection; /*!< USART2 clock source
                                      This parameter can be a value of @ref RCC_USART2_Clock_Source */

  uint32_t Usart3ClockSelection; /*!< USART3 clock source
                                      This parameter can be a value of @ref RCC_USART3_Clock_Source */

  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source
                                      This parameter can be a value of @ref RCC_I2C1_Clock_Source */

  uint32_t Adc12ClockSelection;  /*!< ADC1 & ADC2 clock source
                                      This parameter can be a value of @ref RCCEx_ADC12_Clock_Source */

  uint32_t Tim1ClockSelection;   /*!< TIM1 clock source
                                      This parameter can be a value of @ref RCCEx_TIM1_Clock_Source */

  uint32_t Hrtim1ClockSelection; /*!< HRTIM1 clock source
                                      This parameter can be a value of @ref RCCEx_HRTIM1_Clock_Source */

}RCC_PeriphCLKInitTypeDef;
#endif /* STM32F334x8 */

#if defined(STM32F328xx)
typedef struct
{
  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;      /*!< Specifies RTC Clock Prescalers Selection 
                                      This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t Usart1ClockSelection; /*!< USART1 clock source
                                      This parameter can be a value of @ref RCC_USART1_Clock_Source */

  uint32_t Usart2ClockSelection; /*!< USART2 clock source
                                      This parameter can be a value of @ref RCC_USART2_Clock_Source */

  uint32_t Usart3ClockSelection; /*!< USART3 clock source
                                      This parameter can be a value of @ref RCC_USART3_Clock_Source */

  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source
                                      This parameter can be a value of @ref RCC_I2C1_Clock_Source */

  uint32_t Adc12ClockSelection;  /*!< ADC1 & ADC2 clock source
                                      This parameter can be a value of @ref RCCEx_ADC12_Clock_Source */

  uint32_t Tim1ClockSelection;   /*!< TIM1 clock source
                                      This parameter can be a value of @ref RCCEx_TIM1_Clock_Source */

}RCC_PeriphCLKInitTypeDef;
#endif /* STM32F328xx */

#if defined(STM32F373xC) 
typedef struct
{
  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;      /*!< Specifies RTC Clock Prescalers Selection 
                                      This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t Usart1ClockSelection; /*!< USART1 clock source      
                                      This parameter can be a value of @ref RCCEx_USART1_Clock_Source */

  uint32_t Usart2ClockSelection; /*!< USART2 clock source      
                                      This parameter can be a value of @ref RCC_USART2_Clock_Source */

  uint32_t Usart3ClockSelection; /*!< USART3 clock source      
                                      This parameter can be a value of @ref RCC_USART3_Clock_Source */

  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source      
                                      This parameter can be a value of @ref RCC_I2C1_Clock_Source */

  uint32_t I2c2ClockSelection;   /*!< I2C2 clock source      
                                      This parameter can be a value of @ref RCCEx_I2C2_Clock_Source */

  uint32_t Adc1ClockSelection;   /*!< ADC1 clock source      
                                      This parameter can be a value of @ref RCCEx_ADC1_Clock_Source */

  uint32_t SdadcClockSelection;   /*!< SDADC clock prescaler      
                                      This parameter can be a value of @ref RCCEx_SDADC_Clock_Prescaler */

  uint32_t CecClockSelection;    /*!< HDMI CEC clock source      
                                       This parameter can be a value of @ref RCCEx_CEC_Clock_Source */

  uint32_t USBClockSelection;    /*!< USB clock source      
                                      This parameter can be a value of @ref RCCEx_USB_Clock_Source */

}RCC_PeriphCLKInitTypeDef;
#endif /* STM32F373xC */

#if defined(STM32F378xx)
typedef struct
{
  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;      /*!< Specifies RTC Clock Prescalers Selection 
                                      This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t Usart1ClockSelection; /*!< USART1 clock source      
                                      This parameter can be a value of @ref RCCEx_USART1_Clock_Source */

  uint32_t Usart2ClockSelection; /*!< USART2 clock source      
                                      This parameter can be a value of @ref RCC_USART2_Clock_Source */

  uint32_t Usart3ClockSelection; /*!< USART3 clock source      
                                      This parameter can be a value of @ref RCC_USART3_Clock_Source */

  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source      
                                      This parameter can be a value of @ref RCC_I2C1_Clock_Source */

  uint32_t I2c2ClockSelection;   /*!< I2C2 clock source      
                                      This parameter can be a value of @ref RCCEx_I2C2_Clock_Source */

  uint32_t Adc1ClockSelection;   /*!< ADC1 clock source      
                                      This parameter can be a value of @ref RCCEx_ADC1_Clock_Source */

  uint32_t SdadcClockSelection;   /*!< SDADC clock prescaler      
                                      This parameter can be a value of @ref RCCEx_SDADC_Clock_Prescaler */

  uint32_t CecClockSelection;    /*!< HDMI CEC clock source      
                                       This parameter can be a value of @ref RCCEx_CEC_Clock_Source */

}RCC_PeriphCLKInitTypeDef;
#endif /* STM32F378xx */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Constants RCC Extended Exported Constants
  * @{
  */
#if defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F334x8)                                                 || \
    defined(STM32F373xC) || defined(STM32F378xx)
/** @defgroup RCCEx_MCO_Clock_Source RCC Extended MCO Clock Source
  * @{
  */
#define RCC_MCOSOURCE_NONE               RCC_CFGR_MCO_NOCLOCK
#define RCC_MCOSOURCE_LSI                RCC_CFGR_MCO_LSI
#define RCC_MCOSOURCE_LSE                RCC_CFGR_MCO_LSE
#define RCC_MCOSOURCE_SYSCLK             RCC_CFGR_MCO_SYSCLK
#define RCC_MCOSOURCE_HSI                RCC_CFGR_MCO_HSI
#define RCC_MCOSOURCE_HSE                RCC_CFGR_MCO_HSE
#define RCC_MCOSOURCE_PLLCLK_DIV2        RCC_CFGR_MCO_PLL

#define IS_RCC_MCOSOURCE(SOURCE)  (((SOURCE) == RCC_MCOSOURCE_NONE)    || \
                                   ((SOURCE) == RCC_MCOSOURCE_LSI)     || \
                                   ((SOURCE) == RCC_MCOSOURCE_LSE)     || \
                                   ((SOURCE) == RCC_MCOSOURCE_SYSCLK)  || \
                                   ((SOURCE) == RCC_MCOSOURCE_HSI)     || \
                                   ((SOURCE) == RCC_MCOSOURCE_HSE)     || \
                                   ((SOURCE) == RCC_MCOSOURCE_PLLCLK_DIV2))
/**
  * @}
  */
#endif /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F334x8                                  */
       /* STM32F373xC || STM32F378xx                   */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303x8) || defined(STM32F328xx) ||                         \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/** @defgroup RCCEx_MCO_Clock_Source RCC Extended MCO Clock Source
  * @{
  */
#define RCC_MCOSOURCE_NONE               RCC_CFGR_MCO_NOCLOCK
#define RCC_MCOSOURCE_LSI                RCC_CFGR_MCO_LSI
#define RCC_MCOSOURCE_LSE                RCC_CFGR_MCO_LSE
#define RCC_MCOSOURCE_SYSCLK             RCC_CFGR_MCO_SYSCLK
#define RCC_MCOSOURCE_HSI                RCC_CFGR_MCO_HSI
#define RCC_MCOSOURCE_HSE                RCC_CFGR_MCO_HSE
#define RCC_MCOSOURCE_PLLCLK_DIV1        (RCC_CFGR_PLLNODIV | RCC_CFGR_MCO_PLL)
#define RCC_MCOSOURCE_PLLCLK_DIV2        RCC_CFGR_MCO_PLL

#define IS_RCC_MCOSOURCE(SOURCE)  (((SOURCE) == RCC_MCOSOURCE_NONE)        || \
                                   ((SOURCE) == RCC_MCOSOURCE_LSI)         || \
                                   ((SOURCE) == RCC_MCOSOURCE_LSE)         || \
                                   ((SOURCE) == RCC_MCOSOURCE_SYSCLK)      || \
                                   ((SOURCE) == RCC_MCOSOURCE_HSI)         || \
                                   ((SOURCE) == RCC_MCOSOURCE_HSE)         || \
                                   ((SOURCE) == RCC_MCOSOURCE_PLLCLK_DIV1) || \
                                   ((SOURCE) == RCC_MCOSOURCE_PLLCLK_DIV2))
/**
  * @}
  */
#endif /* STM32F302xE || STM32F303xE || STM32F398xx */
       /* STM32F303x8 || STM32F328xx ||             */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx)
/** @defgroup RCCEx_PLL_Clock_Source RCC Extended PLL Clock Source
  * @{
  */
#define RCC_PLLSOURCE_HSI                RCC_CFGR_PLLSRC_HSI_PREDIV
#define RCC_PLLSOURCE_HSE                RCC_CFGR_PLLSRC_HSE_PREDIV

#define IS_RCC_PLLSOURCE(SOURCE) (((SOURCE) == RCC_PLLSOURCE_HSI) || \
                                  ((SOURCE) == RCC_PLLSOURCE_HSE))
/**
  * @}
  */

/** @defgroup RCCEx_PLL_Prediv_Factor RCC Extended PLL Prediv Factor
  * @{
  */
#define RCC_PREDIV_DIV1                  RCC_CFGR2_PREDIV_DIV1
#define RCC_PREDIV_DIV2                  RCC_CFGR2_PREDIV_DIV2
#define RCC_PREDIV_DIV3                  RCC_CFGR2_PREDIV_DIV3
#define RCC_PREDIV_DIV4                  RCC_CFGR2_PREDIV_DIV4
#define RCC_PREDIV_DIV5                  RCC_CFGR2_PREDIV_DIV5
#define RCC_PREDIV_DIV6                  RCC_CFGR2_PREDIV_DIV6
#define RCC_PREDIV_DIV7                  RCC_CFGR2_PREDIV_DIV7
#define RCC_PREDIV_DIV8                  RCC_CFGR2_PREDIV_DIV8
#define RCC_PREDIV_DIV9                  RCC_CFGR2_PREDIV_DIV9
#define RCC_PREDIV_DIV10                 RCC_CFGR2_PREDIV_DIV10
#define RCC_PREDIV_DIV11                 RCC_CFGR2_PREDIV_DIV11
#define RCC_PREDIV_DIV12                 RCC_CFGR2_PREDIV_DIV12
#define RCC_PREDIV_DIV13                 RCC_CFGR2_PREDIV_DIV13
#define RCC_PREDIV_DIV14                 RCC_CFGR2_PREDIV_DIV14
#define RCC_PREDIV_DIV15                 RCC_CFGR2_PREDIV_DIV15
#define RCC_PREDIV_DIV16                 RCC_CFGR2_PREDIV_DIV16

#define IS_RCC_PREDIV(PREDIV) (((PREDIV) == RCC_PREDIV_DIV1)  || ((PREDIV) == RCC_PREDIV_DIV2)   || \
                               ((PREDIV) == RCC_PREDIV_DIV3)  || ((PREDIV) == RCC_PREDIV_DIV4)   || \
                               ((PREDIV) == RCC_PREDIV_DIV5)  || ((PREDIV) == RCC_PREDIV_DIV6)   || \
                               ((PREDIV) == RCC_PREDIV_DIV7)  || ((PREDIV) == RCC_PREDIV_DIV8)   || \
                               ((PREDIV) == RCC_PREDIV_DIV9)  || ((PREDIV) == RCC_PREDIV_DIV10)  || \
                               ((PREDIV) == RCC_PREDIV_DIV11) || ((PREDIV) == RCC_PREDIV_DIV12)  || \
                               ((PREDIV) == RCC_PREDIV_DIV13) || ((PREDIV) == RCC_PREDIV_DIV14)  || \
                               ((PREDIV) == RCC_PREDIV_DIV15) || ((PREDIV) == RCC_PREDIV_DIV16))
/**
  * @}
  */
#endif /* STM32F302xE || STM32F303xE || STM32F398xx */

#if defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)
/** @defgroup RCCEx_PLL_Clock_Source RCC Extended PLL Clock Source
  * @{
  */
#define RCC_PLLSOURCE_HSI                RCC_CFGR_PLLSRC_HSI_DIV2
#define RCC_PLLSOURCE_HSE                RCC_CFGR_PLLSRC_HSE_PREDIV

#define IS_RCC_PLLSOURCE(SOURCE) (((SOURCE) == RCC_PLLSOURCE_HSI) || \
                                  ((SOURCE) == RCC_PLLSOURCE_HSE))
/**
  * @}
  */

/** @defgroup RCCEx_HSE_Predivision_Factor RCC Extended HSE Predivision Factor
  * @{
  */

#define RCC_HSE_PREDIV_DIV1              RCC_CFGR2_PREDIV_DIV1
#define RCC_HSE_PREDIV_DIV2              RCC_CFGR2_PREDIV_DIV2
#define RCC_HSE_PREDIV_DIV3              RCC_CFGR2_PREDIV_DIV3
#define RCC_HSE_PREDIV_DIV4              RCC_CFGR2_PREDIV_DIV4
#define RCC_HSE_PREDIV_DIV5              RCC_CFGR2_PREDIV_DIV5
#define RCC_HSE_PREDIV_DIV6              RCC_CFGR2_PREDIV_DIV6
#define RCC_HSE_PREDIV_DIV7              RCC_CFGR2_PREDIV_DIV7
#define RCC_HSE_PREDIV_DIV8              RCC_CFGR2_PREDIV_DIV8
#define RCC_HSE_PREDIV_DIV9              RCC_CFGR2_PREDIV_DIV9
#define RCC_HSE_PREDIV_DIV10             RCC_CFGR2_PREDIV_DIV10
#define RCC_HSE_PREDIV_DIV11             RCC_CFGR2_PREDIV_DIV11
#define RCC_HSE_PREDIV_DIV12             RCC_CFGR2_PREDIV_DIV12
#define RCC_HSE_PREDIV_DIV13             RCC_CFGR2_PREDIV_DIV13
#define RCC_HSE_PREDIV_DIV14             RCC_CFGR2_PREDIV_DIV14
#define RCC_HSE_PREDIV_DIV15             RCC_CFGR2_PREDIV_DIV15
#define RCC_HSE_PREDIV_DIV16             RCC_CFGR2_PREDIV_DIV16

#define IS_RCC_HSE_PREDIV(DIV) (((DIV) == RCC_HSE_PREDIV_DIV1)  || ((DIV) == RCC_HSE_PREDIV_DIV2)  || \
                                ((DIV) == RCC_HSE_PREDIV_DIV3)  || ((DIV) == RCC_HSE_PREDIV_DIV4)  || \
                                ((DIV) == RCC_HSE_PREDIV_DIV5)  || ((DIV) == RCC_HSE_PREDIV_DIV6)  || \
                                ((DIV) == RCC_HSE_PREDIV_DIV7)  || ((DIV) == RCC_HSE_PREDIV_DIV8)  || \
                                ((DIV) == RCC_HSE_PREDIV_DIV9)  || ((DIV) == RCC_HSE_PREDIV_DIV10) || \
                                ((DIV) == RCC_HSE_PREDIV_DIV11) || ((DIV) == RCC_HSE_PREDIV_DIV12) || \
                                ((DIV) == RCC_HSE_PREDIV_DIV13) || ((DIV) == RCC_HSE_PREDIV_DIV14) || \
                                ((DIV) == RCC_HSE_PREDIV_DIV15) || ((DIV) == RCC_HSE_PREDIV_DIV16))
/**
  * @}
  */
#endif /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */
       /* STM32F373xC || STM32F378xx                   */

/** @defgroup RCCEx_Periph_Clock_Selection RCC Extended Periph Clock Selection
  * @{
  */
#if defined(STM32F301x8) || defined(STM32F318xx)
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001)
#define RCC_PERIPHCLK_USART2           ((uint32_t)0x00000002)
#define RCC_PERIPHCLK_USART3           ((uint32_t)0x00000004)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020)
#define RCC_PERIPHCLK_I2C2             ((uint32_t)0x00000040)
#define RCC_PERIPHCLK_ADC1             ((uint32_t)0x00000080)
#define RCC_PERIPHCLK_I2S              ((uint32_t)0x00000200)
#define RCC_PERIPHCLK_TIM1             ((uint32_t)0x00001000)
#define RCC_PERIPHCLK_I2C3             ((uint32_t)0x00008000)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00010000)
#define RCC_PERIPHCLK_TIM15            ((uint32_t)0x00040000)
#define RCC_PERIPHCLK_TIM16            ((uint32_t)0x00080000)
#define RCC_PERIPHCLK_TIM17            ((uint32_t)0x00100000)

#define IS_RCC_PERIPHCLK(SELECTION) ((SELECTION) <= (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | \
                                                     RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_I2C2   | \
                                                     RCC_PERIPHCLK_ADC1   | RCC_PERIPHCLK_I2S    | \
                                                     RCC_PERIPHCLK_I2C3   | RCC_PERIPHCLK_TIM1   | \
                                                     RCC_PERIPHCLK_TIM15  | RCC_PERIPHCLK_TIM16  | \
                                                     RCC_PERIPHCLK_TIM17  | RCC_PERIPHCLK_RTC))
#endif /* STM32F301x8 || STM32F318xx */

#if defined(STM32F302x8)
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001)
#define RCC_PERIPHCLK_USART2           ((uint32_t)0x00000002)
#define RCC_PERIPHCLK_USART3           ((uint32_t)0x00000004)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020)
#define RCC_PERIPHCLK_I2C2             ((uint32_t)0x00000040)
#define RCC_PERIPHCLK_ADC1             ((uint32_t)0x00000080)
#define RCC_PERIPHCLK_I2S              ((uint32_t)0x00000200)
#define RCC_PERIPHCLK_TIM1             ((uint32_t)0x00001000)
#define RCC_PERIPHCLK_I2C3             ((uint32_t)0x00008000)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00010000)
#define RCC_PERIPHCLK_USB              ((uint32_t)0x00020000)
#define RCC_PERIPHCLK_TIM15            ((uint32_t)0x00040000)
#define RCC_PERIPHCLK_TIM16            ((uint32_t)0x00080000)
#define RCC_PERIPHCLK_TIM17            ((uint32_t)0x00100000)

#define IS_RCC_PERIPHCLK(SELECTION) ((SELECTION) <= (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | \
                                                     RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_I2C2   | \
                                                     RCC_PERIPHCLK_ADC1   | RCC_PERIPHCLK_I2S    | \
                                                     RCC_PERIPHCLK_I2C3   | RCC_PERIPHCLK_TIM1   | \
                                                     RCC_PERIPHCLK_RTC    | RCC_PERIPHCLK_USB    |  \
                                                     RCC_PERIPHCLK_TIM15  | RCC_PERIPHCLK_TIM16  |  \
                                                     RCC_PERIPHCLK_TIM17))
#endif /* STM32F302x8 */

#if defined(STM32F302xC)
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001)
#define RCC_PERIPHCLK_USART2           ((uint32_t)0x00000002)
#define RCC_PERIPHCLK_USART3           ((uint32_t)0x00000004)
#define RCC_PERIPHCLK_UART4            ((uint32_t)0x00000008)
#define RCC_PERIPHCLK_UART5            ((uint32_t)0x00000010)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020)
#define RCC_PERIPHCLK_I2C2             ((uint32_t)0x00000040)
#define RCC_PERIPHCLK_ADC12            ((uint32_t)0x00000080)
#define RCC_PERIPHCLK_I2S              ((uint32_t)0x00000200)
#define RCC_PERIPHCLK_TIM1             ((uint32_t)0x00001000)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00010000)
#define RCC_PERIPHCLK_USB              ((uint32_t)0x00020000)

#define IS_RCC_PERIPHCLK(SELECTION) ((SELECTION) <= (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | \
                                                     RCC_PERIPHCLK_UART4  | RCC_PERIPHCLK_UART5  | \
                                                     RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_I2C2   | \
                                                     RCC_PERIPHCLK_ADC12  | RCC_PERIPHCLK_I2S    | \
                                                     RCC_PERIPHCLK_TIM1   | RCC_PERIPHCLK_RTC    | \
                                                     RCC_PERIPHCLK_USB))
#endif /* STM32F302xC */

#if defined(STM32F303xC)
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001)
#define RCC_PERIPHCLK_USART2           ((uint32_t)0x00000002)
#define RCC_PERIPHCLK_USART3           ((uint32_t)0x00000004)
#define RCC_PERIPHCLK_UART4            ((uint32_t)0x00000008)
#define RCC_PERIPHCLK_UART5            ((uint32_t)0x00000010)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020)
#define RCC_PERIPHCLK_I2C2             ((uint32_t)0x00000040)
#define RCC_PERIPHCLK_ADC12            ((uint32_t)0x00000080)
#define RCC_PERIPHCLK_ADC34            ((uint32_t)0x00000100)
#define RCC_PERIPHCLK_I2S              ((uint32_t)0x00000200)
#define RCC_PERIPHCLK_TIM1             ((uint32_t)0x00001000)
#define RCC_PERIPHCLK_TIM8             ((uint32_t)0x00002000)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00010000)
#define RCC_PERIPHCLK_USB              ((uint32_t)0x00020000)

#define IS_RCC_PERIPHCLK(SELECTION) ((SELECTION) <= (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | \
                                                     RCC_PERIPHCLK_UART4  | RCC_PERIPHCLK_UART5  | \
                                                     RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_I2C2   | \
                                                     RCC_PERIPHCLK_ADC12  | RCC_PERIPHCLK_ADC34  | \
                                                     RCC_PERIPHCLK_I2S    | RCC_PERIPHCLK_TIM1   | \
                                                     RCC_PERIPHCLK_TIM8   | RCC_PERIPHCLK_RTC    | \
                                                     RCC_PERIPHCLK_USB))
#endif /* STM32F303xC */

#if defined(STM32F302xE)
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001)
#define RCC_PERIPHCLK_USART2           ((uint32_t)0x00000002)
#define RCC_PERIPHCLK_USART3           ((uint32_t)0x00000004)
#define RCC_PERIPHCLK_UART4            ((uint32_t)0x00000008)
#define RCC_PERIPHCLK_UART5            ((uint32_t)0x00000010)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020)
#define RCC_PERIPHCLK_I2C2             ((uint32_t)0x00000040)
#define RCC_PERIPHCLK_ADC12            ((uint32_t)0x00000080)
#define RCC_PERIPHCLK_I2S              ((uint32_t)0x00000200)
#define RCC_PERIPHCLK_TIM1             ((uint32_t)0x00001000)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00010000)
#define RCC_PERIPHCLK_USB              ((uint32_t)0x00020000)
#define RCC_PERIPHCLK_I2C3             ((uint32_t)0x00040000)
#define RCC_PERIPHCLK_TIM2             ((uint32_t)0x00100000)
#define RCC_PERIPHCLK_TIM34            ((uint32_t)0x00200000)
#define RCC_PERIPHCLK_TIM15            ((uint32_t)0x00400000)
#define RCC_PERIPHCLK_TIM16            ((uint32_t)0x00800000)
#define RCC_PERIPHCLK_TIM17            ((uint32_t)0x01000000)

#define IS_RCC_PERIPHCLK(SELECTION) ((SELECTION) <= (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | \
                                                     RCC_PERIPHCLK_UART4  | RCC_PERIPHCLK_UART5  | \
                                                     RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_I2C2   | \
                                                     RCC_PERIPHCLK_ADC12  | RCC_PERIPHCLK_I2S    | \
                                                     RCC_PERIPHCLK_TIM1   | RCC_PERIPHCLK_RTC    | \
                                                     RCC_PERIPHCLK_USB    | RCC_PERIPHCLK_I2C3   | \
                                                     RCC_PERIPHCLK_TIM2   | RCC_PERIPHCLK_TIM34  | \
                                                     RCC_PERIPHCLK_TIM15  | RCC_PERIPHCLK_TIM16  | \
                                                     RCC_PERIPHCLK_TIM17))
#endif /* STM32F302xE */

#if defined(STM32F303xE)
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001)
#define RCC_PERIPHCLK_USART2           ((uint32_t)0x00000002)
#define RCC_PERIPHCLK_USART3           ((uint32_t)0x00000004)
#define RCC_PERIPHCLK_UART4            ((uint32_t)0x00000008)
#define RCC_PERIPHCLK_UART5            ((uint32_t)0x00000010)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020)
#define RCC_PERIPHCLK_I2C2             ((uint32_t)0x00000040)
#define RCC_PERIPHCLK_ADC12            ((uint32_t)0x00000080)
#define RCC_PERIPHCLK_ADC34            ((uint32_t)0x00000100)
#define RCC_PERIPHCLK_I2S              ((uint32_t)0x00000200)
#define RCC_PERIPHCLK_TIM1             ((uint32_t)0x00001000)
#define RCC_PERIPHCLK_TIM8             ((uint32_t)0x00002000)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00010000)
#define RCC_PERIPHCLK_USB              ((uint32_t)0x00020000)
#define RCC_PERIPHCLK_I2C3             ((uint32_t)0x00040000)
#define RCC_PERIPHCLK_TIM2             ((uint32_t)0x00100000)
#define RCC_PERIPHCLK_TIM34            ((uint32_t)0x00200000)
#define RCC_PERIPHCLK_TIM15            ((uint32_t)0x00400000)
#define RCC_PERIPHCLK_TIM16            ((uint32_t)0x00800000)
#define RCC_PERIPHCLK_TIM17            ((uint32_t)0x01000000)
#define RCC_PERIPHCLK_TIM20            ((uint32_t)0x02000000)

#define IS_RCC_PERIPHCLK(SELECTION) ((SELECTION) <= (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | \
                                                     RCC_PERIPHCLK_UART4  | RCC_PERIPHCLK_UART5  | \
                                                     RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_I2C2   | \
                                                     RCC_PERIPHCLK_ADC12  | RCC_PERIPHCLK_ADC34  | \
                                                     RCC_PERIPHCLK_I2S    | RCC_PERIPHCLK_TIM1   | \
                                                     RCC_PERIPHCLK_TIM8   | RCC_PERIPHCLK_RTC    | \
                                                     RCC_PERIPHCLK_USB    | RCC_PERIPHCLK_I2C3   | \
                                                     RCC_PERIPHCLK_TIM2   | RCC_PERIPHCLK_TIM34  | \
                                                     RCC_PERIPHCLK_TIM15  | RCC_PERIPHCLK_TIM16  | \
                                                     RCC_PERIPHCLK_TIM17  | RCC_PERIPHCLK_TIM20))
#endif /* STM32F303xE */

#if defined(STM32F398xx)
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001)
#define RCC_PERIPHCLK_USART2           ((uint32_t)0x00000002)
#define RCC_PERIPHCLK_USART3           ((uint32_t)0x00000004)
#define RCC_PERIPHCLK_UART4            ((uint32_t)0x00000008)
#define RCC_PERIPHCLK_UART5            ((uint32_t)0x00000010)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020)
#define RCC_PERIPHCLK_I2C2             ((uint32_t)0x00000040)
#define RCC_PERIPHCLK_ADC12            ((uint32_t)0x00000080)
#define RCC_PERIPHCLK_ADC34            ((uint32_t)0x00000100)
#define RCC_PERIPHCLK_I2S              ((uint32_t)0x00000200)
#define RCC_PERIPHCLK_TIM1             ((uint32_t)0x00001000)
#define RCC_PERIPHCLK_TIM8             ((uint32_t)0x00002000)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00010000)
#define RCC_PERIPHCLK_I2C3             ((uint32_t)0x00040000)
#define RCC_PERIPHCLK_TIM2             ((uint32_t)0x00100000)
#define RCC_PERIPHCLK_TIM34            ((uint32_t)0x00200000)
#define RCC_PERIPHCLK_TIM15            ((uint32_t)0x00400000)
#define RCC_PERIPHCLK_TIM16            ((uint32_t)0x00800000)
#define RCC_PERIPHCLK_TIM17            ((uint32_t)0x01000000)
#define RCC_PERIPHCLK_TIM20            ((uint32_t)0x02000000)

#define IS_RCC_PERIPHCLK(SELECTION) ((SELECTION) <= (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | \
                                                     RCC_PERIPHCLK_UART4  | RCC_PERIPHCLK_UART5  | \
                                                     RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_I2C2   | \
                                                     RCC_PERIPHCLK_ADC12  | RCC_PERIPHCLK_ADC34  | \
                                                     RCC_PERIPHCLK_I2S    | RCC_PERIPHCLK_TIM1   | \
                                                     RCC_PERIPHCLK_TIM8   | RCC_PERIPHCLK_RTC    | \
                                                     RCC_PERIPHCLK_I2C3   | RCC_PERIPHCLK_TIM2   | \
                                                     RCC_PERIPHCLK_TIM34  | RCC_PERIPHCLK_TIM15  | \
                                                     RCC_PERIPHCLK_TIM16  | RCC_PERIPHCLK_TIM17  | \
                                                     RCC_PERIPHCLK_TIM20))
#endif /* STM32F398xx */

#if defined(STM32F358xx)
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001)
#define RCC_PERIPHCLK_USART2           ((uint32_t)0x00000002)
#define RCC_PERIPHCLK_USART3           ((uint32_t)0x00000004)
#define RCC_PERIPHCLK_UART4            ((uint32_t)0x00000008)
#define RCC_PERIPHCLK_UART5            ((uint32_t)0x00000010)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020)
#define RCC_PERIPHCLK_I2C2             ((uint32_t)0x00000040)
#define RCC_PERIPHCLK_ADC12            ((uint32_t)0x00000080)
#define RCC_PERIPHCLK_ADC34            ((uint32_t)0x00000100)
#define RCC_PERIPHCLK_I2S              ((uint32_t)0x00000200)
#define RCC_PERIPHCLK_TIM1             ((uint32_t)0x00001000)
#define RCC_PERIPHCLK_TIM8             ((uint32_t)0x00002000)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00010000)

#define IS_RCC_PERIPHCLK(SELECTION) ((SELECTION) <= (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | \
                                                     RCC_PERIPHCLK_UART4  | RCC_PERIPHCLK_UART5  | \
                                                     RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_I2C2   | \
                                                     RCC_PERIPHCLK_ADC12  | RCC_PERIPHCLK_ADC34  | \
                                                     RCC_PERIPHCLK_I2S    | RCC_PERIPHCLK_TIM1   | \
                                                     RCC_PERIPHCLK_TIM8   | RCC_PERIPHCLK_RTC))
#endif /* STM32F358xx */

#if defined(STM32F303x8)
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001)
#define RCC_PERIPHCLK_USART2           ((uint32_t)0x00000002)
#define RCC_PERIPHCLK_USART3           ((uint32_t)0x00000004)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020)
#define RCC_PERIPHCLK_ADC12            ((uint32_t)0x00000080)
#define RCC_PERIPHCLK_TIM1             ((uint32_t)0x00001000)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00010000)

#define IS_RCC_PERIPHCLK(SELECTION) ((SELECTION) <= (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | \
                                                     RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_ADC12  | \
                                                     RCC_PERIPHCLK_TIM1   | RCC_PERIPHCLK_RTC))
#endif /* STM32F303x8 */

#if defined(STM32F334x8)
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001)
#define RCC_PERIPHCLK_USART2           ((uint32_t)0x00000002)
#define RCC_PERIPHCLK_USART3           ((uint32_t)0x00000004)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020)
#define RCC_PERIPHCLK_ADC12            ((uint32_t)0x00000080)
#define RCC_PERIPHCLK_TIM1             ((uint32_t)0x00001000)
#define RCC_PERIPHCLK_HRTIM1           ((uint32_t)0x00004000)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00010000)

#define IS_RCC_PERIPHCLK(SELECTION) ((SELECTION) <= (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | \
                                                     RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_ADC12  | \
                                                     RCC_PERIPHCLK_TIM1   | RCC_PERIPHCLK_HRTIM1 | \
                                                     RCC_PERIPHCLK_RTC))
#endif /* STM32F334x8 */

#if defined(STM32F328xx)
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001)
#define RCC_PERIPHCLK_USART2           ((uint32_t)0x00000002)
#define RCC_PERIPHCLK_USART3           ((uint32_t)0x00000004)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020)
#define RCC_PERIPHCLK_ADC12            ((uint32_t)0x00000080)
#define RCC_PERIPHCLK_TIM1             ((uint32_t)0x00001000)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00010000)

#define IS_RCC_PERIPHCLK(SELECTION) ((SELECTION) <= (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | \
                                                     RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_ADC12  | \
                                                     RCC_PERIPHCLK_TIM1   | RCC_PERIPHCLK_RTC))
#endif /* STM32F328xx */

#if defined(STM32F373xC)
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001)
#define RCC_PERIPHCLK_USART2           ((uint32_t)0x00000002)
#define RCC_PERIPHCLK_USART3           ((uint32_t)0x00000004)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020)
#define RCC_PERIPHCLK_I2C2             ((uint32_t)0x00000040)
#define RCC_PERIPHCLK_ADC1             ((uint32_t)0x00000080)
#define RCC_PERIPHCLK_CEC              ((uint32_t)0x00000400)
#define RCC_PERIPHCLK_SDADC            ((uint32_t)0x00000800)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00010000)
#define RCC_PERIPHCLK_USB              ((uint32_t)0x00020000)

#define IS_RCC_PERIPHCLK(SELECTION) ((SELECTION) <= (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | \
                                                     RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_I2C2   | \
                                                     RCC_PERIPHCLK_ADC1   | RCC_PERIPHCLK_SDADC  | \
                                                     RCC_PERIPHCLK_CEC    | RCC_PERIPHCLK_RTC    | \
                                                     RCC_PERIPHCLK_USB))
#endif /* STM32F373xC */

#if defined(STM32F378xx)
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001)
#define RCC_PERIPHCLK_USART2           ((uint32_t)0x00000002)
#define RCC_PERIPHCLK_USART3           ((uint32_t)0x00000004)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020)
#define RCC_PERIPHCLK_I2C2             ((uint32_t)0x00000040)
#define RCC_PERIPHCLK_ADC1             ((uint32_t)0x00000080)
#define RCC_PERIPHCLK_CEC              ((uint32_t)0x00000400)
#define RCC_PERIPHCLK_SDADC            ((uint32_t)0x00000800)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00010000)

#define IS_RCC_PERIPHCLK(SELECTION) ((SELECTION) <= (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | \
                                                     RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_I2C2   | \
                                                     RCC_PERIPHCLK_ADC1   | RCC_PERIPHCLK_SDADC  | \
                                                     RCC_PERIPHCLK_CEC    | RCC_PERIPHCLK_RTC))
#endif /* STM32F378xx */
/**
  * @}
  */

#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)

/** @defgroup RCCEx_USART1_Clock_Source RCC Extended USART1 Clock Source
  * @{
  */
#define RCC_USART1CLKSOURCE_PCLK2        RCC_CFGR3_USART1SW_PCLK
#define RCC_USART1CLKSOURCE_SYSCLK       RCC_CFGR3_USART1SW_SYSCLK
#define RCC_USART1CLKSOURCE_LSE          RCC_CFGR3_USART1SW_LSE
#define RCC_USART1CLKSOURCE_HSI          RCC_CFGR3_USART1SW_HSI

#define IS_RCC_USART1CLKSOURCE(SOURCE)  (((SOURCE) == RCC_USART1CLKSOURCE_PCLK2)  || \
                                         ((SOURCE) == RCC_USART1CLKSOURCE_SYSCLK) || \
                                         ((SOURCE) == RCC_USART1CLKSOURCE_LSE)    || \
                                         ((SOURCE) == RCC_USART1CLKSOURCE_HSI))
/**
  * @}
  */

/** @defgroup RCCEx_I2C2_Clock_Source RCC Extended I2C2 Clock Source
  * @{
  */
#define RCC_I2C2CLKSOURCE_HSI            RCC_CFGR3_I2C2SW_HSI
#define RCC_I2C2CLKSOURCE_SYSCLK         RCC_CFGR3_I2C2SW_SYSCLK

#define IS_RCC_I2C2CLKSOURCE(SOURCE)  (((SOURCE) == RCC_I2C2CLKSOURCE_HSI) || \
                                       ((SOURCE) == RCC_I2C2CLKSOURCE_SYSCLK))
/**
  * @}
  */

/** @defgroup RCCEx_I2C3_Clock_Source RCC Extended I2C3 Clock Source
  * @{
  */
#define RCC_I2C3CLKSOURCE_HSI            RCC_CFGR3_I2C3SW_HSI
#define RCC_I2C3CLKSOURCE_SYSCLK         RCC_CFGR3_I2C3SW_SYSCLK

#define IS_RCC_I2C3CLKSOURCE(SOURCE)  (((SOURCE) == RCC_I2C3CLKSOURCE_HSI) || \
                                       ((SOURCE) == RCC_I2C3CLKSOURCE_SYSCLK))
/**
  * @}
  */

/** @defgroup RCCEx_ADC1_Clock_Source RCC Extended ADC1 Clock Source
  * @{
  */
#define RCC_ADC1PLLCLK_OFF               RCC_CFGR2_ADC1PRES_NO
#define RCC_ADC1PLLCLK_DIV1              RCC_CFGR2_ADC1PRES_DIV1
#define RCC_ADC1PLLCLK_DIV2              RCC_CFGR2_ADC1PRES_DIV2
#define RCC_ADC1PLLCLK_DIV4              RCC_CFGR2_ADC1PRES_DIV4
#define RCC_ADC1PLLCLK_DIV6              RCC_CFGR2_ADC1PRES_DIV6
#define RCC_ADC1PLLCLK_DIV8              RCC_CFGR2_ADC1PRES_DIV8
#define RCC_ADC1PLLCLK_DIV10             RCC_CFGR2_ADC1PRES_DIV10
#define RCC_ADC1PLLCLK_DIV12             RCC_CFGR2_ADC1PRES_DIV12
#define RCC_ADC1PLLCLK_DIV16             RCC_CFGR2_ADC1PRES_DIV16
#define RCC_ADC1PLLCLK_DIV32             RCC_CFGR2_ADC1PRES_DIV32
#define RCC_ADC1PLLCLK_DIV64             RCC_CFGR2_ADC1PRES_DIV64
#define RCC_ADC1PLLCLK_DIV128            RCC_CFGR2_ADC1PRES_DIV128
#define RCC_ADC1PLLCLK_DIV256            RCC_CFGR2_ADC1PRES_DIV256

#define IS_RCC_ADC1PLLCLK_DIV(ADCCLK) (((ADCCLK) == RCC_ADC1PLLCLK_OFF)   || ((ADCCLK) == RCC_ADC1PLLCLK_DIV1)   || \
                                       ((ADCCLK) == RCC_ADC1PLLCLK_DIV2)  || ((ADCCLK) == RCC_ADC1PLLCLK_DIV4)   || \
                                       ((ADCCLK) == RCC_ADC1PLLCLK_DIV6)  || ((ADCCLK) == RCC_ADC1PLLCLK_DIV8)   || \
                                       ((ADCCLK) == RCC_ADC1PLLCLK_DIV10) || ((ADCCLK) == RCC_ADC1PLLCLK_DIV12)  || \
                                       ((ADCCLK) == RCC_ADC1PLLCLK_DIV16) || ((ADCCLK) == RCC_ADC1PLLCLK_DIV32)  || \
                                       ((ADCCLK) == RCC_ADC1PLLCLK_DIV64) || ((ADCCLK) == RCC_ADC1PLLCLK_DIV128) || \
                                       ((ADCCLK) == RCC_ADC1PLLCLK_DIV256))
/**
  * @}
  */

/** @defgroup RCCEx_I2S_Clock_Source RCC Extended I2S Clock Source
  * @{
  */
#define RCC_I2SCLKSOURCE_SYSCLK          RCC_CFGR_I2SSRC_SYSCLK
#define RCC_I2SCLKSOURCE_EXT             RCC_CFGR_I2SSRC_EXT

#define IS_RCC_I2SCLKSOURCE(SOURCE)  (((SOURCE) == RCC_I2SCLKSOURCE_SYSCLK) || \
                                      ((SOURCE) == RCC_I2SCLKSOURCE_EXT))
/**
  * @}
  */

/** @defgroup RCCEx_TIM1_Clock_Source RCC Extended TIM1 Clock Source
  * @{
  */
#define RCC_TIM1CLK_HCLK                  RCC_CFGR3_TIM1SW_HCLK
#define RCC_TIM1CLK_PLLCLK                RCC_CFGR3_TIM1SW_PLL

#define IS_RCC_TIM1CLKSOURCE(SOURCE) (((SOURCE) == RCC_TIM1CLK_HCLK) || \
                                      ((SOURCE) == RCC_TIM1CLK_PLLCLK))
/**
  * @}
  */

/** @defgroup RCCEx_TIM15_Clock_Source RCC Extended TIM15 Clock Source
  * @{
  */
#define RCC_TIM15CLK_HCLK                 RCC_CFGR3_TIM15SW_HCLK
#define RCC_TIM15CLK_PLLCLK               RCC_CFGR3_TIM15SW_PLL

#define IS_RCC_TIM15CLKSOURCE(SOURCE) (((SOURCE) == RCC_TIM15CLK_HCLK) || \
                                       ((SOURCE) == RCC_TIM15CLK_PLLCLK))
/**
  * @}
  */

/** @defgroup RCCEx_TIM16_Clock_Source RCC Extended TIM16 Clock Source
  * @{
  */
#define RCC_TIM16CLK_HCLK                 RCC_CFGR3_TIM16SW_HCLK
#define RCC_TIM16CLK_PLLCLK               RCC_CFGR3_TIM16SW_PLL

#define IS_RCC_TIM16CLKSOURCE(SOURCE) (((SOURCE) == RCC_TIM16CLK_HCLK) || \
                                       ((SOURCE) == RCC_TIM16CLK_PLLCLK))
/**
  * @}
  */

/** @defgroup RCCEx_TIM17_Clock_Source RCC Extended TIM17 Clock Source
  * @{
  */
#define RCC_TIM17CLK_HCLK                 RCC_CFGR3_TIM17SW_HCLK
#define RCC_TIM17CLK_PLLCLK               RCC_CFGR3_TIM17SW_PLL

#define IS_RCC_TIM17CLKSOURCE(SOURCE) (((SOURCE) == RCC_TIM17CLK_HCLK) || \
                                       ((SOURCE) == RCC_TIM17CLK_PLLCLK))
/**
  * @}
  */

#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx */

#if defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx)

/** @defgroup RCCEx_USART1_Clock_Source RCC Extended USART1 Clock Source
  * @{
  */
#define RCC_USART1CLKSOURCE_PCLK2        RCC_CFGR3_USART1SW_PCLK
#define RCC_USART1CLKSOURCE_SYSCLK       RCC_CFGR3_USART1SW_SYSCLK
#define RCC_USART1CLKSOURCE_LSE          RCC_CFGR3_USART1SW_LSE
#define RCC_USART1CLKSOURCE_HSI          RCC_CFGR3_USART1SW_HSI

#define IS_RCC_USART1CLKSOURCE(SOURCE)  (((SOURCE) == RCC_USART1CLKSOURCE_PCLK2)  || \
                                         ((SOURCE) == RCC_USART1CLKSOURCE_SYSCLK) || \
                                         ((SOURCE) == RCC_USART1CLKSOURCE_LSE)    || \
                                         ((SOURCE) == RCC_USART1CLKSOURCE_HSI))
/**
  * @}
  */

/** @defgroup RCCEx_I2C2_Clock_Source RCC Extended I2C2 Clock Source
  * @{
  */
#define RCC_I2C2CLKSOURCE_HSI            RCC_CFGR3_I2C2SW_HSI
#define RCC_I2C2CLKSOURCE_SYSCLK         RCC_CFGR3_I2C2SW_SYSCLK

#define IS_RCC_I2C2CLKSOURCE(SOURCE)  (((SOURCE) == RCC_I2C2CLKSOURCE_HSI) || \
                                       ((SOURCE) == RCC_I2C2CLKSOURCE_SYSCLK))
/**
  * @}
  */

/** @defgroup RCCEx_ADC12_Clock_Source RCC Extended ADC12 Clock Source
  * @{
  */

/* ADC1 & ADC2 */
#define RCC_ADC12PLLCLK_OFF              RCC_CFGR2_ADCPRE12_NO
#define RCC_ADC12PLLCLK_DIV1             RCC_CFGR2_ADCPRE12_DIV1
#define RCC_ADC12PLLCLK_DIV2             RCC_CFGR2_ADCPRE12_DIV2
#define RCC_ADC12PLLCLK_DIV4             RCC_CFGR2_ADCPRE12_DIV4
#define RCC_ADC12PLLCLK_DIV6             RCC_CFGR2_ADCPRE12_DIV6
#define RCC_ADC12PLLCLK_DIV8             RCC_CFGR2_ADCPRE12_DIV8
#define RCC_ADC12PLLCLK_DIV10            RCC_CFGR2_ADCPRE12_DIV10
#define RCC_ADC12PLLCLK_DIV12            RCC_CFGR2_ADCPRE12_DIV12
#define RCC_ADC12PLLCLK_DIV16            RCC_CFGR2_ADCPRE12_DIV16
#define RCC_ADC12PLLCLK_DIV32            RCC_CFGR2_ADCPRE12_DIV32
#define RCC_ADC12PLLCLK_DIV64            RCC_CFGR2_ADCPRE12_DIV64
#define RCC_ADC12PLLCLK_DIV128           RCC_CFGR2_ADCPRE12_DIV128
#define RCC_ADC12PLLCLK_DIV256           RCC_CFGR2_ADCPRE12_DIV256

#define IS_RCC_ADC12PLLCLK_DIV(ADCCLK) (((ADCCLK) == RCC_ADC12PLLCLK_OFF)   || ((ADCCLK) == RCC_ADC12PLLCLK_DIV1)   || \
                                        ((ADCCLK) == RCC_ADC12PLLCLK_DIV2)  || ((ADCCLK) == RCC_ADC12PLLCLK_DIV4)   || \
                                        ((ADCCLK) == RCC_ADC12PLLCLK_DIV6)  || ((ADCCLK) == RCC_ADC12PLLCLK_DIV8)   || \
                                        ((ADCCLK) == RCC_ADC12PLLCLK_DIV10) || ((ADCCLK) == RCC_ADC12PLLCLK_DIV12)  || \
                                        ((ADCCLK) == RCC_ADC12PLLCLK_DIV16) || ((ADCCLK) == RCC_ADC12PLLCLK_DIV32)  || \
                                        ((ADCCLK) == RCC_ADC12PLLCLK_DIV64) || ((ADCCLK) == RCC_ADC12PLLCLK_DIV128) || \
                                        ((ADCCLK) == RCC_ADC12PLLCLK_DIV256))
/**
  * @}
  */

/** @defgroup RCCEx_I2S_Clock_Source RCC Extended I2S Clock Source
  * @{
  */
#define RCC_I2SCLKSOURCE_SYSCLK          RCC_CFGR_I2SSRC_SYSCLK
#define RCC_I2SCLKSOURCE_EXT             RCC_CFGR_I2SSRC_EXT

#define IS_RCC_I2SCLKSOURCE(SOURCE)  (((SOURCE) == RCC_I2SCLKSOURCE_SYSCLK) || \
                                      ((SOURCE) == RCC_I2SCLKSOURCE_EXT))
/**
  * @}
  */
/** @defgroup RCCEx_TIM1_Clock_Source RCC Extended TIM1 Clock Source
  * @{
  */
#define RCC_TIM1CLK_HCLK                  RCC_CFGR3_TIM1SW_HCLK
#define RCC_TIM1CLK_PLLCLK                RCC_CFGR3_TIM1SW_PLL

#define IS_RCC_TIM1CLKSOURCE(SOURCE) (((SOURCE) == RCC_TIM1CLK_HCLK) || \
                                      ((SOURCE) == RCC_TIM1CLK_PLLCLK))
/**
  * @}
  */

/** @defgroup RCCEx_UART4_Clock_Source RCC Extended UART4 Clock Source
  * @{
  */
#define RCC_UART4CLKSOURCE_PCLK1         RCC_CFGR3_UART4SW_PCLK
#define RCC_UART4CLKSOURCE_SYSCLK        RCC_CFGR3_UART4SW_SYSCLK
#define RCC_UART4CLKSOURCE_LSE           RCC_CFGR3_UART4SW_LSE
#define RCC_UART4CLKSOURCE_HSI           RCC_CFGR3_UART4SW_HSI

#define IS_RCC_UART4CLKSOURCE(SOURCE)  (((SOURCE) == RCC_UART4CLKSOURCE_PCLK1)  || \
                                        ((SOURCE) == RCC_UART4CLKSOURCE_SYSCLK) || \
                                        ((SOURCE) == RCC_UART4CLKSOURCE_LSE)    || \
                                        ((SOURCE) == RCC_UART4CLKSOURCE_HSI))
/**
  * @}
  */

/** @defgroup RCCEx_UART5_Clock_Source RCC Extended UART5 Clock Source
  * @{
  */
#define RCC_UART5CLKSOURCE_PCLK1         RCC_CFGR3_UART5SW_PCLK
#define RCC_UART5CLKSOURCE_SYSCLK        RCC_CFGR3_UART5SW_SYSCLK
#define RCC_UART5CLKSOURCE_LSE           RCC_CFGR3_UART5SW_LSE
#define RCC_UART5CLKSOURCE_HSI           RCC_CFGR3_UART5SW_HSI

#define IS_RCC_UART5CLKSOURCE(SOURCE)  (((SOURCE) == RCC_UART5CLKSOURCE_PCLK1)  || \
                                        ((SOURCE) == RCC_UART5CLKSOURCE_SYSCLK) || \
                                        ((SOURCE) == RCC_UART5CLKSOURCE_LSE)    || \
                                        ((SOURCE) == RCC_UART5CLKSOURCE_HSI))
/**
  * @}
  */

#endif /* STM32F302xC || STM32F303xC || STM32F358xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx)

/** @defgroup RCCEx_USART1_Clock_Source RCC Extended USART1 Clock Source
  * @{
  */
#define RCC_USART1CLKSOURCE_PCLK2        RCC_CFGR3_USART1SW_PCLK
#define RCC_USART1CLKSOURCE_SYSCLK       RCC_CFGR3_USART1SW_SYSCLK
#define RCC_USART1CLKSOURCE_LSE          RCC_CFGR3_USART1SW_LSE
#define RCC_USART1CLKSOURCE_HSI          RCC_CFGR3_USART1SW_HSI

#define IS_RCC_USART1CLKSOURCE(SOURCE)  (((SOURCE) == RCC_USART1CLKSOURCE_PCLK2)  || \
                                         ((SOURCE) == RCC_USART1CLKSOURCE_SYSCLK) || \
                                         ((SOURCE) == RCC_USART1CLKSOURCE_LSE)    || \
                                         ((SOURCE) == RCC_USART1CLKSOURCE_HSI))
/**
  * @}
  */

/** @defgroup RCCEx_I2C2_Clock_Source RCC Extended I2C2 Clock Source
  * @{
  */
#define RCC_I2C2CLKSOURCE_HSI            RCC_CFGR3_I2C2SW_HSI
#define RCC_I2C2CLKSOURCE_SYSCLK         RCC_CFGR3_I2C2SW_SYSCLK

#define IS_RCC_I2C2CLKSOURCE(SOURCE)  (((SOURCE) == RCC_I2C2CLKSOURCE_HSI) || \
                                       ((SOURCE) == RCC_I2C2CLKSOURCE_SYSCLK))
/**
  * @}
  */

/** @defgroup RCCEx_I2C3_Clock_Source RCC Extended I2C3 Clock Source
  * @{
  */
#define RCC_I2C3CLKSOURCE_HSI            RCC_CFGR3_I2C3SW_HSI
#define RCC_I2C3CLKSOURCE_SYSCLK         RCC_CFGR3_I2C3SW_SYSCLK

#define IS_RCC_I2C3CLKSOURCE(SOURCE)  (((SOURCE) == RCC_I2C3CLKSOURCE_HSI) || \
                                       ((SOURCE) == RCC_I2C3CLKSOURCE_SYSCLK))
/**
  * @}
  */

/** @defgroup RCCEx_ADC12_Clock_Source RCC Extended ADC12 Clock Source
  * @{
  */

/* ADC1 & ADC2 */
#define RCC_ADC12PLLCLK_OFF              RCC_CFGR2_ADCPRE12_NO
#define RCC_ADC12PLLCLK_DIV1             RCC_CFGR2_ADCPRE12_DIV1
#define RCC_ADC12PLLCLK_DIV2             RCC_CFGR2_ADCPRE12_DIV2
#define RCC_ADC12PLLCLK_DIV4             RCC_CFGR2_ADCPRE12_DIV4
#define RCC_ADC12PLLCLK_DIV6             RCC_CFGR2_ADCPRE12_DIV6
#define RCC_ADC12PLLCLK_DIV8             RCC_CFGR2_ADCPRE12_DIV8
#define RCC_ADC12PLLCLK_DIV10            RCC_CFGR2_ADCPRE12_DIV10
#define RCC_ADC12PLLCLK_DIV12            RCC_CFGR2_ADCPRE12_DIV12
#define RCC_ADC12PLLCLK_DIV16            RCC_CFGR2_ADCPRE12_DIV16
#define RCC_ADC12PLLCLK_DIV32            RCC_CFGR2_ADCPRE12_DIV32
#define RCC_ADC12PLLCLK_DIV64            RCC_CFGR2_ADCPRE12_DIV64
#define RCC_ADC12PLLCLK_DIV128           RCC_CFGR2_ADCPRE12_DIV128
#define RCC_ADC12PLLCLK_DIV256           RCC_CFGR2_ADCPRE12_DIV256

#define IS_RCC_ADC12PLLCLK_DIV(ADCCLK) (((ADCCLK) == RCC_ADC12PLLCLK_OFF)   || ((ADCCLK) == RCC_ADC12PLLCLK_DIV1)   || \
                                        ((ADCCLK) == RCC_ADC12PLLCLK_DIV2)  || ((ADCCLK) == RCC_ADC12PLLCLK_DIV4)   || \
                                        ((ADCCLK) == RCC_ADC12PLLCLK_DIV6)  || ((ADCCLK) == RCC_ADC12PLLCLK_DIV8)   || \
                                        ((ADCCLK) == RCC_ADC12PLLCLK_DIV10) || ((ADCCLK) == RCC_ADC12PLLCLK_DIV12)  || \
                                        ((ADCCLK) == RCC_ADC12PLLCLK_DIV16) || ((ADCCLK) == RCC_ADC12PLLCLK_DIV32)  || \
                                        ((ADCCLK) == RCC_ADC12PLLCLK_DIV64) || ((ADCCLK) == RCC_ADC12PLLCLK_DIV128) || \
                                        ((ADCCLK) == RCC_ADC12PLLCLK_DIV256))
/**
  * @}
  */

/** @defgroup RCCEx_I2S_Clock_Source RCC Extended I2S Clock Source
  * @{
  */
#define RCC_I2SCLKSOURCE_SYSCLK          RCC_CFGR_I2SSRC_SYSCLK
#define RCC_I2SCLKSOURCE_EXT             RCC_CFGR_I2SSRC_EXT

#define IS_RCC_I2SCLKSOURCE(SOURCE)  (((SOURCE) == RCC_I2SCLKSOURCE_SYSCLK) || \
                                      ((SOURCE) == RCC_I2SCLKSOURCE_EXT))
/**
  * @}
  */

/** @defgroup RCCEx_TIM1_Clock_Source RCC Extended TIM1 Clock Source
  * @{
  */
#define RCC_TIM1CLK_HCLK                  RCC_CFGR3_TIM1SW_HCLK
#define RCC_TIM1CLK_PLLCLK                RCC_CFGR3_TIM1SW_PLL

#define IS_RCC_TIM1CLKSOURCE(SOURCE) (((SOURCE) == RCC_TIM1CLK_HCLK) || \
                                      ((SOURCE) == RCC_TIM1CLK_PLLCLK))
/**
  * @}
  */

/** @defgroup RCCEx_TIM2_Clock_Source RCC Extended TIM2 Clock Source
  * @{
  */
#define RCC_TIM2CLK_HCLK                  RCC_CFGR3_TIM2SW_HCLK
#define RCC_TIM2CLK_PLLCLK                RCC_CFGR3_TIM2SW_PLL

#define IS_RCC_TIM2CLKSOURCE(SOURCE) (((SOURCE) == RCC_TIM2CLK_HCLK) || \
                                      ((SOURCE) == RCC_TIM2CLK_PLLCLK))
/**
  * @}
  */

/** @defgroup RCCEx_TIM34_Clock_Source RCC Extended TIM3 & TIM4 Clock Source
  * @{
  */
#define RCC_TIM34CLK_HCLK                  RCC_CFGR3_TIM34SW_HCLK
#define RCC_TIM34CLK_PLLCLK                RCC_CFGR3_TIM34SW_PLL

#define IS_RCC_TIM3CLKSOURCE(SOURCE) (((SOURCE) == RCC_TIM34CLK_HCLK) || \
                                      ((SOURCE) == RCC_TIM34CLK_PLLCLK))
/**
  * @}
  */

/** @defgroup RCCEx_TIM15_Clock_Source RCC Extended TIM15 Clock Source
  * @{
  */
#define RCC_TIM15CLK_HCLK                  RCC_CFGR3_TIM15SW_HCLK
#define RCC_TIM15CLK_PLLCLK                RCC_CFGR3_TIM15SW_PLL

#define IS_RCC_TIM15CLKSOURCE(SOURCE) (((SOURCE) == RCC_TIM15CLK_HCLK) || \
                                      ((SOURCE) == RCC_TIM15CLK_PLLCLK))
/**
  * @}
  */

/** @defgroup RCCEx_TIM16_Clock_Source RCC Extended TIM16 Clock Source
  * @{
  */
#define RCC_TIM16CLK_HCLK                  RCC_CFGR3_TIM16SW_HCLK
#define RCC_TIM16CLK_PLLCLK                RCC_CFGR3_TIM16SW_PLL

#define IS_RCC_TIM16CLKSOURCE(SOURCE) (((SOURCE) == RCC_TIM16CLK_HCLK) || \
                                      ((SOURCE) == RCC_TIM16CLK_PLLCLK))
/**
  * @}
  */

/** @defgroup RCCEx_TIM17_Clock_Source RCC Extended TIM17 Clock Source
  * @{
  */
#define RCC_TIM17CLK_HCLK                  RCC_CFGR3_TIM17SW_HCLK
#define RCC_TIM17CLK_PLLCLK                RCC_CFGR3_TIM17SW_PLL

#define IS_RCC_TIM17CLKSOURCE(SOURCE) (((SOURCE) == RCC_TIM17CLK_HCLK) || \
                                      ((SOURCE) == RCC_TIM17CLK_PLLCLK))
/**
  * @}
  */

/** @defgroup RCCEx_UART4_Clock_Source RCC Extended UART4 Clock Source
  * @{
  */
#define RCC_UART4CLKSOURCE_PCLK1         RCC_CFGR3_UART4SW_PCLK
#define RCC_UART4CLKSOURCE_SYSCLK        RCC_CFGR3_UART4SW_SYSCLK
#define RCC_UART4CLKSOURCE_LSE           RCC_CFGR3_UART4SW_LSE
#define RCC_UART4CLKSOURCE_HSI           RCC_CFGR3_UART4SW_HSI

#define IS_RCC_UART4CLKSOURCE(SOURCE)  (((SOURCE) == RCC_UART4CLKSOURCE_PCLK1)  || \
                                        ((SOURCE) == RCC_UART4CLKSOURCE_SYSCLK) || \
                                        ((SOURCE) == RCC_UART4CLKSOURCE_LSE)    || \
                                        ((SOURCE) == RCC_UART4CLKSOURCE_HSI))
/**
  * @}
  */

/** @defgroup RCCEx_UART5_Clock_Source RCC Extended UART5 Clock Source
  * @{
  */
#define RCC_UART5CLKSOURCE_PCLK1         RCC_CFGR3_UART5SW_PCLK
#define RCC_UART5CLKSOURCE_SYSCLK        RCC_CFGR3_UART5SW_SYSCLK
#define RCC_UART5CLKSOURCE_LSE           RCC_CFGR3_UART5SW_LSE
#define RCC_UART5CLKSOURCE_HSI           RCC_CFGR3_UART5SW_HSI

#define IS_RCC_UART5CLKSOURCE(SOURCE)  (((SOURCE) == RCC_UART5CLKSOURCE_PCLK1)  || \
                                        ((SOURCE) == RCC_UART5CLKSOURCE_SYSCLK) || \
                                        ((SOURCE) == RCC_UART5CLKSOURCE_LSE)    || \
                                        ((SOURCE) == RCC_UART5CLKSOURCE_HSI))
/**
  * @}
  */

#endif /* STM32F302xE || STM32F303xE || STM32F398xx */

#if defined(STM32F303xE) ||  defined(STM32F398xx)
/** @defgroup RCCEx_TIM20_Clock_Source RCC Extended TIM20 Clock Source
  * @{
  */
#define RCC_TIM20CLK_HCLK                  RCC_CFGR3_TIM20SW_HCLK
#define RCC_TIM20CLK_PLLCLK                RCC_CFGR3_TIM20SW_PLL

#define IS_RCC_TIM20CLKSOURCE(SOURCE) (((SOURCE) == RCC_TIM20CLK_HCLK) || \
                                      ((SOURCE) == RCC_TIM20CLK_PLLCLK))
/**
  * @}
  */
#endif /* STM32F303xE || STM32F398xx */

#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)

/** @defgroup RCCEx_ADC34_Clock_Source RCC Extended ADC34 Clock Source
  * @{
  */

/* ADC3 & ADC4 */
#define RCC_ADC34PLLCLK_OFF              RCC_CFGR2_ADCPRE34_NO
#define RCC_ADC34PLLCLK_DIV1             RCC_CFGR2_ADCPRE34_DIV1
#define RCC_ADC34PLLCLK_DIV2             RCC_CFGR2_ADCPRE34_DIV2
#define RCC_ADC34PLLCLK_DIV4             RCC_CFGR2_ADCPRE34_DIV4
#define RCC_ADC34PLLCLK_DIV6             RCC_CFGR2_ADCPRE34_DIV6
#define RCC_ADC34PLLCLK_DIV8             RCC_CFGR2_ADCPRE34_DIV8
#define RCC_ADC34PLLCLK_DIV10            RCC_CFGR2_ADCPRE34_DIV10
#define RCC_ADC34PLLCLK_DIV12            RCC_CFGR2_ADCPRE34_DIV12
#define RCC_ADC34PLLCLK_DIV16            RCC_CFGR2_ADCPRE34_DIV16
#define RCC_ADC34PLLCLK_DIV32            RCC_CFGR2_ADCPRE34_DIV32
#define RCC_ADC34PLLCLK_DIV64            RCC_CFGR2_ADCPRE34_DIV64
#define RCC_ADC34PLLCLK_DIV128           RCC_CFGR2_ADCPRE34_DIV128
#define RCC_ADC34PLLCLK_DIV256           RCC_CFGR2_ADCPRE34_DIV256

#define IS_RCC_ADC34PLLCLK_DIV(ADCCLK) (((ADCCLK) == RCC_ADC34PLLCLK_OFF)   || ((ADCCLK) == RCC_ADC34PLLCLK_DIV1)   || \
                                        ((ADCCLK) == RCC_ADC34PLLCLK_DIV2)  || ((ADCCLK) == RCC_ADC34PLLCLK_DIV4)   || \
                                        ((ADCCLK) == RCC_ADC34PLLCLK_DIV6)  || ((ADCCLK) == RCC_ADC34PLLCLK_DIV8)   || \
                                        ((ADCCLK) == RCC_ADC34PLLCLK_DIV10) || ((ADCCLK) == RCC_ADC34PLLCLK_DIV12)  || \
                                        ((ADCCLK) == RCC_ADC34PLLCLK_DIV16) || ((ADCCLK) == RCC_ADC34PLLCLK_DIV32)  || \
                                        ((ADCCLK) == RCC_ADC34PLLCLK_DIV64) || ((ADCCLK) == RCC_ADC34PLLCLK_DIV128) || \
                                        ((ADCCLK) == RCC_ADC34PLLCLK_DIV256))
/**
  * @}
  */

/** @defgroup RCCEx_TIM8_Clock_Source RCC Extended TIM8 Clock Source
  * @{
  */
#define RCC_TIM8CLK_HCLK                  RCC_CFGR3_TIM8SW_HCLK
#define RCC_TIM8CLK_PLLCLK                RCC_CFGR3_TIM8SW_PLL

#define IS_RCC_TIM8CLKSOURCE(SOURCE) (((SOURCE) == RCC_TIM8CLK_HCLK) || \
                                      ((SOURCE) == RCC_TIM8CLK_PLLCLK))
/**
  * @}
  */

#endif /* STM32F303xC || STM32F303xE || STM32F398xx || STM32F358xx */

#if defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)

/** @defgroup RCCEx_USART1_Clock_Source RCC Extended USART1 Clock Source
  * @{
  */
#define RCC_USART1CLKSOURCE_PCLK1        RCC_CFGR3_USART1SW_PCLK
#define RCC_USART1CLKSOURCE_SYSCLK       RCC_CFGR3_USART1SW_SYSCLK
#define RCC_USART1CLKSOURCE_LSE          RCC_CFGR3_USART1SW_LSE
#define RCC_USART1CLKSOURCE_HSI          RCC_CFGR3_USART1SW_HSI

#define IS_RCC_USART1CLKSOURCE(SOURCE)  (((SOURCE) == RCC_USART1CLKSOURCE_PCLK1)  || \
                                         ((SOURCE) == RCC_USART1CLKSOURCE_SYSCLK) || \
                                         ((SOURCE) == RCC_USART1CLKSOURCE_LSE)    || \
                                         ((SOURCE) == RCC_USART1CLKSOURCE_HSI))
/**
  * @}
  */

/** @defgroup RCCEx_ADC12_Clock_Source RCC Extended ADC12 Clock Source
  * @{
  */
/* ADC1 & ADC2 */
#define RCC_ADC12PLLCLK_OFF              RCC_CFGR2_ADCPRE12_NO
#define RCC_ADC12PLLCLK_DIV1             RCC_CFGR2_ADCPRE12_DIV1
#define RCC_ADC12PLLCLK_DIV2             RCC_CFGR2_ADCPRE12_DIV2
#define RCC_ADC12PLLCLK_DIV4             RCC_CFGR2_ADCPRE12_DIV4
#define RCC_ADC12PLLCLK_DIV6             RCC_CFGR2_ADCPRE12_DIV6
#define RCC_ADC12PLLCLK_DIV8             RCC_CFGR2_ADCPRE12_DIV8
#define RCC_ADC12PLLCLK_DIV10            RCC_CFGR2_ADCPRE12_DIV10
#define RCC_ADC12PLLCLK_DIV12            RCC_CFGR2_ADCPRE12_DIV12
#define RCC_ADC12PLLCLK_DIV16            RCC_CFGR2_ADCPRE12_DIV16
#define RCC_ADC12PLLCLK_DIV32            RCC_CFGR2_ADCPRE12_DIV32
#define RCC_ADC12PLLCLK_DIV64            RCC_CFGR2_ADCPRE12_DIV64
#define RCC_ADC12PLLCLK_DIV128           RCC_CFGR2_ADCPRE12_DIV128
#define RCC_ADC12PLLCLK_DIV256           RCC_CFGR2_ADCPRE12_DIV256

#define IS_RCC_ADC12PLLCLK_DIV(ADCCLK) (((ADCCLK) == RCC_ADC12PLLCLK_OFF)   || ((ADCCLK) == RCC_ADC12PLLCLK_DIV1)   || \
                                        ((ADCCLK) == RCC_ADC12PLLCLK_DIV2)  || ((ADCCLK) == RCC_ADC12PLLCLK_DIV4)   || \
                                        ((ADCCLK) == RCC_ADC12PLLCLK_DIV6)  || ((ADCCLK) == RCC_ADC12PLLCLK_DIV8)   || \
                                        ((ADCCLK) == RCC_ADC12PLLCLK_DIV10) || ((ADCCLK) == RCC_ADC12PLLCLK_DIV12)  || \
                                        ((ADCCLK) == RCC_ADC12PLLCLK_DIV16) || ((ADCCLK) == RCC_ADC12PLLCLK_DIV32)  || \
                                        ((ADCCLK) == RCC_ADC12PLLCLK_DIV64) || ((ADCCLK) == RCC_ADC12PLLCLK_DIV128) || \
                                        ((ADCCLK) == RCC_ADC12PLLCLK_DIV256))
/**
  * @}
  */

/** @defgroup RCCEx_TIM1_Clock_Source RCC Extended TIM1 Clock Source
  * @{
  */
#define RCC_TIM1CLK_HCLK                  RCC_CFGR3_TIM1SW_HCLK
#define RCC_TIM1CLK_PLLCLK                RCC_CFGR3_TIM1SW_PLL

#define IS_RCC_TIM1CLKSOURCE(SOURCE) (((SOURCE) == RCC_TIM1CLK_HCLK) || \
                                      ((SOURCE) == RCC_TIM1CLK_PLLCLK))
/**
  * @}
  */

#endif /* STM32F303x8 || STM32F334x8 || STM32F328xx */

#if defined(STM32F334x8)

/** @defgroup RCCEx_HRTIM1_Clock_Source RCC Extended HRTIM1 Clock Source
  * @{
  */
#define RCC_HRTIM1CLK_HCLK                RCC_CFGR3_HRTIM1SW_HCLK
#define RCC_HRTIM1CLK_PLLCLK              RCC_CFGR3_HRTIM1SW_PLL

#define IS_RCC_HRTIM1CLKSOURCE(SOURCE) (((SOURCE) == RCC_HRTIM1CLK_HCLK) || \
                                        ((SOURCE) == RCC_HRTIM1CLK_PLLCLK))
/**
  * @}
  */

#endif /* STM32F334x8 */

#if defined(STM32F373xC) || defined(STM32F378xx)

/** @defgroup RCCEx_USART1_Clock_Source  RCC Extended USART1 Clock Source
  * @{
  */
#define RCC_USART1CLKSOURCE_PCLK2        RCC_CFGR3_USART1SW_PCLK
#define RCC_USART1CLKSOURCE_SYSCLK       RCC_CFGR3_USART1SW_SYSCLK
#define RCC_USART1CLKSOURCE_LSE          RCC_CFGR3_USART1SW_LSE
#define RCC_USART1CLKSOURCE_HSI          RCC_CFGR3_USART1SW_HSI

#define IS_RCC_USART1CLKSOURCE(SOURCE)  (((SOURCE) == RCC_USART1CLKSOURCE_PCLK2)  || \
                                         ((SOURCE) == RCC_USART1CLKSOURCE_SYSCLK) || \
                                         ((SOURCE) == RCC_USART1CLKSOURCE_LSE)    || \
                                         ((SOURCE) == RCC_USART1CLKSOURCE_HSI))
/**
  * @}
  */

/** @defgroup RCCEx_I2C2_Clock_Source  RCC Extended I2C2 Clock Source
  * @{
  */
#define RCC_I2C2CLKSOURCE_HSI            RCC_CFGR3_I2C2SW_HSI
#define RCC_I2C2CLKSOURCE_SYSCLK         RCC_CFGR3_I2C2SW_SYSCLK

#define IS_RCC_I2C2CLKSOURCE(SOURCE)  (((SOURCE) == RCC_I2C2CLKSOURCE_HSI) || \
                                       ((SOURCE) == RCC_I2C2CLKSOURCE_SYSCLK))
/**
  * @}
  */

/** @defgroup RCCEx_ADC1_Clock_Source  RCC Extended ADC1 Clock Source
  * @{
  */

/* ADC1 */
#define RCC_ADC1PCLK2_DIV2               RCC_CFGR_ADCPRE_DIV2
#define RCC_ADC1PCLK2_DIV4               RCC_CFGR_ADCPRE_DIV4
#define RCC_ADC1PCLK2_DIV6               RCC_CFGR_ADCPRE_DIV6
#define RCC_ADC1PCLK2_DIV8               RCC_CFGR_ADCPRE_DIV8

#define IS_RCC_ADC1PCLK2_DIV(ADCCLK) (((ADCCLK) == RCC_ADC1PCLK2_DIV2) || ((ADCCLK) == RCC_ADC1PCLK2_DIV4) || \
                                      ((ADCCLK) == RCC_ADC1PCLK2_DIV6) || ((ADCCLK) == RCC_ADC1PCLK2_DIV8))
/**
  * @}
  */

/** @defgroup RCCEx_CEC_Clock_Source RCC Extended CEC Clock Source
  * @{
  */
#define RCC_CECCLKSOURCE_HSI             RCC_CFGR3_CECSW_HSI_DIV244
#define RCC_CECCLKSOURCE_LSE             RCC_CFGR3_CECSW_LSE

#define IS_RCC_CECCLKSOURCE(SOURCE)  (((SOURCE) == RCC_CECCLKSOURCE_HSI) || \
                                      ((SOURCE) == RCC_CECCLKSOURCE_LSE))
/**
  * @}
  */

/** @defgroup RCCEx_SDADC_Clock_Prescaler RCC Extended SDADC Clock Prescaler
  * @{
  */
#define RCC_SDADCSYSCLK_DIV1             RCC_CFGR_SDADCPRE_DIV1
#define RCC_SDADCSYSCLK_DIV2             RCC_CFGR_SDADCPRE_DIV2
#define RCC_SDADCSYSCLK_DIV4             RCC_CFGR_SDADCPRE_DIV4
#define RCC_SDADCSYSCLK_DIV6             RCC_CFGR_SDADCPRE_DIV6
#define RCC_SDADCSYSCLK_DIV8             RCC_CFGR_SDADCPRE_DIV8
#define RCC_SDADCSYSCLK_DIV10            RCC_CFGR_SDADCPRE_DIV10
#define RCC_SDADCSYSCLK_DIV12            RCC_CFGR_SDADCPRE_DIV12
#define RCC_SDADCSYSCLK_DIV14            RCC_CFGR_SDADCPRE_DIV14
#define RCC_SDADCSYSCLK_DIV16            RCC_CFGR_SDADCPRE_DIV16
#define RCC_SDADCSYSCLK_DIV20            RCC_CFGR_SDADCPRE_DIV20
#define RCC_SDADCSYSCLK_DIV24            RCC_CFGR_SDADCPRE_DIV24
#define RCC_SDADCSYSCLK_DIV28            RCC_CFGR_SDADCPRE_DIV28
#define RCC_SDADCSYSCLK_DIV32            RCC_CFGR_SDADCPRE_DIV32
#define RCC_SDADCSYSCLK_DIV36            RCC_CFGR_SDADCPRE_DIV36
#define RCC_SDADCSYSCLK_DIV40            RCC_CFGR_SDADCPRE_DIV40
#define RCC_SDADCSYSCLK_DIV44            RCC_CFGR_SDADCPRE_DIV44
#define RCC_SDADCSYSCLK_DIV48            RCC_CFGR_SDADCPRE_DIV48

#define IS_RCC_SDADCSYSCLK_DIV(DIV) (((DIV) == RCC_SDADCSYSCLK_DIV1)  || ((DIV) == RCC_SDADCSYSCLK_DIV2)   || \
                                     ((DIV) == RCC_SDADCSYSCLK_DIV4)  || ((DIV) == RCC_SDADCSYSCLK_DIV6)   || \
                                     ((DIV) == RCC_SDADCSYSCLK_DIV8)  || ((DIV) == RCC_SDADCSYSCLK_DIV10)  || \
                                     ((DIV) == RCC_SDADCSYSCLK_DIV12) || ((DIV) == RCC_SDADCSYSCLK_DIV14)  || \
                                     ((DIV) == RCC_SDADCSYSCLK_DIV16) || ((DIV) == RCC_SDADCSYSCLK_DIV20)  || \
                                     ((DIV) == RCC_SDADCSYSCLK_DIV24) || ((DIV) == RCC_SDADCSYSCLK_DIV28)  || \
                                     ((DIV) == RCC_SDADCSYSCLK_DIV32) || ((DIV) == RCC_SDADCSYSCLK_DIV36)  || \
                                     ((DIV) == RCC_SDADCSYSCLK_DIV40) || ((DIV) == RCC_SDADCSYSCLK_DIV44)  || \
                                     ((DIV) == RCC_SDADCSYSCLK_DIV48))
/**
  * @}
  */

#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || \
    defined(STM32F302xC) || defined(STM32F303xC) || \
    defined(STM32F302x8)                         || \
    defined(STM32F373xC)
/** @defgroup RCCEx_USB_Clock_Source  RCC Extended USB Clock Source
  * @{
  */
#define RCC_USBPLLCLK_DIV1               RCC_CFGR_USBPRE_DIV1
#define RCC_USBPLLCLK_DIV1_5             RCC_CFGR_USBPRE_DIV1_5

#define IS_RCC_USBCLKSOURCE(SOURCE)  (((SOURCE) == RCC_USBPLLCLK_DIV1) || \
                                      ((SOURCE) == RCC_USBPLLCLK_DIV1_5))
/**
  * @}
  */

#endif /* STM32F302xE || STM32F303xE || */
       /* STM32F302xC || STM32F303xC || */
       /* STM32F302x8                || */
       /* STM32F373xC                   */

#if defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)
/** @defgroup RCCEx_MCOx_Clock_Prescaler RCC Extended MCOx Clock Prescaler
  * @{
  */
#define RCC_MCO_NODIV                    ((uint32_t)0x00000000)

#define IS_RCC_MCODIV(DIV) (((DIV) == RCC_MCO_NODIV))
/**
  * @}
  */
#endif /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F373xC || STM32F378xx                   */
      
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)

/** @defgroup RCCEx_MCOx_Clock_Prescaler RCC Extended MCOx Clock Prescaler
  * @{
  */
#define RCC_MCO_DIV1                     ((uint32_t)0x00000000)
#define RCC_MCO_DIV2                     ((uint32_t)0x10000000)
#define RCC_MCO_DIV4                     ((uint32_t)0x20000000)
#define RCC_MCO_DIV8                     ((uint32_t)0x30000000)
#define RCC_MCO_DIV16                    ((uint32_t)0x40000000)
#define RCC_MCO_DIV32                    ((uint32_t)0x50000000)
#define RCC_MCO_DIV64                    ((uint32_t)0x60000000)
#define RCC_MCO_DIV128                   ((uint32_t)0x70000000)

#define IS_RCC_MCODIV(DIV) (((DIV) == RCC_MCO_DIV1)  || ((DIV) == RCC_MCO_DIV2)   || \
                            ((DIV) == RCC_MCO_DIV4)  || ((DIV) == RCC_MCO_DIV8)   || \
                            ((DIV) == RCC_MCO_DIV16) || ((DIV) == RCC_MCO_DIV32)  || \
                            ((DIV) == RCC_MCO_DIV64) || ((DIV) == RCC_MCO_DIV128))
/**
  * @}
  */

#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Macros RCC Extended Exported Macros
 * @{
 */

/** @defgroup RCCEx_PLL_Configuration RCC Extended PLL Configuration
  * @{   
  */ 
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx)
/** @brief  Macro to configure the PLL clock source, multiplication and division factors.
  * @note   This macro must be used only when the PLL is disabled.
  *
  * @param  __RCC_PLLSource__: specifies the PLL entry clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_PLLSOURCE_HSI: HSI oscillator clock selected as PLL clock entry
  *            @arg RCC_PLLSOURCE_HSE: HSE oscillator clock selected as PLL clock entry
  * @param  __PREDIV__: specifies the predivider factor for PLL VCO input clock
  *         This parameter must be a number between RCC_PREDIV_DIV1 and RCC_PREDIV_DIV16.
  * @param  __PLLMUL__: specifies the multiplication factor for PLL VCO input clock
  *         This parameter must be a number between RCC_PLL_MUL2 and RCC_PLL_MUL16.
  *
  */
#define __HAL_RCC_PLL_CONFIG(__RCC_PLLSource__ , __PREDIV__, __PLLMUL__) \
                  do { \
                    MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PREDIV, (__PREDIV__)); \
                    MODIFY_REG(RCC->CFGR, RCC_CFGR_PLLMUL | RCC_CFGR_PLLSRC, (uint32_t)((__PLLMUL__)|(__RCC_PLLSource__))); \
                  } while(0)
#endif /* STM32F302xE || STM32F303xE || STM32F398xx */

#if defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)
/** @brief  Macro to configure the PLL clock source and multiplication factor.
  * @note   This macro must be used only when the PLL is disabled.
  *
  * @param  __RCC_PLLSource__: specifies the PLL entry clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_PLLSOURCE_HSI: HSI oscillator clock selected as PLL clock entry
  *            @arg RCC_PLLSOURCE_HSE: HSE oscillator clock selected as PLL clock entry
  * @param  __PLLMUL__: specifies the multiplication factor for PLL VCO input clock
  *         This parameter must be a number between RCC_PLL_MUL2 and RCC_PLL_MUL16.
  *
  */
#define __HAL_RCC_PLL_CONFIG(__RCC_PLLSource__ , __PLLMUL__) \
                  MODIFY_REG(RCC->CFGR, RCC_CFGR_PLLMUL | RCC_CFGR_PLLSRC, (uint32_t)((__PLLMUL__)|(__RCC_PLLSource__)))
#endif /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */
       /* STM32F373xC || STM32F378xx                   */
/**
  * @}
  */ 
                    
#if defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)
/** @defgroup RCCEx_HSE_Configuration RCC Extended HSE Configuration
  * @{   
  */ 

/**
  * @brief  Macro to configure the External High Speed oscillator (HSE) Predivision factor for PLL.
  * @note   Predivision factor can not be changed if PLL is used as system clock
  *         In this case, you have to select another source of the system clock, disable the PLL and
  *         then change the HSE predivision factor.
  * @param  __HSEPredivValue__: specifies the division value applied to HSE.
  *         This parameter must be a number between RCC_HSE_PREDIV_DIV1 and RCC_HSE_PREDIV_DIV16.
  */
#define __HAL_RCC_HSE_PREDIV_CONFIG(__HSEPredivValue__) \
                  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PREDIV, (uint32_t)(__HSEPredivValue__))
/**
  * @}
  */
#endif /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */
       /* STM32F373xC || STM32F378xx                   */
                    
/** @defgroup RCCEx_AHB_Clock_Enable_Disable RCC Extended AHB Clock Enable Disable
  * @brief  Enable or disable the AHB peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{   
  */
#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
#define __ADC1_CLK_ENABLE()          (RCC->AHBENR |= (RCC_AHBENR_ADC1EN))

#define __ADC1_CLK_DISABLE()         (RCC->AHBENR &= ~(RCC_AHBENR_ADC1EN))
#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx)
#define __DMA2_CLK_ENABLE()          (RCC->AHBENR |= (RCC_AHBENR_DMA2EN))
#define __GPIOE_CLK_ENABLE()         (RCC->AHBENR |= (RCC_AHBENR_GPIOEEN))
#define __ADC12_CLK_ENABLE()         (RCC->AHBENR |= (RCC_AHBENR_ADC12EN))
/* Aliases for STM32 F3 compatibility */
#define __ADC1_CLK_ENABLE()          __ADC12_CLK_ENABLE()
#define __ADC2_CLK_ENABLE()          __ADC12_CLK_ENABLE()

#define __DMA2_CLK_DISABLE()         (RCC->AHBENR &= ~(RCC_AHBENR_DMA2EN))
#define __GPIOE_CLK_DISABLE()        (RCC->AHBENR &= ~(RCC_AHBENR_GPIOEEN))
#define __ADC12_CLK_DISABLE()        (RCC->AHBENR &= ~(RCC_AHBENR_ADC12EN))
/* Aliases for STM32 F3 compatibility */
#define __ADC1_CLK_DISABLE()          __ADC12_CLK_DISABLE()
#define __ADC2_CLK_DISABLE()          __ADC12_CLK_DISABLE()
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx    */

#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)
#define __ADC34_CLK_ENABLE()         (RCC->AHBENR |= (RCC_AHBENR_ADC34EN))

#define __ADC34_CLK_DISABLE()        (RCC->AHBENR &= ~(RCC_AHBENR_ADC34EN))
#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */

#if defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
#define __ADC12_CLK_ENABLE()         (RCC->AHBENR |= (RCC_AHBENR_ADC12EN))
/* Aliases for STM32 F3 compatibility */
#define __ADC1_CLK_ENABLE()          __ADC12_CLK_ENABLE()
#define __ADC2_CLK_ENABLE()          __ADC12_CLK_ENABLE()

#define __ADC12_CLK_DISABLE()        (RCC->AHBENR &= ~(RCC_AHBENR_ADC12EN))
/* Aliases for STM32 F3 compatibility */
#define __ADC1_CLK_DISABLE()          __ADC12_CLK_DISABLE()
#define __ADC2_CLK_DISABLE()          __ADC12_CLK_DISABLE()
#endif /* STM32F303x8 || STM32F334x8 || STM32F328xx */

#if defined(STM32F373xC) || defined(STM32F378xx)
#define __DMA2_CLK_ENABLE()          (RCC->AHBENR |= (RCC_AHBENR_DMA2EN))
#define __GPIOE_CLK_ENABLE()         (RCC->AHBENR |= (RCC_AHBENR_GPIOEEN))

#define __DMA2_CLK_DISABLE()         (RCC->AHBENR &= ~(RCC_AHBENR_DMA2EN))
#define __GPIOE_CLK_DISABLE()        (RCC->AHBENR &= ~(RCC_AHBENR_GPIOEEN))
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx)
#define __FMC_CLK_ENABLE()           (RCC->AHBENR |= (RCC_AHBENR_FMCEN))
#define __GPIOG_CLK_ENABLE()         (RCC->AHBENR |= (RCC_AHBENR_GPIOGEN))
#define __GPIOH_CLK_ENABLE()         (RCC->AHBENR |= (RCC_AHBENR_GPIOHEN))

#define __FMC_CLK_DISABLE()           (RCC->AHBENR &= ~(RCC_AHBENR_FMCEN))
#define __GPIOG_CLK_DISABLE()         (RCC->AHBENR &= ~(RCC_AHBENR_GPIOGEN))
#define __GPIOH_CLK_DISABLE()         (RCC->AHBENR &= ~(RCC_AHBENR_GPIOHEN))
#endif /* STM32F302xE || STM32F303xE || STM32F398xx */
/**
  * @}
  */

/** @defgroup RCCEx_APB1_Clock_Enable_Disable RCC Extended APB1 Clock Enable Disable
  * @brief  Enable or disable the Low Speed APB (APB1) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{   
  */
#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
#define __SPI2_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_SPI2EN))
#define __SPI3_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_SPI3EN))
#define __I2C2_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_I2C2EN))
#define __I2C3_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_I2C3EN))

#define __SPI2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_SPI2EN))
#define __SPI3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_SPI3EN))
#define __I2C2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_I2C2EN))
#define __I2C3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_I2C3EN))
#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx)
#define __TIM3_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_TIM3EN))
#define __TIM4_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_TIM4EN))
#define __SPI2_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_SPI2EN))
#define __SPI3_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_SPI3EN))
#define __UART4_CLK_ENABLE()   (RCC->APB1ENR |= (RCC_APB1ENR_UART4EN))
#define __UART5_CLK_ENABLE()   (RCC->APB1ENR |= (RCC_APB1ENR_UART5EN))
#define __I2C2_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_I2C2EN))

#define __TIM3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM3EN))
#define __TIM4_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM4EN))
#define __SPI2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_SPI2EN))
#define __SPI3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_SPI3EN))
#define __UART4_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_UART4EN))
#define __UART5_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_UART5EN))
#define __I2C2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_I2C2EN))
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx    */

#if defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
#define __TIM3_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_TIM3EN))
#define __DAC2_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_DAC2EN))

#define __TIM3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM3EN))
#define __DAC2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_DAC2EN))
#endif /* STM32F303x8 || STM32F334x8 || STM32F328xx */

#if defined(STM32F373xC) || defined(STM32F378xx)
#define __TIM3_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_TIM3EN))
#define __TIM4_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_TIM4EN))
#define __TIM5_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_TIM5EN))
#define __TIM12_CLK_ENABLE()   (RCC->APB1ENR |= (RCC_APB1ENR_TIM12EN))
#define __TIM13_CLK_ENABLE()   (RCC->APB1ENR |= (RCC_APB1ENR_TIM13EN))
#define __TIM14_CLK_ENABLE()   (RCC->APB1ENR |= (RCC_APB1ENR_TIM14EN))
#define __TIM18_CLK_ENABLE()   (RCC->APB1ENR |= (RCC_APB1ENR_TIM18EN))
#define __SPI2_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_SPI2EN))
#define __SPI3_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_SPI3EN))
#define __I2C2_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_I2C2EN))
#define __DAC2_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_DAC2EN))
#define __CEC_CLK_ENABLE()     (RCC->APB1ENR |= (RCC_APB1ENR_CECEN))

#define __TIM3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM3EN))
#define __TIM4_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM4EN))
#define __TIM5_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM5EN))
#define __TIM12_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM12EN))
#define __TIM13_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM13EN))
#define __TIM14_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM14EN))
#define __TIM18_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM18EN))
#define __SPI2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_SPI2EN))
#define __SPI3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_SPI3EN))
#define __I2C2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_I2C2EN))
#define __DAC2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_DAC2EN))
#define __CEC_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_CECEN))
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F303xE) || defined(STM32F398xx)                         || \
    defined(STM32F303xC) || defined(STM32F358xx)                         || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)     
#define __TIM7_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_TIM7EN))

#define __TIM7_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM7EN))
#endif /* STM32F303xE || STM32F398xx                || */
       /* STM32F303xC || STM32F358xx                || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F373xC || STM32F378xx                   */

#if defined(STM32F302xE) || defined(STM32F303xE) || \
    defined(STM32F302xC) || defined(STM32F303xC) || \
    defined(STM32F302x8)                         || \
    defined(STM32F373xC)
#define __USB_CLK_ENABLE()     (RCC->APB1ENR |= (RCC_APB1ENR_USBEN))

#define __USB_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_USBEN))
#endif /* STM32F302xE || STM32F303xE || */
       /* STM32F302xC || STM32F303xC || */
       /* STM32F302x8                || */
       /* STM32F373xC                   */

#if !defined(STM32F301x8)
#define __CAN_CLK_ENABLE()     (RCC->APB1ENR |= (RCC_APB1ENR_CANEN))

#define __CAN_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_CANEN))
#endif /* STM32F301x8*/

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx)
#define __I2C3_CLK_ENABLE()          (RCC->APB1ENR |= (RCC_APB1ENR_I2C3EN))

#define __I2C3_CLK_DISABLE()         (RCC->APB1ENR &= ~(RCC_APB1ENR_I2C3EN))
#endif /* STM32F302xE || STM32F303xE || STM32F398xx */
/**
  * @}
  */
  
/** @defgroup RCCEx_APB2_Clock_Enable_Disable RCC Extended APB2 Clock Enable Disable
  * @brief  Enable or disable the High Speed APB (APB2) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{   
  */
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx)
#define __SPI1_CLK_ENABLE()    (RCC->APB2ENR |= (RCC_APB2ENR_SPI1EN))

#define __SPI1_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SPI1EN))
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx    */

#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)
#define __TIM8_CLK_ENABLE()    (RCC->APB2ENR |= (RCC_APB2ENR_TIM8EN))

#define __TIM8_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM8EN))
#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */

#if defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
#define __SPI1_CLK_ENABLE()    (RCC->APB2ENR |= (RCC_APB2ENR_SPI1EN))

#define __SPI1_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SPI1EN))
#endif /* STM32F303x8 || STM32F334x8 || STM32F328xx */

#if defined(STM32F334x8)
#define __HRTIM1_CLK_ENABLE()  (RCC->APB2ENR |= (RCC_APB2ENR_HRTIM1EN))

#define __HRTIM1_CLK_DISABLE() (RCC->APB2ENR &= ~(RCC_APB2ENR_HRTIM1EN))
#endif /* STM32F334x8 */

#if defined(STM32F373xC) || defined(STM32F378xx)
#define __ADC1_CLK_ENABLE()      (RCC->APB2ENR |= (RCC_APB2ENR_ADC1EN))
#define __SPI1_CLK_ENABLE()      (RCC->APB2ENR |= (RCC_APB2ENR_SPI1EN))
#define __TIM19_CLK_ENABLE()     (RCC->APB2ENR |= (RCC_APB2ENR_TIM19EN))
#define __SDADC1_CLK_ENABLE()    (RCC->APB2ENR |= (RCC_APB2ENR_SDADC1EN))
#define __SDADC2_CLK_ENABLE()    (RCC->APB2ENR |= (RCC_APB2ENR_SDADC2EN))
#define __SDADC3_CLK_ENABLE()    (RCC->APB2ENR |= (RCC_APB2ENR_SDADC3EN))

#define __ADC1_CLK_DISABLE()     (RCC->APB2ENR &= ~(RCC_APB2ENR_ADC1EN))
#define __SPI1_CLK_DISABLE()     (RCC->APB2ENR &= ~(RCC_APB2ENR_SPI1EN))
#define __TIM19_CLK_DISABLE()    (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM19EN))
#define __SDADC1_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SDADC1EN))
#define __SDADC2_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SDADC2EN))
#define __SDADC3_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SDADC3EN))
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
#define __TIM1_CLK_ENABLE()    (RCC->APB2ENR |= (RCC_APB2ENR_TIM1EN))

#define __TIM1_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM1EN))
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx)
#define __SPI4_CLK_ENABLE()          (RCC->APB2ENR |= (RCC_APB2ENR_SPI4EN))

#define __SPI4_CLK_DISABLE()         (RCC->APB2ENR &= ~(RCC_APB2ENR_SPI4EN))
#endif /* STM32F302xE || STM32F303xE || STM32F398xx */
      
#if defined(STM32F303xE) || defined(STM32F398xx)
#define __TIM20_CLK_ENABLE()         (RCC->APB2ENR |= (RCC_APB2ENR_TIM20EN))

#define __TIM20_CLK_DISABLE()        (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM20EN))
#endif /* STM32F303xE || STM32F398xx */
      
/**
  * @}
  */

/** @defgroup RCCEx_AHB_Force_Release_Reset RCC Extended AHB Force Release Reset
  * @brief  Force or release AHB peripheral reset.
  * @{   
  */
#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
#define __ADC1_FORCE_RESET()     (RCC->AHBRSTR |= (RCC_AHBRSTR_ADC1RST))

#define __ADC1_RELEASE_RESET()  (RCC->AHBRSTR &= ~(RCC_AHBRSTR_ADC1RST))
#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx)
#define __GPIOE_FORCE_RESET()    (RCC->AHBRSTR |= (RCC_AHBRSTR_GPIOERST))
#define __ADC12_FORCE_RESET()    (RCC->AHBRSTR |= (RCC_AHBRSTR_ADC12RST))
/* Aliases for STM32 F3 compatibility */
#define __ADC1_FORCE_RESET()     __ADC12_FORCE_RESET()
#define __ADC2_FORCE_RESET()     __ADC12_FORCE_RESET()

#define __GPIOE_RELEASE_RESET()  (RCC->AHBRSTR &= ~(RCC_AHBRSTR_GPIOERST))
#define __ADC12_RELEASE_RESET()  (RCC->AHBRSTR &= ~(RCC_AHBRSTR_ADC12RST))
/* Aliases for STM32 F3 compatibility */
#define __ADC1_RELEASE_RESET()    __ADC12_RELEASE_RESET()
#define __ADC2_RELEASE_RESET()    __ADC12_RELEASE_RESET()
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx    */

#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)
#define __ADC34_FORCE_RESET()    (RCC->AHBRSTR |= (RCC_AHBRSTR_ADC34RST))

#define __ADC34_RELEASE_RESET()  (RCC->AHBRSTR &= ~(RCC_AHBRSTR_ADC34RST))
#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */

#if defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
#define __ADC12_FORCE_RESET()    (RCC->AHBRSTR |= (RCC_AHBRSTR_ADC12RST))
/* Aliases for STM32 F3 compatibility */
#define __ADC1_FORCE_RESET()     __ADC12_FORCE_RESET()
#define __ADC2_FORCE_RESET()     __ADC12_FORCE_RESET()

#define __ADC12_RELEASE_RESET()  (RCC->AHBRSTR &= ~(RCC_AHBRSTR_ADC12RST))
/* Aliases for STM32 F3 compatibility */
#define __ADC1_RELEASE_RESET()    __ADC12_RELEASE_RESET()
#define __ADC2_RELEASE_RESET()    __ADC12_RELEASE_RESET()
#endif /* STM32F303x8 || STM32F334x8 || STM32F328xx */

#if defined(STM32F373xC) || defined(STM32F378xx)
#define __GPIOE_FORCE_RESET()   (RCC->AHBRSTR |= (RCC_AHBRSTR_GPIOERST))

#define __GPIOE_RELEASE_RESET() (RCC->AHBRSTR &= ~(RCC_AHBRSTR_GPIOERST))
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx)
#define __FMC_FORCE_RESET()            (RCC->AHBRSTR |= (RCC_AHBRSTR_FMCRST))
#define __GPIOG_FORCE_RESET()          (RCC->AHBRSTR |= (RCC_AHBRSTR_GPIOGRST))
#define __GPIOH_FORCE_RESET()          (RCC->AHBRSTR |= (RCC_AHBRSTR_GPIOHRST))

#define __FMC_RELEASE_RESET()            (RCC->AHBRSTR &= ~(RCC_AHBRSTR_FMCRST))
#define __GPIOG_RELEASE_RESET()          (RCC->AHBRSTR &= ~(RCC_AHBRSTR_GPIOGRST))
#define __GPIOH_RELEASE_RESET()          (RCC->AHBRSTR &= ~(RCC_AHBRSTR_GPIOHRST))
#endif /* STM32F302xE || STM32F303xE || STM32F398xx */
/**
  * @}
  */

/** @defgroup RCCEx_APB1_Force_Release_Reset RCC Extended APB1 Force Release Reset
  * @brief  Force or release APB1 peripheral reset.
  * @{   
  */
#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
#define __SPI2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_SPI2RST))
#define __SPI3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_SPI3RST))
#define __I2C2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_I2C2RST))
#define __I2C3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_I2C3RST))

#define __SPI2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_SPI2RST))
#define __SPI3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_SPI3RST))
#define __I2C2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C2RST))
#define __I2C3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C3RST))
#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx)
#define __TIM3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM3RST))
#define __TIM4_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM4RST))
#define __SPI2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_SPI2RST))
#define __SPI3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_SPI3RST))
#define __UART4_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_UART4RST))
#define __UART5_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_UART5RST))
#define __I2C2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_I2C2RST))

#define __TIM3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM3RST))
#define __TIM4_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM4RST))
#define __SPI2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_SPI2RST))
#define __SPI3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_SPI3RST))
#define __UART4_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART4RST))
#define __UART5_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART5RST))
#define __I2C2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C2RST))
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx */

#if defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
#define __TIM3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM3RST))
#define __DAC2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_DAC2RST))

#define __TIM3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM3RST))
#define __DAC2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_DAC2RST))
#endif /* STM32F303x8 || STM32F334x8 || STM32F328xx */

#if defined(STM32F373xC) || defined(STM32F378xx)
#define __TIM3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM3RST))
#define __TIM4_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM4RST))
#define __TIM5_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM5RST))
#define __TIM12_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM12RST))
#define __TIM13_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM13RST))
#define __TIM14_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM14RST))
#define __TIM18_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM18RST))
#define __SPI2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_SPI2RST))
#define __SPI3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_SPI3RST))
#define __I2C2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_I2C2RST))
#define __DAC2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_DAC2RST))
#define __CEC_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_CECRST))

#define __TIM3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM3RST))
#define __TIM4_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM4RST))
#define __TIM5_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM5RST))
#define __TIM12_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM12RST))
#define __TIM13_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM13RST))
#define __TIM14_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM14RST))
#define __TIM18_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM18RST))
#define __SPI2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_SPI2RST))
#define __SPI3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_SPI3RST))
#define __I2C2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C2RST))
#define __DAC2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_DAC2RST))
#define __CEC_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_CECRST))
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)      
#define __TIM7_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM7RST))

#define __TIM7_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM7RST))
#endif /* STM32F303xE || STM32F398xx                || */
       /* STM32F303xC || STM32F358xx                || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F373xC || STM32F378xx                   */

#if defined(STM32F302xE) || defined(STM32F303xE) || \
    defined(STM32F302xC) || defined(STM32F303xC) || \
    defined(STM32F302x8)                         || \
    defined(STM32F373xC)
#define __USB_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_USBRST))

#define __USB_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_USBRST))
#endif /* STM32F302xE || STM32F303xE || */
       /* STM32F302xC || STM32F303xC || */
       /* STM32F302x8                || */
       /* STM32F373xC                   */

#if !defined(STM32F301x8)
#define __CAN_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_CANRST))

#define __CAN_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_CANRST))
#endif /* STM32F301x8*/

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx)
#define __I2C3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_I2C3RST))

#define __I2C3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C3RST))
#endif /* STM32F302xE || STM32F303xE || STM32F398xx */
/**
  * @}
  */

/** @defgroup RCCEx_APB2_Force_Release_Reset RCC Extended APB2 Force Release Reset
  * @brief  Force or release APB2 peripheral reset.
  * @{   
  */
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx)
#define __SPI1_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_SPI1RST))

#define __SPI1_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI1RST))
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx */

#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)
#define __TIM8_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM8RST))

#define __TIM8_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM8RST))
#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */

#if defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
#define __SPI1_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_SPI1RST))

#define __SPI1_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI1RST))
#endif /* STM32F303x8 || STM32F334x8 || STM32F328xx */

#if defined(STM32F334x8)
#define __HRTIM1_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_HRTIM1RST))

#define __HRTIM1_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_HRTIM1RST))
#endif /* STM32F334x8 */

#if defined(STM32F373xC) || defined(STM32F378xx)
#define __ADC1_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_ADC1RST))
#define __SPI1_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_SPI1RST))
#define __TIM19_FORCE_RESET()    (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM19RST))
#define __SDADC1_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_SDADC1RST))
#define __SDADC2_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_SDADC2RST))
#define __SDADC3_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_SDADC3RST))

#define __ADC1_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_ADC1RST))
#define __SPI1_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI1RST))
#define __TIM19_RELEASE_RESET()  (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM19RST))
#define __SDADC1_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SDADC1RST))
#define __SDADC2_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SDADC2RST))
#define __SDADC3_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SDADC3RST))
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
#define __TIM1_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM1RST))

#define __TIM1_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM1RST))
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx)
#define __SPI4_FORCE_RESET()      (RCC->APB2RSTR |= (RCC_APB2RSTR_SPI4RST))

#define __SPI4_RELEASE_RESET()    (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI4RST))
#endif /* STM32F302xE || STM32F303xE || STM32F398xx */

#if defined(STM32F303xE) || defined(STM32F398xx)
#define __TIM20_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM20RST))

#define __TIM20_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM20RST))
#endif /* STM32F303xE || STM32F398xx */

/**
  * @}
  */

#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/** @defgroup RCCEx_I2Cx_Clock_Config RCC Extended I2Cx Clock Config
  * @{   
  */ 

/** @brief  Macro to configure the I2C2 clock (I2C2CLK).
  * @param  __I2C2CLKSource__: specifies the I2C2 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_I2C2CLKSOURCE_HSI: HSI selected as I2C2 clock
  *            @arg RCC_I2C2CLKSOURCE_SYSCLK: System Clock selected as I2C2 clock
  */
#define __HAL_RCC_I2C2_CONFIG(__I2C2CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_I2C2SW, (uint32_t)(__I2C2CLKSource__))

/** @brief  Macro to get the I2C2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_I2C2CLKSOURCE_HSI: HSI selected as I2C2 clock
  *            @arg RCC_I2C2CLKSOURCE_SYSCLK: System Clock selected as I2C2 clock
  */
#define __HAL_RCC_GET_I2C2_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_I2C2SW)))

/** @brief  Macro to configure the I2C3 clock (I2C3CLK).
  * @param  __I2C3CLKSource__: specifies the I2C3 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_I2C3CLKSOURCE_HSI: HSI selected as I2C3 clock
  *            @arg RCC_I2C3CLKSOURCE_SYSCLK: System Clock selected as I2C3 clock
  */
#define __HAL_RCC_I2C3_CONFIG(__I2C3CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_I2C3SW, (uint32_t)(__I2C3CLKSource__))

/** @brief  Macro to get the I2C3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_I2C3CLKSOURCE_HSI: HSI selected as I2C3 clock
  *            @arg RCC_I2C3CLKSOURCE_SYSCLK: System Clock selected as I2C3 clock
  */
#define __HAL_RCC_GET_I2C3_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_I2C3SW)))

/**
  * @}
  */

/** @defgroup RCCEx_TIMx_Clock_Config RCC Extended TIMx Clock Config
  * @{   
  */ 
/** @brief  Macro to configure the TIM1 clock (TIM1CLK).
  * @param  __TIM1CLKSource__: specifies the TIM1 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM1CLKSOURCE_HCLK: HCLK selected as TIM1 clock
  *            @arg RCC_TIM1CLKSOURCE_PLL: PLL Clock selected as TIM1 clock
  */
#define __HAL_RCC_TIM1_CONFIG(__TIM1CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_TIM1SW, (uint32_t)(__TIM1CLKSource__))

/** @brief  Macro to get the TIM1 clock (TIM1CLK).
  * @retval The clock source can be one of the following values:
  *          This parameter can be one of the following values:
  *            @arg RCC_TIM1CLKSOURCE_HCLK: HCLK selected as TIM1 clock
  *            @arg RCC_TIM1CLKSOURCE_PLL: PLL Clock selected as TIM1 clock
  */
#define __HAL_RCC_GET_TIM1_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_TIM1SW)))

/** @brief  Macro to configure the TIM15 clock (TIM15CLK).
  * @param  __TIM15CLKSource__: specifies the TIM15 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM15CLKSOURCE_HCLK: HCLK selected as TIM15 clock
  *            @arg RCC_TIM15CLKSOURCE_PLL: PLL Clock selected as TIM15 clock
  */
#define __HAL_RCC_TIM15_CONFIG(__TIM15CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_TIM15SW, (uint32_t)(__TIM15CLKSource__))

/** @brief  Macro to get the TIM15 clock (TIM15CLK).
  * @retval The clock source can be one of the following values:
  *          This parameter can be one of the following values:
  *            @arg RCC_TIM15CLKSOURCE_HCLK: HCLK selected as TIM15 clock
  *            @arg RCC_TIM15CLKSOURCE_PLL: PLL Clock selected as TIM15 clock
  */
#define __HAL_RCC_GET_TIM15_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_TIM15SW)))

/** @brief  Macro to configure the TIM16 clock (TIM16CLK).
  * @param  __TIM16CLKSource__: specifies the TIM16 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM16CLKSOURCE_HCLK: HCLK selected as TIM16 clock
  *            @arg RCC_TIM16CLKSOURCE_PLL: PLL Clock selected as TIM16 clock
  */
#define __HAL_RCC_TIM16_CONFIG(__TIM16CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_TIM16SW, (uint32_t)(__TIM16CLKSource__))

/** @brief  Macro to get the TIM16 clock (TIM16CLK).
  * @retval The clock source can be one of the following values:
  *          This parameter can be one of the following values:
  *            @arg RCC_TIM16CLKSOURCE_HCLK: HCLK selected as TIM16 clock
  *            @arg RCC_TIM16CLKSOURCE_PLL: PLL Clock selected as TIM16 clock
  */
#define __HAL_RCC_GET_TIM16_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_TIM16SW)))

/** @brief  Macro to configure the TIM17 clock (TIM17CLK).
  * @param  __TIM17CLKSource__: specifies the TIM17 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM17CLKSOURCE_HCLK: HCLK selected as TIM17 clock
  *            @arg RCC_TIM17CLKSOURCE_PLL: PLL Clock selected as TIM17 clock
  */
#define __HAL_RCC_TIM17_CONFIG(__TIM17CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_TIM17SW, (uint32_t)(__TIM17CLKSource__))

/** @brief  Macro to get the TIM17 clock (TIM17CLK).
  * @retval The clock source can be one of the following values:
  *          This parameter can be one of the following values:
  *            @arg RCC_TIM17CLKSOURCE_HCLK: HCLK selected as TIM17 clock
  *            @arg RCC_TIM17CLKSOURCE_PLL: PLL Clock selected as TIM17 clock
  */
#define __HAL_RCC_GET_TIM17_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_TIM17SW)))

/**
  * @}
  */

/** @defgroup RCCEx_I2Sx_Clock_Config RCC Extended I2Sx Clock Config
  * @{   
  */ 
/** @brief  Macro to configure the I2S clock source (I2SCLK).
  * @note   This function must be called before enabling the I2S APB clock.
  * @param  __I2SCLKSource__: specifies the I2S clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_I2SCLKSOURCE_SYSCLK: SYSCLK clock used as I2S clock source
  *            @arg RCC_I2SCLKSOURCE_EXT: External clock mapped on the I2S_CKIN pin
  *                                        used as I2S clock source
  */
#define __HAL_RCC_I2S_CONFIG(__I2SCLKSource__) \
                  MODIFY_REG(RCC->CFGR, RCC_CFGR_I2SSRC, (uint32_t)(__I2SCLKSource__))

/** @brief  Macro to get the I2S clock source (I2SCLK).
  * @retval The clock source can be one of the following values:
  *            @arg RCC_I2SCLKSOURCE_SYSCLK: SYSCLK clock used as I2S clock source
  *            @arg RCC_I2SCLKSOURCE_EXT: External clock mapped on the I2S_CKIN pin
  *                                        used as I2S clock source
  */
#define __HAL_RCC_GET_I2S_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_I2SSRC)))
/**
  * @}
  */

/** @defgroup RCCEx_ADCx_Clock_Config RCC Extended ADCx Clock Config
  * @{   
  */ 

/** @brief  Macro to configure the ADC1 clock (ADC1CLK).
  * @param  __ADC1CLKSource__: specifies the ADC1 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_ADC1PLLCLK_OFF:  ADC1 PLL clock disabled, ADC1 can use AHB clock
  *            @arg RCC_ADC1PLLCLK_DIV1: PLL clock divided by 1 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV2: PLL clock divided by 2 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV4: PLL clock divided by 4 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV6: PLL clock divided by 6 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV8: PLL clock divided by 8 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV10: PLL clock divided by 10 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV12: PLL clock divided by 12 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV16: PLL clock divided by 16 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV32: PLL clock divided by 32 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV64: PLL clock divided by 64 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV128: PLL clock divided by 128 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV256: PLL clock divided by 256 selected as ADC1 clock
  */
#define __HAL_RCC_ADC1_CONFIG(__ADC1CLKSource__) \
                  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_ADC1PRES, (uint32_t)(__ADC1CLKSource__))

/** @brief  Macro to get the ADC1 clock
  * @retval The clock source can be one of the following values:
  *            @arg RCC_ADC1PLLCLK_OFF:  ADC1 PLL clock disabled, ADC1 can use AHB clock
  *            @arg RCC_ADC1PLLCLK_DIV1: PLL clock divided by 1 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV2: PLL clock divided by 2 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV4: PLL clock divided by 4 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV6: PLL clock divided by 6 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV8: PLL clock divided by 8 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV10: PLL clock divided by 10 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV12: PLL clock divided by 12 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV16: PLL clock divided by 16 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV32: PLL clock divided by 32 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV64: PLL clock divided by 64 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV128: PLL clock divided by 128 selected as ADC1 clock
  *            @arg RCC_ADC1PLLCLK_DIV256: PLL clock divided by 256 selected as ADC1 clock
  */
#define __HAL_RCC_GET_ADC1_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_ADC1PRES)))
/**
  * @}
  */

#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx)
/** @defgroup RCCEx_I2Cx_Clock_Config RCC Extended I2Cx Clock Config
  * @{   
  */ 

/** @brief  Macro to configure the I2C2 clock (I2C2CLK).
  * @param  __I2C2CLKSource__: specifies the I2C2 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_I2C2CLKSOURCE_HSI: HSI selected as I2C2 clock
  *            @arg RCC_I2C2CLKSOURCE_SYSCLK: System Clock selected as I2C2 clock
  */
#define __HAL_RCC_I2C2_CONFIG(__I2C2CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_I2C2SW, (uint32_t)(__I2C2CLKSource__))

/** @brief  Macro to get the I2C2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_I2C2CLKSOURCE_HSI: HSI selected as I2C2 clock
  *            @arg RCC_I2C2CLKSOURCE_SYSCLK: System Clock selected as I2C2 clock
  */
#define __HAL_RCC_GET_I2C2_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_I2C2SW)))
/**
  * @}
  */

/** @defgroup RCCEx_ADCx_Clock_Config RCC Extended ADCx Clock Config
  * @{   
  */ 

/** @brief  Macro to configure the ADC1 & ADC2 clock (ADC12CLK).
  * @param  __ADC12CLKSource__: specifies the ADC1 & ADC2 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_ADC12PLLCLK_OFF:  ADC1 & ADC2 PLL clock disabled, ADC1 & ADC2 can use AHB clock
  *            @arg RCC_ADC12PLLCLK_DIV1: PLL clock divided by 1 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV2: PLL clock divided by 2 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV4: PLL clock divided by 4 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV6: PLL clock divided by 6 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV8: PLL clock divided by 8 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV10: PLL clock divided by 10 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV12: PLL clock divided by 12 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV16: PLL clock divided by 16 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV32: PLL clock divided by 32 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV64: PLL clock divided by 64 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV128: PLL clock divided by 128 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV256: PLL clock divided by 256 selected as ADC1 & ADC2 clock
  */
#define __HAL_RCC_ADC12_CONFIG(__ADC12CLKSource__) \
                  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_ADCPRE12, (uint32_t)(__ADC12CLKSource__))

/** @brief  Macro to get the ADC1 & ADC2 clock
  * @retval The clock source can be one of the following values:
  *            @arg RCC_ADC12PLLCLK_OFF:  ADC1 & ADC2 PLL clock disabled, ADC1 & ADC2 can use AHB clock
  *            @arg RCC_ADC12PLLCLK_DIV1: PLL clock divided by 1 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV2: PLL clock divided by 2 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV4: PLL clock divided by 4 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV6: PLL clock divided by 6 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV8: PLL clock divided by 8 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV10: PLL clock divided by 10 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV12: PLL clock divided by 12 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV16: PLL clock divided by 16 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV32: PLL clock divided by 32 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV64: PLL clock divided by 64 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV128: PLL clock divided by 128 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV256: PLL clock divided by 256 selected as ADC1 & ADC2 clock
  */
#define __HAL_RCC_GET_ADC12_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_ADCPRE12)))
/**
  * @}
  */

/** @defgroup RCCEx_TIMx_Clock_Config RCC Extended TIMx Clock Config
  * @{   
  */ 

/** @brief  Macro to configure the TIM1 clock (TIM1CLK).
  * @param  __TIM1CLKSource__: specifies the TIM1 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM1CLKSOURCE_HCLK: HCLK selected as TIM1 clock
  *            @arg RCC_TIM1CLKSOURCE_PLL: PLL Clock selected as TIM1 clock
  */
#define __HAL_RCC_TIM1_CONFIG(__TIM1CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_TIM1SW, (uint32_t)(__TIM1CLKSource__))

/** @brief  Macro to get the TIM1 clock (TIM1CLK).
  * @retval The clock source can be one of the following values:
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM1CLKSOURCE_HCLK: HCLK selected as TIM1 clock
  *            @arg RCC_TIM1CLKSOURCE_PLL: PLL Clock selected as TIM1 clock
  */
#define __HAL_RCC_GET_TIM1_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_TIM1SW)))
/**
  * @}
  */

/** @defgroup RCCEx_I2Sx_Clock_Config RCC Extended I2Sx Clock Config
  * @{   
  */ 

/** @brief  Macro to configure the I2S clock source (I2SCLK).
  * @note   This function must be called before enabling the I2S APB clock.
  * @param  __I2SCLKSource__: specifies the I2S clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_I2SCLKSOURCE_SYSCLK: SYSCLK clock used as I2S clock source
  *            @arg RCC_I2SCLKSOURCE_EXT: External clock mapped on the I2S_CKIN pin
  *                                        used as I2S clock source
  */
#define __HAL_RCC_I2S_CONFIG(__I2SCLKSource__) \
                  MODIFY_REG(RCC->CFGR, RCC_CFGR_I2SSRC, (uint32_t)(__I2SCLKSource__))

/** @brief  Macro to get the I2S clock source (I2SCLK).
  * @retval The clock source can be one of the following values:
  *            @arg RCC_I2SCLKSOURCE_SYSCLK: SYSCLK clock used as I2S clock source
  *            @arg RCC_I2SCLKSOURCE_EXT: External clock mapped on the I2S_CKIN pin
  *                                        used as I2S clock source
  */
#define __HAL_RCC_GET_I2S_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_I2SSRC)))
/**
  * @}
  */

/** @defgroup RCCEx_UARTx_Clock_Config RCC Extended UARTx Clock Config
  * @{   
  */ 

/** @brief  Macro to configure the UART4 clock (UART4CLK).
  * @param  __UART4CLKSource__: specifies the UART4 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_UART4CLKSOURCE_PCLK1: PCLK1 selected as UART4 clock
  *            @arg RCC_UART4CLKSOURCE_HSI: HSI selected as UART4 clock
  *            @arg RCC_UART4CLKSOURCE_SYSCLK: System Clock selected as UART4 clock
  *            @arg RCC_UART4CLKSOURCE_LSE: LSE selected as UART4 clock
  */
#define __HAL_RCC_UART4_CONFIG(__UART4CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_UART4SW, (uint32_t)(__UART4CLKSource__))

/** @brief  Macro to get the UART4 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_UART4CLKSOURCE_PCLK1: PCLK1 selected as UART4 clock
  *            @arg RCC_UART4CLKSOURCE_HSI: HSI selected as UART4 clock
  *            @arg RCC_UART4CLKSOURCE_SYSCLK: System Clock selected as UART4 clock
  *            @arg RCC_UART4CLKSOURCE_LSE: LSE selected as UART4 clock
  */
#define __HAL_RCC_GET_UART4_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_UART4SW)))

/** @brief  Macro to configure the UART5 clock (UART5CLK).
  * @param  __UART5CLKSource__: specifies the UART5 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_UART5CLKSOURCE_PCLK1: PCLK1 selected as UART5 clock
  *            @arg RCC_UART5CLKSOURCE_HSI: HSI selected as UART5 clock
  *            @arg RCC_UART5CLKSOURCE_SYSCLK: System Clock selected as UART5 clock
  *            @arg RCC_UART5CLKSOURCE_LSE: LSE selected as UART5 clock
  */
#define __HAL_RCC_UART5_CONFIG(__UART5CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_UART5SW, (uint32_t)(__UART5CLKSource__))

/** @brief  Macro to get the UART5 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_UART5CLKSOURCE_PCLK1: PCLK1 selected as UART5 clock
  *            @arg RCC_UART5CLKSOURCE_HSI: HSI selected as UART5 clock
  *            @arg RCC_UART5CLKSOURCE_SYSCLK: System Clock selected as UART5 clock
  *            @arg RCC_UART5CLKSOURCE_LSE: LSE selected as UART5 clock
  */
#define __HAL_RCC_GET_UART5_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_UART5SW)))
/**
  * @}
  */
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx    */

#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)
/** @defgroup RCCEx_ADCx_Clock_Config RCC Extended ADCx Clock Config
  * @{   
  */ 

/** @brief  Macro to configure the ADC3 & ADC4 clock (ADC34CLK).
  * @param  __ADC34CLKSource__: specifies the ADC3 & ADC4 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_ADC34PLLCLK_OFF:  ADC3 & ADC4 PLL clock disabled, ADC3 & ADC4 can use AHB clock
  *            @arg RCC_ADC34PLLCLK_DIV1: PLL clock divided by 1 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV2: PLL clock divided by 2 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV4: PLL clock divided by 4 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV6: PLL clock divided by 6 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV8: PLL clock divided by 8 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV10: PLL clock divided by 10 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV12: PLL clock divided by 12 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV16: PLL clock divided by 16 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV32: PLL clock divided by 32 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV64: PLL clock divided by 64 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV128: PLL clock divided by 128 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV256: PLL clock divided by 256 selected as ADC3 & ADC4 clock
  */
#define __HAL_RCC_ADC34_CONFIG(__ADC34CLKSource__) \
                  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_ADCPRE34, (uint32_t)(__ADC34CLKSource__))

/** @brief  Macro to get the ADC3 & ADC4 clock
  * @retval The clock source can be one of the following values:
  *            @arg RCC_ADC34PLLCLK_OFF:  ADC3 & ADC4 PLL clock disabled, ADC3 & ADC4 can use AHB clock
  *            @arg RCC_ADC34PLLCLK_DIV1: PLL clock divided by 1 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV2: PLL clock divided by 2 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV4: PLL clock divided by 4 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV6: PLL clock divided by 6 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV8: PLL clock divided by 8 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV10: PLL clock divided by 10 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV12: PLL clock divided by 12 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV16: PLL clock divided by 16 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV32: PLL clock divided by 32 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV64: PLL clock divided by 64 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV128: PLL clock divided by 128 selected as ADC3 & ADC4 clock
  *            @arg RCC_ADC34PLLCLK_DIV256: PLL clock divided by 256 selected as ADC3 & ADC4 clock
  */
#define __HAL_RCC_GET_ADC34_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_ADCPRE34)))
/**
  * @}
  */

/** @defgroup RCCEx_TIMx_Clock_Config RCC Extended TIMx Clock Config
  * @{   
  */ 

/** @brief  Macro to configure the TIM8 clock (TIM8CLK).
  * @param  __TIM8CLKSource__: specifies the TIM8 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM8CLKSOURCE_HCLK: HCLK selected as TIM8 clock
  *            @arg RCC_TIM8CLKSOURCE_PLL: PLL Clock selected as TIM8 clock
  */
#define __HAL_RCC_TIM8_CONFIG(__TIM8CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_TIM8SW, (uint32_t)(__TIM8CLKSource__))

/** @brief  Macro to get the TIM8 clock (TIM8CLK).
  * @retval The clock source can be one of the following values:
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM8CLKSOURCE_HCLK: HCLK selected as TIM8 clock
  *            @arg RCC_TIM8CLKSOURCE_PLL: PLL Clock selected as TIM8 clock
  */
#define __HAL_RCC_GET_TIM8_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_TIM8SW)))

/**
  * @}
  */
#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */

#if defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
/** @defgroup RCCEx_ADCx_Clock_Config RCC Extended ADCx Clock Config
  * @{   
  */ 

/** @brief  Macro to configure the ADC1 & ADC2 clock (ADC12CLK).
  * @param  __ADC12CLKSource__: specifies the ADC1 & ADC2 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_ADC12PLLCLK_OFF:  ADC1 & ADC2 PLL clock disabled, ADC1 & ADC2 can use AHB clock
  *            @arg RCC_ADC12PLLCLK_DIV1: PLL clock divided by 1 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV2: PLL clock divided by 2 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV4: PLL clock divided by 4 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV6: PLL clock divided by 6 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV8: PLL clock divided by 8 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV10: PLL clock divided by 10 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV12: PLL clock divided by 12 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV16: PLL clock divided by 16 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV32: PLL clock divided by 32 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV64: PLL clock divided by 64 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV128: PLL clock divided by 128 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV256: PLL clock divided by 256 selected as ADC1 & ADC2 clock
  */
#define __HAL_RCC_ADC12_CONFIG(__ADC12CLKSource__) \
                  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_ADCPRE12, (uint32_t)(__ADC12CLKSource__))

/** @brief  Macro to get the ADC1 & ADC2 clock
  * @retval The clock source can be one of the following values:
  *            @arg RCC_ADC12PLLCLK_OFF:  ADC1 & ADC2 PLL clock disabled, ADC1 & ADC2 can use AHB clock
  *            @arg RCC_ADC12PLLCLK_DIV1: PLL clock divided by 1 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV2: PLL clock divided by 2 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV4: PLL clock divided by 4 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV6: PLL clock divided by 6 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV8: PLL clock divided by 8 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV10: PLL clock divided by 10 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV12: PLL clock divided by 12 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV16: PLL clock divided by 16 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV32: PLL clock divided by 32 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV64: PLL clock divided by 64 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV128: PLL clock divided by 128 selected as ADC1 & ADC2 clock
  *            @arg RCC_ADC12PLLCLK_DIV256: PLL clock divided by 256 selected as ADC1 & ADC2 clock
  */
#define __HAL_RCC_GET_ADC12_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_ADCPRE12)))                    
/**
  * @}
  */

/** @defgroup RCCEx_TIMx_Clock_Config RCC Extended TIMx Clock Config
  * @{   
  */ 
/** @brief  Macro to configure the TIM1 clock (TIM1CLK).
  * @param  __TIM1CLKSource__: specifies the TIM1 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM1CLKSOURCE_HCLK: HCLK selected as TIM1 clock
  *            @arg RCC_TIM1CLKSOURCE_PLL: PLL Clock selected as TIM1 clock
  */
#define __HAL_RCC_TIM1_CONFIG(__TIM1CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_TIM1SW, (uint32_t)(__TIM1CLKSource__))

/** @brief  Macro to get the TIM1 clock (TIM1CLK).
  * @retval The clock source can be one of the following values:
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM1CLKSOURCE_HCLK: HCLK selected as TIM1 clock
  *            @arg RCC_TIM1CLKSOURCE_PLL: PLL Clock selected as TIM1 clock
  */
#define __HAL_RCC_GET_TIM1_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_TIM1SW)))
/**
  * @}
  */
#endif /* STM32F303x8 || STM32F334x8 || STM32F328xx */

#if defined(STM32F334x8)
/** @defgroup RCCEx_HRTIMx_Clock_Config RCC Extended HRTIMx Clock Config
  * @{   
  */ 
/** @brief  Macro to configure the HRTIM1 clock.
  * @param  __HRTIM1CLKSource__: specifies the HRTIM1 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_HRTIM1CLKSOURCE_HCLK: HCLK selected as HRTIM1 clock
  *            @arg RCC_HRTIM1CLKSOURCE_PLL: PLL Clock selected as HRTIM1 clock
  */
#define __HAL_RCC_HRTIM1_CONFIG(__HRTIM1CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_HRTIM1SW, (uint32_t)(__HRTIM1CLKSource__))

/** @brief  Macro to get the HRTIM1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_HRTIM1CLKSOURCE_HCLK: HCLK selected as HRTIM1 clock
  *            @arg RCC_HRTIM1CLKSOURCE_PLL: PLL Clock selected as HRTIM1 clock
  */
#define __HAL_RCC_GET_HRTIM1_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_HRTIM1SW)))
/**
  * @}
  */
#endif /* STM32F334x8 */

#if defined(STM32F373xC) || defined(STM32F378xx)
/** @defgroup RCCEx_I2Cx_Clock_Config RCC Extended I2Cx Clock Config
  * @{   
  */ 
/** @brief  Macro to configure the I2C2 clock (I2C2CLK).
  * @param  __I2C2CLKSource__: specifies the I2C2 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_I2C2CLKSOURCE_HSI: HSI selected as I2C2 clock
  *            @arg RCC_I2C2CLKSOURCE_SYSCLK: System Clock selected as I2C2 clock
  */
#define __HAL_RCC_I2C2_CONFIG(__I2C2CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_I2C2SW, (uint32_t)(__I2C2CLKSource__))

/** @brief  Macro to get the I2C2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_I2C2CLKSOURCE_HSI: HSI selected as I2C2 clock
  *            @arg RCC_I2C2CLKSOURCE_SYSCLK: System Clock selected as I2C2 clock
  */
#define __HAL_RCC_GET_I2C2_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_I2C2SW)))
/**
  * @}
  */

/** @defgroup RCCEx_ADCx_Clock_Config RCC Extended ADCx Clock Config
  * @{   
  */ 
/** @brief  Macro to configure the ADC1 clock (ADC1CLK).
  * @param  __ADC1CLKSource__: specifies the ADC1 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_ADC1PCLK2_DIV2: PCLK2 clock divided by 2 selected as ADC1 clock
  *            @arg RCC_ADC1PCLK2_DIV4: PCLK2 clock divided by 4 selected as ADC1 clock
  *            @arg RCC_ADC1PCLK2_DIV6: PCLK2 clock divided by 6 selected as ADC1 clock
  *            @arg RCC_ADC1PCLK2_DIV8: PCLK2 clock divided by 8 selected as ADC1 clock
  */
#define __HAL_RCC_ADC1_CONFIG(__ADC1CLKSource__) \
                  MODIFY_REG(RCC->CFGR, RCC_CFGR_ADCPRE, (uint32_t)(__ADC1CLKSource__))

/** @brief  Macro to get the ADC1 clock (ADC1CLK).
  * @retval The clock source can be one of the following values:
  *            @arg RCC_ADC1PCLK2_DIV2: PCLK2 clock divided by 2 selected as ADC1 clock
  *            @arg RCC_ADC1PCLK2_DIV4: PCLK2 clock divided by 4 selected as ADC1 clock
  *            @arg RCC_ADC1PCLK2_DIV6: PCLK2 clock divided by 6 selected as ADC1 clock
  *            @arg RCC_ADC1PCLK2_DIV8: PCLK2 clock divided by 8 selected as ADC1 clock
  */
#define __HAL_RCC_GET_ADC1_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_ADCPRE)))
/**
  * @}
  */

/** @defgroup RCCEx_SDADCx_Clock_Config RCC Extended SDADCx Clock Config
  * @{   
  */ 
/** @brief  Macro to configure the SDADCx clock (SDADCxCLK).
  * @param  __SDADCPrescaler__: specifies the SDADCx system clock prescaler.
  *         This parameter can be one of the following values:
  *            @arg RCC_SDADCSYSCLK_DIV1: SYSCLK clock selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV2: SYSCLK clock divided by 2 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV4: SYSCLK clock divided by 4 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV6: SYSCLK clock divided by 6 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV8: SYSCLK clock divided by 8 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV10: SYSCLK clock divided by 10 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV12: SYSCLK clock divided by 12 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV14: SYSCLK clock divided by 14 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV16: SYSCLK clock divided by 16 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV20: SYSCLK clock divided by 20 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV24: SYSCLK clock divided by 24 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV28: SYSCLK clock divided by 28 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV32: SYSCLK clock divided by 32 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV36: SYSCLK clock divided by 36 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV40: SYSCLK clock divided by 40 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV44: SYSCLK clock divided by 44 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV48: SYSCLK clock divided by 48 selected as SDADCx clock
  */
#define __HAL_RCC_SDADC_CONFIG(__SDADCPrescaler__) \
                  MODIFY_REG(RCC->CFGR, RCC_CFGR_SDADCPRE, (uint32_t)(__SDADCPrescaler__))

/** @brief  Macro to get the SDADCx clock prescaler.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SDADCSYSCLK_DIV1: SYSCLK clock selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV2: SYSCLK clock divided by 2 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV4: SYSCLK clock divided by 4 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV6: SYSCLK clock divided by 6 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV8: SYSCLK clock divided by 8 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV10: SYSCLK clock divided by 10 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV12: SYSCLK clock divided by 12 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV14: SYSCLK clock divided by 14 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV16: SYSCLK clock divided by 16 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV20: SYSCLK clock divided by 20 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV24: SYSCLK clock divided by 24 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV28: SYSCLK clock divided by 28 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV32: SYSCLK clock divided by 32 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV36: SYSCLK clock divided by 36 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV40: SYSCLK clock divided by 40 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV44: SYSCLK clock divided by 44 selected as SDADCx clock
  *            @arg RCC_SDADCSYSCLK_DIV48: SYSCLK clock divided by 48 selected as SDADCx clock
  */
#define __HAL_RCC_GET_SDADC_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_SDADCPRE)))
/**
  * @}
  */

/** @defgroup RCCEx_CECx_Clock_Config RCC Extended CECx Clock Config
  * @{   
  */ 
/** @brief  Macro to configure the CEC clock.
  * @param  __CECCLKSource__: specifies the CEC clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_CECCLKSOURCE_HSI: HSI selected as CEC clock
  *            @arg RCC_CECCLKSOURCE_LSE: LSE selected as CEC clock
  */
#define __HAL_RCC_CEC_CONFIG(__CECCLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_CECSW, (uint32_t)(__CECCLKSource__))

/** @brief  Macro to get the HDMI CEC clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_CECCLKSOURCE_HSI: HSI selected as CEC clock
  *            @arg RCC_CECCLKSOURCE_LSE: LSE selected as CEC clock
  */
#define __HAL_RCC_GET_CEC_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_CECSW)))
/**
  * @}
  */

#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || \
    defined(STM32F302xC) || defined(STM32F303xC) || \
    defined(STM32F302x8)                         || \
    defined(STM32F373xC)

/** @defgroup RCCEx_USBx_Clock_Config RCC Extended USBx Clock Config
  * @{   
  */ 
/** @brief  Macro to configure the USB clock (USBCLK).
  * @param  __USBCLKSource__: specifies the USB clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_USBPLLCLK_DIV1:  PLL Clock divided by 1 selected as USB clock
  *            @arg RCC_USBPLLCLK_DIV1_5: PLL Clock divided by 1.5 selected as USB clock
  */
#define __HAL_RCC_USB_CONFIG(__USBCLKSource__) \
                  MODIFY_REG(RCC->CFGR, RCC_CFGR_USBPRE, (uint32_t)(__USBCLKSource__))

/** @brief  Macro to get the USB clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_USBPLLCLK_DIV1:  PLL Clock divided by 1 selected as USB clock
  *            @arg RCC_USBPLLCLK_DIV1_5: PLL Clock divided by 1.5 selected as USB clock
  */
#define __HAL_RCC_GET_USB_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_USBPRE)))
/**
  * @}
  */

#endif /* STM32F302xE || STM32F303xE || */
       /* STM32F302xC || STM32F303xC || */
       /* STM32F302x8                || */
       /* STM32F373xC                   */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)

/** @defgroup RCCEx_MCOx_Clock_Config RCC Extended MCOx Clock Config
  * @{   
  */ 
/** @brief macro to configure the MCO clock.
  * @param  __MCOCLKSource__: specifies the MCO clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_MCOSOURCE_HSI: HSI selected as MCO clock
  *            @arg RCC_MCOSOURCE_HSE: HSE selected as MCO clock
  *            @arg RCC_MCOSOURCE_LSI: LSI selected as MCO clock
  *            @arg RCC_MCOSOURCE_LSE: LSE selected as MCO clock
  *            @arg RCC_MCOSOURCE_PLLCLK_DIV2: PLLCLK Divided by 2 selected as MCO clock
  *            @arg RCC_MCOSOURCE_SYSCLK: System Clock selected as MCO clock
  * @param  __MCODiv__: specifies the MCO clock prescaler.
  *          This parameter can be one of the following values:
  *            @arg RCC_MCO_NODIV: No division applied on MCO clock source
  */
#define __HAL_RCC_MCO_CONFIG(__MCOCLKSource__, __MCODiv__) \
                 MODIFY_REG(RCC->CFGR, (RCC_CFGR_MCO | RCC_CFGR_MCOPRE), ((__MCOCLKSource__) | (__MCODiv__)))
/**
  * @}
  */
#else
/** @defgroup RCCEx_MCOx_Clock_Config RCC Extended MCOx Clock Config
  * @{   
  */ 

#define __HAL_RCC_MCO_CONFIG(__MCOCLKSource__, __MCODiv__) \
                 MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO, (__MCOCLKSource__))
/**
  * @}
  */

#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx)

/** @defgroup RCCEx_I2Cx_Clock_Config RCC Extended I2Cx Clock Config
  * @{   
  */ 
/** @brief  Macro to configure the I2C3 clock (I2C3CLK).
  * @param  __I2C3CLKSource__: specifies the I2C3 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_I2C3CLKSOURCE_HSI: HSI selected as I2C3 clock
  *            @arg RCC_I2C3CLKSOURCE_SYSCLK: System Clock selected as I2C3 clock
  */
#define __HAL_RCC_I2C3_CONFIG(__I2C3CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_I2C3SW, (uint32_t)(__I2C3CLKSource__))

/** @brief  Macro to get the I2C3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_I2C3CLKSOURCE_HSI: HSI selected as I2C3 clock
  *            @arg RCC_I2C3CLKSOURCE_SYSCLK: System Clock selected as I2C3 clock
  */
#define __HAL_RCC_GET_I2C3_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_I2C3SW)))
/**
  * @}
  */

/** @defgroup RCCEx_TIMx_Clock_Config RCC Extended TIMx Clock Config
  * @{   
  */ 
/** @brief  Macro to configure the TIM2 clock (TIM2CLK).
  * @param  __TIM2CLKSource__: specifies the TIM2 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM2CLK_HCLK: HCLK selected as TIM2 clock
  *            @arg RCC_TIM2CLK_PLL: PLL Clock selected as TIM2 clock
  */
#define __HAL_RCC_TIM2_CONFIG(__TIM2CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_TIM2SW, (uint32_t)(__TIM2CLKSource__))

/** @brief  Macro to get the TIM2 clock (TIM2CLK).
  * @retval The clock source can be one of the following values:
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM2CLK_HCLK: HCLK selected as TIM2 clock
  *            @arg RCC_TIM2CLK_PLL: PLL Clock selected as TIM2 clock
  */
#define __HAL_RCC_GET_TIM2_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_TIM2SW)))
                    
/** @brief  Macro to configure the TIM3 & TIM4 clock (TIM34CLK).
  * @param  __TIM3CLKSource__: specifies the TIM3 & TIM4 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM34CLK_HCLK: HCLK selected as TIM3 & TIM4 clock
  *            @arg RCC_TIM34CLK_PLL: PLL Clock selected as TIM3 & TIM4 clock
  */
#define __HAL_RCC_TIM34_CONFIG(__TIM34CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_TIM34SW, (uint32_t)(__TIM34CLKSource__))

/** @brief  Macro to get the TIM3 & TIM4 clock (TIM34CLK).
  * @retval The clock source can be one of the following values:
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM34CLK_HCLK: HCLK selected as TIM3 & TIM4 clock
  *            @arg RCC_TIM34CLK_PLL: PLL Clock selected as TIM3 & TIM4 clock
  */
#define __HAL_RCC_GET_TIM34_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_TIM34SW)))

/** @brief  Macro to configure the TIM15 clock (TIM15CLK).
  * @param  __TIM15CLKSource__: specifies the TIM15 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM15CLK_HCLK: HCLK selected as TIM15 clock
  *            @arg RCC_TIM15CLK_PLL: PLL Clock selected as TIM15 clock
  */
#define __HAL_RCC_TIM15_CONFIG(__TIM15CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_TIM15SW, (uint32_t)(__TIM15CLKSource__))

/** @brief  Macro to get the TIM15 clock (TIM15CLK).
  * @retval The clock source can be one of the following values:
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM15CLK_HCLK: HCLK selected as TIM15 clock
  *            @arg RCC_TIM15CLK_PLL: PLL Clock selected as TIM15 clock
  */
#define __HAL_RCC_GET_TIM15_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_TIM15SW)))

/** @brief  Macro to configure the TIM16 clock (TIM16CLK).
  * @param  __TIM16CLKSource__: specifies the TIM16 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM16CLK_HCLK: HCLK selected as TIM16 clock
  *            @arg RCC_TIM16CLK_PLL: PLL Clock selected as TIM16 clock
  */
#define __HAL_RCC_TIM16_CONFIG(__TIM16CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_TIM16SW, (uint32_t)(__TIM16CLKSource__))

/** @brief  Macro to get the TIM16 clock (TIM16CLK).
  * @retval The clock source can be one of the following values:
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM16CLK_HCLK: HCLK selected as TIM16 clock
  *            @arg RCC_TIM16CLK_PLL: PLL Clock selected as TIM16 clock
  */
#define __HAL_RCC_GET_TIM16_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_TIM16SW)))
 
/** @brief  Macro to configure the TIM17 clock (TIM17CLK).
  * @param  __TIM17CLKSource__: specifies the TIM17 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM17CLK_HCLK: HCLK selected as TIM17 clock
  *            @arg RCC_TIM17CLK_PLL: PLL Clock selected as TIM17 clock
  */
#define __HAL_RCC_TIM17_CONFIG(__TIM17CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_TIM17SW, (uint32_t)(__TIM17CLKSource__))

/** @brief  Macro to get the TIM17 clock (TIM17CLK).
  * @retval The clock source can be one of the following values:
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM17CLK_HCLK: HCLK selected as TIM17 clock
  *            @arg RCC_TIM17CLK_PLL: PLL Clock selected as TIM17 clock
  */
#define __HAL_RCC_GET_TIM17_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_TIM17SW)))
                    
/**
  * @}
  */
                   
#endif /* STM32f302xE || STM32f303xE || STM32F398xx */
                    
#if defined(STM32F303xE) || defined(STM32F398xx)
/** @addtogroup RCCEx_TIMx_Clock_Config RCC Extended TIMx Clock Config 
  * @{
  */
/** @brief  Macro to configure the TIM20 clock (TIM20CLK).
  * @param  __TIM20CLKSource__: specifies the TIM20 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM20CLK_HCLK: HCLK selected as TIM20 clock
  *            @arg RCC_TIM20CLK_PLL: PLL Clock selected as TIM20 clock
  */
#define __HAL_RCC_TIM20_CONFIG(__TIM20CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_TIM20SW, (uint32_t)(__TIM20CLKSource__))

/** @brief  Macro to get the TIM20 clock (TIM20CLK).
  * @retval The clock source can be one of the following values:
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM20CLK_HCLK: HCLK selected as TIM20 clock
  *            @arg RCC_TIM20CLK_PLL: PLL Clock selected as TIM20 clock
  */
#define __HAL_RCC_GET_TIM20_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_TIM20SW)))

/**
  * @}
  */
#endif /* STM32f303xE || STM32F398xx */


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCCEx_Exported_Functions RCC Extended Exported Functions
  * @{
  */

/** @addtogroup RCCEx_Exported_Functions_Group1 Extended Peripheral Control functions 
  * @{
  */
HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
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

#endif /* __STM32F3xx_HAL_RCC_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
