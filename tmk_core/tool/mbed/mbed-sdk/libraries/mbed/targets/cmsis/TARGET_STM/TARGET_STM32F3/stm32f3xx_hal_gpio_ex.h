/**
  ******************************************************************************
  * @file    stm32f3xx_hal_gpio_ex.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   Header file of GPIO HAL Extended module.
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
#ifndef __STM32F3xx_HAL_GPIO_EX_H
#define __STM32F3xx_HAL_GPIO_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal_def.h"

/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

/** @addtogroup GPIOEx GPIO Extended HAL module driver
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup GPIOEx_Exported_Constants GPIO Extended Exported Constants
  * @{
  */ 
  
/** @defgroup GPIOEx_Alternate_function_selection GPIO Extended Alternate function selection
  * @{
  */
  
#if defined (STM32F302xC)
/*---------------------------------- STM32F302xC ------------------------------*/
/** 
  * @brief   AF 0 selection  
  */ 
#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)  /* RTC_50Hz Alternate Function mapping                       */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO (MCO1 and MCO2) Alternate Function mapping            */
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping             */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping                          */

/** 
  * @brief   AF 1 selection  
  */ 
#define GPIO_AF1_TIM2           ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */
#define GPIO_AF1_TIM15          ((uint8_t)0x01)  /* TIM15 Alternate Function mapping */
#define GPIO_AF1_TIM16          ((uint8_t)0x01)  /* TIM16 Alternate Function mapping */
#define GPIO_AF1_TIM17          ((uint8_t)0x01)  /* TIM17 Alternate Function mapping */
#define GPIO_AF1_EVENTOUT       ((uint8_t)0x01)  /* EVENTOUT Alternate Function mapping */
/** 
  * @brief   AF 2 selection  
  */ 
#define GPIO_AF2_TIM1           ((uint8_t)0x02)  /* TIM1 Alternate Function mapping */
#define GPIO_AF2_TIM2           ((uint8_t)0x02)  /* TIM2 Alternate Function mapping */
#define GPIO_AF2_TIM3           ((uint8_t)0x02)  /* TIM3 Alternate Function mapping */
#define GPIO_AF2_TIM4           ((uint8_t)0x02)  /* TIM4 Alternate Function mapping */
#define GPIO_AF2_TIM15          ((uint8_t)0x02)  /* TIM15 Alternate Function mapping */
#define GPIO_AF2_COMP1          ((uint8_t)0x02)  /* COMP1 Alternate Function mapping */
/** 
  * @brief   AF 3 selection  
  */ 
#define GPIO_AF3_TSC           ((uint8_t)0x03)  /* TSC Alternate Function mapping  */
#define GPIO_AF3_TIM15         ((uint8_t)0x03)  /* TIM15 Alternate Function mapping */

/** 
  * @brief   AF 4 selection  
  */ 
#define GPIO_AF4_TIM1          ((uint8_t)0x04)  /* TIM1 Alternate Function mapping */
#define GPIO_AF4_TIM16         ((uint8_t)0x04)  /* TIM16 Alternate Function mapping */
#define GPIO_AF4_TIM17         ((uint8_t)0x04)  /* TIM17 Alternate Function mapping */
#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping */
#define GPIO_AF4_I2C2          ((uint8_t)0x04)  /* I2C2 Alternate Function mapping */

/** 
  * @brief   AF 5 selection  
  */ 
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /* SPI1/I2S1 Alternate Function mapping */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF5_SPI3          ((uint8_t)0x05)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF5_I2S           ((uint8_t)0x05)  /* I2S Alternate Function mapping */
#define GPIO_AF5_I2S2ext       ((uint8_t)0x05)  /* I2S2ext Alternate Function mapping */
#define GPIO_AF5_IR            ((uint8_t)0x05)  /* IR Alternate Function mapping */
#define GPIO_AF5_UART4         ((uint8_t)0x05)  /* UART4 Alternate Function mapping */
#define GPIO_AF5_UART5         ((uint8_t)0x05)  /* UART5 Alternate Function mapping */
/** 
  * @brief   AF 6 selection  
  */ 
#define GPIO_AF6_SPI2          ((uint8_t)0x06)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF6_SPI3          ((uint8_t)0x06)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF6_I2S3ext       ((uint8_t)0x06)  /* I2S3ext Alternate Function mapping */
#define GPIO_AF6_TIM1          ((uint8_t)0x06)  /* TIM1 Alternate Function mapping */
#define GPIO_AF6_IR            ((uint8_t)0x06)  /* IR Alternate Function mapping */

/** 
  * @brief   AF 7 selection  
  */ 
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /* USART1 Alternate Function mapping  */
#define GPIO_AF7_USART2        ((uint8_t)0x07)  /* USART2 Alternate Function mapping  */
#define GPIO_AF7_USART3        ((uint8_t)0x07)  /* USART3 Alternate Function mapping  */
#define GPIO_AF7_COMP6         ((uint8_t)0x07)  /* COMP6 Alternate Function mapping  */
#define GPIO_AF7_CAN           ((uint8_t)0x07)  /* CAN Alternate Function mapping  */

/** 
  * @brief   AF 8 selection  
  */ 
#define GPIO_AF8_COMP1         ((uint8_t)0x08)  /* COMP1 Alternate Function mapping  */
#define GPIO_AF8_COMP2         ((uint8_t)0x08)  /* COMP2 Alternate Function mapping  */
#define GPIO_AF8_COMP4         ((uint8_t)0x08)  /* COMP4 Alternate Function mapping  */
#define GPIO_AF8_COMP6         ((uint8_t)0x08)  /* COMP6 Alternate Function mapping  */

/** 
  * @brief   AF 9 selection 
  */ 
#define GPIO_AF9_CAN           ((uint8_t)0x09)  /* CAN Alternate Function mapping  */
#define GPIO_AF9_TIM1          ((uint8_t)0x09)  /* TIM1 Alternate Function mapping */
#define GPIO_AF9_TIM15         ((uint8_t)0x09)  /* TIM15 Alternate Function mapping */

/** 
  * @brief   AF 10 selection  
  */ 
#define GPIO_AF10_TIM2           ((uint8_t)0xA)  /* TIM2 Alternate Function mapping */
#define GPIO_AF10_TIM3           ((uint8_t)0xA)  /* TIM3 Alternate Function mapping */
#define GPIO_AF10_TIM4           ((uint8_t)0xA)  /* TIM4 Alternate Function mapping */
#define GPIO_AF10_TIM17          ((uint8_t)0xA)  /* TIM17 Alternate Function mapping */
/** 
  * @brief   AF 11 selection  
  */ 
#define GPIO_AF11_TIM1           ((uint8_t)0x0B)  /* TIM1 Alternate Function mapping */

/** 
  * @brief   AF 12 selection  
  */ 
#define GPIO_AF12_TIM1            ((uint8_t)0xC)  /* TIM1 Alternate Function mapping */

/** 
  * @brief   AF 14 selection  
  */

#define GPIO_AF14_USB           ((uint8_t)0x0E)  /* USB Alternate Function mapping */
/** 
  * @brief   AF 15 selection  
  */ 
#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */

#define IS_GPIO_AF(AF)          (((AF) <= (uint8_t)0x0C) || ((AF) == (uint8_t)0x0E) || ((AF) == (uint8_t)0x0F))
/*------------------------------------------------------------------------------------------*/
#endif /* STM32F302xC */
   
#if defined (STM32F303xC)
/*---------------------------------- STM32F303xC ------------------------------*/
/** 
  * @brief   AF 0 selection  
  */ 
#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)  /* RTC_50Hz Alternate Function mapping                       */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO (MCO1 and MCO2) Alternate Function mapping            */
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping             */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping                          */

/** 
  * @brief   AF 1 selection  
  */ 
#define GPIO_AF1_TIM2           ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */
#define GPIO_AF1_TIM15          ((uint8_t)0x01)  /* TIM15 Alternate Function mapping */
#define GPIO_AF1_TIM16          ((uint8_t)0x01)  /* TIM16 Alternate Function mapping */
#define GPIO_AF1_TIM17          ((uint8_t)0x01)  /* TIM17 Alternate Function mapping */
#define GPIO_AF1_EVENTOUT       ((uint8_t)0x01)  /* EVENTOUT Alternate Function mapping */
/** 
  * @brief   AF 2 selection  
  */ 
#define GPIO_AF2_TIM1           ((uint8_t)0x02)  /* TIM1 Alternate Function mapping */
#define GPIO_AF2_TIM2           ((uint8_t)0x02)  /* TIM2 Alternate Function mapping */
#define GPIO_AF2_TIM3           ((uint8_t)0x02)  /* TIM3 Alternate Function mapping */
#define GPIO_AF2_TIM4           ((uint8_t)0x02)  /* TIM4 Alternate Function mapping */
#define GPIO_AF2_TIM8           ((uint8_t)0x02)  /* TIM8 Alternate Function mapping */
#define GPIO_AF2_TIM15          ((uint8_t)0x02)  /* TIM15 Alternate Function mapping */
#define GPIO_AF2_COMP1          ((uint8_t)0x02)  /* COMP1 Alternate Function mapping */
/** 
  * @brief   AF 3 selection  
  */ 
#define GPIO_AF3_TSC           ((uint8_t)0x03)  /* TSC Alternate Function mapping  */
#define GPIO_AF3_TIM8          ((uint8_t)0x03)  /* TIM8 Alternate Function mapping  */
#define GPIO_AF3_COMP7         ((uint8_t)0x03)  /* COMP7 Alternate Function mapping */
#define GPIO_AF3_TIM15         ((uint8_t)0x03)  /* TIM15 Alternate Function mapping */

/** 
  * @brief   AF 4 selection  
  */ 
#define GPIO_AF4_TIM1          ((uint8_t)0x04)  /* TIM1 Alternate Function mapping */
#define GPIO_AF4_TIM8          ((uint8_t)0x04)  /* TIM8 Alternate Function mapping */
#define GPIO_AF4_TIM16         ((uint8_t)0x04)  /* TIM16 Alternate Function mapping */
#define GPIO_AF4_TIM17         ((uint8_t)0x04)  /* TIM17 Alternate Function mapping */
#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping */
#define GPIO_AF4_I2C2          ((uint8_t)0x04)  /* I2C2 Alternate Function mapping */

/** 
  * @brief   AF 5 selection  
  */ 
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /* SPI1/I2S1 Alternate Function mapping */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF5_SPI3          ((uint8_t)0x05)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF5_I2S           ((uint8_t)0x05)  /* I2S Alternate Function mapping */
#define GPIO_AF5_I2S2ext       ((uint8_t)0x05)  /* I2S2ext Alternate Function mapping */
#define GPIO_AF5_TIM8          ((uint8_t)0x05)  /* TIM8 Alternate Function mapping */
#define GPIO_AF5_IR            ((uint8_t)0x05)  /* IR Alternate Function mapping */
#define GPIO_AF5_UART4         ((uint8_t)0x05)  /* UART4 Alternate Function mapping */
#define GPIO_AF5_UART5         ((uint8_t)0x05)  /* UART5 Alternate Function mapping */
/** 
  * @brief   AF 6 selection  
  */ 
#define GPIO_AF6_SPI2          ((uint8_t)0x06)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF6_SPI3          ((uint8_t)0x06)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF6_I2S3ext       ((uint8_t)0x06)  /* I2S3ext Alternate Function mapping */
#define GPIO_AF6_TIM1          ((uint8_t)0x06)  /* TIM1 Alternate Function mapping */
#define GPIO_AF6_TIM8          ((uint8_t)0x06)  /* TIM8 Alternate Function mapping */
#define GPIO_AF6_IR            ((uint8_t)0x06)  /* IR Alternate Function mapping */

/** 
  * @brief   AF 7 selection  
  */ 
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /* USART1 Alternate Function mapping  */
#define GPIO_AF7_USART2        ((uint8_t)0x07)  /* USART2 Alternate Function mapping  */
#define GPIO_AF7_USART3        ((uint8_t)0x07)  /* USART3 Alternate Function mapping  */
#define GPIO_AF7_COMP3         ((uint8_t)0x07)  /* COMP3 Alternate Function mapping  */
#define GPIO_AF7_COMP5         ((uint8_t)0x07)  /* COMP5 Alternate Function mapping  */
#define GPIO_AF7_COMP6         ((uint8_t)0x07)  /* COMP6 Alternate Function mapping  */
#define GPIO_AF7_CAN           ((uint8_t)0x07)  /* CAN Alternate Function mapping  */

/** 
  * @brief   AF 8 selection  
  */ 
#define GPIO_AF8_COMP1         ((uint8_t)0x08)  /* COMP1 Alternate Function mapping  */
#define GPIO_AF8_COMP2         ((uint8_t)0x08)  /* COMP2 Alternate Function mapping  */
#define GPIO_AF8_COMP3         ((uint8_t)0x08)  /* COMP3 Alternate Function mapping  */
#define GPIO_AF8_COMP4         ((uint8_t)0x08)  /* COMP4 Alternate Function mapping  */
#define GPIO_AF8_COMP5         ((uint8_t)0x08)  /* COMP5 Alternate Function mapping  */
#define GPIO_AF8_COMP6         ((uint8_t)0x08)  /* COMP6 Alternate Function mapping  */

/** 
  * @brief   AF 9 selection 
  */ 
#define GPIO_AF9_CAN           ((uint8_t)0x09)  /* CAN Alternate Function mapping  */
#define GPIO_AF9_TIM1          ((uint8_t)0x09)  /* TIM1 Alternate Function mapping */
#define GPIO_AF9_TIM8          ((uint8_t)0x09)  /* TIM8 Alternate Function mapping */
#define GPIO_AF9_TIM15         ((uint8_t)0x09)  /* TIM15 Alternate Function mapping */

/** 
  * @brief   AF 10 selection  
  */ 
#define GPIO_AF10_TIM2           ((uint8_t)0xA)  /* TIM2 Alternate Function mapping */
#define GPIO_AF10_TIM3           ((uint8_t)0xA)  /* TIM3 Alternate Function mapping */
#define GPIO_AF10_TIM4           ((uint8_t)0xA)  /* TIM4 Alternate Function mapping */
#define GPIO_AF10_TIM8           ((uint8_t)0xA)  /* TIM8 Alternate Function mapping */
#define GPIO_AF10_TIM17          ((uint8_t)0xA)  /* TIM17 Alternate Function mapping */
/** 
  * @brief   AF 11 selection  
  */ 
#define GPIO_AF11_TIM1           ((uint8_t)0x0B)  /* TIM1 Alternate Function mapping */
#define GPIO_AF11_TIM8           ((uint8_t)0x0B)  /* TIM8 Alternate Function mapping */

/** 
  * @brief   AF 12 selection  
  */ 
#define GPIO_AF12_TIM1            ((uint8_t)0xC)  /* TIM1 Alternate Function mapping */

/** 
  * @brief   AF 14 selection  
  */

#define GPIO_AF14_USB           ((uint8_t)0x0E)  /* USB Alternate Function mapping */
/** 
  * @brief   AF 15 selection  
  */ 
#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */

#define IS_GPIO_AF(AF)          (((AF) <= (uint8_t)0x0C) || ((AF) == (uint8_t)0x0E) || ((AF) == (uint8_t)0x0F))
/*------------------------------------------------------------------------------------------*/
#endif /* STM32F303xC */

#if defined (STM32F303xE)
/*---------------------------------- STM32F303xE ------------------------------*/
/** 
  * @brief   AF 0 selection  
  */ 
#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)  /* RTC_50Hz Alternate Function mapping                       */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO (MCO1 and MCO2) Alternate Function mapping            */
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping             */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping                          */

/** 
  * @brief   AF 1 selection  
  */ 
#define GPIO_AF1_TIM2           ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */
#define GPIO_AF1_TIM15          ((uint8_t)0x01)  /* TIM15 Alternate Function mapping */
#define GPIO_AF1_TIM16          ((uint8_t)0x01)  /* TIM16 Alternate Function mapping */
#define GPIO_AF1_TIM17          ((uint8_t)0x01)  /* TIM17 Alternate Function mapping */
#define GPIO_AF1_EVENTOUT       ((uint8_t)0x01)  /* EVENTOUT Alternate Function mapping */

/** 
  * @brief   AF 2 selection  
  */ 
#define GPIO_AF2_TIM1           ((uint8_t)0x02)  /* TIM1 Alternate Function mapping */
#define GPIO_AF2_TIM2           ((uint8_t)0x02)  /* TIM2 Alternate Function mapping */
#define GPIO_AF2_TIM3           ((uint8_t)0x02)  /* TIM3 Alternate Function mapping */
#define GPIO_AF2_TIM4           ((uint8_t)0x02)  /* TIM4 Alternate Function mapping */
#define GPIO_AF2_TIM8           ((uint8_t)0x02)  /* TIM8 Alternate Function mapping */
#define GPIO_AF2_TIM15          ((uint8_t)0x02)  /* TIM15 Alternate Function mapping */
#define GPIO_AF2_COMP1          ((uint8_t)0x02)  /* COMP1 Alternate Function mapping */
#define GPIO_AF2_I2C3           ((uint8_t)0x02)  /* I2C3 Alternate Function mapping */
#define GPIO_AF2_TIM20          ((uint8_t)0x02)  /* TIM20 Alternate Function mapping */

/** 
  * @brief   AF 3 selection  
  */ 
#define GPIO_AF3_TSC           ((uint8_t)0x03)  /* TSC Alternate Function mapping  */
#define GPIO_AF3_TIM8          ((uint8_t)0x03)  /* TIM8 Alternate Function mapping  */
#define GPIO_AF3_COMP7         ((uint8_t)0x03)  /* COMP7 Alternate Function mapping */
#define GPIO_AF3_TIM15         ((uint8_t)0x03)  /* TIM15 Alternate Function mapping */
#define GPIO_AF3_I2C3          ((uint8_t)0x03)  /* I2C3 Alternate Function mapping */
#define GPIO_AF3_TIM20         ((uint8_t)0x03)  /* TIM20 Alternate Function mapping */

/** 
  * @brief   AF 4 selection  
  */ 
#define GPIO_AF4_TIM1          ((uint8_t)0x04)  /* TIM1 Alternate Function mapping */
#define GPIO_AF4_TIM8          ((uint8_t)0x04)  /* TIM8 Alternate Function mapping */
#define GPIO_AF4_TIM16         ((uint8_t)0x04)  /* TIM16 Alternate Function mapping */
#define GPIO_AF4_TIM17         ((uint8_t)0x04)  /* TIM17 Alternate Function mapping */
#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping */
#define GPIO_AF4_I2C2          ((uint8_t)0x04)  /* I2C2 Alternate Function mapping */

/** 
  * @brief   AF 5 selection  
  */ 
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /* SPI1 Alternate Function mapping */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF5_SPI3          ((uint8_t)0x05)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF5_I2S           ((uint8_t)0x05)  /* I2S Alternate Function mapping */
#define GPIO_AF5_I2S2ext       ((uint8_t)0x05)  /* I2S2ext Alternate Function mapping */
#define GPIO_AF5_TIM8          ((uint8_t)0x05)  /* TIM8 Alternate Function mapping */
#define GPIO_AF5_IR            ((uint8_t)0x05)  /* IR Alternate Function mapping */
#define GPIO_AF5_UART4         ((uint8_t)0x05)  /* UART4 Alternate Function mapping */
#define GPIO_AF5_UART5         ((uint8_t)0x05)  /* UART5 Alternate Function mapping */
#define GPIO_AF5_SPI4          ((uint8_t)0x05)  /* SPI4 Alternate Function mapping */

/** 
  * @brief   AF 6 selection  
  */ 
#define GPIO_AF6_SPI2          ((uint8_t)0x06)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF6_SPI3          ((uint8_t)0x06)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF6_I2S3ext       ((uint8_t)0x06)  /* I2S3ext Alternate Function mapping */
#define GPIO_AF6_TIM1          ((uint8_t)0x06)  /* TIM1 Alternate Function mapping */
#define GPIO_AF6_TIM8          ((uint8_t)0x06)  /* TIM8 Alternate Function mapping */
#define GPIO_AF6_IR            ((uint8_t)0x06)  /* IR Alternate Function mapping */
#define GPIO_AF6_TIM20         ((uint8_t)0x06)  /* TIM20 Alternate Function mapping */

/** 
  * @brief   AF 7 selection  
  */ 
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /* USART1 Alternate Function mapping  */
#define GPIO_AF7_USART2        ((uint8_t)0x07)  /* USART2 Alternate Function mapping  */
#define GPIO_AF7_USART3        ((uint8_t)0x07)  /* USART3 Alternate Function mapping  */
#define GPIO_AF7_COMP3         ((uint8_t)0x07)  /* COMP3 Alternate Function mapping  */
#define GPIO_AF7_COMP5         ((uint8_t)0x07)  /* COMP5 Alternate Function mapping  */
#define GPIO_AF7_COMP6         ((uint8_t)0x07)  /* COMP6 Alternate Function mapping  */
#define GPIO_AF7_CAN           ((uint8_t)0x07)  /* CAN Alternate Function mapping  */

/** 
  * @brief   AF 8 selection  
  */ 
#define GPIO_AF8_COMP1         ((uint8_t)0x08)  /* COMP1 Alternate Function mapping  */
#define GPIO_AF8_COMP2         ((uint8_t)0x08)  /* COMP2 Alternate Function mapping  */
#define GPIO_AF8_COMP3         ((uint8_t)0x08)  /* COMP3 Alternate Function mapping  */
#define GPIO_AF8_COMP4         ((uint8_t)0x08)  /* COMP4 Alternate Function mapping  */
#define GPIO_AF8_COMP5         ((uint8_t)0x08)  /* COMP5 Alternate Function mapping  */
#define GPIO_AF8_COMP6         ((uint8_t)0x08)  /* COMP6 Alternate Function mapping  */
#define GPIO_AF8_I2C3          ((uint8_t)0x08)  /* I2C3 Alternate Function mapping */

/** 
  * @brief   AF 9 selection 
  */ 
#define GPIO_AF9_CAN           ((uint8_t)0x09)  /* CAN Alternate Function mapping  */
#define GPIO_AF9_TIM1          ((uint8_t)0x09)  /* TIM1 Alternate Function mapping */
#define GPIO_AF9_TIM8          ((uint8_t)0x09)  /* TIM8 Alternate Function mapping */
#define GPIO_AF9_TIM15         ((uint8_t)0x09)  /* TIM15 Alternate Function mapping */

/** 
  * @brief   AF 10 selection  
  */ 
#define GPIO_AF10_TIM2           ((uint8_t)0xA)  /* TIM2 Alternate Function mapping */
#define GPIO_AF10_TIM3           ((uint8_t)0xA)  /* TIM3 Alternate Function mapping */
#define GPIO_AF10_TIM4           ((uint8_t)0xA)  /* TIM4 Alternate Function mapping */
#define GPIO_AF10_TIM8           ((uint8_t)0xA)  /* TIM8 Alternate Function mapping */
#define GPIO_AF10_TIM17          ((uint8_t)0xA)  /* TIM17 Alternate Function mapping */
/** 
  * @brief   AF 11 selection  
  */ 
#define GPIO_AF11_TIM1           ((uint8_t)0x0B)  /* TIM1 Alternate Function mapping */
#define GPIO_AF11_TIM8           ((uint8_t)0x0B)  /* TIM8 Alternate Function mapping */

/** 
  * @brief   AF 12 selection  
  */ 
#define GPIO_AF12_TIM1            ((uint8_t)0xC)  /* TIM1 Alternate Function mapping */
#define GPIO_AF12_FMC             ((uint8_t)0xC)  /* FMC Alternate Function mapping                      */
#define GPIO_AF12_SDIO            ((uint8_t)0xC)  /* SDIO Alternate Function mapping                     */

/** 
  * @brief   AF 14 selection  
  */
#define GPIO_AF14_USB           ((uint8_t)0x0E)  /* USB Alternate Function mapping */

/** 
  * @brief   AF 15 selection  
  */ 
#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */

#define IS_GPIO_AF(AF)          (((AF) <= (uint8_t)0x0C) || ((AF) == (uint8_t)0x0E) || ((AF) == (uint8_t)0x0F))
/*------------------------------------------------------------------------------------------*/
#endif /* STM32F303xE */

#if defined (STM32F302xE)
/*---------------------------------- STM32F302xE ------------------------------*/
/** 
  * @brief   AF 0 selection  
  */ 
#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)  /* RTC_50Hz Alternate Function mapping                       */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO (MCO1 and MCO2) Alternate Function mapping            */
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping             */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping                          */

/** 
  * @brief   AF 1 selection  
  */ 
#define GPIO_AF1_TIM2           ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */
#define GPIO_AF1_TIM15          ((uint8_t)0x01)  /* TIM15 Alternate Function mapping */
#define GPIO_AF1_TIM16          ((uint8_t)0x01)  /* TIM16 Alternate Function mapping */
#define GPIO_AF1_TIM17          ((uint8_t)0x01)  /* TIM17 Alternate Function mapping */
#define GPIO_AF1_EVENTOUT       ((uint8_t)0x01)  /* EVENTOUT Alternate Function mapping */

/** 
  * @brief   AF 2 selection  
  */ 
#define GPIO_AF2_TIM1           ((uint8_t)0x02)  /* TIM1 Alternate Function mapping */
#define GPIO_AF2_TIM2           ((uint8_t)0x02)  /* TIM2 Alternate Function mapping */
#define GPIO_AF2_TIM3           ((uint8_t)0x02)  /* TIM3 Alternate Function mapping */
#define GPIO_AF2_TIM4           ((uint8_t)0x02)  /* TIM4 Alternate Function mapping */
#define GPIO_AF2_TIM15          ((uint8_t)0x02)  /* TIM15 Alternate Function mapping */
#define GPIO_AF2_COMP1          ((uint8_t)0x02)  /* COMP1 Alternate Function mapping */
#define GPIO_AF2_I2C3           ((uint8_t)0x02)  /* I2C3 Alternate Function mapping */

/** 
  * @brief   AF 3 selection  
  */ 
#define GPIO_AF3_TSC           ((uint8_t)0x03)  /* TSC Alternate Function mapping  */
#define GPIO_AF3_TIM15         ((uint8_t)0x03)  /* TIM15 Alternate Function mapping */
#define GPIO_AF3_I2C3          ((uint8_t)0x03)  /* I2C3 Alternate Function mapping */

/** 
  * @brief   AF 4 selection  
  */ 
#define GPIO_AF4_TIM1          ((uint8_t)0x04)  /* TIM1 Alternate Function mapping */
#define GPIO_AF4_TIM16         ((uint8_t)0x04)  /* TIM16 Alternate Function mapping */
#define GPIO_AF4_TIM17         ((uint8_t)0x04)  /* TIM17 Alternate Function mapping */
#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping */
#define GPIO_AF4_I2C2          ((uint8_t)0x04)  /* I2C2 Alternate Function mapping */

/** 
  * @brief   AF 5 selection  
  */ 
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /* SPI1 Alternate Function mapping */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF5_SPI3          ((uint8_t)0x05)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF5_I2S           ((uint8_t)0x05)  /* I2S Alternate Function mapping */
#define GPIO_AF5_I2S2ext       ((uint8_t)0x05)  /* I2S2ext Alternate Function mapping */
#define GPIO_AF5_IR            ((uint8_t)0x05)  /* IR Alternate Function mapping */
#define GPIO_AF5_UART4         ((uint8_t)0x05)  /* UART4 Alternate Function mapping */
#define GPIO_AF5_UART5         ((uint8_t)0x05)  /* UART5 Alternate Function mapping */
#define GPIO_AF5_SPI4          ((uint8_t)0x05)  /* SPI4 Alternate Function mapping */

/** 
  * @brief   AF 6 selection  
  */ 
#define GPIO_AF6_SPI2          ((uint8_t)0x06)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF6_SPI3          ((uint8_t)0x06)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF6_I2S3ext       ((uint8_t)0x06)  /* I2S3ext Alternate Function mapping */
#define GPIO_AF6_TIM1          ((uint8_t)0x06)  /* TIM1 Alternate Function mapping */
#define GPIO_AF6_IR            ((uint8_t)0x06)  /* IR Alternate Function mapping */

/** 
  * @brief   AF 7 selection  
  */ 
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /* USART1 Alternate Function mapping  */
#define GPIO_AF7_USART2        ((uint8_t)0x07)  /* USART2 Alternate Function mapping  */
#define GPIO_AF7_USART3        ((uint8_t)0x07)  /* USART3 Alternate Function mapping  */
#define GPIO_AF7_COMP6         ((uint8_t)0x07)  /* COMP6 Alternate Function mapping  */
#define GPIO_AF7_CAN           ((uint8_t)0x07)  /* CAN Alternate Function mapping  */

/** 
  * @brief   AF 8 selection  
  */ 
#define GPIO_AF8_COMP1         ((uint8_t)0x08)  /* COMP1 Alternate Function mapping  */
#define GPIO_AF8_COMP2         ((uint8_t)0x08)  /* COMP2 Alternate Function mapping  */
#define GPIO_AF8_COMP4         ((uint8_t)0x08)  /* COMP4 Alternate Function mapping  */
#define GPIO_AF8_COMP6         ((uint8_t)0x08)  /* COMP6 Alternate Function mapping  */
#define GPIO_AF8_I2C3          ((uint8_t)0x08)  /* I2C3 Alternate Function mapping */

/** 
  * @brief   AF 9 selection 
  */ 
#define GPIO_AF9_CAN           ((uint8_t)0x09)  /* CAN Alternate Function mapping  */
#define GPIO_AF9_TIM1          ((uint8_t)0x09)  /* TIM1 Alternate Function mapping */
#define GPIO_AF9_TIM15         ((uint8_t)0x09)  /* TIM15 Alternate Function mapping */

/** 
  * @brief   AF 10 selection  
  */ 
#define GPIO_AF10_TIM2           ((uint8_t)0xA)  /* TIM2 Alternate Function mapping */
#define GPIO_AF10_TIM3           ((uint8_t)0xA)  /* TIM3 Alternate Function mapping */
#define GPIO_AF10_TIM4           ((uint8_t)0xA)  /* TIM4 Alternate Function mapping */
#define GPIO_AF10_TIM17          ((uint8_t)0xA)  /* TIM17 Alternate Function mapping */
/** 
  * @brief   AF 11 selection  
  */ 
#define GPIO_AF11_TIM1           ((uint8_t)0x0B)  /* TIM1 Alternate Function mapping */

/** 
  * @brief   AF 12 selection  
  */ 
#define GPIO_AF12_TIM1            ((uint8_t)0xC)  /* TIM1 Alternate Function mapping */
#define GPIO_AF12_FMC             ((uint8_t)0xC)  /* FMC Alternate Function mapping                      */
#define GPIO_AF12_SDIO            ((uint8_t)0xC)  /* SDIO Alternate Function mapping                     */

/** 
  * @brief   AF 14 selection  
  */
#define GPIO_AF14_USB           ((uint8_t)0x0E)  /* USB Alternate Function mapping */

/** 
  * @brief   AF 15 selection  
  */ 
#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */

#define IS_GPIO_AF(AF)          (((AF) <= (uint8_t)0x0C) || ((AF) == (uint8_t)0x0E) || ((AF) == (uint8_t)0x0F))
/*------------------------------------------------------------------------------------------*/
#endif /* STM32F302xE */

#if defined (STM32F398xx)
/*---------------------------------- STM32F398xx ------------------------------*/
/** 
  * @brief   AF 0 selection  
  */ 
#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)  /* RTC_50Hz Alternate Function mapping                       */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO (MCO1 and MCO2) Alternate Function mapping            */
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping             */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping                          */

/** 
  * @brief   AF 1 selection  
  */ 
#define GPIO_AF1_TIM2           ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */
#define GPIO_AF1_TIM15          ((uint8_t)0x01)  /* TIM15 Alternate Function mapping */
#define GPIO_AF1_TIM16          ((uint8_t)0x01)  /* TIM16 Alternate Function mapping */
#define GPIO_AF1_TIM17          ((uint8_t)0x01)  /* TIM17 Alternate Function mapping */
#define GPIO_AF1_EVENTOUT       ((uint8_t)0x01)  /* EVENTOUT Alternate Function mapping */

/** 
  * @brief   AF 2 selection  
  */ 
#define GPIO_AF2_TIM1           ((uint8_t)0x02)  /* TIM1 Alternate Function mapping */
#define GPIO_AF2_TIM2           ((uint8_t)0x02)  /* TIM2 Alternate Function mapping */
#define GPIO_AF2_TIM3           ((uint8_t)0x02)  /* TIM3 Alternate Function mapping */
#define GPIO_AF2_TIM4           ((uint8_t)0x02)  /* TIM4 Alternate Function mapping */
#define GPIO_AF2_TIM8           ((uint8_t)0x02)  /* TIM8 Alternate Function mapping */
#define GPIO_AF2_TIM15          ((uint8_t)0x02)  /* TIM15 Alternate Function mapping */
#define GPIO_AF2_COMP1          ((uint8_t)0x02)  /* COMP1 Alternate Function mapping */
#define GPIO_AF2_I2C3           ((uint8_t)0x02)  /* I2C3 Alternate Function mapping */
#define GPIO_AF2_TIM20          ((uint8_t)0x02)  /* TIM20 Alternate Function mapping */

/** 
  * @brief   AF 3 selection  
  */ 
#define GPIO_AF3_TSC           ((uint8_t)0x03)  /* TSC Alternate Function mapping  */
#define GPIO_AF3_TIM8          ((uint8_t)0x03)  /* TIM8 Alternate Function mapping  */
#define GPIO_AF3_COMP7         ((uint8_t)0x03)  /* COMP7 Alternate Function mapping */
#define GPIO_AF3_TIM15         ((uint8_t)0x03)  /* TIM15 Alternate Function mapping */
#define GPIO_AF3_I2C3          ((uint8_t)0x03)  /* I2C3 Alternate Function mapping */
#define GPIO_AF3_TIM20         ((uint8_t)0x03)  /* TIM20 Alternate Function mapping */

/** 
  * @brief   AF 4 selection  
  */ 
#define GPIO_AF4_TIM1          ((uint8_t)0x04)  /* TIM1 Alternate Function mapping */
#define GPIO_AF4_TIM8          ((uint8_t)0x04)  /* TIM8 Alternate Function mapping */
#define GPIO_AF4_TIM16         ((uint8_t)0x04)  /* TIM16 Alternate Function mapping */
#define GPIO_AF4_TIM17         ((uint8_t)0x04)  /* TIM17 Alternate Function mapping */
#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping */
#define GPIO_AF4_I2C2          ((uint8_t)0x04)  /* I2C2 Alternate Function mapping */

/** 
  * @brief   AF 5 selection  
  */ 
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /* SPI1 Alternate Function mapping */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF5_SPI3          ((uint8_t)0x05)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF5_I2S           ((uint8_t)0x05)  /* I2S Alternate Function mapping */
#define GPIO_AF5_I2S2ext       ((uint8_t)0x05)  /* I2S2ext Alternate Function mapping */
#define GPIO_AF5_TIM8          ((uint8_t)0x05)  /* TIM8 Alternate Function mapping */
#define GPIO_AF5_IR            ((uint8_t)0x05)  /* IR Alternate Function mapping */
#define GPIO_AF5_UART4         ((uint8_t)0x05)  /* UART4 Alternate Function mapping */
#define GPIO_AF5_UART5         ((uint8_t)0x05)  /* UART5 Alternate Function mapping */
#define GPIO_AF5_SPI4          ((uint8_t)0x05)  /* SPI4 Alternate Function mapping */

/** 
  * @brief   AF 6 selection  
  */ 
#define GPIO_AF6_SPI2          ((uint8_t)0x06)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF6_SPI3          ((uint8_t)0x06)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF6_I2S3ext       ((uint8_t)0x06)  /* I2S3ext Alternate Function mapping */
#define GPIO_AF6_TIM1          ((uint8_t)0x06)  /* TIM1 Alternate Function mapping */
#define GPIO_AF6_TIM8          ((uint8_t)0x06)  /* TIM8 Alternate Function mapping */
#define GPIO_AF6_IR            ((uint8_t)0x06)  /* IR Alternate Function mapping */
#define GPIO_AF6_TIM20         ((uint8_t)0x06)  /* TIM20 Alternate Function mapping */

/** 
  * @brief   AF 7 selection  
  */ 
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /* USART1 Alternate Function mapping  */
#define GPIO_AF7_USART2        ((uint8_t)0x07)  /* USART2 Alternate Function mapping  */
#define GPIO_AF7_USART3        ((uint8_t)0x07)  /* USART3 Alternate Function mapping  */
#define GPIO_AF7_COMP3         ((uint8_t)0x07)  /* COMP3 Alternate Function mapping  */
#define GPIO_AF7_COMP5         ((uint8_t)0x07)  /* COMP5 Alternate Function mapping  */
#define GPIO_AF7_COMP6         ((uint8_t)0x07)  /* COMP6 Alternate Function mapping  */
#define GPIO_AF7_CAN           ((uint8_t)0x07)  /* CAN Alternate Function mapping  */

/** 
  * @brief   AF 8 selection  
  */ 
#define GPIO_AF8_COMP1         ((uint8_t)0x08)  /* COMP1 Alternate Function mapping  */
#define GPIO_AF8_COMP2         ((uint8_t)0x08)  /* COMP2 Alternate Function mapping  */
#define GPIO_AF8_COMP3         ((uint8_t)0x08)  /* COMP3 Alternate Function mapping  */
#define GPIO_AF8_COMP4         ((uint8_t)0x08)  /* COMP4 Alternate Function mapping  */
#define GPIO_AF8_COMP5         ((uint8_t)0x08)  /* COMP5 Alternate Function mapping  */
#define GPIO_AF8_COMP6         ((uint8_t)0x08)  /* COMP6 Alternate Function mapping  */
#define GPIO_AF8_I2C3          ((uint8_t)0x08)  /* I2C3 Alternate Function mapping */

/** 
  * @brief   AF 9 selection 
  */ 
#define GPIO_AF9_CAN           ((uint8_t)0x09)  /* CAN Alternate Function mapping  */
#define GPIO_AF9_TIM1          ((uint8_t)0x09)  /* TIM1 Alternate Function mapping */
#define GPIO_AF9_TIM8          ((uint8_t)0x09)  /* TIM8 Alternate Function mapping */
#define GPIO_AF9_TIM15         ((uint8_t)0x09)  /* TIM15 Alternate Function mapping */

/** 
  * @brief   AF 10 selection  
  */ 
#define GPIO_AF10_TIM2           ((uint8_t)0xA)  /* TIM2 Alternate Function mapping */
#define GPIO_AF10_TIM3           ((uint8_t)0xA)  /* TIM3 Alternate Function mapping */
#define GPIO_AF10_TIM4           ((uint8_t)0xA)  /* TIM4 Alternate Function mapping */
#define GPIO_AF10_TIM8           ((uint8_t)0xA)  /* TIM8 Alternate Function mapping */
#define GPIO_AF10_TIM17          ((uint8_t)0xA)  /* TIM17 Alternate Function mapping */
/** 
  * @brief   AF 11 selection  
  */ 
#define GPIO_AF11_TIM1           ((uint8_t)0x0B)  /* TIM1 Alternate Function mapping */
#define GPIO_AF11_TIM8           ((uint8_t)0x0B)  /* TIM8 Alternate Function mapping */

/** 
  * @brief   AF 12 selection  
  */ 
#define GPIO_AF12_TIM1            ((uint8_t)0xC)  /* TIM1 Alternate Function mapping */
#define GPIO_AF12_FMC             ((uint8_t)0xC)  /* FMC Alternate Function mapping                      */
#define GPIO_AF12_SDIO            ((uint8_t)0xC)  /* SDIO Alternate Function mapping                     */

/** 
  * @brief   AF 15 selection  
  */ 
#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */

#define IS_GPIO_AF(AF)          (((AF) <= (uint8_t)0x0C) || ((AF) == (uint8_t)0x0F))
/*------------------------------------------------------------------------------------------*/
#endif /* STM32F398xx */

#if defined (STM32F358xx)
/*---------------------------------- STM32F358xx -------------------------------------------*/
/** 
  * @brief   AF 0 selection  
  */ 
#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)  /* RTC_50Hz Alternate Function mapping                       */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO (MCO1 and MCO2) Alternate Function mapping            */
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping             */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping                          */

/** 
  * @brief   AF 1 selection  
  */ 
#define GPIO_AF1_TIM2           ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */
#define GPIO_AF1_TIM15          ((uint8_t)0x01)  /* TIM15 Alternate Function mapping */
#define GPIO_AF1_TIM16          ((uint8_t)0x01)  /* TIM16 Alternate Function mapping */
#define GPIO_AF1_TIM17          ((uint8_t)0x01)  /* TIM17 Alternate Function mapping */
#define GPIO_AF1_EVENTOUT       ((uint8_t)0x01)  /* EVENTOUT Alternate Function mapping */
/** 
  * @brief   AF 2 selection  
  */ 
#define GPIO_AF2_TIM1           ((uint8_t)0x02)  /* TIM1 Alternate Function mapping */
#define GPIO_AF2_TIM2           ((uint8_t)0x02)  /* TIM2 Alternate Function mapping */
#define GPIO_AF2_TIM3           ((uint8_t)0x02)  /* TIM3 Alternate Function mapping */
#define GPIO_AF2_TIM4           ((uint8_t)0x02)  /* TIM4 Alternate Function mapping */
#define GPIO_AF2_TIM8           ((uint8_t)0x02)  /* TIM8 Alternate Function mapping */
#define GPIO_AF2_TIM15          ((uint8_t)0x02)  /* TIM15 Alternate Function mapping */
#define GPIO_AF2_COMP1          ((uint8_t)0x02)  /* COMP1 Alternate Function mapping */
/** 
  * @brief   AF 3 selection  
  */ 
#define GPIO_AF3_TSC           ((uint8_t)0x03)  /* TSC Alternate Function mapping  */
#define GPIO_AF3_TIM8          ((uint8_t)0x03)  /* TIM8 Alternate Function mapping  */
#define GPIO_AF3_COMP7         ((uint8_t)0x03)  /* COMP7 Alternate Function mapping */
#define GPIO_AF3_TIM15         ((uint8_t)0x03)  /* TIM15 Alternate Function mapping */

/** 
  * @brief   AF 4 selection  
  */ 
#define GPIO_AF4_TIM1          ((uint8_t)0x04)  /* TIM1 Alternate Function mapping */
#define GPIO_AF4_TIM8          ((uint8_t)0x04)  /* TIM8 Alternate Function mapping */
#define GPIO_AF4_TIM16         ((uint8_t)0x04)  /* TIM16 Alternate Function mapping */
#define GPIO_AF4_TIM17         ((uint8_t)0x04)  /* TIM17 Alternate Function mapping */
#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping */
#define GPIO_AF4_I2C2          ((uint8_t)0x04)  /* I2C2 Alternate Function mapping */

/** 
  * @brief   AF 5 selection  
  */ 
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /* SPI1/I2S1 Alternate Function mapping      */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF5_SPI3          ((uint8_t)0x05)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF5_I2S           ((uint8_t)0x05)  /* I2S Alternate Function mapping */
#define GPIO_AF5_I2S2ext       ((uint8_t)0x05)  /* I2S2ext Alternate Function mapping */
#define GPIO_AF5_TIM8          ((uint8_t)0x05)  /* TIM8 Alternate Function mapping */
#define GPIO_AF5_IR            ((uint8_t)0x05)  /* IR Alternate Function mapping */
#define GPIO_AF5_UART4         ((uint8_t)0x05)  /* UART4 Alternate Function mapping */
#define GPIO_AF5_UART5         ((uint8_t)0x05)  /* UART5 Alternate Function mapping */
/** 
  * @brief   AF 6 selection  
  */ 
#define GPIO_AF6_SPI2          ((uint8_t)0x06)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF6_SPI3          ((uint8_t)0x06)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF6_I2S3ext       ((uint8_t)0x06)  /* I2S3ext Alternate Function mapping */
#define GPIO_AF6_TIM1          ((uint8_t)0x06)  /* TIM1 Alternate Function mapping */
#define GPIO_AF6_TIM8          ((uint8_t)0x06)  /* TIM8 Alternate Function mapping */
#define GPIO_AF6_IR            ((uint8_t)0x06)  /* IR Alternate Function mapping */

/** 
  * @brief   AF 7 selection  
  */ 
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /* USART1 Alternate Function mapping  */
#define GPIO_AF7_USART2        ((uint8_t)0x07)  /* USART2 Alternate Function mapping  */
#define GPIO_AF7_USART3        ((uint8_t)0x07)  /* USART3 Alternate Function mapping  */
#define GPIO_AF7_COMP3         ((uint8_t)0x07)  /* COMP3 Alternate Function mapping  */
#define GPIO_AF7_COMP5         ((uint8_t)0x07)  /* COMP5 Alternate Function mapping  */
#define GPIO_AF7_COMP6         ((uint8_t)0x07)  /* COMP6 Alternate Function mapping  */
#define GPIO_AF7_CAN           ((uint8_t)0x07)  /* CAN Alternate Function mapping  */

/** 
  * @brief   AF 8 selection  
  */ 
#define GPIO_AF8_COMP1         ((uint8_t)0x08)  /* COMP1 Alternate Function mapping  */
#define GPIO_AF8_COMP2         ((uint8_t)0x08)  /* COMP2 Alternate Function mapping  */
#define GPIO_AF8_COMP3         ((uint8_t)0x08)  /* COMP3 Alternate Function mapping  */
#define GPIO_AF8_COMP4         ((uint8_t)0x08)  /* COMP4 Alternate Function mapping  */
#define GPIO_AF8_COMP5         ((uint8_t)0x08)  /* COMP5 Alternate Function mapping  */
#define GPIO_AF8_COMP6         ((uint8_t)0x08)  /* COMP6 Alternate Function mapping  */

/** 
  * @brief   AF 9 selection 
  */ 
#define GPIO_AF9_CAN           ((uint8_t)0x09)  /* CAN Alternate Function mapping  */
#define GPIO_AF9_TIM1          ((uint8_t)0x09)  /* TIM1 Alternate Function mapping */
#define GPIO_AF9_TIM8          ((uint8_t)0x09)  /* TIM8 Alternate Function mapping */
#define GPIO_AF9_TIM15         ((uint8_t)0x09)  /* TIM15 Alternate Function mapping */

/** 
  * @brief   AF 10 selection  
  */ 
#define GPIO_AF10_TIM2           ((uint8_t)0xA)  /* TIM2 Alternate Function mapping */
#define GPIO_AF10_TIM3           ((uint8_t)0xA)  /* TIM3 Alternate Function mapping */
#define GPIO_AF10_TIM4           ((uint8_t)0xA)  /* TIM4 Alternate Function mapping */
#define GPIO_AF10_TIM8           ((uint8_t)0xA)  /* TIM8 Alternate Function mapping */
#define GPIO_AF10_TIM17          ((uint8_t)0xA)  /* TIM17 Alternate Function mapping */
/** 
  * @brief   AF 11 selection  
  */ 
#define GPIO_AF11_TIM1           ((uint8_t)0x0B)  /* TIM1 Alternate Function mapping */
#define GPIO_AF11_TIM8           ((uint8_t)0x0B)  /* TIM8 Alternate Function mapping */

/** 
  * @brief   AF 12 selection  
  */ 
#define GPIO_AF12_TIM1            ((uint8_t)0xC)  /* TIM1 Alternate Function mapping */

/** 
  * @brief   AF 15 selection  
  */ 
#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */

#define IS_GPIO_AF(AF)          (((AF) <= (uint8_t)0x0C) || ((AF) == (uint8_t)0x0F))
/*------------------------------------------------------------------------------------------*/
#endif /* STM32F358xx */

#if  defined (STM32F373xC)
/*---------------------------------- STM32F373xC--------------------------------*/
/** 
  * @brief   AF 0 selection  
  */ 
#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)  /* RTC_50Hz Alternate Function mapping                       */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO (MCO1 and MCO2) Alternate Function mapping            */
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping             */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping                          */

/** 
  * @brief   AF 1 selection  
  */ 
#define GPIO_AF1_TIM2           ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */
#define GPIO_AF1_TIM15          ((uint8_t)0x01)  /* TIM15 Alternate Function mapping */
#define GPIO_AF1_TIM16          ((uint8_t)0x01)  /* TIM16 Alternate Function mapping */
#define GPIO_AF1_TIM17          ((uint8_t)0x01)  /* TIM17 Alternate Function mapping */
#define GPIO_AF1_EVENTOUT       ((uint8_t)0x01)  /* EVENTOUT Alternate Function mapping */
/** 
  * @brief   AF 2 selection  
  */ 
#define GPIO_AF2_TIM3           ((uint8_t)0x02)  /* TIM3 Alternate Function mapping */
#define GPIO_AF2_TIM4           ((uint8_t)0x02)  /* TIM4 Alternate Function mapping */
#define GPIO_AF2_TIM5           ((uint8_t)0x02)  /* TIM5 Alternate Function mapping */
#define GPIO_AF2_TIM13          ((uint8_t)0x02)  /* TIM13 Alternate Function mapping */
#define GPIO_AF2_TIM14          ((uint8_t)0x02)  /* TIM14 Alternate Function mapping */
#define GPIO_AF2_TIM15          ((uint8_t)0x02)  /* TIM15 Alternate Function mapping */
#define GPIO_AF2_TIM19          ((uint8_t)0x02)  /* TIM19 Alternate Function mapping */

/** 
  * @brief   AF 3 selection  
  */ 
#define GPIO_AF3_TSC           ((uint8_t)0x03)  /* TSC Alternate Function mapping  */
/** 
  * @brief   AF 4 selection  
  */ 
#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping */
#define GPIO_AF4_I2C2          ((uint8_t)0x04)  /* I2C2 Alternate Function mapping */

/** 
  * @brief   AF 5 selection  
  */ 
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /* SPI1/I2S1 Alternate Function mapping */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF5_IR            ((uint8_t)0x05)  /* IR Alternate Function mapping */
/** 
  * @brief   AF 6 selection  
  */ 
#define GPIO_AF6_SPI1          ((uint8_t)0x06)  /* SPI1/I2S1 Alternate Function mapping */
#define GPIO_AF6_SPI3          ((uint8_t)0x06)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF6_IR            ((uint8_t)0x06)  /* IR Alternate Function mapping */
#define GPIO_AF6_CEC           ((uint8_t)0x06)  /* CEC Alternate Function mapping */
/** 
  * @brief   AF 7 selection  
  */ 
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /* USART1 Alternate Function mapping  */
#define GPIO_AF7_USART2        ((uint8_t)0x07)  /* USART2 Alternate Function mapping  */
#define GPIO_AF7_USART3        ((uint8_t)0x07)  /* USART3 Alternate Function mapping  */
#define GPIO_AF7_CAN           ((uint8_t)0x07)  /* CAN Alternate Function mapping  */
#define GPIO_AF7_CEC           ((uint8_t)0x07)  /* CEC Alternate Function mapping  */

/** 
  * @brief   AF 8 selection  
  */ 
#define GPIO_AF8_COMP1         ((uint8_t)0x08)  /* COMP1 Alternate Function mapping  */
#define GPIO_AF8_COMP2         ((uint8_t)0x08)  /* COMP2 Alternate Function mapping  */

/** 
  * @brief   AF 9 selection 
  */ 
#define GPIO_AF9_CAN           ((uint8_t)0x09)  /* CAN Alternate Function mapping  */
#define GPIO_AF9_TIM12         ((uint8_t)0x09)  /* TIM12 Alternate Function mapping */
#define GPIO_AF9_TIM13         ((uint8_t)0x09)  /* TIM13 Alternate Function mapping */
#define GPIO_AF9_TIM14         ((uint8_t)0x09)  /* TIM14 Alternate Function mapping */
#define GPIO_AF9_TIM15         ((uint8_t)0x09)  /* TIM15 Alternate Function mapping */
/** 
  * @brief   AF 10 selection  
  */ 
#define GPIO_AF10_TIM2           ((uint8_t)0xA)  /* TIM2 Alternate Function mapping */
#define GPIO_AF10_TIM3           ((uint8_t)0xA)  /* TIM3 Alternate Function mapping */
#define GPIO_AF10_TIM4           ((uint8_t)0xA)  /* TIM4 Alternate Function mapping */
#define GPIO_AF10_TIM12          ((uint8_t)0xA)  /* TIM12 Alternate Function mapping */
#define GPIO_AF10_TIM17          ((uint8_t)0xA)  /* TIM17 Alternate Function mapping */
/** 
  * @brief   AF 11 selection  
  */ 
#define GPIO_AF11_TIM19          ((uint8_t)0x0B)  /* TIM19 Alternate Function mapping */


/** 
  * @brief   AF 14 selection  
  */ 
#define GPIO_AF14_USB           ((uint8_t)0x0E)  /* USB Alternate Function mapping */

/** 
  * @brief   AF 15 selection  
  */ 
#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */

#define IS_GPIO_AF(AF)          (((AF) <= (uint8_t)0x0B) || ((AF) == (uint8_t)0x0E) || ((AF) == (uint8_t)0x0F))
/*------------------------------------------------------------------------------------------*/
#endif /* STM32F373xC */


#if defined (STM32F378xx)
/*---------------------------------------- STM32F378xx--------------------------------------*/
/** 
  * @brief   AF 0 selection  
  */ 
#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)  /* RTC_50Hz Alternate Function mapping                       */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO (MCO1 and MCO2) Alternate Function mapping            */
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping             */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping                          */

/** 
  * @brief   AF 1 selection  
  */ 
#define GPIO_AF1_TIM2           ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */
#define GPIO_AF1_TIM15          ((uint8_t)0x01)  /* TIM15 Alternate Function mapping */
#define GPIO_AF1_TIM16          ((uint8_t)0x01)  /* TIM16 Alternate Function mapping */
#define GPIO_AF1_TIM17          ((uint8_t)0x01)  /* TIM17 Alternate Function mapping */
#define GPIO_AF1_EVENTOUT       ((uint8_t)0x01)  /* EVENTOUT Alternate Function mapping */
/** 
  * @brief   AF 2 selection  
  */ 
#define GPIO_AF2_TIM3           ((uint8_t)0x02)  /* TIM3 Alternate Function mapping */
#define GPIO_AF2_TIM4           ((uint8_t)0x02)  /* TIM4 Alternate Function mapping */
#define GPIO_AF2_TIM5           ((uint8_t)0x02)  /* TIM5 Alternate Function mapping */
#define GPIO_AF2_TIM13          ((uint8_t)0x02)  /* TIM13 Alternate Function mapping */
#define GPIO_AF2_TIM14          ((uint8_t)0x02)  /* TIM14 Alternate Function mapping */
#define GPIO_AF2_TIM15          ((uint8_t)0x02)  /* TIM15 Alternate Function mapping */
#define GPIO_AF2_TIM19          ((uint8_t)0x02)  /* TIM19 Alternate Function mapping */

/** 
  * @brief   AF 3 selection  
  */ 
#define GPIO_AF3_TSC           ((uint8_t)0x03)  /* TSC Alternate Function mapping  */
/** 
  * @brief   AF 4 selection  
  */ 
#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping */
#define GPIO_AF4_I2C2          ((uint8_t)0x04)  /* I2C2 Alternate Function mapping */

/** 
  * @brief   AF 5 selection  
  */ 
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /* SPI1/I2S1 Alternate Function mapping */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF5_IR            ((uint8_t)0x05)  /* IR Alternate Function mapping */

/** 
  * @brief   AF 6 selection  
  */ 
#define GPIO_AF6_SPI1          ((uint8_t)0x06)  /* SPI1/I2S1 Alternate Function mapping */
#define GPIO_AF6_SPI3          ((uint8_t)0x06)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF6_IR            ((uint8_t)0x06)  /* IR Alternate Function mapping */
#define GPIO_AF6_CEC           ((uint8_t)0x06)  /* CEC Alternate Function mapping */

/** 
  * @brief   AF 7 selection  
  */ 
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /* USART1 Alternate Function mapping  */
#define GPIO_AF7_USART2        ((uint8_t)0x07)  /* USART2 Alternate Function mapping  */
#define GPIO_AF7_USART3        ((uint8_t)0x07)  /* USART3 Alternate Function mapping  */
#define GPIO_AF7_CAN           ((uint8_t)0x07)  /* CAN Alternate Function mapping  */
#define GPIO_AF7_CEC           ((uint8_t)0x07)  /* CEC Alternate Function mapping  */

/** 
  * @brief   AF 8 selection  
  */ 
#define GPIO_AF8_COMP1         ((uint8_t)0x08)  /* COMP1 Alternate Function mapping  */
#define GPIO_AF8_COMP2         ((uint8_t)0x08)  /* COMP2 Alternate Function mapping  */

/** 
  * @brief   AF 9 selection  
  */
#define GPIO_AF9_CAN           ((uint8_t)0x09)  /* CAN Alternate Function mapping  */
#define GPIO_AF9_TIM12         ((uint8_t)0x09)  /* TIM12 Alternate Function mapping */
#define GPIO_AF9_TIM13         ((uint8_t)0x09)  /* TIM13 Alternate Function mapping */
#define GPIO_AF9_TIM14         ((uint8_t)0x09)  /* TIM14 Alternate Function mapping */
#define GPIO_AF9_TIM15         ((uint8_t)0x09)  /* TIM15 Alternate Function mapping */

/** 
  * @brief   AF 10 selection  
  */ 
#define GPIO_AF10_TIM2           ((uint8_t)0xA)  /* TIM2 Alternate Function mapping */
#define GPIO_AF10_TIM3           ((uint8_t)0xA)  /* TIM3 Alternate Function mapping */
#define GPIO_AF10_TIM4           ((uint8_t)0xA)  /* TIM4 Alternate Function mapping */
#define GPIO_AF10_TIM12          ((uint8_t)0xA)  /* TIM12 Alternate Function mapping */
#define GPIO_AF10_TIM17          ((uint8_t)0xA)  /* TIM17 Alternate Function mapping */

/** 
  * @brief   AF 11 selection  
  */ 
#define GPIO_AF11_TIM19          ((uint8_t)0x0B)  /* TIM19 Alternate Function mapping */

/** 
  * @brief   AF 15 selection  
  */ 
#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */

#define IS_GPIO_AF(AF)          (((AF) <= (uint8_t)0x0B) || ((AF) == (uint8_t)0x0F))
/*------------------------------------------------------------------------------------------*/
#endif /* STM32F378xx */

#if defined (STM32F303x8)
/*---------------------------------- STM32F303x8--------------------------------*/
/** 
  * @brief   AF 0 selection  
  */ 
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO (MCO1 and MCO2) Alternate Function mapping            */
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping             */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping                          */

/** 
  * @brief   AF 1 selection  
  */ 
#define GPIO_AF1_TIM2           ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */
#define GPIO_AF1_TIM15          ((uint8_t)0x01)  /* TIM15 Alternate Function mapping */
#define GPIO_AF1_TIM16          ((uint8_t)0x01)  /* TIM16 Alternate Function mapping */
#define GPIO_AF1_TIM17          ((uint8_t)0x01)  /* TIM17 Alternate Function mapping */
#define GPIO_AF1_EVENTOUT       ((uint8_t)0x01)  /* EVENTOUT Alternate Function mapping */
/** 
  * @brief   AF 2 selection  
  */ 
#define GPIO_AF2_TIM3           ((uint8_t)0x02)  /* TIM3 Alternate Function mapping */
#define GPIO_AF2_TIM1           ((uint8_t)0x02)  /* TIM1 Alternate Function mapping */
#define GPIO_AF2_TIM15          ((uint8_t)0x02)  /* TIM15 Alternate Function mapping */
#define GPIO_AF2_TIM16          ((uint8_t)0x02)  /* TIM16 Alternate Function mapping */

/** 
  * @brief   AF 3 selection  
  */ 
#define GPIO_AF3_TSC           ((uint8_t)0x03)  /* TSC Alternate Function mapping  */

/** 
  * @brief   AF 4 selection  
  */ 
#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping */
#define GPIO_AF4_TIM1          ((uint8_t)0x04)  /* TIM1 Alternate Function mapping */

/** 
  * @brief   AF 5 selection  
  */ 
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /* SPI1 Alternate Function mapping */
#define GPIO_AF5_IR            ((uint8_t)0x05)  /* IR Alternate Function mapping */
/** 
  * @brief   AF 6 selection  
  */ 
#define GPIO_AF6_TIM1          ((uint8_t)0x06)  /* TIM1 Alternate Function mapping */
#define GPIO_AF6_IR            ((uint8_t)0x06)  /* IR Alternate Function mapping */

/** 
  * @brief   AF 7 selection  
  */ 
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /* USART1 Alternate Function mapping  */
#define GPIO_AF7_USART2        ((uint8_t)0x07)  /* USART2 Alternate Function mapping  */
#define GPIO_AF7_USART3        ((uint8_t)0x07)  /* USART3 Alternate Function mapping  */
#define GPIO_AF7_GPCOMP6       ((uint8_t)0x07)  /* GPCOMP6 Alternate Function mapping  */

/** 
  * @brief   AF 8 selection  
  */ 
#define GPIO_AF8_GPCOMP2         ((uint8_t)0x08)  /* GPCOMP2 Alternate Function mapping  */
#define GPIO_AF8_GPCOMP4         ((uint8_t)0x08)  /* GPCOMP4 Alternate Function mapping  */
#define GPIO_AF8_GPCOMP6         ((uint8_t)0x08)  /* GPCOMP6 Alternate Function mapping  */

/** 
  * @brief   AF 9 selection 
  */ 
#define GPIO_AF9_CAN           ((uint8_t)0x09)  /* CAN Alternate Function mapping  */
#define GPIO_AF9_TIM1          ((uint8_t)0x09)  /* TIM1 Alternate Function mapping */
#define GPIO_AF9_TIM15         ((uint8_t)0x09)  /* TIM15 Alternate Function mapping */
/** 
  * @brief   AF 10 selection  
  */ 
#define GPIO_AF10_TIM2           ((uint8_t)0xA)  /* TIM2 Alternate Function mapping */
#define GPIO_AF10_TIM3           ((uint8_t)0xA)  /* TIM3 Alternate Function mapping */
#define GPIO_AF10_TIM17          ((uint8_t)0xA)  /* TIM17 Alternate Function mapping */

/** 
  * @brief   AF 11 selection  
  */ 
#define GPIO_AF11_TIM1          ((uint8_t)0x0B)  /* TIM1 Alternate Function mapping */

/** 
  * @brief   AF 12 selection  
  */ 
#define GPIO_AF12_TIM1          ((uint8_t)0x0C)  /* TIM1 Alternate Function mapping */

/** 
  * @brief   AF 13 selection  
  */ 
#define GPIO_AF13_OPAMP2        ((uint8_t)0x0D)  /* OPAMP2 Alternate Function mapping */

/** 
  * @brief   AF 15 selection  
  */ 
#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */

#define IS_GPIO_AF(AF)          (((AF) <= (uint8_t)0x0D) || ((AF) == (uint8_t)0x0F))
/*------------------------------------------------------------------------------------------*/
#endif /* STM32F303x8 */

#if defined (STM32F334x8) || defined (STM32F328xx)
/*---------------------------------- STM32F334x8/STM32F328xx -------------------------------*/
/** 
  * @brief   AF 0 selection  
  */ 
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO (MCO1 and MCO2) Alternate Function mapping            */
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping             */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping                          */

/** 
  * @brief   AF 1 selection  
  */ 
#define GPIO_AF1_TIM2           ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */
#define GPIO_AF1_TIM15          ((uint8_t)0x01)  /* TIM15 Alternate Function mapping */
#define GPIO_AF1_TIM16          ((uint8_t)0x01)  /* TIM16 Alternate Function mapping */
#define GPIO_AF1_TIM17          ((uint8_t)0x01)  /* TIM17 Alternate Function mapping */
#define GPIO_AF1_EVENTOUT       ((uint8_t)0x01)  /* EVENTOUT Alternate Function mapping */
/** 
  * @brief   AF 2 selection  
  */ 
#define GPIO_AF2_TIM3           ((uint8_t)0x02)  /* TIM3 Alternate Function mapping */
#define GPIO_AF2_TIM1           ((uint8_t)0x02)  /* TIM1 Alternate Function mapping */
#define GPIO_AF2_TIM15          ((uint8_t)0x02)  /* TIM15 Alternate Function mapping */
#define GPIO_AF2_TIM16          ((uint8_t)0x02)  /* TIM16 Alternate Function mapping */

/** 
  * @brief   AF 3 selection  
  */ 
#define GPIO_AF3_TSC           ((uint8_t)0x03)  /* TSC Alternate Function mapping  */
#define GPIO_AF3_HRTIM1        ((uint8_t)0x03)  /* HRTIM1 Alternate Function mapping  */

/** 
  * @brief   AF 4 selection  
  */ 
#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping */
#define GPIO_AF4_TIM1          ((uint8_t)0x04)  /* TIM1 Alternate Function mapping */

/** 
  * @brief   AF 5 selection  
  */ 
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /* SPI1 Alternate Function mapping */
#define GPIO_AF5_IR            ((uint8_t)0x05)  /* IR Alternate Function mapping */
/** 
  * @brief   AF 6 selection  
  */ 
#define GPIO_AF6_TIM1          ((uint8_t)0x06)  /* TIM1 Alternate Function mapping */
#define GPIO_AF6_IR            ((uint8_t)0x06)  /* IR Alternate Function mapping */

/** 
  * @brief   AF 7 selection  
  */ 
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /* USART1 Alternate Function mapping  */
#define GPIO_AF7_USART2        ((uint8_t)0x07)  /* USART2 Alternate Function mapping  */
#define GPIO_AF7_USART3        ((uint8_t)0x07)  /* USART3 Alternate Function mapping  */
#define GPIO_AF7_GPCOMP6       ((uint8_t)0x07)  /* GPCOMP6 Alternate Function mapping  */

/** 
  * @brief   AF 8 selection  
  */ 
#define GPIO_AF8_GPCOMP2         ((uint8_t)0x08)  /* GPCOMP2 Alternate Function mapping  */
#define GPIO_AF8_GPCOMP4         ((uint8_t)0x08)  /* GPCOMP4 Alternate Function mapping  */
#define GPIO_AF8_GPCOMP6         ((uint8_t)0x08)  /* GPCOMP6 Alternate Function mapping  */

/** 
  * @brief   AF 9 selection 
  */ 
#define GPIO_AF9_CAN           ((uint8_t)0x09)  /* CAN Alternate Function mapping  */
#define GPIO_AF9_TIM1          ((uint8_t)0x09)  /* TIM1 Alternate Function mapping */
#define GPIO_AF9_TIM15         ((uint8_t)0x09)  /* TIM15 Alternate Function mapping */
/** 
  * @brief   AF 10 selection  
  */ 
#define GPIO_AF10_TIM2           ((uint8_t)0xA)  /* TIM2 Alternate Function mapping */
#define GPIO_AF10_TIM3           ((uint8_t)0xA)  /* TIM3 Alternate Function mapping */
#define GPIO_AF10_TIM17          ((uint8_t)0xA)  /* TIM17 Alternate Function mapping */

/** 
  * @brief   AF 11 selection  
  */ 
#define GPIO_AF11_TIM1          ((uint8_t)0x0B)  /* TIM1 Alternate Function mapping */

/** 
  * @brief   AF 12 selection  
  */ 
#define GPIO_AF12_TIM1          ((uint8_t)0x0C)  /* TIM1 Alternate Function mapping */
#define GPIO_AF12_HRTIM1        ((uint8_t)0x0C)  /* HRTIM1 Alternate Function mapping  */

/** 
  * @brief   AF 13 selection  
  */ 
#define GPIO_AF13_OPAMP2        ((uint8_t)0x0D)  /* OPAMP2 Alternate Function mapping */
#define GPIO_AF13_HRTIM1        ((uint8_t)0x0D)  /* HRTIM1 Alternate Function mapping  */

/** 
  * @brief   AF 15 selection  
  */ 
#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */

#define IS_GPIO_AF(AF)          (((AF) <= (uint8_t)0x0D) || ((AF) == (uint8_t)0x0F))
/*------------------------------------------------------------------------------------------*/
#endif /* STM32F334x8 || STM32F328xx */

#if defined (STM32F301x8) || defined (STM32F318xx)
/*---------------------------------- STM32F301x8 / STM32F318xx ------------------------------------------*/
/** 
  * @brief   AF 0 selection  
  */ 
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO (MCO1 and MCO2) Alternate Function mapping            */
#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)  /* RTC Alternate Function mapping     								       */
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping             */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping                          */

/** 
  * @brief   AF 1 selection  
  */ 
#define GPIO_AF1_TIM2           ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */
#define GPIO_AF1_TIM15          ((uint8_t)0x01)  /* TIM15 Alternate Function mapping */
#define GPIO_AF1_TIM16          ((uint8_t)0x01)  /* TIM16 Alternate Function mapping */
#define GPIO_AF1_TIM17          ((uint8_t)0x01)  /* TIM17 Alternate Function mapping */
#define GPIO_AF1_EVENTOUT       ((uint8_t)0x01)  /* EVENTOUT Alternate Function mapping */
/** 
  * @brief   AF 2 selection  
  */ 
#define GPIO_AF2_I2C3           ((uint8_t)0x02)  /* I2C3 Alternate Function mapping */
#define GPIO_AF2_TIM1           ((uint8_t)0x02)  /* TIM1 Alternate Function mapping */
#define GPIO_AF2_TIM15          ((uint8_t)0x02)  /* TIM15 Alternate Function mapping */
#define GPIO_AF2_TIM2           ((uint8_t)0x02)  /* TIM2 Alternate Function mapping */

/** 
  * @brief   AF 3 selection  
  */ 
#define GPIO_AF3_TSC           ((uint8_t)0x03)  /* TSC Alternate Function mapping  */
#define GPIO_AF3_I2C3          ((uint8_t)0x03)  /* I2C3 Alternate Function mapping  */
#define GPIO_AF3_TIM15         ((uint8_t)0x03)  /* TIM15 Alternate Function mapping  */

/** 
  * @brief   AF 4 selection  
  */ 
#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping */
#define GPIO_AF4_I2C2          ((uint8_t)0x04)  /* I2C2 Alternate Function mapping */
#define GPIO_AF4_TIM1          ((uint8_t)0x04)  /* TIM1 Alternate Function mapping */
#define GPIO_AF4_TIM16         ((uint8_t)0x04)  /* TIM16 Alternate Function mapping */
#define GPIO_AF4_TIM17         ((uint8_t)0x04)  /* TIM17 Alternate Function mapping */

/** 
  * @brief   AF 5 selection  
  */ 
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /* SPI1 Alternate Function mapping */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF5_SPI3          ((uint8_t)0x05)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF5_IR            ((uint8_t)0x05)  /* IR Alternate Function mapping */
/** 
  * @brief   AF 6 selection  
  */ 
#define GPIO_AF6_TIM1          ((uint8_t)0x06)  /* TIM1 Alternate Function mapping */
#define GPIO_AF6_IR            ((uint8_t)0x06)  /* IR Alternate Function mapping */
#define GPIO_AF6_SPI2          ((uint8_t)0x06)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF6_SPI3          ((uint8_t)0x06)  /* SPI3/I2S3 Alternate Function mapping */

/** 
  * @brief   AF 7 selection  
  */ 
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /* USART1 Alternate Function mapping  */
#define GPIO_AF7_USART2        ((uint8_t)0x07)  /* USART2 Alternate Function mapping  */
#define GPIO_AF7_USART3        ((uint8_t)0x07)  /* USART3 Alternate Function mapping  */
#define GPIO_AF7_GPCOMP6       ((uint8_t)0x07)  /* GPCOMP6 Alternate Function mapping  */

/** 
  * @brief   AF 8 selection  
  */ 
#define GPIO_AF8_I2C3            ((uint8_t)0x08)  /* I2C3 Alternate Function mapping  */
#define GPIO_AF8_GPCOMP2         ((uint8_t)0x08)  /* GPCOMP2 Alternate Function mapping  */
#define GPIO_AF8_GPCOMP4         ((uint8_t)0x08)  /* GPCOMP4 Alternate Function mapping  */
#define GPIO_AF8_GPCOMP6         ((uint8_t)0x08)  /* GPCOMP6 Alternate Function mapping  */

/** 
  * @brief   AF 9 selection 
  */ 
#define GPIO_AF9_TIM1          ((uint8_t)0x09)  /* TIM1 Alternate Function mapping */
#define GPIO_AF9_TIM15         ((uint8_t)0x09)  /* TIM15 Alternate Function mapping */

/** 
  * @brief   AF 10 selection  
  */ 
#define GPIO_AF10_TIM2           ((uint8_t)0xA)  /* TIM2 Alternate Function mapping */
#define GPIO_AF10_TIM17          ((uint8_t)0xA)  /* TIM17 Alternate Function mapping */

/** 
  * @brief   AF 11 selection  
  */ 
#define GPIO_AF11_TIM1          ((uint8_t)0x0B)  /* TIM1 Alternate Function mapping */

/** 
  * @brief   AF 12 selection  
  */ 
#define GPIO_AF12_TIM1          ((uint8_t)0x0C)  /* TIM1 Alternate Function mapping */

/** 
  * @brief   AF 15 selection  
  */ 
#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */

#define IS_GPIO_AF(AF)          (((AF) <= (uint8_t)0x0C) || ((AF) == (uint8_t)0x0F))
/*------------------------------------------------------------------------------------------*/
#endif /* STM32F301x8 || STM32F318xx */

#if defined (STM32F302x8)
/*---------------------------------- STM32F302x8------------------------------------------*/
/** 
  * @brief   AF 0 selection  
  */ 
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO (MCO1 and MCO2) Alternate Function mapping            */
#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)  /* RTC Alternate Function mapping     								       */
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping             */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping                          */

/** 
  * @brief   AF 1 selection  
  */ 
#define GPIO_AF1_TIM2           ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */
#define GPIO_AF1_TIM15          ((uint8_t)0x01)  /* TIM15 Alternate Function mapping */
#define GPIO_AF1_TIM16          ((uint8_t)0x01)  /* TIM16 Alternate Function mapping */
#define GPIO_AF1_TIM17          ((uint8_t)0x01)  /* TIM17 Alternate Function mapping */
#define GPIO_AF1_EVENTOUT       ((uint8_t)0x01)  /* EVENTOUT Alternate Function mapping */
/** 
  * @brief   AF 2 selection  
  */ 
#define GPIO_AF2_I2C3           ((uint8_t)0x02)  /* I2C3 Alternate Function mapping */
#define GPIO_AF2_TIM1           ((uint8_t)0x02)  /* TIM1 Alternate Function mapping */
#define GPIO_AF2_TIM15          ((uint8_t)0x02)  /* TIM15 Alternate Function mapping */
#define GPIO_AF2_TIM2           ((uint8_t)0x02)  /* TIM2 Alternate Function mapping */

/** 
  * @brief   AF 3 selection  
  */ 
#define GPIO_AF3_TSC           ((uint8_t)0x03)  /* TSC Alternate Function mapping  */
#define GPIO_AF3_I2C3          ((uint8_t)0x03)  /* I2C3 Alternate Function mapping  */
#define GPIO_AF3_TIM15         ((uint8_t)0x03)  /* TIM15 Alternate Function mapping  */

/** 
  * @brief   AF 4 selection  
  */ 
#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping */
#define GPIO_AF4_I2C2          ((uint8_t)0x04)  /* I2C2 Alternate Function mapping */
#define GPIO_AF4_TIM1          ((uint8_t)0x04)  /* TIM1 Alternate Function mapping */
#define GPIO_AF4_TIM16         ((uint8_t)0x04)  /* TIM16 Alternate Function mapping */
#define GPIO_AF4_TIM17         ((uint8_t)0x04)  /* TIM17 Alternate Function mapping */

/** 
  * @brief   AF 5 selection  
  */ 
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /* SPI1 Alternate Function mapping */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF5_SPI3          ((uint8_t)0x05)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF5_IR            ((uint8_t)0x05)  /* IR Alternate Function mapping */
/** 
  * @brief   AF 6 selection  
  */ 
#define GPIO_AF6_TIM1          ((uint8_t)0x06)  /* TIM1 Alternate Function mapping */
#define GPIO_AF6_IR            ((uint8_t)0x06)  /* IR Alternate Function mapping */
#define GPIO_AF6_SPI2          ((uint8_t)0x06)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF6_SPI3          ((uint8_t)0x06)  /* SPI3/I2S3 Alternate Function mapping */

/** 
  * @brief   AF 7 selection  
  */ 
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /* USART1 Alternate Function mapping  */
#define GPIO_AF7_USART2        ((uint8_t)0x07)  /* USART2 Alternate Function mapping  */
#define GPIO_AF7_USART3        ((uint8_t)0x07)  /* USART3 Alternate Function mapping  */
#define GPIO_AF7_GPCOMP6       ((uint8_t)0x07)  /* GPCOMP6 Alternate Function mapping */
#define GPIO_AF7_CAN           ((uint8_t)0x07)  /* CAN Alternate Function mapping */

/** 
  * @brief   AF 8 selection  
  */ 
#define GPIO_AF8_I2C3   	 ((uint8_t)0x08)  /* I2C3 Alternate Function mapping  */
#define GPIO_AF8_GPCOMP2         ((uint8_t)0x08)  /* GPCOMP2 Alternate Function mapping  */
#define GPIO_AF8_GPCOMP4         ((uint8_t)0x08)  /* GPCOMP4 Alternate Function mapping  */
#define GPIO_AF8_GPCOMP6         ((uint8_t)0x08)  /* GPCOMP6 Alternate Function mapping  */

/** 
  * @brief   AF 9 selection 
  */ 
#define GPIO_AF9_TIM1          ((uint8_t)0x09)  /* TIM1 Alternate Function mapping */
#define GPIO_AF9_TIM15         ((uint8_t)0x09)  /* TIM15 Alternate Function mapping */
#define GPIO_AF9_CAN           ((uint8_t)0x09)  /* CAN Alternate Function mapping */

/** 
  * @brief   AF 10 selection  
  */ 
#define GPIO_AF10_TIM2           ((uint8_t)0xA)  /* TIM2 Alternate Function mapping */
#define GPIO_AF10_TIM17          ((uint8_t)0xA)  /* TIM17 Alternate Function mapping */

/** 
  * @brief   AF 11 selection  
  */ 
#define GPIO_AF11_TIM1          ((uint8_t)0x0B)  /* TIM1 Alternate Function mapping */

/** 
  * @brief   AF 12 selection  
  */ 
#define GPIO_AF12_TIM1          ((uint8_t)0x0C)  /* TIM1 Alternate Function mapping */

/** 
  * @brief   AF 15 selection  
  */ 
#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */

#define IS_GPIO_AF(AF)          (((AF) <= (uint8_t)0x0C) || ((AF) == (uint8_t)0x0F))
/*------------------------------------------------------------------------------------------*/
#endif /* STM32F302x8 */
/**
  * @}
  */ 

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 


/**
  * @}
  */ 

/**
  * @}
  */ 
  
#ifdef __cplusplus
}
#endif

#endif /* __STM32F3xx_HAL_GPIO_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
