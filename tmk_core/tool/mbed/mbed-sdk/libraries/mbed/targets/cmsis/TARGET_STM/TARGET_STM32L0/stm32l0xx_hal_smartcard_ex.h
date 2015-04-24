/**
  ******************************************************************************
  * @file    stm32l0xx_hal_smartcard_ex.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   Header file of SMARTCARD HAL module.
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
#ifndef __STM32L0xx_HAL_SMARTCARD_EX_H
#define __STM32L0xx_HAL_SMARTCARD_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup SMARTCARDEx SMARTCARDEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
   
/** @brief  Reports the SMARTCARD clock source.
  * @param  __HANDLE__: specifies the USART Handle
  * @param  __CLOCKSOURCE__ : output variable   
  * @retval the USART clocking source, written in __CLOCKSOURCE__.
  */
#if defined (STM32L031xx) || defined (STM32L041xx)
#define SMARTCARD_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                             \
    if((__HANDLE__)->Instance == USART2)                      \
    {                                                              \
       switch(__HAL_RCC_GET_USART2_SOURCE())                       \
       {                                                           \
        case RCC_USART2CLKSOURCE_PCLK1:                            \
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_PCLK1;         \
          break;                                                   \
        case RCC_USART2CLKSOURCE_HSI:                              \
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_HSI;           \
          break;                                                   \
        case RCC_USART2CLKSOURCE_SYSCLK:                           \
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_SYSCLK;        \
          break;                                                   \
        case RCC_USART2CLKSOURCE_LSE:                              \
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_LSE;           \
          break;                                                   \
        default:                                                   \
          break;                                                   \
       }                                                           \
    }                                                              \
  } while(0)

#else /* (STM32L031xx) || defined (STM32L041xx) */

#define SMARTCARD_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                             \
    if((__HANDLE__)->Instance == USART1)                           \
    {                                                              \
       switch(__HAL_RCC_GET_USART1_SOURCE())                       \
       {                                                           \
        case RCC_USART1CLKSOURCE_PCLK2:                            \
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_PCLK2;         \
          break;                                                   \
        case RCC_USART1CLKSOURCE_HSI:                              \
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_HSI;           \
          break;                                                   \
        case RCC_USART1CLKSOURCE_SYSCLK:                           \
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_SYSCLK;        \
          break;                                                   \
        case RCC_USART1CLKSOURCE_LSE:                              \
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_LSE;           \
          break;                                                   \
        default:                                                   \
          break;                                                   \
       }                                                           \
    }                                                              \
    else if((__HANDLE__)->Instance == USART2)                      \
    {                                                              \
       switch(__HAL_RCC_GET_USART2_SOURCE())                       \
       {                                                           \
        case RCC_USART2CLKSOURCE_PCLK1:                            \
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_PCLK1;         \
          break;                                                   \
        case RCC_USART2CLKSOURCE_HSI:                              \
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_HSI;           \
          break;                                                   \
        case RCC_USART2CLKSOURCE_SYSCLK:                           \
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_SYSCLK;        \
          break;                                                   \
        case RCC_USART2CLKSOURCE_LSE:                              \
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_LSE;           \
          break;                                                   \
        default:                                                   \
          break;                                                   \
       }                                                           \
    }                                                              \
  } while(0)
#endif /* (STM32L031xx) || (STM32L041xx) */

/* Exported functions --------------------------------------------------------*/
/** @defgroup SMARTCARDEx_Exported_Functions SMARTCARD Extended Exported functions
  * @{
  */
/* Initialization/de-initialization functions  ********************************/
/** @defgroup SMARTCARDEx_Exported_Functions_Group1 Extended Peripheral Control functions
 *  @{
 */

/* Initialization and de-initialization functions  ****************************/
/* IO operation functions *****************************************************/
/* Peripheral Control functions ***********************************************/
void HAL_SMARTCARDEx_BlockLength_Config(SMARTCARD_HandleTypeDef *hsc, uint8_t BlockLength);
void HAL_SMARTCARDEx_TimeOut_Config(SMARTCARD_HandleTypeDef *hsc, uint32_t TimeOutValue);
HAL_StatusTypeDef HAL_SMARTCARDEx_EnableReceiverTimeOut(SMARTCARD_HandleTypeDef *hsc);
HAL_StatusTypeDef HAL_SMARTCARDEx_DisableReceiverTimeOut(SMARTCARD_HandleTypeDef *hsc);

/* Peripheral State and Error functions ***************************************/

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

#endif /* __STM32L0xx_HAL_SMARTCARD_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

