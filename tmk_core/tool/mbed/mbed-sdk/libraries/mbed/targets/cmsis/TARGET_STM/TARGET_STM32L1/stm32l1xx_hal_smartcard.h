/**
  ******************************************************************************
  * @file    stm32l1xx_hal_smartcard.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   This file contains all the functions prototypes for the SMARTCARD 
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
#ifndef __STM32L1xx_HAL_SMARTCARD_H
#define __STM32L1xx_HAL_SMARTCARD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @addtogroup SMARTCARD
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup SMARTCARD_Exported_Types SMARTCARD Exported Types
  * @{
  */ 


/** 
  * @brief SMARTCARD Init Structure definition
  */
typedef struct
{
  uint32_t BaudRate;                  /*!< This member configures the SmartCard communication baud rate.
                                           The baud rate is computed using the following formula:
                                           - IntegerDivider = ((PCLKx) / (8 * (hsc->Init.BaudRate)))
                                           - FractionalDivider = ((IntegerDivider - ((uint32_t) IntegerDivider)) * 8) + 0.5 */

  uint32_t WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref SMARTCARD_Word_Length */

  uint32_t StopBits;                  /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref SMARTCARD_Stop_Bits */

  uint32_t Parity;                   /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref SMARTCARD_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                 word length is set to 8 data bits).*/

  uint32_t Mode;                      /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref SMARTCARD_Mode */

  uint32_t CLKPolarity;               /*!< Specifies the steady state of the serial clock.
                                           This parameter can be a value of @ref SMARTCARD_Clock_Polarity */

  uint32_t CLKPhase;                  /*!< Specifies the clock transition on which the bit capture is made.
                                           This parameter can be a value of @ref SMARTCARD_Clock_Phase */

  uint32_t CLKLastBit;                /*!< Specifies whether the clock pulse corresponding to the last transmitted
                                           data bit (MSB) has to be output on the SCLK pin in synchronous mode.
                                           This parameter can be a value of @ref SMARTCARD_Last_Bit */

  uint32_t  Prescaler;                 /*!< Specifies the SmartCard Prescaler 
                                           This parameter must be a number between Min_Data = 0 and Max_Data = 255 */

  uint32_t  GuardTime;                 /*!< Specifies the SmartCard Guard Time 
                                            This parameter must be a number between Min_Data = 0 and Max_Data = 255 */

  uint32_t NACKState;                 /*!< Specifies the SmartCard NACK Transmission state
                                           This parameter can be a value of @ref SMARTCARD_NACK_State */
}SMARTCARD_InitTypeDef;

/** 
  * @brief HAL State structures definition
  */
typedef enum
{
  HAL_SMARTCARD_STATE_RESET             = 0x00,    /*!< Peripheral is not yet Initialized */
  HAL_SMARTCARD_STATE_READY             = 0x01,    /*!< Peripheral Initialized and ready for use */
  HAL_SMARTCARD_STATE_BUSY              = 0x02,    /*!< an internal process is ongoing */
  HAL_SMARTCARD_STATE_BUSY_TX           = 0x12,    /*!< Data Transmission process is ongoing */
  HAL_SMARTCARD_STATE_BUSY_RX           = 0x22,    /*!< Data Reception process is ongoing */
  HAL_SMARTCARD_STATE_BUSY_TX_RX        = 0x32,    /*!< Data Transmission and Reception process is ongoing */ 
  HAL_SMARTCARD_STATE_TIMEOUT           = 0x03,    /*!< Timeout state */
  HAL_SMARTCARD_STATE_ERROR             = 0x04     /*!< Error */
}HAL_SMARTCARD_StateTypeDef;

/** 
  * @brief  HAL SMARTCARD Error Code structure definition
  */
typedef enum
{
  HAL_SMARTCARD_ERROR_NONE      = 0x00,    /*!< No error            */
  HAL_SMARTCARD_ERROR_PE        = 0x01,    /*!< Parity error        */
  HAL_SMARTCARD_ERROR_NE        = 0x02,    /*!< Noise error         */
  HAL_SMARTCARD_ERROR_FE        = 0x04,    /*!< frame error         */
  HAL_SMARTCARD_ERROR_ORE       = 0x08,    /*!< Overrun error       */
  HAL_SMARTCARD_ERROR_DMA       = 0x10     /*!< DMA transfer error  */
}HAL_SMARTCARD_ErrorTypeDef;

/** 
  * @brief  SMARTCARD handle Structure definition
  */
typedef struct
{
  USART_TypeDef                    *Instance;        /* USART registers base address */

  SMARTCARD_InitTypeDef            Init;             /* SmartCard communication parameters */

  uint8_t                          *pTxBuffPtr;      /* Pointer to SmartCard Tx transfer Buffer */

  uint16_t                         TxXferSize;       /* SmartCard Tx Transfer size */

  uint16_t                         TxXferCount;      /* SmartCard Tx Transfer Counter */

  uint8_t                          *pRxBuffPtr;      /* Pointer to SmartCard Rx transfer Buffer */

  uint16_t                         RxXferSize;       /* SmartCard Rx Transfer size */

  uint16_t                         RxXferCount;      /* SmartCard Rx Transfer Counter */

  DMA_HandleTypeDef                *hdmatx;          /* SmartCard Tx DMA Handle parameters */

  DMA_HandleTypeDef                *hdmarx;          /* SmartCard Rx DMA Handle parameters */

  HAL_LockTypeDef                  Lock;            /* Locking object */

  __IO HAL_SMARTCARD_StateTypeDef  State;           /* SmartCard communication state */

  __IO HAL_SMARTCARD_ErrorTypeDef  ErrorCode;       /* SmartCard Error code */
}SMARTCARD_HandleTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup SMARTCARD_Exported_Constants  SMARTCARD Exported constants
  * @{
  */

/** @defgroup SMARTCARD_Word_Length SMARTCARD Word Length
  * @{
  */
#define SMARTCARD_WORDLENGTH_8B                  ((uint32_t)0x00000000)
#define SMARTCARD_WORDLENGTH_9B                  ((uint32_t)USART_CR1_M)
#define IS_SMARTCARD_WORD_LENGTH(LENGTH) ((LENGTH) == SMARTCARD_WORDLENGTH_9B)
/**
  * @}
  */

/** @defgroup SMARTCARD_Stop_Bits SMARTCARD Number of Stop Bits
  * @{
  */
#define SMARTCARD_STOPBITS_1                     ((uint32_t)0x00000000)
#define SMARTCARD_STOPBITS_0_5                   ((uint32_t)USART_CR2_STOP_0)
#define SMARTCARD_STOPBITS_2                     ((uint32_t)USART_CR2_STOP_1)
#define SMARTCARD_STOPBITS_1_5                   ((uint32_t)(USART_CR2_STOP_0 | USART_CR2_STOP_1))
#define IS_SMARTCARD_STOPBITS(STOPBITS) (((STOPBITS) == SMARTCARD_STOPBITS_0_5) || \
                                         ((STOPBITS) == SMARTCARD_STOPBITS_1_5))
/**
  * @}
  */

/** @defgroup SMARTCARD_Parity SMARTCARD Parity
  * @{
  */
#define SMARTCARD_PARITY_NONE                    ((uint32_t)0x00000000)
#define SMARTCARD_PARITY_EVEN                    ((uint32_t)USART_CR1_PCE)
#define SMARTCARD_PARITY_ODD                     ((uint32_t)(USART_CR1_PCE | USART_CR1_PS)) 
#define IS_SMARTCARD_PARITY(PARITY) (((PARITY) == SMARTCARD_PARITY_EVEN) || \
                                     ((PARITY) == SMARTCARD_PARITY_ODD))
/**
  * @}
  */

/** @defgroup SMARTCARD_Mode SMARTCARD Mode
  * @{
  */
#define SMARTCARD_MODE_RX                        ((uint32_t)USART_CR1_RE)
#define SMARTCARD_MODE_TX                        ((uint32_t)USART_CR1_TE)
#define SMARTCARD_MODE_TX_RX                     ((uint32_t)(USART_CR1_TE |USART_CR1_RE))
#define IS_SMARTCARD_MODE(MODE) ((((MODE) & (uint32_t)0x0000FFF3) == 0x00) && ((MODE) != (uint32_t)0x00000000))
/**
  * @}
  */

/** @defgroup SMARTCARD_Clock_Polarity  SMARTCARD Clock Polarity
  * @{
  */
#define SMARTCARD_POLARITY_LOW                   ((uint32_t)0x00000000)
#define SMARTCARD_POLARITY_HIGH                  ((uint32_t)USART_CR2_CPOL)
#define IS_SMARTCARD_POLARITY(CPOL) (((CPOL) == SMARTCARD_POLARITY_LOW) || ((CPOL) == SMARTCARD_POLARITY_HIGH))
/**
  * @}
  */ 

/** @defgroup SMARTCARD_Clock_Phase SMARTCARD Clock Phase
  * @{
  */
#define SMARTCARD_PHASE_1EDGE                    ((uint32_t)0x00000000)
#define SMARTCARD_PHASE_2EDGE                    ((uint32_t)USART_CR2_CPHA)
#define IS_SMARTCARD_PHASE(CPHA) (((CPHA) == SMARTCARD_PHASE_1EDGE) || ((CPHA) == SMARTCARD_PHASE_2EDGE))
/**
  * @}
  */

/** @defgroup SMARTCARD_Last_Bit  SMARTCARD Last Bit
  * @{
  */
#define SMARTCARD_LASTBIT_DISABLE                ((uint32_t)0x00000000)
#define SMARTCARD_LASTBIT_ENABLE                 ((uint32_t)USART_CR2_LBCL)
#define IS_SMARTCARD_LASTBIT(LASTBIT) (((LASTBIT) == SMARTCARD_LASTBIT_DISABLE) || \
                                       ((LASTBIT) == SMARTCARD_LASTBIT_ENABLE))
/**
  * @}
  */

/** @defgroup SMARTCARD_NACK_State   SMARTCARD NACK State
  * @{
  */
#define SMARTCARD_NACK_ENABLED                  ((uint32_t)USART_CR3_NACK)
#define SMARTCARD_NACK_DISABLED                 ((uint32_t)0x00000000)
#define IS_SMARTCARD_NACK_STATE(NACK) (((NACK) == SMARTCARD_NACK_ENABLED) || \
                                       ((NACK) == SMARTCARD_NACK_DISABLED))
/**
  * @}
  */

/** @defgroup SMARTCARD_DMA_Requests SMARTCARD DMA requests
  * @{
  */

#define SMARTCARD_DMAREQ_TX                    ((uint32_t)USART_CR3_DMAT)
#define SMARTCARD_DMAREQ_RX                    ((uint32_t)USART_CR3_DMAR)

/**
  * @}
  */

/** @defgroup SMARTCARD_Flags    SMARTCARD Flags
  *        Elements values convention: 0xXXXX
  *           - 0xXXXX  : Flag mask in the SR register
  * @{
  */

#define SMARTCARD_FLAG_TXE                       ((uint32_t)USART_SR_TXE)
#define SMARTCARD_FLAG_TC                        ((uint32_t)USART_SR_TC)
#define SMARTCARD_FLAG_RXNE                      ((uint32_t)USART_SR_RXNE)
#define SMARTCARD_FLAG_IDLE                      ((uint32_t)USART_SR_IDLE)
#define SMARTCARD_FLAG_ORE                       ((uint32_t)USART_SR_ORE)
#define SMARTCARD_FLAG_NE                        ((uint32_t)USART_SR_NE)
#define SMARTCARD_FLAG_FE                        ((uint32_t)USART_SR_FE)
#define SMARTCARD_FLAG_PE                        ((uint32_t)USART_SR_PE)
/**
  * @}
  */

/** @defgroup SMARTCARD_Interrupt_definition     SMARTCARD Interrupts Definition
  *        Elements values convention: 0xY000XXXX
  *           - XXXX  : Interrupt mask in the XX register
  *           - Y  : Interrupt source register (4 bits)
  *                 - 01: CR1 register
  *                 - 10: CR3 register

  *
  * @{
  */
#define SMARTCARD_IT_PE                          ((uint32_t)0x10000100)
#define SMARTCARD_IT_TXE                         ((uint32_t)0x10000080)
#define SMARTCARD_IT_TC                          ((uint32_t)0x10000040)
#define SMARTCARD_IT_RXNE                        ((uint32_t)0x10000020)
#define SMARTCARD_IT_IDLE                        ((uint32_t)0x10000010)
#define SMARTCARD_IT_ERR                         ((uint32_t)0x20000001)

/**
  * @}
  */

/** @defgroup SMARTCARD_Interruption_Mask    SMARTCARD interruptions flag mask
  * @{
  */ 
#define SMARTCARD_IT_MASK  ((uint32_t)0x0000FFFF)
/**
  * @}
  */

/**
  * @}
  */
  
/* Exported macro ------------------------------------------------------------*/
/** @defgroup SMARTCARD_Exported_Macros SMARTCARD Exported Macros
  * @{
  */


/** @brief Reset SMARTCARD handle state
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  *         This parameter can be USARTx with x: 1, 2 or 3.
  * @retval None
  */
#define __HAL_SMARTCARD_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_SMARTCARD_STATE_RESET)

/** @brief  Flushs the Smartcard DR register 
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  *         This parameter can be USARTx with x: 1, 2 or 3.
  */
#define __HAL_SMARTCARD_FLUSH_DRREGISTER(__HANDLE__) ((__HANDLE__)->Instance->DR)
    
/** @brief  Checks whether the specified Smartcard flag is set or not.
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  *         This parameter can be USARTx with x: 1, 2 or 3.
  * @param  __FLAG__: specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg SMARTCARD_FLAG_TXE:  Transmit data register empty flag
  *            @arg SMARTCARD_FLAG_TC:   Transmission Complete flag
  *            @arg SMARTCARD_FLAG_RXNE: Receive data register not empty flag
  *            @arg SMARTCARD_FLAG_IDLE: Idle Line detection flag
  *            @arg SMARTCARD_FLAG_ORE:  OverRun Error flag
  *            @arg SMARTCARD_FLAG_NE:   Noise Error flag
  *            @arg SMARTCARD_FLAG_FE:   Framing Error flag
  *            @arg SMARTCARD_FLAG_PE:   Parity Error flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_SMARTCARD_GET_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->SR & (__FLAG__)) == (__FLAG__))

/** @brief  Clears the specified Smartcard pending flags.
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  *         This parameter can be USARTx with x: 1, 2 or 3.
  * @param  __FLAG__: specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg SMARTCARD_FLAG_TC:   Transmission Complete flag.
  *            @arg SMARTCARD_FLAG_RXNE: Receive data register not empty flag.
  *   
  * @note   PE (Parity error), FE (Framing error), NE (Noise error) and ORE (OverRun 
  *          error) flags are cleared by software sequence: a read operation to 
  *          USART_SR register followed by a read operation to USART_DR register.
  * @note   RXNE flag can be also cleared by a read to the USART_DR register.
  * @note   TC flag can be also cleared by software sequence: a read operation to 
  *          USART_SR register followed by a write operation to USART_DR register.
  * @note   TXE flag is cleared only by a write to the USART_DR register.
  *   
  * @retval None
  */
#define __HAL_SMARTCARD_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->SR = ~(__FLAG__))

/** @brief  Clear the SMARTCARD PE pending flag.
  * @param  __HANDLE__: specifies the USART Handle.
  *         This parameter can be USARTx with x: 1, 2 or 3.
  * @retval None
  */
#define __HAL_SMARTCARD_CLEAR_PEFLAG(__HANDLE__) do{(__HANDLE__)->Instance->SR;\
                                               (__HANDLE__)->Instance->DR;}while(0)
/** @brief  Clear the SMARTCARD FE pending flag.
  * @param  __HANDLE__: specifies the USART Handle.
  *         This parameter can be USARTx with x: 1, 2 or 3.
  * @retval None
  */
#define __HAL_SMARTCARD_CLEAR_FEFLAG(__HANDLE__) __HAL_SMARTCARD_CLEAR_PEFLAG(__HANDLE__)

/** @brief  Clear the SMARTCARD NE pending flag.
  * @param  __HANDLE__: specifies the USART Handle.
  *         This parameter can be USARTx with x: 1, 2 or 3.
  * @retval None
  */
#define __HAL_SMARTCARD_CLEAR_NEFLAG(__HANDLE__) __HAL_SMARTCARD_CLEAR_PEFLAG(__HANDLE__)

/** @brief  Clear the SMARTCARD ORE pending flag.
  * @param  __HANDLE__: specifies the USART Handle.
  *         This parameter can be USARTx with x: 1, 2 or 3.
  * @retval None
  */
#define __HAL_SMARTCARD_CLEAR_OREFLAG(__HANDLE__) __HAL_SMARTCARD_CLEAR_PEFLAG(__HANDLE__)

/** @brief  Clear the SMARTCARD IDLE pending flag.
  * @param  __HANDLE__: specifies the USART Handle.
  *         This parameter can be USARTx with x: 1, 2 or 3.
  * @retval None
  */
#define __HAL_SMARTCARD_CLEAR_IDLEFLAG(__HANDLE__) __HAL_SMARTCARD_CLEAR_PEFLAG(__HANDLE__)

/** @brief  Enables the specified SmartCard interrupt.
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  *         This parameter can be USARTx with x: 1, 2 or 3.
  * @param  __INTERRUPT__: specifies the SMARTCARD interrupt to enable.
  *          This parameter can be one of the following values:
  *            @arg SMARTCARD_IT_TXE:  Transmit Data Register empty interrupt
  *            @arg SMARTCARD_IT_TC:   Transmission complete interrupt
  *            @arg SMARTCARD_IT_RXNE: Receive Data register not empty interrupt
  *            @arg SMARTCARD_IT_IDLE: Idle line detection interrupt
  *            @arg SMARTCARD_IT_PE:   Parity Error interrupt
  *            @arg SMARTCARD_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
  */
#define __HAL_SMARTCARD_ENABLE_IT(__HANDLE__, __INTERRUPT__)   ((((__INTERRUPT__) >> 28) == 1)? ((__HANDLE__)->Instance->CR1 |= ((__INTERRUPT__) & SMARTCARD_IT_MASK)): \
                                                               ((__HANDLE__)->Instance->CR3 |= ((__INTERRUPT__) & SMARTCARD_IT_MASK)))

/** @brief  Disables the specified SmartCard interrupts.
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  *         This parameter can be USARTx with x: 1, 2 or 3.
  * @param  __INTERRUPT__: specifies the SMARTCARD interrupt to disable.
  *          This parameter can be one of the following values:
  *            @arg SMARTCARD_IT_TXE:  Transmit Data Register empty interrupt
  *            @arg SMARTCARD_IT_TC:   Transmission complete interrupt
  *            @arg SMARTCARD_IT_RXNE: Receive Data register not empty interrupt
  *            @arg SMARTCARD_IT_IDLE: Idle line detection interrupt
  *            @arg SMARTCARD_IT_PE:   Parity Error interrupt
  *            @arg SMARTCARD_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
  */
#define __HAL_SMARTCARD_DISABLE_IT(__HANDLE__, __INTERRUPT__)  ((((__INTERRUPT__) >> 28) == 1)? ((__HANDLE__)->Instance->CR1 &= ~((__INTERRUPT__) & SMARTCARD_IT_MASK)): \
                                                               ((__HANDLE__)->Instance->CR3 &= ~ ((__INTERRUPT__) & SMARTCARD_IT_MASK)))

/** @brief  Checks whether the specified SmartCard interrupt has occurred or not.
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  *         This parameter can be USARTx with x: 1, 2 or 3.
  * @param  __IT__: specifies the SMARTCARD interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg SMARTCARD_IT_TXE: Transmit Data Register empty interrupt
  *            @arg SMARTCARD_IT_TC:  Transmission complete interrupt
  *            @arg SMARTCARD_IT_RXNE: Receive Data register not empty interrupt
  *            @arg SMARTCARD_IT_IDLE: Idle line detection interrupt
  *            @arg SMARTCARD_IT_ERR: Error interrupt
  *            @arg SMARTCARD_IT_PE: Parity Error interrupt
  * @retval The new state of __IT__ (TRUE or FALSE).
  */
#define __HAL_SMARTCARD_GET_IT_SOURCE(__HANDLE__, __IT__) (((((__IT__) >> 28) == 1)? (__HANDLE__)->Instance->CR1: (__HANDLE__)->Instance->CR3) & (((uint32_t)(__IT__)) & SMARTCARD_IT_MASK))

/** @brief  Enable the USART associated to the SMARTCARD Handle
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  *         This parameter can be USARTx with x: 1, 2 or 3.
  * @retval None
  */ 
#define __HAL_SMARTCARD_ENABLE(__HANDLE__)               (SET_BIT((__HANDLE__)->Instance->CR1, USART_CR1_UE))

/** @brief  Disable the USART associated to the SMARTCARD Handle
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  *         This parameter can be USARTx with x: 1, 2 or 3.
  * @retval None
  */ 
#define __HAL_SMARTCARD_DISABLE(__HANDLE__)              (CLEAR_BIT((__HANDLE__)->Instance->CR1, USART_CR1_UE))


/**
  * @}
  */

/* Private macros --------------------------------------------------------*/
/** @defgroup SMARTCARD_Private_Macros   SMARTCARD Private Macros
  * @{
  */

/** @brief  Macros to enable or disable the SmartCard DMA request.
  * @param  __HANDLE__: specifies the SmartCard Handle.
  * @param  __REQUEST__: specifies the SmartCard DMA request.
  *          This parameter can be one of the following values:
  *            @arg SMARTCARD_DMAREQ_TX: SmartCard DMA transmit request
  *            @arg SMARTCARD_DMAREQ_RX: SmartCard DMA receive request
  */
#define SMARTCARD_DMA_REQUEST_ENABLE(__HANDLE__, __REQUEST__)    (SET_BIT((__HANDLE__)->Instance->CR3, (__REQUEST__)))
#define SMARTCARD_DMA_REQUEST_DISABLE(__HANDLE__, __REQUEST__)   (CLEAR_BIT((__HANDLE__)->Instance->CR3, (__REQUEST__)))

#define SMARTCARD_DIV(__PCLK__, __BAUD__)                (((__PCLK__)*25)/(4*(__BAUD__)))
#define SMARTCARD_DIVMANT(__PCLK__, __BAUD__)            (SMARTCARD_DIV((__PCLK__), (__BAUD__))/100)
#define SMARTCARD_DIVFRAQ(__PCLK__, __BAUD__)            (((SMARTCARD_DIV((__PCLK__), (__BAUD__)) - (SMARTCARD_DIVMANT((__PCLK__), (__BAUD__)) * 100)) * 16 + 50) / 100)
#define SMARTCARD_BRR(__PCLK__, __BAUD__)                ((SMARTCARD_DIVMANT((__PCLK__), (__BAUD__)) << 4)|(SMARTCARD_DIVFRAQ((__PCLK__), (__BAUD__)) & 0x0F))

/** @brief  Check the Baud rate range. The maximum Baud Rate is derived from the 
  *         maximum clock on L1 (i.e. 32 MHz) divided by the oversampling used 
  *         on the SMARTCARD (i.e. 16). No overSampling by 16 on Smartcard.
  * @param  __BAUDRATE__: Baud rate set by the configuration function.
  * @retval Test result (TRUE or FALSE) 
  */ 
#define IS_SMARTCARD_BAUDRATE(__BAUDRATE__) ((__BAUDRATE__) < 2000001)
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/

/** @addtogroup SMARTCARD_Exported_Functions SMARTCARD Exported Functions
  * @{
  */
  
/** @addtogroup SMARTCARD_Exported_Functions_Group1 SmartCard Initialization and de-initialization functions 
  * @{
  */

/* Initialization/de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_SMARTCARD_Init(SMARTCARD_HandleTypeDef *hsc);
HAL_StatusTypeDef HAL_SMARTCARD_ReInit(SMARTCARD_HandleTypeDef *hsc);
HAL_StatusTypeDef HAL_SMARTCARD_DeInit(SMARTCARD_HandleTypeDef *hsc);
void HAL_SMARTCARD_MspInit(SMARTCARD_HandleTypeDef *hsc);
void HAL_SMARTCARD_MspDeInit(SMARTCARD_HandleTypeDef *hsc);

/**
  * @}
  */

/** @addtogroup SMARTCARD_Exported_Functions_Group2 IO operation functions 
  * @{
  */

/* IO operation functions *******************************************************/
HAL_StatusTypeDef HAL_SMARTCARD_Transmit(SMARTCARD_HandleTypeDef *hsc, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SMARTCARD_Receive(SMARTCARD_HandleTypeDef *hsc, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SMARTCARD_Transmit_IT(SMARTCARD_HandleTypeDef *hsc, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SMARTCARD_Receive_IT(SMARTCARD_HandleTypeDef *hsc, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SMARTCARD_Transmit_DMA(SMARTCARD_HandleTypeDef *hsc, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SMARTCARD_Receive_DMA(SMARTCARD_HandleTypeDef *hsc, uint8_t *pData, uint16_t Size);
void HAL_SMARTCARD_IRQHandler(SMARTCARD_HandleTypeDef *hsc);
void HAL_SMARTCARD_TxCpltCallback(SMARTCARD_HandleTypeDef *hsc);
void HAL_SMARTCARD_RxCpltCallback(SMARTCARD_HandleTypeDef *hsc);
void HAL_SMARTCARD_ErrorCallback(SMARTCARD_HandleTypeDef *hsc);

/**
  * @}
  */

/** @addtogroup SMARTCARD_Exported_Functions_Group3 Peripheral State and Errors functions 
  * @{
  */

/* Peripheral State and Errors functions functions  *****************************/
HAL_SMARTCARD_StateTypeDef HAL_SMARTCARD_GetState(SMARTCARD_HandleTypeDef *hsc);
uint32_t                   HAL_SMARTCARD_GetError(SMARTCARD_HandleTypeDef *hsc);

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

#endif /* __STM32L1xx_HAL_SMARTCARD_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
