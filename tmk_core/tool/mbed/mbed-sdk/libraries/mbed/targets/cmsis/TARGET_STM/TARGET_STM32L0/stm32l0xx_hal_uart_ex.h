/**
  ******************************************************************************
  * @file    stm32l0xx_hal_uart_ex.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   Header file of UART HAL Extension module.
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
#ifndef __STM32L0xx_HAL_UART_EX_H
#define __STM32L0xx_HAL_UART_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup UARTEx UARTEx Extended HAL module driver
  * @{
  */

/******************************************************************************/
/* Exported types ------------------------------------------------------------*/
/******************************************************************************/

   /** @defgroup UARTEx_Exported_Types UARTEx Exported Types
  * @{
  */

/** @defgroup UARTEx_Init_Configuration Extended  initialization configuration structure
  * @{
  */
/** 
  * @brief  UART wake up from stop mode parameters
  */
typedef struct
{
  uint32_t WakeUpEvent;        /*!< Specifies which event will activat the Wakeup from Stop mode flag (WUF).
                                    This parameter can be a value of @ref UART_WakeUp_from_Stop_Selection.
                                    If set to UART_WAKEUP_ON_ADDRESS, the two other fields below must
                                    be filled up. */
  
  uint16_t AddressLength;      /*!< Specifies whether the address is 4 or 7-bit long.
                                    This parameter can be a value of @ref UARTEx_WakeUp_Address_Length  */

  uint8_t Address;             /*!< UART/USART node address (7-bit long max) */
} UART_WakeUpTypeDef;

/**
  * @}
  */
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup UARTEx_Extended_Exported_Constants UARTEx Exported Constants
  * @{
  */
  
/** @defgroup UARTEx_Word_Length  Word length definition
  * @{
  */
#define UART_WORDLENGTH_7B                  ((uint32_t)USART_CR1_M_1)
#define UART_WORDLENGTH_8B                  ((uint32_t)0x0000)
#define UART_WORDLENGTH_9B                  ((uint32_t)USART_CR1_M_0)
#define IS_UART_WORD_LENGTH(LENGTH) (((LENGTH) == UART_WORDLENGTH_7B) || \
                                     ((LENGTH) == UART_WORDLENGTH_8B) || \
                                     ((LENGTH) == UART_WORDLENGTH_9B))
/**
  * @}
  */

/** @defgroup UARTEx_AutoBaud_Rate_Mode Auto baud rate mode definition
  * @{
  */
#define UART_ADVFEATURE_AUTOBAUDRATE_ONSTARTBIT    ((uint32_t)0x0000)
#define UART_ADVFEATURE_AUTOBAUDRATE_ONFALLINGEDGE ((uint32_t)USART_CR2_ABRMODE_0)
#define UART_ADVFEATURE_AUTOBAUDRATE_ON0X7FFRAME   ((uint32_t)USART_CR2_ABRMODE_1)
#define UART_ADVFEATURE_AUTOBAUDRATE_ON0X55FRAME   ((uint32_t)USART_CR2_ABRMODE)
#define IS_UART_ADVFEATURE_AUTOBAUDRATEMODE(MODE)  (((MODE) == UART_ADVFEATURE_AUTOBAUDRATE_ONSTARTBIT) || \
                                                    ((MODE) == UART_ADVFEATURE_AUTOBAUDRATE_ONFALLINGEDGE) || \
                                                    ((MODE) == UART_ADVFEATURE_AUTOBAUDRATE_ON0X7FFRAME) || \
                                                    ((MODE) == UART_ADVFEATURE_AUTOBAUDRATE_ON0X55FRAME))
/**
  * @}
  */  
  
/** @defgroup UARTEx_WakeUp_Address_Length WakeUp address length definition
  * @{
  */
#define UART_ADDRESS_DETECT_4B                ((uint32_t)0x00000000)
#define UART_ADDRESS_DETECT_7B                ((uint32_t)USART_CR2_ADDM7)
#define IS_UART_ADDRESSLENGTH_DETECT(ADDRESS) (((ADDRESS) == UART_ADDRESS_DETECT_4B) || \
                                               ((ADDRESS) == UART_ADDRESS_DETECT_7B))
/**
  * @}
  */  

  
/** @defgroup UARTEx_WakeUp_Methods Wakeup methods definition
  * @{
  */
#define UART_WAKEUPMETHOD_IDLELINE                ((uint32_t)0x00000000)
#define UART_WAKEUPMETHOD_ADDRESSMARK             ((uint32_t)USART_CR1_WAKE)
#define IS_UART_WAKEUPMETHOD(WAKEUP) (((WAKEUP) == UART_WAKEUPMETHOD_IDLELINE) || \
                                       ((WAKEUP) == UART_WAKEUPMETHOD_ADDRESSMARK))
/**
  * @}
  */
  
/**
  * @}
  */  
  
/* Exported macro ------------------------------------------------------------*/

/** @defgroup UARTEx_Extended_Exported_Macros UARTEx Exported Macros
  * @{
  */
           
/** @brief  Reports the UART clock source.
  * @param  __HANDLE__: specifies the UART Handle
  * @param  __CLOCKSOURCE__ : output variable   
  * @retval UART clocking source, written in __CLOCKSOURCE__.
  */
#if defined (STM32L031xx) || defined (STM32L041xx)
#define UART_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__)       \
  do {                                                        \
    if((__HANDLE__)->Instance == USART2)                      \
    {                                                         \
       switch(__HAL_RCC_GET_USART2_SOURCE())                  \
       {                                                      \
        case RCC_USART2CLKSOURCE_PCLK1:                       \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;         \
          break;                                              \
        case RCC_USART2CLKSOURCE_HSI:                         \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_HSI;           \
          break;                                              \
        case RCC_USART2CLKSOURCE_SYSCLK:                      \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_SYSCLK;        \
          break;                                              \
        case RCC_USART2CLKSOURCE_LSE:                         \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_LSE;           \
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
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;         \
          break;                                              \
        case RCC_LPUART1CLKSOURCE_HSI:                        \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_HSI;           \
          break;                                              \
        case RCC_LPUART1CLKSOURCE_SYSCLK:                     \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_SYSCLK;        \
          break;                                              \
        case RCC_LPUART1CLKSOURCE_LSE:                        \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_LSE;           \
          break;                                              \
        default:                                              \
          break;                                              \
       }                                                      \
    }                                                         \
  } while(0)

#else /* (STM32L031xx) || defined (STM32L041xx) */

#define UART_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__)       \
  do {                                                        \
    if((__HANDLE__)->Instance == USART1)                      \
    {                                                         \
       switch(__HAL_RCC_GET_USART1_SOURCE())                  \
       {                                                      \
        case RCC_USART1CLKSOURCE_PCLK2:                       \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK2;         \
          break;                                              \
        case RCC_USART1CLKSOURCE_HSI:                         \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_HSI;           \
          break;                                              \
        case RCC_USART1CLKSOURCE_SYSCLK:                      \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_SYSCLK;        \
          break;                                              \
        case RCC_USART1CLKSOURCE_LSE:                         \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_LSE;           \
          break;                                              \
        default:                                              \
          break;                                              \
       }                                                      \
    }                                                         \
    else if((__HANDLE__)->Instance == USART2)                 \
    {                                                         \
       switch(__HAL_RCC_GET_USART2_SOURCE())                  \
       {                                                      \
        case RCC_USART2CLKSOURCE_PCLK1:                       \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;         \
          break;                                              \
        case RCC_USART2CLKSOURCE_HSI:                         \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_HSI;           \
          break;                                              \
        case RCC_USART2CLKSOURCE_SYSCLK:                      \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_SYSCLK;        \
          break;                                              \
        case RCC_USART2CLKSOURCE_LSE:                         \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_LSE;           \
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
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;         \
          break;                                              \
        case RCC_LPUART1CLKSOURCE_HSI:                        \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_HSI;           \
          break;                                              \
        case RCC_LPUART1CLKSOURCE_SYSCLK:                     \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_SYSCLK;        \
          break;                                              \
        case RCC_LPUART1CLKSOURCE_LSE:                        \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_LSE;           \
          break;                                              \
        default:                                              \
          break;                                              \
       }                                                      \
    }                                                         \
  } while(0)
#endif /* (STM32L031xx) || (STM32L041xx) */

/** @brief  Reports the UART mask to apply to retrieve the received data
  *         according to the word length and to the parity bits activation.
  *         If PCE = 1, the parity bit is not included in the data extracted
  *         by the reception API().
  *         This masking operation is not carried out in the case of
  *         DMA transfers.        
  * @param  __HANDLE__: specifies the UART Handle
  * @retval mask to apply to UART RDR register value.
  */
#define UART_MASK_COMPUTATION(__HANDLE__)                             \
  do {                                                                \
  if ((__HANDLE__)->Init.WordLength == UART_WORDLENGTH_9B)            \
  {                                                                   \
     if ((__HANDLE__)->Init.Parity == UART_PARITY_NONE)               \
     {                                                                \
        (__HANDLE__)->Mask = 0x01FF ;                                 \
     }                                                                \
     else                                                             \
     {                                                                \
        (__HANDLE__)->Mask = 0x00FF ;                                 \
     }                                                                \
  }                                                                   \
  else if ((__HANDLE__)->Init.WordLength == UART_WORDLENGTH_8B)       \
  {                                                                   \
     if ((__HANDLE__)->Init.Parity == UART_PARITY_NONE)               \
     {                                                                \
        (__HANDLE__)->Mask = 0x00FF ;                                 \
     }                                                                \
     else                                                             \
     {                                                                \
        (__HANDLE__)->Mask = 0x007F ;                                 \
     }                                                                \
  }                                                                   \
  else if ((__HANDLE__)->Init.WordLength == UART_WORDLENGTH_7B)       \
  {                                                                   \
     if ((__HANDLE__)->Init.Parity == UART_PARITY_NONE)               \
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
/** @defgroup UARTEx_Exported_Functions UARTEx Exported Functions
  * @{
  */
/* Exported functions --------------------------------------------------------*/
/* Initialization/de-initialization functions  ********************************/
/** @defgroup UARTEx_Exported_Functions_Group1 Extended Initialization function
  * @{
  */
HAL_StatusTypeDef HAL_RS485Ex_Init(UART_HandleTypeDef *huart, uint32_t Polarity, uint32_t AssertionTime, uint32_t DeassertionTime);
/**
  * @}
  */
/* IO operation functions *****************************************************/
/* Peripheral Control functions  **********************************************/
/** @defgroup UARTEx_Exported_Functions_Group2 Peripheral Control functions
  * @{
  */
HAL_StatusTypeDef HAL_UARTEx_StopModeWakeUpSourceConfig(UART_HandleTypeDef *huart, UART_WakeUpTypeDef WakeUpSelection);
HAL_StatusTypeDef HAL_UARTEx_EnableStopMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UARTEx_EnableClockStopMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UARTEx_DisableStopMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UARTEx_DisableClockStopMode(UART_HandleTypeDef *huart);
void HAL_UARTEx_WakeupCallback(UART_HandleTypeDef *huart);

/* Peripheral State functions  ************************************************/
HAL_StatusTypeDef HAL_MultiProcessorEx_AddressLength_Set(UART_HandleTypeDef *huart, uint32_t AddressLength);
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

/**
  * @}
  */ 
  
#ifdef __cplusplus
}
#endif

#endif /* __STM32L0xx_HAL_UART_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

