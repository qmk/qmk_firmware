/**
  ******************************************************************************
  * @file    stm32f0xx_hal_smartcard_ex.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    11-December-2014
  * @brief   Header file of SMARTCARD HAL module.
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
#ifndef __STM32F0xx_HAL_SMARTCARD_EX_H
#define __STM32F0xx_HAL_SMARTCARD_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

#if !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6) && !defined(STM32F070xB) && !defined(STM32F030xC) 

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal_def.h"

/** @addtogroup STM32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup SMARTCARDEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/** @defgroup SMARTCARD_Extended_Exported_Macros SMARTCARDEx Exported Macros
  * @{
  */

/** @brief  Reports the SMARTCARD clock source.
  * @param  __HANDLE__: specifies the SMARTCARD Handle
  * @param  __CLOCKSOURCE__ : output variable   
  * @retval the SMARTCARD clocking source, written in __CLOCKSOURCE__.
  */
#if defined(STM32F031x6) || defined(STM32F038xx)
#define __HAL_SMARTCARD_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                             \
     switch(__HAL_RCC_GET_USART1_SOURCE())                         \
     {                                                             \
      case RCC_USART1CLKSOURCE_PCLK1:                              \
        (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_PCLK1;           \
        break;                                                     \
      case RCC_USART1CLKSOURCE_HSI:                                \
        (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_HSI;             \
        break;                                                     \
      case RCC_USART1CLKSOURCE_SYSCLK:                             \
        (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_SYSCLK;          \
        break;                                                     \
      case RCC_USART1CLKSOURCE_LSE:                                \
        (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_LSE;             \
        break;                                                     \
      default:                                                     \
        (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_UNDEFINED;       \
        break;                                                     \
     }                                                             \
  } while(0)
#elif defined (STM32F030x8) ||                                     \
      defined (STM32F042x6) || defined (STM32F048xx) ||            \
      defined (STM32F051x8) || defined (STM32F058xx)
#define __HAL_SMARTCARD_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                             \
    if((__HANDLE__)->Instance == USART1)                           \
    {                                                              \
       switch(__HAL_RCC_GET_USART1_SOURCE())                       \
       {                                                           \
        case RCC_USART1CLKSOURCE_PCLK1:                            \
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_PCLK1;         \
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
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_UNDEFINED;     \
          break;                                                   \
       }                                                           \
    }                                                              \
    else if((__HANDLE__)->Instance == USART2)                      \
    {                                                              \
      (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_PCLK1;             \
    }                                                              \
    else                                                           \
    {                                                              \
      (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_UNDEFINED;         \
    }                                                              \
  } while(0) 
#elif defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx)   
#define __HAL_SMARTCARD_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                             \
    if((__HANDLE__)->Instance == USART1)                           \
    {                                                              \
       switch(__HAL_RCC_GET_USART1_SOURCE())                       \
       {                                                           \
        case RCC_USART1CLKSOURCE_PCLK1:                            \
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_PCLK1;         \
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
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_UNDEFINED;     \
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
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_UNDEFINED;     \
          break;                                                   \
       }                                                           \
    }                                                              \
    else if((__HANDLE__)->Instance == USART3)                      \
    {                                                              \
      (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_PCLK1;             \
    }                                                              \
    else if((__HANDLE__)->Instance == USART4)                      \
    {                                                              \
      (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_PCLK1;             \
    }                                                              \
    else                                                           \
    {                                                              \
      (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_UNDEFINED;         \
    }                                                              \
  } while(0) 
#elif defined(STM32F091xC) || defined(STM32F098xx) 
#define __HAL_SMARTCARD_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                             \
    if((__HANDLE__)->Instance == USART1)                           \
    {                                                              \
       switch(__HAL_RCC_GET_USART1_SOURCE())                       \
       {                                                           \
        case RCC_USART1CLKSOURCE_PCLK1:                            \
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_PCLK1;         \
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
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_UNDEFINED;     \
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
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_UNDEFINED;     \
          break;                                                   \
       }                                                           \
    }                                                              \
    else if((__HANDLE__)->Instance == USART3)                      \
    {                                                              \
       switch(__HAL_RCC_GET_USART3_SOURCE())                       \
       {                                                           \
        case RCC_USART3CLKSOURCE_PCLK1:                            \
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_PCLK1;         \
          break;                                                   \
        case RCC_USART3CLKSOURCE_HSI:                              \
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_HSI;           \
          break;                                                   \
        case RCC_USART3CLKSOURCE_SYSCLK:                           \
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_SYSCLK;        \
          break;                                                   \
        case RCC_USART3CLKSOURCE_LSE:                              \
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_LSE;           \
          break;                                                   \
        default:                                                   \
          (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_UNDEFINED;     \
          break;                                                   \
       }                                                           \
    }                                                              \
    else if((__HANDLE__)->Instance == USART4)                      \
    {                                                              \
      (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_PCLK1;             \
    }                                                              \
    else if((__HANDLE__)->Instance == USART5)                      \
    {                                                              \
      (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_PCLK1;             \
    }                                                              \
    else if((__HANDLE__)->Instance == USART6)                      \
    {                                                              \
      (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_PCLK1;             \
    }                                                              \
    else if((__HANDLE__)->Instance == USART7)                      \
    {                                                              \
      (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_PCLK1;             \
    }                                                              \
    else if((__HANDLE__)->Instance == USART8)                      \
    {                                                              \
      (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_PCLK1;             \
    }                                                              \
    else                                                           \
    {                                                              \
      (__CLOCKSOURCE__) = SMARTCARD_CLOCKSOURCE_UNDEFINED;         \
    }                                                              \
  } while(0)      
#endif /* defined(STM32F031x6) || defined(STM32F038xx) */

/**
  * @}
  */                                

/* Exported functions --------------------------------------------------------*/

/* Initialization and de-initialization functions  ****************************/
/* IO operation functions *****************************************************/

/** @addtogroup SMARTCARDEx_Exported_Functions
  * @{
  */

/** @addtogroup SMARTCARDEx_Exported_Functions_Group1
  * @{
  */
  
/* Peripheral Control functions ***********************************************/
void HAL_SMARTCARDEx_BlockLength_Config(SMARTCARD_HandleTypeDef *hsmartcard, uint8_t BlockLength);
void HAL_SMARTCARDEx_TimeOut_Config(SMARTCARD_HandleTypeDef *hsmartcard, uint32_t TimeOutValue);
HAL_StatusTypeDef HAL_SMARTCARDEx_EnableReceiverTimeOut(SMARTCARD_HandleTypeDef *hsmartcard);
HAL_StatusTypeDef HAL_SMARTCARDEx_DisableReceiverTimeOut(SMARTCARD_HandleTypeDef *hsmartcard);

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

#endif /* !defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070x6) && !defined(STM32F070xB) && !defined(STM32F030xC)  */  
  
#ifdef __cplusplus
}
#endif

#endif /* __STM32F0xx_HAL_SMARTCARD_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

