/**
  ******************************************************************************
  * @file    stm32f0xx_hal_uart_ex.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    11-December-2014
  * @brief   Header file of UART HAL Extension module.
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
#ifndef __STM32F0xx_HAL_UART_EX_H
#define __STM32F0xx_HAL_UART_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal_def.h"

/** @addtogroup STM32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup UARTEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
#if !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6)  && !defined(STM32F070xB)  && !defined(STM32F030xC)
/** @defgroup UARTEx_Exported_Types UARTEx Exported Types
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
                                    This parameter can be a value of @ref UART_WakeUp_Address_Length  */
                                           
  uint8_t Address;             /*!< UART/USART node address (7-bit long max) */
} UART_WakeUpTypeDef;
/**
  * @}
  */
#endif /* !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6)  && !defined(STM32F070xB)  && !defined(STM32F030xC) */  

/* Exported constants --------------------------------------------------------*/
/** @defgroup UARTEx_Exported_Constants UARTEx Exported Constants
  * @{
  */
  
/** @defgroup UARTEx_Word_Length UARTEx Word Length
  * @{
  */
#if defined (STM32F042x6) || defined (STM32F048xx) || defined (STM32F070x6) || \
    defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || defined (STM32F070xB) || \
    defined (STM32F091xC) || defined (STM32F098xx) || defined (STM32F030xC)
#define UART_WORDLENGTH_7B                  ((uint32_t)USART_CR1_M1)
#define UART_WORDLENGTH_8B                  ((uint32_t)0x00000000)
#define UART_WORDLENGTH_9B                  ((uint32_t)USART_CR1_M0)
#define IS_UART_WORD_LENGTH(LENGTH) (((LENGTH) == UART_WORDLENGTH_7B) || \
                                     ((LENGTH) == UART_WORDLENGTH_8B) || \
                                     ((LENGTH) == UART_WORDLENGTH_9B))
#else
#define UART_WORDLENGTH_8B                  ((uint32_t)0x00000000)
#define UART_WORDLENGTH_9B                  ((uint32_t)USART_CR1_M)
#define IS_UART_WORD_LENGTH(LENGTH) (((LENGTH) == UART_WORDLENGTH_8B) || \
                                     ((LENGTH) == UART_WORDLENGTH_9B))
#endif /* defined (STM32F042x6) || defined (STM32F048xx) || defined (STM32F070x6) || \
          defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || defined (STM32F070xB) || \
          defined (STM32F091xC) || defined (STM32F098xx) || defined (STM32F030xC) */
/**
  * @}
  */

/** @defgroup UARTEx_AutoBaud_Rate_Mode    UARTEx Advanced Feature AutoBaud Rate Mode
  * @{
  */
#if defined (STM32F042x6) || defined (STM32F048xx) || defined (STM32F070x6) || \
    defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || defined (STM32F070xB) || \
    defined (STM32F091xC) || defined (STM32F098xx) || defined (STM32F030xC)
#define UART_ADVFEATURE_AUTOBAUDRATE_ONSTARTBIT    ((uint32_t)0x0000)
#define UART_ADVFEATURE_AUTOBAUDRATE_ONFALLINGEDGE ((uint32_t)USART_CR2_ABRMODE_0)
#define UART_ADVFEATURE_AUTOBAUDRATE_ON0X7FFRAME   ((uint32_t)USART_CR2_ABRMODE_1)
#define UART_ADVFEATURE_AUTOBAUDRATE_ON0X55FRAME   ((uint32_t)USART_CR2_ABRMODE)
#define IS_UART_ADVFEATURE_AUTOBAUDRATEMODE(MODE)  (((MODE) == UART_ADVFEATURE_AUTOBAUDRATE_ONSTARTBIT) || \
                                                    ((MODE) == UART_ADVFEATURE_AUTOBAUDRATE_ONFALLINGEDGE) || \
                                                    ((MODE) == UART_ADVFEATURE_AUTOBAUDRATE_ON0X7FFRAME) || \
                                                    ((MODE) == UART_ADVFEATURE_AUTOBAUDRATE_ON0X55FRAME))
#else
#define UART_ADVFEATURE_AUTOBAUDRATE_ONSTARTBIT    ((uint32_t)0x0000)
#define UART_ADVFEATURE_AUTOBAUDRATE_ONFALLINGEDGE ((uint32_t)USART_CR2_ABRMODE_0)
#define IS_UART_ADVFEATURE_AUTOBAUDRATEMODE(MODE)  (((MODE) == UART_ADVFEATURE_AUTOBAUDRATE_ONSTARTBIT) || \
                                                    ((MODE) == UART_ADVFEATURE_AUTOBAUDRATE_ONFALLINGEDGE))
#endif /* defined (STM32F042x6) || defined (STM32F048xx) || defined (STM32F070x6) || \
          defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || defined (STM32F070xB) || \
          defined (STM32F091xC) || defined (STM32F098xx) || defined (STM32F030xC) */
/**
  * @}
  */  
  

#if !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6)  && !defined(STM32F070xB)  && !defined(STM32F030xC)
/** @defgroup UARTEx_LIN    UARTEx Local Interconnection Network mode
  * @{
  */
#define UART_LIN_DISABLE            ((uint32_t)0x00000000)
#define UART_LIN_ENABLE             ((uint32_t)USART_CR2_LINEN)
#define IS_UART_LIN(LIN)            (((LIN) == UART_LIN_DISABLE) || \
                                     ((LIN) == UART_LIN_ENABLE))
/**
  * @}
  */ 
  
/** @defgroup UARTEx_LIN_Break_Detection  UARTEx LIN Break Detection
  * @{
  */
#define UART_LINBREAKDETECTLENGTH_10B            ((uint32_t)0x00000000)
#define UART_LINBREAKDETECTLENGTH_11B            ((uint32_t)USART_CR2_LBDL)
#define IS_UART_LIN_BREAK_DETECT_LENGTH(LENGTH) (((LENGTH) == UART_LINBREAKDETECTLENGTH_10B) || \
                                                 ((LENGTH) == UART_LINBREAKDETECTLENGTH_11B))
/**
  * @}
  */   
#endif /* !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6)  && !defined(STM32F070xB)  && !defined(STM32F030xC) */  

/** @defgroup UART_Flags     UARTEx Status Flags
  *        Elements values convention: 0xXXXX
  *           - 0xXXXX  : Flag mask in the ISR register
  * @{
  */
#define UART_FLAG_REACK                     ((uint32_t)0x00400000)
#define UART_FLAG_TEACK                     ((uint32_t)0x00200000)
#if !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6)  && !defined(STM32F070xB)  && !defined(STM32F030xC)
#define UART_FLAG_WUF                       ((uint32_t)0x00100000)
#endif /* !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6)  && !defined(STM32F070xB)  && !defined(STM32F030xC) */ 
#define UART_FLAG_RWU                       ((uint32_t)0x00080000)
#define UART_FLAG_SBKF                      ((uint32_t)0x00040000
#define UART_FLAG_CMF                       ((uint32_t)0x00020000)
#define UART_FLAG_BUSY                      ((uint32_t)0x00010000)
#define UART_FLAG_ABRF                      ((uint32_t)0x00008000)  
#define UART_FLAG_ABRE                      ((uint32_t)0x00004000)
#if !defined(STM32F030x6) && !defined(STM32F030x8)
#define UART_FLAG_EOBF                      ((uint32_t)0x00001000)
#endif /* !defined(STM32F030x6) && !defined(STM32F030x8) */ 
#define UART_FLAG_RTOF                      ((uint32_t)0x00000800)
#define UART_FLAG_CTS                       ((uint32_t)0x00000400)
#define UART_FLAG_CTSIF                     ((uint32_t)0x00000200)
#if !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6)  && !defined(STM32F070xB)  && !defined(STM32F030xC)
#define UART_FLAG_LBDF                      ((uint32_t)0x00000100)
#endif /* !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6)  && !defined(STM32F070xB)  && !defined(STM32F030xC) */ 
#define UART_FLAG_TXE                       ((uint32_t)0x00000080)
#define UART_FLAG_TC                        ((uint32_t)0x00000040)
#define UART_FLAG_RXNE                      ((uint32_t)0x00000020)
#define UART_FLAG_IDLE                      ((uint32_t)0x00000010)
#define UART_FLAG_ORE                       ((uint32_t)0x00000008)
#define UART_FLAG_NE                        ((uint32_t)0x00000004)
#define UART_FLAG_FE                        ((uint32_t)0x00000002)
#define UART_FLAG_PE                        ((uint32_t)0x00000001)
/**
  * @}
  */

/** @defgroup UART_Interrupt_definition   UARTEx Interrupts Definition
  *        Elements values convention: 0000ZZZZZ0XXYYYYYb
  *           - YYYYY  : Interrupt source position in the XX register (5bits)
  *           - XX  : Interrupt source register (2bits)
  *                 - 01: CR1 register
  *                 - 10: CR2 register
  *                 - 11: CR3 register
  *           - ZZZZZ  : Flag position in the ISR register(5bits)
  * @{   
  */  
#define UART_IT_PE                          ((uint16_t)0x0028)
#define UART_IT_TXE                         ((uint16_t)0x0727)
#define UART_IT_TC                          ((uint16_t)0x0626)
#define UART_IT_RXNE                        ((uint16_t)0x0525)
#define UART_IT_IDLE                        ((uint16_t)0x0424)
#if !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6)  && !defined(STM32F070xB)  && !defined(STM32F030xC) 
#define UART_IT_LBD                         ((uint16_t)0x0846)
#endif /* !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6)  && !defined(STM32F070xB)  && !defined(STM32F030xC) */ 
#define UART_IT_CTS                         ((uint16_t)0x096A)
#define UART_IT_CM                          ((uint16_t)0x112E)
#if !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6)  && !defined(STM32F070xB)  && !defined(STM32F030xC) 
#define UART_IT_WUF                         ((uint16_t)0x1476)
#endif /* !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6)  && !defined(STM32F070xB)  && !defined(STM32F030xC) */ 
/**
  * @}
  */


/** @defgroup UART_IT_CLEAR_Flags  UARTEx Interruption Clear Flags
  * @{
  */
#define UART_CLEAR_PEF                       USART_ICR_PECF            /*!< Parity Error Clear Flag */          
#define UART_CLEAR_FEF                       USART_ICR_FECF            /*!< Framing Error Clear Flag */         
#define UART_CLEAR_NEF                       USART_ICR_NCF             /*!< Noise detected Clear Flag */        
#define UART_CLEAR_OREF                      USART_ICR_ORECF           /*!< OverRun Error Clear Flag */         
#define UART_CLEAR_IDLEF                     USART_ICR_IDLECF          /*!< IDLE line detected Clear Flag */    
#define UART_CLEAR_TCF                       USART_ICR_TCCF            /*!< Transmission Complete Clear Flag */ 
#if !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6)  && !defined(STM32F070xB)  && !defined(STM32F030xC)
#define UART_CLEAR_LBDF                      USART_ICR_LBDCF           /*!< LIN Break Detection Clear Flag (not available on F030xx devices)*/
#endif /* !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6)  && !defined(STM32F070xB)  && !defined(STM32F030xC) */    
#define UART_CLEAR_CTSF                      USART_ICR_CTSCF           /*!< CTS Interrupt Clear Flag */         
#define UART_CLEAR_RTOF                      USART_ICR_RTOCF           /*!< Receiver Time Out Clear Flag */     
#define UART_CLEAR_EOBF                      USART_ICR_EOBCF           /*!< End Of Block Clear Flag */          
#define UART_CLEAR_CMF                       USART_ICR_CMCF            /*!< Character Match Clear Flag */  
#if !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6)  && !defined(STM32F070xB)  && !defined(STM32F030xC)      
#define UART_CLEAR_WUF                       USART_ICR_WUCF            /*!< Wake Up from stop mode Clear Flag */
#endif /* !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6)  && !defined(STM32F070xB)  && !defined(STM32F030xC) */ 
/**
  * @}
  */ 

/** @defgroup UART_Request_Parameters UARTEx Request Parameters
  * @{
  */
#define UART_AUTOBAUD_REQUEST            ((uint32_t)USART_RQR_ABRRQ)        /*!< Auto-Baud Rate Request */     
#define UART_SENDBREAK_REQUEST           ((uint32_t)USART_RQR_SBKRQ)        /*!< Send Break Request */         
#define UART_MUTE_MODE_REQUEST           ((uint32_t)USART_RQR_MMRQ)         /*!< Mute Mode Request */          
#define UART_RXDATA_FLUSH_REQUEST        ((uint32_t)USART_RQR_RXFRQ)        /*!< Receive Data flush Request */ 
#if !defined(STM32F030x6) && !defined(STM32F030x8) 
#define UART_TXDATA_FLUSH_REQUEST        ((uint32_t)USART_RQR_TXFRQ)        /*!< Transmit data flush Request */
#define IS_UART_REQUEST_PARAMETER(PARAM) (((PARAM) == UART_AUTOBAUD_REQUEST) || \
                                          ((PARAM) == UART_SENDBREAK_REQUEST) || \
                                          ((PARAM) == UART_MUTE_MODE_REQUEST) || \
                                          ((PARAM) == UART_RXDATA_FLUSH_REQUEST) || \
                                          ((PARAM) == UART_TXDATA_FLUSH_REQUEST))   
#else
#define IS_UART_REQUEST_PARAMETER(PARAM) (((PARAM) == UART_AUTOBAUD_REQUEST) || \
                                          ((PARAM) == UART_SENDBREAK_REQUEST) || \
                                          ((PARAM) == UART_MUTE_MODE_REQUEST) || \
                                          ((PARAM) == UART_RXDATA_FLUSH_REQUEST))  
#endif /* !defined(STM32F030x6) && !defined(STM32F030x8) */ 
/**
  * @}
  */
  
#if !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6) && !defined(STM32F070xB)  && !defined(STM32F030xC)
/** @defgroup UART_Stop_Mode_Enable   UARTEx Advanced Feature Stop Mode Enable
  * @{
  */
#define UART_ADVFEATURE_STOPMODE_DISABLE      ((uint32_t)0x00000000)
#define UART_ADVFEATURE_STOPMODE_ENABLE       ((uint32_t)USART_CR1_UESM)
#define IS_UART_ADVFEATURE_STOPMODE(STOPMODE) (((STOPMODE) == UART_ADVFEATURE_STOPMODE_DISABLE) || \
                                               ((STOPMODE) == UART_ADVFEATURE_STOPMODE_ENABLE))
/**
  * @}
  */  
  
/** @defgroup UART_WakeUp_from_Stop_Selection   UART WakeUp From Stop Selection
  * @{
  */
#define UART_WAKEUP_ON_ADDRESS           ((uint32_t)0x0000)
#define UART_WAKEUP_ON_STARTBIT          ((uint32_t)USART_CR3_WUS_1)
#define UART_WAKEUP_ON_READDATA_NONEMPTY ((uint32_t)USART_CR3_WUS)
#define IS_UART_WAKEUP_SELECTION(WAKE)   (((WAKE) == UART_WAKEUP_ON_ADDRESS) || \
                                          ((WAKE) == UART_WAKEUP_ON_STARTBIT) || \
                                          ((WAKE) == UART_WAKEUP_ON_READDATA_NONEMPTY))
/**
  * @}
  */       
#endif /* !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6) && !defined(STM32F070xB) && !defined(STM32F030xC) */   
  
/**
  * @}
  */  
  
/* Exported macro ------------------------------------------------------------*/

/** @defgroup UARTEx_Exported_Macros UARTEx Exported Macros
  * @{
  */

/** @brief  Reports the UART clock source.
  * @param  __HANDLE__: specifies the UART Handle
  * @param  __CLOCKSOURCE__ : output variable   
  * @retval UART clocking source, written in __CLOCKSOURCE__.
  */


#if defined(STM32F030x6) || defined(STM32F031x6) || defined(STM32F038xx)
#define __HAL_UART_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                        \
     switch(__HAL_RCC_GET_USART1_SOURCE())                    \
     {                                                        \
      case RCC_USART1CLKSOURCE_PCLK1:                         \
        (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;           \
        break;                                                \
      case RCC_USART1CLKSOURCE_HSI:                           \
        (__CLOCKSOURCE__) = UART_CLOCKSOURCE_HSI;             \
        break;                                                \
      case RCC_USART1CLKSOURCE_SYSCLK:                        \
        (__CLOCKSOURCE__) = UART_CLOCKSOURCE_SYSCLK;          \
        break;                                                \
      case RCC_USART1CLKSOURCE_LSE:                           \
        (__CLOCKSOURCE__) = UART_CLOCKSOURCE_LSE;             \
        break;                                                \
      default:                                                \
        (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;       \
        break;                                                \
     }                                                        \
  } while(0) 
#elif defined (STM32F030x8) || defined (STM32F070x6) ||       \
      defined (STM32F042x6) || defined (STM32F048xx) ||       \
      defined (STM32F051x8) || defined (STM32F058xx)
#define __HAL_UART_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                        \
    if((__HANDLE__)->Instance == USART1)                      \
    {                                                         \
       switch(__HAL_RCC_GET_USART1_SOURCE())                  \
       {                                                      \
        case RCC_USART1CLKSOURCE_PCLK1:                       \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;         \
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
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;     \
          break;                                              \
       }                                                      \
    }                                                         \
    else if((__HANDLE__)->Instance == USART2)                 \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;             \
    }                                                         \
    else                                                      \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;         \
    }                                                         \
  } while(0) 
#elif defined(STM32F070xB)
#define __HAL_UART_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                        \
    if((__HANDLE__)->Instance == USART1)                      \
    {                                                         \
       switch(__HAL_RCC_GET_USART1_SOURCE())                  \
       {                                                      \
        case RCC_USART1CLKSOURCE_PCLK1:                       \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;         \
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
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;     \
          break;                                              \
       }                                                      \
    }                                                         \
    else if((__HANDLE__)->Instance == USART2)                 \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;             \
    }                                                         \
    else if((__HANDLE__)->Instance == USART3)                 \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;             \
    }                                                         \
    else if((__HANDLE__)->Instance == USART4)                 \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;             \
    }                                                         \
    else                                                      \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;         \
    }                                                         \
  } while(0)   
#elif defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx)
#define __HAL_UART_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                        \
    if((__HANDLE__)->Instance == USART1)                      \
    {                                                         \
       switch(__HAL_RCC_GET_USART1_SOURCE())                  \
       {                                                      \
        case RCC_USART1CLKSOURCE_PCLK1:                       \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;         \
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
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;     \
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
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;     \
          break;                                              \
       }                                                      \
    }                                                         \
    else if((__HANDLE__)->Instance == USART3)                 \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;             \
    }                                                         \
    else if((__HANDLE__)->Instance == USART4)                 \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;             \
    }                                                         \
    else                                                      \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;         \
    }                                                         \
  } while(0)   
#elif defined(STM32F091xC) || defined (STM32F098xx)
#define __HAL_UART_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                        \
    if((__HANDLE__)->Instance == USART1)                      \
    {                                                         \
       switch(__HAL_RCC_GET_USART1_SOURCE())                  \
       {                                                      \
        case RCC_USART1CLKSOURCE_PCLK1:                       \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;         \
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
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;     \
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
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;     \
          break;                                              \
       }                                                      \
    }                                                         \
    else if((__HANDLE__)->Instance == USART3)                 \
    {                                                         \
       switch(__HAL_RCC_GET_USART3_SOURCE())                  \
       {                                                      \
        case RCC_USART3CLKSOURCE_PCLK1:                       \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;         \
          break;                                              \
        case RCC_USART3CLKSOURCE_HSI:                         \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_HSI;           \
          break;                                              \
        case RCC_USART3CLKSOURCE_SYSCLK:                      \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_SYSCLK;        \
          break;                                              \
        case RCC_USART3CLKSOURCE_LSE:                         \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_LSE;           \
          break;                                              \
        default:                                              \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;     \
          break;                                              \
       }                                                      \
    }                                                         \
    else if((__HANDLE__)->Instance == USART4)                 \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;             \
    }                                                         \
    else if((__HANDLE__)->Instance == USART5)                 \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;             \
    }                                                         \
    else if((__HANDLE__)->Instance == USART6)                 \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;             \
    }                                                         \
    else if((__HANDLE__)->Instance == USART7)                 \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;             \
    }                                                         \
    else if((__HANDLE__)->Instance == USART8)                 \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;             \
    }                                                         \
    else                                                      \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;         \
    }                                                         \
  } while(0)
#elif defined(STM32F030xC)
#define __HAL_UART_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                        \
    if((__HANDLE__)->Instance == USART1)                      \
    {                                                         \
       switch(__HAL_RCC_GET_USART1_SOURCE())                  \
       {                                                      \
        case RCC_USART1CLKSOURCE_PCLK1:                       \
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;         \
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
          (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;     \
          break;                                              \
       }                                                      \
    }                                                         \
    else if((__HANDLE__)->Instance == USART2)                 \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;             \
    }                                                         \
    else if((__HANDLE__)->Instance == USART3)                 \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;             \
    }                                                         \
    else if((__HANDLE__)->Instance == USART4)                 \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;             \
    }                                                         \
    else if((__HANDLE__)->Instance == USART5)                 \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;             \
    }                                                         \
    else if((__HANDLE__)->Instance == USART6)                 \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_PCLK1;             \
    }                                                         \
    else                                                      \
    {                                                         \
      (__CLOCKSOURCE__) = UART_CLOCKSOURCE_UNDEFINED;         \
    }                                                         \
  } while(0)
  
#endif /* defined(STM32F030x6) || defined(STM32F031x6) || defined(STM32F038xx) */
  

/** @brief  Computes the UART mask to apply to retrieve the received data
  *         according to the word length and to the parity bits activation.
  *         If PCE = 1, the parity bit is not included in the data extracted
  *         by the reception API().
  *         This masking operation is not carried out in the case of
  *         DMA transfers.        
  * @param  __HANDLE__: specifies the UART Handle
  * @retval none
  */  
#if defined (STM32F042x6) || defined (STM32F048xx) || defined (STM32F070x6) || \
    defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || defined (STM32F070xB) || \
    defined (STM32F091xC) || defined (STM32F098xx) || defined (STM32F030xC)
#define __HAL_UART_MASK_COMPUTATION(__HANDLE__)                       \
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
#else
#define __HAL_UART_MASK_COMPUTATION(__HANDLE__)                       \
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
} while(0) 
#endif /* defined (STM32F042x6) || defined (STM32F048xx) || defined (STM32F070x6) || \
          defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || defined (STM32F070xB) || \
          defined (STM32F091xC) || defined (STM32F098xx) || defined (STM32F030xC)  */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup UARTEx_Exported_Functions
  * @{
  */

/** @addtogroup UARTEx_Exported_Functions_Group1
  * @brief    Extended Initialization and Configuration Functions
  * @{
  */
/* Initialization and de-initialization functions  ****************************/
#if !defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070xB)&& !defined(STM32F070x6)&& !defined(STM32F030xC)
HAL_StatusTypeDef HAL_RS485Ex_Init(UART_HandleTypeDef *huart, uint32_t UART_DEPolarity, uint32_t UART_DEAssertionTime, uint32_t UART_DEDeassertionTime);
HAL_StatusTypeDef HAL_LIN_Init(UART_HandleTypeDef *huart, uint32_t BreakDetectLength);
#endif /* !defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070xB)&& !defined(STM32F070x6)&& !defined(STM32F030xC) */ 
/**
  * @}
  */

/** @addtogroup UARTEx_Exported_Functions_Group2
  * @brief    Extended UART Interrupt handling function
  * @{
  */
  
/* IO operation functions  ***************************************************/
void HAL_UART_IRQHandler(UART_HandleTypeDef *huart);

#if !defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070xB)&& !defined(STM32F070x6)&& !defined(STM32F030xC)
void HAL_UART_WakeupCallback(UART_HandleTypeDef *huart);
#endif /* !defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070xB)&& !defined(STM32F070x6)&& !defined(STM32F030xC) */ 
/**
  * @}
  */

/** @addtogroup UARTEx_Exported_Functions_Group3
  * @brief    Extended Peripheral Control functions
  * @{
  */

/* Peripheral Control functions  **********************************************/
HAL_StatusTypeDef HAL_MultiProcessorEx_AddressLength_Set(UART_HandleTypeDef *huart, uint32_t AddressLength);
#if !defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070xB)&& !defined(STM32F070x6) && !defined(STM32F030xC)
HAL_StatusTypeDef HAL_UARTEx_StopModeWakeUpSourceConfig(UART_HandleTypeDef *huart, UART_WakeUpTypeDef WakeUpSelection);
HAL_StatusTypeDef HAL_UARTEx_EnableStopMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UARTEx_DisableStopMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_LIN_SendBreak(UART_HandleTypeDef *huart);
#endif /* !defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070xB)&& !defined(STM32F070x6)&& !defined(STM32F030xC) */ 
/**
  * @}
  */
/* Peripheral State functions  ************************************************/

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

#endif /* __STM32F0xx_HAL_UART_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

