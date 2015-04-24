/**
  ******************************************************************************
  * @file    stm32l1xx_hal_gpio_ex.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   Header file of GPIO HAL Extension module.
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
#ifndef __STM32L1xx_HAL_GPIO_EX_H
#define __STM32L1xx_HAL_GPIO_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @defgroup GPIOEx GPIOEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/** @defgroup GPIOEx_Exported_Constants GPIOEx Exported Constants
  * @{
  */ 
  
/** @defgroup GPIOEx_Alternate_function_selection GPIOEx Alternate function selection 
  * @{
  */
  
/** 
  * @brief   AF 0 selection  
  */ 
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO Alternate Function mapping                 */
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)  /* TAMPER  Alternate Function mapping             */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping  */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping               */
#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)  /* RTC_OUT Alternate Function mapping             */
   
/** 
  * @brief   AF 1 selection  
  */ 
#define GPIO_AF1_TIM2           ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */

/** 
  * @brief   AF 2 selection  
  */ 
#define GPIO_AF2_TIM3           ((uint8_t)0x02)  /* TIM3 Alternate Function mapping */
#define GPIO_AF2_TIM4           ((uint8_t)0x02)  /* TIM4 Alternate Function mapping */
#if defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) || defined (STM32L162xC) || defined (STM32L152xC) || defined (STM32L151xC)
#define GPIO_AF2_TIM5           ((uint8_t)0x02)  /* TIM5 Alternate Function mapping */

#endif /*  STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD ...STM32L151xC */ 

/** 
  * @brief   AF 3 selection  
  */ 
#define GPIO_AF3_TIM9            ((uint8_t)0x03)  /* TIM9 Alternate Function mapping */
#define GPIO_AF3_TIM10           ((uint8_t)0x03)  /* TIM10 Alternate Function mapping */
#define GPIO_AF3_TIM11           ((uint8_t)0x03)  /* TIM11 Alternate Function mapping */


/** 
  * @brief   AF 4 selection  
  */ 
#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping */
#define GPIO_AF4_I2C2          ((uint8_t)0x04)  /* I2C2 Alternate Function mapping */

/** 
  * @brief   AF 5 selection  
  */ 
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /* SPI1/I2S1 Alternate Function mapping      */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2/I2S2 Alternate Function mapping */

/** 
  * @brief   AF 6 selection  
  */ 
#if defined (STM32L100xC) || defined (STM32L151xC) || defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L151xE) ||\
    defined (STM32L152xC) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L152xE) ||\
    defined (STM32L162xC) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L162xE)
    
#define GPIO_AF6_SPI3          ((uint8_t)0x06)  /* SPI3/I2S3 Alternate Function mapping */

#endif /* STM32L100xC || STM32L151xC || (...) || STM32L162xD || STM32L162xE */


/** 
  * @brief   AF 7 selection  
  */ 
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /* USART1 Alternate Function mapping  */
#define GPIO_AF7_USART2        ((uint8_t)0x07)  /* USART2 Alternate Function mapping  */
#define GPIO_AF7_USART3        ((uint8_t)0x07)  /* USART3 Alternate Function mapping  */

/** 
  * @brief   AF 8 selection  
  */ 
#if defined (STM32L151xD) || defined (STM32L151xE) ||\
    defined (STM32L152xD) || defined (STM32L152xE) ||\
    defined (STM32L162xD) || defined (STM32L162xE)
   
#define GPIO_AF8_UART4        ((uint8_t)0x08)  /* UART4 Alternate Function mapping  */
#define GPIO_AF8_UART5        ((uint8_t)0x08)  /* UART5 Alternate Function mapping  */

#endif /* STM32L151xD || STM32L151xE || STM32L152xD || STM32L 152xE || STM32L162xD || STM32L162xE */


/** 
  * @brief   AF 9 selection 
  */ 

/** 
  * @brief   AF 10 selection  
  */ 

/** 
  * @brief   AF 11 selection  
  */ 
#if defined (STM32L100xB) || defined (STM32L100xBA) || defined (STM32L100xC) ||\
    defined (STM32L152xB) || defined (STM32L152xBA) || defined (STM32L152xC) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L152xE) ||\
    defined (STM32L162xC) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L162xE)

#define GPIO_AF11_LCD            ((uint8_t)0x0B)  /* LCD Alternate Function mapping */

#endif /* STM32L100xB || STM32L100xBA || STM32L100xC || (...) || STM32L162xCA || STM32L162xD || STM32L162xE */

/** 
  * @brief   AF 12 selection  
  */ 
#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD)
    
#define GPIO_AF12_FSMC            ((uint8_t)0x0C)  /* FSMC Alternate Function mapping */
#define GPIO_AF12_SDIO            ((uint8_t)0x0C)  /* SDIO Alternate Function mapping */

#endif /* STM32L151xD || STM32L152xD || STM32L162xD */
/** 
  * @brief   AF 13 selection  
  */ 

/** 
  * @brief   AF 14 selection  
  */ 
#define GPIO_AF14_TIM_IC1         ((uint8_t)0x0E)  /* TIMER INPUT CAPTURE Alternate Function mapping */
#define GPIO_AF14_TIM_IC2         ((uint8_t)0x0E)  /* TIMER INPUT CAPTURE Alternate Function mapping */
#define GPIO_AF14_TIM_IC3         ((uint8_t)0x0E)  /* TIMER INPUT CAPTURE Alternate Function mapping */
#define GPIO_AF14_TIM_IC4         ((uint8_t)0x0E)  /* TIMER INPUT CAPTURE Alternate Function mapping */

/** 
  * @brief   AF 15 selection  
  */ 
#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */

/**
  * @}
  */ 

/**
  * @}
  */

/** @defgroup GPIOEx_Private_Macros GPIOEx Private Macros
  * @{
  */


#define IS_GPIO_AF(AF)   ((AF) <= (uint8_t)0x0F)


#if defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define GET_GPIO_INDEX(__GPIOx__) (((__GPIOx__) == (GPIOA))? 0U :\
                                   ((__GPIOx__) == (GPIOB))? 1U :\
                                   ((__GPIOx__) == (GPIOC))? 2U :\
                                   ((__GPIOx__) == (GPIOD))? 3U :\
                                   ((__GPIOx__) == (GPIOE))? 4U :\
                                   ((__GPIOx__) == (GPIOF))? 5U :\
                                   ((__GPIOx__) == (GPIOG))? 6U :\
                                   ((__GPIOx__) == (GPIOH))? 7U : 8U)
#endif 

#if defined (STM32L151xB) || defined (STM32L151xBA) || defined (STM32L151xC) || defined (STM32L152xB) || defined (STM32L152xBA) || defined (STM32L152xC) || defined (STM32L162xC)
#define GET_GPIO_INDEX(__GPIOx__) (((__GPIOx__) == (GPIOA))? 0U :\
                                   ((__GPIOx__) == (GPIOB))? 1U :\
                                   ((__GPIOx__) == (GPIOC))? 2U :\
                                   ((__GPIOx__) == (GPIOD))? 3U :\
                                   ((__GPIOx__) == (GPIOE))? 4U :\
                                   ((__GPIOx__) == (GPIOH))? 7U : 8U)
#endif 

#if defined (STM32L100xB) || defined (STM32L100xBA) || defined (STM32L100xC)
#define GET_GPIO_INDEX(__GPIOx__) (((__GPIOx__) == (GPIOA))? 0U :\
                                   ((__GPIOx__) == (GPIOB))? 1U :\
                                   ((__GPIOx__) == (GPIOC))? 2U :\
                                   ((__GPIOx__) == (GPIOD))? 3U :\
                                   ((__GPIOx__) == (GPIOH))? 7U : 8U)
#endif 



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

#endif /* __STM32L1xx_HAL_GPIO_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
