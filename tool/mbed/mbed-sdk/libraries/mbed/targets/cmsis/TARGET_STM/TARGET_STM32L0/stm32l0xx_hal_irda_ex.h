/**
  ******************************************************************************
  * @file    stm32l0xx_hal_irda_ex.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   Header file of IRDA HAL Extension module.
  ******************************************************************************
  * @attention
  *                               
  * <h2><center>&copy; COPYRIGHT(c) 2013 STMicroelectronics</center></h2>
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
#ifndef __STM32L0xx_HAL_IRDA_EX_H
#define __STM32L0xx_HAL_IRDA_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @addtogroup IRDAEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup IRDAEx_Extended_Exported_Constants IRDA Extended Exported Constants
  * @{
  */
  
/** @defgroup IRDAEx_Word_Length IRDAEx Word length
  * @{
  */
#define IRDA_WORDLENGTH_7B                  ((uint32_t)USART_CR1_M_1)
#define IRDA_WORDLENGTH_8B                  ((uint32_t)0x00000000)
#define IRDA_WORDLENGTH_9B                  ((uint32_t)USART_CR1_M_0)
#define IS_IRDA_WORD_LENGTH(LENGTH) (((LENGTH) == IRDA_WORDLENGTH_7B) || \
                                     ((LENGTH) == IRDA_WORDLENGTH_8B) || \
                                     ((LENGTH) == IRDA_WORDLENGTH_9B))
/**
  * @}
  */
  
  
/**
  * @}
  */  
  
/* Exported macro ------------------------------------------------------------*/

/** @defgroup IRDAEx_Extended_Exported_Macros IRDA Extended Exported Macros
  * @{
  */
/** @brief  Reports the IRDA clock source.
  * @param  __HANDLE__: specifies the UART Handle
  * @param  __CLOCKSOURCE__ : output variable   
  * @retval IRDA clocking source, written in __CLOCKSOURCE__.
  */
#if defined (STM32L031xx) || defined (STM32L041xx)
#define IRDA_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                        \
    if((__HANDLE__)->Instance == USART2)                      \
    {                                                         \
       switch(__HAL_RCC_GET_USART2_SOURCE())                  \
       {                                                      \
        case RCC_USART2CLKSOURCE_PCLK1:                       \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_PCLK1;         \
          break;                                              \
        case RCC_USART2CLKSOURCE_HSI:                         \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_HSI;           \
          break;                                              \
        case RCC_USART2CLKSOURCE_SYSCLK:                      \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_SYSCLK;        \
          break;                                              \
        case RCC_USART2CLKSOURCE_LSE:                         \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_LSE;           \
          break;                                              \
        default:                                              \
          break;                                              \
       }                                                      \
    }                                                         \
    else if((__HANDLE__)->Instance == LPUART1)                \
    {                                                         \
       switch(__HAL_RCC_GET_LPUART1_SOURCE())                 \
       {                                                      \
        case RCC_LPUART1CLKSOURCE_PCLK1:                      \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_PCLK1;         \
          break;                                              \
        case RCC_LPUART1CLKSOURCE_HSI:                        \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_HSI;           \
          break;                                              \
        case RCC_LPUART1CLKSOURCE_SYSCLK:                     \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_SYSCLK;        \
          break;                                              \
        case RCC_LPUART1CLKSOURCE_LSE:                        \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_LSE;           \
          break;                                              \
        default:                                              \
          break;                                              \
       }                                                      \
    }                                                         \
  } while(0)

#else /* (STM32L031xx) || defined (STM32L041xx) */

#define IRDA_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                        \
    if((__HANDLE__)->Instance == USART1)                      \
    {                                                         \
       switch(__HAL_RCC_GET_USART1_SOURCE())                  \
       {                                                      \
        case RCC_USART1CLKSOURCE_PCLK2:                       \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_PCLK2;         \
          break;                                              \
        case RCC_USART1CLKSOURCE_HSI:                         \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_HSI;           \
          break;                                              \
        case RCC_USART1CLKSOURCE_SYSCLK:                      \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_SYSCLK;        \
          break;                                              \
        case RCC_USART1CLKSOURCE_LSE:                         \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_LSE;           \
          break;                                              \
        default:                                              \
          break;                                              \
       }                                                      \
    }                                                         \
    else  if((__HANDLE__)->Instance == USART2)                \
    {                                                         \
       switch(__HAL_RCC_GET_USART2_SOURCE())                  \
       {                                                      \
        case RCC_USART2CLKSOURCE_PCLK1:                       \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_PCLK1;         \
          break;                                              \
        case RCC_USART2CLKSOURCE_HSI:                         \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_HSI;           \
          break;                                              \
        case RCC_USART2CLKSOURCE_SYSCLK:                      \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_SYSCLK;        \
          break;                                              \
        case RCC_USART2CLKSOURCE_LSE:                         \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_LSE;           \
          break;                                              \
        default:                                              \
          break;                                              \
       }                                                      \
    }                                                         \
    else if((__HANDLE__)->Instance == LPUART1)                \
    {                                                         \
       switch(__HAL_RCC_GET_LPUART1_SOURCE())                 \
       {                                                      \
        case RCC_LPUART1CLKSOURCE_PCLK1:                      \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_PCLK1;         \
          break;                                              \
        case RCC_LPUART1CLKSOURCE_HSI:                        \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_HSI;           \
          break;                                              \
        case RCC_LPUART1CLKSOURCE_SYSCLK:                     \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_SYSCLK;        \
          break;                                              \
        case RCC_LPUART1CLKSOURCE_LSE:                        \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_LSE;           \
          break;                                              \
        default:                                              \
          break;                                              \
       }                                                      \
    }                                                         \
  } while(0)
#endif /* (STM32L031xx) || (STM32L041xx) */
    
/** @brief  Reports the mask to apply to retrieve the received data
  *         according to the word length and to the parity bits activation.
  * @param  __HANDLE__: specifies the IRDA Handle
  * @retval mask to apply to USART RDR register value.
  */    
#define IRDA_MASK_COMPUTATION(__HANDLE__)                       \
  do {                                                                \
  if ((__HANDLE__)->Init.WordLength == IRDA_WORDLENGTH_9B)            \
  {                                                                   \
     if ((__HANDLE__)->Init.Parity == IRDA_PARITY_NONE)               \
     {                                                                \
        (__HANDLE__)->Mask = 0x01FF ;                                 \
     }                                                                \
     else                                                             \
     {                                                                \
        (__HANDLE__)->Mask = 0x00FF ;                                 \
     }                                                                \
  }                                                                   \
  else if ((__HANDLE__)->Init.WordLength == IRDA_WORDLENGTH_8B)       \
  {                                                                   \
     if ((__HANDLE__)->Init.Parity == IRDA_PARITY_NONE)               \
     {                                                                \
        (__HANDLE__)->Mask = 0x00FF ;                                 \
     }                                                                \
     else                                                             \
     {                                                                \
        (__HANDLE__)->Mask = 0x007F ;                                 \
     }                                                                \
  }                                                                   \
  else if ((__HANDLE__)->Init.WordLength == IRDA_WORDLENGTH_7B)       \
  {                                                                   \
     if ((__HANDLE__)->Init.Parity == IRDA_PARITY_NONE)               \
     {                                                                \
        (__HANDLE__)->Mask = 0x007F ;                                 \
     }                                                                \
     else                                                             \
     {                                                                \
        (__HANDLE__)->Mask = 0x003F ;                                 \
     }                                                                \
  }                                                                   \
} while(0)
/**
  * @}
  */
  
/* Exported functions --------------------------------------------------------*/
/* Initialization/de-initialization methods  **********************************/
/* IO operation methods *******************************************************/
/* Peripheral Control methods  ************************************************/
/* Peripheral State methods  **************************************************/


/**
  * @}
  */ 

/**
  * @}
  */ 
  
#ifdef __cplusplus
}
#endif

#endif /* __STM32L0xx_HAL_IRDA_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

