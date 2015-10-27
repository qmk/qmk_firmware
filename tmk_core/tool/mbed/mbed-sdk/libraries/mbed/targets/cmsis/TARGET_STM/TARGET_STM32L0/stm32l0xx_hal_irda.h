/**
  ******************************************************************************
  * @file    stm32l0xx_hal_irda.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   Header file of IRDA HAL module.
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
#ifndef __STM32L0xx_HAL_IRDA_H
#define __STM32L0xx_HAL_IRDA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup IRDA IRDA
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 

/** 
  * @brief IRDA Init Structure definition  
  */ 
typedef struct
{
  uint32_t BaudRate;                  /*!< This member configures the IRDA communication baud rate.
                                           The baud rate register is computed using the following formula:
                                              Baud Rate Register = ((PCLKx) / ((hirda->Init.BaudRate))) */

  uint32_t WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref IRDAEx_Word_Length */

  uint32_t Parity;                    /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref IRDA_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                 word length is set to 8 data bits). */
 
  uint16_t Mode;                      /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref IRDA_Mode */
  
  uint8_t  Prescaler;                 /*!< Specifies the Prescaler value for dividing the UART/USART source clock
                                           to achieve low-power frequency.
                                           @note Prescaler value 0 is forbidden */
  
  uint16_t PowerMode;                 /*!< Specifies the IRDA power mode.
                                           This parameter can be a value of @ref IRDA_Low_Power */
}IRDA_InitTypeDef;

/** 
  * @brief HAL IRDA State structures definition  
  */ 
typedef enum
{
  HAL_IRDA_STATE_RESET             = 0x00,    /*!< Peripheral is not yet Initialized */
  HAL_IRDA_STATE_READY             = 0x01,    /*!< Peripheral Initialized and ready for use */
  HAL_IRDA_STATE_BUSY              = 0x02,    /*!< an internal process is ongoing */
  HAL_IRDA_STATE_BUSY_TX           = 0x12,    /*!< Data Transmission process is ongoing */
  HAL_IRDA_STATE_BUSY_RX           = 0x22,    /*!< Data Reception process is ongoing */
  HAL_IRDA_STATE_BUSY_TX_RX        = 0x32,    /*!< Data Transmission and Reception process is ongoing */
  HAL_IRDA_STATE_TIMEOUT           = 0x03,    /*!< Timeout state */
  HAL_IRDA_STATE_ERROR             = 0x04     /*!< Error */
}HAL_IRDA_StateTypeDef;

/** 
  * @brief  HAL IRDA Error Code definition
  */ 

#define  HAL_IRDA_ERROR_NONE      ((uint32_t)0x00)    /*!< No error            */
#define  HAL_IRDA_ERROR_PE        ((uint32_t)0x01)    /*!< Parity error        */
#define  HAL_IRDA_ERROR_NE        ((uint32_t)0x02)    /*!< Noise error         */
#define  HAL_IRDA_ERROR_FE        ((uint32_t)0x04)    /*!< frame error         */
#define  HAL_IRDA_ERROR_ORE       ((uint32_t)0x08)    /*!< Overrun error       */
#define  HAL_IRDA_ERROR_DMA       ((uint32_t)0x10)     /*!< DMA transfer error  */

/**
  * @brief IRDA clock sources definition
  */
typedef enum
{
  IRDA_CLOCKSOURCE_PCLK1      = 0x00,    /*!< PCLK1 clock source  */
  IRDA_CLOCKSOURCE_PCLK2      = 0x01,    /*!< PCLK2 clock source  */
  IRDA_CLOCKSOURCE_HSI        = 0x02,    /*!< HSI clock source    */
  IRDA_CLOCKSOURCE_SYSCLK     = 0x04,    /*!< SYSCLK clock source */
  IRDA_CLOCKSOURCE_LSE        = 0x08     /*!< LSE clock source     */
}IRDA_ClockSourceTypeDef;

/** 
  * @brief  IRDA handle Structure definition  
  */
typedef struct
{
  USART_TypeDef            *Instance;        /* IRDA registers base address        */

  IRDA_InitTypeDef         Init;             /* IRDA communication parameters      */

  uint8_t                  *pTxBuffPtr;      /* Pointer to IRDA Tx transfer Buffer */

  uint16_t                 TxXferSize;       /* IRDA Tx Transfer size              */

  uint16_t                 TxXferCount;      /* IRDA Tx Transfer Counter           */

  uint8_t                  *pRxBuffPtr;      /* Pointer to IRDA Rx transfer Buffer */

  uint16_t                 RxXferSize;       /* IRDA Rx Transfer size              */

  uint16_t                 RxXferCount;      /* IRDA Rx Transfer Counter           */

  uint16_t                 Mask;             /* IRDA RX RDR register mask         */

  DMA_HandleTypeDef        *hdmatx;          /* IRDA Tx DMA Handle parameters      */

  DMA_HandleTypeDef        *hdmarx;          /* IRDA Rx DMA Handle parameters      */

  HAL_LockTypeDef          Lock;             /* Locking object                     */

  __IO HAL_IRDA_StateTypeDef    State;       /* IRDA communication state           */

  __IO uint32_t           ErrorCode;         /* IRDA Error code                    */

}IRDA_HandleTypeDef;

/** 
  * @brief  IRDA Configuration enumeration values definition  
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup IRDA_Exported_Constants  IRDA Exported Constants
  * @{
  */

/** @defgroup IRDA_Parity IRDA Parity
  * @{
  */ 
#define IRDA_PARITY_NONE                    ((uint32_t)0x0000)
#define IRDA_PARITY_EVEN                    ((uint32_t)USART_CR1_PCE)
#define IRDA_PARITY_ODD                     ((uint32_t)(USART_CR1_PCE | USART_CR1_PS)) 
#define IS_IRDA_PARITY(PARITY) (((PARITY) == IRDA_PARITY_NONE) || \
                                ((PARITY) == IRDA_PARITY_EVEN) || \
                                ((PARITY) == IRDA_PARITY_ODD))
/**
  * @}
  */ 


/** @defgroup IRDA_Transfer_Mode IRDA transfer mode
  * @{
  */ 
#define IRDA_MODE_RX                        ((uint32_t)USART_CR1_RE)
#define IRDA_MODE_TX                        ((uint32_t)USART_CR1_TE)
#define IRDA_MODE_TX_RX                     ((uint32_t)(USART_CR1_TE |USART_CR1_RE))
#define IS_IRDA_TX_RX_MODE(MODE) ((((MODE) & (~((uint32_t)(IRDA_MODE_TX_RX)))) == (uint32_t)0x00) && ((MODE) != (uint32_t)0x00))
/**
  * @}
  */

/** @defgroup IRDA_Low_Power IRDA low power
  * @{
  */
#define IRDA_POWERMODE_NORMAL                    ((uint32_t)0x0000)
#define IRDA_POWERMODE_LOWPOWER                  ((uint32_t)USART_CR3_IRLP)
#define IS_IRDA_POWERMODE(MODE) (((MODE) == IRDA_POWERMODE_LOWPOWER) || \
                                 ((MODE) == IRDA_POWERMODE_NORMAL))
/**
  * @}
  */
    
 /** @defgroup IRDA_State IRDA State
  * @{
  */ 
#define IRDA_STATE_DISABLE                  ((uint32_t)0x0000)
#define IRDA_STATE_ENABLE                   ((uint32_t)USART_CR1_UE)
#define IS_IRDA_STATE(STATE) (((STATE) == IRDA_STATE_DISABLE) || \
                              ((STATE) == IRDA_STATE_ENABLE))
/**
  * @}
  */

 /** @defgroup IRDA_Mode IRDA Mode
  * @{
  */ 
#define IRDA_MODE_DISABLE                  ((uint32_t)0x0000)
#define IRDA_MODE_ENABLE                   ((uint32_t)USART_CR3_IREN)
#define IS_IRDA_MODE(STATE)  (((STATE) == IRDA_MODE_DISABLE) || \
                              ((STATE) == IRDA_MODE_ENABLE))
/**
  * @}
  */

/** @defgroup IRDA_One_Bit IRDA One bit
  * @{
  */
#define IRDA_ONE_BIT_SAMPLE_DISABLE          ((uint32_t)0x00000000)
#define IRDA_ONE_BIT_SAMPLE_ENABLE           ((uint32_t)USART_CR3_ONEBIT)
#define IS_IRDA_ONE_BIT_SAMPLE(ONEBIT)         (((ONEBIT) == IRDA_ONE_BIT_SAMPLE_DISABLE) || \
                                                  ((ONEBIT) == IRDA_ONE_BIT_SAMPLE_ENABLE))
/**
  * @}
  */  
  
/** @defgroup IRDA_DMA_Tx IRDA DMA TX
  * @{
  */
#define IRDA_DMA_TX_DISABLE          ((uint32_t)0x00000000)
#define IRDA_DMA_TX_ENABLE           ((uint32_t)USART_CR3_DMAT)
#define IS_IRDA_DMA_TX(DMATX)         (((DMATX) == IRDA_DMA_TX_DISABLE) || \
                                       ((DMATX) == IRDA_DMA_TX_ENABLE))
/**
  * @}
  */  
  
/** @defgroup IRDA_DMA_Rx IRDA DMA RX
  * @{
  */
#define IRDA_DMA_RX_DISABLE           ((uint32_t)0x0000)
#define IRDA_DMA_RX_ENABLE            ((uint32_t)USART_CR3_DMAR)
#define IS_IRDA_DMA_RX(DMARX)         (((DMARX) == IRDA_DMA_RX_DISABLE) || \
                                       ((DMARX) == IRDA_DMA_RX_ENABLE))
/**
  * @}
  */
  
/** @defgroup IRDA_Flags IRDA Flags
  *        Elements values convention: 0xXXXX
  *           - 0xXXXX  : Flag mask in the ISR register
  * @{
  */
#define IRDA_FLAG_REACK                     ((uint32_t)0x00400000)
#define IRDA_FLAG_TEACK                     ((uint32_t)0x00200000)  
#define IRDA_FLAG_BUSY                      ((uint32_t)0x00010000)
#define IRDA_FLAG_ABRF                      ((uint32_t)0x00008000)  
#define IRDA_FLAG_ABRE                      ((uint32_t)0x00004000)
#define IRDA_FLAG_TXE                       ((uint32_t)0x00000080)
#define IRDA_FLAG_TC                        ((uint32_t)0x00000040)
#define IRDA_FLAG_RXNE                      ((uint32_t)0x00000020)
#define IRDA_FLAG_ORE                       ((uint32_t)0x00000008)
#define IRDA_FLAG_NE                        ((uint32_t)0x00000004)
#define IRDA_FLAG_FE                        ((uint32_t)0x00000002)
#define IRDA_FLAG_PE                        ((uint32_t)0x00000001)
/**
  * @}
  */ 

/** @defgroup IRDA_Interrupt_definition IRDA Interrupt definition
  *        Elements values convention: 0000ZZZZ0XXYYYYYb
  *           - YYYYY  : Interrupt source position in the XX register (5bits)
  *           - XX  : Interrupt source register (2bits)
  *                 - 01: CR1 register
  *                 - 10: CR2 register
  *                 - 11: CR3 register
  *           - ZZZZ  : Flag position in the ISR register(4bits)
  * @{   
  */  
#define IRDA_IT_PE                          ((uint16_t)0x0028)
#define IRDA_IT_TXE                         ((uint16_t)0x0727)
#define IRDA_IT_TC                          ((uint16_t)0x0626)
#define IRDA_IT_RXNE                        ((uint16_t)0x0525)
#define IRDA_IT_IDLE                        ((uint16_t)0x0424)


                                
/**       Elements values convention: 000000000XXYYYYYb
  *           - YYYYY  : Interrupt source position in the XX register (5bits)
  *           - XX  : Interrupt source register (2bits)
  *                 - 01: CR1 register
  *                 - 10: CR2 register
  *                 - 11: CR3 register
  */
#define IRDA_IT_ERR                         ((uint16_t)0x0060)

/**       Elements values convention: 0000ZZZZ00000000b
  *           - ZZZZ  : Flag position in the ISR register(4bits)
  */
#define IRDA_IT_ORE                         ((uint16_t)0x0300)
#define IRDA_IT_NE                          ((uint16_t)0x0200)
#define IRDA_IT_FE                          ((uint16_t)0x0100)
/**
  * @}
  */
  
/** @defgroup IRDA_IT_CLEAR_Flags IRDA Interrupt clear flag
  * @{
  */
#define IRDA_CLEAR_PEF                       USART_ICR_PECF            /*!< Parity Error Clear Flag */          
#define IRDA_CLEAR_FEF                       USART_ICR_FECF            /*!< Framing Error Clear Flag */         
#define IRDA_CLEAR_NEF                       USART_ICR_NCF             /*!< Noise detected Clear Flag */        
#define IRDA_CLEAR_OREF                      USART_ICR_ORECF           /*!< OverRun Error Clear Flag */         
#define IRDA_CLEAR_TCF                       USART_ICR_TCCF            /*!< Transmission Complete Clear Flag */
#define IRDA_CLEAR_IDLEF                     USART_ICR_IDLECF          /*!< IDLE line detected Clear Flag */
/**
  * @}
  */ 



/** @defgroup IRDA_Request_Parameters IRDA Request parameters
  * @{
  */
#define IRDA_AUTOBAUD_REQUEST            ((uint32_t)USART_RQR_ABRRQ)        /*!< Auto-Baud Rate Request */
#define IRDA_RXDATA_FLUSH_REQUEST        ((uint32_t)USART_RQR_RXFRQ)        /*!< Receive Data flush Request */
#define IRDA_TXDATA_FLUSH_REQUEST        ((uint32_t)USART_RQR_TXFRQ)        /*!< Transmit data flush Request */
#define IS_IRDA_REQUEST_PARAMETER(PARAM) (((PARAM) == IRDA_AUTOBAUD_REQUEST) || \
                                          ((PARAM) == IRDA_SENDBREAK_REQUEST) || \
                                          ((PARAM) == IRDA_MUTE_MODE_REQUEST) || \
                                          ((PARAM) == IRDA_RXDATA_FLUSH_REQUEST) || \
                                          ((PARAM) == IRDA_TXDATA_FLUSH_REQUEST))   
/**
  * @}
  */
  
/** @defgroup IRDA_Interruption_Mask IRDA Interruption mask
  * @{
  */ 
#define IRDA_IT_MASK  ((uint16_t)0x001F)  
/**
  * @}
  */
  
/**
 * @}
 */

  
/* Exported macro ------------------------------------------------------------*/
/** @defgroup IRDA_Exported_Macros IRDA Exported Macros
  * @{
  */

/** @brief Reset IRDA handle state
  * @param  __HANDLE__: specifies the IRDA Handle.
  *         The Handle Instance which can be USART1 or USART2.
  * @retval None
  */
#define __HAL_IRDA_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_IRDA_STATE_RESET)

/** @brief  Flushs the IRDA DR register
  * @param  __HANDLE__: specifies the IRDA Handle.
  *         The Handle Instance which can be USART1 or USART2.
  * @retval None
  */
#define __HAL_IRDA_FLUSH_DRREGISTER(__HANDLE__)                            \
    do{                                                                    \
         SET_BIT((__HANDLE__)->Instance->RQR, IRDA_RXDATA_FLUSH_REQUEST); \
         SET_BIT((__HANDLE__)->Instance->RQR, IRDA_TXDATA_FLUSH_REQUEST); \
      } while(0)


/** @brief  Clears the specified IRDA pending flag.
  * @param  __HANDLE__: specifies the IRDA Handle.
  * @param  __FLAG__: specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg IRDA_CLEAR_PEF
  *            @arg IRDA_CLEAR_FEF
  *            @arg IRDA_CLEAR_NEF
  *            @arg IRDA_CLEAR_OREF
  *            @arg IRDA_CLEAR_TCF
  *            @arg IRDA_CLEAR_IDLEF
  * @retval None
  */
#define __HAL_IRDA_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->ICR = ~(__FLAG__))

/** @brief  Clear the IRDA PE pending flag.
  * @param  __HANDLE__: specifies the IRDA Handle.
  * @retval None
  */
#define __HAL_IRDA_CLEAR_PEFLAG(__HANDLE__)    __HAL_IRDA_CLEAR_FLAG(__HANDLE__, IRDA_CLEAR_PEF)


/** @brief  Clear the IRDA FE pending flag.
  * @param  __HANDLE__: specifies the IRDA Handle.
  * @retval None
  */
#define __HAL_IRDA_CLEAR_FEFLAG(__HANDLE__)    __HAL_IRDA_CLEAR_FLAG(__HANDLE__, IRDA_CLEAR_FEF)

/** @brief  Clear the IRDA NE pending flag.
  * @param  __HANDLE__: specifies the IRDA Handle.
  * @retval None
  */
#define __HAL_IRDA_CLEAR_NEFLAG(__HANDLE__)    __HAL_IRDA_CLEAR_FLAG(__HANDLE__, IRDA_CLEAR_NEF)

/** @brief  Clear the IRDA ORE pending flag.
  * @param  __HANDLE__: specifies the IRDA Handle.
  * @retval None
  */
#define __HAL_IRDA_CLEAR_OREFLAG(__HANDLE__)    __HAL_IRDA_CLEAR_FLAG(__HANDLE__, IRDA_CLEAR_OREF)

/** @brief  Clear the IRDA IDLE pending flag.
  * @param  __HANDLE__: specifies the IRDA Handle.
  * @retval None
  */
#define __HAL_IRDA_CLEAR_IDLEFLAG(__HANDLE__)   __HAL_IRDA_CLEAR_FLAG(__HANDLE__, IRDA_CLEAR_IDLEF)

/** @brief  Check whether the specified IRDA flag is set or not.
  * @param  __HANDLE__: specifies the IRDA Handle.
  *         The Handle Instance which can be USART1 or USART2.
  *         UART peripheral
  * @param  __FLAG__: specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg IRDA_FLAG_REACK: Receive enable ackowledge flag
  *            @arg IRDA_FLAG_TEACK: Transmit enable ackowledge flag
  *            @arg IRDA_FLAG_BUSY:  Busy flag
  *            @arg IRDA_FLAG_ABRF:  Auto Baud rate detection flag
  *            @arg IRDA_FLAG_ABRE:  Auto Baud rate detection error flag
  *            @arg IRDA_FLAG_TXE:   Transmit data register empty flag
  *            @arg IRDA_FLAG_TC:    Transmission Complete flag
  *            @arg IRDA_FLAG_RXNE:  Receive data register not empty flag
  *            @arg IRDA_FLAG_IDLE:  Idle Line detection flag
  *            @arg IRDA_FLAG_ORE:   OverRun Error flag
  *            @arg IRDA_FLAG_NE:    Noise Error flag
  *            @arg IRDA_FLAG_FE:    Framing Error flag
  *            @arg IRDA_FLAG_PE:    Parity Error flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_IRDA_GET_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->ISR & (__FLAG__)) == (__FLAG__))   

/** @brief  Enable the specified IRDA interrupt.
  * @param  __HANDLE__: specifies the IRDA Handle.
  *         The Handle Instance which can be USART1 or USART2.
  *         UART peripheral
  * @param  __INTERRUPT__: specifies the IRDA interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg IRDA_IT_TXE:  Transmit Data Register empty interrupt
  *            @arg IRDA_IT_TC:   Transmission complete interrupt
  *            @arg IRDA_IT_RXNE: Receive Data register not empty interrupt
  *            @arg IRDA_IT_IDLE: Idle line detection interrupt
  *            @arg IRDA_IT_PE:   Parity Error interrupt
  *            @arg IRDA_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
  * @retval None
  */
#define __HAL_IRDA_ENABLE_IT(__HANDLE__, __INTERRUPT__) (((((uint8_t)(__INTERRUPT__)) >> 5) == 1)? ((__HANDLE__)->Instance->CR1 |= (1 << ((__INTERRUPT__) & IRDA_IT_MASK))): \
                                                          ((((uint8_t)(__INTERRUPT__)) >> 5) == 2)? ((__HANDLE__)->Instance->CR2 |= (1 << ((__INTERRUPT__) & IRDA_IT_MASK))): \
                                                          ((__HANDLE__)->Instance->CR3 |= (1 << ((__INTERRUPT__) & IRDA_IT_MASK))))

/** @brief  Disable the specified IRDA interrupt.
  * @param  __HANDLE__: specifies the IRDA Handle.
  *         The Handle Instance which can be USART1 or USART2.
  * @param  __INTERRUPT__: specifies the IRDA interrupt source to disable.
  *          This parameter can be one of the following values:
  *            @arg IRDA_IT_TXE:  Transmit Data Register empty interrupt
  *            @arg IRDA_IT_TC:   Transmission complete interrupt
  *            @arg IRDA_IT_RXNE: Receive Data register not empty interrupt
  *            @arg IRDA_IT_IDLE: Idle line detection interrupt
  *            @arg IRDA_IT_PE:   Parity Error interrupt
  *            @arg IRDA_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
  * @retval None
  */
#define __HAL_IRDA_DISABLE_IT(__HANDLE__, __INTERRUPT__)  (((((uint8_t)(__INTERRUPT__)) >> 5) == 1)? ((__HANDLE__)->Instance->CR1 &= ~ ((uint32_t)1 << ((__INTERRUPT__) & IRDA_IT_MASK))): \
                                                           ((((uint8_t)(__INTERRUPT__)) >> 5) == 2)? ((__HANDLE__)->Instance->CR2 &= ~ ((uint32_t)1 << ((__INTERRUPT__) & IRDA_IT_MASK))): \
                                                           ((__HANDLE__)->Instance->CR3 &= ~ ((uint32_t)1 << ((__INTERRUPT__) & IRDA_IT_MASK))))

/** @brief  Check whether the specified IRDA interrupt has occurred or not.
  * @param  __HANDLE__: specifies the IRDA Handle.
  *         The Handle Instance which can be USART1 or USART2.
  * @param  __IT__: specifies the IRDA interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg IRDA_IT_TXE: Transmit Data Register empty interrupt
  *            @arg IRDA_IT_TC:  Transmission complete interrupt
  *            @arg IRDA_IT_RXNE: Receive Data register not empty interrupt
  *            @arg IRDA_IT_IDLE: Idle line detection interrupt
  *            @arg IRDA_IT_ORE: OverRun Error interrupt
  *            @arg IRDA_IT_NE: Noise Error interrupt
  *            @arg IRDA_IT_FE: Framing Error interrupt
  *            @arg IRDA_IT_PE: Parity Error interrupt  
  * @retval The new state of __IT__ (TRUE or FALSE).
  */
#define __HAL_IRDA_GET_IT(__HANDLE__, __IT__) ((__HANDLE__)->Instance->ISR & ((uint32_t)1 << ((__IT__)>> 0x08))) 

/** @brief  Check whether the specified IRDA interrupt source is enabled.
  * @param  __HANDLE__: specifies the IRDA Handle.
  *         The Handle Instance which can be USART1 or USART2.
  * @param  __IT__: specifies the IRDA interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg IRDA_IT_TXE: Transmit Data Register empty interrupt
  *            @arg IRDA_IT_TC:  Transmission complete interrupt
  *            @arg IRDA_IT_RXNE: Receive Data register not empty interrupt
  *            @arg IRDA_IT_IDLE: Idle line detection interrupt
  *            @arg IRDA_IT_ORE: OverRun Error interrupt
  *            @arg IRDA_IT_NE: Noise Error interrupt
  *            @arg IRDA_IT_FE: Framing Error interrupt
  *            @arg IRDA_IT_PE: Parity Error interrupt  
  * @retval The new state of __IT__ (TRUE or FALSE).
  */
#define __HAL_IRDA_GET_IT_SOURCE(__HANDLE__, __IT__) ((((((uint8_t)(__IT__)) >> 5) == 1)? (__HANDLE__)->Instance->CR1:(((((uint8_t)(__IT__)) >> 5) == 2)? \
                                                          (__HANDLE__)->Instance->CR2 : (__HANDLE__)->Instance->CR3)) & ((uint32_t)1 << (((uint16_t)(__IT__)) & IRDA_IT_MASK)))

/** @brief  Clear the specified IRDA ISR flag, in setting the proper ICR register flag.
  * @param  __HANDLE__: specifies the IRDA Handle.
  *         The Handle Instance which can be USART1 or USART2.
  * @param  __IT_CLEAR__: specifies the interrupt clear register flag that needs to be set
  *                       to clear the corresponding interrupt
  *          This parameter can be one of the following values:
  *            @arg IRDA_CLEAR_PEF: Parity Error Clear Flag
  *            @arg IRDA_CLEAR_FEF: Framing Error Clear Flag
  *            @arg IRDA_CLEAR_NEF: Noise detected Clear Flag
  *            @arg IRDA_CLEAR_OREF: OverRun Error Clear Flag
  *            @arg IRDA_CLEAR_TCF: Transmission Complete Clear Flag 
  * @retval None
  */
#define __HAL_IRDA_CLEAR_IT(__HANDLE__, __IT_CLEAR__) ((__HANDLE__)->Instance->ICR |= (uint32_t)(__IT_CLEAR__))

/** @brief  Set a specific IRDA request flag.
  * @param  __HANDLE__: specifies the IRDA Handle.
  *         The Handle Instance which can be USART1 or USART2.
  * @param  __REQ__: specifies the request flag to set
  *          This parameter can be one of the following values:
  *            @arg IRDA_AUTOBAUD_REQUEST: Auto-Baud Rate Request     
  *            @arg IRDA_RXDATA_FLUSH_REQUEST: Receive Data flush Request 
  *            @arg IRDA_TXDATA_FLUSH_REQUEST: Transmit data flush Request 
  *
  * @retval None
  */
#define __HAL_IRDA_SEND_REQ(__HANDLE__, __REQ__) ((__HANDLE__)->Instance->RQR |= (uint32_t)(__REQ__))

/** @brief  Enables the IRDA one bit sample method
  * @param  __HANDLE__: specifies the IRDA Handle.
  * @retval None
  */
#define __HAL_IRDA_ONE_BIT_SAMPLE_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR3|= USART_CR3_ONEBIT)

/** @brief  Disables the IRDA one bit sample method
  * @param  __HANDLE__: specifies the IRDA Handle.
  * @retval None
  */
#define __HAL_IRDA_ONE_BIT_SAMPLE_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->CR3 &= (uint32_t)~((uint32_t)USART_CR3_ONEBIT))

/** @brief  Enable UART/USART associated to IRDA Handle
  * @param  __HANDLE__: specifies the IRDA Handle.
  *         The Handle Instance which can be USART1 or USART2.
  * @retval None
  */
#define __HAL_IRDA_ENABLE(__HANDLE__)                   ((__HANDLE__)->Instance->CR1 |=  USART_CR1_UE)

/** @brief  Disable UART/USART associated to IRDA Handle
  * @param  __HANDLE__: specifies the IRDA Handle.
  *         The Handle Instance which can be USART1 or USART2.
  * @retval None
  */
#define __HAL_IRDA_DISABLE(__HANDLE__)                  ((__HANDLE__)->Instance->CR1 &=  ~USART_CR1_UE)

/** @brief  Ensure that IRDA Baud rate is less or equal to maximum value
  * @param  __BAUDRATE__: specifies the IRDA Baudrate set by the user.
  * @retval True or False
  */   
#define IS_IRDA_BAUDRATE(__BAUDRATE__) ((__BAUDRATE__) < 115201)

/** @brief  Ensure that IRDA prescaler value is strictly larger than 0
  * @param  __PRESCALER__: specifies the IRDA prescaler value set by the user.
  * @retval True or False
  */  
#define IS_IRDA_PRESCALER(__PRESCALER__) ((__PRESCALER__) > 0)

/**
 * @}
 */

/* Include IRDA HAL Extension module */
#include "stm32l0xx_hal_irda_ex.h"  

/* Exported functions --------------------------------------------------------*/
/** @defgroup IRDA_Exported_Functions IRDA Exported Functions
  * @{
  */

/** @defgroup IRDA_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
/* Exported functions --------------------------------------------------------*/
/* Initialization/de-initialization methods  **********************************/
HAL_StatusTypeDef HAL_IRDA_Init(IRDA_HandleTypeDef *hirda);
HAL_StatusTypeDef HAL_IRDA_DeInit(IRDA_HandleTypeDef *hirda);
void HAL_IRDA_MspInit(IRDA_HandleTypeDef *hirda);
void HAL_IRDA_MspDeInit(IRDA_HandleTypeDef *hirda);
/**
  * @}
  */

/** @defgroup IRDA_Exported_Functions_Group2 IRDA IO operationfunctions
  * @{
  */

/* IO operation methods *******************************************************/
HAL_StatusTypeDef HAL_IRDA_Transmit(IRDA_HandleTypeDef *hirda, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_IRDA_Receive(IRDA_HandleTypeDef *hirda, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_IRDA_Transmit_IT(IRDA_HandleTypeDef *hirda, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_IRDA_Receive_IT(IRDA_HandleTypeDef *hirda, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_IRDA_Transmit_DMA(IRDA_HandleTypeDef *hirda, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_IRDA_Receive_DMA(IRDA_HandleTypeDef *hirda, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_IRDA_DMAPause(IRDA_HandleTypeDef *hirda);
HAL_StatusTypeDef HAL_IRDA_DMAResume(IRDA_HandleTypeDef *hirda);
HAL_StatusTypeDef HAL_IRDA_DMAStop(IRDA_HandleTypeDef *hirda);
void HAL_IRDA_IRQHandler(IRDA_HandleTypeDef *hirda);
void HAL_IRDA_TxCpltCallback(IRDA_HandleTypeDef *hirda);
void HAL_IRDA_RxCpltCallback(IRDA_HandleTypeDef *hirda);
void HAL_IRDA_TxHalfCpltCallback(IRDA_HandleTypeDef *hirda);
void HAL_IRDA_RxHalfCpltCallback(IRDA_HandleTypeDef *hirda);
void HAL_IRDA_ErrorCallback(IRDA_HandleTypeDef *hirda);
/**
  * @}
  */

/** @defgroup IRDA_Exported_Functions_Group3 Peripheral Control functions
  * @{
  */
/* Peripheral State methods  **************************************************/
HAL_IRDA_StateTypeDef HAL_IRDA_GetState(IRDA_HandleTypeDef *hirda);
uint32_t HAL_IRDA_GetError(IRDA_HandleTypeDef *hirda);

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

#endif /* __STM32L0xx_HAL_IRDA_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

